#ifndef ADVENTOFCODE_DAY02_HPP
#define ADVENTOFCODE_DAY02_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>

static std::array<std::vector<unsigned int>, 1000> read_reports() {
    std::ifstream file_stream{};
    file_stream.open("../day02/puzzle_input.txt");

    std::array<std::vector<unsigned int>, 1000> reports{{}};

    int index = 0;
    for (std::string line; std::getline(file_stream, line);) {
        std::vector<unsigned int> levels;
        std::stringstream string_stream{line};
        int level;
        while (string_stream) {
            string_stream >> level;
            if (!string_stream) break;
            levels.push_back(level);
        }
        reports[index++] = std::move(levels);
    }
    file_stream.close();

    return reports;
}

static unsigned int diff(unsigned int a, unsigned int b) {
    if (a > b) {
        return a - b;
    } else {
        return b - a;
    }
}

static bool test_for_safe_report(const std::vector<unsigned  int>& report) {
    bool is_safe_report = true;
    unsigned int last_value = report[0];
    bool is_increasing;
    for (int i = 1; i < report.size(); ++i) {
        unsigned int current_value = report[i];
        if (i == 1) {
            if (last_value < report[1]) {
                is_increasing = true;
            } else {
                is_increasing = false;
            }
        }
        if ((is_increasing and last_value > current_value) or (!is_increasing and last_value < current_value)) {
            is_safe_report = false;
            break;
        } else if (diff(last_value, current_value) > 3 or diff(last_value, current_value) < 1) {
            is_safe_report = false;
            break;
        }
        last_value = report[i];
    }
    return is_safe_report;
}

void day02part1() {

    auto reports = read_reports();

    int safe_counter = 0;
    for (auto &report: reports) {
        bool is_safe_report = test_for_safe_report(report);
        if (is_safe_report) {
            ++safe_counter;
        }
    }

    std::cout << safe_counter << '\n';

}

static std::vector<std::vector<unsigned int>> get_all_n_minus_one_combinations(std::vector<unsigned int> input_vector) {
    std::vector<std::vector<unsigned int>> lists;

    for(int i = 0; i< input_vector.size(); ++i) {
        std::vector<unsigned int> new_list;
        for(int j = 0; j< input_vector.size(); ++j) {
            if(i != j) {
                new_list.push_back(input_vector[j]);
            }
        }
        lists.push_back(new_list);
    }
    return lists;
}

void day02part2() {

    std::vector<unsigned int> vecc = {1,2,3,4,5};

    auto test = get_all_n_minus_one_combinations(vecc);

    for(auto& vec: test) {
        for(auto& val: vec) {
            std::cout << val<< ' ';
        }
        std::cout << '\n';
    }

    auto reports = read_reports();

    int safe_counter = 0;
    for (auto &report: reports) {
        bool is_safe_report = test_for_safe_report(report);

        if(!is_safe_report) {
            for(auto& mini_report: get_all_n_minus_one_combinations(report)) {
                is_safe_report = test_for_safe_report(mini_report);
                if(is_safe_report) break;
            }
        }

        if (is_safe_report) {
            ++safe_counter;
        }
    }

    std::cout << safe_counter << '\n';

}

#endif //ADVENTOFCODE_DAY02_HPP
