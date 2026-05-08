#include "SampleOrder.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void printOrder(const SampleOrder& o) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "----------------------------------------\n";
    std::cout << "  시료 ID       : " << o.id << "\n";
    std::cout << "  고객명         : " << o.customer_name << "\n";
    std::cout << "  주문 수량      : " << o.order_quantity << " 개\n";
    std::cout << "  평균 생산시간  : " << o.avg_production_time << " 시간\n";
    std::cout << "  수율           : " << o.yield_rate << " %\n";
    std::cout << "  현재 재고      : " << o.current_inventory << " 개\n";
    std::cout << "----------------------------------------\n";
}

void printAllOrders(const std::vector<SampleOrder>& orders) {
    if (orders.empty()) {
        std::cout << "등록된 주문이 없습니다.\n";
        return;
    }
    std::cout << "\n총 " << orders.size() << "건의 주문\n";
    for (const auto& o : orders)
        printOrder(o);
}

std::vector<SampleOrder>::iterator findById(std::vector<SampleOrder>& orders, const std::string& id) {
    return std::find_if(orders.begin(), orders.end(),
        [&id](const SampleOrder& o) { return o.id == id; });
}
