#include "Ball.h"
#include "Platform.h"
#include "Brick.h"
#include "FunctionsAndConst.h"
using namespace std;
using namespace sf;
Ball::Ball(double x, double y) {
	setPosition(x, y);
	setRadius(RadiusBall);
	setFillColor(Color::White);
	setOrigin(RadiusBall, RadiusBall);
	vel.x = ball_vel_x;
	vel.y = -ball_vel_y;
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

void Ball::ReflectPlatform(Platform* platform) {
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
	}
	if (sides & side::right) {
		ballPos.x = bounds.left + bounds.width - (ballPos.x - bounds.left - bounds.width);
		vel.x = -vel.x;
	}
	/*if (sides & side::bot) {
		ballPos.y = bounds.top + bounds.height - (ballPos.y - bounds.top - bounds.height);
		vel.y = -vel.y;
	}*/
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

	/*bool y_more_blocks_bot = fabs(ballPos.y - (brickPos.y + brickSize.y)) < max_dist;
	bool y_less_blocks_top = fabs(ballPos.y + 2 * rad - brickPos.y) < max_dist;
	bool x_more_blocks_left = fabs(ballPos.x + 2 * rad - brickPos.x) < max_dist;
	bool x_less_blocks_right = fabs(ballPos.x - (brickPos.x + brickSize.x)) < max_dist;

	bool y_more_blocks_bot_strict = ballPos.y > brickPos.y;
	bool y_less_blocks_top_strict = ballPos.y < brickPos.y + brickSize.y;
	bool x_more_blocks_left_strict = ballPos.x > brickPos.x;
	bool x_less_blocks_right_strict = ballPos.x < brickPos.x + brickSize.x;


	if (y_more_blocks_bot && x_more_blocks_left_strict &&
	x_less_blocks_right_strict) {
	vel.y *= -1;
	isHit = true;
	}

	else if (y_less_blocks_top && x_more_blocks_left_strict &&
	x_less_blocks_right_strict) {
	vel.y *= -1;
	isHit = true;
	}

	else if (x_more_blocks_left && y_more_blocks_bot_strict &&
	y_less_blocks_top_strict) {
	vel.x *= -1;
	isHit = true;
	}

	else if (x_less_blocks_right && y_more_blocks_bot_strict &&
	y_less_blocks_top_strict) {
	vel.x *= -1;
	isHit = true;
	}

	else if (x_less_blocks_right && y_more_blocks_bot) {
		vel.x *= -1;
		vel.y *= -1;
		isHit = true;
	}


	else if (x_less_blocks_right && y_less_blocks_top) {
		vel.x *= -1;
		vel.y *= -1;
		isHit = true;
	}

	else if (x_more_blocks_left && y_less_blocks_top) {
		vel.x *= -1;
		vel.y *= -1;
		isHit = true;
	}

	else if (x_more_blocks_left && y_more_blocks_bot) {
		vel.x *= -1;
		vel.y *= -1;
		isHit = true;
	}*/

	/*bool isTop = abs(ballPos.y - (brickPos.y + brickSize.y)) > vel.y;
	bool isBot = abs((ballPos.y + 2 * rad) - (brickPos.y)) < vel.y;
	bool isLeft = ballPos.x >= (brickPos.x + brickSize.x);
	bool isRight = (ballPos.x + 2 * rad) <= (brickPos.x);

	if (isLeft) {
		vel.x *= -1;
		isHit = true;
	}
	else if (isRight) {
		vel.x *= -1;
		isHit = true;
	}

	if (isTop) {
		vel.y *= -1;
		isHit = true;
	}
	else if (isBot) {
		vel.y *= -1;
		isHit = true;
	}*/
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

void Ball::update() {
	move(vel);
	ReflectWall();
}

void Ball::Draw(shared_ptr <RenderWindow> window) {
	window->draw(*this);
}