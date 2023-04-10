#include <game.hpp>

/**
 * Every Stone will have a StoneChain.
 * If the liberties of this chain are surrounded with stones,
 * and all these surrounding stones have the opposite color to 
 * the color of the chain, then all the stones in the chain are captured.
*/


// Constructor
Game::Game():window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", sf::Style::Default, SETTINGS) {
    SETTINGS.antialiasingLevel = 10;
}

void Game::captureStone(Stone stone) {
    
}

int main() {
    Game game;
    game.run();
}