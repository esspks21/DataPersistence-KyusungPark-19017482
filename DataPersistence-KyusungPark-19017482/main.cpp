#include <iostream>
#include <string>
#include <limits>
#include "SampleOrder.h"
#include "JsonStorage.h"

const std::string DATA_FILE = "sample_orders.json";

static void printMenu() {
    std::cout << "\n======================================\n";
    std::cout << "  반도체 시료 생산주문 관리 시스템\n";
    std::cout << "======================================\n";
    std::cout << " 1. 전체 주문 조회  (Read All)\n";
    std::cout << " 2. ID로 주문 조회  (Read by ID)\n";
    std::cout << " 3. 주문 등록       (Create)\n";
    std::cout << " 4. 주문 수정       (Update)\n";
    std::cout << " 5. 주문 삭제       (Delete)\n";
    std::cout << " 0. 종료\n";
    std::cout << "--------------------------------------\n";
    std::cout << " 선택: ";
}

static SampleOrder inputOrder() {
    SampleOrder o;
    std::cout << "  시료 ID          : "; std::cin >> o.id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "  고객명           : "; std::getline(std::cin, o.customer_name);
    std::cout << "  주문 수량 (개)   : "; std::cin >> o.order_quantity;
    std::cout << "  평균 생산시간(h) : "; std::cin >> o.avg_production_time;
    std::cout << "  수율 (%)         : "; std::cin >> o.yield_rate;
    std::cout << "  현재 재고 (개)   : "; std::cin >> o.current_inventory;
    return o;
}

int main() {
    auto orders = loadFromFile(DATA_FILE);
    int choice;

    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            printAllOrders(orders);
            break;

        case 2: {
            std::cout << "  조회할 시료 ID: ";
            std::string id; std::cin >> id;
            auto it = findById(orders, id);
            if (it != orders.end()) printOrder(*it);
            else std::cout << "  [오류] 해당 ID가 없습니다.\n";
            break;
        }

        case 3: {
            std::cout << "\n[주문 등록]\n";
            SampleOrder o = inputOrder();
            if (findById(orders, o.id) != orders.end()) {
                std::cout << "  [오류] 이미 존재하는 ID입니다.\n";
                break;
            }
            orders.push_back(o);
            if (saveToFile(orders, DATA_FILE)) std::cout << "  주문이 등록되었습니다.\n";
            else std::cout << "  [오류] 파일 저장에 실패했습니다.\n";
            break;
        }

        case 4: {
            std::cout << "  수정할 시료 ID: ";
            std::string id; std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto it = findById(orders, id);
            if (it == orders.end()) { std::cout << "  [오류] 해당 ID가 없습니다.\n"; break; }
            std::cout << "\n[새 정보 입력]\n";
            SampleOrder updated = inputOrder();
            updated.id = id;
            *it = updated;
            if (saveToFile(orders, DATA_FILE)) std::cout << "  수정이 완료되었습니다.\n";
            else std::cout << "  [오류] 파일 저장에 실패했습니다.\n";
            break;
        }

        case 5: {
            std::cout << "  삭제할 시료 ID: ";
            std::string id; std::cin >> id;
            auto it = findById(orders, id);
            if (it == orders.end()) { std::cout << "  [오류] 해당 ID가 없습니다.\n"; break; }
            orders.erase(it);
            if (saveToFile(orders, DATA_FILE)) std::cout << "  삭제가 완료되었습니다.\n";
            else std::cout << "  [오류] 파일 저장에 실패했습니다.\n";
            break;
        }

        case 0:
            std::cout << "  프로그램을 종료합니다.\n";
            return 0;

        default:
            std::cout << "  [오류] 올바른 번호를 입력하세요.\n";
        }
    }
}
