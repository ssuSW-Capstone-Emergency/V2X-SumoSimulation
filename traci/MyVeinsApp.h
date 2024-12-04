#ifndef MYVEINSAPP_H
#define MYVEINSAPP_H

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/messages/DemoSafetyMessage_m.h"
#include "veins/veins.h"
#include "veins/base/utils/Coord.h"

using namespace omnetpp;

namespace veins {
class MyVeinsApp : public veins::DemoBaseApplLayer {
public:
    virtual void initialize(int stage) override; // 초기화 단계
    virtual void handleSelfMsg(cMessage* msg) override; // 내부 메시지 처리


protected:
    veins::TraCICommandInterface* traci = nullptr; // TraCI 인터페이스 객체
    veins::TraCICommandInterface::Vehicle* emergencyVehicle; // 차량 객체

    Coord emergencyVehiclePos; // 긴급 차량 위치
    double notifyDistance = 500; // 긴급 차량 알림 거리
    std::set<std::string> notifiedVehicles; // 알림 받은 차량 ID 목록

    void onWSM(BaseFrame1609_4* wsm) override;
    virtual void onBSM(DemoSafetyMessage* bsm) override;
    void notifyNearbyVehicles();
    double calculateDistance(const Coord& pos1, const Coord& pos2); // 거리 계산 함수
};

}
#endif /* MYVEINSAPP_H */
