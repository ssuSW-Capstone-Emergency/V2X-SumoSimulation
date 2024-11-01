import traci
import traci.constants as tc


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
    traci.trafficlight.setProgram(tls_id, "0")  # Replace "0" with default program ID if different