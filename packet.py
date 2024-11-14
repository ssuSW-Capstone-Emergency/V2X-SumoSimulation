import traci
import utils

def send_evasion_request(emergency_vehicle_id, target_vehicle_id, direction):
    emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)
    emergency_speed = traci.vehicle.getSpeed(emergency_vehicle_id)
    timestamp = traci.simulation.getTime()

    # packet information
    packet = {
        "vehicle_id" : emergency_vehicle_id,
        "latitude" : emergency_position[0],
        "longitude" : emergency_position[1],
        "speed" : emergency_speed,
        "direction" : direction, # 1,2,3 line case
        "timestamp" : timestamp
    }

    print(f"send packet to {target_vehicle_id} : {packet} ")
    traci.vehicle.setColor(target_vehicle_id, (255,0,0)) # change vehicle color to red when they got the packet 

    if direction == "right_edge":
        print(f"{target_vehicle_id} : 편도 1차로 - 우측 가장자리로 피양하세요.")
    elif direction == "right_lane":
        print(f"{target_vehicle_id} : 편도 2차로 - 2차선으로 피양하세요.")
    elif direction == "both_sides":
        print(f"{target_vehicle_id} : 편도 3차로 - 좌, 우측 차로로 피양 하세요.")


# Function to send a traffic light change request
def send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index):
    position, current_edge = utils.get_ambulance_position(ambulance_id)
    lane = utils.get_ambulance_lane(ambulance_id)
    emergency_speed = utils.get_ambulance_speed(ambulance_id)
    timestamp = utils.get_simulation_timestamp()


    # packet information
    packet = {
        "vehicle_id" : ambulance_id,
        "latitude" : position[0],
        "longitude" : position[1],
        "edge" : current_edge,
        "lane" : lane,
        "speed" : emergency_speed,
        "timestamp" : timestamp
    }    
    
    print(f"send packet to {tls_id}(Traffic Light) : {packet} ")
    utils.set_traffic_light_to_green(tls_id, green_phase_index)