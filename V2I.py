import traci
from utils import *
from packet import *

notify_v2i_distance = 500  
ambulance_id = "emergency1"
passed_tls = set()

def handle_traffic_lights(ambulance_id):
    # 앰뷸런스 in-lane, out-lane 획득
    ambulance_in_lane = get_ambulance_lane(ambulance_id)
    traffic_lights = get_upcoming_traffic_lights(ambulance_id)
    if not traffic_lights:
        return
    
    # 가장 가까운 신호등에 대해 처리 (원한다면 모든 신호등에 대해 반복 가능)
    tls_id = traffic_lights[0]
    ambulance_out_lane = get_ambulance_out_lane(ambulance_id, tls_id, ambulance_in_lane)

    # 신호등까지 거리
    distance = get_distance_to_tls(ambulance_id, tls_id)
    if distance is not None:
        if distance < notify_v2i_distance and tls_id not in passed_tls and ambulance_out_lane is not None:
            green_phase_index = get_green_phase_for_ambulance(tls_id, ambulance_in_lane, ambulance_out_lane)
            if green_phase_index is not None:
                send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index)
        elif tls_id in passed_tls:
            reset_traffic_light(tls_id)
            passed_tls.remove(tls_id)

    # 지나간 신호등 업데이트
    for t_id in traffic_lights:
        dist = get_distance_to_tls(ambulance_id, t_id)
        if dist is not None and dist < 0:
            passed_tls.add(t_id)
