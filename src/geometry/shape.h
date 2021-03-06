/**
 * This code is part of libcity library.
 *
 * @file geometry/shape.h
 * @date 01.05.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a Shape by a polygon base and the object height.
 *
 */

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>
#include <string>
#include <list>

class Point;
class Vector;
class LineSegment;
class Polygon;

class Shape
{
  public:
    Shape();
    Shape(Polygon const& base, double height);

    Shape(Shape const& source);
    Shape& operator=(Shape const& source);

    ~Shape();

  private:
    Polygon* shapeBase;
    double   shapeHeight;

  public:
    Polygon base() const;
    Polygon top() const;
    double  height() const;

    void setBase(Polygon const& polygon);
    void setHeight(double const& number);

    bool encloses(Point const& point);
    bool encloses(Shape const& shape);
    bool encloses(Polygon const& polygon);

    std::string toString();
  private:
    void initialize();
    void freeMemory();
};

#endif