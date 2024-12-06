#include "veins/modules/application/traci/MyVeinsApp.h"
#include "veins/modules/messages/DemoSafetyMessage_m.h"
#include "veins/base/utils/Coord.h"
#include "veins/modules/mobility/traci/TraCIMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIConstants.h"
#include <cmath>

using namespace veins;

Define_Module(veins::MyVeinsApp);

void MyVeinsApp::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);

    if (stage == 0) {
        if(FindModule<TraCIMobility*>::findSubModule(getParentModule())){
            mobility = TraCIMobilityAccess().get(getParentModule());
            traci = mobility->getCommandInterface();
            traciVehicle = mobility->getVehicleCommandInterface();

            std::list<std::string> trafficLightIds = traci->getTrafficlightIds();
            traciTrafficLight = traci->getTrafficlightCommandInterface(trafficLightIds.front());
        } else {
            traci = nullptr;
            mobility = nullptr;
            traciVehicle = nullptr;
            traciTrafficLight = nullptr;
        }

        currentOfferedServiceId = -1;
        curPosition = mobility->getPositionAt(simTime());
        curSpeed = mobility->getCurrentSpeed();
    }
}

void MyVeinsApp::finish(){
    DemoBaseApplLayer::finish();
}

void MyVeinsApp::handleSelfMsg(cMessage* msg) {
    DemoBaseApplLayer::handleSelfMsg(msg);
}

double MyVeinsApp::calculateDistance(const Coord& pos1, const Coord& pos2) const{
    return std::sqrt(pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
}

std::pair<Coord, std::string> MyVeinsApp::getAmbulancePosition(const std::string& ambulanceId) const{
    Coord position = traciVehicle->getPosition();
    std::string currentEdge = traciVehicle->getRoadId();
    return {position, currentEdge};
}

double MyVeinsApp::getAmbulanceSpeed(const std::string& ambulanceId) const {
    return traciVehicle->getSpeed();
}

std::string MyVeinsApp::getAmbulanceLane(const std::string& ambulanceId) const {
    return traciVehicle->getLaneId();
}

simtime_t MyVeinsApp::getSimulationTimestamp() const{
    return simTime();
}

std::vector<std::string> MyVeinsApp::getUpcomingTrafficLights(const std::string& ambulanceId) const{
    auto nextTlsList = traciVehicle->getNextTls();
    std::vector<std::string> trafficLights;
    for (const auto& tlsInfo : nextTlsList) {
        trafficLights.push_back(std::get<0>(tlsInfo));
    }
    return trafficLights;
}

double MyVeinsApp::getDistanceToTrafficLight(const std::string& ambulanceId, const std::string& tlsId) const{
    auto nextTlsList = traciVehicle->getNextTls();
    for (const auto& tlsInfo : nextTlsList) {
        if (std::get<0>(tlsInfo) == tlsId){
            return std::get<2>(tlsInfo);
        }
    }
    return -1;
}

int MyVeinsApp::getGreenPhaseForAmbulance(const std::string& tlsId, const std::string& ambulanceLane) const{
    auto logic = traciTrafficLight->getCompleteRedYellowGreenDefinition()[0];
    auto controlledLinks = traciTrafficLight->getControlledLinks();

    size_t phaseIndex = 0;
    for (const auto& phase : logic.phases) {
        size_t signalIndex = 0;
        for (const auto& signalLinks : controlledLinks) {
            for (const auto& link : signalLinks){
                if (ambulanceLane == link.outgoing) {
                    if (phase.state[signalIndex] == 'G') {
                        return static_cast<int>(phaseIndex);
                    }
                }
            }
            ++signalIndex;
        }
        ++phaseIndex;
    }
    return -1;
}

void MyVeinsApp::setTrafficLightToGreen(const std::string& tlsId, int greenPhaseIndex){
    traciTrafficLight->setPhase(greenPhaseIndex);
}
void MyVeinsApp::resetTrafficLight(const std::string& tlsId){
    traciTrafficLight->setProgram("0");
}

std::pair<int, int> MyVeinsApp::findLeastCongestedLane(const std::string& emergencyVehicleId) const{
    std::string currentEdge = traciVehicle->getRoadId();

    int numLanes = traci->getNumLanes(currentEdge);

    int minLaneIndex = -1;
    int minVehicleCount = std::numeric_limits<int>::max();

    for (int laneIndex = 0; laneIndex < numLanes; ++laneIndex) {
        std::string laneId = currentEdge + "_" + std::to_string(laneIndex);

        //buf = traci->getConnection()->query(CMD_GET_EDGE_VARIABLE, TraCIBuffer() << LAST_STEP_VEHICLE_NUMBER << laneId);
        int vehicleCount = traci->getVehicleCountOnLane(laneId);
        //buf >> vehicleCount;

        if (vehicleCount < minVehicleCount) {
            minVehicleCount = vehicleCount;
            minLaneIndex = laneIndex;
        }
    }
    return {minLaneIndex, minVehicleCount};
}

void MyVeinsApp::changeEmergencyVehicleLane(const std::string& emergencyVehicleId){
    auto [minLaneIndex, minVehicleCount] = findLeastCongestedLane(emergencyVehicleId);

    if (minLaneIndex != -1){
        std::string currentRoadId = traciVehicle->getRoadId();
        std::string targetLaneId = currentRoadId + "_" + std::to_string(minLaneIndex);

        traciVehicle->changeRoute(targetLaneId, 25.0);
        EV_INFO << "Emergency vehicle changing to lane " << minLaneIndex
                << " with " << minVehicleCount << " vehicles." << std::endl;
    }
}
//
//void MyVeinsApp::onWSM(BaseFrame1609_4* wsm) {
//    EV << "Received WSM: " << wsm->getName() << endl;
//}
//
//void MyVeinsApp::onBSM(DemoSafetyMessage* bsm) {
//    if (bsm->getSenderAddress() == 1) {
//        emergencyVehiclePos = bsm -> getSenderPos();
//        EV << "Received emergency vehicle position : " << emergencyVehiclePos << endl;
//
//        notifyNearbyVehicles();
//    }
//}
//
//void MyVeinsApp::notifyNearbyVehicles() {
//    auto* commandInterface = mobility->getCommandInterface();
//    if(!commandInterface) return;
//
//    auto vehicleList = commandInterface->getVehicleTypeIds();
//    for (const auto& vehId : vehicleList) {
//        if (vehId == "emergency") continue;
//
//        auto veh = commandInterface->vehicle(vehId);
//        Coord vehPos = commandInterface->getVehiclePosition(vehId);
//        double distance = calculateDistance(emergencyVehiclePos, vehPos);
//
//        if (distance < notifyDistance && notifiedVehicles.find(vehId) == notifiedVehicles.end()) {
//            EV << "Notifying vehicle: " << vehId << " at distance " << distance << endl;
//            notifiedVehicles.insert(vehId);
//
//            DemoSafetyMessage* safetyMsg = new DemoSafetyMessage();
//            safetyMsg->setSenderAddress(getId());
//            safetyMsg->setRecipientAddress(LAddress::L2Type(std::stol(vehId)));
//            safetyMsg->setSenderPos(emergencyVehiclePos);
//            sendDown(safetyMsg);
//            commandInterface->genericSetDouble(
//                                TraCIConstants::CMD_SET_VEHICLE_VARIABLE,
//                                vehId,
//                                TraCIConstants::CMD_CHANGELANE,
//                                0);
//        }
//    }
//}


void MyVeinsApp::sendEvasionRequest(const std::string& emergencyVehicleId, const std::string& targetVehicleId, const std::string& direction) {

    auto emergencyVehicle = traci->vehicle(emergencyVehicleId);
    Coord emergencyPosition = emergencyVehicle.getPosition();
    double emergencySpeed = emergencyVehicle.getSpeed();
    simtime_t timestamp = simTime();

    EV << "Sending evasion request to " << targetVehicleId << ": {"
       << "Vehicle ID: " << emergencyVehicleId
       << ", Latitude: " << emergencyPosition.x
       << ", Longitude: " << emergencyPosition.y
       << ", Speed: " << emergencySpeed
       << ", Direction: " << direction
       << ", Timestamp: " << timestamp
       << " }" << endl;

    auto targetVehicle = traci->vehicle(targetVehicleId);
    targetVehicle.setColor(TraCIColor(0, 255, 0, 255));

    if (direction == "right_edge"){
        EV << targetVehicleId << ": one-way single lane : Move to the rightmost edge" << endl;
    } else if (direction == "right_lane") {
        EV << targetVehicleId << ": one-way two lanes : Move to the second lane" << endl;
    } else if (direction == "both_sides") {
        EV << targetVehicleId << ": one-way three lanes : Move to the left and right lanes" << endl;
    }
}

void MyVeinsApp::sendTrafficLightChangeRequest(const std::string& tlsId, const std::string& ambulanceId, int greenPhaseIndex){
    auto ambulance = traci->vehicle(ambulanceId);
    auto trafficLight = traci->trafficlight(tlsId);

    Coord position = ambulance.getPosition();
    std::string currentEdge = ambulance.getRoadId();
    std::string lane = ambulance.getLaneId();
    double emergencySpeed = ambulance.getSpeed();
    simtime_t timestamp = simTime();

    EV << "Sending traffic light change request to: " << tlsId << ": {"
       << "vehicleId: " << ambulanceId
       << ", Latitude: " << position.x
       << ", Longitude: " << position.y
       << ", Edge: " << currentEdge
       << ", Lane: " << lane
       << ", Speed: " << emergencySpeed
       << ", Timestamp: " << timestamp
       << " }" << endl;

    trafficLight.setProgram(tlsId);
    trafficLight.setPhaseIndex(greenPhaseIndex);

}

void MyVeinsApp::handleLowerMsg(cMessage* msg) {
    BaseFrame1609_4* wsm = dynamic_cast<BaseFrame1609_4*>(msg);
    ASSERT(wsm);

    if(DemoSafetyMessage* bsm = dynamic_cast<DemoSafetyMessage*>(wsm)){
        std::string emergencyVehicleId = bsm->getSenderId();
        std::string direction = "right_edge";
        std::string targetVehicleId = "target_vehicle";

        sendEvasionRequest(emergencyVehicleId, targetVehicleId, direction);
    } else if (DemoServiceAdvertisment* wsa = dynamic_cast<DemoServiceAdvertisment*>(wsm)){
        EV_INFO << "Received WSA : " << wsa->getServiceDescription() << endl;
    } else {
        EV_WARN << "Unhandled message type" << endl;
    }

    delete msg;
}
