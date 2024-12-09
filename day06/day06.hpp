#ifndef ADVENTOFCODE_DAY06_HPP
#define ADVENTOFCODE_DAY06_HPP

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

static std::vector<std::vector<char>> read_day06() {
    std::ifstream file_stream{};
    file_stream.open("../day06/puzzle_input.txt");

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

static std::pair<int, int> find_guard(const std::vector<std::vector<char>> &grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == '^') {
                return {j, i};
            }
        }
    }
    return {-1, -1};
}

void day06part1() {

    auto grid = read_day06();
    auto pos = find_guard(grid);
    Direction dir = UP;

    bool left_grid = false;


    while (!left_grid) {
        std::pair<int, int> next_pos;
        switch (dir) {
            case UP:
                next_pos = {pos.first, pos.second - 1};
                break;
            case RIGHT:
                next_pos = {pos.first + 1, pos.second};
                break;
            case DOWN:
                next_pos = {pos.first, pos.second + 1};
                break;
            case LEFT:
                next_pos = {pos.first - 1, pos.second};
                break;
        }

        grid[pos.second][pos.first] = 'X';
        if (next_pos.first < 0 or next_pos.first >= grid.size() or next_pos.second < 0 or
            next_pos.second >= grid[0].size()) {
            left_grid = true;
        } else if (grid[next_pos.second][next_pos.first] == '#') {
            dir = static_cast<Direction>((dir + 1) % 4);
        } else {
            pos = next_pos;
        }
    }

    int x_sum = 0;

    // Count X's
    for (auto &row: grid) {
        for (char tile: row) {
            if (tile == 'X') {
                ++x_sum;
            }
        }
    }

    std::cout << x_sum << '\n';

}

static bool test_for_loop(std::vector<std::vector<char>> grid, std::pair<int, int> pos) {

    Direction dir = UP;

    while (true) {
        std::pair<int, int> next_pos;
        switch (dir) {
            case UP:
                next_pos = {pos.first, pos.second - 1};
                grid[pos.second][pos.first] = grid[pos.second][pos.first] == '.' ? 'U' : grid[pos.second][pos.first];
                break;
            case RIGHT:
                next_pos = {pos.first + 1, pos.second};
                grid[pos.second][pos.first] = grid[pos.second][pos.first] == '.' ? 'R' : grid[pos.second][pos.first];
                break;
            case DOWN:
                next_pos = {pos.first, pos.second + 1};
                grid[pos.second][pos.first] = grid[pos.second][pos.first] == '.' ? 'D' : grid[pos.second][pos.first];
                break;
            case LEFT:
                next_pos = {pos.first - 1, pos.second};
                grid[pos.second][pos.first] = grid[pos.second][pos.first] == '.' ? 'L' : grid[pos.second][pos.first];
                break;
        }

        if (next_pos.first < 0 or next_pos.first >= grid[0].size() or next_pos.second < 0 or
            next_pos.second >= grid.size()) {
            return false;
        } else if (grid[next_pos.second][next_pos.first] == '#') {
            dir = static_cast<Direction>((dir + 1) % 4);
        } else if (grid[next_pos.second][next_pos.first] == 'U' and dir == UP or
                                                                    grid[next_pos.second][next_pos.first] == 'R' and
                   dir == RIGHT or
                   grid[next_pos.second][next_pos.first] == 'D' and dir == DOWN or
                                                                    grid[next_pos.second][next_pos.first] == 'L' and
                   dir == LEFT) {
            return true;
        } else {
            pos = next_pos;
        }
    }
}

void day06part2() {
    auto grid = read_day06();
    auto pos = find_guard(grid);
    Direction dir = UP;

    bool left_grid = false;

    int obst_count = 0;

    while (!left_grid) {
        std::pair<int, int> next_pos;
        switch (dir) {
            case UP:
                next_pos = {pos.first, pos.second - 1};
                break;
            case RIGHT:
                next_pos = {pos.first + 1, pos.second};
                break;
            case DOWN:
                next_pos = {pos.first, pos.second + 1};
                break;
            case LEFT:
                next_pos = {pos.first - 1, pos.second};
                break;
        }
        grid[pos.second][pos.first] = 'X';

        if (next_pos.first < 0 or next_pos.first >= grid[0].size() or next_pos.second < 0 or
            next_pos.second >= grid.size()) {
            left_grid = true;
        } else if (grid[next_pos.second][next_pos.first] == '#') {
            dir = static_cast<Direction>((dir + 1) % 4);
        } else {
            pos = next_pos;
        }
    }

    std::vector<std::pair<int, int>> walked_tiles;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'X') {
                walked_tiles.emplace_back(i, j);
            }
        }
    }

    grid = read_day06();
    std::pair<int, int> start_pos = find_guard(grid);

    for (auto &tile: walked_tiles) {
        char temp_value = grid[tile.first][tile.second];
        grid[tile.first][tile.second] = '#';
        if (test_for_loop(grid, start_pos)) {
            ++obst_count;
        }

        grid[tile.first][tile.second] = temp_value;
    }

    std::cout << obst_count << '\n';

}

#endif //ADVENTOFCODE_DAY06_HPP
