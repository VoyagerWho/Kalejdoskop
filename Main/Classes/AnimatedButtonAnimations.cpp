#include "AnimatedButton.h"

bool AButtonCircle::onHover(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseMove.x, evnt.mouseMove.y);
    if(isInActiveZone(mousePos))
    {
      if((animStage == animStages::turnedOff) || (animStage == animStages::turningOff))
        animStage = animStages::turningOn;
      return true;
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

bool AButtonCircle::onClick(const sf::Event& evnt)
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------
bool AButtonRectangle::onHover(const sf::Event& evnt)
{
  if(flags & active)
  {
    sf::Vector2f mousePos = sf::Vector2f(evnt.mouseMove.x, evnt.mouseMove.y);
    if(isInActiveZone(mousePos))
    {
      if((animStage = animStages::turnedOff) || (animStage = animStages::turningOff))
        animStage = animStages::turningOn;
      return true;
    }
    else
    {
      if((animStage = animStages::turnedOn) || (animStage = animStages::turningOn))
        animStage = animStages::turningOff;
    }
  }

  return false;
}
//-----------------------------------------------------------------------------------------------------------

bool AButtonRectangle::onClick(const sf::Event& evnt)
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
