import traci
import time

from utils import *
from packet import *
from V2I import handle_traffic_lights

notify_distance = 100 
ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle

sumoCmd = ["sumo-gui", "-c", "asanH/map_1.11.0/tt.sumocfg"]  

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
            current_edge = traci.vehicle.getRoadID(veh_id)
            lane_count = traci.edge.getLaneNumber(current_edge)
            current_lane_index = traci.vehicle.getLaneIndex(veh_id)
            if lane_count == 1:
                send_evasion_request(emergency_vehicle_id, veh_id, "right_edge")
                # For single-lane roads, vehicles cannot change lanes
            elif lane_count >= 2:
                send_evasion_request(emergency_vehicle_id, veh_id, "right_lane")
                if current_lane_index != 0:
                    traci.vehicle.changeLane(veh_id, 0, 25.0)  # Move to rightmost lane
            # Additional logic can be added for lane_count >= 3 if needed

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

    # GUI zoom level
    zoom_level = 3000 
    traci.gui.setZoom("View #0", zoom_level)

    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2)  # Simulation speed control
        traci.simulationStep()

        try:
            if scenario == 1:
                scenario_1(ambulance_id, notify_distance)
            elif scenario == 2:
                scenario_2(ambulance_id, notify_distance)
            handle_v2i()
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
