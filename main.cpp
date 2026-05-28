#include "core/ZOOrkEngine.h"

int main() {
    int playerX = 20, playerY = 16;

    ZOOrkEngine zoork(playerX, playerY);
    zoork.run();
    
    return 0;
}