# Advanced-Programming-2019-2
2019-2 심화프로그래밍 어사인먼트 업로드 레포입니다.

## 2048

- 문제정의

 ![1](https://user-images.githubusercontent.com/57410044/101593402-2eed9f80-3a33-11eb-98e0-9a1db2f743f2.png)
> https://play2048.co/

>본 과제는 2048 게임을 구현하고 2048 게임을 자동으로 수행하는 AI를 구현하여 점수를 겨루는 것이 목적이다. 위 이미지처럼 4by4 격자에 랜덤하게 생성되는 타일을 병합되며, AI 는 상하좌우의 조작이 가능하다. 공정성과 투명성을 위해 특정 부분의 템플릿 코드는 주어지고 템플릿 코드는 수정금지이다.

- 어싸인 수행에 필요한 것
    - C++ 프로그래밍, OOP 관점에 대한 이해
    - 타인 작성 코드 이해 능력
    - 알고리즘 설계능력

- 채점기준
    - 코드의 정상작동
    - 코드의 논리적 구조와 설계
    - 도입한 알고리즘의 타당성
    - 코드의 가독성 및 유지보수성
    - 2048 수행 점수(상대평가)

- 템플릿 구조
    - GameManager : 게임의 생성과 종료, 전반적인 운영
    - main : 메인, GameManager 호출
    - Board : 게임판의 관리 현재 상태 등
    - Point : 타일의 좌표를 나타내는 클래스
    - Action : 상,하,좌,우로 이동할 때의 enum
    - Player.h : 사용자 상속 -> 구현

- 구현 plot
    - 1st Step : 더 좋은 상황에 대한 정량화(Entropy 정의) 
    > Entropy(x) = 10000 - ((countBlankCell(x)+1))*(pointSum(x)+1) // x 는 board  
    - 2nd Step : 기본 모델 생성, 상-하-좌-우 이동시 예측되는 board의 상태를 통해 entropy 계산하고 비교해 선택하는 함수 구현(그리디 알고리즘) 
    - 3rd step : 통계적 기법으로 특정 방향과 행위에 가중치 두도록 모델 생성(Advanced A,B,A+B)
    - 4th step : 재귀적 기법으로 현재 상황의 tree 구현 후 각 노드의 entropy 판단, 랜덤 배제 global optimal search

- 실행결과 

    ![2](https://user-images.githubusercontent.com/57410044/101596703-ea650280-3a38-11eb-82ce-77db744befdd.PNG)
    ![3](https://user-images.githubusercontent.com/57410044/101596798-184a4700-3a39-11eb-9b4b-92c922d913d4.PNG)
    ![4](https://user-images.githubusercontent.com/57410044/101596833-239d7280-3a39-11eb-94d7-b005489ecaee.PNG)
    ![5](https://user-images.githubusercontent.com/57410044/101596855-2e580780-3a39-11eb-8a88-110448278b1f.PNG)
    ![6](https://user-images.githubusercontent.com/57410044/101596877-3748d900-3a39-11eb-8b17-655bbf247490.PNG)
    ![7](https://user-images.githubusercontent.com/57410044/101596912-416ad780-3a39-11eb-8f4f-3ddb25a29688.PNG)