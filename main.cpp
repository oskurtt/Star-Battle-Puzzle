#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Zone.h"
#include "Grid_Class.h"
#include "Point.h"

//for loop to print out grid
void print_grid(std::ofstream& outfile, std::vector<std::vector<char>> grid, int r, int c){
    for (int y = 0; y<c; ++y){
        for (int x = 0; x<r; ++x){
            outfile<<grid[x][y];
        }
        outfile<<std::endl;
    }
}
bool neighbors(int x, int y, std::vector<std::vector<char>>& grid){
    if (x>0 && y>0 && x<grid.size()-1 && y<grid[x].size()-1){
        if ((grid[x+1][y] == '@') || (grid[x-1][y] == '@') || (grid[x][y+1] == '@') || (grid[x][y-1] == '@') ||
        (grid[x+1][y+1] == '@') || (grid[x+1][y-1] == '@') || (grid[x-1][y+1] == '@') || (grid[x-1][y-1] == '@')){
            return false;
        }
    }
    //top left corner
    else if(x==0 && y == 0){
        if ((grid[x+1][y] == '@') || (grid[x+1][y+1] == '@') || (grid[x][y+1] == '@')){
            return false;
        }
    }
    //bottom left corner
    else if (x==0 && y==grid[x].size()-1){
        if ((grid[x+1][y] == '@') || (grid[x+1][y-1] == '@') || (grid[x][y-1] == '@')){
            return false;
        }
    }
    //top right corner
    else if (x==grid.size()-1 && y==0){
        if ((grid[x-1][y] == '@') || (grid[x-1][y+1] == '@') || (grid[x][y+1] == '@')){
            return false;
        }
    }
    //bottom right corner
    else if (x==grid.size()-1 && y==grid[x].size()-1){
        if ((grid[x-1][y] == '@') || (grid[x-1][y-1] == '@') || (grid[x][y-1] == '@')){
            return false;
        }
    }
    else {
        //left border
        if (x==0 && y>0){
            if ((grid[x+1][y] == '@') || (grid[x+1][y+1] == '@') || (grid[x+1][y-1] == '@') || 
            (grid[x][y-1] == '@') || (grid[x][y+1] == '@')){
                return false;
            }
        }
        //right border
        else if (x==grid.size()-1 && y>0){
            if ((grid[x-1][y] == '@') || (grid[x-1][y+1] == '@') || (grid[x-1][y-1] == '@') || 
            (grid[x][y-1] == '@') || (grid[x][y+1] == '@')){
                return false;
            }
        }
        //top border
        else if (x>0 && y == 0){
            if ((grid[x+1][y] == '@') || (grid[x+1][y+1] == '@') || (grid[x][y+1] == '@') || 
            (grid[x-1][y+1] == '@') || (grid[x-1][y] == '@')){
                return false;
            }
        }
        //bottom border
        else if (x>0 && y==grid[x].size()-1){
            if ((grid[x-1][y] == '@') || (grid[x-1][y-1] == '@') || (grid[x][y-1] == '@') || 
            (grid[x+1][y-1] == '@') || (grid[x+1][y] == '@')){
                return false;
            }
        }
    }
    return true;
}
bool possible (int x, int y, std::vector<std::vector<char>>& grid, Zone& zone, int maxstars){
    
    //if does not pass neighbors check, return false
    if (neighbors(x, y, grid) == false){
        return false;
    }
    int hor_count = 0;
    int ver_count = 0;
    
    //checks horizontal line
    for (int i = 0; i < grid.size(); ++i){
        if (grid[i][y] == '@'){
            hor_count ++;
        }
    }
    for (int i = 0; i < grid[x].size(); ++i){
        if (grid[x][i] == '@'){
            ver_count ++;
        }
    }
    if ((ver_count >= maxstars) || (hor_count >= maxstars)){
        return false;
    }
    //check if zone stars are all filled
    if (zone.stars == 0){
        return false;
    }

    //if pass all criterias return true
    return true; 
}

bool solved(Grid_Class& grid, int maxstars){
    for (int i = 0; i < grid.zones.size(); ++i){
        if (grid.zones[i].stars > 0){
            return false;
        }
    }
    return true;
}
void solve(std::vector<Grid_Class>& grids, std::vector<std::vector<char>>& grid, std::vector<Zone>& zones, int zones_pos, int points_pos, int maxstars, std::ofstream& outfile){
    int start_x = zones[zones_pos].points[points_pos].x;
    int start_y = zones[zones_pos].points[points_pos].y;
    std::vector<std::vector<char>> default_grid = grid;
    std::vector<Zone> default_zones = zones;
    if (possible(zones[zones_pos].points[points_pos].x, zones[zones_pos].points[points_pos].y, grid, zones[zones_pos], maxstars)){
            grid[start_x][start_y] = '@';
            zones[zones_pos].stars--;
            //if grid is solved, store grid in a vector of Grids
            Grid_Class temp_grid (grid, zones);
            if (solved(temp_grid, maxstars)){
                grids.push_back(temp_grid);
                //if iterated through all points in zone
                if (points_pos+1 == zones[zones_pos].points.size()){
                    //reaches end of all zones
                    if (zones_pos + 1 == zones.size()){
                        return;
                    }
                    //move on to next zone
                    solve(grids, default_grid, default_zones, zones_pos +1, 0, maxstars, outfile);
                }
                //move on to next point in same zone
                else{
                    solve (grids, default_grid, default_zones, zones_pos, points_pos+1, maxstars, outfile);
                }
            }
            else{
                //if iterated through all points in zone
                if (points_pos+1 == zones[zones_pos].points.size()){
                    //reaches end of all zones
                    if (zones_pos + 1 == zones.size()){
                        return;
                    }
                    //move on to next zone
                    solve(grids, grid, zones, zones_pos +1, 0, maxstars, outfile);
                }
                //move on to next point in same zone
                else{
                    solve (grids, grid, zones, zones_pos, points_pos+1, maxstars, outfile);
                }
            }
    }
    else{
        if (points_pos+1 == zones[zones_pos].size){
            if (zones_pos + 1 == zones.size()){
                return;
            }
            solve(grids, grid, zones, zones_pos +1, 0, maxstars, outfile);
        }
        else{
            solve (grids, grid, zones, zones_pos, points_pos+1, maxstars, outfile);
        }
    }
    
}
void all_solutions(std::string outmode, std::ofstream& outfile, std::vector<std::vector<char>>& grid, std::vector<Zone>& zones, int maxstars, std::vector<Grid_Class>& grids){
    if (outmode == "print"){
        for (int i = 0; i < zones[0].size; ++i){
            std::vector<std::vector<char>> g = grid;
            std::vector<Zone> z = zones;
            solve(grids, g, z, 0 , i, maxstars, outfile);
        }
        //solve(grids, grid, zones, 0 , 5, maxstars, outfile);
        outfile<<"Number of solutions: "<<grids.size()<<std::endl<<std::endl;
        for (int i = 0; i < grids.size(); ++i){
            outfile<<"Solution "<<i+1<<":"<<std::endl;
            print_grid(outfile, grids[i].grid, grids[i].grid.size(), grids[i].grid[0].size());
            outfile<<std::endl;
        }
    }
    if (outmode == "count"){
        for (int i = 0; i < zones[0].size; ++i){
            std::vector<std::vector<char>> g = grid;
            std::vector<Zone> z = zones;
            solve(grids, g, z, 0 , i, maxstars, outfile);
        }
        outfile<<"Number of solutions: "<<grids.size()<<std::endl<<std::endl;
    }
}

void one_solution(std::string outmode, std::ofstream& outfile, std::vector<std::vector<char>>& grid, std::vector<Zone>& zones, int maxstars, std::vector<Grid_Class>& grids){
    if (outmode == "print"){
        for (int i = 0; i < zones[0].size; ++i){
            std::vector<std::vector<char>> g = grid;
            std::vector<Zone> z = zones;
            solve(grids, g, z, 0 , i, maxstars, outfile);
        }
        outfile<<"Number of solutions: 1"<<std::endl<<std::endl;
        outfile<<"Solution 1"<<std::endl;
        print_grid(outfile, grids[0].grid, grids[0].grid.size(), grids[0].grid[0].size());
        outfile<<std::endl;
        
    }
    if (outmode == "count"){
        for (int i = 0; i < zones[0].size; ++i){
            std::vector<std::vector<char>> g = grid;
            std::vector<Zone> z = zones;
            solve(grids, g, z, 0 , i, maxstars, outfile);
        }
        outfile<<"Number of solutions: "<<grids.size()<<std::endl<<std::endl;
    }
}

int main(int argc, char* argv[]){
    //intialize variables
    std::ifstream infile (argv[1]); 
    std::ofstream outfile (argv[2]);
    int maxstars ((*argv[3])-48);
    std::string outmode (argv[4]);
    std::string solmode (argv[5]);

    int x, y, r, c;
    char z;
    int zsize;
    std::vector<std::vector<char>> grid;
    std::vector<Grid_Class> grids;
    std::vector<Zone> zones;

    //set number of rows and columns
    infile >> c >> r;
    //create the grid with specific size with a filler character (.)
    for (int i = 0; i<r; ++i){
        std::vector <char> column(c, '.');
        grid.push_back(column);
    }

    //set the grid to its initial state
    while (infile >> z >> zsize){
        zones.push_back(Zone(z, maxstars, zsize));
        for (int i = 0; i< zsize; ++i){
            infile >> x >> y;
            grid[x][y] = z;
            zones[zones.size()-1].points.push_back(Point(x,y));
        }
    }

    std::sort(zones.begin(), zones.end());

    if (solmode == "all_solutions"){
        all_solutions(outmode, outfile, grid, zones, maxstars, grids);
    }

    if (solmode == "one_solution"){
        one_solution(outmode, outfile, grid, zones, maxstars, grids);
    }
}
