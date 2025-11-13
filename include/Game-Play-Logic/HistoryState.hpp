#include <vector>

class HistoryState {

public:
    enum class Turn{
        black,
        white
    };

    Turn turn;
    int y_newStone, x_newStone;
    std::vector<std::pair<int, int>> capturedStones;
    bool canredo = false;

    HistoryState(Turn _turn, int y, int x,
                 const std::vector<std::pair<int, int>> &_capturedStones)
        :  turn(_turn), y_newStone(y), x_newStone(x), capturedStones(_capturedStones) {}
};
