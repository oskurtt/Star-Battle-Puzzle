#ifndef _ZONE_H_
#define _ZONE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Point.h"

class Zone{
    public: 
        Zone(char zone_, int stars_, int size_);
        char zone;
        int stars;
        int size;
        std::vector<Point> points;
        bool operator<(const Zone& other);
};


#endif