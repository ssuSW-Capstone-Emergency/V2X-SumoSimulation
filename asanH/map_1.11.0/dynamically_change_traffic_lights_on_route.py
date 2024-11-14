# emergency_priority.py

import traci
import traci.constants as tc
import time

# Function to get the ambulance's position and current edge
def get_ambulance_position(ambulance_id):
    position = traci.vehicle.getPosition(ambulance_id)
    current_edge = traci.vehicle.getRoadID(ambulance_id)
    return position, current_edge

# Function to get upcoming traffic lights along the ambulance's route
def get_upcoming_traffic_lights(ambulance_id):
    next_tls_list = traci.vehicle.getNextTLS(ambulance_id)
    traffic_lights = []
    for tls_info in next_tls_list:
        tls_id = tls_info[0]
        if tls_id not in traffic_lights:
            traffic_lights.append(tls_id)
    return traffic_lights

# Function to get distance to a specific traffic light
def get_distance_to_tls(ambulance_id, tls_id):
    next_tls_list = traci.vehicle.getNextTLS(ambulance_id)
    for tls_info in next_tls_list:
        if tls_info[0] == tls_id:
            return tls_info[2]  # distance to traffic light
    return None  # If not found

# Function to determine the green phase index for the ambulance's lane at a traffic light
def get_green_phase_for_ambulance(tls_id, ambulance_lane):
    logic = traci.trafficlight.getCompleteRedYellowGreenDefinition(tls_id)[0]
    controlled_links = traci.trafficlight.getControlledLinks(tls_id)

    for phase_index, phase in enumerate(logic.getPhases()):
        for link_index, link in enumerate(controlled_links):
            for lane_tuple in link:
                if ambulance_lane == lane_tuple[0]:
                    if phase.state[link_index] == 'G':
                        return phase_index
    return None

# Function to set a traffic light to the specified green phase
def set_traffic_light_to_green(tls_id, green_phase_index):
    traci.trafficlight.setPhase(tls_id, green_phase_index)

# Function to reset the traffic light to its default program
def reset_traffic_light(tls_id):
    traci.trafficlight.setProgram(tls_id, "0")  # Replace "0" with your default program ID if different

# Main function to run the simulation
def run_simulation():
    # Start the TraCI server with your SUMO configuration file
    sumoCmd = ["sumo-gui", "-c", "tt.sumocfg"]  # Replace with your config file
    traci.start(sumoCmd)

    ambulance_id = "emergency1"  # The ID assigned to your ambulance vehicle
    passed_tls = set()

    traci.gui.trackVehicle("View #0", ambulance_id)  # "View #0"은 기본 GUI 화면 ID

    # GUI 확대 배율 설정
    zoom_level = 3000  # 확대 배율 수준 (예: 3000)
    traci.gui.setZoom("View #0", zoom_level)

    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2)
        traci.simulationStep()

        try:
            # Get the ambulance's position and lane
            position, current_edge = get_ambulance_position(ambulance_id)
            ambulance_lane = traci.vehicle.getLaneID(ambulance_id)

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
                            set_traffic_light_to_green(tls_id, green_phase_index)
                    elif tls_id in passed_tls:
                        reset_traffic_light(tls_id)
                        passed_tls.remove(tls_id)

            # Update passed traffic lights
            for tls_id in traffic_lights:
                distance = get_distance_to_tls(ambulance_id, tls_id)
                if distance is not None and distance < 0:
                    passed_tls.add(tls_id)

        except traci.TraCIException:
            # Handle exceptions (e.g., ambulance has arrived at destination)
            pass

    traci.close()

if __name__ == "__main__":
    run_simulation()
