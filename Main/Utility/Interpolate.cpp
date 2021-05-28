#include "Interpolate.h"

Container::Container(std::string file_name)
{
    dw = 800;
    dh = 800;
    angle = 0.0;
    NoAxis = 8;
    offsetX = 0;
    offsetY = 0;

    needUpdate = true;
    interpolationBC = false;

    oryginal.loadFromFile(file_name);
    tw = oryginal.getSize().x;
    th = oryginal.getSize().y;
    display.create(dw, dh);

    piksele = new sf::Uint8[dw*dh*4];
    for(unsigned i=0;i<dh;i++)
    {
      for(unsigned j=0;j<dw;j++)
      {
        piksele[4*(i*dw + j) + 3]=255;
      }
    }
}

Container::~Container()
{
  //delete[] piksele;
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

void Container::moveAngle(float deltaTime, float speed)
{
  angle += deltaTime*speed;
  angle = angle > 2*M_PI ? angle - 2*M_PI : angle;
}

void Container::add_Axis(){
  if(NoAxis<20) NoAxis++;
  needUpdate = true;
}

void Container::sub_Axis(){
  if(NoAxis>1)NoAxis--;
  needUpdate = true;
}

void Container::reset(){
  angle = 0.0;
  NoAxis = 8;
  offsetX = 0;
  offsetY = 0;
  needUpdate = true;
  interpolationBC = false;
}

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
  double radiusT = radiusD*(double(ds.tw-2)/double(ds.dw))*0.7071;
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
  int x1 = int(pos.x + ds.offsetX*0.01*ds.tw);
  int y1 = int(pos.y + ds.offsetY*0.01*ds.th);
  x1 = x1<0 ? ds.tw+x1: x1;
  y1 = y1<0 ? ds.th+y1 : y1;
  x1 = x1>=ds.tw ? x1 - ds.tw : x1;
  y1 = y1>=ds.th ? y1 - ds.th : y1;
  int x2 = x1+1 < ds.tw ? x1+1 : x1+1 - ds.tw;
  int y2 = y1+1 < ds.th ? y1+1 : y1+1 - ds.th;
  double decX = abs(pos.x - float(x1) + ds.offsetX*0.01*ds.tw);
  double decY = abs(pos.y - float(y1) + ds.offsetX*0.01*ds.tw);
  decX-=int(decX);
  decY-=int(decY);

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

float cubicFunc(float a, float b, float c, float d, float X){
  float A = (-1.0)*a/2.0 + 3*b/2.0 - 3*c/2.0 + d/2.0;
  float B = a - 5*b/2.0 + 2*c - d/2.0;
  float C = (-1.0)*a/2.0 + c/2.0;
  float D = b;

  //return A*pow(X, 3) + B*pow(X, 2) + C*X + D;
  return ((A*X+B)*X+C)*X+D;
}

//prototyp bikubicznej/////////////////////////////////////////////////

sf::Color interpolateBC(sf::Vector2f pos, Container& ds)
{
  int x1 = int(pos.x + ds.offsetX*0.01*ds.tw);
  int y1 = int(pos.y + ds.offsetY*0.01*ds.th);
  int x0 = x1-1<0 ? ds.tw+(x1-1): x1-1;
  int y0 = y1-1<0 ? ds.tw+(y1-1): y1-1;
  x1 = x1<0 ? ds.tw+x1: x1;
  y1 = y1<0 ? ds.th+y1 : y1;
  x1 = x1>=ds.tw ? x1 - ds.tw : x1;
  y1 = y1>=ds.th ? y1 - ds.th : y1;
  int x2 = x1+1 < ds.tw ? x1+1 : x1+1 - ds.tw;
  int y2 = y1+1 < ds.th ? y1+1 : y1+1 - ds.th;
  int x3 = x1+2 < ds.tw ? x1+2 : x1+2 - ds.tw;
  int y3 = y1+2 < ds.th ? y1+2 : y1+2 - ds.th;
  double decX = abs(pos.x - float(x1) + ds.offsetX*0.01*ds.tw);
  double decY = abs(pos.y - float(y1) + ds.offsetX*0.01*ds.tw);
  decX-=int(decX);
  decY-=int(decY);

  sf::Color a00 = ds.oryginal.getPixel(x0, y0);
  sf::Color a10 = ds.oryginal.getPixel(x1, y0);
  sf::Color a20 = ds.oryginal.getPixel(x2, y0);
  sf::Color a30 = ds.oryginal.getPixel(x3, y0);

  sf::Color a01 = ds.oryginal.getPixel(x0, y1);
  sf::Color a11 = ds.oryginal.getPixel(x1, y1);
  sf::Color a21 = ds.oryginal.getPixel(x2, y1);
  sf::Color a31 = ds.oryginal.getPixel(x3, y1);

  sf::Color a02 = ds.oryginal.getPixel(x0, y2);
  sf::Color a12 = ds.oryginal.getPixel(x1, y2);
  sf::Color a22 = ds.oryginal.getPixel(x2, y2);
  sf::Color a32 = ds.oryginal.getPixel(x3, y2);

  sf::Color a03 = ds.oryginal.getPixel(x0, y3);
  sf::Color a13 = ds.oryginal.getPixel(x1, y3);
  sf::Color a23 = ds.oryginal.getPixel(x2, y3);
  sf::Color a33 = ds.oryginal.getPixel(x3, y3);

  sf::Color result;

//  float col0R = cubicFunc(a00.r, a10.r, a20.r, a30.r, decX);
//  float col1R = cubicFunc(a01.r, a11.r, a21.r, a31.r, decX);
//  float col2R = cubicFunc(a02.r, a12.r, a22.r, a32.r, decX);
//  float col3R = cubicFunc(a03.r, a13.r, a23.r, a33.r, decX);
  float r = cubicFunc(cubicFunc(a00.r, a10.r, a20.r, a30.r, decX),
                      cubicFunc(a01.r, a11.r, a21.r, a31.r, decX),
                      cubicFunc(a02.r, a12.r, a22.r, a32.r, decX),
                      cubicFunc(a03.r, a13.r, a23.r, a33.r, decX), decY);
  if(r<0.0) result.r = 0;
  else if(r>255.0) result.r = 255;
  else result.r = r;

//  float col0G = cubicFunc(a00.g, a10.g, a20.g, a30.g, decX);
//  float col1G = cubicFunc(a01.g, a11.g, a21.g, a31.g, decX);
//  float col2G = cubicFunc(a02.g, a12.g, a22.g, a32.g, decX);
//  float col3G = cubicFunc(a03.g, a13.g, a23.g, a33.g, decX);
  float g = cubicFunc(cubicFunc(a00.g, a10.g, a20.g, a30.g, decX),
                      cubicFunc(a01.g, a11.g, a21.g, a31.g, decX),
                      cubicFunc(a02.g, a12.g, a22.g, a32.g, decX),
                      cubicFunc(a03.g, a13.g, a23.g, a33.g, decX), decY);
  if(g<0.0) result.g = 0;
  else if(g>255.0) result.g = 255;
  else result.g = g;

//  float col0B = cubicFunc(a00.b, a10.b, a20.b, a30.b, decX);
//  float col1B = cubicFunc(a01.b, a11.b, a21.b, a31.b, decX);
//  float col2B = cubicFunc(a02.b, a12.b, a22.b, a32.b, decX);
//  float col3B = cubicFunc(a03.b, a13.b, a23.b, a33.b, decX);
  float b = cubicFunc(cubicFunc(a00.b, a10.b, a20.b, a30.b, decX),
                      cubicFunc(a01.b, a11.b, a21.b, a31.b, decX),
                      cubicFunc(a02.b, a12.b, a22.b, a32.b, decX),
                      cubicFunc(a03.b, a13.b, a23.b, a33.b, decX), decY);
  if(b<0.0) result.b = 0;
  else if(b>255.0) result.b = 255;
  else result.b = b;

  return result;
}

void updateThread(Container& ds, unsigned ymin, unsigned ymax)
{
  sf::Color tmp;
  for(unsigned i=ymin;i<ymax;i++)
  {
    for(unsigned j=0;j<ds.dw;j++)
    {
      if (ds.interpolationBC) tmp = interpolateBC(translate(sf::Vector2f(j, i), ds), ds);
      else tmp = interpolateBL(translate(sf::Vector2f(j, i), ds), ds);
      ds.piksele[4*(i*ds.dw+j)]=tmp.r;
      ds.piksele[4*(i*ds.dw+j)+1]=tmp.g;
      ds.piksele[4*(i*ds.dw+j)+2]=tmp.b;
    }
  }
}
