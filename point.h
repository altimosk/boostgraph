#pragma once
#include "geom_base.h"
#include <utility>


class tPoint : public std::pair<int, int>
{
public:

    tPoint()                { SetXY(0, 0); }
    tPoint(int x, int y)    { SetXY(x, y); }
    void SetXY(int x, int y)  { first = x; second = y; }
    void Set(int i, int z)    { (i ? second : first) = z; }
    int Coord(int i) const    { return (i ? second : first); }
    int X() const             { return first; }
    int Y() const             { return second; }
    double ELength() const    { return std::hypot(X(), Y()); }

    tPoint& operator += (const tPoint& a)        { first += a.first; second += a.second; return *this; }
    tPoint& operator -= (const tPoint& a)        { first -= a.first; second -= a.second; return *this; }
    tPoint& operator *= (int n)                    { first *= n; second *= n; return *this; }
    bool      operator == (const tPoint& a) const  { return first == a.first && second == a.second; }
    bool      operator != (const tPoint& a) const  { return !(*this == a); }
};


inline tPoint operator + (const tPoint &a, const tPoint &b) { tPoint t = a; t += b; return t; }
inline tPoint operator - (const tPoint &a, const tPoint &b) { tPoint t = a; t -= b; return t; }
inline tPoint operator * (int n, const tPoint &a)             { tPoint t = a; t *= n; return t; }

inline long long VectorProduct(tPoint v, tPoint w) { return VectorProduct(v.X(), v.Y(), w.X(), w.Y()); }
inline long long InnerProduct(tPoint v, tPoint w)  { return InnerProduct(v.X(), v.Y(), w.X(), w.Y()); }
