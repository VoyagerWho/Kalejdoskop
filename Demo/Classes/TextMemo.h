#ifndef TEXTMEMO_H
#define TEXTMEMO_H

#define CHAR_WIDTH_MULTIPLIER double(9864)/double(16384)
#include <SFML/Graphics.hpp>
#include <vector>


class TextMemo : public sf::Drawable
{
  public:
    TextMemo();
    virtual ~TextMemo();

    sf::Vector2f GetPosition() const;

    void SetPosition(const sf::Vector2f&);
    void SetCharacterSize(const unsigned int&);
    void SetLength(const float&);
    void SetTextColor(const sf::Color&);
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
    unsigned maxStringLength;
    unsigned maxLinesNumber;
    unsigned cursorPos;

    float deltaTime;

    sf::Vector2f editSize;
    sf::Text text;
    std::vector<sf::String>Strings;
    sf::RectangleShape background;
    sf::RectangleShape cursor;
    sf::Font font;
};

#endif // TEXTMEMO_H
