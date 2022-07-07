#pragma once
#include "Bonus.h"
class BonusManager
{
private:
	std::vector <std::shared_ptr <Bonus>> bonuses;

public:
	BonusManager() {};
	~BonusManager() {};
	void DrawBonuses(std::shared_ptr<sf::RenderWindow> window);
	void AddRandomBonus(const sf::Vector2f& pos);
	void MoveAll(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
		std::shared_ptr <Ball> ball);

};