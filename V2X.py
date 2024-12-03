import traci
import time

from utils import *
from packet import *
from V2I import handle_traffic_lights

import threading

notify_distance = 100 
ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle

# Directory
sumo_binary = "C:\\Users\\1228t\\src\\sumo-1.8.0\\PFiles\\Eclipse\\Sumo\\bin\\sumo-gui"
sumocfg_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.sumocfg"
route_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.rou.xml"

# Run SUMO
sumoCmd = [sumo_binary, "-c", sumocfg_dir, "-r", route_dir, "--junction-taz", "--no-warnings", "--random"]
    
def scenario_1(emergency_vehicle_id, notify_distance):
    """
    Scenario 1: Surrounding vehicles evade based on their lane count,
    and the emergency vehicle continues its route without lane optimization.
    """
    emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)

    # Handle surrounding vehicles
    for veh_id in traci.vehicle.getIDList():
        if veh_id == emergency_vehicle_id:
            continue

        position = traci.vehicle.getPosition(veh_id)
        distance = calculate_distance(emergency_position, position)

        if distance < notify_distance:  # In a valid distance
            lane_count = traci.vehicle.getLaneIndex(veh_id)
            if lane_count == 1:
                send_evasion_request(emergency_vehicle_id, veh_id, "right_edge")
                traci.vehicle.changeLane(veh_id, 0, 25.0)  # Move to lane 0 for 25 seconds
            elif lane_count == 2:
                send_evasion_request(emergency_vehicle_id, veh_id, "right_lane")
                traci.vehicle.changeLane(veh_id, 1, 25.0)  # Move to lane 1 for 25 seconds
            elif lane_count >= 3:
                send_evasion_request(emergency_vehicle_id, veh_id, "both_sides")
                traci.vehicle.changeLane(veh_id, 2, 25.0)  # Move to lane 2 for 25 seconds

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
    # sumoCmd = ["sumo-gui", "-c", "/cauH/map/cauH.sumocfg"]
    traci.start(sumoCmd)

    traci.gui.trackVehicle("View #0", ambulance_id)  # "View #0" is the default GUI screen ID

    # GUI zoom level
    zoom_level = 3000 
    traci.gui.setZoom("View #0", zoom_level)

    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2) # Simulation speed control
        traci.simulationStep()

        try:
            v2i_thread = threading.Thread(target = handle_v2i)

            if scenario == 1:
                v2v_thread = threading.Thread(target = scenario_1(ambulance_id, notify_distance))
                
            elif scenario == 2:
                v2v_thread = threading.Thread(target = scenario_2(ambulance_id, notify_distance))

            # Start threads
            v2v_thread.start()
            v2i_thread.start()

            # Wait for both threads to complete
            v2v_thread.join()
            v2i_thread.join()
            
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
    

if __name__ == '__main__':
    # Choose scenario (1 or 2)
    selected_scenario = int(input("Enter scenario (1 or 2): "))
    simulation(selected_scenario)