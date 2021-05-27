#ifndef INTERPOLATIONS_H
#define INTERPOLATIONS_H

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <functional>

class Container
{
public:
  friend void updateThread(Container& ds, unsigned ymin, unsigned ymax);
  friend sf::Color interpolateBL(sf::Vector2f pos, Container& ds);
  friend sf::Vector2f translate(sf::Vector2f posDis, Container& ds);

  Container(std::string file_name);
  ~Container();
  void update();
  void moveAngle(float deltaTime, float speed);
  void add_Axis();
  void sub_Axis();
  void refresh();

  //get_methods
  sf::Texture& get_display(){return display;}
  sf::Image& get_oryginal(){return oryginal;}
  unsigned get_tw(){return tw;}
  unsigned get_th(){return th;}
  double get_angle(){return angle;}
  double get_offsetX(){return offsetX;}
  double get_offsetY(){return offsetY;}
  unsigned get_NoAxis(){return NoAxis;}

  //set_methods
  void set_angle(double value){angle = value;}
  void set_offsetX(double value){offsetX = value;}
  void set_offsetY(double value){offsetY = value;}

    bool needUpdate;
    sf::Uint8* piksele;

protected:
  unsigned dw, dh, tw, th;
  double angle;
  double offsetX, offsetY;
  unsigned NoAxis;

  sf::Image oryginal;
  sf::Texture display;
};

void updateThread(Container& ds, unsigned ymin, unsigned ymax);

sf::Vector2f translate(sf::Vector2f posDis, Container& ds);

sf::Color interpolateBL(sf::Vector2f pos, Container& ds);

#endif // INTERPOLATIONS_H
