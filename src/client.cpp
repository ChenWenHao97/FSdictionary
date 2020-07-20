#include"utils/common.hpp"
#include"utils/zk_base.hpp"
int main(int argc,char** argv)
{
    if (argc < 2)
    {
        std::cout << "input server address and port!" << std::endl;
    }
    zk_base *base_handle = new zk_base();
    const char *host = argv[1];
    int timeout = 300;
    const char *context = "client_query";
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    zhandle_t *zk_handle = base_handle->zk_init(host,
                                                reinterpret_cast<watcher_fn>(zk_base::watcher_global),
                                                timeout, 0, (void *)context, 0);
    const char * father_node_name = "/election";
    struct Stat stat;
    base_handle->zk_exists(zk_handle,father_node_name,1,&stat);

    struct String_vector child_infos;
    base_handle->zk_getchild(zk_handle, father_node_name, 0, &child_infos);
   
    std::string reg_node;
    for (int i = 0; i < child_infos.count; i++)
    {
        // std::cout<<child_infos.data[i]<<std::endl;
        int pos = std::string(child_infos.data[i]).find("registry");
        if (pos != -1)
        {
            //获取父节点子列表并找到registry节点
            reg_node = std::string(child_infos.data[i]).substr(pos);
            break;
        }
    }
    //构建设置节点
    std::string path = std::string(father_node_name) + "/" + reg_node;
    char *get_node_info = new char[256];
    int get_node_len;
    base_handle->zk_get(zk_handle, path.c_str(), 1, get_node_info, &get_node_len, &stat);
    std::cout<<"get_node_info:"<<get_node_info<<std::endl;//获取到提供服务的ip地址以及端口



}