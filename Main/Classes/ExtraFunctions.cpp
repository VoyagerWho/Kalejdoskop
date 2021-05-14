#include "ExtraFunctions.h"

void drawLine(sf::RenderWindow& window, std::vector<sf::Vector2f>& points, sf::Color color)
{
  int i = points.size();
  sf::Vertex* line = new sf::Vertex[i];
  int iCopy = i;
  while(i--)
  {
    line[i] = sf::Vertex(points[i], color);
  }
  window.draw(line, iCopy, sf::LineStrip);
  delete [] line;
}
void drawLine(sf::RenderWindow& window, sf::Vector2f p1, sf::Vector2f p2, sf::Color color)
{
  sf::Vertex line[] =
  {
      sf::Vertex(p1, color),
      sf::Vertex(p2, color)
  };

  window.draw(line, 2, sf::Lines);
}
float lengthVector2(const sf::Vector2f& vec)
{
  return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}
sf::Vector2f lineMovement(const sf::Vector2f& moveVector, const float& dist)
{
  float veclen = lengthVector2(moveVector);
  float distRatio = dist/veclen;
  sf::Vector2f distTraveled = sf::Vector2f(moveVector.x * distRatio, moveVector.y * distRatio);
  return distTraveled;
}
int mapValue(int value, float percent)
{
  return int((value * percent)/100);
}
double dist2D(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
    float x,y;
    x = pos1.x - pos2.x;
    y = pos1.y - pos2.y;
    return sqrt(x*x + y*y);
}
