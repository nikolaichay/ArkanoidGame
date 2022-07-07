#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "FunctionsAndConst.h"
#include "Brick.h"
const sf::Vector2u FIELD_SIZE = { 8U, 6U };
class Field {
private:
	std::vector<std::shared_ptr<Brick>> grid;
	sf::Vector2u size;
	sf::Vector2f pos;
public:
	Field(const sf::Vector2f& top, const sf::Vector2u& _size,
		const sf::Vector2f& window_size, const sf::Vector2f& brick_size);
	sf::Vector2u GetSize() const { return size; };
	void Draw(std::shared_ptr<sf::RenderWindow> window);
	void MoveMovingBlocks();
	void AddMovingBlock();
	void ReduceHealthField(unsigned pos);
	bool CheckXForNewMoving(float x, float y);
	void CheckCollisionsBetweenBlocks();
	int NumMovingBlocks() const;
	std::vector<std::shared_ptr<Brick>> GetGrid() { return grid; };
	bool CheckGameEnd() const;
};