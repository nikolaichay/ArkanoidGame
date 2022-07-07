#include "Brick.h"
#include "FunctionsAndConst.h"
using namespace std;
using namespace sf;
Brick::Brick(const Vector2f& size, const Vector2f& pos, int _health,
	TYPE _type, Color c) {
	setSize(size);
	setFillColor(c);
	setOutlineColor(Color::Black);
	setOutlineThickness(0.5f);
	setPosition(pos);
	move_dir = -1;
	health = _health;
	type = _type;
}
int Brick::GetType() { 
	return int(type);
}

int Brick::ReduceHealth() {
	health--;
	if (health == 0) {
		setFillColor(Color::White);
	}
	if (health == MAX_HEALTH - 1) {
		setFillColor(Color::Yellow);
	}
	else if (health == MAX_HEALTH - 2) {
		setFillColor(Color::Red);
	}
	return health;
}
void MovingBrick::Move() {
	if (getPosition().x <= 0 || getPosition().x + getSize().x >= windowWidth)
		SetDirection(-1*GetDirection());
	Vector2f sp = { speed * GetDirection(),0 };
	move(sp);
}