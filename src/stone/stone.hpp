#ifndef STONE_HPP
#define STONE_HPP

class Stone {
    public:
        float x;
        float y;
        sf::Color color;
        bool status; // dead (false), alive (true); every stone is alive initially
};

#endif