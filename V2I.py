import traci
import traci.constants as tc
import time

from utils import *
from packet import *


# Main function to run the simulation
def run_simulation():
    # Start the TraCI server with SUMO configuration file
    sumoCmd = ["sumo-gui", "-c", "asanH/map_1.11.0/tt.sumocfg"]
    traci.start(sumoCmd)

    ambulance_id = "emergency1"  # The ID assigned to ambulance vehicle
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
                            send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index)
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
