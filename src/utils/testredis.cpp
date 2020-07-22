#include"common.hpp"
#include"Redis.hpp"
int main()
{
    Redis *handle = new Redis();
    if(!handle->rd_connect("127.0.0.1",6379))
    {
        std::cout<<"main create connect error"<<std::endl;
        return 0;
    }
    std::cout<<handle->rd_get("hello")<<std::endl;
    delete handle;

    return 0;
}
