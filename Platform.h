#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "FunctionsAndConst.h"

const double PlatformWidth = 100.f; const double PlatformHeight = 15.f; const double PlatformVel = 8.f;
class Platform : public sf::RectangleShape {
private:
	sf::Vector2f vel{ 0, 0 };
	bool stick_ball;
public:
	Platform(double x, double y);
	double getX();
	double getY();
	double isLeft();
	double isRight();
	double isTop();
	double isBot();
	void Move();
	void SetStickBall(bool t);
	bool IsStickBall();
	void Draw(std::shared_ptr <sf::RenderWindow> window);
};