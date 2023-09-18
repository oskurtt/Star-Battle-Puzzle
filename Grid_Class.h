#ifndef _Grid_Class_H_
#define _Grid_Class_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Zone.h"

class Grid_Class{
    public: 
        Grid_Class(std::vector<std::vector<char>> grid_, std::vector<Zone> zones_);
        std::vector<std::vector<char>> grid;
        std::vector<Zone> zones;
};


#endif