#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Get the position after movement so we know where we end up
int applyInstruction(int current, const std::string& instruction) {
    char direction = instruction[0];              
    int value = std::stoi(instruction.substr(1));

    if (direction == 'R') {
        current = (current + value) % 100;
    } else if (direction == 'L') {
        // Make sure we don't divide by negative so get Absolute
        current = (current - value) % 100;
        if (current < 0) current += 100;
    }

    return current;
}

// Use in countMovement to make sure we don't divide by negative number
// Writing code was messing up the floor div and I had mistakes so moved to function
int floor_div(int x, int d) {
    if (x >= 0) return x / d;
    int q = x / d;     
    int r = x % d;
    if (r == 0) return q;    
    return q - 1; 
}

// Count how many times we pass (point at 0)p
int countMovement(int start, int amount, char direction) {
    int s = start;
    int a = amount;

    if (direction == 'R') {
        int end = s + a;
        return floor_div(end, 100) - floor_div(s, 100);
    } else { 
        // it will move to left 'L'
        int end = s - a;
        // Make sure we don't divide by negative number
        return floor_div(s - 1, 100) - floor_div(end - 1, 100);
    }
}

int main() 
{
    std::ifstream file("file.txt");   
    // std::ifstream fil("sample1.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Start dial position
    int pos = 50;   
    // Count how many times it passes/hits 0
    int totalHits = 0;   

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // L or R
        char direction = line[0];    
        // Amount to move either L or R
        int value = std::stoi(line.substr(1));

        // Running count of movement
        totalHits += countMovement(pos, value, direction);

        // Position of file after each movement
        pos = applyInstruction(pos, line);
    }

    std::cout << "Total times: " << totalHits << std::endl;
    std::cout << "Final position: " << pos << std::endl;

    file.close();
    return 0;
}

