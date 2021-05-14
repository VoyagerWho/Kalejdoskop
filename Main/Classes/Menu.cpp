#include "Menu.h"

Menu::Menu(const sf::Vector2f pos, const unsigned& numOfOptions, unsigned characterSize)
:InteractiveObject(pos, sf::Vector2f(0.0f, 0.0f)), option(0)
{
  //ctor - fill with basic stuff
  label.setString("Menu");
  label.setCharacterSize(characterSize);
  for(unsigned int i=0;i<numOfOptions;i++)
  {
    options.push_back(InteractiveObject(sf::Vector2f(position.x + 10.0f, position.y + 10.0f + float(i * characterSize)),
                                        sf::Vector2f(0.0f, 0.0f)));
    options[i].setLabelCharacterSize(characterSize);
  }
}
//-----------------------------------------------------------------------------------------------------------
Menu::~Menu()
{
  //dtor
}
//-----------------------------------------------------------------------------------------------------------

void Menu::setPosition(const sf::Vector2f& val)
{
  InteractiveObject::setPosition(val);
  float offset = float(label.getCharacterSize());
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].setPosition(sf::Vector2f(position.x + 10.0f, position.y + 10.0f + offset));
    offset += float(options[i].getLabelCharacterSize());
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::setOrigin(const sf::Vector2f& val)
{
  InteractiveObject::setOrigin(val);
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].setOrigin(val);
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::setScale(const sf::Vector2f& val)
{
  InteractiveObject::setScale(val);
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].setScale(val);
  }
}
//-----------------------------------------------------------------------------------------------------------
int Menu::getOption()
{
  return option;
}

//-----------------------------------------------------------------------------------------------------------

void Menu::move(const float& offsetX, const float& offsetY)
{
  InteractiveObject::move(offsetX, offsetY);
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].move(offsetX, offsetY);
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::move(const sf::Vector2f& offset)
{
  InteractiveObject::move(offset);
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].move(offset);
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::scale(const float& factorX, const float& factorY)
{
  InteractiveObject::scale(factorX, factorY);
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].scale(factorX, factorY);
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::scale(const sf::Vector2f& factor)
{
  InteractiveObject::scale(factor);
  for(unsigned int i=0;i<options.size();i++)
  {
    options[i].scale(factor);
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(flags & visible)
  {
    InteractiveObject::draw(target, states);
    for(unsigned i=0;i<options.size();i++)
    {
      target.draw(options[i], states);
    }
  }
}
//-----------------------------------------------------------------------------------------------------------

void Menu::update(const float&)
{

}
//-----------------------------------------------------------------------------------------------------------
void Menu::scaleToText()
{
  sf::Text temp("", font);
  for(unsigned i=0;i<options.size();i++)
  {
    temp.setString(options[i].getLabelString());
    temp.setCharacterSize(options[i].getLabelCharacterSize());
    options[i].setSize(sf::Vector2f(temp.getGlobalBounds().width, temp.getGlobalBounds().height));
  }
}
//-----------------------------------------------------------------------------------------------------------







