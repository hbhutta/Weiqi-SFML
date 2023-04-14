#ifndef STONE_HPP
#define STONE_HPP
#include <SFML/Graphics.hpp>

class Stone {
    public:
        float x;
        float y;
        sf::Color color;
        bool isAlive; // dead (false), alive (true); every stone is alive initially

        int getX() {
            return x;
        }

        void setX(int x_) {
            x = x_;
        }

        int getY() {
            return y;
        }

        void setY(int y_) {
            y = y_;
        }

        sf::Color getColor() {
            return color;
        }

        void setColor(sf::Color color_) {
            color = color_;
        }

        bool getIsAlive() {
            return isAlive;
        }

        void setIsAlive(bool isAlive_) {
            isAlive = isAlive_;
        }
};

#endif