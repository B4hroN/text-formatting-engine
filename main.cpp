#include "main.hpp"

int size_of_screen = 100;
int size_of_left_decorations = 2;
int size_of_right_decorations = 2;

int main()
{
    std::vector<std::string> replicas;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::string alfabet = "Ничего не навернулось";
    if (not(saveFileAsVector(replicas, Files::replicas))){
        exit(404);
    }
    for (size_t i = 0; i < replicas.size(); i++){
        print(replicas[i], TextAlignment::Left, '.', '.');
        std::cout << std::endl;
    }


    std::cout << alfabet;
}

