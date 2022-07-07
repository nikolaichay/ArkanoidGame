#include "Bonus.h"
#include "Game.h"
using namespace std;
using namespace sf;
const float Bonus::DEFAULT_BONUS_SPEED = 1.f;
const int Bonus::BONUS_SPAWN_CHANCE = 10;
const float PlatformChangeBonus::DEFAULT_SIZE_MULTIPLIER = 1.4f;
const float BallSpeedBonus::DEFAULT_SPEED_MULTIPLIER = 1.2f;

bool Bonus::IsContactedWithPlatform(const Platform& platform) const {
	auto bounds = platform.getGlobalBounds();
	bool isContacted = sideIntersect(bounds, getGlobalBounds());
	return isContacted;
}

void PlatformChangeBonus::Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball) {
	auto cur_size = platform->getSize();
	Vector2f new_size = { cur_size.x * size_multiplier, cur_size.y };
	platform->setSize(new_size);

}

void BallSpeedBonus::Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball) {

	auto cur_speed = ball->GetSpeed();
	Vector2f new_speed = { cur_speed.x * speed_multiplier,
						 cur_speed.y * speed_multiplier };
	ball->ChangeSpeed(new_speed);
}

void PlatformStickBonus::Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball) {
	platform->setFillColor(Color::Magenta);
	platform->SetStickBall(true);
}


void BotReflectBonus::Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball) {
	ball->SetReflectBot(true);
	ball->setFillColor(Color::Cyan);
}

void ChangeTrajectoryBonus::Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball) {
	ball->SetRandomReflect(true);
	ball->setFillColor(sf::Color::Red);
}

void MovingBlockBonus::Activate(std::shared_ptr <Platform> platform, std::shared_ptr <Field> field,
	std::shared_ptr <Ball> ball) {
	field->AddMovingBlock();
}

