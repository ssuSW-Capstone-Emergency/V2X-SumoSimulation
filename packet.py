import traci
import packet


# Function to set a traffic light to the specified green phase
def set_traffic_light_to_green(tls_id, green_phase_index):
    traci.trafficlight.setPhase(tls_id, green_phase_index)