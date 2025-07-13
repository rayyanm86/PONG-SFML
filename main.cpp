#include "class.cpp"
#include <iostream>
#include "Button.cpp"
using namespace sf;

void gameLoop(RenderWindow& window, bool isSinglePlayer, string diff);
void Finish(RenderWindow& window, Text* G) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(*G);
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "THE PONG GAME");
    window.setFramerateLimit(60);

    // Load font
    Font font;
    if (!font.loadFromFile("pricedown bl.otf")) {
        std::cout << "Error loading font\n";
        return -1;
    }
    Font Hfont;
    if (!Hfont.loadFromFile("SFSportsNight.ttf")) {
        std::cout << "Error loading font\n";
        return -1;
    }
    Color tcolor(255, 255, 255);
    Text text;
    text.setFont(Hfont);
    text.setString("THE PONG GAME");
    text.setStyle(Text::Bold);
    text.setFillColor(tcolor);
    text.setPosition(Vector2f(100, 0));
    text.setCharacterSize(70);

    Texture pongbg_tex;
    if (!pongbg_tex.loadFromFile("man vs robot.png")) {
        cout << "Error loading background texture\n";
        system("pause");
    }

    RectangleShape pongbg;
    pongbg.setSize(Vector2f(800, 600));
    pongbg.setPosition(0, 0);
    pongbg.setTexture(&pongbg_tex);

    Texture man_tex;
    if (!man_tex.loadFromFile("man vs man.png")) {
        cout << "Error loading man background texture\n";
        system("pause");
    }

    // Create rectangle shape for manbg
    RectangleShape manbg;
    manbg.setSize(Vector2f(window.getSize().x / 2, window.getSize().y)); // Size is half of window height
    manbg.setPosition(window.getSize().x / 2, 0); // Position at bottom half of window
    manbg.setTexture(&man_tex);

    // Load the texture for robotbg
    Texture robot_tex;
    if (!robot_tex.loadFromFile("man vs robot.png")) {
        cout << "Error loading robot background texture\n";
        system("pause");
    }

    // Create rectangle shape for robotbg
    RectangleShape robotbg;
    robotbg.setSize(Vector2f(window.getSize().x / 2, window.getSize().y)); // Size is half of window height
    robotbg.setPosition(0, 0); // Position at top left corner
    robotbg.setTexture(&robot_tex);

    // Create buttons
    Button singlePlayerButton("SINGLE PLAYER", font, Vector2f(100, 400), Vector2f(200, 50));
    Button twoPlayerButton("TWO PLAYER", font, Vector2f(500, 400), Vector2f(200, 50));
    Button easy("EASY", font, Vector2f(300, 400), Vector2f(200, 50));
    Button hard("HARD", font, Vector2f(300, 500), Vector2f(200, 50));
    string difficulty = "";
    bool isSinglePlayer = false;
    bool gameSelected = false;
    bool difficultySelected = false;
    bool theme_selected = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    if (!gameSelected) {
                        if (singlePlayerButton.isClicked(mousePos)) {
                            isSinglePlayer = true;
                            gameSelected = true;
                        }
                        else if (twoPlayerButton.isClicked(mousePos)) {
                            isSinglePlayer = false;
                            gameSelected = true;
                            difficultySelected = true;
                        }
                    }
                    else if (isSinglePlayer && !difficultySelected) {
                        if (easy.isClicked(mousePos)) {
                            difficulty = "Easy";
                            difficultySelected = true;
                        }
                        else if (hard.isClicked(mousePos)) {
                            difficulty = "Hard";
                            difficultySelected = true;
                        }
                    }
                }
            }
        }

        window.clear();

        if (!gameSelected) {
            window.draw(robotbg);
            window.draw(manbg);
            window.draw(text);
            singlePlayerButton.draw(window);
            twoPlayerButton.draw(window);

        }
        else if (isSinglePlayer && !difficultySelected) {
            window.draw(pongbg);
            window.draw(text);
            easy.draw(window);
            hard.draw(window);
        }
        else {
            gameLoop(window, isSinglePlayer, difficulty);
            break; // Exit the main loop to start the game loop
        }

        window.display();
    }

    return 0;
}

void gameLoop(RenderWindow& window, bool isSinglePlayer, string diff)
{
    Clock clock;
    Clock gameClock;
    float dt = 0.f;
    float dtMult = 58.8f;


    //======================================INIT=================================
    Texture bg_tex;
    if (!bg_tex.loadFromFile("bg.png")) {
        std::cout << "Error loading background texture\n";
        system("pause");
    }

    int time = 60;
    int maxScore = 10;
    bool starting = false;
    bool p1WonLastRound = false;
    bool p2WonLastRound = false;
    bool aiWonLastRound = false;
    CircleShape ball(20.f);
    ball.setPosition(Vector2f(400, 200));
    player1 p1(10, 100);
    player2 p2;
    AIopponent ai;
    RectangleShape background;
    background.setSize(Vector2f(800, 600));
    background.setPosition(0, 0);
    background.setTexture(&bg_tex);
    const float wallWidth = 10.f;
    const float wallHeight = 10.f;
    Color deewar(191, 0, 255);

    //SCORE PRINTING
    Font Sfont;
    if (!Sfont.loadFromFile("CursedTimerUlil-Aznm.ttf")) {
        std::cout << "Error loading font\n";
    }
    Text score;
    score.setFont(Sfont);
    auto updateScoreText = [&]() {
        score.setString(to_string(p1.getScore()));
        };
    score.setString(to_string(p1.getScore()));
    score.setPosition(Vector2f(window.getSize().x / 2 - 200, 30));
    score.setCharacterSize(90);

    Font Gfont;
    if (!Gfont.loadFromFile("JackportCollegeNcv-1MZe.ttf")) {
        std::cout << "Error loading font\n";
    }
    Text GameOver;
    GameOver.setFont(Gfont);
    GameOver.setPosition(Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2));
    GameOver.setCharacterSize(60);
    Color neonBlue(0, 150, 150);
    GameOver.setFillColor(neonBlue);

    Text secondScore;
    secondScore.setFont(Sfont);
    auto updateScoreText2 = [&]() {
        secondScore.setString(to_string(p2.getScore()));
        };
    secondScore.setString(to_string(p2.getScore()));
    secondScore.setPosition(Vector2f(window.getSize().x / 2 + 100, 30));
    secondScore.setCharacterSize(90);

    Text timer;
    timer.setFont(Sfont);
    auto updateTimer = [&]() {
        timer.setString(to_string(time));
        };
    timer.setString(to_string(p2.getScore()));
    timer.setPosition(Vector2f(30, 30));
    timer.setCharacterSize(30);

    Text aiScore;
    aiScore.setFont(Sfont);
    auto updateAiScoreText = [&]() {
        aiScore.setString(to_string(ai.getScore()));
        };
    aiScore.setString(to_string(ai.getScore()));
    aiScore.setPosition(Vector2f(window.getSize().x / 2 + 100, 30));
    aiScore.setCharacterSize(90);

    // Initialize ball velocity
    Vector2f ballVelocity;

    // Create top and bottom walls
    vector<RectangleShape> topWalls;
    vector<RectangleShape> bottomWalls;

    for (int x = 0; x < window.getSize().x; x += wallWidth) {
        RectangleShape Uwall(Vector2f(wallWidth, wallHeight));
        RectangleShape Dwall(Vector2f(wallWidth, wallHeight));
        Color uwall(128, 0, 0);
        Uwall.setFillColor(uwall);
        Uwall.setPosition(x, 0);
        topWalls.push_back(Uwall);

        Dwall.setPosition(x, window.getSize().y - wallHeight);
        Color dwall(128, 0, 128);
        Dwall.setFillColor(dwall);
        bottomWalls.push_back(Dwall);
    }

    // Function to reset the ball
    float x = 3;
    float y = 3;
    auto resetBall = [&]() {
        ball.setPosition(Vector2f(400, 200));
        if (p1WonLastRound) {
            ballVelocity = Vector2f(-x, -y); // Ball moves towards p1
        }

        else if (p2WonLastRound) {
            ballVelocity = Vector2f(x, -y);  // Ball moves towards p2

        }
        else if (aiWonLastRound) {
            ballVelocity = Vector2f(x, -y);  // Ball moves towards p2

        }
        else {
            ballVelocity = Vector2f(x, y);  // Default direction
        }
        p1WonLastRound = false;
        p2WonLastRound = false;
        aiWonLastRound = false;
        };

    // Reset the ball at the start
    resetBall();

    //==============================================================================
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        dt = clock.restart().asSeconds();
        if (gameClock.getElapsedTime().asSeconds() >= 1.0f) {
            time--;
            updateTimer();
            gameClock.restart();
        }
        //==================================UPDATE=====================================
        //if 2 players
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            p1.getShape().move(0, -10 * dt * dtMult);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            p1.getShape().move(0, 10 * dt * dtMult);
        }
        if (isSinglePlayer) {
            // AI movement
            if (ball.getPosition().y < ai.getShape().getPosition().y) {
                ai.getShape().move(0, -12 * dt * dtMult);
            }
            else if (ball.getPosition().y > ai.getShape().getPosition().y + ai.getShape().getGlobalBounds().height) {
                ai.getShape().move(0, 12 * dt * dtMult);
            }
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                p2.getShape().move(0, -10 * dt * dtMult);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                p2.getShape().move(0, 10 * dt * dtMult);
            }
        }

        // Player 1 collision with walls
        if (p1.getShape().getPosition().y < wallHeight) {
            p1.getShape().setPosition(p1.getShape().getPosition().x, wallHeight);
        }

        if (p1.getShape().getPosition().y > window.getSize().y - p1.getShape().getGlobalBounds().height - wallHeight) {
            p1.getShape().setPosition(p1.getShape().getPosition().x, window.getSize().y - p1.getShape().getGlobalBounds().height - wallHeight);
        }
        if (!isSinglePlayer) {
            // Player 2 collision with walls
            if (p2.getShape().getPosition().y < wallHeight) {
                p2.getShape().setPosition(p2.getShape().getPosition().x, wallHeight);
            }
            if (p2.getShape().getPosition().y > window.getSize().y - p2.getShape().getGlobalBounds().height - wallHeight) {
                p2.getShape().setPosition(p2.getShape().getPosition().x, window.getSize().y - p2.getShape().getGlobalBounds().height - wallHeight);
            }
        }
        else {
            if (ai.getShape().getPosition().y < wallHeight) {
                ai.getShape().setPosition(ai.getShape().getPosition().x, wallHeight);
            }
            if (ai.getShape().getPosition().y > window.getSize().y - ai.getShape().getGlobalBounds().height - wallHeight) {
                ai.getShape().setPosition(ai.getShape().getPosition().x, window.getSize().y - ai.getShape().getGlobalBounds().height - wallHeight);
            }
        }


        // Ball movement logic
        ball.move(ballVelocity * dt * dtMult);

        // Ball collision with top and bottom walls
        if (ball.getPosition().y < wallHeight || ball.getPosition().y > window.getSize().y - ball.getGlobalBounds().height - wallHeight) {
            ballVelocity.y = -ballVelocity.y;
        }

        // Ball collision with players
        auto handlePaddleCollision = [&](const RectangleShape& paddle) {
            FloatRect ballBounds = ball.getGlobalBounds();
            FloatRect paddleBounds = paddle.getGlobalBounds();

            // Check if there's an intersection
            if (ballBounds.intersects(paddleBounds)) {
                // Calculate the intersection area
                float overlapLeft = ballBounds.left + ballBounds.width - paddleBounds.left;
                float overlapRight = paddleBounds.left + paddleBounds.width - ballBounds.left;
                float overlapTop = ballBounds.top + ballBounds.height - paddleBounds.top;
                float overlapBottom = paddleBounds.top + paddleBounds.height - ballBounds.top;

                bool ballFromLeft = overlapLeft < overlapRight;
                bool ballFromTop = overlapTop < overlapBottom;

                float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
                float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

                // Adjust ball position and velocity based on the side of the collision
                if (minOverlapX < minOverlapY) {
                    ballVelocity.x = -ballVelocity.x;
                    ball.move(ballFromLeft ? -minOverlapX * dt * dtMult : minOverlapX * dt * dtMult, 0.f);
                }
                else {
                    ballVelocity.y = -ballVelocity.y;
                    ball.move(0.f, ballFromTop ? -minOverlapY * dt * dtMult : minOverlapY * dt * dtMult);
                }
                // Increase ball speed
                if (diff == "Hard" || !isSinglePlayer) {
                    ballVelocity.x *= 1.1f;
                    ballVelocity.y *= 1.1f;
                }

            }
            };

        if (isSinglePlayer) {
            handlePaddleCollision(p1.getShape());
            handlePaddleCollision(ai.getShape());
        }
        else {
            handlePaddleCollision(p1.getShape());
            handlePaddleCollision(p2.getShape());
        }
        // Check if ball goes off screen (player wins)
        if (!isSinglePlayer) {
            if (ball.getPosition().x < 0) {
                p2WonLastRound = true;
                p2.increment_score();
                if (p2.getScore() == 10) {
                    GameOver.setString("Player 2 Won");
                    Finish(window, &GameOver);
                    break;
                }
                updateScoreText2();
                updateTimer();
                resetBall();
            }

            if (ball.getPosition().x > window.getSize().x) {
                p1WonLastRound = true;
                p1.increment_score();
                if (p1.getScore() == 10) {
                    GameOver.setString("Player 1 Won");
                    Finish(window, &GameOver);
                    break;
                }
                updateScoreText();
                updateTimer();
                resetBall();
            }
        }
        else {
            if (ball.getPosition().x < 0) {
                aiWonLastRound = true;
                ai.increment_score();
                if (ai.getScore() == 10) {
                    GameOver.setString("AI Won");
                    Finish(window, &GameOver);
                    break;
                }
                updateAiScoreText();
                updateTimer();
                resetBall();
            }

            if (ball.getPosition().x > window.getSize().x) {
                p1WonLastRound = true;
                p1.increment_score();
                if (p1.getScore() == 10) {

                    GameOver.setString("Player 1 Won");
                    Finish(window, &GameOver);
                }
                updateScoreText();
                updateTimer();
                resetBall();
            }
        }

        window.clear();
        //===================================DRAW==============================

        window.draw(background);
        if (isSinglePlayer) {
            window.draw(p1.getShape());
            window.draw(ai.getShape());
            window.draw(score);
            window.draw(aiScore);
            window.draw(timer);
        }
        else {
            window.draw(p1.getShape());
            window.draw(p2.getShape());
            window.draw(score);
            window.draw(secondScore);
            window.draw(timer);
        }
        window.draw(ball);

        // Draw top and bottom walls
        for (const auto& wall : topWalls) {
            window.draw(wall);
        }

        for (const auto& wall : bottomWalls) {
            window.draw(wall);
        }
        RectangleShape rectangle(Vector2f(3.f, 580.f));
        rectangle.setOutlineColor(Color::Red);
        Vector2u windowSize = window.getSize();
        Vector2f rectSize = rectangle.getSize();
        rectangle.setPosition(
            (windowSize.x - rectSize.x) / 2,
            (windowSize.y - rectSize.y) / 2
        );

        window.draw(rectangle);

        window.display();
        if (time <= 0) {
            if (p1.getScore() > p2.getScore() || p1.getScore() > ai.getScore()) {
                GameOver.setString("Player 1 Wins");
            }
            else if (p2.getScore() > p1.getScore()) {
                GameOver.setString("Player 2 Wins");
            }
            else if (ai.getScore() > p1.getScore()) {
                GameOver.setString("AI Wins");
            }
            else {
                GameOver.setString("It's a Draw");
            }
            Finish(window, &GameOver);
            break;
        }
    }
}
