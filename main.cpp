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

        /*std::map<int, int> map1;

        for(int i=0; i<10;++i){
            std::pair<int, int> pair = {i, factorial(i)};
            map1.insert(pair);

        }
        for(const auto& item : map1)
        {
            std::cout << item.first << " " << item.second << std::endl;
        }
        std::cout << "1----------" << std::endl;*/
        //std::map<int, int, std::less<>, LoggingAllocator<int>> map2;

        ArenaAllocator<std::pair<const int, int>> alloc(200);
        std::map<int, int, std::less<int>, ArenaAllocator<std::pair<const int, int>>> map2{alloc};

        //ArenaAllocator<std::pair<const int, int>> alloc;
        //std::map<int, int, std::less<int>, ArenaAllocator<std::pair<const int, int>>> map2;//(1,1, alloc);
        //std::map<int, int, std::less<int>, ArenaAllocator<int>> map2{alloc};
        for(int i=0; i<5;++i){
            map2[i] = factorial(i);
        }
        for(const auto& item : map2)
        {
            std::cout << item.first << " " << item.second << std::endl;
        }


        /*std::cout << "2----------" << std::endl;
        MyVector<int> vec;
        for(int i=0; i<10;++i){
            vec.push_back(i);
        }

        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << "3----------" << std::endl;*/
        /*ArenaAllocator<int> alloc2(124);
        std::vector<int, ArenaAllocator<int>> vec{alloc2};

        for(int i=0; i<10;++i){
            std::cout << "add element to vector " << std::to_string(i) << std::endl;
            vec.push_back(i);
        }

        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << "4----------" << std::endl;*/
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }



    return 0;

}
