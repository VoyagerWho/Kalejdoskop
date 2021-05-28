#include "Scrollbar.h"

Scrollbar::Scrollbar(double smin, double smax)
:InteractiveObject(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 10.0f)), valmin(smin), valmax(smax), scrollVal(valmin)
{
  //ctor
  scroll = sf::RectangleShape(sf::Vector2f(3.0f, 10.0f));
  scroll.setFillColor(sf::Color::White);
  scroll.setOutlineThickness(1.0f);
  scroll.setOutlineColor(sf::Color(150,150,150));
  scroll.setOrigin(1.5f, 0.0f);
  scroll.setPosition(sf::Vector2f(position.x + (size.x)*(scrollVal - valmin)/(valmax - valmin), position.y));
  label.setString("Scrollbar");
  alignLabel();
  activeZone.setFillColor(sf::Color(200, 200, 200));
  scroll.setOutlineThickness(1.0f);
  scroll.setOutlineColor(sf::Color(100,100,100));
}
//-----------------------------------------------------------------------------------------------------------

Scrollbar::~Scrollbar()
{
  //dtor
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::setMin(const double& val)
{
  valmin=val;
  scrollVal = scrollVal < valmin ? valmin : scrollVal;
  scroll.setPosition(sf::Vector2f(position.x + (size.x)*(scrollVal - valmin)/(valmax - valmin), position.y));
}
//-----------------------------------------------------------------------------------------------------------

double Scrollbar::getMin() const
{
  return valmin;
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::setMax(const double& val)
{
  valmax=val;
  scrollVal = scrollVal > valmax ? valmax : scrollVal;
  scroll.setPosition(sf::Vector2f(position.x + (size.x)*(scrollVal - valmin)/(valmax - valmin), position.y));
}
//-----------------------------------------------------------------------------------------------------------

double Scrollbar::getMax() const
{
  return valmax;
}
//-----------------------------------------------------------------------------------------------------------

double Scrollbar::getValue() const
{
  return scrollVal;
}
//-----------------------------------------------------------------------------------------------------------


void Scrollbar::setSize(const sf::Vector2f& val)
{
  InteractiveObject::setSize(val);
  scroll.setSize(sf::Vector2f(3.0, size.y));
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::setPosition(const sf::Vector2f& val)
{
  InteractiveObject::setPosition(val);
  double ofFromMin = (size.x)*(scrollVal - valmin)/(valmax - valmin);
  scroll.setPosition(position.x+ofFromMin, position.y);
}
//-----------------------------------------------------------------------------------------------------------
void Scrollbar::setPosition_ver2(const sf::Vector2f& val)
{
  InteractiveObject::setPosition(val);
  double ofFromMin = (size.x)*(scrollVal - valmin)/(valmax - valmin)+(valmax - valmin)/2;
  scroll.setPosition(position.x+ofFromMin, position.y);
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::setScale(const sf::Vector2f& val)
{
  InteractiveObject::setScale(val);
  scroll.setScale(scaleVal);
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::setFillColorScroll(const sf::Color& color)
{
  scroll.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color Scrollbar::getFillColorScroll() const
{
  return scroll.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::move(const float& offsetX, const float& offsetY)
{
  InteractiveObject::move(offsetX, offsetY);
  scroll.move(offsetX, offsetY);
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::move(const sf::Vector2f& offset)
{
  InteractiveObject::move(offset);
  scroll.move(offset);
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::scale(const float& factorX, const float& factorY)
{
  InteractiveObject::scale(factorX, factorY);
  scroll.scale(factorX, factorY);
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::scale(const sf::Vector2f& factor)
{
  InteractiveObject::scale(factor);
  scroll.scale(factor);
}
//-----------------------------------------------------------------------------------------------------------

void Scrollbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(flags & visible)
  {
    target.draw(activeZone, states);
    target.draw(scroll, states);
    if(flags & showLabel)
      target.draw(label, states);
  }
}
//-----------------------------------------------------------------------------------------------------------
