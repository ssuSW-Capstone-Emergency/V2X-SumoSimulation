import traci
import sumolib
import time

# 트래픽 시뮬레이션 초기화
sumoBinary = sumolib.checkBinary('sumo-gui') 
traci.start([sumoBinary, "-c", "tt.sumocfg"]) 

# 구급차의 차량 타입 ID (SUMO 설정 파일에서 정의된 vehicle type ID 사용)
AMBULANCE_TYPE = "ambulance" 

def change_traffic_light_to_blue(tl_id):
    # 트래픽 라이트를 파란색으로 바꾸는 함수
    traci.trafficlight.setProgram(tl_id, 0)  # 특정 시그널 프로그램을 설정하거나 
    traci.trafficlight.setPhase(tl_id, 2)    # 신호를 파란색으로 바꾸는 새로운 phase를 추가합니다.

try:
    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()  # 시뮬레이션을 한 단계 진행합니다.
        time.sleep(0.1)  # 각 시뮬레이션 스텝마다 0.1초 지연을 추가하여 속도를 늦춤

        # 모든 차량을 가져와 구급차가 있는지 확인
        for vehicle_id in traci.vehicle.getIDList():
            if traci.vehicle.getTypeID(vehicle_id) == AMBULANCE_TYPE:
                vehicle_position = traci.vehicle.getPosition(vehicle_id)
                vehicle_edge = traci.vehicle.getRoadID(vehicle_id)

                # 신호등 ID를 가져와 가까운 신호등이 있는지 확인
                for tl_id in traci.trafficlight.getIDList():
                    tl_position = traci.junction.getPosition(tl_id)

                    # 차량과 신호등 사이의 거리 계산
                    distance = ((vehicle_position[0] - tl_position[0]) ** 2 + (vehicle_position[1] - tl_position[1]) ** 2) ** 0.5
                    
                    # 신호등 근처(예: 50m 이내)에 있을 경우 신호등을 파란색으로 변경
                    if distance < 50:
                        change_traffic_light_to_blue(tl_id)

finally:
    traci.close()
