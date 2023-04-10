#include <SFML/Graphics.hpp>

// PAT: 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

class Game {
    public:
        Game();
        void run() {
            // loadTextures();
            createBoard();
            while (window.isOpen()) {
                processEvents();
                update();
                render();
            }
        }

        void createBoard() {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    BOARD[i].push_back(EMPTY);
                }
            }
        }

        void loadTextures() {
            // try {
            //     background_texture.loadFromFile("images/background/wood_3.png");
            //     board_background.setScale(5.f, 5.f);
            //     board_background.setTexture(background_texture);
            // }
            // catch (std::runtime_error) {
            //     // just catch, do nothing; resort to backup
            // }
            // test
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
                            float x = event.mouseButton.x;
                            float y = event.mouseButton.y;

                            printf("Placing stone...\n");
                            placeStone(x, y); // stone must be of the right color (if black stone was previously placed, next stone is white)
                         }
                    }
                }
            }
        }
    
        /**
         * When the stone is placed, round the x and y values to multiples of 100
        */
        void placeStone(float x, float y) {
            sf::CircleShape white_stone_shape;
            white_stone_shape.setRadius(CELL_SIZE / 2);
            white_stone_shape.setFillColor(sf::Color::White);
            white_stone_shape.setPosition(sf::Vector2f(x,y));
            window.draw(white_stone_shape);
            printf("Placed white stone at (%4.2f, %4.2f)\n", x, y);
            /**
             * try-catch load texture for fancy stone
             * otherwise just use sf::CircleShape
            */
            if (TURN_COLOR) {
                
            }


            else {
                sf::CircleShape black_stone_shape;
                black_stone_shape.setRadius(CELL_SIZE);
                black_stone_shape.setFillColor(sf::Color::Black);
                black_stone_shape.setPosition(sf::Vector2f(x,y));
                window.draw(black_stone_shape);
                printf("Placed black stone at (%4.2f, %4.2f)\n", x, y);
            }
            TURN_COLOR = !(TURN_COLOR); 
        }
        
        void update() {
            // Updates stone positions if a stone has been placed/captured/etc..
        }

         // float STONE_RADIUS = CELL_SIZE / 2;
            // float STONE_OUTLINE_THICKNESS = 1.f;

            // sf::CircleShape black_stone_shape;
            // black_stone_shape.setRadius(STONE_RADIUS);
            // black_stone_shape.setOrigin(black_stone_shape.getLocalBounds().width / 2, black_stone_shape.getLocalBounds().height / 2);
            // black_stone_shape.setFillColor(sf::Color::Black);
            // black_stone_shape.setOutlineThickness(STONE_OUTLINE_THICKNESS);
            // black_stone_shape.setOutlineColor(sf::Color::Black);
            // black_stone_shape.setPosition(sf::Vector2f(900,900));
            // window.draw(black_stone_shape);

            // sf::CircleShape white_stone_shape;
            // white_stone_shape.setRadius(STONE_RADIUS);
            // white_stone_shape.setOrigin(white_stone_shape.getLocalBounds().width / 2, white_stone_shape.getLocalBounds().height / 2);
            // white_stone_shape.setFillColor(sf::Color::White);
            // white_stone_shape.setOutlineThickness(STONE_OUTLINE_THICKNESS);
            // white_stone_shape.setOutlineColor(sf::Color::Black);
            // white_stone_shape.setPosition(sf::Vector2f(1000,900));
            // window.draw(white_stone_shape);

        void render() {
            /**
             * 1. Clear
             * 2. Draw
             * 3. Display
            */

            window.clear(sf::Color(230, 210, 90)); // Backup background
            // window.draw(board_background); // Needs to be drawn everytime, so keep in loop

            drawBoard();

           

            window.display();
            float x = window.getSize().x;
            float y = window.getSize().y;
            // window.setPosition(sf::Vector2i(x,y));
        }

        void drawBoard() {
            drawLines();
            drawStarPoints();
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
            // std::cout << "drawing star points";
            /**
             * Draw 9 small circles at the corrrect positions relative to the window width and height using a for loop
            */

            sf::CircleShape starPoint;
            // float offset = (6.9 + (star_radius / 2));
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
        std::vector<std::vector<int>> BOARD; // 2D Array

        bool TURN_COLOR = 0;
        // int HALF_CELL_SIZE = CELL_SIZE / 2;

        // Sprites
        sf::Sprite board_background;
        // sf::Sprite black_stone;
        // sf::Sprite white_stone;

        // Textures
        // sf::Texture black_stone_texture;
        // sf::Texture white_stone_texture;
        sf::Texture background_texture;

        // Shapes
};

// Constructor
Game::Game():window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", sf::Style::Default, SETTINGS) {
    SETTINGS.antialiasingLevel = 10;
}

int main() {
    Game game;
    game.run();
}