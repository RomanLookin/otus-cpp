#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

void out_vect(vector<string>& vc, vector<time_t>& vt)
{
    if((vc.size() != 0) && (vt.size() > 0)){

        string fname = "bulk"+to_string(vt.at(0))+".log";
        ofstream file(fname);

        if (file.is_open()) {

            for(size_t n = 0;n < vc.size();n++){
                cout << vc[n];
                file << vc[n];
                if(n != vc.size()-1){
                    cout << ", ";
                    file << ", ";
                }
            }
            cout << endl;
            vc.clear();
            vt.erase(vt.begin());

            file.close();
        //cout << "Запись прошла успешно!" << endl;
        } else {
            cout << "Ошибка при открытии файла!" << endl;
        }

    }

}

int main()
{
    vector<string> vec_str;
    vector<time_t> vec_time;
    bool dynamic_bloc = false;
    unsigned int N = 3, count_block = 0;
    string line;
    getline(cin, line);



    while(line != "eof"){

            if(line == "{"){

                if(count_block == 0){
                    out_vect(vec_str, vec_time);


                    dynamic_bloc = true;
                    std::time_t result = std::time(nullptr);
                    vec_time.push_back(result);//std::asctime(std::localtime(&result)));
                }
                count_block++;

                getline(cin, line);
                continue;
            }
            if(line == "}"){
                count_block--;
                if(count_block == 0){
                    out_vect(vec_str, vec_time);
                    dynamic_bloc = false;
                }
                getline(cin, line);
                continue;
            }

        vec_str.push_back(line);
        if(vec_str.size() == 1){
            std::time_t result = std::time(nullptr);
            vec_time.push_back(result);//std::asctime(std::localtime(&result)));
        }
        if((vec_str.size() == N) && !dynamic_bloc){
            out_vect(vec_str, vec_time);
        }

        getline(cin, line);
    }
    if(!dynamic_bloc){
        out_vect(vec_str, vec_time);
    }

    return 0;
}

