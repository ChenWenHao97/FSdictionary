#include"utils/common.hpp"
#include"utils/zk_base.hpp"
void get_node_name(char* buf,char* node_name);
void is_leader(zhandle_t* zk_handle,const char* father_node_name,const char* child_node);
void election_child_watcher(zhandle_t* zk_handle,int type,int state,const char* path,void* watcherCtx);
struct watcher_node_info{
    zhandle_t* handle;
    std::string father_node_name;
    std::string child_node_name;
};
int main()
{
    zk_base* base_handle = new zk_base();
    const char* host = "127.0.0.1:2181";
    int timeout = 300;
    const char * context="zk_selection";
     zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    zhandle_t* zk_handle=base_handle->zk_init(host,
                                            reinterpret_cast<watcher_fn>(zk_base::watcher_global),
                                            timeout,0,(void *)context,0);
    char* buf = new char[256];
    std::string father_node_name = "/election";
    std::string znode_name = "/election/member";
    std::string alias_name = "znode";
    base_handle->zk_create(zk_handle,
                        znode_name.c_str(),
                        alias_name.c_str(),
                        alias_name.size(),
                        &ZOO_OPEN_ACL_UNSAFE,//ͨ����acl����
                        ZOO_SEQUENCE|ZOO_EPHEMERAL,
                        buf,
                        256);

    char *child_node_name = new char[256];
    get_node_name(buf,child_node_name);

    is_leader(zk_handle,father_node_name.c_str(),child_node_name);
    struct String_vector child_infos;
    struct watcher_node_info node_info;
    node_info.handle = zk_handle;
    node_info.father_node_name = father_node_name;
    node_info.child_node_name = child_node_name;
    struct Stat stat;//�ƶ��ڵ���Ϣ
    //�õ�ָ��node��Ϣ��״̬
    base_handle->zk_wgetchild2(zk_handle,father_node_name.c_str(),election_child_watcher,&node_info,&child_infos,&stat);
    sleep(10000);
    base_handle->zk_close(zk_handle);
}
void get_node_name(char* buf,char* node_name)
{

    const char *p = buf;
    int i;
    for (i = strlen(buf) - 1; i >= 0; i--) 
    {
        if (*(p + i) == '/') {
            break;
        }
    }

    strcpy(node_name, p + i + 1);
}
void is_leader(zhandle_t*zk_handle,const char* father_node_name,const char* child_node)
{
    struct String_vector child_infos;
    zk_base *base_handle = new zk_base();
    base_handle->zk_getchild(zk_handle,father_node_name,0,&child_infos);
    for(int i = 0;i < child_infos.count;i++)
    {
        if(strcmp(child_node,child_infos.data[i])>0)//�ڵ�ԽС��Խ��leader
        {
            std::cout <<"this is "<<child_node<<std::endl;
            std::cout <<"I am a follower"<<std::endl;
            return;
        }
    }
    std::cout <<"this is "<<child_node<<std::endl;
    std::cout <<"I am a leader"<<std::endl;

}
void election_child_watcher(zhandle_t* zk_handle,int type,int state,const char* path,void* watcherCtx)
{
    struct watcher_node_info* para = (struct watcher_node_info*)watcherCtx;
    struct String_vector child_infos;
    struct Stat stat;
    zk_base* base_handle = new zk_base();
    //���¼���
    base_handle->zk_wgetchild2(para->handle,para->father_node_name.c_str(),election_child_watcher,watcherCtx,&child_infos,&stat);
    is_leader(para->handle,(para->father_node_name).c_str(),(para->child_node_name).c_str());
}