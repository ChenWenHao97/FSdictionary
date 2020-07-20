#include<zookeeper/zookeeper.h>
#include<zookeeper/zookeeper_log.h>
#ifndef ZK_BASE_HPP
#define ZK_BASE_HPP
class zk_base{
    public:
        zk_base();
        ~zk_base();
        zhandle_t * zk_init(const char* host,watcher_fn watcher,
                        int timeout,const clientid_t * clientid,void *context,int flags);
        void zk_exists(zhandle_t* handle,const char* path,int is_watch,struct Stat* state);//¼ì²é´æÔÚ
        void zk_create(zhandle_t* handle,const char* path,const char* value,int valuelen,
                    const struct ACL_vector* acl,int flags,char* buffer_path,int buffer_len);
        void zk_get(zhandle_t* zk_handle,const char* path,int watch,char* buff,int* buff_len,struct Stat* stat);
        void zk_set(zhandle_t* zk_handle,const char* path,const char* buff,int buff_len,int dataversion);
        void zk_getchild(zhandle_t* handle,const char* path,int watch,struct String_vector* child_infos);
        void zk_wgetchild2(zhandle_t* handle,const char* path,watcher_fn watcher,
                        void* wathcerCtx,struct String_vector* child_infos,struct Stat* stat);
        void zk_delete(zhandle_t* handle,const char* path,int version);
        static void watcher_global(zhandle_t* handle,int type,int state,const char* path,void* context);
        void zk_close(zhandle_t* handle);
    private:
        int zk_timeout;
        clientid_t zk_clientid;
        int zk_flags;
};
#endif