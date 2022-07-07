#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
constexpr int windowWidth{ 800 }, windowHeight{ 600 };
enum side { none = 0, top = 1, bot = 2, left = 4, right = 8 };
int sideIntersect(sf::FloatRect first, sf::FloatRect second);