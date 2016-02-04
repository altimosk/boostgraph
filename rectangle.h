#pragma once
#include "point.h"

struct tRect : public std::pair<tPoint, tPoint>
{
    tRect(tPoint x, tPoint y) : std::pair<tPoint, tPoint>(x, y) {/*reorder?*/ }
    tPoint& LL() { return first; }
    tPoint& UR() { return second; }
    int& left() { return first.first; }
    int& bottom() { return first.second; }
    int& right() { return second.first; }
    int& top() { return second.second; }
};

