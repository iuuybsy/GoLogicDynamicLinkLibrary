#include "GoLogic.h"

#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

namespace go_logic {

    bool GoLogic::is_cord_valid(int x, int y) {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }

    int GoLogic::get_local_liberty(int x, int y) {
        if (this->board[x][y] == Status::EMPTY)
            throw std::invalid_argument("The position is not occupied by any stone.");

        if (!is_cord_valid(x, y)) {
            std::string error_message =
                    "The position is out of range: (" + std::to_string(x) + ", " +
                    std::to_string(y) + ").";
            throw std::out_of_range(error_message);
        }

        auto friendly_status = this->board[x][y];

        bool unvisited[BOARD_SIZE][BOARD_SIZE] = {true};

        std::stack<std::pair<int, int>> count_stack;
        std::pair<int, int> cur_pos = std::make_pair(x, y);
        count_stack.emplace(cur_pos);
        unvisited[cur_pos.first][cur_pos.second] = false;

        int liberty = 0;

        while (!count_stack.empty()) {
            cur_pos = count_stack.top();
            count_stack.pop();

            for (auto direction : SEARCH_DIRECTION) {
                int x_next = cur_pos.first + direction[0];
                int y_next = cur_pos.second + direction[1];

                if (!is_cord_valid(x_next, y_next))
                    continue;
                if (unvisited[x_next][y_next]) {
                    if (this->board[x_next][y_next] == friendly_status) {
                        std::pair<int, int> next_pos = std::make_pair(x_next, y_next);
                        count_stack.emplace(next_pos);
                        unvisited[x_next][y_next] = false;
                    }
                    else if (this->board[x_next][y_next] == Status::EMPTY) {
                        ++liberty;
                        unvisited[x_next][y_next] = false;
                    }
                }
            }
        }
        return liberty;
    }

    void GoLogic::set_liberty(int x, int y, int liberty) {
        if (this->board[x][y] == Status::EMPTY)
            throw std::invalid_argument("The position is not occupied by any stone.");

        if (!is_cord_valid(x, y)) {
            std::string error_message =
                    "The position is out of range: (" + std::to_string(x) + ", " +
                    std::to_string(y) + ").";
            throw std::out_of_range(error_message);
        }

        auto friendly_status = this->board[x][y];

        bool unvisited[BOARD_SIZE][BOARD_SIZE] = {true};

        std::stack<std::pair<int, int>> count_stack;
        std::pair<int, int> cur_pos = std::make_pair(x, y);
        count_stack.emplace(cur_pos);
        unvisited[cur_pos.first][cur_pos.second] = false;

        while (!count_stack.empty()) {
            cur_pos = count_stack.top();
            count_stack.pop();
            this->liberty_rec[cur_pos.first][cur_pos.second] = liberty;

            for (auto direction : SEARCH_DIRECTION) {
                int x_next = cur_pos.first + direction[0];
                int y_next = cur_pos.second + direction[1];

                if (!is_cord_valid(x_next, y_next))
                    continue;
                if (unvisited[x_next][y_next]) {
                    if (this->board[x_next][y_next] == friendly_status) {
                        std::pair<int, int> next_pos = std::make_pair(x_next, y_next);
                        count_stack.emplace(next_pos);
                        unvisited[x_next][y_next] = false;
                    }
                }
            }
        }
    }

    void GoLogic::set_stone(int x, int y) {
        if (this->board[x][y] != Status::EMPTY) {
            std::string error_message =
                    "The position is already occupied by a stone: (" + std::to_string(x) +
                    ", " + std::to_string(y) + ").";
            throw std::invalid_argument(error_message);
        }
        if (!is_cord_valid(x, y)) {
            std::string error_message =
                    "The position is out of range: (" + std::to_string(x) + ", " +
                    std::to_string(y) + ").";
            throw std::out_of_range(error_message);
        }

        this->board[x][y] = this->is_black_move ? Status::BLACK : Status::WHITE;
        int local_liberty = this->get_local_liberty(x, y);
        this->set_liberty(x, y, local_liberty);

        this->is_black_move = !this->is_black_move;
    }

    void GoLogic::plot_board_info() {
        for (int j = BOARD_SIZE - 1; j != -1; --j) {
            for (auto & row : this->board) {
                if (row[j] == Status::EMPTY)
                    std::cout << ". ";
                else if (row[j] == Status::BLACK)
                    std::cout << "X ";
                else if (row[j] == Status::WHITE)
                    std::cout << "O ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
