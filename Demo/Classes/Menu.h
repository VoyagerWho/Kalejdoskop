#ifndef MENU_H
#define MENU_H

#include "AnimatedButton.h"

class Menu : public InteractiveObject
{
  public:
    Menu(const sf::Vector2f pos, const unsigned& numOfOptions, unsigned characterSize = 64);
    virtual ~Menu();

    void setPosition(const sf::Vector2f&);

    void setOrigin(const sf::Vector2f&);

    void setScale(const sf::Vector2f&);

    int getOption();

    void move(const float&, const float&);
    void move(const sf::Vector2f&);
    void scale(const float&, const float&);
    void scale(const sf::Vector2f&);


    // misc
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const float&);

    bool onHover(const sf::Event&);
    bool onClick(const sf::Event&);

    void scaleToText();

    enum flag {showActiveZone=8};

    std::vector<InteractiveObject> options;

  protected:

    int option;

};

#endif // MENU_H
