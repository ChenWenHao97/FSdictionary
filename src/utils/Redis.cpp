#include"Redis.hpp"
Redis::Redis()
{

}
Redis::~Redis()
{
    this->rd_close(this->handle);
    this->handle=NULL;
}
bool Redis::rd_connect(std::string host,int port)
{
    this->handle = redisConnect(host.c_str(),port);
    if(this->handle !=NULL && this->handle->err)
    {
        std::cout<<"redis connect error:"<<this->handle->errstr<<std::endl;
        return false;
    }
    return true;
}
std::string Redis::rd_get(std::string key)
{
    redisReply* reply= (redisReply*)redisCommand(this->handle,"GET %s",key.c_str());
    std::string value = reply->str;
    // 释放redisCommand执行后返回的的redisReply所占用的内存
    freeReplyObject(reply);
    return value;
}
void Redis::rd_set(std::string key,std::string value)
{
    redisCommand(this->handle,"SET %s %s",key.c_str(),value.c_str());
}
void Redis::rd_close(redisContext* handle)
{
    redisFree(this->handle);
}