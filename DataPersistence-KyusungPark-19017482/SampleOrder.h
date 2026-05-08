#pragma once
#include <string>
#include <vector>

struct SampleOrder {
    std::string id;
    std::string customer_name;
    int         order_quantity       = 0;
    double      avg_production_time  = 0.0; // hours
    double      yield_rate           = 0.0; // percentage (0-100)
    int         current_inventory    = 0;
};

void printOrder(const SampleOrder& order);
void printAllOrders(const std::vector<SampleOrder>& orders);
std::vector<SampleOrder>::iterator findById(std::vector<SampleOrder>& orders, const std::string& id);
