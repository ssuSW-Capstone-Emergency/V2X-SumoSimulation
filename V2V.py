import traci
import math

from utils import calculate_distance
from packet import send_evasion_request

def simulation():
    # Directory
    sumo_binary = "C:\\Users\\1228t\\src\\sumo-1.8.0\\PFiles\\Eclipse\\Sumo\\bin\\sumo"
    sumocfg_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.sumocfg"
    route_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.rou.xml"

    # Run SUMO
    sumo_cmd = [sumo_binary, "-c", sumocfg_dir, "-r", route_dir, "--junction-taz", "--no-warnings", "--random"]
    traci.start(sumo_cmd)

    # Set variables
    time = 0
    reroute_freq = 10
    
    emergency_vehicle_id = "emergency1"  # ID setting
    notify_distance = 500 # valid range (meter?)

    # Running ...
    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()

        emergency_position = traci.vehicle.getPosition(emergency_vehicle_id)

        # retrieving all vehicle's position and send the packet of emergency vehicle
        for veh_id in traci.vehicle.getIDList():
            position = traci.vehicle.getPosition(veh_id)
            print(f"{veh_id} 위치 : {position}")

            if veh_id != emergency_vehicle_id:
                distance = calculate_distance(emergency_position, position)

                if distance < notify_distance: # In a valid distance
                    lane_count = traci.vehicle.getLaneIndex(veh_id)
                    if lane_count == 1:
                        send_evasion_request(emergency_vehicle_id, veh_id, "right_edge")
                    elif lane_count == 2:
                        send_evasion_request(emergency_vehicle_id, veh_id, "right_lane")
                    elif lane_count == 3:
                        send_evasion_request(emergency_vehicle_id, veh_id, "both_sides")


        # recalculate the route every specific period
        time += 1
        if time // reroute_freq == 0:
            for vid in traci.simulation.getDepartedIDList():
                traci.vehicle.rerouteTraveltime(vid)
                print("vid:", vid)

        # Close SUMO
        if time > 100:
            traci.close()
            break
            
    return 0
    

if __name__ == '__main__':
    simulation() # run