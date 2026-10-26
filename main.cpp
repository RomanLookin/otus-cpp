#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <type_traits>
#include <tuple>

//using namespace std;

template<typename T>
struct wrapper
{
    struct iterator
        {
             typedef typename std::map<std::pair<int, int>, T>::iterator It;
             It it1;//, it2, it3;
             iterator(It it1) : it1(it1) {}
             iterator & operator++()
             {
                ++it1;  return *this;
             }

             std::tuple<int, int, int> operator*()
             {
                 std::pair<std::pair<int, int>,T> pairmap=*it1; 
                 std::pair<int, int> ppairmap = pairmap.first;
                 int val = static_cast<int>(pairmap.second);
                std::tuple<int, int, int> tpl = {ppairmap.first, ppairmap.second, val};
                return tpl;
             }
             bool operator == (const iterator &other)
             {
                 return !(*this != other);
             }
             bool operator != (const iterator &other)
             {
                 return it1 != other.it1;
             }
        };

    iterator begin_, end_;

    wrapper(std::map<std::pair<int, int>, T> &v1)
          : begin_(v1.begin()),end_(v1.end())
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


template<typename T>
class Matrix
{
    public:
    Matrix(){}
    private:
    std::map<std::pair<int, int>, T> mp;
    public:
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
                    }



                    void operator=(T v) const {
                        int int_v = static_cast<int>(v);
                        std::pair<int, int> pair_serc={x, y};
                        if(matrix.mp.count(pair_serc)){

                            if(int_v == 0){
                                matrix.mp.erase(pair_serc);
                            }
                            else{
                                matrix.mp[pair_serc] = v;
                            }
                        }
                        else{
                            if(int_v !=0){
                                matrix.mp[pair_serc] = v;
                            }
                        }
                    }

                    operator int() const {
                        std::pair<int, int> pair_serc={x, y};
                        if(matrix.mp.count(pair_serc)){
                            return matrix.mp[pair_serc];
                        }
                        else {
                            return 0;
                        }

                    }
                };
                CellProxy operator[](int y) const {

                    return CellProxy(matrix, x, y);
                }


    };

    RowProxy operator[](int x){
        return RowProxy(*this, x);
    }
    int size() const {

        return mp.size();
    }
    std::map<std::pair<int, int>, T>& get_matrix()
    {
        return mp;
    }


};

int main()
{
    Matrix<int> m;

    for(int l=0;l<10;l++){
        m[l][l]=l;
        std::cout << m.size() << std::endl;
    }
    for(int l=0;l<10;l++){
        m[9-l][l]=9-l;
        std::cout << m.size() << std::endl;
    }
    for(int k=1;k<9;k++){
        for(int l=1;l<9;l++)
            std::cout << std::to_string(m[k][l]) << " ";
        std::cout << std::endl;
    }


    std::cout << m.size() << std::endl;
    wrapper<int> w(m.get_matrix());
    for(auto c : w)
    {
        int x,y,z;
        std::tie(x,y, z) = c;
        std::cout << x << y << z << std::endl;
    }
    return 0;
}
