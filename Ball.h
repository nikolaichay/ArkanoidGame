#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
const double RadiusBall = 7.f ; const double ball_vel_x = 5.f; const double ball_vel_y = 7.f ;
class Platform;
class Brick;
class Ball : public sf::CircleShape {
private:
	sf::Vector2f vel{ 0, 0 };
	bool stickPlatform;
	bool reflcectBot;
	bool reflectRandom;
public:
	Ball(double x, double y);
	double getX();
	double getY();
	double isLeft();
	double isRight();
	double isTop();
	double isBot();
	void ReflectPlatform(std::shared_ptr<Platform> platform);
	bool ReflectBrick(const Brick& brick);
	sf::Vector2f GetSpeed();
	void ChangeSpeed(sf::Vector2f newSpeed);
	void IncreaseSpeed(sf::Vector2f accl);
	void SetReflectBot(bool t);
	void SetRandomReflect(bool t);
	void ReflectWall();
	void MovingWith();
	void Move();
	void Draw(std::shared_ptr<sf::RenderWindow> window);
	void RandomlyReflect();
	bool ReflectBot();
};