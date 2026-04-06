#include "main.hpp"

bool saveFileAsVector(std::vector<std::string>& filled_string, std::string file_name){
    filled_string.clear();
    std::string line;
    std::ifstream file(file_name);
    if(file.is_open()){
        while(std::getline(file, line)){
            filled_string.push_back(line);
        }
        return true;
    } else{
        return false;
    }
}

