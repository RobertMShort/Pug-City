#include "Game.hpp"

int main(int argc, const char * argv[]) {
    
    static Game game;
    
    while (game.running() && !game.getEndGame()) {
        game.update();
        game.render();
    }

    return 0;
}
