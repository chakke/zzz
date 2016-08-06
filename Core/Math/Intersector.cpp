#include "Intersector.hpp"

namespace Intersector {

	float distanceLinePoint(float startX, float startY, float endX, float endY, float pointX, float pointY)
	{
		float normalLength = (float)sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
		return abs((pointX - startX) * (endY - startY) - (pointY - startY) * (endX - startX)) / normalLength;
	}

	float distanceLinePoint(Vector2* start, Vector2* end, Vector2* point)
	{
		return distanceLinePoint(start->getX(), start->getY(), end->getX(), end->getY(), point->getX(), point->getY());
	}
	float distanceLinePoint(cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Vec2 point)
	{
		return distanceLinePoint(start.x, start.y, end.x, end.y, point.x, point.y);
	}
	cocos2d::Vec2 nearestSegmentPoint(float startX, float startY, float endX, float endY, float pointX, float pointY)
	{
		cocos2d::Vec2 nearest(0, 0);

		const float xDiff = endX - startX;
		const float yDiff = endY - startY;
		float length2 = xDiff * xDiff + yDiff * yDiff;
		if (length2 == 0) { nearest.set(startX, startY); return nearest; }
		float t = ((pointX - startX) * (endX - startX) + (pointY - startY) * (endY - startY)) / length2;
		if (t < 0) { nearest.set(startX, startY); return nearest; }
		if (t > 1) { nearest.set(endX, endY); return nearest; }
		nearest.set(startX + t * (endX - startX), startY + t * (endY - startY));
		return nearest;
	}

	cocos2d::Vec2 nearestSegmentPoint(cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Vec2 point)
	{
		return nearestSegmentPoint(start.x, start.y, end.x, end.y, point.x, point.y);
	}
	Vector2* nearestSegmentPoint(Vector2* start, Vector2* end, Vector2* point)
	{
		cocos2d::Vec2 rs = nearestSegmentPoint(start->getX(), start->getY(), end->getX(), end->getY(), point->getX(), point->getY());
		return new Vector2(rs.x, rs.y);
	}

	float distanceSegmentPoint(float startX, float startY, float endX, float endY, float pointX, float pointY)
	{
		return nearestSegmentPoint(startX, startY, endX, endY, pointX, pointY).getDistance(cocos2d::Vec2(pointX, pointY));
	}
	float distanceSegmentPoint(cocos2d::Vec2 start, cocos2d::Vec2 end, cocos2d::Vec2 point)
	{
		return nearestSegmentPoint(start, end, point).getDistance(point);
	}
	float distanceSegmentPoint(Vector2 * start, Vector2 * end, Vector2 * point)
	{
		return nearestSegmentPoint(start, end, point)->dst(point);
	}

	bool isPointInTriangle(float px, float py, float ax, float ay, float bx, float by, float cx, float cy)
	{
		float px1 = px - ax;
		float py1 = py - ay;
		bool side12 = (bx - ax) * py1 - (by - ay) * px1 > 0;
		if ((cx - ax) * py1 - (cy - ay) * px1 > 0 == side12) return false;
		if ((cx - bx) * (py - by) - (cy - by) * (px - bx) > 0 != side12) return false;
		return true;

	}
	bool isPointInTriangle(Vector2 * p, Vector2 * a, Vector2 * b, Vector2 * c)
	{
		return isPointInTriangle(p->getX(), p->getY(), a->getX(), a->getY(), b->getX(), b->getY(), c->getX(), c->getY());
	}
	bool isPointInTriangle(cocos2d::Vec2 p, cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c)
	{
		return isPointInTriangle(p.x, p.y, a.x, a.y, b.x, b.y, c.x, c.y);
	}

	int pointLineSide(float linePoint1X, float linePoint1Y, float linePoint2X, float linePoint2Y, float pointX, float pointY)
	{
		int val = (linePoint2X - linePoint1X) * (pointY - linePoint1Y) - (linePoint2Y - linePoint1Y)
			* (pointX - linePoint1X);

		return (val > 0) - (val < 0);
	}
	int pointLineSide(cocos2d::Vec2 linePoint1, cocos2d::Vec2 linePoint2, cocos2d::Vec2 point) {
		return pointLineSide(linePoint1.x, linePoint1.y, linePoint2.x, linePoint2.y, point.x, point.y);
	}
	int pointLineSide(Vector2 * linePoint1, Vector2 * linePoint2, Vector2 * point)
	{
		return pointLineSide(linePoint1->getX(), linePoint1->getY(), linePoint2->getX(), linePoint2->getY(), point->getX(), point->getY());
	}

	bool intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
		cocos2d::Vec2 intersection) {
		float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
		if (d == 0) return false;


		float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
		intersection.set(x1 + (x2 - x1) * ua, y1 + (y2 - y1) * ua);

		return true;
	}
	bool intersectLines(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,
		Vector2* intersection) {
		float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
		if (d == 0) return false;

		if (intersection) {
			float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
			intersection->set(x1 + (x2 - x1) * ua, y1 + (y2 - y1) * ua);
		}
		return true;
	}
	bool intersectLines(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3, cocos2d::Vec2 p4, cocos2d::Vec2 intersection)
	{
		float x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y, x3 = p3.x, y3 = p3.y, x4 = p4.x, y4 = p4.y;

		float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
		if (d == 0) return false;


		float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
		intersection.set(x1 + (x2 - x1) * ua, y1 + (y2 - y1) * ua);

		return true;
	}
	bool intersectLines(Vector2 * p1, Vector2 * p2, Vector2 * p3, Vector2 * p4, Vector2 * intersection)
	{
		float x1 = p1->getX(), y1 = p1->getY(), x2 = p2->getX(), y2 = p2->getY(), x3 = p3->getX(), y3 = p3->getY(), x4 = p4->getX(), y4 = p4->getY();
		float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
		if (d == 0) return false;

		if (intersection) {
			float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
			intersection->set(x1 + (x2 - x1) * ua, y1 + (y2 - y1) * ua);
		}
		return true;
	}

	bool isPointInPoly(std::vector<Vector2*> Poly, Vector2 * point)
	{
		if (Poly.size() == 0) return false;
		Vector2* lastVertice = Poly.at(Poly.size() - 1);
		bool oddNodes = false;
		for (size_t i = 0; i < Poly.size(); i++) {
			Vector2* vertice = Poly.at(i);
			if ((vertice->getY() < point->getY() && lastVertice->getY() >= point->getY()) || (lastVertice->getY() < point->getY() && vertice->getY() >= point->getY())) {
				if (vertice->getX() + (point->getY() - vertice->getY()) / (lastVertice->getY() - vertice->getY()) * (lastVertice->getX() - vertice->getX()) < point->getX()) {
					oddNodes = !oddNodes;
				}
			}
			lastVertice = vertice;
		}
		return oddNodes;
	}
	bool isPointInPoly(std::vector<float> Poly, int offset, int count, float x, float y) {
		bool oddNodes = false;
		int j = offset + count - 2;
		for (size_t i = offset, n = j; i <= n; i += 2) {
			float yi = Poly[i + 1];
			float yj = Poly[j + 1];
			if ((yi < y && yj >= y) || (yj < y && yi >= y)) {
				float xi = Poly[i];
				if (xi + (y - yi) / (yj - yi) * (Poly[j] - xi) < x) oddNodes = !oddNodes;
			}
			j = i;
		}
		return oddNodes;
	}

	bool intersectPolys(Poly * p1, Poly * p2, Poly * overlap)
	{
		//reusable points to trace edges around Poly
		Vector2* ep1 = new Vector2(0, 0);
		Vector2* ep2 = new Vector2(0, 0);
		Vector2* s = new Vector2(0, 0);
		Vector2* e = new Vector2(0, 0);
		Vector2* ip = new Vector2(0, 0);

		std::vector<float> floatArray;
		std::vector<float> floatArray2(p1->getTransformedVertices());

		if (p1->getVertices().size() == 0 || p2->getVertices().size() == 0) {
			return false;
		}
		for (int i = 0; i < p2->getTransformedVertices().size(); i += 2) {
			ep1->set(p2->getTransformedVertices()[i], p2->getTransformedVertices()[i + 1]);
			//wrap around to beginning of array if index points to end;
			if (i < p2->getTransformedVertices().size() - 2) {
				ep2->set(p2->getTransformedVertices()[i + 2], p2->getTransformedVertices()[i + 3]);
			}
			else {
				ep2->set(p2->getTransformedVertices()[0], p2->getTransformedVertices()[1]);
			}
			if (floatArray2.size() == 0) {
				return false;
			}
			s->set(floatArray2.at(floatArray2.size() - 2), floatArray2.at(floatArray2.size() - 1));
			for (int j = 0; j < floatArray2.size(); j += 2) {
				e->set(floatArray2.at(j), floatArray2.at(j + 1));
				//determine if point is inside clip edge
				if (pointLineSide(ep2, ep1, e) > 0) {
					if (!(pointLineSide(ep2, ep1, s) > 0)) {
						intersectLines(s, e, ep1, ep2, ip);
						if (floatArray.size() < 2 || floatArray.at(floatArray.size() - 2) != ip->getX() || floatArray.at(floatArray.size() - 1) != ip->getY())
						{
							floatArray.push_back(ip->getX());
							floatArray.push_back(ip->getY());
						}
					}
					floatArray.push_back(e->getX());
					floatArray.push_back(e->getY());
				}
				else if (pointLineSide(ep2, ep1, s) > 0) {
					intersectLines(s, e, ep1, ep2, ip);
					floatArray.push_back(ip->getX());
					floatArray.push_back(ip->getY());
				}
				s->set(e->getX(), e->getY());
			}
			floatArray2.clear();
			for (auto x : floatArray) {
				floatArray2.push_back(x);
			}
			floatArray.clear();
		}
		if (!(floatArray2.size() == 0)) {
			overlap->setVertices(floatArray2);
			return true;
		}
		else {
			return false;
		}
	}
	bool intersectLinePoly(float x1, float y1, float x2, float y2, Poly* Poly) {
		std::vector<float> vertices = Poly->getTransformedVertices();
		int n = vertices.size();
		float x3 = vertices[n - 2], y3 = vertices[n - 1];
		for (int i = 0; i < n; i += 2) {
			float x4 = vertices[i], y4 = vertices[i + 1];
			float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
			if (d != 0) {
				float yd = y1 - y3;
				float xd = x1 - x3;
				float ua = ((x4 - x3) * yd - (y4 - y3) * xd) / d;
				if (ua >= 0 && ua <= 1) {
					return true;
				}
			}
			x3 = x4;
			y3 = y4;
		}
		return false;
	}
	bool intersectLinePoly(Vector2* p1, Vector2* p2, Poly* Poly) {
		return intersectLinePoly(p1->getX(), p1->getY(), p2->getX(), p2->getY(), Poly);
	}
	bool intersectLinePoly(cocos2d::Vec2 p1, cocos2d::Vec2 p2, Poly* Poly) {
		return intersectLinePoly(p1.x, p1.y, p2.x, p2.y, Poly);
	}

	bool intersectRects(Rect Rect1, Rect Rect2, Rect intersection) {
		if (Rect1.intersectsRect(Rect2)) {
			intersection.origin.x = MAX(Rect1.origin.x, Rect2.origin.x);
			intersection.size.width = MIN(Rect1.origin.x + Rect1.size.width, Rect2.origin.x + Rect2.size.width) - intersection.origin.x;
			intersection.origin.y = MAX(Rect1.origin.y, Rect2.origin.y);
			intersection.size.height = MIN(Rect1.origin.y + Rect1.size.height, Rect2.origin.y + Rect2.size.height) - intersection.origin.y;
			return true;
		}
		return false;
	}

	bool intersectSegmentPoly(float x1, float y1, float x2, float y2, Poly* Poly) {
		std::vector<float> vertices = Poly->getTransformedVertices();
		int n = vertices.size();
		float x3 = vertices[n - 2], y3 = vertices[n - 1];
		for (int i = 0; i < n; i += 2) {
			float x4 = vertices[i], y4 = vertices[i + 1];
			float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
			if (d != 0) {
				float yd = y1 - y3;
				float xd = x1 - x3;
				float ua = ((x4 - x3) * yd - (y4 - y3) * xd) / d;
				if (ua >= 0 && ua <= 1) {
					float ub = ((x2 - x1) * yd - (y2 - y1) * xd) / d;
					if (ub >= 0 && ub <= 1) {
						return true;
					}
				}
			}
			x3 = x4;
			y3 = y4;
		}
		return false;
	}
	bool intersectSegmentPoly(cocos2d::Vec2 p1, cocos2d::Vec2 p2, Poly* Poly) {
		return intersectSegmentPoly(p1.x, p1.y, p2.x, p2.y, Poly);
	}
	bool intersectSegmentPoly(Vector2* p1, Vector2* p2, Poly* Poly) {
		return intersectSegmentPoly(p1->getX(), p1->getY(), p2->getX(), p2->getY(), Poly);
	}

	bool intersectSegments(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, Vector2 * intersection)
	{

		float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
		if (d == 0) return false;

		float yd = y1 - y3;
		float xd = x1 - x3;
		float ua = ((x4 - x3) * yd - (y4 - y3) * xd) / d;
		if (ua < 0 || ua > 1) return false;

		float ub = ((x2 - x1) * yd - (y2 - y1) * xd) / d;
		if (ub < 0 || ub > 1) return false;

		if (intersection) intersection->set(x1 + (x2 - x1) * ua, y1 + (y2 - y1) * ua);
		return true;
	}
	bool intersectSegments(cocos2d::Vec2 p1, cocos2d::Vec2 p2, cocos2d::Vec2 p3, cocos2d::Vec2 p4, Vector2 * intersection)
	{
		return intersectSegments(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, intersection);
	}
	bool intersectSegments(Vector2 * p1, Vector2 * p2, Vector2 * p3, Vector2 * p4, Vector2 * intersection)
	{
		return intersectSegments(p1->getX(), p1->getY(), p2->getX(), p2->getY(), p3->getX(), p3->getY(), p4->getX(), p4->getY(), intersection);
	}

}
