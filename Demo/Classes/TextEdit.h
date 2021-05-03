#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#define CHAR_WIDTH_MULTIPLIER double(9864)/double(16384)
#include <SFML/Graphics.hpp>

class TextEdit : public sf::Drawable
{
  public:
    TextEdit();
    TextEdit(const sf::Vector2f& position, const float& length);
    TextEdit(const sf::Vector2f& position, const unsigned int& charNumber);
    virtual ~TextEdit();

    sf::Vector2f GetPosition() const;
    sf::String GetString() const;

    void SetPosition(const sf::Vector2f&);
    void SetCharacterSize(const unsigned int&);
    void SetLength(const float&);
    void SetTextColor(const sf::Color&);
    void SetTextString(const char*);
    void SetBackgroundFillColor(const sf::Color&);
    void SetBackgroundOutlineColor(const sf::Color&);
    void SetBackgroundTexture(const sf::Texture*);
    void SetCursorColor(const sf::Color&);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool isInActiveZone(const sf::Vector2f&);
    void addCharacter(const char&);
    void delCharacter();
    void update(const float&);
    void moveCursor(const int&);
    void moveCursor(const sf::Vector2f&);
    void hideCursor();
    void showCursor();

    bool active;
    bool visible;



  protected:
    float deltaTime;

    unsigned int maxStringLength;
    unsigned int cursorPos;

    sf::Vector2f editSize;
    sf::Text text;
    sf::RectangleShape background;
    sf::RectangleShape cursor;
    sf::Font font;


};

#endif // TEXTEDIT_H
