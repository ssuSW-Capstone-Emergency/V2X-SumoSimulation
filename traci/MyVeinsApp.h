#ifndef MYVEINSAPP_H
#define MYVEINSAPP_H

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
//#include "veins/modules/messages/DemoSafetyMessage_m.h"
//#include "veins/veins.h"
//#include "veins/base/utils/Coord.h"

using namespace omnetpp;

namespace veins {
class MyVeinsApp : public veins::DemoBaseApplLayer {
protected:
    TraCICommandInterface* traci;
    TraCICommandInterface::Vehicle* traciVehicle;
    TraCICommandInterface::Trafficlight* traciTrafficLight;

    void sendEvasionRequest(const std::string& emergencyVehicleId, const std::string& targetVehicleId, const std::string& direction); //packet.py : send_evasion_requeset
    void sendTrafficLightChangeRequest(const std::string& tlsId, const std::string& ambulanceId, int greenPhaseIndex); //packet.py : send_traffic_light_change_request

    virtual void handleSelfMsg(cMessage* msg) override;
    virtual void handleLowerMsg(cMessage* msg) override;

    double calculateDistance(const Coord& pos1, const Coord& pos2) const;
    std::pair<Coord, std::string> getAmbulancePosition(const std::string& ambulanceId) const;
    double getAmbulanceSpeed(const std::string& ambulanceId) const;
    std::string getAmbulanceLane(const std::string& ambulanceId) const;
    simtime_t getSimulationTimestamp() const;
    std::vector<std::string> getUpcomingTrafficLights(const std::string& ambulanceId) const;
    double getDistanceToTrafficLight(const std::string& ambulanceId, const std::string& tlsId) const;
    int getGreenPhaseForAmbulance(const std::string& tlsId, const std::string& ambulanceLane) const;
    void setTrafficLightToGreen(const std::string& tlsId, int greenPhaseIndex);
    void resetTrafficLight(const std::string& tlsId);
    std::pair<int, int> findLeastCongestedLane(const std::string& emergencyVehicleId) const;
    void changeEmergencyVehicleLane(const std::string& emergencyVehicleId);

public:
    virtual void initialize(int stage) override;
    virtual void finish() override;
//    veins::TraCICommandInterface* traci = nullptr; // TraCI 인터페이스 객체
//    veins::TraCICommandInterface::Vehicle* emergencyVehicle; // 차량 객체
//
//    Coord emergencyVehiclePos; // 긴급 차량 위치
//    double notifyDistance = 500; // 긴급 차량 알림 거리
//    std::set<std::string> notifiedVehicles; // 알림 받은 차량 ID 목록
//
//    void onWSM(BaseFrame1609_4* wsm) override;
//    virtual void onBSM(DemoSafetyMessage* bsm) override;
//    void notifyNearbyVehicles();
//    double calculateDistance(const Coord& pos1, const Coord& pos2); // 거리 계산 함수


};

}
#endif /* MYVEINSAPP_H */
