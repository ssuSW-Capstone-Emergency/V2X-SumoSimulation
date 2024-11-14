**주요 데이터**

asanH.net.xml // 도로&신호등 구축된 도로 네트워크(service 도로 진입 못하던 문제 해결) + 도로 약간 더 확장

asanH.rou.xml // 긴급차량(빨간색) 잠실역->아산병원 경로 설정

asanH.poly.xml // 건물 정보

asanH.sumocfg // 네트워크 & 차량 & 건물 데이터 결합 시뮬레이션

====================

**주요 사항**

asanH_1_11_0.net.xml 파일명 수정 // -> asanH.net.xml

asanH.sumocfg 내용 수정 // asanH_1_11_0.net.xml -> asanH.net.xml

불필요한 파일 삭제

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

asanH.osm // (poly 정보 추가)+(도로 약간 더 확장) -> asanH.net.xml 생성

asanH.png // 도로 이미지

=====================

**교통정보**

emergency 차량 : 어느 정도의 교통 flow 진행 후 (100초 후) 출발 시작

flow : emergency와 유사 경로 / emergency 경로와 겹치는 또는 반대 차선 위주로 흐름 설정

=====================

**추가정보**

versionSafe.py // SUMO 1.11.0과 버전 맞추기 위한 추가 세팅 

  (현재 내 노트북 : SUMO 1.20.0)

======================

(+) 추가로, 차량 데이터 변경이 필요시, .rou.xml만 건드려도 됩니다.(.sumocfg 건드릴 필요 x)

