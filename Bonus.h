#pragma once
#include "FunctionsAndConst.h"
class Platform;
class Field;
class Ball;
enum type {
    SPEED_UP_B = 0,
    SPEED_DOWN = 1,
    SHIELD = 2,
    SIZE_UP = 3,
    SIZE_DOWN = 4,
    STICKY = 5,
    RANDOMIZER = 6,
    BALL_UP = 7
};
const int NumOfBonus = 6;
const double DefaultRadius = 5.f;
class Bonus : public sf::CircleShape
{
private:
	float speed;
	sf::Vector2f size;
private:
	const static float DEFAULT_BONUS_SPEED;
	const static int BONUS_SPAWN_CHANCE;
public:
	const static int BONUS_TYPES;
public:
	Bonus(double x, double y, double rad, sf::Color color)
	{
	setPosition(x, y);
	setRadius(rad);
	setFillColor(color);
	setOrigin(rad, rad);
	speed = DEFAULT_BONUS_SPEED;
	};

	void Move() { move({ 0,speed }); };
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball) = 0;
	bool IsContactedWithPlatform(const Platform& Platform) const;
	void Draw(std::shared_ptr<sf::RenderWindow> window) { window->draw(*this); };
};
class PlatformChangeBonus : public Bonus {
private:
	float size_multiplier;
private:
	const static float DEFAULT_SIZE_MULTIPLIER;
public:
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);
	void SetSizeMultiplier(float size_multiplier) { size_multiplier = size_multiplier; }
	PlatformChangeBonus(sf::Vector2f pos) :
		Bonus(pos.x,pos.y,DefaultRadius,sf::Color::Red),
		size_multiplier(DEFAULT_SIZE_MULTIPLIER) {};
};

class BallSpeedBonus : public Bonus {
private:
	float speed_multiplier;
private:
	const static float DEFAULT_SPEED_MULTIPLIER;
public:
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);
	void SetSpeedMultiplier(float multiplier) { speed_multiplier = multiplier; };
	BallSpeedBonus(sf::Vector2f pos) :
		Bonus(pos.x, pos.y, DefaultRadius, sf::Color::Red),
		speed_multiplier(DEFAULT_SPEED_MULTIPLIER) {};

};

class PlatformStickBonus : public Bonus {
public:
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);
	PlatformStickBonus(sf::Vector2f pos) :
		Bonus(pos.x, pos.y, DefaultRadius, sf::Color::Red) {};
};


class BotReflectBonus : public Bonus {
public:
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);
	BotReflectBonus(sf::Vector2f pos) :
		Bonus(pos.x, pos.y, DefaultRadius, sf::Color::Red) {};

};


class ChangeTrajectoryBonus : public Bonus {
public:
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);
	ChangeTrajectoryBonus(sf::Vector2f pos) :
		Bonus(pos.x, pos.y, DefaultRadius, sf::Color::Red) {};

};


class MovingBlockBonus : public Bonus {
public:
	virtual void Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);
	MovingBlockBonus(sf::Vector2f pos) :
		Bonus(pos.x, pos.y, DefaultRadius, sf::Color::Red) {};

};

