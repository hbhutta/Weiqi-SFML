#include <SFML/Graphics.hpp>
// #include <math.h>

/**
 * Near: (Resolved)
 * You haven't showed your render method, but it most likely clears the window. When processing events you should for example just save that a cell is now occupied
 * And only in render actually render everything based on your data
 * This can be as simple as a 2D array for the board
 * And if you handle the click event just store a flag in the array indicating that a clicked position now belongs to the player
 * And the render method would iterate over that array every frame and render the board state based on it
*/

class Game {
    public:
        Game();

        struct Stone {
            float x;
            float y;
            sf::Color color;
        };

        void run() {
            while (window.isOpen()) {
                processEvents();
                update();
                render();
            }
        }

        void processEvents() {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed: {
                        window.close();
                    }
                    case sf::Event::MouseButtonPressed: {
                         if (event.mouseButton.button == sf::Mouse::Left) {
                            int x = roundToHundreds(event.mouseButton.x);
                            int y = roundToHundreds(event.mouseButton.y);

                            struct Stone stone;

                            if (TURN_COLOR) {
                                stone.x = x;
                                stone.y = y;
                                stone.color = sf::Color::White;
                                printf("Placing black stone at (%d, %d)\n", x, y);
                                // constructStone(x, y, sf::Color::White);

                            }
                            else {
                                stone.x = x;
                                stone.y = y;
                                stone.color = sf::Color::Black;
                                printf("Placing white stone at (%d, %d)\n", x, y);
                                // constructStone(x, y, sf::Color::Black);
                            }
                            TURN_COLOR = !(TURN_COLOR);
                            flagPosition(stone);
                         }
                    }   
                }
            }
        }

        void flagPosition(Stone stone) {
            BOARD.push_back(stone);
        }

        void updateBoard() {
            for (int i = 0; i < BOARD.size(); i++) {
                drawStone(BOARD[i]);
            }
        }

        void drawStone(Stone stone) {
            float STONE_RADIUS = CELL_SIZE / 2;
            float STONE_OUTLINE_THICKNESS = 3.f;

            sf::CircleShape black_stone_shape;
            black_stone_shape.setRadius(STONE_RADIUS);
            black_stone_shape.setOrigin(black_stone_shape.getLocalBounds().width / 2, black_stone_shape.getLocalBounds().height / 2);
            black_stone_shape.setFillColor(stone.color);
            black_stone_shape.setOutlineThickness(STONE_OUTLINE_THICKNESS);
            black_stone_shape.setOutlineColor(sf::Color::Black);
            black_stone_shape.setPosition(sf::Vector2f(stone.x, stone.y));

            window.draw(black_stone_shape);
        }
        
        int roundToHundreds(int value) {
            int tens = value % 100;
            int step = 50;
            if (tens < 50) {
                return value - tens;
            }
            return (value - tens) + 100;
        } 
    
        
        void update() {
        }

        void render() {
            window.clear(sf::Color(230, 210, 90)); 

            drawBoard();
            updateBoard();
            
            window.display();
            float x = window.getSize().x;
            float y = window.getSize().y;
        }

        void drawBoard() {
            drawBorders();
            drawLines();
            drawStarPoints();
        }

        void drawBorders() {
            int BORDER_SIZE = CELL_SIZE;
            sf::RectangleShape top_border, bottom_border, left_border, right_border;
            std::vector<sf::RectangleShape> borders;
            borders.push_back(top_border);
            borders.push_back(left_border);
            borders.push_back(left_border);
            borders.push_back(right_border);

            for (sf::RectangleShape border : borders) {
                border.setFillColor(sf::Color::Black);
            }

            top_border.setSize(sf::Vector2f(WINDOW_WIDTH, BORDER_SIZE));
            top_border.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 0));

            bottom_border.setSize(sf::Vector2f(WINDOW_WIDTH, BORDER_SIZE));
            bottom_border.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT));

            left_border.setSize(sf::Vector2f(BORDER_SIZE, WINDOW_HEIGHT));
            left_border.setPosition(sf::Vector2f(0, WINDOW_HEIGHT / 2));

            right_border.setSize(sf::Vector2f(BORDER_SIZE, WINDOW_HEIGHT));
            right_border.setPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2));
        }

        void drawLines() {
            drawHorizontalLines();
            drawVerticalLines();
        }
        
        void drawHorizontalLines() {
            for (int y = 0; y < 19 + 1 + 1; y++) {
                sf::Vertex v_tail;
                v_tail.position = sf::Vector2f(0, CELL_SIZE + y*CELL_SIZE);
                sf::Vertex v_head;
                v_head.position = sf::Vector2f(WINDOW_WIDTH, CELL_SIZE + y*CELL_SIZE);

                sf::Vertex vertical_line[] = {
                    v_tail,
                    v_head
                };
                vertical_line[0].color = sf::Color::Black;
                vertical_line[1].color = sf::Color::Black;
                window.draw(vertical_line, 2, sf::Lines);
            }
        }

        void drawVerticalLines() {
            for (int x = 0; x < 19 + 1 + 1; x++) {
                sf::Vertex v_tail;
                v_tail.position = sf::Vector2f(CELL_SIZE + x*CELL_SIZE, 0);
                sf::Vertex v_head;
                v_head.position = sf::Vector2f(CELL_SIZE + x*CELL_SIZE, WINDOW_HEIGHT);

                sf::Vertex vertical_line[] = {
                    v_tail,
                    v_head
                };
                
                vertical_line[0].color = sf::Color::Black;
                vertical_line[1].color = sf::Color::Black;
                window.draw(vertical_line, 2, sf::Lines);
            }
        }

        void drawStarPoints() {
            sf::CircleShape starPoint;
            starPoint.setRadius(15.f);
            starPoint.setOrigin(starPoint.getLocalBounds().width / 2, starPoint.getLocalBounds().height / 2);
            starPoint.setFillColor(sf::Color::Black);

            starPoint.setPosition(sf::Vector2f((3 * CELL_SIZE), (3 * CELL_SIZE)));
            window.draw(starPoint); // TOP-LEFT

            starPoint.setPosition(sf::Vector2f(((19 / 2) * CELL_SIZE), (3 * CELL_SIZE)));
            window.draw(starPoint); // TOP-MIDDLE

            starPoint.setPosition(sf::Vector2f(((19 - 3) * CELL_SIZE), (3 * CELL_SIZE)));
            window.draw(starPoint); // TOP-RIGHT

            starPoint.setPosition(sf::Vector2f((3 * CELL_SIZE), ((19 / 2) * CELL_SIZE)));
            window.draw(starPoint); // MIDDLE-LEFT

            starPoint.setPosition(sf::Vector2f(((19 / 2) * CELL_SIZE), ((19 / 2) * CELL_SIZE)));
            window.draw(starPoint); // CENTER

            starPoint.setPosition(sf::Vector2f(((19 - 3) * CELL_SIZE), ((19 / 2) * CELL_SIZE)));
            window.draw(starPoint); // MIDDLE-RIGHT

            starPoint.setPosition(sf::Vector2f((3 * CELL_SIZE), ((19 - 3) * CELL_SIZE)));
            window.draw(starPoint); // BOTTOM-LEFT

            starPoint.setPosition(sf::Vector2f(((19 / 2) * CELL_SIZE), ((19 - 3) * CELL_SIZE)));
            window.draw(starPoint); // BOTTOM-CENTER

            starPoint.setPosition(sf::Vector2f(((19 - 3) * CELL_SIZE), ((19 - 3) * CELL_SIZE)));
            window.draw(starPoint); // BOTTOM-RIGHT
        }

    private:
        // Window constants
        int WINDOW_WIDTH = 1900;
        int WINDOW_HEIGHT = WINDOW_WIDTH;
        sf::RenderWindow window;

        // Window settings
        sf::ContextSettings SETTINGS;

        // Board constants
        int BOARD_SIZE = 19;
        int RIGHT_BORDER = 100, LEFT_BORDER = 0, TOP_BORDER = 100, BOTTOM_BORDER = 100;
        int PADDING = 100;
        int CELL_SIZE = WINDOW_WIDTH / BOARD_SIZE;

        int EMPTY = -1, BLACK = 0, WHITE = 1;

        /**
         * Possible entries are:
         * EMPTY : -1
         * BLACK : 0
         * WHITE : 1
        */
        std::vector<Stone> BOARD; // 2D Array

        bool TURN_COLOR = 0;
        // int HALF_CELL_SIZE = CELL_SIZE / 2;

        // Sprites
        sf::Sprite board_background;

        // Textures
        sf::Texture background_texture;

        // Shapes
        sf::CircleShape BLACK_STONE;
        sf::CircleShape WHITE_STONE;
        // sf::CircleShape EMPTY_STONE;
};

// Constructor
Game::Game():window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", sf::Style::Default, SETTINGS) {
    SETTINGS.antialiasingLevel = 10;
}

int main() {
    Game game;
    game.run();
}