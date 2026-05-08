# DataPersistence-KyusungPark-19017482

## 프로젝트 개요

반도체 시료 생산주문 데이터를 JSON 파일로 저장하고 CRUD 기능을 제공하는 C++ 콘솔 애플리케이션 PoC.

## 아키텍처

```
main.cpp          ─ 진입점, 메뉴 루프, 사용자 입력 처리
SampleOrder.h/cpp ─ 데이터 구조 정의 및 출력·검색 유틸리티
JsonStorage.h/cpp ─ JSON 파일 직렬화/역직렬화
sample_orders.json─ 런타임 생성되는 영속성 데이터 파일
```

## 데이터 구조 (SampleOrder)

| 필드 | 타입 | 설명 |
|------|------|------|
| `id` | string | 시료 고유 ID |
| `customer_name` | string | 고객명 |
| `order_quantity` | int | 주문 수량 (개) |
| `avg_production_time` | double | 평균 생산시간 (시간) |
| `yield_rate` | double | 수율 (%, 0~100) |
| `current_inventory` | int | 현재 재고 (개) |

## JSON 포맷

```json
{
  "samples": [
    {
      "id": "SMPL001",
      "customer_name": "Samsung Electronics",
      "order_quantity": 500,
      "avg_production_time": 3.50,
      "yield_rate": 97.20,
      "current_inventory": 120
    }
  ]
}
```

## CRUD 동작

- **Create**: 중복 ID 체크 후 신규 레코드를 추가하고 JSON 저장
- **Read**: 전체 목록 출력 또는 ID로 단건 조회
- **Update**: ID로 레코드를 찾아 전체 필드를 새 입력값으로 교체 후 저장
- **Delete**: ID로 레코드를 삭제 후 저장

## 빌드 환경

- Visual Studio 2022 / MSVC v145
- C++20 (`stdcpp20`)
- 외부 의존성 없음 (표준 라이브러리만 사용)
- 플랫폼: Win32 / x64

## 주요 설계 결정

- 외부 JSON 라이브러리 없이 직접 파서 구현 (PoC 최소 의존성 원칙)
- 파일 저장은 모든 쓰기 연산 즉시 반영 (인메모리 벡터 → 파일 전체 재기록)
- `findById`는 `std::find_if`로 선형 탐색 (소규모 PoC에 적합)
