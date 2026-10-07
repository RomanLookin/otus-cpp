#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <tuple>

using namespace std;


//template<typename T>
class Matrix
{
    public:
    Matrix(){

        int sz = vals_mpp.size();
        RowProxy* vrpp = new RowProxy;
        vals_mpp[sz] =vrpp;
        
    };

    struct RowProxy{
        
        RowProxy(){

            
            if(!rowpm){
                
                rowpm = new map<int, int>;
            }
            
        }
        std::map<int, int>* rowpm=nullptr;

        int& operator[](int n){

            auto it = rowpm->find(n);
            if (it != rowpm->end()) {
                return rowpm->at(n);
            }
            else{
                rowpm->operator[](n) = 0;
                return rowpm->at(n);
            }

            
        }
    };


    std::map<int, RowProxy> vals_mp;
    std::map<int, RowProxy*> vals_mpp;

    std::vector<int> rows, cols;

    RowProxy& operator[](int x){
        auto it = vals_mpp.find(x);
        if (it != vals_mpp.end()) {
            return *vals_mpp[x];
        } else {
            RowProxy* vrpp = new RowProxy;
            vals_mpp[x] =vrpp;
            return *vrpp;
        }

    }
    int size(){
        int count_v = 0;
        for (const auto& [numb, val] : vals_mpp) {
            for (const auto& pair : *val->rowpm) {
                if(pair.second != 0)count_v++;
            }

        }
        return count_v;

    }
    auto begin() { return vals_mpp.begin(); }
    auto cbegin() { return vals_mpp.begin(); }
    auto end() { return vals_mpp.end(); }
    auto cend() { return vals_mpp.end(); }

    //template<typename X>
    friend std::ostream& operator << (std::ostream& os, const Matrix& m)
    {

            for (const auto& [numb, val] : m.vals_mpp) {
                    //std::cout << to_string(numb) << ":";// << to_string(val->rowp->size()) << endl;//": " << year << std::endl;
                for (const auto& pair : *val->rowpm) {
                    //std::cout << pair.first << ": " << pair.second << std::endl;
                    if(pair.second != 0){
                        os << to_string(numb) << to_string(pair.first) <<  to_string(pair.second) << endl;
                    }
                }
            }




        return os;



    }

protected:

};


int main()
{

    Matrix m;
    for(int l=0;l<10;l++)
        m[l][l]=l;

    for(int l=0;l<10;l++)
        m[9-l][l]=9-l;

    for(int k=1;k<9;k++){
        for(int l=1;l<9;l++)
            cout << to_string(m[k][l]) << " ";
        cout << endl;
    }
    
    cout << to_string(m.size()) << endl;
    cout << m;



     return 0;
}


