#pragma once
#include <vector>
#include <string>
#include "SampleOrder.h"

std::vector<SampleOrder> loadFromFile(const std::string& filename);
bool saveToFile(const std::vector<SampleOrder>& orders, const std::string& filename);
