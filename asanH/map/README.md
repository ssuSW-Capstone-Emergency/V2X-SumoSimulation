**주요 데이터**

asanH.net.xml // 도로&신호등 구축된 도로 네트워크

asanH.rou.xml // 긴급차량(빨간색) 잠실역->아산병원 경로 설정

asanH.poly.xml // 건물 정보

asanH.sumocfg // 네트워크 & 차량 & 건물 데이터 결합 시뮬레이션

=====================

**omnet++ 적용 방법**

1) .ini 파일 내용 수정
  ```
  *.playgroundSizeX = 4921m
  *.playgroundSizeY = 3587m
  *.playgroundSizeZ = 50m
  ```

2) 내용 복붙하기(파일명은 veins 것 수정하면 안 됨)
  - config.xml
  - .launchd.xml
  - .net.xml
  - .poly.xml
  - .rou.xml
  - .sumo.cfg
  - .ned

(+) veins에서 sumo-gui 띄우는 방법
  1) veins/bin 디렉터리로 이동
    ```
    cd src/veins/bin
    ```

  2) python veins_launchd 실행
    ```
    python veins_launchd -vv -c sumo-gui
    ```

=====================

**도로 데이터 파일**

- asanH.osm
- asanH.png // 도로 이미지

=====================

**추가정보**

- versionSafe.py // SUMO 1.11.0과 버전 맞추기 위한 추가 세팅 

