import traci
from utils import *
from packet import *

notify_v2i_distance = 80  
ambulance_id = "emergency1"
manipulated_tls = dict() # passed but not reset [tls_id]=time

def get_in_out_lanes_for_tls(ambulance_id, tls_id):
    """
    주어진 신호등 tls_id에 대해 구급차가 해당 신호등을 지날 때 이용하는 in-lane과 out-lane을 찾아 반환한다.
    현재 위치에 관계없이 구급차의 전체 route를 바탕으로, 신호등이 제어하는 link들 중에서
    route 상 연속되는 edge 쌍에 해당하는 in-lane, out-lane을 찾는다.
    """
    route = traci.vehicle.getRoute(ambulance_id)
    controlled_links = traci.trafficlight.getControlledLinks(tls_id)
    
    # route 상 연속된 edge 쌍(in_edge -> out_edge)을 모두 탐색
    for i in range(len(route)-1):
        in_edge = route[i]
        out_edge = route[i+1]
        # 신호등이 제어하는 링크 (in-lane, out-lane) 중 in_edge -> out_edge로 이어지는 것 확인
        for link in controlled_links:
            for lane_tuple in link:
                # lane_tuple: (in-lane, out-lane, via-lane)
                # in-lane이 in_edge를 포함하고, out-lane이 out_edge를 포함하면 매칭
                if in_edge in lane_tuple[0] and out_edge in lane_tuple[1]:
                    return lane_tuple[0], lane_tuple[1]

    # 해당하는 in-lane/out-lane을 찾지 못한 경우
    return None, None


def handle_traffic_lights(ambulance_id):
    traffic_lights = get_upcoming_traffic_lights(ambulance_id)
    if not traffic_lights:
        return

    # 경로 상의 모든 다가오는 신호등에 대해 처리
    for tls_id in traffic_lights:
        distance = get_distance_to_tls(ambulance_id, tls_id)
        if distance is not None:
            # notify_v2i_distance 이내에 있을 경우 해당 신호등을 구급차 경로에 맞춰 녹색 신호로 설정
            # 한 번 신호를 바꾼 경우 manipulated_tls에 추가하고, 5초 이후에 다시 변경 가능
            if 0 <= distance < notify_v2i_distance and ( tls_id not in manipulated_tls.keys() or ( (get_current_time()-manipulated_tls[tls_id])>5 ) ):
                # tls_id에 대한 in-lane, out-lane 식별
                ambulance_in_lane, ambulance_out_lane = get_in_out_lanes_for_tls(ambulance_id, tls_id)
                if ambulance_in_lane is None or ambulance_out_lane is None:
                    # 라우트 매칭 실패 시 건너뜀
                    continue

                green_phase_index = get_green_phase_for_ambulance(tls_id, ambulance_in_lane, ambulance_out_lane)
                if green_phase_index is not None:
                    send_traffic_light_change_request(tls_id, ambulance_id, green_phase_index)
                    manipulated_tls[tls_id]=get_current_time() # 신호 변경 시간 기록


    # 지나간 신호등 업데이트
    # manipulated_tls에 존재한다: 이미 해당 tls에 제어 신호를 전송했다.
    # traffic_lights: 다가오는 신호등 목록
    # 신호를 전송했고, 이미 지나간 것이 확실한 신호등은 기본 tls 프로그램으로 리셋 
    for tls_id in traffic_lights:
        dist = get_distance_to_tls(ambulance_id, tls_id)
        if ( tls_id in manipulated_tls.keys() ) and ( tls_id not in traffic_lights ):
            reset_traffic_light(tls_id)
            manipulated_tls.remove(tls_id)
