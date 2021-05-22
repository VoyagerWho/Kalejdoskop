#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Classes/SidebarMenu.h"
#include "Utility/Interpolate.h"

/**
//opcjonalnie
display

dodaj os
odejmij os

//opcjonalnie
animacja start
animacja stop

generuj bmp

zamknij

k¹t pod suwakiem
//roz
przesuniêcie ox oY w %
*/

/**
to do
suwak
*/

void displayHandler(const sf::Texture& tex)
{
  sf::RenderWindow window(sf::VideoMode(200, 200), "Display", sf::Style::Default);
  window.setFramerateLimit(30);
  sf::Event evnt;
  sf::Sprite sp;
  sp.setTexture(tex);
  while(window.isOpen())
  {
    while(window.pollEvent(evnt))
    {
      switch (evnt.type)
      {
      case sf::Event::Closed:
          window.close();
        break;

        default:
        break;
      }
    }
    window.clear(sf::Color(64,64,64));
    window.draw(sp);

    window.display();
  }
}

void makeDrawing(sf::RenderTexture& tex)
{
  sf::CircleShape c(30.0f);
  sf::Texture im;
  im.loadFromFile("Files/Testowy.jpg");
  sf::Sprite sp;
  sp.setTexture(im);
  sp.scale(0.2, 0.2);

  tex.clear(sf::Color::Transparent);

  c.setFillColor(sf::Color::Red);
  c.setOutlineColor(sf::Color::Black);
  c.setOutlineThickness(1.0f);
  c.setPosition(85.0f, 85.0f);
  tex.draw(c);

  c.setFillColor(sf::Color::Blue);
  c.setOutlineColor(sf::Color::Black);
  c.setOutlineThickness(1.0f);
  c.setPosition(115.0f, 55.0f);
  c.setPointCount(3);
  tex.draw(c);

  c.setFillColor(sf::Color::Green);
  c.setOutlineColor(sf::Color::Black);
  c.setOutlineThickness(1.0f);
  c.setPosition(55.0f, 115.0f);
  c.setPointCount(4);
  tex.draw(c);

  c.setFillColor(sf::Color::Magenta);
  c.setOutlineColor(sf::Color::Black);
  c.setOutlineThickness(1.0f);
  c.setPosition(115.0f, 115.0f);
  c.setPointCount(6);
  tex.draw(c);

  c.setFillColor(sf::Color::Cyan);
  c.setOutlineColor(sf::Color::Black);
  c.setOutlineThickness(1.0f);
  c.setPosition(55.0f, 55.0f);
  c.setPointCount(8);
  tex.draw(c);

  //tex.draw(sp);

  tex.display();
}

void test(int a, int b)
{
  for(unsigned i=0;i<1000;i++)
  {
    std::cout<<a*b<<std::endl;
  }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Demo", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::RenderTexture renderTex;
    renderTex.create(200, 200);
    makeDrawing(renderTex);
    sf::Thread displayThread(displayHandler, renderTex.getTexture());
    sf::Cursor cursor;
    sf::Event evnt;
    sf::Clock clock;
    float deltaTime=0.0;
    float angle=0.0f;
    float speed=M_PI/25.0;
    SidebarMenu sidemenu(window, SidebarMenu::Right, 4);
    sidemenu.flags ^= SidebarMenu::showLabel | SidebarMenu::visible;
    sidemenu.buttons[0].setLabelString("Display");
    sidemenu.buttons[1].setLabelString("Start");
    sidemenu.buttons[2].setLabelString("Stop");
    sidemenu.buttons[3].setLabelString("Off");
    sidemenu.buttons[3].flags ^= AButtonCircle::showLabel;
    sidemenu.buttons[3].setTextureRect(sf::IntRect(0, 0, 256, 256));
    sidemenu.buttons[3].loadTextureFromFile("Files/OnOff.png");

    sf::VertexArray triangle(sf::Triangles, 3);
    Container datastorage;
    //do konstruktora
   
    //datastorage.needUpdate=true;
    datastorage.set_oryginal("Files/slimakiv2.png");
    datastorage.create_Texture();
    datastorage.piksele=new sf::Uint8[datastorage.get_dw()*datastorage.get_dh()*4];
    for(unsigned i=0;i<datastorage.get_dh();i++)
    {
      for(unsigned j=0;j<datastorage.get_dw();j++)
      {
        datastorage.piksele[4*(i*datastorage.get_dw() + j) + 3]=255;
      }
    }
    sf::Sprite display;
    display.setTexture(datastorage.get_Texture());

    //-----------------------------------------------------------------------------------------------------------
    //         Beware!      Debug zone
    //-----------------------------------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------------------------------


    while(window.isOpen())
    {
      deltaTime=clock.restart().asSeconds();
      // do moveAngle
      datastorage.moveAngle(deltaTime, speed);
      //datastorage.angle+=deltaTime*speed;
      //datastorage.angle = datastorage.angle > 2*M_PI ? datastorage.angle - 2*M_PI : datastorage.angle;//zrobic metode w klasie
      //datastorage.needUpdate=true;
      while(window.pollEvent(evnt))
      {
        switch (evnt.type)
        {
        case sf::Event::Closed:
            window.close();
          break;
        case sf::Event::Resized:
          {
            window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y)));
            sidemenu.setPosition(window);
          }break;
        case sf::Event::MouseMoved:
          {
            cursor.loadFromSystem(sf::Cursor::Arrow);
            if(sidemenu.onHover(evnt))
              cursor.loadFromSystem(sf::Cursor::Hand);
            window.setMouseCursor(cursor);
          }break;
        case sf::Event::MouseButtonPressed:
          {
            if(sidemenu.onClick(evnt))
            {
              switch (sidemenu.getOption())
              {
                case 0:
                {
                  displayThread.launch();
                }break;
                case 1:
                {
                  speed=M_PI/25;
                }break;
                case 2:
                {
                  speed=0.0f;
                }break;
                case 3:
                {
                  displayThread.terminate();
                  window.close();
                }break;

                default:
                  break;
              }
            }
          }break;

          default:
          break;
        }

      }
      window.clear(sf::Color(64,64,64));

      datastorage.update();
      window.draw(display);

      sidemenu.update(deltaTime);
      window.draw(sidemenu);

//      for(unsigned i=0;i<16;i++)
//      {
//        triangle[0].position = sf::Vector2f(400.0f, 400.0f);
//        triangle[0].texCoords = sf::Vector2f(100.0f, 100.0f);
//        triangle[i%2+1].position = sf::Vector2f(400.0f+400.f*cos(i*(M_PI/8.0)), 400.0f+400.f*sin(i*(M_PI/8.0)));
//        triangle[i%2+1].texCoords = sf::Vector2f(100.0f+100.f*cos((i%2)*(M_PI/8.0)+angle), 100.0f+100.f*sin((i%2)*(M_PI/8.0)+angle));
//        triangle[i%2+1].position = sf::Vector2f(400.0f+400.f*cos((i+1)*(M_PI/8.0)), 400.0f+400.f*sin((i+1)*(M_PI/8.0)));
//        triangle[i%2+1].texCoords = sf::Vector2f(100.0f+100.f*cos((i%2)*(M_PI/8.0)+angle), 100.0f+100.f*sin((i%2)*(M_PI/8.0)+angle));
//        window.draw(triangle, &renderTex.getTexture());
//      }


      window.display();

    }
    delete[] datastorage.piksele;
    return 0;
}
