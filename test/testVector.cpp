/**
 * This code is part of libcity library.
 *
 * @file test/testVector.cpp
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Vector class
 *
 * Unit tests require UnitTest++ framework! See README
 * for more informations.
 */

/* Include UnitTest++ headers.
 * Check the symlink in test/ directory */
#include <UnitTest++.h>

// Includes
#include <cmath>

// Tested modules
#include "../src/geometry/vector.h"
#include "../src/geometry/units.h"

#include "../src/debug.h"

SUITE(VectorClass)
{
  TEST(AccessFunctions)
  {
    Vector vector(0, 0, 0);
    CHECK_EQUAL(vector.x(), 0);
    CHECK_EQUAL(vector.y(), 0);
    CHECK_EQUAL(vector.z(), 0);

    vector.setX(10);
    vector.setY(20);
    vector.setZ(30);

    CHECK_EQUAL(vector.x(), 10);
    CHECK_EQUAL(vector.y(), 20);
    CHECK_EQUAL(vector.z(), 30);

    vector.set(1.1, 2.23);
    CHECK_EQUAL(vector.x(), 1.1);
    CHECK_EQUAL(vector.y(), 2.23);
    CHECK_EQUAL(vector.z(), 0);

    vector.set(11.7, 12.8, 13.9);
    CHECK_EQUAL(vector.x(), 11.7);
    CHECK_EQUAL(vector.y(), 12.8);
    CHECK_EQUAL(vector.z(), 13.9);
  }

  TEST(Length)
  {
    Vector vector(10, 0, 0);
    CHECK_EQUAL(vector.length(), 10);

    vector = Vector(1, 2, 3);

    CHECK_EQUAL(vector.length(), sqrt(1*1 + 2*2 + 3*3));
  }

  TEST(Normalization)
  {
    Vector vector(10, 11, 12);
    vector.normalize();
    CHECK_CLOSE(vector.length(), 1, libcity::EPSILON);

    vector = Vector(1.123, 2.348, 12.35135);
    vector.normalize();
    CHECK_CLOSE(vector.length(), 1, libcity::EPSILON);
  }

  TEST(Operators)
  {
    Vector v1, v2, v3;

    /* Equal */
    CHECK(v1 == v2);

    v1.set(11.3, 12.7, 13.5);
    v2.set(11.3, 12.7, 13.5);
    CHECK(v1 == v2);

    /* Adding */
    v3 = v1 + v2;
    CHECK(v1 == v2);
    CHECK(v3 == Vector(11.3*2, 12.7*2, 13.5*2));

    /* Multiplication/division by constant */
    CHECK(v3 == v1*2.0);
    CHECK(v3/2.0 == v2);
  }

  TEST(Rotations)
  {
    Vector v(1,0,0);
    v.rotateAroundZ(-90);
    CHECK(v == Vector(0,-1,0));
  }

  TEST(AngleBetweenTwoVectors)
  {
    Vector one(1,0,0), two(0,1,0);

    CHECK_CLOSE(libcity::PI/2, two.angleTo(one), libcity::EPSILON);
    CHECK_CLOSE(libcity::PI/2, one.angleTo(two), libcity::EPSILON);

    one.set(1,0,0);
    two.set(-1,0,0);
    CHECK_CLOSE(libcity::PI, one.angleTo(two), libcity::EPSILON);

    one.set(1,0,0);
    two.set(-1,-1,0);
    CHECK_CLOSE(libcity::PI*0.75, one.angleTo(two), libcity::EPSILON);

    one.set(0.707107, 0.707107, -0);
    two.set(-0.707107, -0.707107, -0);
    CHECK_CLOSE(libcity::PI, one.angleTo(two), libcity::EPSILON);
  }

  TEST(AngleToXAxis)
  {
    Vector v(0,0,0);

    v.set(1,0,0);
    CHECK_CLOSE(0, v.angleToXAxis(), libcity::EPSILON);

    v.set(0,1,0);
    CHECK_CLOSE(libcity::PI/2, v.angleToXAxis(), libcity::EPSILON);

    v.set(-1,0,0);
    CHECK_CLOSE(libcity::PI, v.angleToXAxis(), libcity::EPSILON);

    v.set(0,-1,0);
    CHECK_CLOSE(libcity::PI*(3.0/2.0), v.angleToXAxis(), libcity::EPSILON);

    v.set(0,0,0);
    CHECK_CLOSE(0, v.angleToXAxis(), libcity::EPSILON);

    v.set(200,0,0);
    CHECK_CLOSE(0, v.angleToXAxis(), libcity::EPSILON);

    v.set(-200,0,0);
    CHECK_CLOSE(libcity::PI, v.angleToXAxis(), libcity::EPSILON);
  }

  TEST(CrossProduct)
  {
    Vector v1(1,2,3), v2(4,5,6);

    CHECK(Vector(-3,6,-3) == v1.crossProduct(v2));
    CHECK(Vector(3,-6,3) == v2.crossProduct(v1));

    v1.set(0,0,0);
    v2.set(1,2,3);
    CHECK(Vector(0,0,0) == v2.crossProduct(v1));
  }
}