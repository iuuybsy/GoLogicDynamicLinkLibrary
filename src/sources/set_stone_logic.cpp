#include "../headers/go_logic.h"

#include <stack>

namespace go_logic {
    int GoLogic::get_local_liberty(int x, int y) const {
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
        std::string unvisited = std::string(BOARD_LENGTH * BOARD_LENGTH, '1');
        unvisited[grid_to_list(x, y)] = '0';

        while (!cord_stack.empty()) {
            std::pair<int, int> cur_cord = cord_stack.top();
            int cur_ind = grid_to_list(cur_cord.first, cur_cord.second);
            cord_stack.pop();
            for (auto& dir: SEARCH_DIRECTIONS) {
                int next_x = cur_cord.first + dir[0];
                int next_y = cur_cord.second + dir[1];
                if (!is_valid_cord(next_x, next_y)) {
                    continue;
                }

                int next_ind = grid_to_list(next_x, next_y);
                if (unvisited[next_ind] == '0') {
                    continue;
                }
                if (board_info[next_ind] == status_to_char_dict.at(OccupyStatus::Free)) {
                    ++local_liberty;
                    unvisited[next_ind] = '0';
                    continue;
                }
                if (board_info[next_ind] != board_info[cur_ind]) {
                    continue;
                }
                unvisited[next_ind] = '0';
                cord_stack.emplace(next_x, next_y);
            }
        }
        return local_liberty;
    }
}