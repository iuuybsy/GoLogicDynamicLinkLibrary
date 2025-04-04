#include "../headers/go_logic.h"

namespace go_logic {
    void GoLogic::regret() {
        if (this->record.empty()) {
            return;
        }
        record.pop_back();
        reset_to_last_move();
    }
}