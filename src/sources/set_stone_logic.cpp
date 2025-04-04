#include "../headers/go_logic.h"

#include <stack>
#include <iostream>

namespace go_logic {
    int GoLogic::get_local_liberty(int x, int y, const std::vector<std::string>& cur_board) const {
        if (!is_valid_cord(x, y)) {
            std::string err_msg = "Invalid cord: (" + std::to_string(x) + ", " +
                    std::to_string(y) + ")";
            throw std::invalid_argument(err_msg);
        }
        if (!is_occupied_by_stone(x, y)) {
            std::string err_msg = "Cord (" + std::to_string(x) + ", " +
                    std::to_string(y) + ") is not occupied by stone";
            throw std::invalid_argument(err_msg);
        }

        int local_liberty = 0;
        std::stack<std::pair<int, int>> cord_stack;
        cord_stack.emplace(x, y);
        std::vector<std::vector<bool>> unvisited(BOARD_LENGTH,
                                                 std::vector<bool>(BOARD_LENGTH,
                                                                   true));
        unvisited[x][y] = false;

        while (!cord_stack.empty()) {
            std::pair<int, int> cur_cord = cord_stack.top();
            int cur_x = cur_cord.first;
            int cur_y = cur_cord.second;
            cord_stack.pop();
            for (auto& dir: SEARCH_DIRECTIONS) {
                int next_x = cur_cord.first + dir[0];
                int next_y = cur_cord.second + dir[1];

                if (!is_valid_cord(next_x, next_y)) {
                    continue;
                }
                if (!unvisited[next_x][next_y]) {
                    continue;
                }

                if (!is_occupied_by_stone(next_x, next_y)) {
                    ++local_liberty;
                    unvisited[next_x][next_y] = false;
                    continue;
                }
                if (cur_board[next_x][next_y] != cur_board[cur_x][cur_y]) {
                    continue;
                }
                unvisited[next_x][next_y] = false;
                cord_stack.emplace(next_x, next_y);
            }
        }

        return local_liberty;
    }

    void GoLogic::remove_stones(int x, int y) {
        if (!is_valid_cord(x, y)) {
            std::string err_msg = "Invalid cord: (" + std::to_string(x) + ", " +
                                  std::to_string(y) + ")";
            throw std::invalid_argument(err_msg);
        }
        if (!is_occupied_by_stone(x, y)) {
            std::string err_msg = "Cord (" + std::to_string(x) + ", " +
                                  std::to_string(y) + ") is not occupied by stone";
            throw std::invalid_argument(err_msg);
        }

        std::stack<std::pair<int, int>> cord_stack;
        cord_stack.emplace(x, y);
        auto cur_stone = board_info[x][y];

        while (!cord_stack.empty()) {
            std::pair<int, int> cur_cord = cord_stack.top();
            cord_stack.pop();
            board_info[cur_cord.first][cur_cord.second] = FREE;
            for (auto& dir: SEARCH_DIRECTIONS) {
                int next_x = cur_cord.first + dir[0];
                int next_y = cur_cord.second + dir[1];
                if (!is_valid_cord(next_x, next_y)) {
                    continue;
                }
                if (board_info[next_x][next_y] == cur_stone) {
                    cord_stack.emplace(next_x, next_y);
                }
            }
        }
    }

    void GoLogic::set_stone(int x, int y) {
        if (!is_valid_cord(x, y)) {
            std::string err_msg = "Invalid cord: (" + std::to_string(x) + ", " +
                                  std::to_string(y) + ")";
            throw std::invalid_argument(err_msg);
        }
        if (is_occupied_by_stone(x, y)) {
            is_last_move_valid = false;
            return;
        }

        auto friendly_color = is_black_turn ? BLACK: WHITE;
        auto enemy_color = is_black_turn? WHITE: BLACK;

        board_info[x][y] = friendly_color;

        for (auto& dir: SEARCH_DIRECTIONS) {
            int next_x = x + dir[0];
            int next_y = y + dir[1];
            if (!is_valid_cord(next_x, next_y)) {
                continue;
            }
            if (board_info[next_x][next_y] == enemy_color) {
                int surrounding_enemy_liberty = get_local_liberty(next_x, next_y, board_info);
                if (surrounding_enemy_liberty == 0) {
                    remove_stones(next_x, next_y);
                }
            }
        }

        int local_liberty = get_local_liberty(x, y, board_info);
        if (local_liberty == 0) {
            board_info[x][y] = FREE;
            is_last_move_valid = false;
            return;
        }

        std::string cur_bord_info = record_current_board();
        if (record.size() >= 2 && cur_bord_info == record[record.size() - 2].get_board()) {
            reset_to_last_move();
            is_last_move_valid = false;
        }

        is_black_turn = !is_black_turn;
    }
}