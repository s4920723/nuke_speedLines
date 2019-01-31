#ifndef SPEEDLINE_H
#define SPEEDLINE_H

#include "DDImage/ChannelSet.h"
#include "DDImage/Row.h"
#include "ControlPoint.h"

#include <vector>

class SpeedLine
{
    std::vector<ControlPoint> points;
    float U, V;

public:
    SpeedLine(float colU, float colV);
    void drawSegment(ControlPoint current, ControlPoint previous);
    bool placePoint(DD::Image::ChannelSet& UVset);
};

#endif // SPEEDLINE_H
