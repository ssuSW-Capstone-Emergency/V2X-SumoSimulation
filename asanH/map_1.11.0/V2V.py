import traci
import os

# 현재 스크립트 파일이 위치한 디렉터리의 절대경로를 얻음
script_dir = os.path.abspath(os.path.dirname(__file__))


def simulation():
    # Directory
    sumo_binary = "sumo-gui"
    sumocfg_dir = script_dir+"/tt.sumocfg"
    route_dir = script_dir+"/asanH.rou.xml"

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