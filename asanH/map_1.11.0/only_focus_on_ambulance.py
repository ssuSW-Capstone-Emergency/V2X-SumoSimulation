import traci
import sumolib
import time
import logging


# 디버깅 설정
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

# 트래픽 시뮬레이션 초기화
sumoBinary = sumolib.checkBinary('sumo-gui') 
traci.start([sumoBinary, "-c", "tt.sumocfg"]) 

# 구급차의 차량 타입 ID (SUMO 설정 파일에서 정의된 vehicle type ID 사용)
AMBULANCE_TYPE = "ambulance" 
AMBULANCE_ID = "emergency1"  # 구급차 ID (시뮬레이션에서 실제 구급차 ID로 설정)

traci.gui.trackVehicle("View #0", AMBULANCE_ID)  # "View #0"은 기본 GUI 화면 ID
# GUI 확대 배율 설정
zoom_level = 3000  # 확대 배율 수준 (예: 3000)
traci.gui.setZoom("View #0", zoom_level)


try:
    # 구급차를 화면에서 따라가도록 설정
    traci.gui.trackVehicle("View #0", AMBULANCE_ID)  # "View #0"은 기본 GUI 화면 ID입니다

    while traci.simulation.getMinExpectedNumber() > 0:
        traci.simulationStep()  # 시뮬레이션을 한 단계 진행
        time.sleep(0.2)  # 각 시뮬레이션 스텝마다 0.1초 지연을 추가하여 속도를 늦춤

finally:
    traci.close()
