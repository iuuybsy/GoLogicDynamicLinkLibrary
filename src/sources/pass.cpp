#include "../headers/go_logic.h"

namespace go_logic{
    void GoLogic::pass() {
        if (is_last_move_pass) {
            is_game_finished = true;
            return;
        }
        is_black_turn = !is_black_turn;
    }
}