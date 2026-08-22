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

        std::vector<ip_addr> vec_ip;

        for(std::string line; std::getline(std::cin, line);)
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

        vec_ip = sortIP_Address(vec_ip);
        
        for(size_t l=0;l < vec_ip.size();l++)
            vec_ip.at(l).print();

        random_device rd;
        mt19937 g(rd());

        shuffle(vec_ip.begin(), vec_ip.end(), g);

	std::vector<ip_addr> new_vec_ip = ip_filter_and(vec_ip, 1);
		
	for(auto num : new_vec_ip){
            num.print();
        }

        shuffle(vec_ip.begin(), vec_ip.end(), g);

	new_vec_ip = ip_filter_and(vec_ip, 46, 70);

	for(auto num : new_vec_ip){
            num.print();
        }

        shuffle(vec_ip.begin(), vec_ip.end(), g);

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
