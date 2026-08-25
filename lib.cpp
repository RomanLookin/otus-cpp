#include "lib.h"
#include <algorithm>

bool customComp_back(ip_addr a, ip_addr b) {
    if (a.arr_okt == b.arr_okt) {
        return false;
    }
    if(a.arr_okt > b.arr_okt){
            return true;
    }
     return false;
}

std::vector<ip_addr> sortIP_Address(std::vector<ip_addr> arr) {
    // Sort the Array using Custom Comparator
    sort(arr.begin(), arr.end(), customComp_back);
    return arr;
}

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


std::vector<ip_addr> ip_filter_and(std::vector<ip_addr> vec_ip, int oct1)
{
    std::vector<ip_addr> new_vec_ip(vec_ip.size());
	auto end_vec_ip = copy_if(begin(vec_ip), end(vec_ip),begin(new_vec_ip),
                [&oct1](const ip_addr& ip){
                    return ip.arr_okt.at(0) == (unsigned)oct1;
    });
    new_vec_ip.erase(end_vec_ip, new_vec_ip.end());

    new_vec_ip = sortIP_Address(new_vec_ip);
	
	return new_vec_ip;

}
std::vector<ip_addr> ip_filter_and(std::vector<ip_addr> vec_ip, int oct1, int oct2)
{
    std::vector<ip_addr> new_vec_ip(vec_ip.size());
	auto end_vec_ip = copy_if(begin(vec_ip), end(vec_ip),begin(new_vec_ip),
                [&oct1, &oct2](const ip_addr& ip){
                    return ((ip.arr_okt.at(0) == (unsigned)oct1) && (ip.arr_okt.at(1) == (unsigned)oct2));
    });
    new_vec_ip.erase(end_vec_ip, new_vec_ip.end());
    new_vec_ip = sortIP_Address(new_vec_ip);
	
	return new_vec_ip;

}
std::vector<ip_addr> ip_filter_or(std::vector<ip_addr> vec_ip, int oct1)
{
    std::vector<ip_addr> new_vec_ip(vec_ip.size());
	auto end_vec_ip3 = copy_if(begin(vec_ip), end(vec_ip),begin(new_vec_ip),
                [&oct1](const ip_addr& ip){
                    return (ip.arr_okt.at(0) == (unsigned)oct1) or (ip.arr_okt.at(1) == (unsigned)oct1) or
                            (ip.arr_okt.at(2) == (unsigned)oct1) or (ip.arr_okt.at(3) == (unsigned)oct1);
        });
        new_vec_ip.erase(end_vec_ip3, new_vec_ip.end());
        
        new_vec_ip = sortIP_Address(new_vec_ip);
		
		return new_vec_ip;

}
std::vector<int> get_ip_adr(std::string str, bool& is_ok)
{
	std::vector<std::string> v = split(str, '\t');
    std::vector<int> octetsA;
    if(v.size() == 0){
        is_ok = false;
        return octetsA;//empty vector

    }

    std::string octet;
    for (unsigned i = 0; i < v.at(0).size(); i++) {
        if (v.at(0)[i] == '.') {
            int numb= stoi(octet);

            if((numb > 255) or (numb < 0)){
                is_ok = false;
                return octetsA;
            }
            octetsA.push_back(numb);

            octet = "";
        } else {
            octet += v.at(0)[i];
        }
    }
    int numb= stoi(octet);
    if((numb > 255) or (numb < 0)){
        is_ok = false;
        return octetsA;
    }
    octetsA.push_back(numb);

    if(octetsA.size() != 4){
        is_ok = false;
        return octetsA;
    }
    return octetsA;
}
