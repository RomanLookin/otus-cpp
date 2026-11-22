#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <thread>
#include "async.h"
//#include <pthread.h>

/*class IObserver
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
        if((vc.size()>0) && (timestamp != 0)){
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

};*/


/*class Observable
{
public:
    Observable(){
        timestamp = 0;
        count_block =0;
    }
    void AddObserver(std::shared_ptr<IObserver> o){
        _obs.push_back(o);
    }

    void setN(unsigned n){
        N = n;
    }

    void SetData(const std::string& cmd) {

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

    void Notify(){
        for (std::shared_ptr<IObserver> o : _obs) {
            o->NotifyV();//vec_str, timestamp);
        }
        clear(vec_str, timestamp);
    }

    void clear(std::vector<std::string>& vec_str, std::time_t& timestamp){
        vec_str.clear();
        timestamp = 0;
    }
    unsigned get_count(){
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
                //simple::connect(N);
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
};*/

std::string read(std::string& input_line, size_t len){
    //int numb_symbol = 3;//читаем по 3 символа
    size_t pos = 0;
    std::string str_ret = input_line.substr(pos, len); // size_t len = npos)
    input_line.erase(pos, len);
    return str_ret;
}

/*std::mutex m;
std::condition_variable cv;
bool ready = false;
bool processed = false;

void thread_terminal(){
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});

    //here out string to terminal

    processed = true;
    //std::cout << "  Worker thread signals data processing completed\n";

    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
}*/

/*std::string aaa="";
void receive1(std::string& line) //void* handle, const char* data, std::size_t size)
{
    //Handle* hndl = static_cast<Handle*>(handle);
    //std::string data_str = data;
    //std::cout << line << std::endl;
    std::size_t pos = line.find("\n", 0);
    while(pos != std::string::npos)
    {
        //std::cout << line << " 0 " << std::to_string(pos) << std::endl << "-----" << std::endl;
        std::string cmd = line.substr( 0, pos);
        line.erase(0, pos+1);//, len);
        aaa += cmd;
        std::cout << aaa << std::endl;
        aaa.clear();
        pos = line.find("\n", pos+1);
        //hndl->parser.receiveLine( std::string( cmd ) );

    }
    aaa += line;



    //std::cout << line << " 0 " << std::endl << "-----" << std::endl;

}*/
int main()//int argc, char* argv[])
{
    std::string input_str1 = "cmd1\ncmd2\ncmd3\ncmd4\ncmd5\n";
    std::string input_str2 = "cmd1\ncmd2\n{\ncmd3\ncmd4\n}\n{\ncmd5\ncmd6\n{\ncmd7\ncmd8\n}\ncmd9\n}\n{\ncmd10\ncmd11\n";

    void* ctx = connect(3);//static_cast(3)); // присоединились

    //std::shared_ptr<Terminal> shp_h = std::make_shared<Terminal>();
    //std::shared_ptr<FileLogger> shp_fl = std::make_shared<FileLogger>();
    Terminal shp_h;

    std::thread t(&Terminal::NotifyV, std::ref(shp_h));
    //std::thread t([&shp_h](){ shp_h.NotifyV(); });
    //Observable observable;
    //observable.AddObserver(shp_h);
    //observable.AddObserver(shp_fl);



    while(input_str2.size() > 0){
        std::string str_new = read(input_str2, 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        //std::cout << str_new << std::endl << "-----" << std::endl;
        if(str_new.size() > 0) {
            //receive(ctx, buffer);
            receive(ctx, str_new);
        } else if (str_new.size() == 0) {
            break;
        } /*else if (errno != EINTR) {
                    std::cerr << "Error reading stdin." << std::endl;
                    break;
        }*/
    }
    t.join();
    /*unsigned int N;
    if(argc > 1){
        N = std::stoi(argv[1]);

        Controller c(N);
        c.AppRun();

    }*/
    return 0;
}
