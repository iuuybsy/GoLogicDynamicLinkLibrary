#include "../headers/go_logic.h"

namespace go_logic {
    Move GoLogic::move(MoveType move_type, int x, int y) {
        if (move_type == MoveType::PASS) {
            pass();
        }
        else if (move_type == MoveType::REGRET) {
            regret();
        }
        else {
            is_last_move_valid = true;
            set_stone(x, y);
        }

        is_last_move_pass = move_type == MoveType::PASS;

        std::string cur_bord_info = record_current_board();
        Move move(move_type, x, y, is_black_turn, cur_bord_info);
        if (move_type == MoveType::SET_STONE && is_last_move_valid) {
            record.push_back(move);
        }
        return move;
    }
}