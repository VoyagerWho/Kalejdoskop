#ifndef EXTRAFUNCTIONS_H_INCLUDED
#define EXTRAFUNCTIONS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

void drawLine(sf::RenderWindow& window, std::vector<sf::Vector2f>& points, sf::Color color = sf::Color(255,255,255));
void drawLine(sf::RenderWindow& window, sf::Vector2f p1, sf::Vector2f p2, sf::Color color = sf::Color(255,255,255));
float lengthVector2(const sf::Vector2f& vec);
sf::Vector2f lineMovement(const sf::Vector2f& moveVector, const float& dist);
int mapValue(int value, float percent);
double dist2D(const sf::Vector2f& pos1, const sf::Vector2f& pos2);

#endif // EXTRAFUNCTIONS_H_INCLUDED
