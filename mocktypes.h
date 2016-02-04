#pragma once

#include <list>
#include "rectangle.h"
#include "lines.h"

enum eMockPrimitiveType
{
    kMPolygon = 0,
    kMTrack = 1,
    kMPad = 2,
    kMVia = 3
};

class tMockNet
{
public:
    int xNum;
};

class tMockPrimitive
{
    eMockPrimitiveType xType;

    bool xAllowGlobalEdit;
    bool xMoveable;
    bool xSelected;

    tMockNet* xNet;

protected:

    tPolygon xPolygon;

public:

    tMockPrimitive(eMockPrimitiveType t) : xType(t) { Init(); }
    tMockPrimitive(eMockPrimitiveType t, tPolygon& p) : xType(t), xPolygon(p) { Init(); }

    void Init()
    {
        xAllowGlobalEdit = true;
        xMoveable = true;
        xSelected = false;
        xNet = 0;
    }

    eMockPrimitiveType Type() const { return xType; }
    tPolygon const& Polygon() const { return xPolygon; }

    virtual tMockPrimitive* Replicate() const
    {
        tMockPrimitive* p = new tMockPrimitive(*this);
        return p;
    }

    void SetAllowGlobalEdit(bool age) { xAllowGlobalEdit = age; }
    void SetMoveable(bool m) { xMoveable = m; }
    void SetSelected(bool s) { xSelected = s; }
    void SetMockNet(tMockNet* n) { xNet = n; }

    bool AllowGlobalEdit() const { return xAllowGlobalEdit; }
    bool Moveable() const { return xMoveable; }
    bool Selected() const { return xSelected; }
    tMockNet* Net() const { return xNet; }
};

class tMockTrack : public tMockPrimitive
{
    int xWidth;
    int xLayer;

public:

    tMockTrack(tPoint p0, tPoint p1, int w, int l) : tMockPrimitive(kMTrack), xWidth(w), xLayer(l)
    {
        tContour c;
        c.push_back(p0);
        c.push_back(p1);
        xPolygon.push_back(c);
    }

    int Width() const { return xWidth; }
    int Layer() const { return xLayer; }

    void SetEnd(int i, tPoint p)
    {
        xPolygon[0][i] = p;
    }

    tPoint End(int i) const
    {
        tContour c = *(xPolygon.begin());
        std::vector<tPoint>::iterator it = c.begin();
        if (i)
            it++;
        return *it;
    }

    tMockPrimitive* Replicate() const
    {
        tMockTrack* tr = new tMockTrack(*this);
        return static_cast<tMockPrimitive*>(tr);
    }
};

class tMockPad : public tMockPrimitive
{
public:
    tMockPad(tPoint p) : tMockPrimitive(kMPad)
    {
        tContour c;
        c.push_back(p);
        xPolygon.push_back(c);
    }
    tPoint Location() const
    {
        return xPolygon[0][0];
    }
};

class tMockVia : public tMockPrimitive
{
public:
    tMockVia(tPoint p) : tMockPrimitive(kMVia)
    {
        tContour c;
        c.push_back(p);
        xPolygon.push_back(c);
    }
    tPoint Location() const
    {
        return xPolygon[0][0];
    }
};

inline tMockTrack* IsMockTrack(tMockPrimitive* prim)
{
    if (prim->Type() != kMTrack)
        return 0;
    return static_cast<tMockTrack*>(prim);
}

inline tMockPrimitive* IsMockPrimitive(tMockTrack*t)
{
    return static_cast<tMockPrimitive*>(t);
}

inline tMockPad* IsMockPad(tMockPrimitive* prim)
{
    if (prim->Type() != kMPad)
        return 0;
    return static_cast<tMockPad*>(prim);
}

inline tMockPrimitive* IsMockPrimitive(tMockPad*t)
{
    return static_cast<tMockPrimitive*>(t);
}

inline tMockVia* IsMockVia(tMockPrimitive* prim)
{
    if (prim->Type() != kMVia)
        return 0;
    return static_cast<tMockVia*>(prim);
}

inline tMockPrimitive* IsMockPrimitive(tMockVia* t)
{
    return static_cast<tMockPrimitive*>(t);
}

inline tMockTrack const* IsMockTrack(tMockPrimitive const* prim)
{
    if (prim->Type() != kMTrack)
        return 0;
    return static_cast<tMockTrack const*>(prim);
}

inline tMockPrimitive const* IsMockPrimitive(tMockTrack const*t)
{
    return static_cast<tMockPrimitive const*>(t);
}

inline tMockPad const* IsMockPad(tMockPrimitive const* prim)
{
    if (prim->Type() != kMPad)
        return 0;
    return static_cast<tMockPad const*>(prim);
}

inline tMockPrimitive const* IsMockPrimitive(tMockPad const*t)
{
    return static_cast<tMockPrimitive const*>(t);
}

inline tMockVia const* IsMockVia(tMockPrimitive const* prim)
{
    if (prim->Type() != kMVia)
        return 0;
    return static_cast<tMockVia const*>(prim);
}

inline tMockPrimitive const* IsMockPrimitive(tMockVia const*t)
{
    return static_cast<tMockPrimitive const*>(t);
}

inline tMockPrimitive* MockReplicate(tMockPrimitive const* p)
{
    return p->Replicate();
}

inline tMockNet* MockNet(tMockPrimitive const* p)
{
    return p->Net();
}

inline bool MockAllowGlobalEdit(tMockPrimitive const* p)
{
    return p->AllowGlobalEdit();
}

inline bool MockMoveable(tMockPrimitive const* p)
{
    return p->Moveable();
}

inline bool MockIsSelected(tMockPrimitive const* prim)
{
    return prim->Selected();
}

inline bool MockIsOnLayer(int l, tMockPrimitive const* p)
{
    if (tMockTrack const* tr = IsMockTrack(p))
        return l == tr->Layer();
    return true;
}

inline int MockLayer(tMockTrack const* t)
{
    return t->Layer();
}

inline int MockWidth(tMockTrack const* t)
{
    return t->Width();
}

inline tPoint MockEnd(tMockTrack const* t, int endIndex)
{
    return t->End(endIndex);
}

inline void MockSetEnd(tMockTrack* t, int endIndex, tPoint p)
{
    t->SetEnd(endIndex, p);
}

inline tPoint MockLocation(tMockPad const* t)
{
    return t->Location();
}

inline tPoint MockLocation(tMockVia const* t)
{
    return t->Location();
}

inline char const *MockPrimitiveTypeString(tMockPrimitive const* prim)
{
    switch (prim->Type())
    {
    case kMPolygon: return "MockPolygon\n";
    case kMTrack: return "MockTrackt\n";
    case kMPad: return "MockPad\n";
    case kMVia: return "MockVia\n";
    }
    return "???";
}

typedef std::list<tMockPrimitive*> tPrimList;

class tMockBoard
{
    tRect xWindowBoundingRectangle;
    tRect xBoundingRectangle;

    tPrimList xPrimList;

public:
    tMockBoard() : xWindowBoundingRectangle({0, 0}, {200, 200}), xBoundingRectangle({0, 0}, {200, 200}) {}

    tRect WindowBoundingRectangle()
    {
        return xWindowBoundingRectangle;
    }
    tRect BoundingRectangle()
    {
        return xBoundingRectangle;
    }
    void SetWindowBoundingRectangle(tRect r)
    {
        xWindowBoundingRectangle = r;
    }
    void SetBoundingRectangle(tRect r)
    {
        xBoundingRectangle = r;
    }
    void AddPrimitive(tMockPrimitive* p)
    {
        xPrimList.push_back(p);
    }
    void RemovePrimitive(tMockPrimitive* p)
    {
        for (auto it = xPrimList.begin(); it != xPrimList.end(); it++)
        {
            if (*it == p)
            {
                xPrimList.erase(it);
                break;
            }
        }
    }
    tPrimList& PrimList() { return xPrimList; }
};

class tMockSpatialIterator
{
    tMockBoard& xBoard;
    tPrimList::iterator xIter;
    bool xSelected;

public:
    tMockSpatialIterator(tMockBoard& b) : xBoard(b), xIter(b.PrimList().begin()), xSelected(false) {}

    void AddFilter_Selected()
    {
        xSelected = true;
    }
    tMockPrimitive* FirstObject()
    {
        xIter = xBoard.PrimList().begin();
        return NextObject();
    }
    tMockPrimitive* NextObject()
    {
        if (xSelected)
            return NextSelectedObject();
        if (xIter == xBoard.PrimList().end())
            return 0;
        tMockPrimitive* p = *xIter;
        xIter++;
        return p;
    }
    tMockPrimitive* NextSelectedObject()
    {
        while (xIter != xBoard.PrimList().end())
        {
            tMockPrimitive* p = *xIter;
            xIter++;
            if (p->Selected())
                return p;
        }
        return 0;
    }
};
