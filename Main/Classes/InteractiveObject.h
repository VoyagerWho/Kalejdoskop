#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#define CHAR_WIDTH_MULTIPLIER double(9864)/double(16384)
#define PI 3.141592653589f
#define RADIANS(a) (a/180.0f*PI)

#include <SFML/Graphics.hpp>
#include "ExtraFunctions.h"

class InteractiveObject : public sf::Drawable
{
  public:
    // construction
    InteractiveObject(const sf::Vector2f& newSize=sf::Vector2f(0.0f, 0.0f));

    InteractiveObject(const sf::Vector2f& pos, const sf::Vector2f& newSize);

    virtual ~InteractiveObject();

    // setters and getters

    void setSize(const sf::Vector2f&);
    sf::Vector2f getSize() const;

    void setPosition(const sf::Vector2f&);
    sf::Vector2f getPosition() const;

    void setOrigin(const sf::Vector2f&);
    sf::Vector2f getOrigin() const;

    void setScale(const sf::Vector2f&);
    sf::Vector2f getScale() const;

//    void setRotation(const float&);
//    float getRotation() const;

    void setFillColor(const sf::Color&);
    sf::Color getFillColor() const;

    void setOutlineColor(const sf::Color&);
    sf::Color getOutlineColor() const;

    void setOutlineThickness(const float&);
    float getOutlineThickness() const;

    void setLabelCharacterSize(const unsigned&);
    unsigned getLabelCharacterSize() const;

    void setLabelFillColor(const sf::Color&);
    sf::Color getLabelFillColor() const;

    void setLabelOutlineColor(const sf::Color&);
    sf::Color getLabelOutlineColor() const;

    void setLabelOutlineThickness(const float&);
    float getLabelOutlineThickness() const;

    void setLabelString(const sf::String&);
    sf::String getLabelString() const;

    void setLabelStyle(const sf::Uint32&);
    sf::Uint32 getLabelStyle() const;

    void setLabelOffset(const sf::Vector2f&);
    sf::Vector2f getLabelOffset() const;

    void setLabelRotation(const float&);
    float getLabelRotation() const;

    void setLabelScale(const sf::Vector2f&);
    sf::Vector2f getLabelScale() const;


    void move(const float&, const float&);
    void move(const sf::Vector2f&);
//    void rotate(const float&);
    void scale(const float&, const float&);
    void scale(const sf::Vector2f&);


    // misc
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const float&);

    bool onHover(const sf::Event&);
    bool onClick(const sf::Event&);

    unsigned flags;

    enum flag {visible=1, active=2, showLabel=4};

    static sf::Font font;

  protected:
    sf::RectangleShape activeZone;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f origin;
    sf::Vector2f scaleVal;
    float rotation;
    sf::Text label;
    sf::Vector2f labelOffset;

    bool isInActiveZone(const sf::Vector2f&);

    // for animations & events
    unsigned animStage;
    enum animStages {turnedOff, turningOn, turnedOn, turningOff};

    //misc

    void alignLabel();

  private:
};

#endif // INTERACTIVEOBJECT_H
