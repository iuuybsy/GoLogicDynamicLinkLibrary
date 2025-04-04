#include <iostream>

#include "src/headers/go_logic.h"

int main() {
    auto logic = go_logic::GoLogic();

    int moves[][2] = {{0, 0},
                      {1, 1},
                      {1, 0},
                      {0, 1},
                      {0, 2},
                      {2, 0},
                      {1, 0},
                      {0, 0},
                      {1, 0}};
    for (auto& move: moves) {
        logic.set_stone(move[0], move[1]);
        logic.print_board_info();
        std::cout << std::endl;
    }
}