#include "Menu.h"

bool Menu::onHover(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseMove.x, evnt.mouseMove.y);
    if(isInActiveZone(mousePos))
    {
      bool result = false;
      for(unsigned int i=0;i<options.size();i++)
      {
          result |=options[i].onHover(evnt);
      }
      return result;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------------

bool Menu::onClick(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y);
    if(isInActiveZone(mousePos))
    {
      if(evnt.mouseButton.button == sf::Mouse::Left)
      {
        for(unsigned int i=0;i<options.size();i++)
        {
          if(options[i].onClick(evnt))
          {
              option = i;
              return true;
          }
        }
      }
      else if(evnt.mouseButton.button == sf::Mouse::Right)
      {
        // sth
      }
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------------
