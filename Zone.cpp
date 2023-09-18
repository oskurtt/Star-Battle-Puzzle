#include <iostream>
#include <string>
#include <vector>
#include "Zone.h"


Zone::Zone(char zone_, int stars_, int size_){
   zone = zone_;
   stars = stars_;
   size = size_;
}

bool Zone::operator<(const Zone& other){
   return size < other.size;
}
