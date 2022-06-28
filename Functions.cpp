#include "FunctionsAndConst.h"
int sideIntersect(sf::FloatRect first, sf::FloatRect second) {
	sf::FloatRect cross;
	if (!first.intersects(second, cross)) {
		return side::none;
	}

	bool overlapT = cross.top == first.top;
	bool overlapB = cross.top + cross.height == first.top + first.height;
	bool overlapL = cross.left == first.left;
	bool overlapR = cross.left + cross.width == first.left + first.width;

	int ret = 0;
	if (overlapT) {
		ret += side::top;
	}
	if (overlapB) {
		ret += side::bot;
	}
	if (overlapL) {
		ret += side::left;
	}
	if (overlapR) {
		ret += side::right;
	}

	return ret;
}