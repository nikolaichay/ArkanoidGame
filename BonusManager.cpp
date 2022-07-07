#include "BonusManager.h"
#include "Field.h"
using namespace sf;
void BonusManager::DrawBonuses(std::shared_ptr<sf::RenderWindow> window) {
	for (const auto& b : bonuses)
		b->Draw(window);
}

void BonusManager::AddRandomBonus(const Vector2f& pos) {
	std::shared_ptr <Bonus> bonus;
	int tmp = rand();
	switch (tmp % NumOfBonus) {
	case 0:
		bonus = std::make_shared <PlatformChangeBonus>(pos);
		break;
	case 1:
		bonus = std::make_shared <BallSpeedBonus>(pos);
		break;
	case 2:
		bonus = std::make_shared <PlatformStickBonus>(pos);
		break;
	case 3:
		bonus = std::make_shared <BotReflectBonus>(pos);
		break;
	case 4:
		bonus = std::make_shared <ChangeTrajectoryBonus>(pos);
		break;
	case 5:
		bonus = std::make_shared <MovingBlockBonus>(pos);
		break;
	}
	bonuses.push_back(bonus);
}



void BonusManager::MoveAll(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball){
	int i = 0;
	for (auto& bonus : bonuses) {
		bonus->Move();

		// bonus is caught
		if (bonus->IsContactedWithPlatform(*platform)) {
			bonus->Activate(platform, field, ball);
			bonuses.erase(bonuses.begin() + i);
			break;
		}

		// bonus fell off
		if (bonus->getPosition().y >= windowHeight) {
			bonuses.erase(bonuses.begin() + i);
			break;
		}

		i++;
	}
}