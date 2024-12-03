import traci
import time
from utils import *
from packet import *

notify_v2i_distance = 200  
ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle
passed_tls = set()

def handle_traffic_lights(ambulance_id):
    # """
    # Handle V2I communication for traffic lights.
    # This function manages traffic light adjustments based on the ambulance's position.
    # """
    # ambulance_lane = get_ambulance_lane(emergency_vehicle_id)
    # traffic_lights = get_upcoming_traffic_lights(emergency_vehicle_id)
    # passed_tls = set()

    # for tls_id in traffic_lights:
    #     distance_to_tls = get_distance_to_tls(emergency_vehicle_id, tls_id)

    #     if distance_to_tls is not None:
    #         if distance_to_tls < notify_v2i_distance and tls_id not in passed_tls:
    #             green_phase_index = get_green_phase_for_ambulance(tls_id, ambulance_lane)
    #             if green_phase_index is not None:
    #                 print("call")
    #                 send_traffic_light_change_request(tls_id, emergency_vehicle_id, green_phase_index)
                    
    #         elif tls_id in passed_tls:
    #             reset_traffic_light(tls_id)
    #             passed_tls.remove(tls_id)

    # for tls_id in traffic_lights:
    #     distance_to_tls = get_distance_to_tls(emergency_vehicle_id, tls_id)
    #     if distance_to_tls is not None and distance_to_tls < 0:
    #         passed_tls.add(tls_id)
# Get the ambulance's position and lane
    ambulance_lane = get_ambulance_lane(ambulance_id)

    # Get upcoming traffic lights
    traffic_lights = get_upcoming_traffic_lights(ambulance_id)

    for tls_id in traffic_lights:
        # Get distance to the traffic light
        distance = get_distance_to_tls(ambulance_id, tls_id)

        if distance is not None:
            if distance < 200 and tls_id not in passed_tls:
                # Get the green phase index for the ambulance's lane
                green_phase_index = get_green_phase_for_ambulance(tls_id, ambulance_lane)
                if green_phase_index is not None:
                    send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index)
            elif tls_id in passed_tls:
                reset_traffic_light(tls_id)
                passed_tls.remove(tls_id)

    # Update passed traffic lights
    for tls_id in traffic_lights:
        distance = get_distance_to_tls(ambulance_id, tls_id)
        if distance is not None and distance < 0:
            passed_tls.add(tls_id)

# # Main function to run the simulation
# def run_simulation():
#     # Start the TraCI server with SUMO configuration file
#     # sumoCmd = ["sumo-gui", "-c", "asanH/map_1.11.0/tt.sumocfg"]
#     # Directory
#     sumo_binary = "C:\\Users\\1228t\\src\\sumo-1.8.0\\PFiles\\Eclipse\\Sumo\\bin\\sumo-gui"
#     sumocfg_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.sumocfg"
#     route_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.rou.xml"

#     # Run SUMO
#     sumo_cmd = [sumo_binary, "-c", sumocfg_dir, "-r", route_dir, "--junction-taz", "--no-warnings", "--random"]
        
#     traci.start(sumo_cmd)

#     ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle
#     passed_tls = set()

#     traci.gui.trackVehicle("View #0", ambulance_id)  # "View #0"은 기본 GUI 화면 ID

#     # GUI 확대 배율 설정
#     zoom_level = 3000  # 확대 배율 수준 (예: 3000)
#     traci.gui.setZoom("View #0", zoom_level)

#     while traci.simulation.getMinExpectedNumber() > 0:
#         time.sleep(0.2) # 시뮬레이션 속도 조절
#         traci.simulationStep()

#         try:
#             ambulance_lane = get_ambulance_lane(ambulance_id)

#             # Get upcoming traffic lights
#             traffic_lights = get_upcoming_traffic_lights(ambulance_id)

#             for tls_id in traffic_lights:
#                 # Get distance to the traffic light
#                 distance = get_distance_to_tls(ambulance_id, tls_id)

#                 if distance is not None:
#                     if distance < 200 and tls_id not in passed_tls:
#                         # Get the green phase index for the ambulance's lane
#                         green_phase_index = get_green_phase_for_ambulance(tls_id, ambulance_lane)
#                         if green_phase_index is not None:
#                             send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index)
#                     elif tls_id in passed_tls:
#                         reset_traffic_light(tls_id)
#                         passed_tls.remove(tls_id)

#             # Update passed traffic lights
#             for tls_id in traffic_lights:
#                 distance = get_distance_to_tls(ambulance_id, tls_id)
#                 if distance is not None and distance < 0:
#                     passed_tls.add(tls_id)

#         except traci.TraCIException as e:
#             # Handle exceptions (e.g., ambulance has arrived at destination)
#             if str(e) == "Vehicle 'emergency1' is not known.":
#                 print("Ambulance has arrived at destination")
#                 break
#             else:
#                 print(str(e))
#                 pass

#     traci.close()
#     print("Simulation ended")

# if __name__ == "__main__":
#     run_simulation()
