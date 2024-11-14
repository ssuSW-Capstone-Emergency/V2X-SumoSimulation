import traci
import time

def run():
    # 트래픽 시뮬레이션 초기화
    traci.start(['sumo-gui', '-c', 'tt.sumocfg'])

    ambulanceID = 'emergency1'  # Replace with your ambulance's vehicle ID
    threshold = 100  # Distance threshold in meters
    modifiedTLS = {}  # Dictionary to keep track of modified traffic lights

    # 초록불 전환 시간 설정
    green_duration = 30  # 초 단위로 설정 가능
    traci.gui.trackVehicle("View #0", ambulanceID)  # "View #0"은 기본 GUI 화면 ID

    # GUI 확대 배율 설정
    zoom_level = 3000  # 확대 배율 수준 (예: 3000)
    traci.gui.setZoom("View #0", zoom_level)


    while traci.simulation.getMinExpectedNumber() > 0:
        time.sleep(0.1)
        traci.simulationStep()

        # Get the ambulance's upcoming traffic lights
        nextTLS = traci.vehicle.getNextTLS(ambulanceID)
        nextTLS_dict = {tls[0]: tls for tls in nextTLS}

        # Reset traffic lights that the ambulance has passed
        for tlsID in list(modifiedTLS.keys()):
            if tlsID in nextTLS_dict:
                tls = nextTLS_dict[tlsID]
                currentDistance = tls[2]
                initialDistance = modifiedTLS[tlsID]
                if currentDistance > initialDistance:
                    # Ambulance has passed the traffic light
                    traci.trafficlight.setProgram(tlsID, '0')  # Reset to default program
                    del modifiedTLS[tlsID]
            else:
                # Traffic light is no longer in ambulance's route
                traci.trafficlight.setProgram(tlsID, '0')  # Reset to default program
                del modifiedTLS[tlsID]

        # Modify nearby traffic lights for the ambulance
        for tls in nextTLS:
            tlsID, tlsIndex, distance, state = tls
            if distance < threshold and tlsID not in modifiedTLS:
                laneID = traci.vehicle.getLaneID(ambulanceID)
                controlledLinks = traci.trafficlight.getControlledLinks(tlsID)
                numSignals = len(controlledLinks)
                newState = ['r'] * numSignals

                # Set signals controlling the ambulance's lane to green
                for i, links in enumerate(controlledLinks):
                    for link in links:
                        fromLane, toLane, via = link
                        if fromLane == laneID:
                            newState[i] = 'g'

                traci.trafficlight.setRedYellowGreenState(tlsID, ''.join(newState))
                modifiedTLS[tlsID] = distance  # Store initial distance

    traci.close()

if __name__ == "__main__":
    run()
