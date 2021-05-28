#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Classes/SidebarMenu.h"
#include "Classes/Scrollbar.h"
#include "Classes/TextEdit.h"
#include "Utility/Interpolate.h"

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

    SidebarMenu sidemenu(window, SidebarMenu::Right, 11);
    sidemenu.flags ^= SidebarMenu::showLabel | SidebarMenu::visible;
    /*sidemenu.buttons[0].setLabelString("Display");
    sidemenu.buttons[1].setLabelString("Start");
    sidemenu.buttons[2].setLabelString("Stop");
    sidemenu.buttons[3].setLabelString("+1");
    sidemenu.buttons[4].setLabelString("-1");
    sidemenu.buttons[5].setLabelString("Zapisz");
    sidemenu.buttons[6].setLabelString("Generuj");
    sidemenu.buttons[7].setLabelString("CPU");
    sidemenu.buttons[8].setLabelString("GPU");
    sidemenu.buttons[9].setLabelString("Reset");
    sidemenu.buttons[10].setLabelString("Off");*/

    for (int i = 0; i < 11; i++) {
        sidemenu.buttons[i].flags ^= AButtonCircle::showLabel;
        sidemenu.buttons[i].setTextureRect(sf::IntRect(0, 0, 256, 256));
    }

    sidemenu.buttons[0].loadTextureFromFile("Files/Buttons/display.png");
    sidemenu.buttons[1].loadTextureFromFile("Files/Buttons/start.png");
    sidemenu.buttons[2].loadTextureFromFile("Files/Buttons/stop.png");
    sidemenu.buttons[3].loadTextureFromFile("Files/Buttons/plus.png");
    sidemenu.buttons[4].loadTextureFromFile("Files/Buttons/minus.png");
    sidemenu.buttons[5].loadTextureFromFile("Files/Buttons/save.png");
    sidemenu.buttons[6].loadTextureFromFile("Files/Buttons/generujBitmapy.png");
    sidemenu.buttons[7].loadTextureFromFile("Files/Buttons/bc.png");
    sidemenu.buttons[8].loadTextureFromFile("Files/Buttons/gpu.png");
    sidemenu.buttons[9].loadTextureFromFile("Files/Buttons/reset.png");
    sidemenu.buttons[10].loadTextureFromFile("Files/Buttons/OnOff.png");

    //sidemenu.setPosition(window);

    Scrollbar scrollPosX(-100.0, 100.0);
    scrollPosX.setPosition_ver2(sf::Vector2f(10.0f, 770.0f));
    scrollPosX.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollPosX.setLabelString("X: 0");

    Scrollbar scrollPosY(-100.0, 100.0);
    scrollPosY.setPosition_ver2(sf::Vector2f(300.0f, 770.0f));
    scrollPosY.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollPosY.setLabelString("Y: 0");

    Scrollbar scrollAngle(0.0, 2*M_PI);
    scrollAngle.setPosition(sf::Vector2f(590.0f, 770.0f));
    scrollAngle.setSize(sf::Vector2f(200.0f, 20.0f));
    scrollAngle.setLabelString("Kat: 0");

    TextEdit edit1(sf::Vector2f(600.0f, 10.0f), (unsigned)9);
    edit1.SetTextString("");
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
    //--
    std::fstream fs;
    fs.open("Setup.cfg");
    std::string nazwaPliku;
    getline(fs, nazwaPliku);
    fs.close();
    //--
    Container datastorage(nazwaPliku);
    sf::Sprite display;
    display.setTexture(datastorage.get_display());
    sf::Thread displayThread(displayHandler, datastorage.get_oryginal());
    sf::Texture oryginalTex;
    oryginalTex.create(datastorage.get_tw(), datastorage.get_th());
    oryginalTex.update(datastorage.get_oryginal());
    oryginalTex.setRepeated(true);
    //-----------------------------------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------------------------------
    //         Beware!      Debug zone
    //-----------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------------

    while(window.isOpen())
    {
      deltaTime=clock.restart().asSeconds();
      datastorage.moveAngle(deltaTime, speed);
      scrollAngle.setValue(datastorage.get_angle());
      scrollAngle.setLabelString("Kat: "+std::to_string(static_cast<int>(datastorage.get_angle()*360/(2*M_PI)))+" stopni");

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
                  datastorage.add_Axis();
                }break;
                case 4:
                {
                  datastorage.sub_Axis();
                }break;
                case 5:
                {
                  datastorage.get_display().copyToImage().saveToFile("Output/preview.bmp");
                }break;
                case 6:
                {
                  speed = 0.0f;
                  const std::string filename = "Output/" + edit1.GetString();
                  const std::string rozsz = ".bmp";
                  float tempSpeed = 2.0* M_PI / 100.0;

                  //generuj bitmapê, czyli 100 obrazków

                  for (int i = 1; i <= 100; i++)
                  {
                    datastorage.moveAngle(tempSpeed, 1);
                    datastorage.needUpdate=true;
                    datastorage.update();
                    if (i < 10) {
                        datastorage.get_display().copyToImage().saveToFile(filename + "00" + std::to_string(i) + rozsz);
                    } else if (i < 100) {
                        datastorage.get_display().copyToImage().saveToFile(filename + "0"+std::to_string(i) + rozsz);
                    } else {
                        datastorage.get_display().copyToImage().saveToFile(filename + std::to_string(i) + rozsz);
                    }
                  }
                }break;
                case 7:
                {
                  if(datastorage.interpolationBC)
                  {
                    datastorage.interpolationBC=false;
                    sidemenu.buttons[7].loadTextureFromFile("Files/Buttons/bc.png");
                  }
                  else
                  {
                    datastorage.interpolationBC=true;
                    sidemenu.buttons[7].loadTextureFromFile("Files/Buttons/bl.png");
                  }
                  datastorage.needUpdate = true;
                }break;
                case 8:
                {
                  if(GPUacceleration)
                  {
                    GPUacceleration=false;
                    sidemenu.buttons[8].loadTextureFromFile("Files/Buttons/GPU.png");
                  }
                  else
                  {
                    GPUacceleration=true;
                    sidemenu.buttons[8].loadTextureFromFile("Files/Buttons/CPU.png");
                  }
                }break;
                case 9:
                {
                  datastorage.reset();
                  scrollAngle.setValue(0.0);
                  scrollPosX.setValue(0.0);
                  scrollPosY.setValue(0.0);
                  scrollAngle.setLabelString("Kat: "+std::to_string(static_cast<int>(datastorage.get_angle()*360/(2*M_PI)))+" stopni");
                  scrollPosX.setLabelString("X: " + std::to_string(static_cast<int>(datastorage.get_offsetX())) + "%");
                  scrollPosY.setLabelString("Y: " + std::to_string(static_cast<int>(datastorage.get_offsetY())) + "%");
                }break;
                case 10:
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
              datastorage.set_angle(scrollAngle.getValue());
              scrollAngle.setLabelString("Kat: "+std::to_string(static_cast<int>(datastorage.get_angle()*360/(2*M_PI)))+" stopni");
              datastorage.needUpdate=true;
            }
            if (scrollPosX.onClick(evnt))
            {
              datastorage.set_offsetX(scrollPosX.getValue());
              scrollPosX.setLabelString("X: " + std::to_string(static_cast<int>(datastorage.get_offsetX())) + "%");
              datastorage.needUpdate = true;
            }
            if (scrollPosY.onClick(evnt))
            {
              datastorage.set_offsetY(scrollPosY.getValue());
              scrollPosY.setLabelString("Y: " + std::to_string(static_cast<int>(datastorage.get_offsetY())) + "%");
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
        double tx=datastorage.get_tw()/2.0, ty=datastorage.get_th()/2.0;
        int offx = int(datastorage.get_offsetX()*0.01*datastorage.get_tw());
        int offy = int(datastorage.get_offsetY()*0.01*datastorage.get_th());
        for(unsigned i=0;i<2*datastorage.get_NoAxis();i++)
        {
          triangle[0].position = sf::Vector2f(400.0f, 400.0f);
          triangle[0].texCoords = sf::Vector2f(tx + offx, ty + offy);
          triangle[i%2+1].position = sf::Vector2f(400.0f+400.f*cos(i*(M_PI/datastorage.get_NoAxis())), 400.0f+400.f*sin(i*(M_PI/datastorage.get_NoAxis())));
          triangle[i%2+1].texCoords = sf::Vector2f(tx+offx+tx*cos((i%2)*(M_PI/datastorage.get_NoAxis())+datastorage.get_angle()), ty+offy+ty*sin((i%2)*(M_PI/datastorage.get_NoAxis())+datastorage.get_angle()));
          triangle[i%2+1].position = sf::Vector2f(400.0f+400.f*cos((i+1)*(M_PI/datastorage.get_NoAxis())), 400.0f+400.f*sin((i+1)*(M_PI/datastorage.get_NoAxis())));
          triangle[i%2+1].texCoords = sf::Vector2f(tx+tx*cos((i%2)*(M_PI/datastorage.get_NoAxis())+datastorage.get_angle()), ty+offy+ty*sin((i%2)*(M_PI/datastorage.get_NoAxis())+datastorage.get_angle()));
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
}
