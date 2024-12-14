## 긴급차량 이동시간 최적화를 위한 V2X 기반 피양 시스템
V2X (Vehicle-to-Everything) is a concept that encompasses V2V (Vehicle-to-Vehicle), V2I (Vehicle-to-Infrastructure), and V2P (Vehicle-to-Pedestrian), where vehicles can access various transportation elements and information. Allows for real-time exchange. In this study, we are constructing and simulating a V2V and V2I communication environment through SUMO, TraCI, and Omnet++, and comparing performance.

## Requirement
- python 3.8
- SUMO 1.11.0
- Omnet++ 5.6.2
- Veins 5.2
- Instant Veins(Debian) 5.2-i1(11)
- Visual Studio Code 1.93.1


## Installation to simulate V2X
- clone this repository. Assume this repository is downloaded to `/V2X-SumoSimulation`
- Install dependencies
  - `cd /V2X-SumoSimulation`
  - `pip install -r requirements.txt`

## Usage
- general(no V2V, V2I)
  1) edit general.py
     Uncomment the scenario you want to simulate.
     ```
     11 | # sumoCmd = ["sumo-gui", "-c", "asanH/map/asanH.sumocfg"]
     12 | # sumoCmd = ["sumo-gui", "-c", "cauH/map/cauH.sumocfg"]
     ```
  2) run general.py
     ```
     python general.py
     ```
     
- V2X
  1) edit V2X.py
     Uncomment the scenario you want to simulate.
     ```
     14 | # sumoCmd = ["sumo-gui", "-c", "asanH/map/asanH.sumocfg"]
     15 | # sumoCmd = ["sumo-gui", "-c", "cauH/map/cauH.sumocfg"]
     ```
  2) run V2X.py

     When you run V2X.py, two ways are possible. All are technologies using V2X, and there are differences in specific algorithms and standards for adoption.
     ```
     python V2X.py
     # Enter scenario (1 or 2):
     ```

## 시연
  
- apply V2X
  
  We can see nearby vehicles giving shelter to the emergency vehicle(red) to pass. Additionally, traffic lights within a certain distance from an emergency vehicle will remain green.
  
  ![제목+없는+동영상+-+Clipchamp로+제작 (1)](https://github.com/user-attachments/assets/6519ceea-2a40-45a1-aae1-cba066c72175)
