#include"utils/common.hpp"
#include"utils/zk_base.hpp"
int main()
{
    zk_base* base_handle = new zk_base();
    const char* host = "127.0.0.1:2181";
    int timeout = 300;
    const char * context="zk_selection";

    zhandle_t* zk_handle=base_handle->zk_init(host,reinterpret_cast<void *>(zk_base::watcher_global),timeout,context,0);

}