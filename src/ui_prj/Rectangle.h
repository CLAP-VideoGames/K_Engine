#pragma once
#ifndef RECT_H
#define RECT_H

namespace K_Engine {
	typedef struct Rectangle
	{
		int x, y;
		int w, h;
	} Rectangle;

	typedef struct Point
	{
		int x;
		int y;
	} Point;

	inline bool PointInRect(const Point* p, const Rectangle* r)
	{
		return ((p->x >= r->x) && (p->x < (r->x + r->w)) &&
			(p->y >= r->y) && (p->y < (r->y + r->h))) ? true : false;
	}
}
#endif // RECT_H