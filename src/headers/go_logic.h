#ifndef GO_LOGIC_H
#define GO_LOGIC_H

#include <string>
#include <unordered_map>
#include <vector>

namespace go_logic {
    const int BOARD_LENGTH = 19;
    const std::vector<std::vector<int>> SEARCH_DIRECTIONS {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0},
    };

    enum class OccupyStatus {
        Free,
        Black,
        White,
    };

    const std::unordered_map<OccupyStatus, char> status_to_char_dict {
            {OccupyStatus::Free, '0'},
            {OccupyStatus::Black, '1'},
            {OccupyStatus::White, '2'},
    };

    const std::unordered_map<char, OccupyStatus> char_to_status_dict {
            {'0', OccupyStatus::Free,},
            {'1', OccupyStatus::Black},
            {'2', OccupyStatus::White},
    };

    const std::unordered_map<char, char> char_to_char_dict {
            {'0', '.',},
            {'1', 'X'},
            {'2', 'O'},
    };

    class GoLogic {
    private:
        std::string board_info;
        bool is_black_turn;

    public:
        GoLogic(): board_info(std::string(BOARD_LENGTH * BOARD_LENGTH, '0')),
            is_black_turn(true) {}
        ~GoLogic() = default;
        void print_board_info();

    private:
        static int grid_to_list(int x, int y);
        static std::pair<int, int> list_to_grid(int ind);
        static bool is_valid_cord(int x, int y);
        bool is_occupied_by_stone(int x, int y) const;
        int get_local_liberty(int x, int y) const;
    };
}

#endif //GO_LOGIC_H
