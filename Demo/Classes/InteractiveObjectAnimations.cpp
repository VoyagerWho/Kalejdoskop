#include "InteractiveObject.h"

bool InteractiveObject::onHover(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseMove.x, evnt.mouseMove.y);
    if(isInActiveZone(mousePos))
    {
      // sth
      return true;
    }
  }

  return false;
}
//-----------------------------------------------------------------------------------------------------------

bool InteractiveObject::onClick(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y);
    if(isInActiveZone(mousePos))
    {
      // react to click
      if(evnt.mouseButton.button == sf::Mouse::Left)
      {
        // sth
      }
      else if(evnt.mouseButton.button == sf::Mouse::Right)
      {
        // sth
      }
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------------
