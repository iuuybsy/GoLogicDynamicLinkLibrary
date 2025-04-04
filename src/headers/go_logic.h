#ifndef GO_LOGIC_H
#define GO_LOGIC_H

#include <string>
#include <unordered_map>
#include <vector>

namespace go_logic {
    const int BOARD_LENGTH = 19;
    const int SEARCH_DIRECTIONS[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    const char FREE = '.';
    const char BLACK = 'X';
    const char WHITE = 'O';


    class GoLogic {
    private:
        std::vector<std::string> board_info;
        bool is_black_turn;

    public:
        GoLogic(): board_info(std::vector<std::string>(BOARD_LENGTH, std::string(BOARD_LENGTH, FREE))),
                is_black_turn(true) {}
        ~GoLogic() = default;
        void print_board_info() noexcept;
        void set_stone(int x, int y);

    private:
        static bool is_valid_cord(int x, int y) noexcept;
        bool is_occupied_by_stone(int x, int y) const;
        int get_local_liberty(int x, int y, const std::vector<std::string>& cur_board) const;
        void remove_stones(int x, int y);
    };
}

#endif //GO_LOGIC_H
