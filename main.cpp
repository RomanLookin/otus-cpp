#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <utility>

#include "allocator.h"

int main()
{
    try
        {

        std::map<int, int> map1;

        for(int i=0; i<10;++i){
            std::pair<int, int> pair = {i, factorial(i)};
            map1.insert(pair);

        }
        for(const auto& item : map1)
        {
            std::cout << item.first << " " << item.second << std::endl;
        }
        std::cout << "1----------" << std::endl;
        std::map<int, int, std::less<>, LoggingAllocator<int>> map2;

        for(int i=0; i<10;++i){
            std::pair<int, int> pair = {i, factorial(i)};
            map2.insert(pair);

        }
        for(const auto& item : map2)
        {
            std::cout << item.first << " " << item.second << std::endl;
        }
        std::cout << "2----------" << std::endl;
        MyVector<int> vec;
        for(int i=0; i<10;++i){
            vec.push_back(i);
        }

        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << "3----------" << std::endl;
        MyVector<int, LoggingAllocator<int>> vec2;
        for(int i=0; i<10;++i){
            std::cout << ">>" << std::to_string(i) << std::endl;
            vec2.push_back(i);
        }

        for (const auto& elem : vec2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << "4----------" << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }



    return 0;

}
