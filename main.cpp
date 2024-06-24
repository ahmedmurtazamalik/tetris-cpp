// AHMED MURTAZA MALIK		i220985		PROJECT

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>
using namespace sf;

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Music music;
    if (!music.openFromFile("img/bonetrousle.wav"))
    {
        std::cout << "ERROR" << std::endl;
    }
    music.play();

    Font funk;
    funk.loadFromFile("img/funk.ttf");

    Text gameover;
    gameover.setFont(funk);
    gameover.setString("Game Over!");
    gameover.setPosition(50, 220);
    gameover.setFillColor(Color::Red);
    gameover.setCharacterSize(50);

    Text scoreText;
    scoreText.setFont(funk);
    scoreText.setPosition(130, 420);
    scoreText.setFillColor(Color::Green);
    scoreText.setCharacterSize(40);

    Text menuTitle;
    menuTitle.setFont(funk);
    menuTitle.setString("~~TETRIS~~");
    menuTitle.setPosition(50, 50);
    menuTitle.setFillColor(Color::Red);
    menuTitle.setCharacterSize(50);

    Text menuOption1;
    menuOption1.setFont(funk);
    menuOption1.setString("1. Play Game.");
    menuOption1.setPosition(95, 180);
    menuOption1.setFillColor(Color::Cyan);
    menuOption1.setCharacterSize(30);

    Text menuOption2;
    menuOption2.setFont(funk);
    menuOption2.setString("2. High Score.");
    menuOption2.setPosition(85, 260);
    menuOption2.setFillColor(Color::Red);
    menuOption2.setCharacterSize(30);

    Text menuOption3;
    menuOption3.setFont(funk);
    menuOption3.setString("3. Exit Game.");
    menuOption3.setPosition(95, 340);
    menuOption3.setFillColor(Color::Red);
    menuOption3.setCharacterSize(30);

    Texture obj1, obj2, obj3;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");

    Sprite sprite(obj1), background(obj2), frame(obj3);
    int delta_x = 0, colorNum = 1, currentBlock = -1;
    float timer = 0, delay = 0.3;
    bool rotate = 0;
    int score = 0;
    bool isMenuScreen = true;
    int currentMenuOption = 1;
    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                                // Event is occurring - until the game is in running state
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // Opened window disposes
            if (e.type == Event::KeyPressed)
            { // If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Escape)
                {
                    if (isMenuScreen)
                    {
                        window.close();
                    }
                    else
                    {
                        sprite = Sprite(obj1);
                        background = Sprite(obj2);
                        frame = Sprite(obj3);
                        delta_x = 0;
                        colorNum = 1;
                        currentBlock = -1;
                        timer = 0;
                        delay = 0.3;
                        rotate = 0;
                        score = 0;
                        isMenuScreen = true;
                        currentMenuOption = 1;
                        clock = Clock();
                        for (int i = 0; i < M; i++)
                        {
                            for (int j = 0; j < N; j++)
                            {
                                gameGrid[i][j] = 0;
                            }
                        }
                        for (int i = 0; i < 4; i++)
                        {
                            point_1[i][0] = 0;
                            point_1[i][1] = 0;
                            point_2[i][0] = 0;
                            point_2[i][1] = 0;
                            shadowPoint[i][0] = 0;
                            shadowPoint[i][1] = 0;
                        }
                    }
                }
                if (e.key.code == Keyboard::Up)
                {
                    if (!isMenuScreen) // during game
                    {
                        rotate = true;
                    }
                    else // during menu screen
                    {
                        if (currentMenuOption == 1)
                        {
                            currentMenuOption = 3;
                        }
                        else
                        {
                            currentMenuOption--;
                        }
                    }
                }
                else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                    delta_x = -1;                       // Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                    delta_x = 1;                        // Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)
                    spacebarDown(currentBlock);
                else if (e.key.code == Keyboard::Down)
                {
                    if (isMenuScreen) // during menu
                    {
                        if (currentMenuOption == 3)
                        {
                            currentMenuOption = 1;
                        }
                        else
                        {
                            currentMenuOption++;
                        }
                    }
                }
                else if (e.key.code == Keyboard::Enter)
                {
                    if (isMenuScreen)
                    {
                        if (currentMenuOption == 1)
                        {
                            isMenuScreen = false;
                        }
                        else if (currentMenuOption == 2)
                        {
                        }
                        else if (currentMenuOption == 3)
                        {
                            window.close();
                        }
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (!isMenuScreen) // during game
            {
                // Just another way to detect key presses without event listener
                delay = 0.05; // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
            }
        }

        if (isMenuScreen)
        {
            window.clear(Color::Black);

            if (currentMenuOption == 1)
            {
                menuOption1.setFillColor(Color::Cyan);
                menuOption2.setFillColor(Color::Red);
                menuOption3.setFillColor(Color::Red);
            }
            if (currentMenuOption == 2)
            {
                menuOption1.setFillColor(Color::Red);
                menuOption2.setFillColor(Color::Cyan);
                menuOption3.setFillColor(Color::Red);
            }
            if (currentMenuOption == 3)
            {
                menuOption1.setFillColor(Color::Red);
                menuOption2.setFillColor(Color::Red);
                menuOption3.setFillColor(Color::Cyan);
            }
            window.draw(menuTitle);
            window.draw(menuOption1);
            window.draw(menuOption2);
            window.draw(menuOption3);
        }

        if (isMenuScreen == false)
        {

            ///////////////////////////////////////////////
            ///*** START CALLING YOUR FUNCTIONS HERE ***///

            fallingPiece(timer, delay, colorNum, delta_x, currentBlock, score); // Example: fallingPiece() function is called here
            rotation(rotate);
            setShadowPoint(currentBlock); // setting the coordinates for shadowPoint
            scoreText.setString("Score: " + to_string(score));

            ///*** YOUR CALLING STATEMENTS END HERE ***///
            //////////////////////////////////////////////

            window.clear(Color::Black);
            window.draw(background);
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (gameGrid[i][j] == 0)
                    {
                        continue;
                    }
                    sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                    sprite.setPosition(j * 18, i * 18);
                    sprite.setColor(Color(255, 255, 255, 255));
                    sprite.move(28, 31); // offset
                    window.draw(sprite);
                }
            }
            for (int i = 0; i < 4; i++)
            {
                sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                sprite.setColor(Color(255, 255, 255, 255));
                sprite.move(28, 31);
                window.draw(sprite);
            }
            // draw the shadow sprite
            for (int i = 0; i < 4; i++)
            {
                sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                sprite.setPosition(shadowPoint[i][0] * 18, shadowPoint[i][1] * 18);
                sprite.setColor(Color(255, 255, 255, 20));
                sprite.move(28, 31);
                window.draw(sprite);
            }
            //---The Final on Which Everything is Drawn Over is Loaded---//
            window.draw(scoreText);
            window.draw(frame);
            //      window.draw(gameover);
        }

        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
