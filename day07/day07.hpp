#ifndef ADVENTOFCODE_DAY07_HPP
#define ADVENTOFCODE_DAY07_HPP

#include <vector>
#include <cmath>

typedef unsigned long long ulolo;

std::vector<std::vector<ulolo>> read_day07() {

    std::vector<std::vector<ulolo>> calibrations;
    std::ifstream file_stream{};
    file_stream.open("../day07/puzzle_input.txt");

    for (std::string line; std::getline(file_stream, line);) {

        std::stringstream string_stream{line};
        std::vector<ulolo> calibration;
        ulolo value = 0;
        while (string_stream >> value) {
            calibration.push_back(value);

            if (calibration.size() == 1) {
                char tmp = ':';
                string_stream >> tmp;
            }

        }
        calibrations.push_back(calibration);

    }

    file_stream.close();
    return calibrations;

}

static ulolo concat (ulolo left, ulolo right) {

    int right_digit = floor(log10(right)) +1;

    int pow = 1;

    for(int i = 0 ; i < right_digit; ++i) {
        pow *= 10;
    }

    left *= pow;
    left += right;

    return left;

}

bool reaches_value(const std::vector<ulolo> &vec, ulolo curr_value, int index) {
    if (index >= vec.size()) {
        return curr_value == vec[0];
    } else if (curr_value > vec[0]) {
        return false;
    }

    return reaches_value(vec, curr_value * vec[index], index + 1) or
           reaches_value(vec, curr_value + vec[index], index + 1) or
            reaches_value(vec, concat(curr_value , vec[index]), index + 1);
}

void day07part1() {

    auto calibrations = read_day07();

    ulolo calib_sum = 0;

    for(auto& val: calibrations[0]) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    for(auto& calib: calibrations) {
        if(reaches_value(calib,0,1)) {
            calib_sum += calib[0];
        }
    }

    std::cout << calib_sum << '\n';

}

void day07part2() {

}

#endif //ADVENTOFCODE_DAY07_HPP
