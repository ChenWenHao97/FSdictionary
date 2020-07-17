#include"common.hpp"
#include"zk_base.hpp"
zk_base::zk_base():zk_timeout(300),zk_flags(0)
{

}
zk_base::~zk_base()
{

}
zhandle_t * zk_base::zk_init(const char* host,watcher_fn watcher,
                        int timeout,const clientid_t * clientid,void *context,int flags)
{
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    zhandle_t* handle = zookeeper_init(host,watcher,timeout,0,context,flags);
    if(handle == NULL)
    {
        fprintf(stderr,"zk_init error\n");
        exit(EXIT_FAILURE);
    }
    return handle;
}
void zk_exists(zhandle_t* handle,const char* path,int is_watch,struct Stat* state)
{
    int res = zoo_exists(handle,path,is_watch,state);
    if(res)
    {
        fprintf(stderr,"zk_exists error:znode exists\n");
        exit(EXIT_FAILURE);
    }
}
void zk_create(zhandle_t* handle,const char* path,const char* value,int valuelen,
                    const struct ACL_vector* acl,int flags,char* buffer_path,int buffer_len)
{
    int res = zoo_create(handle,path,value,valuelen,acl,flags,buffer_path,buffer_len);
    if(res)
    {
        fprintf(stderr,"zk_create error:create node error\n");
        exit(EXIT_FAILURE);
    }

}
void zk_getchild(zhandle_t* handle,const char* path,int is_watch,struct String_vector* strings)
{
    int res = zoo_get_children(handle,path,is_watch,strings);
    if(res)
    {
        fprintf(stderr,"zk_getchild error:getchild error\n");
        exit(EXIT_FAILURE);
    }
}
void zk_delete(zhandle_t* handle,const char* path,int version)
{
    int res = zoo_delete(handle,path,version);
    if(res)
    {
        fprintf(stderr,"zk_delete error\n");
        exit(EXIT_FAILURE);
    }
}

void watcher_global(zhandle_t* handle,int type,int state,const char* path,void* context,int flags)
{
    std::cout <<"zookpeer init"<<std::endl;
    std::cout<<"type:"<<type<<std::endl;
    std::cout<<"state:"<<state<<std::endl;
    std::cout<<"path:"<<path<<std::endl;
    std::cout<<"context:"<<context<<std::endl;
    std::cout<<"flags:"<<flags<<std::endl;
}
void zk_close(zhandle_t* handle)
{
    zookeeper_close(handle);
}
