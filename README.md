# 반도체 시료 생산주문 관리 시스템

반도체 시료의 생산주문 정보를 JSON 파일로 저장하고 관리하는 C++ 콘솔 애플리케이션입니다.

## 기능

| 번호 | 기능 | 설명 |
|------|------|------|
| 1 | 전체 주문 조회 | 등록된 모든 주문 목록 출력 |
| 2 | ID로 주문 조회 | 시료 ID를 입력하여 단건 조회 |
| 3 | 주문 등록 | 새 시료 주문 정보 입력 및 저장 |
| 4 | 주문 수정 | 기존 주문 정보 변경 |
| 5 | 주문 삭제 | ID 기준으로 주문 삭제 |

## 저장 항목

- **시료 ID** – 시료 고유 식별자
- **고객명** – 주문 고객사명
- **주문 수량** – 요청 생산 수량 (개)
- **평균 생산시간** – 단위당 평균 생산 소요 시간 (시간)
- **수율** – 양품 비율 (%)
- **현재 재고** – 현재 보유 재고 수량 (개)

## 빌드 방법

1. Visual Studio 2022에서 `DataPersistence-KyusungPark-19017482.slnx` 열기
2. 빌드 구성 선택 (Debug / Release, x64 / Win32)
3. **Ctrl+Shift+B** 로 빌드

## 실행

빌드 후 생성된 `.exe`를 실행하면 메뉴가 표시됩니다.  
데이터는 실행 파일과 같은 디렉토리에 `sample_orders.json` 파일로 자동 저장됩니다.

## 데이터 파일 예시 (`sample_orders.json`)

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
