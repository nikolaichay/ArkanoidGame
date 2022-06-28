#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
constexpr double RadiusBall{ 10.f }; constexpr double ball_vel_x{ 6.f }; constexpr double ball_vel_y{ 8.f };
class Platform;
class Brick;
class Ball : public CircleShape {
private:
	Vector2f vel{ 0, 0 };
public:
	Ball(double x, double y);
	double getX();
	double getY();
	double isLeft();
	double isRight();
	double isTop();
	double isBot();
	void ReflectPlatform(Platform* platform);
	bool ReflectBrick(const Brick& brick);
	void ReflectWall();
	void update();
	void Draw(shared_ptr<RenderWindow> window);
};