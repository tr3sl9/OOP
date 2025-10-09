#include <catch2/catch_all.hpp>

#include "../lib/polygon.h"
#include "point.h"

static Polygon makeTriangle() {
    Point pts[3] = { Point(0.0f, 0.0f), Point(2.0f, 0.0f), Point(2.0f, 2.0f) };
    return Polygon(3, pts);
}

TEST_CASE("Polygon constructors and index access") {
    SECTION("Default constructor") {
        Polygon p0;

        CHECK(p0.getCount() == 0);
    }

    SECTION("Constructor with only point count") {
        Polygon a0(2);
        REQUIRE(a0.getCount() == 2);
        CHECK(a0[0].getX() == Catch::Approx(0.0F));
        CHECK(a0[0].getY() == Catch::Approx(0.0F));
        CHECK(a0[1].getX() == Catch::Approx(0.0F));
        CHECK(a0[1].getY() == Catch::Approx(0.0F));
    }

    SECTION("Constructor with 1 Point") {
        Point p0(1.0f, 2.0f);
        Polygon a0(p0);

        REQUIRE(a0.getCount() == 1);
        CHECK(a0[0].getX() == Catch::Approx(1.0f));
        CHECK(a0[0].getY() == Catch::Approx(2.0f));
    }

    SECTION("Constructor with array") {
        Point arr[2] = {Point(1.0f, 2.0f), Point(3.0f, 4.0f)};
        Polygon a0(2, arr);
        
        REQUIRE(a0.getCount() == 2);
        CHECK(a0[0].getX() == Catch::Approx(1.0f));
        CHECK(a0[0].getY() == Catch::Approx(2.0f));
        CHECK(a0[1].getX() == Catch::Approx(3.0f));
        CHECK(a0[1].getY() == Catch::Approx(4.0f));
    }
}

TEST_CASE("Copy/move semantics and assignments") {
    SECTION("Copy constructor makes deep copy") {
        Polygon t = makeTriangle();
        Polygon copy(t);
        t[0] = Point(10.0f, 10.0f);

        CHECK(copy[0].getX() == Catch::Approx(0.0f));
        CHECK(copy[0].getY() == Catch::Approx(0.0f));
    }

    SECTION("Copy assignment is deep and handles self-assignment") {
        Polygon t = makeTriangle();
        Polygon other(1);
        other = t;
        t[1] = Point(5.0f, 5.0f);

        CHECK(other[1].getX() == Catch::Approx(0.0f));

        other = other;

        CHECK(other[0].getX() == Catch::Approx(0.0f));
        CHECK(other.getCount() == 3);
    }

    SECTION("Move constructor empties source") {
        Polygon t = makeTriangle();
        Polygon moved(std::move(t));

        std::ostringstream oss;
        oss << t;
        CHECK(oss.str().rfind("0 ", 0) == 0);
        CHECK(moved.getCount() == 3);
    }

    SECTION("Move assignment empties source") {
        Polygon t = makeTriangle();
        Polygon target(1);
        target = std::move(t);
        std::ostringstream oss;
        oss << t;

        CHECK(oss.str().rfind("0 ", 0) == 0);
        CHECK(target.getCount() == 3);
    }
}

TEST_CASE("Operator +=") {
    Polygon p(Point(0.0f, 0.0f));
    p += Point(1.0f, 0.0f);
    p += Point(1.0f, 1.0f);

    REQUIRE(p.getCount() == 3);
    CHECK(p[2].getX() == Catch::Approx(1.0f));
    CHECK(p[2].getY() == Catch::Approx(1.0f));
}

TEST_CASE("centerOfMass computes arithmetic mean") {
    Polygon t = makeTriangle();
    Point c = t.centerOfMass();

    CHECK(c.getX() == Catch::Approx((0.0f + 2.0f + 2.0f) / 3.0f));
    CHECK(c.getY() == Catch::Approx((0.0f + 0.0f + 2.0f) / 3.0f));
}

TEST_CASE("move translates all vertices by delta") {
    Polygon t = makeTriangle();
    t.move(Point(1.0f, -1.0f));

    CHECK(t[0].getX() == Catch::Approx(1.0f));
    CHECK(t[0].getY() == Catch::Approx(-1.0f));
    CHECK(t[2].getX() == Catch::Approx(3.0f));
    CHECK(t[2].getY() == Catch::Approx(1.0f));
}

TEST_CASE("rotate only allows multiples of 90 and rotates around center") {
    Polygon p = makeTriangle();

    SECTION("Invalid angle throws") {
        CHECK_THROWS_AS(p.rotate(Point(0.0f, 0.0f), 45), std::invalid_argument);
    }

    SECTION("Clockwise 90 around origin (current implementation)") {
        Point pts[4] = { Point(1,0), Point(0,1), Point(-1,0), Point(0,-1) };
        Polygon poly(4, pts);

        poly.rotate(Point(0,0), 90);
        CHECK(poly[0].getX() == Catch::Approx(0));
        CHECK(poly[0].getY() == Catch::Approx(-1));
        CHECK(poly[1].getX() == Catch::Approx(1));
        CHECK(poly[1].getY() == Catch::Approx(0));

        poly.rotate(Point(0,0), 180);
        CHECK(poly[0].getX() == Catch::Approx(0));
        CHECK(poly[0].getY() == Catch::Approx(1));
    }

    SECTION("Rotation around arbitrary center") {
        Point pts[2] = { Point(2,1), Point(4,1) };
        Polygon poly(2, pts);
        poly.rotate(Point(3,1), 90);

        CHECK(poly[0].getX() == Catch::Approx(3));
        CHECK(poly[0].getY() == Catch::Approx(2));
        CHECK(poly[1].getX() == Catch::Approx(3));
        CHECK(poly[1].getY() == Catch::Approx(0));
    }
}

TEST_CASE("Stream operators >> and <<") {
    SECTION("Good input") {
        std::istringstream iss("3 0 0 1 0 1 1");
        Polygon poly;
        iss >> poly;
        REQUIRE_FALSE(iss.fail());
        REQUIRE(poly.getCount() == 3);
        CHECK(poly[0].getX() == Catch::Approx(0.0f));
        CHECK(poly[2].getY() == Catch::Approx(1.0f));

        std::ostringstream oss;
        oss << poly;
        CHECK(oss.str().rfind("3 ", 0) == 0);
    }

    SECTION("Bad input sets failbit") {
        std::istringstream bad("NAN 1 2");
        Polygon poly;
        bad >> poly;
        CHECK(bad.fail());
    }
}
