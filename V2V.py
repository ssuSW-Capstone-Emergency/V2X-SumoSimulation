import traci
from utils import calculate_distance
from packet import send_evasion_request
import time

def simulation():
    # Directory
    sumo_binary = "C:\\Users\\1228t\\src\\sumo-1.8.0\\PFiles\\Eclipse\\Sumo\\bin\\sumo-gui"
    sumocfg_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.sumocfg"
    route_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.rou.xml"

    # Run SUMO
    sumo_cmd = [sumo_binary, "-c", sumocfg_dir, "-r", route_dir, "--junction-taz", "--no-warnings", "--random"]
    traci.start(sumo_cmd)
    
    emergency_vehicle_id = "emergency1"  # ID setting
    notify_distance = 5000 # valid range (meter?)

    traci.gui.trackVehicle("View #0", emergency_vehicle_id)  # "View #0"은 기본 GUI 화면 ID

    # GUI 확대 배율 설정
    zoom_level = 3000  # 확대 배율 수준 (예: 3000)
    traci.gui.setZoom("View #0", zoom_level)

    # Running ...
    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2) # 시뮬레이션 속도 조절
        traci.simulationStep()

        try:
            emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)

            # retrieving all vehicle's position and send the packet of emergency vehicle
            for veh_id in traci.vehicle.getIDList():
                position = traci.vehicle.getPosition(veh_id)
                print(f"{veh_id} 위치 : {position}")

                if veh_id != emergency_vehicle_id:
                    distance = calculate_distance(emergency_position, position)
                    print(distance)

                    if distance < notify_distance: # In a valid distance
                        lane_count = traci.vehicle.getLaneIndex(veh_id)
                        print(lane_count)
                        if lane_count == 1:
                            send_evasion_request(emergency_vehicle_id, veh_id, "right_edge")
                            traci.vehicle.changeLane(veh_id, 0, 25.0)  # 차로 0으로 변경하고 25초 동안 유지
                        elif lane_count == 2:
                            send_evasion_request(emergency_vehicle_id, veh_id, "right_lane")
                            traci.vehicle.changeLane(veh_id, 1, 25.0)  # 차로 1로 변경하고 25초 동안 유지
                        elif lane_count == 3:
                            send_evasion_request(emergency_vehicle_id, veh_id, "both_sides")
                            traci.vehicle.changeLane(veh_id, 2, 25.0)  # 차로 2로 변경하고 25초 동안 유지

        except traci.TraCIException as e:
            if str(e) == "Vehicle 'emergency1' is not known.":
                print("Ambulance has arrived at destination")
                break
            else:
                print(e)
                pass

        # traci.close()
        # print("Simulation ended")

    

if __name__ == '__main__':
    simulation() # run