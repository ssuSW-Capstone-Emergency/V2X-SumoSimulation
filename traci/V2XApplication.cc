#include "veins/modules/application/traci/V2XApplication.h"
#include <cstdlib>
#include "veins/modules/application/traci/TraCIDemo11p.h"

#include "veins/modules/application/traci/TraCIDemo11pMessage_m.h"


Define_Module(V2XApplication);

void V2XApplication::initialize(int stage){
    TraCIDemo11p::initialize(stage);

    if(stage == 0) {
        scheduleAt(simTime() + SimTime(1, SIMTIME_S), new cMessage("RunPythonScript"));
    }
}

void V2XApplication::handleSelfMsg(cMessage* msg) {
    if (std::string(msg->getName()) == "RunPythonScript") {
        runPythonScript();
        delete msg;
    } else {
        TraCIDemo11p::handleSelfMsg(msg);
    }
}

void V2XApplication::runPythonScript() {
    const char* command = "python3 scripts/V2X.py";
    int ret = std::system(command);

    if (ret != 0) {
        EV_ERROR << "Python script execution failed with return code : " << ret << "\n";
    } else {
        EV_INFO << "Python script executed successfully. \n";
    }
}
