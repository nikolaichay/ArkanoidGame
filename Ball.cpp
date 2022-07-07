#include "Ball.h"
#include "Game.h"

const int RANDOM_REFLECT_CHANCE = 20;
using namespace std;
using namespace sf;
Ball::Ball(double x, double y) {
	setPosition(x, y);
	setRadius(RadiusBall);
	setFillColor(Color::White);
	setOrigin(RadiusBall, RadiusBall);
	vel.x = -ball_vel_x;
	vel.y = -ball_vel_y;
	stickPlatform = false;
	reflcectBot = false;
	reflectRandom = false;
}
double Ball::getX() {
	return getPosition().x;
}
double Ball::getY() {
	return getPosition().y;
}
double Ball::isLeft() {
	return getX() - getRadius();
}
double Ball::isRight() {
	return getX() + getRadius();
}
double Ball::isTop() {
	return getY() - getRadius();
}
double Ball::isBot() {
	return getY() + getRadius();
}

void Ball::ReflectPlatform(std::shared_ptr<Platform> platform) {
	auto ballPos = getPosition();
	auto bounds = platform->getGlobalBounds();
	int sides = sideIntersect(bounds, getGlobalBounds());
	if (sides & side::left) {
		ballPos.x = bounds.left - (ballPos.x + 2 * getRadius() - bounds.left);
		vel.x = -vel.x;
	}
	if (sides & side::top) {
		ballPos.y = bounds.top - (ballPos.y + 2 * getRadius() - bounds.top);
		vel.y = -vel.y;
		if (platform->IsStickBall()) {
			stickPlatform = true;
			platform->SetStickBall(false);
			platform->setFillColor(Color::Blue);
			setPosition(ballPos.x, ballPos.y);
		}
	}
	if (sides & side::right) {
		ballPos.x = bounds.left + bounds.width - (ballPos.x - bounds.left - bounds.width);
		vel.x = -vel.x;
	}
}
void Ball::ReflectWall() {
	if (isLeft() < 0) {
		vel.x = -1 * vel.x;
	}
	else if (isRight() > windowWidth) {
		vel.x = -1 * vel.x;
	}
	if (isTop() < 0) {
		vel.y = -1 * vel.y;
	}
	else if (isBot() > windowHeight) {
		vel.y = -1 * vel.y;
	}

}

bool Ball::ReflectBrick(const Brick& brick) {
	bool isHit = false;
	auto ballPos = this->getPosition();
	auto brickPos = brick.getPosition();
	auto rad = this->getRadius();
	auto brickSize = brick.getSize();

	double max_dist = sqrt(vel.y * vel.y + vel.x * vel.x);

	auto bounds = brick.getGlobalBounds();
	int sides = sideIntersect(bounds, getGlobalBounds());
	if (sides & side::left) {
		ballPos.x = bounds.left - (ballPos.x + 2 * getRadius() - bounds.left);
		vel.x = -vel.x;
		isHit = true;
	}
	if (sides & side::top) {
		ballPos.y = bounds.top - (ballPos.y + 2 * getRadius() - bounds.top);
		vel.y = -vel.y;
		isHit = true;
	}
	if (sides & side::right) {
		ballPos.x = bounds.left + bounds.width - (ballPos.x - bounds.left - bounds.width);
		vel.x = -vel.x;
		isHit = true;
	}
	if (sides & side::bot) {
		ballPos.y = bounds.top + bounds.height - (ballPos.y - bounds.top - bounds.height);
		vel.y = -vel.y;
		isHit = true;
	}
	return isHit;
}

void Ball::MovingWith() {
	auto x = getPosition().x;

	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		if (x >= 0)
			move({ -PlatformVel, 0 });
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		if (x + 2 * getRadius() <= windowWidth)
			move({ PlatformVel, 0 });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		setFillColor(sf::Color::White);
		stickPlatform = false;
	}
}

void Ball::Move() {
	if (stickPlatform) {
		MovingWith();
	}
	else {
		if (reflectRandom) {
			int tmp = rand() % 100;
			if (tmp < RANDOM_REFLECT_CHANCE) {
				RandomlyReflect();
				SetRandomReflect(false);
				setFillColor(Color::White);
			}
		}
		move(vel);
	}
	ReflectWall();
}

void Ball::Draw(shared_ptr <RenderWindow> window) {
	window->draw(*this);
}
void Ball::SetReflectBot(bool t) {
	reflcectBot = t;
}
void Ball::SetRandomReflect(bool t) {
	reflectRandom = t;
}
Vector2f Ball::GetSpeed() {
	return vel;
}
void Ball::ChangeSpeed(Vector2f newSpeed) {
	vel = newSpeed;
}
void Ball::IncreaseSpeed(Vector2f accl) {
	if ((vel.x > accl.x && vel.y > accl.y) ||(
		accl.x > 0 && accl.y > 0)) {
		vel += accl;
	}
}
void Ball::RandomlyReflect() {
	if ((rand() % 100) < RANDOM_REFLECT_CHANCE) {
		if (rand() % 2)
			vel.y *= -1;
		else
			vel.x *= -1;
	}
}
bool Ball::ReflectBot() {
	return reflcectBot;
}