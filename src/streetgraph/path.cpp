/**
 * This code is part of libcity library.
 *
 * @file streetgraph/path.cpp
 * @date 23.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see path.h
 *
 */

#include "path.h"

#include "intersection.h"
#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/linesegment.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"

Path::Path()
{
  representation = new LineSegment();
}

Path::Path(LineSegment const& line)
{
  representation = new LineSegment(line);
}

Path::Path(Path const& source)
{
  representation = new LineSegment(*(source.representation));
}

Path& Path::operator=(Path const& source)
{
  *representation = *(source.representation);

  return *this;
}

Path::~Path()
{
  delete representation;
}

Point Path::begining() const
{
  return representation->begining();
}

Point Path::end() const
{
  return representation->end();
}

void Path::setBegining(Point const& begining)
{
  representation->setBegining(begining);
}

void Path::setEnd(Point const& end)
{
  representation->setEnd(end);
}

bool Path::isInside(Polygon const& certainArea) const
{
  return certainArea.encloses2D(begining()) ||
         certainArea.encloses2D(end());
}

bool Path::goesThrough(Point const& certainPoint) const
{
  return representation->hasPoint2D(certainPoint);
}

LineSegment::Intersection Path::crosses(Path const& anotherPath, Point* intersection)
{
  return representation->intersection2D(*(anotherPath.representation), intersection);
}

Point Path::nearestPoint(Point const& point)
{
  return representation->nearestPoint(point);
}

double Path::distance(Point const& point)
{
  return representation->distance(point);
}

void Path::shorten(Point const& newBegining, Point const& newEnd)
{
  if (!representation->hasPoint2D(newBegining) ||
      !representation->hasPoint2D(newEnd))
  {
    // FIXME throw exception
  }

  representation->setBegining(newBegining);
  representation->setBegining(newEnd);
}

std::string Path::toString()
{
  return "Path(" + representation->toString() + ")";
}

double Path::length()
{
  return representation->length();
}

Vector Path::beginingDirectionVector()
{
  Vector beginingDirection(end(), begining());
  beginingDirection.normalize();

  return beginingDirection;
}

Vector Path::endDirectionVector()
{
  Vector endDirection(begining(), end());
  endDirection.normalize();

  return endDirection;
}