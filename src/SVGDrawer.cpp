
#include "SVGDrawer.hpp"
#include<iostream>

using namespace std;

namespace MPIScheduler {

SVGDrawer::SVGDrawer(const string &filepath,
    double maxXValue,
    double maxYValue):
  _os(filepath),
  _width(500.0),
  _height(500.0),
  _ratioWidth(_width / maxXValue),
  _ratioHeight(_height / maxYValue)
{
  if (!_os) {
    cerr << "Warning: cannot open  " << filepath << ". Skipping svg export." << endl;
    return;
  }
}

SVGDrawer::~SVGDrawer()
{
}

string SVGDrawer::getRandomHex()
{
  static const char *buff = "0123456789abcdef";
  char res[8];
  res[0] = '#';
  res[7] = 0;
  for (int i = 0; i < 6; ++i) {
    res[i+1] = buff[rand() % 16];
  }
  return string(res);
}
  
void SVGDrawer::writeSquare(double x, double y, double w, double h, const char *color)
{
  writeSquareAbsolute(x * _ratioWidth, y * _ratioHeight, w * _ratioWidth, h * _ratioHeight, color);
}

void SVGDrawer::writeSquareAbsolute(double x, double y, double w, double h, const char *color)
{
  if (!_os) {
    return;
  }
  string colorStr(color ? string(color) : getRandomHex());
  //_os << "  <svg x=\"" << x << "\" y=\"" << y << "\" ";
  //_os << "width=\"" << w  << "\" "  << "height=\""  << h << "\" >" << endl;
  _os << "    <rect x=\"" << x << "\"  y=\"" << y << "\" height=\"" << h << "\" width=\"" << w << "\" style=\"fill: ";
  _os << colorStr  <<  "\"/>" << endl;
  //_os << "  </svg>" << endl;
}
  
void SVGDrawer::writeCaption(const string &text)
{
  if (!_os) {
    return;
  }
  _os << "<svg x = \"50\" y=\"550\">" << endl;
  _os << "  <text fill=\"blue\" font-size=\"30\" transform=\"translate(0, 35)\">" << text << "</text>" << endl;
  _os << "</svg>" << endl;
}



void SVGDrawer::writeHeader(const string &caption)
{
  if (!_os) {
    return;
  }

  _os << "<svg  xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0\" y=\"0\" width=\"600\" height=\"600\">" << endl;
  _os << "<rect x=\"0%\" y=\"0%\" height=\"100%\" width=\"100%\" style=\"fill: #ffffff\"/>" << endl;
  _os << "<svg x=\"0\" y=\"0\">"  << endl;
  _os << "  <text fill=\"dark\" font-size=\"35\" transform=\"translate(250, 30)\">cores</text>" << endl;
  _os << "</svg>" << endl;
  _os << "<svg x=\"0\" y=\"0\"> " << endl;
  _os << "  <text fill=\"dark\" font-size=\"35\" transform=\"translate(30, 300) rotate(270)\">time</text>" << endl;
  _os << "</svg>" << endl;
  writeCaption(caption);
  _os << "<svg x=\"50\" y=\"50\" width=\"500\" height=\"500\" >" << endl;
  _os << "  <rect x=\"0%\" y=\"0%\" height=\"100%\" width=\"100%\" style=\"fill: #eeeeee\"/>" << endl;
}

void SVGDrawer::writeFooter()
{
  if (!_os) {
    return;
  }
  _os << "</svg>" << endl;
  _os << "</svg>" << endl;

}


} // namespace MPIScheduler

