import traci
from utils import *
from packet import *

notify_v2i_distance = 200  
ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle
passed_tls = set()

def handle_traffic_lights(ambulance_id):
    # Get the ambulance's position and lane
    ambulance_lane = get_ambulance_lane(ambulance_id)

    # Get upcoming traffic lights
    traffic_lights = get_upcoming_traffic_lights(ambulance_id)

    for tls_id in traffic_lights:
        # Get distance to the traffic light
        distance = get_distance_to_tls(ambulance_id, tls_id)

        if distance is not None:
            if distance < notify_v2i_distance and tls_id not in passed_tls:
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
