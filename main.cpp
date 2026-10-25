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
    /*struct iterator
    {
         typedef typename std::vector<T>::iterator It;
         It it1, it2, it3;
         iterator(It it1, It it2, It it3) : it1(it1), it2(it2), it3(it3) {}
         iterator & operator++()
         {
            ++it1; ++it2; ++it3; return *this;
         }

         std::tuple<int, int, int> operator *()
         {
             std::tuple<int, int, int> tpl = {*it1, *it2, *it3};
             return tpl;//*it1;
         }
         bool operator == (const iterator &other)
         {
             return !(*this != other);
         }
         bool operator != (const iterator &other)
         {
             return it1 != other.it1 && it2 != other.it2 && it3 != other.it3;
         }
    };*/

    struct iterator
        {
             typedef typename std::map<std::pair<int, int>, T>::iterator It;
             It it1;//, it2, it3;
             iterator(It it1) : it1(it1) {}
             iterator & operator++()
             {
                ++it1;  return *this;
             }

             std::tuple<int, int, int> operator *()
             {
                 //std::tuple<int, int, int> tpl = {*it1, *it2, *it3};
                 std::map<std::pair<int, int>, T> pmap=*it1;
                 std::pair<int, int> pairmap=pmap.key();
                 int valmap=static_cast<int>(pmap.value());
                 std::tuple<int, int, int> tpl = {pairmap.first, pairmap.second, valmap};

                 return tpl;//*it1;
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

    /*wrapper(std::vector<T> &v1,  std::vector<T> &v2,  std::vector<T> &v3)
      : begin_(v1.begin(), v2.begin(), v3.begin()),end_(v1.end(), v2.end(), v3.end())*/
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
    /*std::tuple<int, int, int> operator=(const wrapper & other)
    {
        //++it1; ++it2; return *this;
        std::tuple<int, int, int> tr ={other.it1, other.it2, other.it3};
        return tr;
    }*/
    /*std::tuple<int, int, int> operator*()
    {
        //++it1; ++it2; return *this;
        std::tuple<int, int, int> tr ={*it1, *it2, *it3};
        return tr;
    }*/
    
};


/*template<typename T>
class MyIterator : public std::iterator<std::random_access_iterator_tag, T> {
private:
    T* ptr_; // Указатель на текущий элемент
    size_t index_; // Индекс элемента (для поддержки RandomAccessIterator)
public:
    // Конструктор от указателя и индекса
    MyIterator(T* ptr, size_t index) : ptr_(ptr), index_(index) {}

    // Разыменование
    T& operator*() const { return *ptr_; }

    // Оператор ->
    T* operator->() const { return ptr_; }

    // Префиксный инкремент
    MyIterator& operator++() {
        ++ptr_;
        return *this;
    }

    // Постфиксный инкремент
    MyIterator operator++(int) {
        MyIterator copy = *this;
        ++ptr_;
        return copy;
    }

    bool operator==(const MyIterator& other) const {// Сравнение на равенство
        return ptr_ == other.ptr_;
    }

    bool operator!=(const MyIterator& other) const {// Сравнение на неравенство
        return ptr_ != other.ptr_;
    }
};*/

template<typename T>
class Matrix
{
    public:
    Matrix(){}
    /*std::vector<int> X;
    std::vector<int> Y;
    std::vector<int> V;
    int index;*/
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
                        /*matrix.index = -1;
                        for(size_t l=0;l<matrix.X.size();l++){
                            if((matrix.X.at(l) == x) && (matrix.Y.at(l) == y)){
                                matrix.index = l;
                            }
                        }
                        if(matrix.index == -1){
                            matrix.X.push_back(x);
                            matrix.Y.push_back(y);
                        }*/
                        //std::cout << "ctor cell" << endl;
                    }


                    /*int operator[](int x){
                        
                        return x;
                    }*/

                    //void operator=(int v){
                    void operator=(T v) const {
                        /*std::cout << "oprator= x=" << to_string(x) << " y=" << to_string(y)
                                  << " v=" << to_string(v) << endl;*/
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

                        /*if(v != 0){
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

                        }*/
                        
                    }

                    operator int() const {
                        /*std::cout << "oprator int x=" << to_string(x) << " y=" << to_string(y)
                                  << " val=" << to_string(val) << endl;*/

                        std::pair<int, int> pair_serc={x, y};
                        if(matrix.mp.count(pair_serc)){
                            return matrix.mp[pair_serc];
                        }
                        else {
                            return 0;
                        }

                        /*if(matrix.X.size() == matrix.V.size()){
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
                        return 0;*/

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
        /*if((X.size() == Y.size()) && (X.size() == V.size()))
            return X.size();
        else return -1;*/
        return mp.size();
    }
    std::map<std::pair<int, int>, T>& get_matrix()
    {
        return mp;
    }


};
/*template<typename T>
class VectorPair {
public:
    using Iterator = typename std::vector<T>::iterator;

    Iterator begin() const { return it1_.begin(); }
    Iterator end() const { return it2_.end(); }

private:
    Iterator it1_, it2_;

    Iterator make_iterator(Iterator it1, Iterator it2) {
        return Iterator(it1, it2);
    }
};

template<typename T>
class VectorPair<T>::Iterator
{
public:
    using IteratorType = typename std::vector<T>::iterator;

    IteratorType it1, it2;

    Iterator operator++() {
        ++it1;
        ++it2;
        return *this;
    }

    bool operator!=(const Iterator& other) const {
        return it1 != other.it1 && it2 != other.it2;
    }

    T& operator*() {
        return *it1; // или *it2, в зависимости от задачи
    }
};*/

int main()
{
    Matrix<int> m;

    /*m[0][0] = 1;
    std::cout << "------" << endl;
    int k=m[0][0];
    std::cout << "k=" << to_string(k) << endl;
    std::cout << "------" << endl;
    m[0][0] = 0;
    std::cout << "------" << endl;
    k=m[0][0];
    std::cout << "k=" << to_string(k) << endl;
    std::cout << "------" << endl;*/


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


    /*m.X.push_back(11);
    m.Y.push_back(12);
    m.V.push_back(13);
    m.X.push_back(21);
    m.Y.push_back(22);
    m.V.push_back(23);*/
    std::cout << m.size() << std::endl;
    //wrapper<int> w(m.X, m.Y, m.V);
    wrapper<int> w(m.get_matrix());
    for(auto c : w)
    {
        int x,y,z;
        //std::tie(x,y,z) = {*c.it1, *c.it2, *c.it3};
        //x = *c.it1;
        //y = *c.it2;
        //z = *c.it3;
        //std::tuple(x,y, z) = c;
        std::tie(x,y, z) = c;
        std::cout << x << y << z << std::endl;
    }

    

    return 0;
}
