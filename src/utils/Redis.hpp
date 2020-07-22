#ifndef REDIS_HPP
#define REDIS_HPP
#include"common.hpp"
class Redis{
    public:
        Redis();
        ~Redis();
        bool rd_connect(std::string host,int port);
        std::string rd_get(std::string key);
        void rd_set(std::string key,std::string value);
        void rd_close(redisContext* handle);
    private:
        redisContext* handle;
};
#endif