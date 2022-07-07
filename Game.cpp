#include "Game.h"


using namespace sf;



void Game::ShowScore() {
	Text text;
	auto window_size = window->getSize();
	text.setFont(scoreFont);
	text.setString("Score: " + std::to_string(score));
	text.setCharacterSize((unsigned)(score_size.x + score_size.y) / 10);
	text.setStyle(sf::Text::Bold);
	text.setPosition(0.1f * window_size.x, 0.9f * window_size.y);
	window->draw(text);
}


bool Game::CheckGameOver() {
	if (field->CheckGameEnd()) {
		window->clear();
		ShowScore();

		sf::Text text;
		auto window_size = window->getSize();
		text.setPosition(0.3f * window_size.x, 0.5f * window_size.y);
		text.setFont(scoreFont);
		text.setFillColor(sf::Color::Red);
		text.setString("GAME OVER. Press space to exit");
		text.setStyle(sf::Text::Bold);


		window->draw(text);

		window->display();

		return true;
	}
	return false;
}

void Game::Start() {
	while (window->isOpen()) {

		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (CheckGameOver())
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				break;
			}
			else
				continue;
		window->clear();
		CheckBallFellDown();
		MoveAll();
		ReflectAll();
		DrawAll();
		window->display();
	}

}

void Game::BallReflectBlocks() {
	std::vector<std::shared_ptr<Brick>> grid = field->GetGrid();
	int i = 0;
	for (auto brick : grid) {

		if (ball->ReflectBrick(*brick)) {

			auto brickType = brick->GetType();
			if (brickType != TYPE::INDESTRUCTABLE) {
				score++;
			}
			if (brickType == TYPE::SPEED_UP) {
				Vector2f acc = brick->GetSpeedIncrement();
				ball->IncreaseSpeed(acc);
			}
			if (brickType == TYPE::HAS_BONUS) {
				auto brick_p = brick->getPosition();
				auto brick_s = brick->getSize();
				float bonus_x = brick_p.x + 0.5f * brick_s.x;
				float bonus_y = brick_p.y + 0.5f * brick_s.y;

				bonuses->AddRandomBonus({ bonus_x,bonus_y });
			}
			field->ReduceHealthField(i);
			;
			break;
		}

		i++;
	}
}


void Game::DrawAll() {
	field->Draw(window);
	platform->Draw(window);
	ball->Draw(window);
	bonuses->DrawBonuses(window);
	ShowScore();
}



void Game::CheckBallFellDown() {

	if (((ball->isBot()) - windowHeight < 0))
		return;
	else {
		if (!ball->ReflectBot())
			score--;
		else {
			ball->SetReflectBot(false);
			ball->setFillColor(Color::White);
		}
	}

}

void Game::MoveAll() {

	ball->Move();
	bonuses->MoveAll(platform, field, ball);
	platform->Move();
	field->MoveMovingBlocks();

}

void Game::ReflectAll() {
	ball->ReflectPlatform(platform);
	BallReflectBlocks();
	field->CheckCollisionsBetweenBlocks();

}

void Game::InitObjects() {
	Vector2f window_size = { windowWidth,windowHeight };
	Vector2f block_size = { (float)(window_size.x-100) / FIELD_SIZE.x,
							   0.3f * (window_size.y-15) / FIELD_SIZE.y };
	Vector2f field_top_coord = { 0, 15 };
	Vector2f size_field = { windowWidth - 100, windowHeight - 15 };
	field = std::make_shared <Field>
		(field_top_coord, FIELD_SIZE, size_field, block_size);


	Vector2f platform_size = { PlatformWidth, PlatformHeight };
	Vector2f platform_start_pos = { 0.5f * window_size.x, (float)(window_size.y - PlatformHeight / 2) };

	platform = std::make_shared <Platform>(platform_start_pos.x, platform_start_pos.y);


	float ball_radius = RadiusBall;
	Vector2f ball_start_pos = { platform_start_pos.x + platform_size.x / 2 - ball_radius / 2,
							  platform_start_pos.y - 3 * ball_radius };
	ball = std::make_shared <Ball>(ball_start_pos.x, ball_start_pos.y);

	bonuses = std::make_shared<BonusManager>();
}

Game::Game() {
	Vector2f window_size = { windowWidth,windowHeight };
	window = std::make_shared <sf::RenderWindow>
		(sf::VideoMode(window_size.x, window_size.y), "Arkanoid");
	window->setFramerateLimit(60);
	scoreFont.loadFromFile("arial.ttf");
	score_size = { window_size.x * 0.3f, window_size.y * 0.1f };
	score = 0;
	InitObjects();


}