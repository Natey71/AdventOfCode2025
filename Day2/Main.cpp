#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>


std::vector<long> getNumberRange(long start, long end) {
  // If start > than end then return empty vector
  if(start > end) {
    return {};
  }
 
  // Get size diference between start and end
  long size = end - start + 1;
  // Create vector to store the range of numbers
  std::vector<long> range_array(size);
 
  // iterate over start and end number
  std::iota(range_array.begin(), range_array.end(), start);
  return range_array;
}

// Check if number has repeated sequence
bool isValidId(long num) {
  /*
  Part 1
  
  std::string id = std::to_string(num);
  // If number is not even it won't have duplicate
  if(id.size() % 2 != 0) return false;
  
  // Get length and divide by 2 to find duplicates
  size_t middle = id.length() / 2;
  
  // first half of numbers
  std::string left = id.substr(0, middle);
  // second half of numbers
  std::string right = id.substr(middle);
  // If it is duplicate then return true
  return left == right;
  */
  
  ////////////
  // Part 2
  ////////////
  // int to string
  std::string s = std::to_string(num);
  size_t n = s.size();
  
  // p as position <= size of string / 2
  for (size_t p = 1; p <= n / 2; ++p) {
      // if division doesn't get us to 0
      if (n % p != 0) continue;

      // store pattern or size p
      std::string pattern = s.substr(0, p);
      
      // set ok to true to continue numbers that don't meet reqs
      bool ok = true;
      // for pos of p < size (n) pos sum of p
      for (size_t pos = p; pos < n; pos += p) {
        // if pos substring at p != pattern return false this is valid number
        if (s.substr(pos, p) != pattern) {
          ok = false;
          break;
        }
      }

      if (ok) {
          return true;  
      }
  }

  return false;
}

int main() {
    std::ifstream file("file.txt");
    if(!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;  
    }
    
    // get from type file to string
    std::string line;
    // store file into string line
    std::getline(file, line);
    
    // stream the line to iterate 
    std::stringstream ss(line);
    std::string id;
    // store all id in vector
    std::vector<std::string> all_ids;
    
    // while line has not reached the end substring it on delimiter ','
    while(std::getline(ss, id, ',')) {
        all_ids.push_back(id);
    }
    
    // store the sum of invalid values
    long sum_invalid = 0;
    // loop each it
    for(const auto& i : all_ids) {
      //std::cout << i << std::endl;
      size_t del = i.find('-');
      // get left and right side of - to get start and end number to find range
      long left = std::stol(i.substr(0, del));
      long right = std::stol(i.substr(del + 1));
      //std::cout << "One: " << left << " Two: " << right << std::endl;
      // get the range of numbers between start (left) and end (right) 
      std::vector<long> range = getNumberRange(left, right);

      // each number in range
      for(long num : range){
        //std::cout << num << std::endl;
        if(isValidId(num)){
          //std::cout << "Invalid: " << num << std::endl;
          
          // If number is the same then add to sum_invalid
          sum_invalid += num;
        }
      }
    }
    
    std::cout << "Sum of Invalid: " << sum_invalid << std::endl;
    
    return 0;
}
