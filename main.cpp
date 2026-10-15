#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <type_traits>
#include <tuple>

using namespace std;

template<typename T>
struct wrapper
{
    struct iterator
    {
         typedef typename std::vector<T>::iterator It;
         It it1, it2, it3;
         iterator(It it1, It it2, It it3) : it1(it1), it2(it2), it3(it3) {}
         iterator & operator++()
         {
            ++it1; ++it2; ++it3; return *this;
         }

         iterator & operator *()
         {
            return *this;
         }
         bool operator == (const iterator &other)
         {
             return !(*this != other);
         }
         bool operator != (const iterator &other)
         {
             return it1 != other.it1 && it2 != other.it2 && it3 != other.it3;
         }
    };
    iterator begin_, end_;
    wrapper(std::vector<T> &v1,  std::vector<T> &v2,  std::vector<T> &v3)
      : begin_(v1.begin(), v2.begin(), v3.begin()),end_(v1.end(), v2.end(), v3.end())
    {
    }
    wrapper(const wrapper & other) : begin_(other.begin_), end_(other.end_) {}
    iterator begin()
    {
          return begin_;
    }
    iterator end()
    {
          return end_;
    }
    
};

class Matrix
{
    public:
    Matrix(){

    };
    vector<int> X;
    vector<int> Y;
    vector<int> V;
    int index;

    class RowProxy {
            Matrix& matrix;
            int x;

            public:
            //RowProxy(){}
            RowProxy(Matrix& matrix, int x) : matrix(matrix), x(x) {

            }
                class CellProxy {
                    Matrix& matrix;
                    int x, y;
                    int val;
                    public:
                    CellProxy(Matrix& matrix, int x, int y) : matrix(matrix), x(x), y(y) {
                        matrix.index = -1;
                        for(size_t l=0;l<matrix.X.size();l++){
                            if((matrix.X.at(l) == x) && (matrix.Y.at(l) == y)){
                                matrix.index = l;
                            }
                        }
                        if(matrix.index == -1){
                            matrix.X.push_back(x);
                            matrix.Y.push_back(y);
                        }
                        
                    }


                    int& operator[](int x){
                        
                        return x;
                    }

                    int &operator=(int v){
                        if(v != 0){
                            if(matrix.index == -1){
                                matrix.V.push_back(v);
                            }
                            else{
                                matrix.V.at(matrix.index) = v;

                            }
                        }
                        else{
                            if(matrix.index == -1){
                                matrix.X.pop_back();
                                matrix.Y.pop_back();
                            }
                            else{
                                auto it = matrix.X.begin() + matrix.index;
                                matrix.X.erase(it);
                                auto it1 = matrix.Y.begin() + matrix.index;
                                matrix.Y.erase(it1);
                                auto it2 = matrix.V.begin() + matrix.index;
                                matrix.V.erase(it2);
                            }

                        }
                        
                    }

                    operator int(){
                        
                        if(matrix.X.size() == matrix.V.size()){
                            matrix.index = -1;
                            for(size_t l=0;l<matrix.X.size();l++){
                                if((matrix.X.at(l) == x) && (matrix.Y.at(l) == y)){
                                    matrix.index = l;
                                }
                            }
                            if(matrix.index != -1)
                                return matrix.V.at(matrix.index);
                            else {
                                return 0;
                            }
                        }
                        else if(matrix.X.size() == matrix.V.size()+1){
                            matrix.X.pop_back();
                            matrix.Y.pop_back();
                            return 0;

                        }

                        

                    }
                };
                CellProxy operator[](int y) {
                   
                    return CellProxy(matrix, x, y);
                }
                

    };
    
    RowProxy operator[](int x){
        return RowProxy(*this, x);
    }
    int size(){
        if((X.size() == Y.size()) && (X.size() == V.size()))
            return X.size();
        else return -1;
    }
    

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


    
    cout << m.size() << endl;
    wrapper<int> w(m.X, m.Y, m.V);

    for(auto c : w)
    {
        int x,y,z;
        //std::tie(x,y,z) = {*c.it1, *c.it2, *c.it3};
        x = *c.it1;
        y = *c.it2;
        z = *c.it3;
        cout << x << y << z << endl;
    }

    

    return 0;
}
