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
        std::cout << move[0] << " " << move[1] << std::endl;
        logic.move(go_logic::MoveType::SET_STONE,move[0], move[1]);
        logic.print_board_info();
        std::cout << std::endl;
        logic.move(go_logic::MoveType::PASS);
        logic.print_board_info();
        std::cout << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    std::cout << "regret" << std::endl;
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
    logic.move(go_logic::MoveType::REGRET);
    logic.print_board_info();
}