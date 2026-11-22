#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>
#include <thread.h>

//namespace simple {

std::mutex m;
std::condition_variable cv;
bool ready = false;
bool processed = false;
std::vector<std::string> vec_str;

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> m_queue;  // Внутренний контейнер
    mutable std::mutex m_mutex;  // Мьютекс для защиты доступа
    std::condition_variable m_cond;  // Условная переменная

public:
    // Поместить элемент в очередь
    void push(T item) {
        std::lock_guard<std::mutex> lock(m_mutex);  // Блокировка с автоматическим освобождением
        m_queue.push(item);
        m_cond.notify_one();  // Уведомляем один ожидающий поток
    }

    // Удалить и вернуть элемент из очереди
    T pop() {
        std::unique_lock<std::mutex> lock(m_mutex);  // Для wait() нужен unique_lock
        // Ждём, пока очередь не станет пустой
        m_cond.wait(lock, [this] { return !m_queue.empty(); });
        T item = m_queue.front();
        m_queue.pop();
        return item;
    }

    // Проверить, пуста ли очередь
    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    // Получить размер очереди
    size_t size() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    // Отправить сигнал разрушения (для корректной очистки)
    void signal_destroy() {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_cond.notify_one();
    }
};

class IObserver
{
public:

    virtual void NotifyV() = 0;//const std::vector<std::string>& vec_str, std::time_t timestamp
    virtual ~IObserver() = default;
};

class Terminal : public IObserver
{
public:

    void NotifyV() override //const std::vector<std::string>& vc, std::time_t timestamp
    {

        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return ready;});

        //here out string to terminal


        if((vec_str.size()>0)){ // && (timestamp != 0)
            std::cout << "bulk: ";
            for(size_t n = 0;n < vec_str.size();n++){
                std::cout << vec_str.at(n);

                if(n != vec_str.size()-1){
                    std::cout << ", ";

                }
            }
            std::cout << std::endl;
        }


        processed = true;
        //std::cout << "  Worker thread signals data processing completed\n";

        // Manual unlocking is done before notifying, to avoid waking up
        // the waiting thread only to block again (see notify_one for details)
        lk.unlock();
        cv.notify_one();

    }
};
class FileLogger : public IObserver
{
public:


    void NotifyV() override //const std::vector<std::string>& vc, std::time_t timestamp
    {

        /*if(vc.size() > 0){
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


        }*/
    }

};

struct Parser
{
public:
    Parser(){
        timestamp = 0;
        count_block =0;
    }
    /*void AddObserver(std::shared_ptr<IObserver> o){
        _obs.push_back(o);
    }*/

    void setN(unsigned n){
        N = n;
    }

    void receiveLine(const std::string& cmd) {

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
        /*for (std::shared_ptr<IObserver> o : _obs) {
            o->NotifyV(vec_str, timestamp);
        }

        if(vec_str.size() > 0){
            for(std::string& str : vec_str){
                std::cout << str << ",";
            }
            std::cout << std::endl;
            clear(vec_str, timestamp);
        }*/
        {
            std::lock_guard<std::mutex> lk(m);
            ready = true;
            //std::cout << "test_simple() signals data ready for processing\n";
        }

        //std::cout << "before cv.notify_one in test_simple\n";
        cv.notify_one(); //notify_all();
        //std::cout << "after cv.notify_one in test_simple\n";

        // wait for the worker
        {
            std::unique_lock<std::mutex> lk(m);
            //std::cout << "before cv.wait in test_simple\n";
            cv.wait(lk, []{return processed;});
            //std::cout << "after cv.wait in test_simple\n";

            ready = false;
            processed = false;
            clear(vec_str, timestamp);
        }


    }
    void clear(std::vector<std::string>& vec_str, std::time_t& timestamp){
        vec_str.clear();
        timestamp = 0;
    }
    unsigned get_count(){
        return count_block;
    }
private:
    //std::vector<std::string> vec_str;
    std::time_t timestamp;
    std::list<std::shared_ptr<IObserver>> _obs;
    unsigned N, count_block;
};

struct Handle
{
    Handle(unsigned N_) : N(N_),count_block(0){}
    Parser parser;

    std::string accumulator;
    unsigned N, count_block;
    /*std::string send_data()
    {
        return buffer;
    }*/

};

std::string aaa="";





void* connect(std::size_t bulk)
{
    Handle* hndl=new Handle(bulk);
    hndl->parser.setN(bulk);
    void* vphndl = static_cast<void*>(hndl);
    return vphndl;
}
void receive(void* handle, std::string& line) // const char* data, std::size_t size)
{
    Handle* hndl = static_cast<Handle*>(handle);
    //std::string data_str = data;
    //std::cout << line << std::endl;
    std::size_t pos = line.find("\n", 0);
    while(pos != std::string::npos)
    {
        //std::cout << line << " 0 " << std::to_string(pos) << std::endl << "-----" << std::endl;
        std::string cmd = line.substr( 0, pos);
        line.erase(0, pos+1);//, len);
        aaa += cmd;
        //std::cout << aaa << std::endl;
        hndl->parser.receiveLine(aaa);
        aaa.clear();
        pos = line.find("\n", pos+1);
        //hndl->parser.receiveLine( std::string( cmd ) );

    }
    aaa += line;

    /*for(std::size_t l =0;l< size;l++)
    {
        if(data_str == "{"){
            hndl->count_block++;
            hndl->send_data();
            hndl->buffer.clear();
            hndl->buffer.push_back(*data);
            hndl->send_data();
            hndl->buffer.clear();
        }
        else if(data_str == "}"){
            hndl->count_block--;
            hndl->send_data();
            hndl->buffer.clear();
            hndl->buffer.push_back(*data);
            hndl->send_data();
            hndl->buffer.clear();

        }
        else if(data_str == "/n"){
            //send buffer to parcer
            hndl->send_data();
            hndl->buffer.clear();
        }
        else {
            //hndl->buffer.push_back(*data);
            hndl->buffer = data_str;
        }
        data++;

    }*/


}
/*void disconnect(void* handle)
{
    Handle* hndl = static_cast<Handle*>(handle);
    if(hndl->buffer.size()>0){
        hndl->send_data();
        hndl->buffer.clear();
    }
    delete hndl;
}*/
//}
