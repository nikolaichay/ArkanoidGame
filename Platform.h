#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
constexpr double PlatformWidth{ 100.f }; constexpr double PlatformHeight{ 15.f }; constexpr double PlatformVel{ 8.f };
class Platform : public RectangleShape {
private:
	Vector2f vel{ 0, 0 };
public:
	Platform(double x, double y);
	double getX();
	double getY();
	double isLeft();
	double isRight();
	double isTop();
	double isBot();
	void update();
	void Draw(shared_ptr <RenderWindow> window);
};