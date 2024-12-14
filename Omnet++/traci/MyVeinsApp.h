#ifndef MYVEINSAPP_H
#define MYVEINSAPP_H

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include <unordered_set>
#include <vector>
#include <string>
//#include "veins/modules/messages/DemoSafetyMessage_m.h"
//#include "veins/veins.h"
//#include "veins/base/utils/Coord.h"

using namespace omnetpp;

namespace veins {
class MyVeinsApp : public veins::DemoBaseApplLayer {
protected:
    TraCIMobility* mobility;
    TraCICommandInterface* traci;
    TraCICommandInterface::Vehicle* traciVehicle;
    TraCICommandInterface::Trafficlight* traciTrafficLight;

    void setNodeColorToRed();

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
    void handleTrafficLights(const std::string& ambulanceId);
    void setZoomLevel(const std::string& viewId, double zoomLevel);

public:
    virtual void initialize(int stage) override;
    virtual void finish() override;

    void scenario1(const std::string& emergencyVehicleId, double notifyDistance);
    void handleV2I();

private:
    Coord curPostion;
    veins::Coord curSpeed;

    std::unordered_set<std::string> passedTls;
    const double notifyV2IDistance = 200.0;
    std::string ambulanceId = "emergency1";
};

}
#endif /* MYVEINSAPP_H */
