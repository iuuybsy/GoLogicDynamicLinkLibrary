#include "../headers/go_logic.h"

#include <iostream>

namespace go_logic {
    bool GoLogic::game_finished() const noexcept {
        return is_game_finished;
    }

    void GoLogic::print_board_info() const noexcept {
        for (int i = BOARD_LENGTH - 1; i != -1; --i) {
            for (int j = 0; j!= BOARD_LENGTH; ++j) {
                std::cout << board_info[j][i];
            }
            std::cout << std::endl;
        }
        std::cout << record.size() << std::endl;
        std::cout << std::endl;
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

    std::string GoLogic::record_current_board() const noexcept {
        std::string cur_bord_info;
        for (int i = 0; i!= BOARD_LENGTH; ++i) {
            cur_bord_info += this->board_info[i];
        }
        return cur_bord_info;
    }

    void GoLogic::reset_to_last_move() noexcept{
        if (this->record.empty()) {
            is_black_turn = true;
            board_info = std::vector<std::string>(BOARD_LENGTH,std::string(BOARD_LENGTH * BOARD_LENGTH, FREE));
            return;
        }
        is_black_turn = record.back().get_is_black_move();
        std::string cur_bord_info = record.back().get_board();
        for (int i = 0; i!= BOARD_LENGTH; ++i) {
            for (int j = 0; j!= BOARD_LENGTH; ++j) {
                board_info[i][j] = cur_bord_info[i * BOARD_LENGTH + j];
            }
        }
    }
}