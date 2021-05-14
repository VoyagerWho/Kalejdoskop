#include "Interpolate.h"

sf::Vector2f translate(sf::Vector2f posDis, Container& ds)
{
	sf::Vector2f middleDis(ds.dw/2.0, ds.dh/2.0);
	//sf::Vector2f middleTex(ds.tw/2.0, ds.th/2.0);
	double theta = 180.0/double(ds.NoAxis);
	sf::Vector2f ofcenter = posDis-middleDis;
	double phi = atan2(ofcenter.y, ofcenter.x);
	unsigned part = int(phi/theta);
	double radiusD = sqrt(ofcenter.y*ofcenter.y+ ofcenter.x*ofcenter.x);
	double radiusT = radiusD;//*ds.tw/ds.dw;
	double alpha;
	if(part & 1)
	{
		alpha = phi - part*theta;
	}
	else
	{
		alpha = (part+1)*theta - phi;
	}
	return sf::Vector2f(radiusT*cos(ds.angle+alpha), radiusT*sin(ds.angle+alpha))+middleDis+sf::Vector2f(1.0, 1.0);
}

sf::Color interpolateBL(sf::Vector2f pos, Container& ds)
{
  int x1 = int(pos.x);
  int y1 = int(pos.y);
  x1 = x1<0 ? 0 : x1;
  y1 = y1<0 ? 0 : y1;
  x1 = x1>=ds.tw ? ds.tw-2 : x1;
  y1 = y1>=ds.th ? ds.th-2 : y1;
  int x2 = x1+1;
  int y2 = y1+1;
  double decX = pos.x - float(x1);
  double decY = pos.y - float(y1);

  sf::Color a11, a12, a21, a22;
  a11 = ds.oryginal.getPixel(x1, y1);
  a12 = ds.oryginal.getPixel(x2, y1);
  a21 = ds.oryginal.getPixel(x1, y2);
  a22 = ds.oryginal.getPixel(x2, y2);

  sf::Color result;
  result.r=(1-decY)*(1-decX)*a11.r + (1-decY)*(decX)*a12.r + (decY)*(1-decX)*a21.r + (decY)*(decX)*a22.r;
  result.g=(1-decY)*(1-decX)*a11.g + (1-decY)*(decX)*a12.g + (decY)*(1-decX)*a21.g + (decY)*(decX)*a22.g;
  result.b=(1-decY)*(1-decX)*a11.b + (1-decY)*(decX)*a12.b + (decY)*(1-decX)*a21.b + (decY)*(decX)*a22.b;
  return result;
}

void Container::update()
{
  if(needUpdate)
  {
    sf::Color tmp;
    for(unsigned i=0;i<dh;i++)
    {
      for(unsigned j=0;j<dw;j++)
      {
        tmp = interpolateBL(translate(sf::Vector2f(j, i), *this), *this);
        piksele[4*(i*dw+j)]=tmp.r;
        piksele[4*(i*dw+j)+1]=tmp.g;
        piksele[4*(i*dw+j)+2]=tmp.b;
      }
    }
    needUpdate=false;
    display.update(piksele);
  }
}
