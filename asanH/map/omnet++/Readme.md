## GatcomSumo를 활용한 Omnet++ 모델 파일 생성

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
