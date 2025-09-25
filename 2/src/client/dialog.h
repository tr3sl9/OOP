#ifndef DIALOG_H
#define DIALOG_H

#include "point.h"

class Dialog {
public:
    static void run();
    
private:
    static Point createPoint();
    static void testConstructors();
    static void testGettersSetters();
    static void testDistance();
    static void testArithmetic();
    static void testRotation();
    static void printPointInfo(const Point& point, const std::string& name);
};

#endif