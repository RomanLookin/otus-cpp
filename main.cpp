#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <fstream>
#include "lib.h"
using namespace std;

int main() {

    try
    {
        std::vector<std::string> vecline;
        std::ifstream file("C:\\Users\\lukso\\Documents\\otus\\hw2\\ip_filter_copy.tsv"); // Открываем файл для чтения

        if(file.is_open()) { // Проверяем, успешно ли открылся файл
            std::string line; // Строка для хранения каждой прочитанной строки

            // Цикл продолжается, пока getline успешно считывает строку
            while(std::getline(file, line)) {
                //std::cout << line << std::endl; // Выводим строку
                vecline.push_back(line);
            }

            file.close(); // Закрываем файл после завершения чтения
         } else {
            std::cerr << "Unable to open file." << std::endl; // Выводим ошибку, если файл не открылся
         }

        std::vector<ip_addr> vec_ip;

        //for(std::string line; std::getline(std::cin, line);)
        for(const std::string& line : vecline)
        {
            bool ok = true;

            std::vector<int> octets_int = get_ip_adr(line, ok);
            if(ok){
                ip_addr ip_adr(static_cast<unsigned>(octets_int.at(0)),
                               static_cast<unsigned>(octets_int.at(1)),
                               static_cast<unsigned>(octets_int.at(2)),
                               static_cast<unsigned>(octets_int.at(3)));
				vec_ip.push_back(ip_adr);
            }
        }

        for(size_t l=0;l < vec_ip.size();l++){
            std::cout << std::to_string(l) << " ";
            vec_ip.at(l).print();
        }
      
        vec_ip = sortIP_Address(vec_ip);
        
        for(size_t l=0;l < vec_ip.size();l++)
            vec_ip.at(l).print();

        random_device rd;
        mt19937 g(rd());

        shuffle(vec_ip.begin(), vec_ip.end(), g);

        std::vector<ip_addr> new_vec_ip; /*= ip_filter_and(vec_ip, 1);
		
		for(auto num : new_vec_ip){
            num.print();
        }

        shuffle(vec_ip.begin(), vec_ip.end(), g);

		new_vec_ip = ip_filter_and(vec_ip, 46, 70);

		for(auto num : new_vec_ip){
            num.print();
        }*/
        for_variadic fwar1;
        fwar1.vec_oct = {1};
        std::vector<ip_addr>* p_new_vec_ip= &new_vec_ip;
        fwar1.adr = p_new_vec_ip;

        for_variadic fwar2;
        fwar2.vec_oct = {46, 70};
        fwar2.adr = p_new_vec_ip;

        ip_filter_1(fwar1, fwar2);

        shuffle(vec_ip.begin(), vec_ip.end(), g);

        //vector<ip_addr> new_vec_ip3(vec_ip.size());
        new_vec_ip = ip_filter_or(vec_ip, 46);

        for(auto num : new_vec_ip){
            num.print();
        }
    }
    catch(const std::exception &e)
    {
            std::cerr << e.what() << std::endl;
    }


    return 0;
}
