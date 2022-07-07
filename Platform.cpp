#include "Platform.h"
#include "FunctionsAndConst.h"
using namespace std;
using namespace sf;
Platform::Platform(double x, double y) {
	setPosition(x, y);
	setSize({ PlatformWidth, PlatformHeight });
	setFillColor(Color::Blue);
	setOrigin(PlatformWidth / 2, PlatformHeight / 2);
	stick_ball = false;
}
double Platform::getX() {
	return getPosition().x;
}
double Platform::getY() {
	return getPosition().y;
}
double Platform::isLeft() {
	return getX() - getSize().x / 2;
}
double Platform::isRight() {
	return getX() + getSize().x / 2;
}
double Platform::isTop() {
	return getY() - getSize().y / 2;
}
double Platform::isBot() {
	return getY() + getSize().y / 2;
}
void Platform::Move() {
	move(vel);
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && isLeft() > 0) {
		vel.x = -PlatformVel;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && isRight() < windowWidth) {
		vel.x = PlatformVel;
	}
	else {
		vel.x = 0;
	}
}
void Platform::Draw(shared_ptr <RenderWindow> window) {
	window->draw(*this);
}
void Platform::SetStickBall(bool t) {
	stick_ball = t;
}
bool Platform::IsStickBall() {
	return stick_ball;
}