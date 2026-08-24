#pragma once
#include <iostream>
#include <vector>
int version();

class ip_addr{
public:
    ip_addr() : okt1(0), okt2(0), okt3(0), okt4(0){}
    ip_addr(int oct1_, int oct2_, int oct3_, int oct4_) : okt1(oct1_), okt2(oct2_), okt3(oct3_), okt4(oct4_)
    {}

    unsigned okt1, okt2, okt3, okt4;
    void print(){
        std::cout << std::to_string(okt1) << "." << std::to_string(okt2) << "." << std::to_string(okt3) <<
                "." << std::to_string(okt4) << std::endl;
    }
};
class for_variadic{
public:
    for_variadic(){};
    std::vector<ip_addr>* adr;
    std::vector<int> vec_oct;
};

bool customComp_back(ip_addr a, ip_addr b);
bool customComp_forw(ip_addr a, ip_addr b);
std::vector<ip_addr> sortIP_Address(std::vector<ip_addr> arr);
std::vector<std::string> split(const std::string &str, char d);
std::vector<ip_addr> ip_filter_and(std::vector<ip_addr> vec_ip, int oct1);
std::vector<ip_addr> ip_filter_and(std::vector<ip_addr> vec_ip, int oct1, int oct2);
std::vector<ip_addr> ip_filter_or(std::vector<ip_addr> vec_ip, int oct1);
std::vector<int> get_ip_adr(std::string str, bool& is_ok);
template<typename T> void ip_filter_1(T oct);
template<typename T, typename... Args> void ip_filter_1(T oct, Args... args);

