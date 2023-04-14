#include <SFML/Graphics.hpp>

/* Notes:
- Allow users to save and come back to previous game session using serialization with JSON:
    - https://gamedev.stackexchange.com/questions/25963/how-do-i-create-a-save-file-for-a-c-game
- Allow users to save their games as a .SGF file
- Create bool board to keep track of occupied and non-occupied positions
    - OCCUPIED is edited when:
        1. Initializing it
        2. When a stone is removed by capturing, so that the spot becomes open again
- All initialization functions will be called in the constructor
**/

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

class Game {
    public:
        Game();

        void run() {
            while (window.isOpen()) {
                processEvents();
                // update();
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

                            // struct Stone stone;
                            Stone stone;

                            stone.setX(x);
                            stone.setY(y);
                            
                            if (TURN_COLOR) {
                                stone.setColor(sf::Color::White);
                                printf("Placing white stone at (%d, %d)\n", x, y);
                            }
                            else {
                                stone.color = sf::Color::Black;
                                printf("Placing white stone at (%d, %d)\n", x, y);
                            }
                            stone.setIsAlive(true);
                            TURN_COLOR = !(TURN_COLOR);
                            flagPosition(stone);
                         }
                    }  
                }
            }
        }
        
        bool isStoneAtPosition(int x, int y) {
            return false; // stub
        }

        /**
         * Sets the (x,y) position on the board to a placed stone if the position is empty.
         * When the stone is placed, the value of OCCUPIED at that position is set to true.
         * When it is removed, the value of OCCUPIED is changed to false.
        */
        void flagPosition(Stone stone) {
            if (OCCUPIED[stone.getY()][stone.getX()] == false) {
                BOARD[stone.getY()][stone.getX()] = stone;
                OCCUPIED[stone.getY()][stone.getX()] = true;
            } 
        }

        /**
         * Updates the stones on the board, which includes placing and capturing.
         * 
         * @param Values
         * @return -
        */
        void updateBoard() {
            // BOARD.size() should be null at this stage, how is this working?
            // Use BOARD_SIZE = 19 instead
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    // if (OCCUPIED[i][j] == false) {
                    drawStone(BOARD[i][j]);
                    // }  
                }
            }
        }
    
        void initializeOccupied() { //
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    OCCUPIED[i][j] = false; // All positions are initially empty
                }  
            }
        }

        /**
         * Iterate through BOARD, and for each stone 
         * that has the "captured" tag on it, in a given chain,
         * replace that stone with EMPTY
        */
        // void captureStoneChain(StoneChain stoneChain) {
        //     if (isStoneChainValid()) {
        //         if (isStoneChainDead()) {
        //             for (Stone stone: stoneChain.getChain()) {
        //             captureStone(stone);
        //             }
        //         }
        //     }
        // }

        void removeStone(Stone stone) {

        }
        
        void captureStone(Stone stone); // The body of this function is defined in game.cpp

        void drawStone(Stone stone) {
            float STONE_RADIUS = CELL_SIZE / 2;
            float STONE_OUTLINE_THICKNESS = 3.f;

            sf::CircleShape stone_shape;
            stone_shape.setRadius(STONE_RADIUS);
            stone_shape.setOrigin(stone_shape.getLocalBounds().width / 2, stone_shape.getLocalBounds().height / 2);
            stone_shape.setFillColor(stone.color);
            stone_shape.setOutlineThickness(STONE_OUTLINE_THICKNESS);
            stone_shape.setOutlineColor(sf::Color::Black);
            stone_shape.setPosition(sf::Vector2f(stone.x, stone.y));

            window.draw(stone_shape);
        }
        
        int roundToHundreds(int value) {
            int tens = value % 100;
            int step = 50;
            if (tens < 50) {
                return value - tens;
            }
            return (value - tens) + 100;
        } 
    
        
//         void update() {
//         }

        void render() {
            window.clear(sf::Color(230, 210, 90)); 

            drawBoard();
            updateBoard();
            
            window.display();
            float x = window.getSize().x;
            float y = window.getSize().y;
        }

        void drawBoard() {
//             drawBorders();
            drawLines();
            drawStarPoints();
        }

//         void drawBorders() {
//             int BORDER_SIZE = CELL_SIZE;
//             sf::RectangleShape top_border, bottom_border, left_border, right_border;
//             std::vector<sf::RectangleShape> borders;
//             borders.push_back(top_border);
//             borders.push_back(left_border);
//             borders.push_back(left_border);
//             borders.push_back(right_border);

//             for (sf::RectangleShape border : borders) {
//                 border.setFillColor(sf::Color::Black);
//             }

//             top_border.setSize(sf::Vector2f(WINDOW_WIDTH, BORDER_SIZE));
//             top_border.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 0));

//             bottom_border.setSize(sf::Vector2f(WINDOW_WIDTH, BORDER_SIZE));
//             bottom_border.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT));

//             left_border.setSize(sf::Vector2f(BORDER_SIZE, WINDOW_HEIGHT));
//             left_border.setPosition(sf::Vector2f(0, WINDOW_HEIGHT / 2));

//             right_border.setSize(sf::Vector2f(BORDER_SIZE, WINDOW_HEIGHT));
//             right_border.setPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2));
//         }

        /* Adjusting to prevent stone placement on border (other step includes
        creating a new function related to the rounding function, that prevents 
        a stone from being placed if it is outside of a position interval, which 
        will be a function of WIDTH and HEIGHT
        **/
        void drawLines() {
            drawHorizontalLines();
            drawVerticalLines();
        }
        
        void drawHorizontalLines() {
            for (int y = 0; y < 19 + 1 + 1; y++) {
                sf::Vertex v_tail;
                // 
                v_tail.position = sf::Vector2f(0 + CELL_SIZE, CELL_SIZE + y*CELL_SIZE);
                sf::Vertex v_head;
                v_head.position = sf::Vector2f(WINDOW_WIDTH - CELL_SIZE, CELL_SIZE + y*CELL_SIZE);

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
                v_tail.position = sf::Vector2f(CELL_SIZE + x*CELL_SIZE, 0 + CELL_SIZE);
                sf::Vertex v_head;
                v_head.position = sf::Vector2f(CELL_SIZE + x*CELL_SIZE, WINDOW_HEIGHT - CELL_SIZE);

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
        // 2D arrays, that will have a fixed size; they do not need to be dynamic
        static Stone BOARD[19][19];
        // std::vector<std::vector<Stone>> BOARD;
        static bool OCCUPIED[19][19];

        bool TURN_COLOR = 0;

        // Sprites
        sf::Sprite board_background;

        // Textures
        sf::Texture background_texture;

        // Shapes
        sf::CircleShape BLACK_STONE;
        sf::CircleShape WHITE_STONE;
};