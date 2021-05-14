#include "TextEdit.h"

TextEdit::TextEdit()
{
  //ctor
  font.loadFromFile("C:/Windows/Fonts/monos.ttf");

  text = sf::Text("Edit", font);
  text.setOrigin(-5.0f, 0.0f);
  text.setPosition(0.0f, 0.0f);
  text.setFillColor(sf::Color::Black);

  background.setPosition(0.0f, 0.0f);
  background.setSize(sf::Vector2f(10.0f*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER + 10.0f,text.getCharacterSize()*1.3f));
  background.setOutlineThickness(1.0f);
  background.setOutlineColor(sf::Color::Blue);

  cursor.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 2.0f, text.getLineSpacing());
  cursor.setSize(sf::Vector2f(1.0f, text.getCharacterSize()*1.25f));
  cursor.setFillColor(sf::Color::Black);
  cursorPos = text.getString().getSize();

  maxStringLength = 10;

  deltaTime = 0.0f;
  active = false;
  visible = true;
}

TextEdit::TextEdit(const sf::Vector2f& position, const float& length)
{
  //ctor
  font.loadFromFile("C:/Windows/Fonts/monos.ttf");
  text = sf::Text("Edit", font);
  text.setOrigin(-5.0f, 0.0f);
  text.setPosition(position);
  text.setFillColor(sf::Color::Black);

  maxStringLength = int(length / float(text.getCharacterSize()) / CHAR_WIDTH_MULTIPLIER);

  background.setPosition(position);
  background.setSize(sf::Vector2f((length-10.0f) > maxStringLength*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER
                                  ? length : maxStringLength*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER + 10.0f,
                                  text.getCharacterSize()*1.3f));
  background.setOutlineThickness(1.0f);
  background.setOutlineColor(sf::Color::Blue);

  cursor.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 2.0f, position.y+text.getLineSpacing());
  cursor.setSize(sf::Vector2f(1.0f, text.getCharacterSize()*1.25f));
  cursor.setFillColor(sf::Color::Black);
  cursorPos = text.getString().getSize();

  deltaTime = 0.0f;
  active = false;
  visible = true;
}

TextEdit::TextEdit(const sf::Vector2f& position, const unsigned int& charNumber)
:maxStringLength(charNumber)
{
  //ctor
  font.loadFromFile("C:/Windows/Fonts/monos.ttf");
  text = sf::Text("Edit", font);
  text.setOrigin(-5.0f, 0.0f);
  text.setPosition(position);
  text.setFillColor(sf::Color::Black);

  background.setPosition(position);
  background.setSize(sf::Vector2f(maxStringLength*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER + 10.0f,text.getCharacterSize()*1.3f));
  background.setOutlineThickness(1.0f);
  background.setOutlineColor(sf::Color::Blue);

  cursor.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 2.0f, position.y+text.getLineSpacing());
  cursor.setSize(sf::Vector2f(1.0f, text.getCharacterSize()*1.25f));
  cursor.setFillColor(sf::Color::Black);
  cursorPos = text.getString().getSize();

  deltaTime = 0.0f;
  active = false;
  visible = true;
}

TextEdit::~TextEdit()
{
  //dtor
}
//-----------------------------------------------------------------------------------------------------------
sf::Vector2f TextEdit::GetPosition() const
{
  return text.getPosition();
}
//-----------------------------------------------------------------------------------------------------------
sf::String TextEdit::GetString() const
{
  return text.getString();
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetPosition(const sf::Vector2f& position)
{
  text.setPosition(position);
  background.setPosition(position);
  cursor.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 2.0f, position.y+text.getLineSpacing());
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetCharacterSize(const unsigned int& Size)
{
  text.setCharacterSize(Size);

  float length = background.getSize().x;
  background.setSize(sf::Vector2f(length,text.getCharacterSize()*1.3f));
  cursor.setSize(sf::Vector2f(1.0f, text.getCharacterSize()*1.25f));
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetLength(const float& length)
{
  background.setSize(sf::Vector2f(length, background.getSize().y));
  maxStringLength = int(length / float(text.getCharacterSize()) / CHAR_WIDTH_MULTIPLIER);
  if(text.getString().getSize()>maxStringLength)
  {
    sf::String bufor = text.getString();
    bufor.erase(bufor.getSize()-1,text.getString().getSize()-maxStringLength);
    text.setString(bufor);
  }
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetTextColor(const sf::Color& color)
{
  text.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetBackgroundFillColor(const sf::Color& color)
{
  background.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetBackgroundOutlineColor(const sf::Color& color)
{
  background.setOutlineColor(color);
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetBackgroundTexture(const sf::Texture* texture)
{
  background.setTexture(texture);
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetTextString(const char* vString)
{
  text.setString(vString);
  cursor.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width + 2.0f,text.getPosition().y+text.getLineSpacing());
  cursorPos = text.getString().getSize();
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::SetCursorColor(const sf::Color& color)
{
  cursor.setFillColor(color);
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(visible)
  {
    target.draw(background, states);
    target.draw(text, states);
    if(active)
      target.draw(cursor, states);
  }
}
//-----------------------------------------------------------------------------------------------------------
bool TextEdit::isInActiveZone(const  sf::Vector2f& mousePos)
{
  if(visible)
  {
    if((mousePos.x >= background.getPosition().x) && (mousePos.x <= background.getPosition().x + background.getSize().x)
    && (mousePos.y >= background.getPosition().y) && (mousePos.y <= background.getPosition().y + background.getSize().y))
    {
      return true;
    }
  }
  return false;
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::addCharacter(const char& c)
{
  if((c >= 32) && (c<=126) && (text.getString().getSize()<maxStringLength))
  {
    if(cursorPos == text.getString().getSize())
    {
      text.setString(text.getString() + c);
    }
    else
    {
      sf::String bufor = text.getString();
      bufor.insert(cursorPos, c);
      text.setString(bufor);
    }
    moveCursor(1);
  }
  else if((c == 8) && (!text.getString().isEmpty()))
  {
    if(cursorPos == text.getString().getSize())
    {
      sf::String bufor = text.getString();
      bufor.erase(bufor.getSize()-1);
      text.setString(bufor);
    }
    else
    {
      if(cursorPos)
      {
        sf::String bufor = text.getString();
        bufor.erase(cursorPos-1);
        text.setString(bufor);
      }
    }
    moveCursor(-1);
  }
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::delCharacter()
{
  if(cursorPos < text.getString().getSize())
  {
    sf::String bufor = text.getString();
    bufor.erase(cursorPos);
    text.setString(bufor);
  }
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::update(const float& vDeltaTime)
{
  deltaTime += vDeltaTime;
  if(deltaTime > 0.5f)
  {
    if(cursor.getFillColor() == sf::Color::Black)
      cursor.setFillColor(sf::Color::Transparent);
    else
      cursor.setFillColor(sf::Color::Black);
    deltaTime -= 0.5f;
  }
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::moveCursor(const int& dist)
{
  if(((cursorPos > 0) && (dist < 0)) || ((cursorPos < text.getString().getSize()) && (dist > 0)))
  {
    cursorPos += dist;
    cursor.setPosition(text.getPosition().x + cursorPos*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER + 5.0f,
                      cursor.getPosition().y);
  }
}
//-----------------------------------------------------------------------------------------------------------
void TextEdit::moveCursor(const sf::Vector2f& mousePos)
{
  unsigned int length = text.getString().getSize();
  float charBegin = text.getPosition().x + 5.0f;
  if(mousePos.x < charBegin + text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER*0.5f)
    moveCursor(-cursorPos);
  else if(mousePos.x > charBegin + float(length-0.5f)*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER)
  {
    cursorPos = length;
    cursor.setPosition(text.getPosition().x + cursorPos*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER + 5.0f,
                      cursor.getPosition().y);
  }
  else
  {
    for(unsigned int i=0;i<length;i++)
    {
      if((mousePos.x > charBegin + text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER*float(i + 0.5f))
         && (mousePos.x < charBegin + text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER*float(i + 1.5f)))
      {
           cursorPos = i+1;
           cursor.setPosition(text.getPosition().x + cursorPos*text.getCharacterSize()*CHAR_WIDTH_MULTIPLIER + 5.0f,
                      cursor.getPosition().y);
      }
    }
  }
}
//-----------------------------------------------------------------------------------------------------------
