#include "Interpolate.h"

sf::Vector2f translate(sf::Vector2f posDis, Container& ds)
{
	//std::cout<<"Calculations:"<<std::endl;
	sf::Vector2f middleDis(ds.dw/2.0, ds.dh/2.0);
	sf::Vector2f middleTex(ds.tw/2.0, ds.th/2.0);
	double theta = M_PI/double(ds.NoAxis);
	//std::cout<<"Theta: "<<theta<<std::endl;
	sf::Vector2f ofcenter = posDis-middleDis;
	double phi = atan2(ofcenter.y, ofcenter.x) + 2*M_PI;
	//std::cout<<"Phi: "<<phi<<std::endl;
	unsigned part = int(phi/theta);
	//std::cout<<"part: "<<part<<std::endl;
	double radiusD = sqrt(ofcenter.y*ofcenter.y+ ofcenter.x*ofcenter.x);
	//std::cout<<"R: "<<radiusD<<std::endl;
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
	//std::cout<<"Alpha: "<<alpha<<std::endl;
	return sf::Vector2f(radiusT*cos(ds.angle+alpha), radiusT*sin(ds.angle+alpha))+middleTex;
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
    //single thread
//    sf::Color tmp;
//    for(unsigned i=0;i<dh;i++)
//    {
//      for(unsigned j=0;j<dw;j++)
//      {
//        tmp = interpolateBL(translate(sf::Vector2f(j, i), *this), *this);
//        piksele[4*(i*dw+j)]=tmp.r;
//        piksele[4*(i*dw+j)+1]=tmp.g;
//        piksele[4*(i*dw+j)+2]=tmp.b;
//      }
//    }
//    needUpdate=false;
//    display.update(piksele);

    // multi tread
    sf::Thread th1(std::bind(updateThread, *this, 0, dh*1.0/4.0));
    sf::Thread th2(std::bind(updateThread, *this, dh*1.0/4.0, dh*2.0/4.0));
    sf::Thread th3(std::bind(updateThread, *this, dh*2.0/4.0, dh*3.0/4.0));
    sf::Thread th4(std::bind(updateThread, *this, dh*3.0/4.0, dh*4.0/4.0));

    th1.launch();
    th2.launch();
    th3.launch();
    th4.launch();

    th1.wait();
    th2.wait();
    th3.wait();
    th4.wait();
    needUpdate=false;
    display.update(piksele);
  }

}

void updateThread(Container& ds, unsigned ymin, unsigned ymax)
{
  sf::Color tmp;
  for(unsigned i=ymin;i<ymax;i++)
  {
    for(unsigned j=0;j<ds.dw;j++)
    {
      tmp = interpolateBL(translate(sf::Vector2f(j, i), ds), ds);
      ds.piksele[4*(i*ds.dw+j)]=tmp.r;
      ds.piksele[4*(i*ds.dw+j)+1]=tmp.g;
      ds.piksele[4*(i*ds.dw+j)+2]=tmp.b;
    }
  }
}
