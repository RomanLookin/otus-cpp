#include <iostream>

namespace simple {
struct Handle
{
    Handle(unsigned N_) : N(N_),count_block(0){}
    std::string buffer;
    unsigned count_block, N;
    std::string send_data()
    {
        return buffer;
    }

};







void* connect(std::size_t bulk)
{
    Handle* hndl=new Handle(bulk);
    void* vphndl = static_cast<void*>(hndl);
    return vphndl;
}
void receive(void* handle, const char* data, std::size_t size)
{
    Handle* hndl = static_cast<Handle*>(handle);
    for(int l =0;l< size;l++)
    {
        if(*data == '{'){
            hndl->count_block++;
            hndl->send_data();
            hndl->buffer.clear();
            hndl->buffer.push_back(*data);
            hndl->send_data();
            hndl->buffer.clear();
        }
        else if(*data == '}'){
            hndl->count_block--;
            hndl->send_data();
            hndl->buffer.clear();
            hndl->buffer.push_back(*data);
            hndl->send_data();
            hndl->buffer.clear();

        }
        else if(*data == '/n'){
            //send buffer to parcer
            hndl->send_data();
            hndl->buffer.clear();
        }
        else {
            hndl->buffer.push_back(*data);
        }
        data++;

    }


}
void disconnect(void* handle)
{
    Handle* hndl = static_cast<Handle*>(handle);
    if(hndl->buffer.size()>0){
        hndl->send_data();
        hndl->buffer.clear();
    }
    delete hndl;
}
}
