#include "Scrollbar.h"

bool Scrollbar::onHover(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseMove.x, evnt.mouseMove.y);
    if(isInActiveZone(mousePos))
    {
      return true;
    }
    else
    {

    }
  }

  return false;
}
//-----------------------------------------------------------------------------------------------------------

bool Scrollbar::onClick(const sf::Event& evnt)
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
        float of = mousePos.x-position.x;
        scrollVal=of/(size.x)*(valmax - valmin) + valmin;
        scroll.setPosition(sf::Vector2f(position.x + (size.x)*(scrollVal - valmin)/(valmax - valmin), position.y));
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
