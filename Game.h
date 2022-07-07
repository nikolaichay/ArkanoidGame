#pragma once
#include "Field.h"
#include "Platform.h"
#include "Ball.h"
#include "BonusManager.h"
#include "FunctionsAndConst.h"
class Game
{
private:
    int score;

    std::shared_ptr <sf::RenderWindow> window;
    std::shared_ptr <Field> field;
    std::shared_ptr <Platform> platform;
    std::shared_ptr <Ball> ball;
    std::shared_ptr <BonusManager> bonuses;

    sf::Font scoreFont;
    sf::Vector2f score_size;

private:

    void ShowScore();

    void ReflectAll(); // check reflections for all objects
    void BallReflectBlocks();
    void CheckBallFellDown();

    void MoveAll();
    void DrawAll();

    void InitObjects();
    bool CheckGameOver();
public:
    Game();
    ~Game() {};
    void Start();


};