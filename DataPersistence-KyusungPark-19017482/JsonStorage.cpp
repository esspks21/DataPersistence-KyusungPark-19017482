#include "JsonStorage.h"
#include <fstream>
#include <sstream>
#include <iomanip>

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n,");
    size_t end   = s.find_last_not_of(" \t\r\n,");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

static std::string extractString(const std::string& line) {
    size_t colon = line.find(':');
    if (colon == std::string::npos) return "";
    size_t q1 = line.find('"', colon);
    if (q1 == std::string::npos) return "";
    size_t q2 = line.find('"', q1 + 1);
    if (q2 == std::string::npos) return "";
    return line.substr(q1 + 1, q2 - q1 - 1);
}

static double extractNumber(const std::string& line) {
    size_t colon = line.find(':');
    if (colon == std::string::npos) return 0.0;
    std::string val = trim(line.substr(colon + 1));
    try { return std::stod(val); } catch (...) { return 0.0; }
}

std::vector<SampleOrder> loadFromFile(const std::string& filename) {
    std::vector<SampleOrder> orders;
    std::ifstream file(filename);
    if (!file.is_open()) return orders;

    std::string line;
    SampleOrder current;
    int braceDepth = 0;
    bool inObject  = false;

    while (std::getline(file, line)) {
        std::string t = trim(line);

        if (t == "{") {
            braceDepth++;
            if (braceDepth == 2) { inObject = true; current = SampleOrder{}; }
        } else if (t == "}" || t == "},") {
            if (braceDepth == 2 && inObject && !current.id.empty())
                orders.push_back(current);
            if (braceDepth == 2) inObject = false;
            braceDepth--;
        } else if (inObject) {
            if      (t.find("\"id\"")                 != std::string::npos) current.id                  = extractString(t);
            else if (t.find("\"customer_name\"")      != std::string::npos) current.customer_name       = extractString(t);
            else if (t.find("\"order_quantity\"")     != std::string::npos) current.order_quantity      = static_cast<int>(extractNumber(t));
            else if (t.find("\"avg_production_time\"")!= std::string::npos) current.avg_production_time = extractNumber(t);
            else if (t.find("\"yield_rate\"")         != std::string::npos) current.yield_rate          = extractNumber(t);
            else if (t.find("\"current_inventory\"")  != std::string::npos) current.current_inventory   = static_cast<int>(extractNumber(t));
        }
    }
    return orders;
}

bool saveToFile(const std::vector<SampleOrder>& orders, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "{\n  \"samples\": [\n";
    for (size_t i = 0; i < orders.size(); ++i) {
        const auto& o = orders[i];
        file << std::fixed << std::setprecision(2);
        file << "    {\n";
        file << "      \"id\": \""                << o.id                  << "\",\n";
        file << "      \"customer_name\": \""     << o.customer_name       << "\",\n";
        file << "      \"order_quantity\": "      << o.order_quantity      << ",\n";
        file << "      \"avg_production_time\": " << o.avg_production_time << ",\n";
        file << "      \"yield_rate\": "          << o.yield_rate          << ",\n";
        file << "      \"current_inventory\": "   << o.current_inventory   << "\n";
        file << "    }" << (i + 1 < orders.size() ? "," : "") << "\n";
    }
    file << "  ]\n}\n";
    return true;
}
