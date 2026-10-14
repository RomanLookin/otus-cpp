#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <list>




class IObserver
{
public:

    virtual void NotifyV(std::vector<std::string>* vec_str, std::vector<time_t>& vt) = 0;

    virtual ~IObserver() = default;
};

class Terminal : public IObserver
{
public:

    void NotifyV(std::vector<std::string>* vc, std::vector<time_t>& vt) override
    {
        if((*vc).size()>0){
            std::cout << "bulk: ";
            for(size_t n = 0;n < (*vc).size();n++){
                std::cout << (*vc).at(n);

                if(n != (*vc).size()-1){
                    std::cout << ", ";

                }
            }
            std::cout << std::endl;
        }

    }
};
class FileLogger : public IObserver
{
public:

    void NotifyV(std::vector<std::string>* vc, std::vector<time_t>& vt) override
    {
        if(((*vc).size() > 0) && (vt.size() > 0)){

            std::string fname = "bulk"+std::to_string(vt.at(0))+".log";
            std::ofstream file(fname);

            if (file.is_open()) {

                for(size_t n = 0;n < (*vc).size();n++){

                    file << (*vc)[n];
                    if(n != (*vc).size()-1){

                        file << ", ";
                    }
                }

            } else {
                std::cout << "Ошибка при открытии файла!" << std::endl;
            }


        }
    }
};


class Observable
{
public:

    Observable()
    {

        vec_str = new std::vector<std::string>;
        count_block =0;

    }
    void AddObserver(IObserver* o)
    {
        _obs.push_back(o);
    }
    ~Observable()
    {
        delete vec_str;

    }
    void setN(unsigned n)
    {
        N = n;
    }



    void SetData(void* arg)
    {
        if (arg) {


            std::string* str = static_cast<std::string*>(arg);

            if(*str == "{"){

                if(count_block == 0){
                    Notify();

                }
                count_block++;



            }
            else if(*str == "}"){
                if(count_block >= 1){
                    count_block--;
                    if(count_block == 0){
                        Notify();
                    }
                }
            }
            else{
                vec_str->push_back(*str);
                if((*vec_str).size() == 1){
                    std::time_t result = std::time(nullptr);
                    vec_time.push_back(result);
                }
                if(((*vec_str).size() == N) && (count_block == 0)){
                    Notify();
                }
           }
        }
    }

    void Notify()
    {


            for (IObserver* o : _obs) {

                o->NotifyV(vec_str, vec_time);
            }
            clear(vec_str, vec_time);

    }
    void clear(std::vector<std::string>* vec_str, std::vector<time_t>& vt)
    {
        (*vec_str).clear();
        vt.clear();
    }
private:

    std::vector<std::string>* vec_str = nullptr;
    std::vector<time_t> vec_time;

    std::list<IObserver*> _obs;
    unsigned N, count_block;
};

class Controller
{
public:

    Controller(unsigned n){
        N = n;

        Observable observable;
    }

    void AppRun()
    {
        observable.AddObserver(new Terminal());
        observable.AddObserver(new FileLogger());
        observable.setN(N);


        std::string input;


        while (std::getline(std::cin, input)) {

        //for (;;) {
            //std::getline(std::cin, input);

            if (!input.empty()) {

                observable.SetData((void*)&input);
            }
            else {
                std::cout << "Empty command!" << std::endl;
            }
        }
    }
protected:
    Observable observable;
    unsigned N;
};


int main(int argc, char* argv[])
{
    unsigned int N;

    N = std::stoi(argv[1]);
    Controller c(N);
    c.AppRun();


    return 0;
}
