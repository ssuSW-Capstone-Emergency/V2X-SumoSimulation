import traci

def simulation():
    # Directory
    sumo_binary = "C:\\Users\\1228t\\src\\sumo-1.8.0\\PFiles\\Eclipse\\Sumo\\bin\\sumo-gui"
    sumocfg_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.sumocfg"
    route_dir = "C:\\Program Files (x86)\\Eclipse\\Sumo\\Project\\asanH.rou.xml"

    # Run SUMO
    sumo_cmd = [sumo_binary, "-c", sumocfg_dir, "-r", route_dir, "--junction-taz", "--no-warnings", "--random"]
    traci.start(sumo_cmd)

    # Set variables
    time = 0
    reroute_freq = 10
    
    # Running ...
    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()
        time += 1
        if time // reroute_freq == 0:
            for vid in traci.simulation.getDepartedIDList():
                traci.vehicle.rerouteTraveltime(vid)
                print("vid:", vid)

        # Close SUMO
        if time > 300:
            traci.close()
            break
            
    return 0
    
simulation() # call (run)