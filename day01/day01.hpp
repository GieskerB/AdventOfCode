#ifndef ADVENTOFCODE_DAY01_HPP
#define ADVENTOFCODE_DAY01_HPP

#include <fstream>
#include <iostream>
#include <array>
#include <algorithm>

struct Arrays {
    std::array<unsigned int, 1000> left_list{0}, right_list{0};
};

static Arrays read_arrays() {
    std::ifstream file_stream{};
    file_stream.open("../day01/puzzle_input.txt");

    Arrays arrays;
    int index = 0;
    while (index < 1000 && file_stream.is_open()) {
        unsigned int left, right;
        file_stream >> left >> right;

        arrays.left_list[index] = left;
        arrays.right_list[index] = right;

        ++index;
    }
    file_stream.close();

    std::sort(arrays.left_list.begin(), arrays.left_list.end());
    std::sort(arrays.right_list.begin(), arrays.right_list.end());

    return arrays;
}

void day01part1() {
    auto arrays = read_arrays();

    unsigned int distance_sum = 0;
    for (int i = 0; i < 1000; ++i) {
        distance_sum += arrays.left_list[i] < arrays.right_list[i] ? arrays.right_list[i] - arrays.left_list[i] :
                        arrays.left_list[i] -
                        arrays.right_list[i];
    }

    std::cout << distance_sum << '\n';

}

void day01part2() {

    auto arrays = read_arrays();
    unsigned int similarity_score = 0;
    for (unsigned int value: arrays.left_list) {
        int nums_found = 0;
        unsigned int *ptr_to_found = nullptr;
        while ((ptr_to_found = std::find(arrays.right_list.begin(), arrays.right_list.end(), value)) !=
               arrays.right_list.end()) {
            ++nums_found;
            *ptr_to_found = 0;
        }
        similarity_score += value * nums_found;
    }

    std::cout << similarity_score << '\n';

}

#endif //ADVENTOFCODE_DAY01_HPP
