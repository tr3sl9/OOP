#include <catch2/catch_all.hpp>
#include <sstream>
#include "../lib/point.h"

TEST_CASE("Point constructors, getters, setters") {
    Point p0;
    CHECK(p0.getX() == Catch::Approx(0.0f));
    CHECK(p0.getY() == Catch::Approx(0.0f));

    Point p1(3.5f, -2.0f);
    CHECK(p1.getX() == Catch::Approx(3.5f));
    CHECK(p1.getY() == Catch::Approx(-2.0f));

    float arr[2] = {1.25f, 4.75f};
    Point p2(arr);
    CHECK(p2.getX() == Catch::Approx(1.25f));
    CHECK(p2.getY() == Catch::Approx(4.75f));

    p2.setX(-10.0f);
    p2.setY(7.0f);
    CHECK(p2.getX() == Catch::Approx(-10.0f));
    CHECK(p2.getY() == Catch::Approx(7.0f));
}

TEST_CASE("Point arithmetic and distance") {
    Point a(1.0f, 2.0f);
    Point b(-3.0f, 5.0f);

    Point sum = a + b;
    CHECK(sum.getX() == Catch::Approx(-2.0f));
    CHECK(sum.getY() == Catch::Approx(7.0f));

    Point diff = a - b;
    CHECK(diff.getX() == Catch::Approx(4.0f));
    CHECK(diff.getY() == Catch::Approx(-3.0f));

    Point div = a / 2.0f;
    CHECK(div.getX() == Catch::Approx(0.5f));
    CHECK(div.getY() == Catch::Approx(1.0f));

    float d = a.distanceTo(b);
    CHECK(d == Catch::Approx(std::sqrt((1.0f + 3.0f)*(1.0f + 3.0f) + (2.0f - 5.0f)*(2.0f - 5.0f))));
}

TEST_CASE("Point rotate90Clockwise (current implementation behavior)") {
    Point p(2.0f, -3.0f);
    p.rotate90Clockwise();
    CHECK(p.getX() == Catch::Approx(-3.0f));
    CHECK(p.getY() == Catch::Approx(2.0f));
}

TEST_CASE("Point stream operators >> and <<") {
    std::istringstream iss("1.5 2.5");
    Point p;
    iss >> p;
    CHECK(p.getX() == Catch::Approx(1.5f));
    CHECK(p.getY() == Catch::Approx(2.5f));

    std::ostringstream oss;
    oss << p;

    CHECK(oss.str() == std::string("Point: (1.5 ; 2.5)"));
}
