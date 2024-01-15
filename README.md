# Hey Joody?


## 소개

**주제:** 인형 보호소 테마의 1인칭 공포 탈출게임

**배경:** 주인에게서 버려진 인형이 우연히 인형 보호소에 찾아오게 된다. 처음에는 평화로운 분위기로 시작하지만, 밤이 되고 바뀐 분위기와 함께 방에 갇힌다. 보호소 원장 Joody(주디)에게서 벗어나기 위해 탈출해야 한다.

## 프로젝트 정보

- **기간 및 인원:** 23/08 ~ 진행 중, 개발 2인, 디자인 2인 (디자인 전공)
- **수상:**
  - 2023 예술적인 소프트웨어 장려상 & 한국청소년게임문화협의회 특별상 수상
  - 2023 경희대학교 SW페스티벌 인기상 수상
- **사용 Tool:** Unreal Engine 5.1.1, C++, Perforce
- **게임 출시 계획:** 2024년 중 Steam 출시 계획

## 게임 시스템

### 1인칭 시점

플레이어는 걷기와 뛰기 동작이 가능합니다.

### 심박수 시스템

화면 좌측 상단에 표시되는 심박수가 플레이어의 움직임에 따라 변화합니다.

- 걷기: 소폭 증가
- 뛰기: 대폭 증가
- 정지: 감소

캐릭터의 숨참과 헐떡임도 심박수에 따라 화면을 진동시켜 표현됩니다.

적(주디)은 플레이어의 심박수에 따라 추격의 정도가 변화합니다.

### 아이템과 인벤토리

- 인벤토리는 최대 5개의 아이템을 소지할 수 있습니다.
- 1~5 번호키로 아이템을 교환할 수 있습니다.
- 다양한 아이템이 구현되어 있으며, 키, 손전등, 지도 등이 있습니다.

### 클래스 다이어그램

객체지향적 요소인 다형성을 활용하여 아이템이 구현되었습니다.

## 게임 트레일러
