#ifndef ADVENTOFCODE_DAY05_HPP
#define ADVENTOFCODE_DAY05_HPP

#include <fstream>
#include <vector>

struct Day5Input {
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> orders;
};

static Day5Input read_input() {

    std::ifstream file_stream{};
    file_stream.open("../day05/puzzle_input.txt");

    bool first_part = true;

    Day5Input input;

    for (std::string line; std::getline(file_stream, line);) {

        if (line.empty()) {
            first_part = false;
            continue;
        }

        if (first_part) {
            char bar = '|';
            std::stringstream string_stream{line};
            std::pair<int, int> rule;
            string_stream >> rule.first >> bar >> rule.second;
            input.rules.push_back(rule);
        } else {
            std::stringstream ss(line);
            std::vector<int> order;
            for (int elem; ss >> elem;) {
                order.push_back(elem);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            input.orders.push_back(order);
        };


    }
    file_stream.close();
    return input;
}

void day05part1() {

    auto input = read_input();

    int total_mid_page_sum = 0;

    for(auto& section:input.orders) {
        bool section_valid = true;
        for(auto& rule: input.rules) {
            auto first_occ = std::find(section.begin(), section.end(),rule.first);
            auto second_occ = std::find(section.begin(), section.end(), rule.second);
            if (first_occ == section.end() or second_occ == section.end()) {
                // both numbers do not exist. Therefore, we don't care.
                continue;
            }
            if(first_occ > second_occ) {
                // Rule does not apply;
                section_valid = false;
                break;
            }
        }
        if(section_valid) {
            total_mid_page_sum += section[section.size() / 2];
        }
    }
    std::cout << total_mid_page_sum<< '\n';
}
void day05part2() {

    auto input = read_input();

}

#endif //ADVENTOFCODE_DAY05_HPP
