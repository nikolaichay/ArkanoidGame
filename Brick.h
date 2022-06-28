#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;
enum class TYPE {
	NORMAL,
	INDESTRUCTABLE,
	SPEED_UP,
	HAS_BONUS,
	MOVING,
	DEFAULT
};


class Brick : public RectangleShape
{
private:
	int health;
	enum class TYPE type;
	int move_dir;
private:
	const int MAX_HEALTH = 3;
public:
	Brick(const Vector2f& size, const Vector2f& pos,
		enum class TYPE type = TYPE::NORMAL, Color c = Color::Green);
	virtual int ReduceHealth();
	int GetHealth() const { return health; };
	virtual ~Brick() {};
	virtual void Move() {};
	TYPE GetType() const { return type; };
	void SetDirection(int dir) { if (dir == 1 || dir == -1) move_dir = dir; };
	int GetDirection() const { return move_dir; };
	virtual sf::Vector2f GetSpeedIncrement() const { return { 0.f,0.f }; };
	void Draw(shared_ptr <RenderWindow> window);
};
class IndestructableBrick :	public Brick
{
public:
	IndestructableBrick(const sf::Vector2f& size, const sf::Vector2f& pos) :
		Brick(size, pos, TYPE::INDESTRUCTABLE, sf::Color::Magenta) {};
	virtual int ReduceHealth() { return -1; }
};