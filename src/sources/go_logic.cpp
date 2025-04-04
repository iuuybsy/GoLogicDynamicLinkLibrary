#include "../headers/go_logic.h"

#include <iostream>

namespace go_logic {
    void GoLogic::print_board_info() noexcept {
        for (int i = BOARD_LENGTH - 1; i != -1; --i) {
            for (int j = 0; j!= BOARD_LENGTH; ++j) {
                std::cout << board_info[j][i];
            }
            std::cout << std::endl;
        }
    }

    bool GoLogic::is_valid_cord(int x, int y) noexcept {
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
        return this->board_info[x][y] != FREE;
    }
}