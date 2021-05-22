#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Classes/SidebarMenu.h"
#include "Classes/Scrollbar.h"
#include "Classes/TextEdit.h"
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
kšt pod suwakiem
//roz
przesunięcie ox oY w %
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

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Kalejdoskop", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::RenderTexture renderTex;
    renderTex.create(200, 200);
    makeDrawing(renderTex);
    sf::Thread displayThread(displayHandler, renderTex.getTexture());
    sf::Cursor cursor;
    sf::Event evnt;
    sf::Clock clock;
    float deltaTime=0.0;
    float speed=0.0;
    SidebarMenu sidemenu(window, SidebarMenu::Right, 8);
    sidemenu.flags ^= SidebarMenu::showLabel | SidebarMenu::visible;
    sidemenu.buttons[0].setLabelString("Display");
    sidemenu.buttons[1].setLabelString("Start");
    sidemenu.buttons[2].setLabelString("Stop");
    sidemenu.buttons[3].setLabelString("+1");
    sidemenu.buttons[4].setLabelString("-1");
    sidemenu.buttons[5].setLabelString("Zapisz");
    sidemenu.buttons[6].setLabelString("Generuj");

    sidemenu.buttons[7].setLabelString("Off");
    sidemenu.buttons[7].flags ^= AButtonCircle::showLabel;
    sidemenu.buttons[7].setTextureRect(sf::IntRect(0, 0, 256, 256));
    sidemenu.buttons[7].loadTextureFromFile("Files/OnOff.png");

    Scrollbar scrollAngle(0.0, 2*M_PI);
    scrollAngle.setPosition(sf::Vector2f(590.0f, 770.0f));
    scrollAngle.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollAngle.setLabelString("Kat");

    TextEdit edit1(sf::Vector2f(600.0f, 10.0f), (unsigned)9);
    edit1.visible = true;
    TextEdit* activeEdit = nullptr;


    sf::VertexArray triangle(sf::Triangles, 3);
    Container datastorage;
    //do konstruktora
    datastorage.dw = 800;
    datastorage.dh = 800;
    datastorage.tw = 800;//dw*sqrt(2)
    datastorage.th = 800;//dh*sqrt(2)
    datastorage.angle=0.0;
    datastorage.NoAxis=8;
    datastorage.needUpdate=true;
    datastorage.oryginal.loadFromFile("Files/Kalejdoskop.png");
    datastorage.display.create(datastorage.dw, datastorage.dh);
    datastorage.piksele=new sf::Uint8[datastorage.dw*datastorage.dh*4];
    for(unsigned i=0;i<datastorage.dh;i++)
    {
      for(unsigned j=0;j<datastorage.dw;j++)
      {
        datastorage.piksele[4*(i*datastorage.dw + j) + 3]=255;
      }
    }
    sf::Sprite display;
    display.setTexture(datastorage.display);

    //-----------------------------------------------------------------------------------------------------------
    //         Beware!      Debug zone
    //-----------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------------

    while(window.isOpen())
    {
      deltaTime=clock.restart().asSeconds();
      // do moveAngle
      datastorage.angle+=deltaTime*speed;
      datastorage.angle = datastorage.angle > 2*M_PI ? datastorage.angle - 2*M_PI : datastorage.angle;//zrobic metode w klasie
      if(speed != 0.0)
        datastorage.needUpdate=true;
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
        case sf::Event::TextEntered:
          {
            if(activeEdit)
              activeEdit->addCharacter(evnt.text.unicode);
          }break;
        case sf::Event::KeyPressed:
          {
            if(activeEdit)
            {
              if(evnt.key.code == sf::Keyboard::Left)
                activeEdit->moveCursor(-1);
              else if(evnt.key.code == sf::Keyboard::Right)
                activeEdit->moveCursor(1);
              else if(evnt.key.code == sf::Keyboard::Delete)
                activeEdit->delCharacter();
            }
          }break;
        case sf::Event::MouseMoved:
          {
            cursor.loadFromSystem(sf::Cursor::Arrow);
            if(sidemenu.onHover(evnt))
              cursor.loadFromSystem(sf::Cursor::Hand);
            if(scrollAngle.onHover(evnt))
              cursor.loadFromSystem(sf::Cursor::Hand);
//            if(edit1.isInActiveZone(sf::Vector2f(evnt.mouseMove.x,evnt.mouseMove.y)));
//            {
//              cursor.loadFromSystem(sf::Cursor::Text);
//            }
            window.setMouseCursor(cursor);
          }break;
        case sf::Event::MouseButtonPressed:
          {
            if(evnt.mouseButton.button == 0)
            {
              //Turn off active stuff
              if((activeEdit)&&!(activeEdit->isInActiveZone(sf::Vector2f(evnt.mouseButton.x,evnt.mouseButton.y))))
              {
                activeEdit->active=false;
                activeEdit=nullptr;
              }
              //Find new active think
              if(edit1.isInActiveZone(sf::Vector2f(evnt.mouseButton.x,evnt.mouseButton.y)))
              {
                if(activeEdit)
                  activeEdit->active=false;
                activeEdit=&edit1;
                activeEdit->active=true;
                activeEdit->moveCursor(sf::Vector2f(evnt.mouseButton.x,evnt.mouseButton.y));
              }
            }
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
                  if(datastorage.NoAxis<20)
                  {
                    datastorage.NoAxis++;
                    datastorage.needUpdate=true;
                  }
                }break;
                case 4:
                {
                  if(datastorage.NoAxis>1)
                  {
                    datastorage.NoAxis--;
                    datastorage.needUpdate=true;
                  }
                }break;
                case 5:
                {
                  datastorage.display.copyToImage().saveToFile("Output/preview.png");
                }break;
                case 6:
                {
                  speed = 0.0f;
                  const std::string filename = "Output/" + edit1.GetString();
                  const std::string rozsz = ".png";
                  float tempSpeed = 2.0* M_PI / 100.0;

                  //generuj bitmapê, czyli 100 obrazków

                  for (int i = 1; i <= 100; i++)
                  {
                    datastorage.angle+=tempSpeed;
                    datastorage.angle = datastorage.angle > 2*M_PI ? datastorage.angle - 2*M_PI : datastorage.angle;
                    datastorage.needUpdate=true;
                    datastorage.update();
                    if (i < 10) {
                        datastorage.display.copyToImage().saveToFile(filename + "00" + std::to_string(i) + rozsz);
                    } else if (i < 100) {
                        datastorage.display.copyToImage().saveToFile(filename + "0"+std::to_string(i) + rozsz);
                    } else {
                        datastorage.display.copyToImage().saveToFile(filename + std::to_string(i) + rozsz);
                    }
                  }
                }break;
                case 7:
                {
                  displayThread.terminate();
                  window.close();
                }break;

                default:
                  break;
              }
            }
            if(scrollAngle.onClick(evnt))
            {
              datastorage.angle=scrollAngle.getValue();
              datastorage.needUpdate=true;
            }
          }break;

          default:
          break;
        }

      }
      if(activeEdit)
        activeEdit->update(deltaTime);
      window.clear(sf::Color(64,64,64));

      datastorage.update();
      window.draw(display);

      sidemenu.update(deltaTime);
      window.draw(sidemenu);
      window.draw(edit1);
      window.draw(scrollAngle);

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
