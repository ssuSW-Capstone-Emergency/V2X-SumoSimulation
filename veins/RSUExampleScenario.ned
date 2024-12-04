// -----------------------------------------------------------------
// File: asanH.ned
//
// NOTES: it could be necessary to do the following:
// 1. To include this folder (or an upper one) in the list of
//    .ned folders from the project properties:
//        OMNeT++ > NED Source Folder.
// 2. To specify a 'package' line if there exist same package.ned
//    file in the working directory (or an upper one).
// -----------------------------------------------------------------

//package asanH.simulations.asanH;

import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;
import org.car2x.veins.nodes.Car;

network RSUExampleScenario extends Scenario
{
    submodules:
        vehicle[10]: Car {
            @display("p=100,100;i=veins/car/regular;is=vs");
            applType = "MyVeinsApp";
        }
            
        rsu[1]: RSU {
            @display("p=200,200;i=veins/sign/yellowdiamond;is=vs");
        }
}
