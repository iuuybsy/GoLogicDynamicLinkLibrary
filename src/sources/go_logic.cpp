#include "../headers/go_logic.h"

#include <iostream>

namespace go_logic {
    int GoLogic::grid_to_list(int x, int y) {
        int ind = x * BOARD_LENGTH + y;
        return ind;
    }

    std::pair<int, int> GoLogic::list_to_grid(int ind) {
        int y = ind % BOARD_LENGTH;
        int x = (ind - y) / BOARD_LENGTH;
        return std::make_pair(x, y);
    }

    void GoLogic::print_board_info() {
        for (int i = 0; i != BOARD_LENGTH; ++i) {
            for (int j = 0; j != BOARD_LENGTH; ++j) {
                int ind = grid_to_list(i, j);
                std::cout << char_to_char_dict.at(board_info[ind]);
            }
            std::cout << std::endl;
        }
    }

    bool GoLogic::is_valid_cord(int x, int y) {
        if (x < 0 || x >= BOARD_LENGTH || y < 0 || y >= BOARD_LENGTH) {
            return false;
        }
        return true;
    }

    bool GoLogic::is_occupied_by_stone(int x, int y) const {
        if (!is_valid_cord(x, y)) {
            std::string err_msg = "Invalid cord: (" + std::to_string(x) + ", " +
                    std::to_string(y) + ")";
            throw std::invalid_argument(err_msg);
        }
        int ind = grid_to_list(x, y);
        if (char_to_status_dict.at(board_info[ind]) != OccupyStatus::Free) {
            return true;
        }
        return false;
    }
}