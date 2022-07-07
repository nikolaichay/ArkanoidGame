#pragma once
#include "SFML/Graphics.hpp"
enum TYPE {
	NORMAL = 0,
	INDESTRUCTABLE = 1,
	SPEED_UP = 2,
	HAS_BONUS = 3,
	MOVING = 4,
	DEFAULT = 5
};
const int MAX_HEALTH = 3;
const double DefaultSpeed = 1.f;
class Brick : public sf::RectangleShape
{
private:
	int health;
	TYPE type;
	int move_dir;
private:
	
public:
	Brick(const sf::Vector2f& size, const sf::Vector2f& pos, int _health = MAX_HEALTH,
		TYPE _type = TYPE::NORMAL, sf::Color c = sf::Color::Green);
	virtual int ReduceHealth();
	int GetHealth() const { return health; };
	virtual ~Brick() {};
	virtual void Move() {};
	int GetType();
	void SetDirection(int dir) { if (dir == 1 || dir == -1) move_dir = dir; };
	int GetDirection() const { return move_dir; };
	virtual sf::Vector2f GetSpeedIncrement() const { return { 0.f,0.f }; };
};
class IndestructableBrick :	public Brick
{
public:
	IndestructableBrick(const sf::Vector2f& size, const sf::Vector2f& pos) :
		Brick(size, pos, MAX_HEALTH, TYPE::INDESTRUCTABLE, sf::Color::Magenta) {};
	virtual int ReduceHealth() { return -1; }
};
class SpeedUpBrick :
	public Brick
{
private:
	sf::Vector2f speed_increment;
public:
	SpeedUpBrick(const sf::Vector2f& size, const sf::Vector2f& pos) :
		Brick(size, pos,MAX_HEALTH-2, TYPE::SPEED_UP,sf::Color::Cyan), speed_increment(1.f,1.f) {};
	~SpeedUpBrick() {};
	void SetSpeedIncrement(const sf::Vector2f& inc) { speed_increment = inc; }
	virtual sf::Vector2f GetSpeedIncrement() const { return speed_increment; }
};
class BonusedBrick : public Brick {
public:
	BonusedBrick(const sf::Vector2f& size, const sf::Vector2f& pos) :
		Brick(size, pos, 1, TYPE::HAS_BONUS, sf::Color::White) {};

	~BonusedBrick() {};
};
class MovingBrick : public Brick {
private:
	float speed;
public:
	MovingBrick(const sf::Vector2f& size, const sf::Vector2f& pos) :
		Brick(size, pos, MAX_HEALTH, TYPE::MOVING), speed(DefaultSpeed) {};
	virtual void Move();
};