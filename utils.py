import math
import traci

# between two positions
def calculate_distance(pos1, pos2):
    return math.sqrt((pos1[0] - pos2[0]) ** 2 + (pos1[1] - pos2[1]) ** 2)

# Function to get the ambulance's position and current edge
def get_ambulance_position(ambulance_id):
    position = traci.vehicle.getPosition(ambulance_id)
    current_edge = traci.vehicle.getRoadID(ambulance_id)
    return position, current_edge

def get_ambulance_speed(ambulance_id):
    return traci.vehicle.getSpeed(ambulance_id)

def get_ambulance_lane(ambulance_id):
    return traci.vehicle.getLaneID(ambulance_id)

def get_simulation_timestamp():
    return traci.simulation.getTime()

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
    print("green!")
    traci.trafficlight.setPhase(tls_id, green_phase_index)

# Function to reset the traffic light to its default program
def reset_traffic_light(tls_id):
    traci.trafficlight.setProgram(tls_id, "0")

def find_least_congested_lane(emergency_vehicle_id):
    """
    Finds the lane with the least number of vehicles for the current road of the emergency vehicle.
    """
    current_edge = traci.vehicle.getRoadID(emergency_vehicle_id)
    lanes = traci.edge.getLaneNumber(current_edge)
    
    min_lane_index = None
    min_vehicle_count = float('inf')

    for lane_index in range(lanes):
        lane_id = f"{current_edge}_{lane_index}"
        vehicle_count = traci.lane.getLastStepVehicleNumber(lane_id)
        if vehicle_count < min_vehicle_count:
            min_vehicle_count = vehicle_count
            min_lane_index = lane_index

    return min_lane_index, min_vehicle_count

def change_emergency_vehicle_lane(emergency_vehicle_id):
    """
    Changes the lane of the emergency vehicle to the one with the least congestion.
    """
    min_lane_index, min_vehicle_count = find_least_congested_lane(emergency_vehicle_id)

    if min_lane_index is not None and traci.vehicle.getLaneIndex(emergency_vehicle_id) != min_lane_index:
        traci.vehicle.changeLane(emergency_vehicle_id, min_lane_index, 25.0)
        print(f"Emergency vehicle changing to lane {min_lane_index} with {min_vehicle_count} vehicles.")