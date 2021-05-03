#ifndef ANIMATEDBUTTON_H
#define ANIMATEDBUTTON_H

#include "InteractiveObject.h"

class AButtonCircle : public InteractiveObject
{
  public:
    // construction
    AButtonCircle(const float& newRadius=0.0f);

    AButtonCircle(const sf::Vector2f& pos, const float& newRadius);

    virtual ~AButtonCircle();

    // setters and getters

    void setRadius(const float&);
    float getRadius() const;

    void setPosition(const sf::Vector2f&);

    void setOrigin(const sf::Vector2f&);

    void setScale(const sf::Vector2f&);

    void setFillColorFg(const sf::Color&);
    sf::Color getFillColorFg() const;

    void setFillColorBg(const sf::Color&);
    sf::Color getFillColorBg() const;

    void setOutlineColor(const sf::Color&);
    sf::Color getOutlineColor() const;

    void setOutlineThickness(const float&);
    float getOutlineThickness() const;

    void move(const float&, const float&);
    void move(const sf::Vector2f&);
    void scale(const float&, const float&);
    void scale(const sf::Vector2f&);


    // misc
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const float&);

    bool onHover(const sf::Event&);
    bool onClick(const sf::Event&);

    bool loadTextureFromFile(const std::string&);
    void setTextureRect(const sf::IntRect&);
    void setTex();

    enum flag {showActiveZone=8};


  protected:
    float radius;
    sf::CircleShape foreground;
    sf::CircleShape background;
    sf::Texture texture;

    bool isInActiveZone(const sf::Vector2f&);

    // for animations & events

    //misc

  private:
};


class AButtonRectangle : public InteractiveObject
{
  public:
    // construction
    AButtonRectangle(const sf::Vector2f& newSize=sf::Vector2f(0.0f, 0.0f));

    AButtonRectangle(const sf::Vector2f& pos, const sf::Vector2f& newSize);

    virtual ~AButtonRectangle();

    // setters and getters

    void setSize(const sf::Vector2f&);

    void setPosition(const sf::Vector2f&);

    void setOrigin(const sf::Vector2f&);

    void setScale(const sf::Vector2f&);

    void setFillColorFg(const sf::Color&);
    sf::Color getFillColorFg() const;

    void setFillColorBg(const sf::Color&);
    sf::Color getFillColorBg() const;

    void setOutlineColor(const sf::Color&);
    sf::Color getOutlineColor() const;

    void setOutlineThickness(const float&);
    float getOutlineThickness() const;

    void move(const float&, const float&);
    void move(const sf::Vector2f&);
    void scale(const float&, const float&);
    void scale(const sf::Vector2f&);


    // misc
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const float&);

    bool onHover(const sf::Event&);
    bool onClick(const sf::Event&);

    bool loadTextureFromFile(const std::string&);
    void setTextureRect(const sf::IntRect&);
    void setTex();

    enum flag {showActiveZone=8};


  protected:
    sf::RectangleShape foreground;
    sf::RectangleShape background;
    sf::Texture texture;

    // for animations & events

    //misc

  private:
};
#endif // ANIMATEDBUTTON_H
