#include "Ball.h"
#include "Platform.h"
#include "Brick.h"
#include <iostream>
#include "FunctionsAndConst.h"


class Field {
private:
	vector<shared_ptr<Brick>> grid;
	Vector2u size;
	Vector2f pos;
public:
	Field(const sf::Vector2f& top, const sf::Vector2u& _size,
		const sf::Vector2f& window_size, const sf::Vector2f& brick_size) {
		size = _size;
		pos = top;
		float x = pos.x;
		float y = pos.y;
		for(int i=0;i<size.y;++i){
			for (int j = 0; j < size.x; ++j) {
				shared_ptr <Brick> brick;
				Vector2f cur_pos = { x,y };
				int type = rand() % 2;
				if (type == 0) {
					brick = make_shared<IndestructableBrick>(IndestructableBrick(brick_size, cur_pos));
				}
				else {
					brick = make_shared<Brick>(Brick(brick_size, cur_pos));
				}
				grid.push_back(brick);
				x += (brick_size.x);
			}
			y += (brick_size.y);
			x = top.x;
		}
	}
	Vector2u GetSize() const { return size; };
	void Draw(shared_ptr<RenderWindow> window) {
		for (const auto& block : grid) {
			window->draw(*block);
		}
	}
	void MoveMovingBlocks();
	void AddMovingBlock();
	void ReduceHealth(unsigned pos) {
		int health_left = grid[pos]->ReduceHealth();
		if (health_left == 0) {
			grid.erase(grid.begin() + pos);
			//cout << grid.size() << endl;
		}
	}
	// check if x,y is free for spawning new moving block
	bool CheckXForNewMoving(float x, float y);
	void CheckCollisionsBetweenBlocks();
	int NumMovingBlocks() const;
	std::vector<std::shared_ptr<Brick>> GetGrid() { return grid; };
	bool CheckGameEnd() const;
};

void DrawAll() {

}

void ReflectAll(Field* field,Ball* ball) {
	std::vector<std::shared_ptr<Brick>> grid = field->GetGrid();
	int i = 0;
	for (auto block : grid) {

		if (ball->ReflectBrick(*block)) {

			auto blockType = block->GetType();

			if (blockType != TYPE::INDESTRUCTABLE)

			field->ReduceHealth(i);

			break;
		}

		i++;
	}
}

int main()
{
	shared_ptr <RenderWindow> window;
	window = make_shared <RenderWindow>
	(VideoMode(windowWidth, windowHeight), "Arkanoid");
	Ball ball(400, 300);
	Platform platform(400, windowHeight-15/2);
	window->setFramerateLimit(60);
	Vector2f brick_size = { (float)800 / FIELD_SIZE.x,
							   0.3f * 600 / FIELD_SIZE.y };
	Vector2f field_top_coord = { 0, 10 };
	Field field(field_top_coord, FIELD_SIZE, {800,600}, brick_size);
	while (true)
	{
		window->clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
		ball.ReflectPlatform(&platform);
		ball.update();
		platform.update();
		ReflectAll(&field, &ball);
		ball.Draw(window);
		platform.Draw(window);
		field.Draw(window);
		window->display();
	}

	return 0;
}