import traci
import time

# 트래픽 시뮬레이션 초기화
traci.start(['sumo-gui', '-c', 'tt.sumocfg'])

# 차량 ID
vehicle_id = "emergency1"

# 초록불 전환 시간 설정
green_duration = 30  # 초 단위로 설정 가능

traci.gui.trackVehicle("View #0", vehicle_id)  # "View #0"은 기본 GUI 화면 ID
# GUI 확대 배율 설정
zoom_level = 3000  # 확대 배율 수준 (예: 3000)
traci.gui.setZoom("View #0", zoom_level)

# 시뮬레이션 루프
while traci.simulation.getMinExpectedNumber() > 0:
    time.sleep(0.1)
    traci.simulationStep()
    
    # 차량이 경로 상에 있는지 확인
    if vehicle_id in traci.vehicle.getIDList():
        # 차량의 다음 경로를 가져옴
        route_edges = traci.vehicle.getRoute(vehicle_id)
        
        for edge_id in route_edges:
            # 현재 경로 상에 있는 모든 신호등 가져오기
            traffic_lights = traci.trafficlight.getIDList()
            
            for light_id in traffic_lights:
                controlled_links = traci.trafficlight.getControlledLinks(light_id)
                
                # 신호등의 각 교차로가 해당 차량의 경로에 있는지 확인
                for link in controlled_links:
                    if link[0][0] == edge_id:
                        # 초록불 페이즈를 동적으로 확인
                        program = traci.trafficlight.getCompleteRedYellowGreenDefinition(light_id)[0]
                        green_phase_index = None
                        
                        for phase in range(len(program.phases)):
                            # 현재 페이즈의 신호등 상태 확인
                            state = program.phases[phase].state
                            
                            # 초록불 상태 확인 (g가 초록불을 의미함)
                            if 'g' in state:
                                green_phase_index = phase
                                break

                        # 초록불 페이즈가 발견되면 해당 페이즈로 전환
                        if green_phase_index is not None:
                            traci.trafficlight.setPhase(light_id, green_phase_index)
                            traci.trafficlight.setPhaseDuration(light_id, green_duration)
                            print(f"Traffic light {light_id} set to green phase {green_phase_index} for vehicle {vehicle_id} on edge {edge_id}")

    # 신호등 원상 복귀
    # 필요시 추가 구현 가능

# 시뮬레이션 종료
traci.close()
