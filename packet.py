import traci
import utils


# Function to send a traffic light change request
def send_traffic_light_change_request(tls_id, green_phase_index):
    utils.set_traffic_light_to_green(tls_id, green_phase_index)