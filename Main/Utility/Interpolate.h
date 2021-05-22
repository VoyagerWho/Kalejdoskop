#ifndef INTERPOLATIONS_H
#define INTERPOLATIONS_H

#include <iostream>
#include <cmath>
#include <string>
#define M_PI 3.141592653589
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <functional>

class Container// do dokoñczenia
{
public:
  void update();
  Container(){
    dw = 800;
    dh = 800;
    tw = 1135;//dw*sqrt(2)
    th = 1135;//dh*sqrt(2)
    angle=0.0;
    NoAxis=8;
    needUpdate=true;
    piksele  = new sf::Uint8[dw * dh * 4];
  }
    //ewentualnie: sf::Vector2u dim = oryginal.getSize();

  ~Container(){}
  //ctor
  //dtor=

  void moveAngle(float deltaTime, float speed){
    angle+=deltaTime*speed;
    angle = angle > 2*M_PI ? angle - 2*M_PI : angle;
  }
  //void moveAngle(float deltatime);

  unsigned int get_dw(){
    return dw;
  }

  unsigned int  get_dh(){
    return dh;
  }

  unsigned int  get_tw(){
    return tw;
  }

  unsigned int  get_th(){
    return th;
  }

  unsigned int  get_angle(){
    return angle;
  }

  sf::Image get_oryginal(){
    return oryginal;
  }

  void set_oryginal(const std::string& name){
    oryginal.loadFromFile(name);
  }

  void create_Texture(){
    display.create(dw, dh);
  }

 sf::Color getPixel(unsigned int x, unsigned int y){
    return oryginal.getPixel(x,y);
  }
  //getPixel -> return oryginal.getPixel()

  sf::Texture& get_Texture(){
    return display;
  }
  //get texture

  unsigned int get_NoAxis(){
    return NoAxis;
  }

  void add_Axis(){
    if(NoAxis<12) NoAxis++;
    //needUpdate=true;
  }

  void sub_Axis(){
    if(NoAxis>1) NoAxis--;
    //needUpdate=true;
  }

  //+1 -1 dla osi
  sf::Uint8* piksele;//
  bool needUpdate;

private:
  unsigned dw, dh, tw, th;
  double angle;

  unsigned NoAxis;
  sf::Image oryginal;
  sf::Texture display;
  //sf::Uint8* piksele;
};

void updateThread(Container& ds, unsigned ymin, unsigned ymax);

sf::Vector2f translate(sf::Vector2f posDis, Container& ds);

sf::Color interpolateBL(sf::Vector2f pos, Container& ds);

#endif // INTERPOLATIONS_H
