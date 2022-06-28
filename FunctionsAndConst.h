#pragma once
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
enum side { none = 0, top = 1, bot = 2, left = 4, right = 8 };
constexpr int windowWidth{ 800 }, windowHeight{ 600 };
const Vector2u FIELD_SIZE = { 6U, 4U };
int sideIntersect(sf::FloatRect first, sf::FloatRect second);