#include "AnimatedButton.h"
#include <iostream>


AButtonCircle::AButtonCircle(const float& newRadius)
: InteractiveObject::InteractiveObject(sf::Vector2f(2*newRadius, 2*newRadius)), radius(newRadius)
{
  //ctor

  label.setString("AB_Circle");
  InteractiveObject::setOrigin(sf::Vector2f(radius, radius));

  alignLabel();

  foreground.setRadius(radius);
  foreground.setOrigin(radius, radius);
  foreground.setPosition(position);

  background.setRadius(radius);
  background.setOrigin(radius, radius);
  background.setPosition(position);

  animStage = turnedOff;
}
AButtonCircle::AButtonCircle(const sf::Vector2f& pos, const float& newRadius)
: InteractiveObject::InteractiveObject(pos, sf::Vector2f(2*newRadius, 2*newRadius)), radius(newRadius)
{
  //ctor

  label.setString("AB_Circle");
  InteractiveObject::setOrigin(sf::Vector2f(radius, radius));
  alignLabel();

  foreground.setRadius(radius);
  foreground.setOrigin(radius, radius);
  foreground.setPosition(position);

  background.setRadius(radius);
  background.setOrigin(radius, radius);
  background.setPosition(position);

  animStage = turnedOff;
}

AButtonCircle::~AButtonCircle()
{
  //dtor
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setRadius(const float& val)
{
  radius=val;
  foreground.setRadius(radius);
  background.setRadius(radius);
  InteractiveObject::setSize(sf::Vector2f(2*radius, 2*radius));
}
//-----------------------------------------------------------------------------------------------------------

float AButtonCircle::getRadius() const
{
  return radius;
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setPosition(const sf::Vector2f& val)
{
  InteractiveObject::setPosition(val);
  foreground.setPosition(position);
  background.setPosition(position);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setOrigin(const sf::Vector2f& val)
{
  InteractiveObject::setOrigin(val);
  foreground.setOrigin(origin);
  background.setOrigin(origin);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setScale(const sf::Vector2f& val)
{
  InteractiveObject::setScale(val);
  foreground.setScale(scaleVal);
  background.setScale(scaleVal);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setFillColorFg(const sf::Color& color)
{
  foreground.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color AButtonCircle::getFillColorFg() const
{
  return foreground.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setFillColorBg(const sf::Color& color)
{
  background.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color AButtonCircle::getFillColorBg() const
{
  return background.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setOutlineColor(const sf::Color& color)
{
  foreground.setOutlineColor(color);
  background.setOutlineColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color AButtonCircle::getOutlineColor() const
{
  return foreground.getOutlineColor();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setOutlineThickness(const float& val)
{
  foreground.setOutlineThickness(val);
  background.setOutlineThickness(val);
}
//-----------------------------------------------------------------------------------------------------------

float AButtonCircle::getOutlineThickness() const
{
  return foreground.getOutlineThickness();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::move(const float& offsetX, const float& offsetY)
{
  InteractiveObject::move(offsetX, offsetY);
  foreground.move(offsetX, offsetY);
  background.move(offsetX, offsetY);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::move(const sf::Vector2f& offset)
{
  InteractiveObject::move(offset);
  foreground.move(offset);
  background.move(offset);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::scale(const float& factorX, const float& factorY)
{
  InteractiveObject::scale(factorX, factorY);
  foreground.scale(factorX, factorY);
  background.scale(factorX, factorY);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::scale(const sf::Vector2f& factor)
{
  InteractiveObject::scale(factor);
  foreground.scale(factor);
  background.scale(factor);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(flags & visible)
  {
    if(flags & showActiveZone)
      target.draw(activeZone, states);
    target.draw(background, states);
    target.draw(foreground, states);
    if(flags & showLabel)
      target.draw(label, states);
  }
}
//-----------------------------------------------------------------------------------------------------------
void AButtonCircle::update(const float& deltaTime)
{
  if(flags & active)
  {
    sf::Color color = foreground.getFillColor();
    if(animStage == animStages::turningOn)
    {
      color.a = color.a >= 230 ? 255 : color.a+25;
      if(color.a == 255)
        animStage = animStages::turnedOn;
    }
    else if(animStage == animStages::turningOff)
    {
      color.a = color.a <= 25 ? 0 : color.a-25;
      if(color.a == 0)
        animStage = animStages::turnedOff;
    }
    foreground.setFillColor(color);
  }
}
//-----------------------------------------------------------------------------------------------------------
bool AButtonCircle::loadTextureFromFile(const std::string& filename)
{
  bool result = texture.loadFromFile(filename);
  if(result)
    setTex();
  return result;
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setTextureRect(const sf::IntRect& rect)
{
  foreground.setTextureRect(rect);
  foreground.setFillColor(sf::Color(255,255,255,0));
  background.setTextureRect(sf::IntRect(rect.left, rect.height, rect.width, rect.height));
}
//-----------------------------------------------------------------------------------------------------------

void AButtonCircle::setTex()
{
  /**
    Use this function at the end of creating buttons to initialize end texture pointer
  **/
  foreground.setTexture(&texture);
  background.setTexture(&texture);
}

//-----------------------------------------------------------------------------------------------------------
bool AButtonCircle::isInActiveZone(const sf::Vector2f& pos)
{
  if((pos.x >= position.x - origin.x)
     && (pos.x <= position.x - origin.x + size.x)
     && (pos.y >= position.y - origin.y)
     && (pos.y <= position.y - origin.y + size.y))
  {
    if(dist2D(pos, position) <= radius)
      return true;
  }
  return false;
}

//-----------------------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------

AButtonRectangle::AButtonRectangle(const sf::Vector2f& newSize)
: InteractiveObject::InteractiveObject(newSize)
{
  //ctor

  label.setString("AB_Box");
  InteractiveObject::setOrigin(sf::Vector2f(size.x/2.0f, size.x/2.0f));
  alignLabel();

  foreground.setSize(size);
  foreground.setOrigin(sf::Vector2f(size.x/2.0f, size.x/2.0f));
  foreground.setPosition(position);

  background.setSize(size);
  foreground.setOrigin(sf::Vector2f(size.x/2.0f, size.x/2.0f));
  background.setPosition(position);

  animStage = turnedOff;
}
AButtonRectangle::AButtonRectangle(const sf::Vector2f& pos, const sf::Vector2f& newSize)
: InteractiveObject::InteractiveObject(pos, newSize)
{
  //ctor

  label.setString("AB_Box");
  InteractiveObject::setOrigin(sf::Vector2f(size.x/2.0f, size.x/2.0f));
  alignLabel();

  foreground.setSize(size);
  foreground.setOrigin(sf::Vector2f(size.x/2.0f, size.x/2.0f));
  foreground.setPosition(position);

  background.setSize(size);
  foreground.setOrigin(sf::Vector2f(size.x/2.0f, size.x/2.0f));
  background.setPosition(position);

  animStage = turnedOff;
}

AButtonRectangle::~AButtonRectangle()
{
  //dtor
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setSize(const sf::Vector2f& val)
{
  InteractiveObject::setSize(val);
  foreground.setSize(size);
  background.setSize(size);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setPosition(const sf::Vector2f& val)
{
  InteractiveObject::setPosition(val);
  foreground.setPosition(position);
  background.setPosition(position);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setOrigin(const sf::Vector2f& val)
{
  InteractiveObject::setOrigin(val);
  foreground.setOrigin(origin);
  background.setOrigin(origin);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setScale(const sf::Vector2f& val)
{
  InteractiveObject::setScale(val);
  foreground.setScale(scaleVal);
  background.setScale(scaleVal);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setFillColorFg(const sf::Color& color)
{
  foreground.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color AButtonRectangle::getFillColorFg() const
{
  return foreground.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setFillColorBg(const sf::Color& color)
{
  background.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color AButtonRectangle::getFillColorBg() const
{
  return background.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setOutlineColor(const sf::Color& color)
{
  foreground.setOutlineColor(color);
  background.setOutlineColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color AButtonRectangle::getOutlineColor() const
{
  return foreground.getOutlineColor();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setOutlineThickness(const float& val)
{
  foreground.setOutlineThickness(val);
  background.setOutlineThickness(val);
}
//-----------------------------------------------------------------------------------------------------------

float AButtonRectangle::getOutlineThickness() const
{
  return foreground.getOutlineThickness();
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::move(const float& offsetX, const float& offsetY)
{
  InteractiveObject::move(offsetX, offsetY);
  foreground.move(offsetX, offsetY);
  background.move(offsetX, offsetY);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::move(const sf::Vector2f& offset)
{
  InteractiveObject::move(offset);
  foreground.move(offset);
  background.move(offset);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::scale(const float& factorX, const float& factorY)
{
  InteractiveObject::scale(factorX, factorY);
  foreground.scale(factorX, factorY);
  background.scale(factorX, factorY);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::scale(const sf::Vector2f& factor)
{
  InteractiveObject::scale(factor);
  foreground.scale(factor);
  background.scale(factor);
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(flags & visible)
  {
    if(flags & showActiveZone)
      target.draw(activeZone, states);
    target.draw(background, states);
    target.draw(foreground, states);
    if(flags & showLabel)
      target.draw(label, states);
  }
}
//-----------------------------------------------------------------------------------------------------------
void AButtonRectangle::update(const float& deltaTime)
{
  if(flags & active)
  {
    sf::Color color = foreground.getFillColor();
    if(animStage == animStages::turningOn)
    {
      color.a = color.a >= 230 ? 255 : color.a+25;
      if(color.a == 255)
        animStage = animStages::turnedOn;
    }
    else if(animStage == animStages::turningOff)
    {
      color.a = color.a <= 25 ? 0 : color.a-25;
      if(color.a == 0)
        animStage = animStages::turnedOff;
    }
    foreground.setFillColor(color);
  }
}
//-----------------------------------------------------------------------------------------------------------

bool AButtonRectangle::loadTextureFromFile(const std::string& filename)
{
  bool result = texture.loadFromFile(filename);
  setTex();
  return result;
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setTextureRect(const sf::IntRect& rect)
{
  foreground.setTextureRect(rect);
  foreground.setFillColor(sf::Color(255,255,255,0));
  background.setTextureRect(sf::IntRect(rect.left, rect.height, rect.width, rect.height));
}
//-----------------------------------------------------------------------------------------------------------

void AButtonRectangle::setTex()
{
  /**
    Use this function at the end of creating buttons to initialize end texture pointer
  **/
  foreground.setTexture(&texture);
  background.setTexture(&texture);
}

//-----------------------------------------------------------------------------------------------------------









