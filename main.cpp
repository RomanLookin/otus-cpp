#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>



class IObserver
{
public:

    virtual void NotifyV(const std::vector<std::string>& vec_str, std::time_t timestamp) = 0;
    virtual ~IObserver() = default;
};

class Terminal : public IObserver
{
public:

    void NotifyV(const std::vector<std::string>& vc, std::time_t timestamp) override
    {
        if(vc.size()>0){
            std::cout << "bulk: ";
            for(size_t n = 0;n < vc.size();n++){
                std::cout << vc.at(n);

                if(n != vc.size()-1){
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


    void NotifyV(const std::vector<std::string>& vc, std::time_t timestamp) override
    {

        if(vc.size() > 0){
            std::string fname = "bulk"+std::to_string(timestamp)+".log";
            std::ofstream file(fname);

            if (file.is_open()) {

                for(size_t n = 0;n < vc.size();n++){

                    file << vc[n];
                    if(n != vc.size()-1){

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


        count_block =0;

    }
    void AddObserver(std::shared_ptr<IObserver> o)
    {
        _obs.push_back(o);
    }

    void setN(unsigned n)
    {
        N = n;
    }



    void SetData(const std::string& cmd) //void* arg)
    {

            if(cmd == "{"){
                if(count_block == 0){
                    Notify();
                }
                count_block++;
            }
            else if(cmd == "}"){
                if(count_block >= 1){
                    count_block--;
                    if(count_block == 0){
                        Notify();
                    }
                }
            }
            else{
                vec_str.push_back(cmd);
                if(vec_str.size() == 1){

                    timestamp = std::time(nullptr);
                }
                if((vec_str.size() == N) && (count_block == 0)){
                    Notify();
                }
            }

    }

    void Notify()
    {



            for (std::shared_ptr<IObserver> o : _obs) {

                o->NotifyV(vec_str, timestamp);
            }
            clear(vec_str);

    }
    void clear(std::vector<std::string>& vec_str)
    {
        vec_str.clear();

    }
    unsigned get_count()
    {
        return count_block;
    }
private:


    std::vector<std::string> vec_str;

    std::time_t timestamp;

    std::list<std::shared_ptr<IObserver>> _obs;
    unsigned N, count_block;
};

class Controller
{
public:

    Controller(unsigned n) : N(n) {}

    void AppRun()
    {
        std::shared_ptr<Terminal> shp_h = std::make_shared<Terminal>();
        std::shared_ptr<FileLogger> shp_fl = std::make_shared<FileLogger>();


        observable.AddObserver(shp_h);
        observable.AddObserver(shp_fl);
        observable.setN(N);


        std::string input;


        while (std::getline(std::cin, input)) {

        //for (;;) {
            //std::getline(std::cin, input);

            if (!input.empty()) {

                observable.SetData(input);
            }
            else {
                std::cout << "Empty command!" << std::endl;
            }
        }
        if(observable.get_count() ==0)
            observable.Notify();
    }
protected:
    Observable observable;
    unsigned N;
};


int main(int argc, char* argv[])
{
    unsigned int N;
    if(argc > 1){
        N = std::stoi(argv[1]);

        Controller c(N);
        c.AppRun();

    }
    return 0;
}
