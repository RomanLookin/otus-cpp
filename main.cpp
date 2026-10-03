#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


template<typename T>
class SparseMatrix
{
    private:
            int m, n;
            std::vector<T> vals;//* vals;
            std::vector<int> rows, cols;//* rows, * cols;

public:
                // === CREATION ==============================================
                SparseMatrix(int lines = 0, int columns = 0)
                    : m(lines), n(columns){}; //
                SparseMatrix(int n); // square matrix n×n
                
                T get(int row, int col)// const;
                {
                    if(rows.size() !=0){
                        for(size_t ind=0;ind<rows.size();ind++){
                            if((rows.at(ind) == row) && (cols.at(ind) == col))
                                return vals.at(ind);

                        }
                    }
                    return 0;

                }
        //SparseMatrix & set(T val, int row, int col)//{
        void set(T val, int row, int col)//;
        {
            int remove_ind =-1;
            if((rows.empty()) && (cols.empty()) && (val != 0)){
                        rows.push_back(row);
                        cols.push_back(col);
                        vals.push_back(val);
                    }
            else{
                bool add_v = true;
                        for(size_t ind=0;ind<rows.size();ind++){

                            if((rows.at(ind) == row) && (cols.at(ind) == col)){
                                if(val != 0){
                                    vals.at(ind) = val;


                                }
                                else{
                                    remove_ind = ind;

                                }
                                add_v = false;
                                //break;
                            }
                        }
                        if(add_v && (val != 0)){
                            rows.push_back(row);
                            cols.push_back(col);
                            vals.push_back(val);
                        }
                        if(remove_ind != -1){
                            auto iterr = rows.cbegin();
                            rows.erase(iterr + remove_ind);
                            auto iterc = cols.cbegin();
                            cols.erase(iterc + remove_ind);
                            auto iterv = vals.cbegin();
                            vals.erase(iterv + remove_ind);
                        }

                    }

                }

        int size(){
            return rows.size();
        }

        template<typename X>
        friend std::ostream& operator << (std::ostream& os, const SparseMatrix<X> & matrix)
        {
            if(matrix.rows.size() !=0){
                for(size_t ind=0;ind<matrix.rows.size();ind++){
                    os << to_string(matrix.vals.at(ind)) << " " <<
                                 to_string(matrix.rows.at(ind)) << " " <<
                                 to_string(matrix.cols.at(ind)) << std::endl;
                    //if((rows->at(ind) == row) && (cols->at(ind) == col))
                        //return vals->at(ind);

                }
            }
            return os;
        }

        };

//template<typename T>
class Matrix
{
    public:
    Matrix();
    //std::vector<T> vals;
    //std::vector<int> vals;


    //int& operator[](int x){return vals[x];}
    /*Matrix & set(int val, int row, int col);
    int get(int row, int col) const;*/

    struct ProxyRow{
        int* row;
        int& operator[](int n){return row[n];}
    };

    std::vector<ProxyRow> vals;
    std::vector<int> rows, cols;
    //Matrix(int n); // square matrix n×n
    //Matrix(int rows, int columns);
    ProxyRow& operator[](int x){return vals[x];}

//protected:
    //int m, n;
};

int main()
{
 

    SparseMatrix<int> sprsmtrx;
    int matrix_size = 10;
    for(int i=0;i<matrix_size;i++){
        sprsmtrx.set(i, i, i);
    }
    for(int i=matrix_size-1;i>=0;i--){//9 8 .. 1 0
        sprsmtrx.set(9-i, 9-i, i);
    }
    std::string line;
    for(int nr=1;nr < 9;nr++){
        for(int nc=1;nc < 9;nc++){

            int val = sprsmtrx.get(nr, nc);
            //if(val)
                line += to_string(val)+" ";
            //else
            //    line += to_string(0)+" ";
        }
        std::cout << line << endl;
        line.clear();

    }
    std::cout << to_string(sprsmtrx.size()) << endl;

    cout << sprsmtrx;
    return 0;
}
