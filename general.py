import traci
import time

from utils import *
from packet import *
from random import *

notify_distance = 100
ambulance_id = "emergency1"  # The ID assigned to the ambulance vehicle

sumoCmd = ["sumo-gui", "-c", "asanH/map/asanH.sumocfg"]
# sumoCmd = ["sumo-gui", "-c", "cauH/map/cauH.sumocfg"]

def scenario_no_v2v_v2i(emergency_vehicle_id):
    """
    Scenario with no V2V or V2I functionality. The emergency vehicle
    proceeds without influencing surrounding vehicles or traffic lights.
    """
    emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)

    # No V2V or V2I logic applied here; emergency vehicle proceeds normally
    print(f"Emergency vehicle at position: {emergency_position}")
    
# Main function to run the simulation
def simulation_no_v2v_v2i():
    # Start the TraCI server with SUMO configuration file
    traci.start(sumoCmd)

    traci.gui.trackVehicle("View #0", ambulance_id)  # "View #0" is the default GUI screen ID

    # GUI zoom level
    zoom_level = 3000
    traci.gui.setZoom("View #0", zoom_level)

    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.2)  # Simulation speed control
        traci.simulationStep()

        try:
            # Call the no V2V/V2I scenario function
            scenario_no_v2v_v2i(ambulance_id)
        except traci.TraCIException as e:
            # Handle exceptions (e.g., ambulance has arrived at destination)
            if str(e) == f"Vehicle '{ambulance_id}' is not known.":
                print("Ambulance has arrived at destination")
                break
            else:
                print(str(e))
                pass

    traci.close()
    print("Simulation ended")

if __name__ == '__main__':
    print("Running simulation with no V2V or V2I functionality.")
    simulation_no_v2v_v2i()
