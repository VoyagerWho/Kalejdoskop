#ifndef SIDEBARMENU_H
#define SIDEBARMENU_H

#include "AnimatedButton.h"

class SidebarMenu : public InteractiveObject
{
  public:
    SidebarMenu(sf::RenderWindow&, const unsigned&, const unsigned int& =1, const float& =20.0f, const float& =100.0f);
    virtual ~SidebarMenu();

    // setters and getters

    void setPosition(const sf::Vector2f&);
    void setPosition(sf::RenderWindow&);

    void setOrigin(const sf::Vector2f&);

    void setScale(const sf::Vector2f&);

    int getOption() const;

    void setSpacing(const float&);
    float getSpacing() const;

    void setSpeed(const float&);
    float getSpeed() const;


    void move(const float&, const float&);
    void move(const sf::Vector2f&);
    void moveAnimation(const float&, const float&);
    void scale(const float&, const float&);
    void scale(const sf::Vector2f&);


    // misc
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const float&);

    bool loadTextureFromFile(const std::string&);

    bool onHover(const sf::Event&);
    bool onClick(const sf::Event&);

    enum Side {Up=1, Left=2, Down=3, Right=4};
    enum flag {showActiveZone=8};
    std::vector<AButtonCircle> buttons;

  protected:
    int option;
    float spacing;
    float middlePoint;
    float speed;
    sf::Vector2f positionStart;
    sf::Texture texture;

    unsigned facing;

    // for animations & events

    //misc

};

#endif // SIDEBARMENU_H
