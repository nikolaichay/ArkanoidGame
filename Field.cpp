#include "Field.h"
#include "Brick.cpp"
using namespace std;
using namespace sf;

Field::Field(const sf::Vector2f& top, const sf::Vector2u& _size,
	const sf::Vector2f& window_size, const sf::Vector2f& brick_size) {
	size = _size;
	pos = top;
	float x = pos.x + 50;
	float y = pos.y;
	for (int i = 0; i < size.y; ++i) {
		for (int j = 0; j < size.x; ++j) {
			shared_ptr <Brick> brick;
			Vector2f cur_pos = { x,y };
			int type = rand() % 4;
			switch (type) {
			case 0:
				brick = make_shared<Brick>(Brick(brick_size, cur_pos));
				break;
			case 1:
				brick = make_shared<BonusedBrick>(BonusedBrick(brick_size, cur_pos));
				break;
			case 2:
				brick = make_shared<IndestructableBrick>(IndestructableBrick(brick_size, cur_pos));
				break;
			case 3:
				brick = make_shared<SpeedUpBrick>(SpeedUpBrick(brick_size, cur_pos));
				break;
			default:
				break;
			}
			grid.push_back(brick);
			x += (brick_size.x) + 1;
		}
		y += (brick_size.y) + 1;
		x = top.x + 50;
	}
}

bool Field::CheckXForNewMoving(float x, float y) {
	float size = grid[0]->getSize().x;

	for (auto block : grid) {
		if (block->getPosition().y == y &&
			(x + block->getSize().x > block->getPosition().x &&
				x < block->getPosition().x + block->getSize().x ||
				(x + block->getSize().x * 1.5f > windowWidth)))
			return false;



	}

	return true;
}
void Field::Draw(shared_ptr<RenderWindow> window) {
	for (const auto& brick : grid) {
		window->draw(*brick);
	}
}
void Field::CheckCollisionsBetweenBlocks() {
	for (auto& block1 : grid) {
		if (block1->GetType() != TYPE::MOVING)
			continue;
		float block1_left_x = block1->getPosition().x;
		float block1_right_x = block1_left_x + block1->getSize().x;
		float block1_top_y = block1->getPosition().y;
		auto block1_type = block1->GetType();

		for (auto& block2 : grid) {
			if (block2->GetType() != TYPE::MOVING)
				continue;

			float block2_left_x = block2->getPosition().x;
			float block2_right_x = block2_left_x + block2->getSize().x;
			float block2_top_y = block2->getPosition().y;
			auto block2_type = block2->GetType();

			bool collision_block1_left =
				fabs(block1_left_x - block2_right_x)
				<= DefaultSpeed;
			bool collision_block2_right =
				fabs(block1_right_x - block2_left_x)
				<= DefaultSpeed;
			bool same_y_pos = (block1_top_y == block2_top_y);
			if (collision_block1_left && same_y_pos)
				block1->SetDirection(1);
			else if (collision_block2_right && same_y_pos)
				block1->SetDirection(-1);
		}
	}
}
int Field::NumMovingBlocks() const {
	int i = 0;
	for (const auto& b : grid) {
		if (b->GetType() == TYPE::MOVING)
			i++;
	}
	return i;
}
bool Field::CheckGameEnd() const {
	for (const auto& block : grid) {
		if (block->GetType() != TYPE::INDESTRUCTABLE)
			return false;
	}
	return true;
}
void Field::MoveMovingBlocks() {
	for (auto& block : grid)
		block->Move();
}
void Field::AddMovingBlock() {
	float block_width = grid[0]->getSize().x;
	float block_height = grid[0]->getSize().y;
	float x_pos;
	int num_free_line = NumMovingBlocks() % size.x;
	float y_pos = Field::pos.y + 1.05f * (num_free_line + size.y) * block_height;

	do
		x_pos = (float)(rand() % (int)(windowWidth - block_width));
	while (!CheckXForNewMoving(x_pos, y_pos));
	auto block = make_shared <MovingBrick>
		(Vector2f(block_width, block_height), Vector2f(x_pos, y_pos));
	grid.push_back(block);
}
void Field::ReduceHealthField(unsigned pos) {
	int health_left = grid[pos]->ReduceHealth();
	if (health_left == 0) {
		grid.erase(grid.begin() + pos);
	}
}
