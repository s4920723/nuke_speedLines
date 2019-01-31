#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "DDImage/ChannelSet.h"
#include "DDImage/Row.h"

#include <vector>


class ControlPoint
{
    int posX, posY;
    float velX, velY, velZ;
    public:
    ControlPoint(int x, int y, float vel);
};

#endif // CONTROLPOINT_H
