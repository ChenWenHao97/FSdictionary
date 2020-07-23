#include "Redis.hpp"
#include "common.hpp"
Redis::Redis() : handle(NULL) {}
Redis::~Redis()
{
    this->rd_close(this->handle);
    this->handle = NULL;
}
bool Redis::rd_connect(std::string host, int port)
{
    this->handle = redisConnect(host.c_str(), port);
    if (this->handle == NULL || this->handle->err)
    {
        std::cout << "redis connect error:" << this->handle->errstr << std::endl;
        return false;
    }
    return true;
}
std::string Redis::rd_get(std::string key)
{
 
        redisReply *reply = (redisReply *)redisCommand(this->handle, "GET %s", key.c_str());
        // std::cout<<"after rd_get "<<std::endl;
        if(reply->len ==0)
        {
            std::cout<<"rd_get null"<<std::endl;
            return "";
        }
        std::string value(reply->str);
        // 释放redisCommand执行后返回的的redisReply所占用的内存
        freeReplyObject(reply);
        return value;
   
    // if(!(reply->type == REDIS_REPLY_STATUS))
    // if(reply->type == REDIS_REPLY_ERROR)
    // if(reply == "nil")
    // {
    //     std::cout<<"rd_get func error"<<std::endl;
    //     return "";
    // }
}
void Redis::rd_set(std::string key, std::string value)
{
    redisContext *reply = (redisContext *)redisCommand(this->handle, "SET %s %s", key.c_str(), value.c_str());
    if ((reply->err) != 0)
    {
        std::cout << "rd_set func error" << std::endl;
    }
}
void Redis::rd_close(redisContext *handle)
{
    redisFree(this->handle);
}
