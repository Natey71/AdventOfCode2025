#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int applyInstruction(int current, const std::string& instruction) {
    char direction = instruction[0];            // 'R' or 'L'
    int value = std::stoi(instruction.substr(1)); // the number part
    // If R subtract from current position
    // L add to current postion
    if (direction == 'R') {
        current = (current + value) % 100;
    } 
    else if (direction == 'L') {
        current = (current - value + 100) % 100;
    }

    return current;
}

int main() 
{
    std::ifstream file("file.txt");
    int pos = 50;
    int zero_count = 0;
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        pos = applyInstruction(pos, line);
        if(pos == 0) {
          zero_count++;
        }
      // std::cout << "Current pos: " << pos << std::endl;
    }
    std:cout << "Count of Zero: " << zero_count;

    file.close();
    
    return 0;
}

