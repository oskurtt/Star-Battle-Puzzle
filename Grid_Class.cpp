#include <iostream>
#include <string>
#include <vector>
#include "Grid_Class.h"


Grid_Class::Grid_Class(std::vector<std::vector<char>> grid_, std::vector<Zone> zones_){
    grid = grid_;
    zones = zones_;
}
