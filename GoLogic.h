#ifndef GOLOGIC_H
#define GOLOGIC_H

namespace go_logic {
    const int BOARD_SIZE = 19;
    const int SEARCH_DIRECTION[4][2] =
            {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    enum class Status {
        EMPTY,
        BLACK,
        WHITE,
    };

    class GoLogic {
    public:
        GoLogic() = default;

        void set_stone(int x, int y);

        void plot_board_info();

    private:
        bool is_black_move = true;
        Status board[BOARD_SIZE][BOARD_SIZE] = {Status::EMPTY};
        int liberty_rec[BOARD_SIZE][BOARD_SIZE] = {0};
        int captured_black = 0;
        int captured_white = 0;

        static bool is_cord_valid(int x, int y);
        int get_local_liberty(int x, int y);
        void set_liberty(int x, int y, int liberty);
    };
}

#endif //GOLOGIC_H
