#ifndef INTERPOLATIONS_H
#define INTERPOLATIONS_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class Container// do dokończenia
{
public:
  void update();
  //ctor
  //dtor
  //void moveAngle(float deltatime);

  //get wymiarów
  //getPixel -> return oryginal.getPixel()
  //get texture

  //+1 -1 dla osi

  bool needUpdate;

public://private:
	unsigned dw, dh, tw, th;
	double angle;

	unsigned NoAxis;
	sf::Image oryginal;
	sf::Texture display;
	sf::Uint8* piksele;
};

sf::Vector2f translate(sf::Vector2f posDis, Container& ds);

sf::Color interpolateBL(sf::Vector2f pos, Container& ds);

#endif // INTERPOLATIONS_H
