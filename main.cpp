#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <random>

using namespace std;

class ip_addr{
public:
    unsigned okt1, okt2, okt3, okt4;
    void print(){
        cout << to_string(okt1) << "." << to_string(okt2) << "." << to_string(okt3) <<
                "." << to_string(okt4) << endl;

    }
};


// Custom Comparator to sort the array in increasing order
/*bool customComparator(string a, string b) {
    // Breaking into the octets
    //vector<string> octetsA;
    //vector<string> octetsB;
    vector<unsigned char> octetsA;//д.б. 4 числа!
    vector<unsigned char> octetsB;//д.б. 4 числа!

    string octet = "";
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '.') {
            octetsA.push_back(stoi(octet));
            octet = "";
        } else {
            octet += a[i];
        }
    }
    octetsA.push_back(stoi(octet));

    octet = "";
    for (int i = 0; i < b.size(); i++) {
        if (b[i] == '.') {
            octetsB.push_back(stoi(octet));
            octet = "";
        } else {
            octet += b[i];
        }
    }
    octetsB.push_back(stoi(octet));

    // Condition if the IP Address is same then return false
    if (octetsA == octetsB) {
        return false;
    }

    // Compare the octets and return the result
    for (int i = 0; i < 4; i++) {
        if (octetsA[i] > octetsB[i]) {
            return true;//false;
        } else if (octetsA[i] < octetsB[i]) {
            return false;//true;
        }
    }
    return false;
}

// Function to sort the IP Addresses
vector<string> sortIPAddress(vector<string> arr) {
    // Sort the Array using Custom Comparator
    sort(arr.begin(), arr.end(), customComparator);
    return arr;
}*/

bool customComp_back(ip_addr a, ip_addr b) {
    if ((a.okt1 == b.okt1) && (a.okt2 == b.okt2) &&
        (a.okt3 == b.okt3) && (a.okt4 == b.okt4)) {
        return false;
    }

    // Compare the octets and return the result
    if(a.okt1 > b.okt1){
        return true;
    }
    else if(a.okt1 < b.okt1){
        return false;
    }
    else if(a.okt1 == b.okt1){
        if(a.okt2 > b.okt2){
            return true;
        }
        else if(a.okt2 < b.okt2){
            return false;
        }
        else if(a.okt2 == b.okt2){
            if(a.okt3 > b.okt3){
                return true;
            }
            else if(a.okt3 < b.okt3){
                return false;
            }
            else if(a.okt3 == b.okt3){
                if(a.okt4 > b.okt4){
                    return true;
                }
                else if(a.okt4 < b.okt4){
                    return false;
                }

            }

        }
    }

    return false;
}
bool customComp_forw(ip_addr a, ip_addr b) {
    if ((a.okt1 == b.okt1) && (a.okt2 == b.okt2) &&
        (a.okt3 == b.okt3) && (a.okt4 == b.okt4)) {
        return false;
    }

    // Compare the octets and return the result
    if(a.okt1 < b.okt1){
        return true;
    }
    else if(a.okt1 > b.okt1){
        return false;
    }
    else if(a.okt1 == b.okt1){
        if(a.okt2 < b.okt2){
            return true;
        }
        else if(a.okt2 > b.okt2){
            return false;
        }
        else if(a.okt2 == b.okt2){
            if(a.okt3 < b.okt3){
                return true;
            }
            else if(a.okt3 > b.okt3){
                return false;
            }
            else if(a.okt3 == b.okt3){
                if(a.okt4 < b.okt4){
                    return true;
                }
                else if(a.okt4 > b.okt4){
                    return false;
                }

            }

        }
    }

    return false;
}
vector<ip_addr> sortIP_Address(vector<ip_addr> arr) {
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

// Driver Code
int main() {
    /*std::vector<std::string> vecline;
    std::ifstream file("C:\\Users\\lukso\\Documents\\otus\\hw2\\ip_filter.tsv"); // Открываем файл для чтения

        if (file.is_open()) { // Проверяем, успешно ли открылся файл
            std::string line; // Строка для хранения каждой прочитанной строки

            // Цикл продолжается, пока getline успешно считывает строку
            while (std::getline(file, line)) {
                //std::cout << line << std::endl; // Выводим строку
                vecline.push_back(line);
            }

            file.close(); // Закрываем файл после завершения чтения
        } else {
            std::cerr << "Unable to open file." << std::endl; // Выводим ошибку, если файл не открылся
        }*/

    //std::map<vector<unsigned char>, int> map_ip;

    try
    {
        //std::vector<std::vector<std::string> > ip_pool;
        //std::vector<std::string> arr;
        std::vector<ip_addr> vec_ip;
        for(std::string line; std::getline(std::cin, line);)
        //for(int str=0;str< vecline.size();str++)
        {
            //std::vector<std::string> v = split(vecline[str], '\t');
            std::vector<std::string> v = split(line, '\t');
            //ip_pool.push_back(split(v.at(0), '.'));
            //arr.push_back(v.at(0));

            vector<unsigned> octetsA;
            ip_addr ip_adr;
            string octet;
            for (int i = 0; i < v.at(0).size(); i++) {
                if (v.at(0)[i] == '.') {
                    octetsA.push_back(stoi(octet));

                    octet = "";
                } else {
                    octet += v.at(0)[i];
                }
            }
            octetsA.push_back(stoi(octet));

            ip_adr.okt1=octetsA.at(0);
            ip_adr.okt2=octetsA.at(1);
            ip_adr.okt3=octetsA.at(2);
            ip_adr.okt4=octetsA.at(3);
            vec_ip.push_back(ip_adr);
            //map_ip[octetsA] = 1;
        }
        //for(int l=0;l < vec_ip.size();l++)
        //    vec_ip.at(l).print();

      
        vec_ip = sortIP_Address(vec_ip);
        
        //cout << "---------------------" << endl;
        for(int l=0;l < vec_ip.size();l++)
            vec_ip.at(l).print();
        //cout << "---------------------" << endl;
        random_device rd;
        mt19937 g(rd());

        shuffle(vec_ip.begin(), vec_ip.end(), g);

        //Сразу следом список адресов, первый байт которых равен 1.

        vector<ip_addr> new_vec_ip(vec_ip.size());

        auto end_vec_ip = copy_if(begin(vec_ip), end(vec_ip),begin(new_vec_ip),
                [](const ip_addr& ip){
                            return ip.okt1 == 1;
        });
        new_vec_ip.erase(end_vec_ip, new_vec_ip.end());

        new_vec_ip = sortIP_Address(new_vec_ip);


        for(auto num : new_vec_ip){
            num.print();
        }


        //cout << "---------------------" << endl;
        //список адресов, первый байт которых равен 46, а второй 70.
        shuffle(vec_ip.begin(), vec_ip.end(), g);
        vector<ip_addr> new_vec_ip2(vec_ip.size());

        auto end_vec_ip2 = copy_if(begin(vec_ip), end(vec_ip),begin(new_vec_ip2),
                [](const ip_addr& ip){
                            return (ip.okt1 == 46 && ip.okt2 == 70);
        });
        new_vec_ip2.erase(end_vec_ip2, new_vec_ip2.end());
        new_vec_ip2 = sortIP_Address(new_vec_ip2);
        for(auto num : new_vec_ip2){
            num.print();
        }



        //cout << "---------------------" << endl;
        //любой байт которых равен 46
        shuffle(vec_ip.begin(), vec_ip.end(), g);
        vector<ip_addr> new_vec_ip3(vec_ip.size());

        auto end_vec_ip3 = copy_if(begin(vec_ip), end(vec_ip),begin(new_vec_ip3),
                [](const ip_addr& ip){
                            return (ip.okt1 == 46) or (ip.okt2 == 46) or (ip.okt3 == 46) or (ip.okt4 == 46);
        });
        new_vec_ip3.erase(end_vec_ip3, new_vec_ip3.end());
        

        new_vec_ip3 = sortIP_Address(new_vec_ip3);
        for(auto num : new_vec_ip3){
            num.print();
        }





    }
    catch(const std::exception &e)
    {
            std::cerr << e.what() << std::endl;
    }


    return 0;
}
