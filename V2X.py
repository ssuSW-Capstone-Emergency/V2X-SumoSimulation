import traci
import time

from utils import *
from packet import *

# Main function to run the simulation
def run_simulation():
    # Start the TraCI server with SUMO configuration file
    sumoCmd = ["sumo-gui", "-c", "/cauH/map/cauH.sumocfg"]
    traci.start(sumoCmd)

    ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle
    passed_tls = set()

    traci.gui.trackVehicle("View #0", ambulance_id)  # "View #0"은 기본 GUI 화면 ID

    notify_distance = 5000 # valid range

    # GUI 확대 배율 설정
    zoom_level = 3000  # 확대 배율 수준 (예: 3000)
    traci.gui.setZoom("View #0", zoom_level)

    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2) # 시뮬레이션 속도 조절
        traci.simulationStep()

        try:
            # Get the ambulance's position and lane
            ambulance_lane = get_ambulance_lane(ambulance_id)
            emergency_position = traci.vehicle.getPosition(ambulance_id)
            # Get upcoming traffic lights
            traffic_lights = get_upcoming_traffic_lights(ambulance_id)

                        # retrieving all vehicle's position and send the packet of emergency vehicle
            for veh_id in traci.vehicle.getIDList():
                position = traci.vehicle.getPosition(veh_id)
                # print(f"{veh_id} 위치 : {position}")

                if veh_id != ambulance_id:
                    distance = calculate_distance(emergency_position, position)
                    print(distance)

                    if distance < notify_distance: # In a valid distance
                        lane_count = traci.vehicle.getLaneIndex(veh_id)
                        print(lane_count)
                        if lane_count == 1:
                            send_evasion_request(ambulance_id, veh_id, "right_edge")
                            traci.vehicle.changeLane(veh_id, 0, 25.0)  # 차로 0으로 변경하고 25초 동안 유지
                        elif lane_count == 2:
                            send_evasion_request(ambulance_id, veh_id, "right_lane")
                            traci.vehicle.changeLane(veh_id, 1, 25.0)  # 차로 1로 변경하고 25초 동안 유지
                        elif lane_count == 3:
                            send_evasion_request(ambulance_id, veh_id, "both_sides")
                            traci.vehicle.changeLane(veh_id, 2, 25.0)  # 차로 2로 변경하고 25초 동안 유지

            for tls_id in traffic_lights:
                # Get distance to the traffic light
                distance_to_tls = get_distance_to_tls(ambulance_id, tls_id)

                if distance_to_tls is not None:
                    if distance_to_tls < 200 and tls_id not in passed_tls:
                        # Get the green phase index for the ambulance's lane
                        green_phase_index = get_green_phase_for_ambulance(tls_id, ambulance_lane)
                        if green_phase_index is not None:
                            send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index)
                    elif tls_id in passed_tls:
                        reset_traffic_light(tls_id)
                        passed_tls.remove(tls_id)

            # Update passed traffic lights
            for tls_id in traffic_lights:
                distance_to_tls = get_distance_to_tls(ambulance_id, tls_id)
                if distance_to_tls is not None and distance_to_tls < 0:
                    passed_tls.add(tls_id)

        except traci.TraCIException as e:
            # Handle exceptions (e.g., ambulance has arrived at destination)
            if str(e) == "Vehicle 'emergency1' is not known.":
                print("Ambulance has arrived at destination")
                break
            else:
                print(str(e))
                pass

    traci.close()
    print("Simulation ended")
    


run_simulation()