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

    enum class MoveType {
        PASS,
        REGRET,
        SET_STONE
    };

    class Move {
    private:
        MoveType move_type;
        int x;
        int y;
        std::string board;
        bool is_black_move;
    public:
        Move(MoveType move_type, int x, int y, bool is_black_move, std::string board):
                move_type(move_type), x(x), y(y), is_black_move(is_black_move), board(board) {}
        ~Move() = default;

        bool get_is_black_move() const noexcept { return is_black_move; }
        MoveType get_move_type() const noexcept { return move_type; }
        std::pair<int, int> get_last_move() const noexcept { return {x, y}; }
        std::string get_board() const noexcept { return board; }
    };

    class GoLogic {
    private:
        std::vector<std::string> board_info;
        std::vector<Move> record;
        bool is_black_turn;
        bool is_game_finished;
        bool is_last_move_pass;
        bool is_last_move_valid;

    public:
        GoLogic(): board_info(std::vector<std::string>(BOARD_LENGTH, std::string(BOARD_LENGTH, FREE))),
                is_black_turn(true),
                is_game_finished(false),
                is_last_move_pass(false),
                is_last_move_valid(true) {}
        ~GoLogic() = default;
        void print_board_info() const noexcept;
        bool game_finished() const noexcept;
        Move move(MoveType move_type, int x = -1, int y = -1);

    private:
        static bool is_valid_cord(int x, int y) noexcept;
        bool is_occupied_by_stone(int x, int y) const;
        int get_local_liberty(int x, int y, const std::vector<std::string>& cur_board) const;
        void remove_stones(int x, int y);
        void set_stone(int x, int y);
        void pass();
        void regret();
        std::string record_current_board() const noexcept;
        void reset_to_last_move() noexcept;
    };
}

#endif //GO_LOGIC_H
