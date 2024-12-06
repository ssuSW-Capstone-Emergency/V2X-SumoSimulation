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
def get_green_phase_for_ambulance(tls_id, ambulance_in_lane, ambulance_out_lane):
    logic = traci.trafficlight.getCompleteRedYellowGreenDefinition(tls_id)[0]
    controlled_links = traci.trafficlight.getControlledLinks(tls_id)

    for phase_index, phase in enumerate(logic.getPhases()):
        for link_index, link in enumerate(controlled_links):
            for lane_tuple in link:
                # in-lane, out-lane 모두 일치하는 흐름에 대해 녹색 신호 체크
                if lane_tuple[0] == ambulance_in_lane and lane_tuple[1] == ambulance_out_lane:
                    if phase.state[link_index] == 'G':
                        return phase_index
    return None

# Function to set a traffic light to the specified green phase
def set_traffic_light_to_green(tls_id, green_phase_index):
    # print("green!")
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


def get_ambulance_out_lane(ambulance_id, tls_id, ambulance_in_lane):
    """
    앰뷸런스가 현재 in-lane에서 다음 경로로 이동할 때, 해당 신호등이 제어하는
    (in-lane, out-lane) 흐름 중 앰뷸런스의 다음 edge로 이어지는 out-lane을 반환한다.
    """
    route = traci.vehicle.getRoute(ambulance_id)
    route_index = traci.vehicle.getRouteIndex(ambulance_id)
    #print("route", route)
    print("route_index", route_index)

    # 다음 edge가 있는지 확인
    if route_index < len(route) - 1:
        next_edge = route[route_index + 1]
    else:
        return None
    
    controlled_links = traci.trafficlight.getControlledLinks(tls_id)
    for link in controlled_links:
        for lane_tuple in link:
            # lane_tuple: (in-lane, out-lane, via-lane)
            # out-lane 이름에 next_edge가 포함되어 있으면 해당 out-lane은 다음 edge로 이어지는 차선일 가능성이 큼
            if lane_tuple[0] == ambulance_in_lane and next_edge in lane_tuple[1]:
                return lane_tuple[1]

    return None
