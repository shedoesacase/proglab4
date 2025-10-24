#include <iostream>
#include "vector.hpp"
#include "1list.hpp"
#include "2list.hpp"
#include <map>

unsigned int factorial(unsigned int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main(){
    std::map<int, int> defMap;
    for(int i = 0; i < 10; i++){
        defMap[i] = factorial(i);
    }
    std::cout << "_=DEFMAP=_" << std::endl;
    for(std::pair<int, int> i : defMap){
        std::cout << i.first << ": " << i.second << std::endl;
    }


    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> myMap;
    for(int i = 0; i < 10; i++){
        myMap[i] = factorial(i);
    }
    std::cout << "_=MYMAP=_" << std::endl;
    for(std::pair<int, int> i : myMap){
        std::cout << i.first << ": " << i.second << std::endl;
    }

    std::cout << "defList: " << std::endl;

    SingleList<int> defList;
    for(int i = 0; i < 10; i++){
        defList.push_back(i);
    }

    for(int i = 0; i < 10; i++){
        std::cout << defList[i] << std::endl;
    }

    std::cout << "myList: " << std::endl;
    SingleList<int, MyAllocator<int>> myList;
    for(int i = 0; i < 10; i++){
        myList.push_back(i);
    }

    for(int i = 0; i < 10; i++){
        std::cout << myList[i] << std::endl;
    }
    return 0;
}
