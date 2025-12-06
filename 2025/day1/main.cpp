#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int decodeLine(const std::string& line){
    // Each Line is represented as sequence of character
    // the first character represent the operation this can either be R (right rotation) or L (left rotation)
    // the remainder of the character represent the number of movement to make
    // We can have `R24` (go 24 steps right) or `L50` (go 50 steps left)
    if(line.empty()){
        throw std::runtime_error("Invalid line!!!");
    }

    int move = 0;
    for(auto iter = line.begin() + 1; iter != line.end(); ++iter){
        if(std::isnan(*iter)){
            throw std::runtime_error("Invalid line!!!");
        }else {
            move *= 10;
            move += ((*iter) - '0');
        }
    }

    if(line[0] == 'L'){
        return move * -1;
    }else if(line[0] == 'R'){
        return move;
    }else {
        throw std::runtime_error("Invalid line!!!");
    }
}

int decodePassword(int startDial){
    // The dial starts from `0` and end at `99` inclusive
    std::ifstream file("input.txt");

    std::string line;
    int zeroCount = 0;
    while(std::getline(file, line)){
        int distance = decodeLine(line);

        startDial += distance;
        int diff = startDial - distance;
        if(startDial < 0){
            zeroCount += ((startDial * -1) / 100);
            startDial = 100 + (startDial % 100);
            if(diff > 0 && startDial != 0 && startDial != 100){
                zeroCount++;
            }
        }else if(startDial > 100){
            zeroCount += (startDial / 100);
            startDial %= 100;
            if(diff == 100 || startDial == 100 || startDial == 0){
                --zeroCount;
            }
        }

        if(startDial == 0 || startDial == 100){
            zeroCount++;
        }
    }

    return zeroCount;
}

int main(int argc, char *argv[])
{
    std::cout << "Main code" << std::endl;
    try {
        std::cout << "Password=" << decodePassword(50) << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error occurred: " << ex.what() << '\n';
    }
}