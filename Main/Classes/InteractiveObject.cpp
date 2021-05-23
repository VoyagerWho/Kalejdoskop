#include "InteractiveObject.h"

sf::Font InteractiveObject::font;


InteractiveObject::InteractiveObject(const sf::Vector2f& newSize)
:size(newSize), position(sf::Vector2f(0.0f, 0.0f)),
 origin(sf::Vector2f(0.0f, 0.0f)), scaleVal(sf::Vector2f(1.0f, 1.0f)), rotation(0.0f),
 labelOffset(sf::Vector2f(0.0f, 0.0f))
{
  //ctor

  font.loadFromFile("Files/defaultFont.ttf");

  activeZone.setSize(size);


  label.setFont(font);
  label.setString("InterObject");
  label.setCharacterSize(10);
  label.setFillColor(sf::Color::Black);
  label.setPosition(sf::Vector2f(size.x/2, size.y/2));
  labelOffset=sf::Vector2f(0.0f, 0.0f);
  alignLabel();

  flags = visible | active | showLabel;
}
InteractiveObject::InteractiveObject(const sf::Vector2f& pos, const sf::Vector2f& newSize)
:size(newSize), position(pos),
 origin(sf::Vector2f(0.0f, 0.0f)), scaleVal(sf::Vector2f(1.0f, 1.0f)), rotation(0.0f),
 labelOffset(sf::Vector2f(0.0f, 0.0f))
{
  //ctor

  font.loadFromFile("Files/defaultFont.ttf");

  activeZone.setSize(size);
  activeZone.setPosition(position);

  label.setFont(font);
  label.setString("InterObject");
  label.setCharacterSize(10);
  label.setFillColor(sf::Color::Black);
  label.setPosition(sf::Vector2f(position.x + size.x/2, position.y + size.y/2));
  labelOffset=sf::Vector2f(0.0f, 0.0f);
  alignLabel();

  flags = visible | active | showLabel;
}

InteractiveObject::~InteractiveObject()
{
  //dtor
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setSize(const sf::Vector2f& val)
{
  size=val;
  activeZone.setSize(size);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Vector2f InteractiveObject::getSize() const
{
  return size;
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setPosition(const sf::Vector2f& val)
{
  position=val;
  activeZone.setPosition(position);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Vector2f InteractiveObject::getPosition() const
{
  return position;
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setOrigin(const sf::Vector2f& val)
{
  origin=val;
  activeZone.setOrigin(origin);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Vector2f InteractiveObject::getOrigin() const
{
  return origin;
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setScale(const sf::Vector2f& val)
{
  scaleVal=val;
  activeZone.setScale(scaleVal);
  label.setScale(scaleVal);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Vector2f InteractiveObject::getScale() const
{
  return scaleVal;
}
//-----------------------------------------------------------------------------------------------------------

// Don't work
//void InteractiveObject::setRotation(const float& angle)
//{
//  rotation=angle;
//  activeZone.setRotation(angle);
//  label.setRotation(angle);
//  sf::Vector2f arm = label.getPosition()-position;
//  if((arm.x != 0.0f) && (arm.y != 0.0f))
//  {
//    float armAngle = atan2(arm.y, arm.x);
//    float radius = lengthVector2(arm);
//    label.setPosition(position.x + radius*cos(RADIANS(angle)-armAngle),
//                      position.y + radius*sin(RADIANS(angle)-armAngle));
//  }
//}
//-----------------------------------------------------------------------------------------------------------
//
//float InteractiveObject::getRotation() const
//{
//  return rotation;
//}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setFillColor(const sf::Color& color)
{
  activeZone.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color InteractiveObject::getFillColor() const
{
  return activeZone.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

  void InteractiveObject::setOutlineColor(const sf::Color& color)
{
  activeZone.setOutlineColor(color);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color InteractiveObject::getOutlineColor() const
{
  return activeZone.getOutlineColor();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setOutlineThickness(const float& val)
{
  activeZone.setOutlineThickness(val);
}
//-----------------------------------------------------------------------------------------------------------

float InteractiveObject::getOutlineThickness() const
{
  return activeZone.getOutlineThickness();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelCharacterSize(const unsigned& val)
{
  label.setCharacterSize(val);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

unsigned InteractiveObject::getLabelCharacterSize() const
{
  return label.getCharacterSize();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelFillColor(const sf::Color& val)
{
  label.setFillColor(val);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color InteractiveObject::getLabelFillColor() const
{
  return label.getFillColor();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelOutlineColor(const sf::Color& val)
{
  label.setOutlineColor(val);
}
//-----------------------------------------------------------------------------------------------------------

sf::Color InteractiveObject::getLabelOutlineColor() const
{
  return label.getOutlineColor();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelOutlineThickness(const float& val)
{
  label.setOutlineThickness(val);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

float InteractiveObject::getLabelOutlineThickness() const
{
  return label.getOutlineThickness();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelString(const sf::String& val)
{
  label.setString(val);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::String InteractiveObject::getLabelString() const
{
  return label.getString();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelStyle(const sf::Uint32& val)
{
  label.setStyle(val);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Uint32 InteractiveObject::getLabelStyle() const
{
  return label.getStyle();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelOffset(const sf::Vector2f& val)
{
  labelOffset=val;
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Vector2f InteractiveObject::getLabelOffset() const
{
  return labelOffset;
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::setLabelRotation(const float& val)
{
  label.setRotation(val);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

float InteractiveObject::getLabelRotation() const
{
  return label.getRotation();
}
//-----------------------------------------------------------------------------------------------------------
void InteractiveObject::setLabelScale(const sf::Vector2f& val)
{
  label.setScale(val);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

sf::Vector2f InteractiveObject::getLabelScale() const
{
  return label.getScale();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::move(const float& offsetX, const float& offsetY)
{
  position.x+=offsetX;
  position.y+=offsetY;
  activeZone.move(offsetX, offsetY);
  label.move(offsetX, offsetY);
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::move(const sf::Vector2f& offset)
{
  position+=offset;
  activeZone.move(offset);
  label.move(offset);
}
//-----------------------------------------------------------------------------------------------------------

//void InteractiveObject::rotate(const float& angle)
//{
//  rotation+=angle;
//  activeZone.rotate(angle);
//  label.rotate(angle);
//  sf::Vector2f arm = label.getPosition()-position;
//  if((arm.x != 0.0f) && (arm.y != 0.0f))
//  {
//    float armAngle = atan2(arm.y, arm.x);
//    float radius = lengthVector2(arm);
//    label.setPosition(position.x + radius*cos(armAngle+RADIANS(angle)),
//                      position.y + radius*sin(armAngle+RADIANS(angle)));
//  }
//
//}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::scale(const float& factorX, const float& factorY)
{
  scaleVal.x*=factorX;
  scaleVal.y*=factorY;
  activeZone.scale(factorX, factorY);
  label.scale(factorX, factorY);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::scale(const sf::Vector2f& factor)
{
  scaleVal.x*=factor.x;
  scaleVal.y*=factor.y;
  activeZone.scale(factor);
  label.scale(factor);
  alignLabel();
}
//-----------------------------------------------------------------------------------------------------------

void InteractiveObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(flags & visible)
  {
    target.draw(activeZone, states);
    if(flags & showLabel)
      target.draw(label, states);
  }

}
//-----------------------------------------------------------------------------------------------------------
void InteractiveObject::update(const float& deltaTime)
{
  // for animations and other time based features
}

//-----------------------------------------------------------------------------------------------------------
bool InteractiveObject::isInActiveZone(const sf::Vector2f& pos)
{
  if((pos.x >= position.x - origin.x)
     && (pos.x <= position.x - origin.x + size.x)
     && (pos.y >= position.y - origin.y)
     && (pos.y <= position.y - origin.y + size.y))
  {
    return true;
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------------
void InteractiveObject::alignLabel()
{
  label.setOrigin(label.getLocalBounds().width/2.0f + label.getLocalBounds().left,
                  label.getLocalBounds().height/2.0f + label.getLocalBounds().top);
  label.setPosition(sf::Vector2f((position.x-origin.x) + size.x/2*scaleVal.x,
                                 (position.y-origin.y) + size.y/2*scaleVal.y));
  label.move(labelOffset);
}
//-----------------------------------------------------------------------------------------------------------










