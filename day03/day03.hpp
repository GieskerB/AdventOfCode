#ifndef ADVENTOFCODE_DAY03_HPP
#define ADVENTOFCODE_DAY03_HPP

#include <vector>
#include <string>
#include <fstream>
#include <regex>

static std::vector<std::string> read_instructions(std::string pattern_str) {
    std::ifstream file_stream{};
    file_stream.open("../day03/puzzle_input.txt");

    std::vector<std::string> instructions{};

    const std::regex pattern{pattern_str};


    for (std::string line; std::getline(file_stream, line);) {

        std::sregex_iterator iter{line.begin(), line.end(),pattern};
        std::sregex_iterator end;

        while(iter != end) {
            instructions.push_back(iter->str());
            ++iter;
        }

    }
    file_stream.close();

    return instructions;
}

void day03part1() {

    auto instr = read_instructions("mul\\([0-9]{1,3},[0-9]{1,3}\\)");

    int sum = 0;

    const std::regex pattern{"[0-9]+"};
    for(auto& inst: instr) {

        std::sregex_iterator iter{inst.begin(), inst.end(),pattern};
        std::sregex_iterator end;

        std::vector<int> numbers;

        while (iter != end) {
            numbers.push_back(std::stoi(iter->str()));

            ++iter;
        }

        sum += numbers[0] * numbers[1];

    }

    std::cout << sum << '\n';

}

void day03part2() {

    auto instr = read_instructions("mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)");

    int sum = 0;

    const std::regex pattern{"[0-9]+"};

    bool enabled = true;

    for(auto& inst: instr) {

        if(inst == "do()") {
            enabled = true;
            continue;
        } else if (inst == "don't()") {
            enabled = false;
            continue;
        }

        std::sregex_iterator iter{inst.begin(), inst.end(),pattern};
        std::sregex_iterator end;

        std::vector<int> numbers;

        while (iter != end) {
            numbers.push_back(std::stoi(iter->str()));

            ++iter;
        }

        if(enabled)
        sum += numbers[0] * numbers[1];

    }

    std::cout << sum << '\n';
}

#endif //ADVENTOFCODE_DAY03_HPP
