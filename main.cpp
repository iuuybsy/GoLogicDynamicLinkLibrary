#include <iostream>

#include "GoLogic.h"

int main() {
    go_logic::GoLogic goLogic;
    goLogic.plot_board_info();

    goLogic.set_stone(1, 1);
    goLogic.plot_board_info();

    goLogic.set_stone(0, 1);
    goLogic.plot_board_info();

    goLogic.set_stone(1, 0);
    goLogic.plot_board_info();

    goLogic.set_stone(0, 0);
    goLogic.plot_board_info();

    return 0;
}
