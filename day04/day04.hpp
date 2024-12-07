#ifndef ADVENTOFCODE_DAY04_HPP
#define ADVENTOFCODE_DAY04_HPP

static std::vector<std::vector<char>> read_grid() {
    std::ifstream file_stream{};
    file_stream.open("../day04/puzzle_input.txt");

    std::vector<std::vector<char>> grid{{}};

    int row = 0;
    char ch;
    while (file_stream.get(ch)) {

        if (ch == '\n') {
            ++row;
            grid.emplace_back();
            continue;
        }

        grid[row].push_back(ch);

    }

    file_stream.close();

    return grid;
}

void day04part1() {

    auto grid = read_grid();

    int hits = 0;

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            // dir: up
            if (row - 3 >= 0) {
                if (grid[row][col] == 'X' and grid[row - 1][col] == 'M' and grid[row - 2][col] == 'A' and
                    grid[row - 3][col] == 'S')
                    ++hits;
            }
            // dir: up-right
            if (row - 3 >= 0 and col + 3 < grid[0].size()) {
                if (grid[row][col] == 'X' and grid[row - 1][col + 1] == 'M' and grid[row - 2][col + 2] == 'A' and
                    grid[row - 3][col + 3] == 'S')
                    ++hits;
            }
            // dir: right
            if (col + 3 < grid[0].size()) {
                if (grid[row][col] == 'X' and grid[row][col + 1] == 'M' and grid[row][col + 2] == 'A' and
                    grid[row][col + 3] == 'S')
                    ++hits;
            }
            // dir: down-right
            if (row + 3 < grid.size() and col + 3 < grid[0].size()) {
                if (grid[row][col] == 'X' and grid[row + 1][col + 1] == 'M' and grid[row + 2][col + 2] == 'A' and
                    grid[row + 3][col + 3] == 'S')
                    ++hits;
            }
            // dir: down
            if (row + 3 < grid.size()) {
                if (grid[row][col] == 'X' and grid[row + 1][col] == 'M' and grid[row + 2][col] == 'A' and
                    grid[row + 3][col] == 'S')
                    ++hits;
            }
            // dir: down-left
            if (row + 3 < grid.size() and col - 3 >= 0) {
                if (grid[row][col] == 'X' and grid[row + 1][col - 1] == 'M' and grid[row + 2][col - 2] == 'A' and
                    grid[row + 3][col - 3] == 'S')
                    ++hits;
            }
            // dir: left
            if (col - 3 >= 0) {
                if (grid[row][col] == 'X' and grid[row][col - 1] == 'M' and grid[row][col - 2] == 'A' and
                    grid[row][col - 3] == 'S')
                    ++hits;
            }
            // dir: top-left
            if (row - 3 >= 0 and col - 3 >= 0) {
                if (grid[row][col] == 'X' and grid[row - 1][col - 1] == 'M' and grid[row - 2][col - 2] == 'A' and
                    grid[row - 3][col - 3] == 'S')++hits;
            }
        }
    }

    std::cout << hits << '\n';

}

void day04part2() {

    auto grid = read_grid();

    int hits = 0;

    for (int row = 1; row < grid.size()-1; ++row) {
        for (int col = 1; col < grid[0].size()-1; ++col) {
            if (grid[row-1][col-1] == 'M' and grid[row-1][col+1] == 'M' and grid[row][col] == 'A' and grid[row+1][col-1] == 'S' and grid[row+1][col+1] == 'S')++hits;
            if (grid[row-1][col-1] == 'M' and grid[row-1][col+1] == 'S' and grid[row][col] == 'A' and grid[row+1][col-1] == 'M' and grid[row+1][col+1] == 'S')++hits;
            if (grid[row-1][col-1] == 'S' and grid[row-1][col+1] == 'M' and grid[row][col] == 'A' and grid[row+1][col-1] == 'S' and grid[row+1][col+1] == 'M')++hits;
            if (grid[row-1][col-1] == 'S' and grid[row-1][col+1] == 'S' and grid[row][col] == 'A' and grid[row+1][col-1] == 'M' and grid[row+1][col+1] == 'M')++hits;
        }
    }

    std::cout << hits << '\n';

}

#endif //ADVENTOFCODE_DAY04_HPP
