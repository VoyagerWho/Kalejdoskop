#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "InteractiveObject.h"


class Scrollbar : public InteractiveObject
{
  public:
    /** Default constructor */
    Scrollbar(double smin=0.0, double smax=100.0);
    /** Default destructor */
    virtual ~Scrollbar();

    //setters and getters

    void setSize(const sf::Vector2f&);

    void setMin(const double&);
    double getMin() const;

    void setMax(const double&);
    double getMax() const;

    double getValue() const;

    void setPosition(const sf::Vector2f&);
    void setPosition_ver2(const sf::Vector2f&);

    void setScale(const sf::Vector2f&);



    void setFillColorScroll(const sf::Color&);
    sf::Color getFillColorScroll() const;

    void move(const float&, const float&);
    void move(const sf::Vector2f&);
    void scale(const float&, const float&);
    void scale(const sf::Vector2f&);


    // misc
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool onHover(const sf::Event&);
    bool onClick(const sf::Event&);


  protected:
    sf::RectangleShape scroll;
    double valmin;
    double valmax;
    double scrollVal;

  private:
};

#endif // SCROLLBAR_H
