#include "Brick.h"
#include "FunctionsAndConst.h"
Brick::Brick(const Vector2f& size, const Vector2f& pos,
	enum class TYPE type, Color c) {
	setSize(size);
	setFillColor(c);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(0.5f);
	setPosition(pos);
	move_dir = -1;
	health = MAX_HEALTH;
	type = type;
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
