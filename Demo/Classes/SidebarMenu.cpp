#include "SidebarMenu.h"

SidebarMenu::SidebarMenu(sf::RenderWindow& window, const unsigned& newFacing, const unsigned int& buttonCount, const float& buttonRadius, const float& newSpeed)
: InteractiveObject(), spacing(0.0f), middlePoint(0.0f), speed(newSpeed), positionStart(sf::Vector2f(0.0f, 0.0f)), facing(newFacing)
{
  label.setString("Sidebar Menu");
  spacing = buttonRadius/2.0f;
  float buttonOffset = 2*buttonRadius+spacing;
  middlePoint = (buttonCount-1)*buttonOffset/2.0f;

  switch (facing)
  {
  case Up:
    {
      InteractiveObject::setPosition(sf::Vector2f(window.getSize().x/2.0f, spacing));
      positionStart = position;
      InteractiveObject::move(0.0f, -buttonOffset);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons.push_back(AButtonCircle(sf::Vector2f(position.x - middlePoint + i*buttonOffset, position.y + buttonRadius), buttonRadius));
      }
      InteractiveObject::setOrigin(sf::Vector2f((middlePoint + spacing + buttonRadius), spacing));
      InteractiveObject::setSize(sf::Vector2f(2*(middlePoint + spacing + buttonRadius), 2*(buttonRadius + spacing)));
    }break;
  case Left:
    {
      InteractiveObject::setPosition(sf::Vector2f(spacing, window.getSize().y/2.0f));
      positionStart = position;
      InteractiveObject::move(-buttonOffset, 0.0f);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons.push_back(AButtonCircle(sf::Vector2f(position.x + buttonRadius, position.y - middlePoint + i*buttonOffset), buttonRadius));
      }
      InteractiveObject::setOrigin(sf::Vector2f(spacing, (middlePoint + spacing + buttonRadius)));
      InteractiveObject::setSize(sf::Vector2f(2*(buttonRadius + spacing) ,2*(middlePoint + spacing + buttonRadius)));
    }break;
  case Down:
    {
      InteractiveObject::setPosition(sf::Vector2f(window.getSize().x/2.0f, window.getSize().y-buttonOffset));
      positionStart = position;
      InteractiveObject::move(0.0f, buttonOffset);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons.push_back(AButtonCircle(sf::Vector2f(position.x - middlePoint + i*buttonOffset, position.y + buttonRadius), buttonRadius));
      }
      InteractiveObject::setOrigin(sf::Vector2f((middlePoint + spacing + buttonRadius), spacing));
      InteractiveObject::setSize(sf::Vector2f(2*(middlePoint + spacing + buttonRadius), 2*(buttonRadius + spacing)));
    }break;
  case Right:
    {
      InteractiveObject::setPosition(sf::Vector2f(window.getSize().x-buttonOffset, window.getSize().y/2.0f));
      positionStart = position;
      InteractiveObject::move(buttonOffset, 0.0f);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons.push_back(AButtonCircle(sf::Vector2f(position.x + buttonRadius, position.y - middlePoint + i*buttonOffset), buttonRadius));
      }
      InteractiveObject::setOrigin(sf::Vector2f(spacing, (middlePoint + spacing + buttonRadius)));
      InteractiveObject::setSize(sf::Vector2f(2*(buttonRadius + spacing) ,2*(middlePoint + spacing + buttonRadius)));
    }break;
  default:
    break;
  }
  animStage = turnedOff;
}
//-----------------------------------------------------------------------------------------------------------

SidebarMenu::~SidebarMenu()
{
    //dtor
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::setPosition(const sf::Vector2f& val)
{
  InteractiveObject::setPosition(val);
  positionStart = position;
  float radius = buttons[0].getRadius();

  float buttonOffset = 2*radius+spacing;

  unsigned buttonCount = buttons.size();

  sf::Vector2f positionLocal = position - origin;

  switch (facing)
  {
  case Up:
    {
      InteractiveObject::move(0.0f, -buttonOffset);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x - middlePoint + i*buttonOffset, positionLocal.y + radius));
      }
    }break;
  case Left:
    {
      InteractiveObject::move(-buttonOffset, 0.0f);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius, positionLocal.y - middlePoint + i*buttonOffset));
      }
    }break;
  case Down:
    {
      InteractiveObject::move(0.0f, buttonOffset);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x - middlePoint + i*buttonOffset, positionLocal.y + radius));
      }
    }break;
  case Right:
    {
      InteractiveObject::move(buttonOffset, 0.0f);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius, positionLocal.y - middlePoint + i*buttonOffset));
      }
    }break;
  default:
    break;
  }
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::setPosition(sf::RenderWindow& window)
{
  float radius = buttons[0].getRadius();

  float buttonOffset = 2*radius+spacing;

  unsigned buttonCount = buttons.size();

  switch (facing)
  {
  case Up:
    {
      InteractiveObject::setPosition(sf::Vector2f(window.getSize().x/2.0f, spacing));
      positionStart = position;
      InteractiveObject::move(0.0f, -buttonOffset);
      sf::Vector2f positionLocal = position - origin;
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius + spacing + i*buttonOffset, positionLocal.y + radius + spacing));
      }
    }break;
  case Left:
    {
      InteractiveObject::setPosition(sf::Vector2f(spacing, window.getSize().y/2.0f));
      positionStart = position;
      InteractiveObject::move(-buttonOffset, 0.0f);
      sf::Vector2f positionLocal = position - origin;
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius + spacing, positionLocal.y + radius + spacing + i*buttonOffset));
      }
    }break;
  case Down:
    {
      InteractiveObject::setPosition(sf::Vector2f(window.getSize().x/2.0f, window.getSize().y-buttonOffset));
      positionStart = position;
      InteractiveObject::move(0.0f, buttonOffset);
      sf::Vector2f positionLocal = position - origin;
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius + spacing + i*buttonOffset, positionLocal.y + radius + spacing));
      }
    }break;
  case Right:
    {
      InteractiveObject::setPosition(sf::Vector2f(window.getSize().x-buttonOffset, window.getSize().y/2.0f));
      positionStart = position;
      InteractiveObject::move(buttonOffset, 0.0f);
      sf::Vector2f positionLocal = position - origin;
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius + spacing, positionLocal.y + radius + spacing + i*buttonOffset));
      }
    }break;
  default:
    break;
  }

}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::setOrigin(const sf::Vector2f& val)
{
  InteractiveObject::setOrigin(val);

  float radius = buttons[0].getRadius();

  //float buttonOffset = 2*radius+spacing;

  unsigned buttonCount = buttons.size();

  sf::Vector2f positionLocal = position - origin;

  switch (facing)
  {
  case Up:
    {
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x - middlePoint + i*(2*radius+spacing), positionLocal.y + radius));
      }
    }break;
  case Left:
    {
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius, positionLocal.y - middlePoint + i*(2*radius+spacing)));
      }
    }break;
  case Down:
    {
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x - middlePoint + i*(2*radius+spacing), positionLocal.y + radius));
      }
    }break;
  case Right:
    {
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius, positionLocal.y - middlePoint + i*(2*radius+spacing)));
      }
    }break;
  default:
    break;
  }

}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::setScale(const sf::Vector2f& val)
{
  InteractiveObject::setScale(val);
  unsigned buttonCount = buttons.size();
  for(unsigned int i=0;i<buttonCount;i++)
  {
    buttons[i].setScale(val);
  }
}
//-----------------------------------------------------------------------------------------------------------

int SidebarMenu::getOption() const
{
  return option;
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::setSpacing(const float& val)
{
  float oldSpacing = spacing;
  spacing=val;
  float radius = buttons[0].getRadius();
  middlePoint = (buttons.size()-1)*(2*radius+spacing)/2.0f;

  float buttonOffset = 2*radius+spacing;

  unsigned buttonCount = buttons.size();

  sf::Vector2f positionLocal = position - origin;

  switch (facing)
  {
  case Up:
    {
      InteractiveObject::setPosition(sf::Vector2f(position.x, spacing));
      positionStart = position;
      InteractiveObject::move(0.0f, -buttonOffset);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x - middlePoint + i*(2*radius+spacing), positionLocal.y + radius));
      }
      InteractiveObject::setOrigin(sf::Vector2f(middlePoint, spacing));
      InteractiveObject::setSize(sf::Vector2f(2*(middlePoint + spacing + radius), 2*(radius + spacing)));
    }break;
  case Left:
    {
      InteractiveObject::setPosition(sf::Vector2f(spacing, position.y));
      positionStart = position;
      InteractiveObject::move(-buttonOffset, 0.0f);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius, positionLocal.y - middlePoint + i*(2*radius+spacing)));
      }
      InteractiveObject::setOrigin(sf::Vector2f(spacing, middlePoint));
      InteractiveObject::setSize(sf::Vector2f(2*(radius + spacing) ,2*(middlePoint + spacing + radius) ));
    }break;
  case Down:
    {
      InteractiveObject::setPosition(sf::Vector2f(position.x, position.y+oldSpacing-spacing));
      positionStart = position;
      InteractiveObject::move(0.0f, buttonOffset);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x - middlePoint + i*(2*radius+spacing), positionLocal.y + radius));
      }
      InteractiveObject::setOrigin(sf::Vector2f(middlePoint, spacing));
      InteractiveObject::setSize(sf::Vector2f(2*(middlePoint + spacing + radius), 2*(radius + spacing)));
    }break;
  case Right:
    {
      InteractiveObject::setPosition(sf::Vector2f(position.x+oldSpacing-spacing, position.y));
      positionStart = position;
      InteractiveObject::move(buttonOffset, 0.0f);
      for(unsigned int i=0;i<buttonCount;i++)
      {
        buttons[i].setPosition(sf::Vector2f(positionLocal.x + radius, positionLocal.y - middlePoint + i*(2*radius+spacing)));
      }
      InteractiveObject::setOrigin(sf::Vector2f(spacing, middlePoint));
      InteractiveObject::setSize(sf::Vector2f(2*(radius + spacing) ,2*(middlePoint + spacing + radius) ));
    }break;
  default:
    break;
  }
}
//-----------------------------------------------------------------------------------------------------------

float SidebarMenu::getSpacing() const
{
  return spacing;
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::setSpeed(const float& val)
{
  speed=val;
}
//-----------------------------------------------------------------------------------------------------------

float SidebarMenu::getSpeed() const
{
  return speed;
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::move(const float& offsetX, const float& offsetY)
{
  InteractiveObject::move(offsetX, offsetY);
  positionStart=position;
  for (unsigned int i=0; i<buttons.size(); i++)
  {
    buttons[i].move(offsetX, offsetY);
  }
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::move(const sf::Vector2f& offset)
{
  InteractiveObject::move(offset);
  positionStart=position;
  for (unsigned int i=0; i<buttons.size(); i++)
  {
    buttons[i].move(offset);
  }
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::moveAnimation(const float& offsetX, const float& offsetY)
{
  InteractiveObject::move(offsetX, offsetY);
  for (unsigned int i=0; i<buttons.size(); i++)
  {
    buttons[i].move(offsetX, offsetY);
  }
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::scale(const float& factorX, const float& factorY)
{
  InteractiveObject::scale(factorX, factorY);
  for (unsigned int i=0; i<buttons.size(); i++)
  {
    buttons[i].scale(factorX, factorY);
  }
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::scale(const sf::Vector2f& factor)
{
  InteractiveObject::scale(factor);
  for (unsigned int i=0; i<buttons.size(); i++)
  {
    buttons[i].scale(factor);
  }
}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(flags & visible)
  {
    if(flags & showActiveZone)
      target.draw(activeZone, states);
    for (unsigned int i=0; i<buttons.size(); i++)
    {
      target.draw(buttons[i], states);
    }
    if(flags & showLabel)
      target.draw(label, states);
  }

}
//-----------------------------------------------------------------------------------------------------------

void SidebarMenu::update(const float& deltaTime)
{
  // for animations and other time based features

  if(flags & active)
  {
    for(unsigned int i=0;i<buttons.size();i++)
    {
      buttons[i].update(deltaTime);
    }
    float radius = buttons[0].getRadius();
    float buttonOffset = 2*radius+spacing;
    float dist = speed*deltaTime;

    if(animStage == animStages::turningOn)
    {
      switch (facing)
      {
      case Up:
        {
          if(position.y + dist > positionStart.y)
          {
            moveAnimation(0.0f, positionStart.y-position.y);
            animStage=animStages::turnedOn;
          }
          else
          {
            moveAnimation(0.0f, dist);
          }
        }break;
      case Left:
        {
          if(position.x + dist > positionStart.x)
          {
            moveAnimation(positionStart.x-position.x, 0.0f);
            animStage=animStages::turnedOn;
          }
          else
          {
            moveAnimation(dist, 0.0f);
          }
        }break;
      case Down:
        {
          if(position.y - dist < positionStart.y)
          {
            moveAnimation(0.0f, -(positionStart.y-position.y));
            animStage=animStages::turnedOn;
          }
          else
          {
            moveAnimation(0.0f, -dist);
          }
        }break;
      case Right:
        {
          if(position.x - dist < positionStart.x)
          {
            moveAnimation(-(positionStart.x-position.x), 0.0f);
            animStage=animStages::turnedOn;
          }
          else
          {
            moveAnimation(-dist, 0.0f);
          }
        }break;
        default:
        break;
      }
      flags |= visible;
    }
    else if(animStage == animStages::turningOff)
    {
      switch (facing)
      {
      case Up:
        {
          if(position.y - dist < positionStart.y - buttonOffset)
          {
            moveAnimation(0.0f, -(positionStart.y - buttonOffset - position.y));
            animStage=animStages::turnedOff;
            flags = (flags & visible) ?  (flags ^ visible ) : visible;
          }
          else
          {
            moveAnimation(0.0f, -dist);
          }
        }break;
      case Left:
        {
          if(position.x - dist < positionStart.x - buttonOffset)
          {
            moveAnimation(-(positionStart.x - buttonOffset - position.x), 0.0f);
            animStage=animStages::turnedOff;
            flags = (flags & visible) ?  (flags ^ visible ) : visible;
          }
          else
          {
            moveAnimation(-dist, 0.0f);
          }
        }break;
      case Down:
        {
          if(position.y + dist > positionStart.y + buttonOffset)
          {
            moveAnimation(0.0f, positionStart.y - buttonOffset - position.y);
            animStage=animStages::turnedOff;
            flags = (flags & visible) ?  (flags ^ visible ) : visible;
          }
          else
          {
            moveAnimation(0.0f, dist);
          }
        }break;
      case Right:
        {
          if(position.x + dist > positionStart.x + buttonOffset)
          {
            moveAnimation(positionStart.x + buttonOffset - position.x, 0.0f);
            animStage=animStages::turnedOff;
            flags = (flags & visible) ?  (flags ^ visible ) : visible;
          }
          else
          {
            moveAnimation(dist, 0.0f);
          }
        }break;
        default:
        break;
      }
    }
  }
}

//-----------------------------------------------------------------------------------------------------------
