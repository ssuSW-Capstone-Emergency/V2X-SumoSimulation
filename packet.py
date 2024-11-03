import traci
import utils


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