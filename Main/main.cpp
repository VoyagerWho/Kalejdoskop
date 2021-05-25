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

void displayHandler(const sf::Image& org)
{
  sf::RenderWindow window(sf::VideoMode(org.getSize().x, org.getSize().y), "Display", sf::Style::Default);
  window.setFramerateLimit(30);
  sf::Event evnt;
  sf::Sprite sp;
  sf::Texture tex;
  tex.create(org.getSize().x, org.getSize().y);
  tex.update(org);
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

int main()
{
    //-----------------------------------------------------------------------------------------------------------
    // SFML stuff
    //-----------------------------------------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(800, 800), "Kalejdoskop", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Cursor cursor;
    sf::Event evnt;
    sf::Clock clock;
    //-----------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------------
    // GUI stuff
    //-----------------------------------------------------------------------------------------------------------
    SidebarMenu sidemenu(window, SidebarMenu::Right, 10);
    sidemenu.flags ^= SidebarMenu::showLabel | SidebarMenu::visible;
    sidemenu.buttons[0].setLabelString("Display");
    sidemenu.buttons[1].setLabelString("Start");
    sidemenu.buttons[2].setLabelString("Stop");
    sidemenu.buttons[3].setLabelString("+1");
    sidemenu.buttons[4].setLabelString("-1");
    sidemenu.buttons[5].setLabelString("Zapisz");
    sidemenu.buttons[6].setLabelString("Generuj");
    sidemenu.buttons[7].setLabelString("CPU");
    sidemenu.buttons[8].setLabelString("GPU");

    sidemenu.buttons[9].setLabelString("Off");
    sidemenu.buttons[9].flags ^= AButtonCircle::showLabel;
    sidemenu.buttons[9].setTextureRect(sf::IntRect(0, 0, 256, 256));
    sidemenu.buttons[9].loadTextureFromFile("Files/OnOff.png");
    //sidemenu.setPosition(window);

    Scrollbar scrollPosX(-100.0, 100.0);
    scrollPosX.setPosition(sf::Vector2f(10.0f, 770.0f));
    scrollPosX.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollPosX.setLabelString("X: 0");
    
    Scrollbar scrollPosY(-100.0, 100.0);
    scrollPosY.setPosition(sf::Vector2f(300.0f, 770.0f));
    scrollPosY.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollPosY.setLabelString("Y: 0");

    Scrollbar scrollAngle(0.0, 2*M_PI);
    scrollAngle.setPosition(sf::Vector2f(590.0f, 770.0f));
    scrollAngle.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollAngle.setLabelString("Kat: 0");

    

    TextEdit edit1(sf::Vector2f(600.0f, 10.0f), (unsigned)9);
    edit1.visible = true;
    TextEdit* activeEdit = nullptr;
    //-----------------------------------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------------------------------
    // Misc stuff
    //-----------------------------------------------------------------------------------------------------------
    float deltaTime=0.0;
    float speed=0.0;
    bool GPUacceleration=false;
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
    sf::Thread displayThread(displayHandler, datastorage.oryginal);
    sf::Texture oryginalTex;
    oryginalTex.create(datastorage.tw, datastorage.th);
    oryginalTex.update(datastorage.oryginal);
    //-----------------------------------------------------------------------------------------------------------


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
            if (scrollPosX.onHover(evnt))
                cursor.loadFromSystem(sf::Cursor::Hand);
            if (scrollPosY.onHover(evnt))
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
                  GPUacceleration=false;
                }break;
                case 8:
                {
                  GPUacceleration=true;
                }break;
                case 9:
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
              scrollAngle.setLabelString("Kat: "+std::to_string(static_cast<int>(datastorage.angle*360/(2*M_PI)))+" stopni");
              datastorage.needUpdate=true;
            }
            if (scrollPosX.onClick(evnt))
            {
                datastorage.offsetX = scrollPosX.getValue();
                scrollPosX.setLabelString("X: " + std::to_string(static_cast<int>(datastorage.offsetX)));
                datastorage.needUpdate = true;
            }
            if (scrollPosY.onClick(evnt))
            {
                datastorage.offsetY = scrollPosY.getValue();
                scrollPosY.setLabelString("Y: " + std::to_string(static_cast<int>(datastorage.offsetY)));
                datastorage.needUpdate = true;
            }
          }break;

          default:
          break;
        }

      }
      if(activeEdit)
        activeEdit->update(deltaTime);
      window.clear(sf::Color(64,64,64));

      if(GPUacceleration)
      {
        double tx=datastorage.tw/2.0, ty=datastorage.th/2.0;
        for(unsigned i=0;i<2*datastorage.NoAxis;i++)
        {
          triangle[0].position = sf::Vector2f(400.0f, 400.0f);
          triangle[0].texCoords = sf::Vector2f(tx, ty);
          triangle[i%2+1].position = sf::Vector2f(400.0f+400.f*cos(i*(M_PI/datastorage.NoAxis)), 400.0f+400.f*sin(i*(M_PI/datastorage.NoAxis)));
          triangle[i%2+1].texCoords = sf::Vector2f(tx+tx*cos((i%2)*(M_PI/datastorage.NoAxis)+datastorage.angle), ty+tx*sin((i%2)*(M_PI/datastorage.NoAxis)+datastorage.angle));
          triangle[i%2+1].position = sf::Vector2f(400.0f+400.f*cos((i+1)*(M_PI/datastorage.NoAxis)), 400.0f+400.f*sin((i+1)*(M_PI/datastorage.NoAxis)));
          triangle[i%2+1].texCoords = sf::Vector2f(tx+tx*cos((i%2)*(M_PI/datastorage.NoAxis)+datastorage.angle), tx+ty*sin((i%2)*(M_PI/datastorage.NoAxis)+datastorage.angle));
          window.draw(triangle, &oryginalTex);
        }
      }
      else
      {
        datastorage.update();
        window.draw(display);
      }

      sidemenu.update(deltaTime);
      window.draw(sidemenu);
      window.draw(edit1);
      window.draw(scrollAngle);
      window.draw(scrollPosX);
      window.draw(scrollPosY);
      window.display();

    }
    delete[] datastorage.piksele;
    return 0;
}
