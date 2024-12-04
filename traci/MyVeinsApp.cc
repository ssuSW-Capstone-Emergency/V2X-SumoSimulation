#include "veins/modules/application/traci/MyVeinsApp.h"
#include "veins/modules/messages/DemoSafetyMessage_m.h"
#include "veins/base/utils/Coord.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

using namespace veins;

Define_Module(veins::MyVeinsApp);

void MyVeinsApp::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        auto* mobility = TraCIMobilityAccess().get(getParentModule());
        ASSERT(mobility);
    }
}

void MyVeinsApp::handleSelfMsg(cMessage* msg) {
    if (msg->getKind() == SEND_BEACON_EVT){
        notifyNearbyVehicles();
    }
    DemoBaseApplLayer::handleSelfMsg(msg);
}

void MyVeinsApp::onWSM(BaseFrame1609_4* wsm) {
    auto* bsm = dynamic_cast<DemoSafetyMessage*>(wsm);
    if (bsm) {
        onBSM(bsm);
    }
}

void MyVeinsApp::onBSM(DemoSafetyMessage* bsm) {
    if (bsm->getSenderAddress() == 1) {
        emergencyVehiclePos = bsm -> getSenderPos();
        EV << "Received emergency vehicle position : " << emergencyVehiclePos << endl;

        notifyNearbyVehicles();
    }
}

void MyVeinsApp::notifyNearbyVehicles() {
    auto* commandInterface = mobility->getCommandInterface();
    if(!commandInterface) return;

    auto vehicleList = commandInterface->getVehicleTypeIds();
    for (const auto& vehId : vehicleList) {
        if (vehId == "emergency") continue;

        auto veh = commandInterface->vehicle(vehId);
        Coord vehPos = commandInterface->getVehiclePosition(vehId);
        double distance = calculateDistance(emergencyVehiclePos, vehPos);

        if (distance < notifyDistance && notifiedVehicles.find(vehId) == notifiedVehicles.end()) {
            EV << "Notifying vehicle: " << vehId << " at distance " << distance << endl;
            notifiedVehicles.insert(vehId);

            DemoSafetyMessage* safetyMsg = new DemoSafetyMessage();
            safetyMsg->setSenderAddress(getId());
            safetyMsg->setRecipientAddress(LAddress::L2Type(std::stol(vehId)));
            safetyMsg->setSenderPos(emergencyVehiclePos);
            sendDown(safetyMsg);
            commandInterface->genericSetDouble(
                                TraCIConstants::CMD_SET_VEHICLE_VARIABLE,
                                vehId,
                                TraCIConstants::CMD_CHANGELANE,
                                0);
        }
    }
}

double MyVeinsApp::calculateDistance(const Coord& pos1, const Coord& pos2){
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}
