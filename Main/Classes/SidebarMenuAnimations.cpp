#include "SidebarMenu.h"
bool SidebarMenu::onHover(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseMove.x, evnt.mouseMove.y);
    if(isInActiveZone(mousePos))
    {
      if((animStage == animStages::turnedOff) || (animStage == animStages::turningOff))
        animStage = animStages::turningOn;

      bool result = false;
      for(unsigned int i=0;i<buttons.size();i++)
      {
        result |= buttons[i].onHover(evnt);
      }
      return result;
    }
    else
    {
      if((animStage == animStages::turnedOn) || (animStage == animStages::turningOn))
        animStage = animStages::turningOff;
    }
  }

  return false;
}
//-----------------------------------------------------------------------------------------------------------

bool SidebarMenu::onClick(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y);
    if(isInActiveZone(mousePos))
    {
      // react to click
      if(evnt.mouseButton.button == sf::Mouse::Left)
      {
        for(unsigned int i=0;i<buttons.size();i++)
        {
          if(buttons[i].onClick(evnt))
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
