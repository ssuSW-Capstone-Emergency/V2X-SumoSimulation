#ifndef V2XAPPLICATION_H
#define V2XAPPLICATION_H

#include "veins/modules/application/traci/TraCIDemo11p.h"
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

class V2XApplication : public veins::TraCIDemo11p {
protected:
    void initialize(int stage) override;
    void handleSelfMsg(cMessage* msg) override;

public:
    void runPythonScript();
};

#endif
