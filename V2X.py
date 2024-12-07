import traci
import time

from utils import *
from packet import *
from V2I import handle_traffic_lights
from random import *

notify_distance = 100 
ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle


# sumoCmd = ["sumo-gui", "-c", "asanH/map/asanH.sumocfg"]  
sumoCmd = ["sumo-gui", "-c", "asanH/map/asanH.sumocfg"]

def scenario_1(emergency_vehicle_id, notify_distance):
    """
    Scenario 1:
    - 기존: 주변 차량이 구급차 접근 시 차선 변경을 통해 회피 동작 수행
    - 수정: 도로가 좁아지는 구간(다음 edge의 차선 수 < 현재 edge의 차선 수)에서
            같은 도로 상 뒤에 있는 일반 차량들은 구급차를 추월하지 않고 뒤에서 대기
    """
    emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)
    current_edge = traci.vehicle.getRoadID(emergency_vehicle_id)
    lane_count = traci.edge.getLaneNumber(current_edge)
    
    # 구급차 경로 파악
    route = traci.vehicle.getRoute(emergency_vehicle_id)
    route_index = traci.vehicle.getRouteIndex(emergency_vehicle_id)

    next_edge = None
    if route_index < len(route)-1:
        next_edge = route[route_index+1]

    next_lane_count = traci.edge.getLaneNumber(next_edge) if next_edge else lane_count

    # 긴급 차량 정지 상태 시 1차선으로 이동 로직
    if traci.vehicle.getSpeed(emergency_vehicle_id) == 0:
        current_lane_index = traci.vehicle.getLaneIndex(emergency_vehicle_id)
        if current_lane_index != 0:
            traci.vehicle.changeLane(emergency_vehicle_id, 0, 25.0)
            print(f"{emergency_vehicle_id}가 정지 상태에서 1차선으로 이동")

    # 차선이 좁아지는 구간인지 판단
    lane_narrowing = (next_lane_count < lane_count)

    # 구급차 현재 도로 상 위치(해당 차선 시작점으로부터의 거리)
    amb_lane_pos = traci.vehicle.getLanePosition(emergency_vehicle_id)

    # 주변 차량 처리
    for veh_id in traci.vehicle.getIDList():
        if veh_id == emergency_vehicle_id:
            continue

        position = traci.vehicle.getPosition(veh_id)
        distance = calculate_distance(emergency_position, position)

        if distance < notify_distance:
            # 도로 좁아지는 구간에서 같은 도로 상 구급차 뒤에 있는 차량 제어
            if lane_narrowing:
                # 같은 도로에 있고, lane position 상 구급차 뒤(작은 값)인 경우
                if traci.vehicle.getRoadID(veh_id) == current_edge:
                    veh_lane_pos = traci.vehicle.getLanePosition(veh_id)
                    if veh_lane_pos < amb_lane_pos:
                        # 뒤에 있는 차량을 강제 감속시켜 추월 불가하게 함
                        traci.vehicle.slowDown(veh_id, 0.0, 10.0)
                        traci.vehicle.setColor(veh_id, (0,0,255)) 
                        print(f"{veh_id}가 병목구간에서 구급차 뒤에서 대기하도록 속도 감소")
            else:
                # 기존 회피 로직(차선 수에 따른 회피)
                current_lane_index_vehicle = traci.vehicle.getLaneIndex(veh_id)
                lane_count = traci.edge.getLaneNumber(current_edge)
                
                if lane_count == 1:
                    continue
                elif lane_count == 2:
                    if current_lane_index_vehicle == 2:
                        send_evasion_request(emergency_vehicle_id, veh_id, "right_edge")
                        traci.vehicle.changeLane(veh_id, 1, 25.0)
                    
                    traci.vehicle.changeLane(emergency_vehicle_id, 1, 25.0)
                elif lane_count >= 3:
                    if current_lane_index_vehicle == 2:
                        ran = randint(1,10)
                        if ran >= 5:
                            send_evasion_request(emergency_vehicle_id, veh_id, "right_edge")
                            traci.vehicle.changeLane(veh_id, 0, 25.0)
                            traci.vehicle.changeLane(emergency_vehicle_id, 1, 25.0)
                        else:
                            send_evasion_request(emergency_vehicle_id, veh_id, "left_edge")
                            traci.vehicle.changeLane(emergency_vehicle_id, 1, 25.0)
                            traci.vehicle.changeLane(veh_id, 2, 25.0)


            

def handle_v2i():
    handle_traffic_lights(ambulance_id)

def scenario_2(emergency_vehicle_id, notify_distance, min_change_interval=5.0):
    """
    Scenario 2: The emergency vehicle optimizes its route by moving to
    the lane with the least congestion, while surrounding vehicles do not evade.
    """
    # Record the last time the lane was changed
    if not hasattr(scenario_2, "last_changed_lane_time"):
        scenario_2.last_changed_lane_time = 0

    current_time = traci.simulation.getTime()
    emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)

    # Consider vehicles within notify_distance
    close_vehicles = [
        veh_id for veh_id in traci.vehicle.getIDList()
        if calculate_distance(emergency_position, traci.vehicle.getPosition(veh_id)) < notify_distance and veh_id != emergency_vehicle_id
    ]
    if close_vehicles:
        # Only check for lane change if sufficient time has passed
        if current_time - scenario_2.last_changed_lane_time >= min_change_interval:
            min_lane_index, _ = find_least_congested_lane(emergency_vehicle_id)
            if min_lane_index is not None and traci.vehicle.getLaneIndex(emergency_vehicle_id) != min_lane_index:
                traci.vehicle.changeLane(emergency_vehicle_id, min_lane_index, 25.0)  # Move to the least congested lane
                scenario_2.last_changed_lane_time = current_time  # Update last changed time
                print(f"Emergency vehicle moved to lane {min_lane_index}")

# Main function to run the simulation
def simulation(scenario):
    # Start the TraCI server with SUMO configuration file
    traci.start(sumoCmd)

    traci.gui.trackVehicle("View #0", ambulance_id)  # "View #0" is the default GUI screen ID

 #   GUI zoom level
    zoom_level = 3000 
    traci.gui.setZoom("View #0", zoom_level)

    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2)  # Simulation speed control
        traci.simulationStep()

        try:
            handle_v2i()
            if scenario == 1:
                scenario_1(ambulance_id, notify_distance)
            elif scenario == 2:
                scenario_2(ambulance_id, notify_distance)
        except traci.TraCIException as e:
            # Handle exceptions (e.g., ambulance has arrived at destination)
            if str(e) == f"Vehicle '{ambulance_id}' is not known.":
                print("Ambulance has arrived at destination")
                break
            else:
                print(str(e))
                pass

    traci.close()
    print("Simulation ended")

if __name__ == '__main__':
    # Choose scenario (1 or 2)
    selected_scenario = int(input("Enter scenario (1 or 2): "))
    simulation(selected_scenario)
