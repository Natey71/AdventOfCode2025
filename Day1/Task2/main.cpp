#include <iostream>
#include <fstream>
#include <string>


int main() 
{
    std::ifstream file("file.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << "Current pos: " << pos << std::endl;
    }

    file.close();
    
    return 0;
}

