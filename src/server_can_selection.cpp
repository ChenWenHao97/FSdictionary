#include "utils/common.hpp"
#include "utils/zk_base.hpp"
#include "utils/Redis.hpp"
#include "utils/echo_service.pb.h"
void get_node_name(char *buf, char *node_name);
void is_leader(zhandle_t *zk_handle, const char *father_node_name, const char *child_node, const char *set_registry_info);
void election_child_watcher(zhandle_t *zk_handle, int type, int state, const char *path, void *watcherCtx);
std::string get_translate(std::string key);
struct watcher_node_info
{
    zhandle_t *handle;
    std::string father_node_name;
    std::string child_node_name;
    std::string set_registry_info;
};
class EchoServerImpl : public fs::EchoServer
{
public:
    EchoServerImpl() {}
    virtual ~EchoServerImpl() {}

private:
    virtual void Echo(google::protobuf::RpcController *controller,
                      const fs::EchoRequest *request,
                      fs::EchoResponse *response,
                      google::protobuf::Closure *done)
    {
        sofa::pbrpc::RpcController *cntl =
            static_cast<sofa::pbrpc::RpcController *>(controller);
        SLOG(NOTICE, "Echo():request message from %s:%s",
             cntl->RemoteAddress().c_str(), request->message().c_str());
        
        response->set_message(get_translate(request->message()));
        done->Run(); //֪ͨrpcϵͳ������ɣ���������response
    }
};
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "input server address and port!" << std::endl;
    }
    zk_base *base_handle = new zk_base();
    const char *zk_host = "127.0.0.1:2181";
    const char *server_host = argv[1];
    int timeout = 300;
    const char *context = "zk_selection";
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    zhandle_t *zk_handle = base_handle->zk_init(zk_host,
                                                reinterpret_cast<watcher_fn>(zk_base::watcher_global),
                                                timeout, 0, (void *)context, 0);
    char *buf = new char[256];
    std::string father_node_name = "/election";
    std::string znode_name = "/election/member";
    std::string alias_name = "znode";
    base_handle->zk_create(zk_handle,
                           znode_name.c_str(),
                           alias_name.c_str(),
                           alias_name.size(),
                           &ZOO_OPEN_ACL_UNSAFE, //ͨ����acl����
                           ZOO_SEQUENCE | ZOO_EPHEMERAL,
                           buf,
                           256);
    char *child_node_name = new char[256];
    get_node_name(buf, child_node_name); //��ȡ�������ӽڵ�����
    const char *set_registry_info = server_host;

    is_leader(zk_handle, father_node_name.c_str(), child_node_name, set_registry_info); //�ж��Ƿ�Ϊleader�ڵ�
    struct String_vector child_infos;
    struct watcher_node_info node_info;
    node_info.handle = zk_handle;
    node_info.father_node_name = father_node_name;
    node_info.child_node_name = child_node_name;
    node_info.set_registry_info = server_host;
    struct Stat stat; //�ƶ��ڵ���Ϣ
    //�õ�ָ��node��Ϣ��״̬
    base_handle->zk_wgetchild2(zk_handle, father_node_name.c_str(), election_child_watcher, &node_info, &child_infos, &stat);

    //rpc����
    SOFA_PBRPC_SET_LOG_LEVEL(NOTICE);

    sofa::pbrpc::RpcServerOptions options;
    options.work_thread_num = 2;
    sofa::pbrpc::RpcServer rpc_server(options);

    if (!rpc_server.Start(server_host))
    {
        SLOG(ERROR, "start server failed");
        return EXIT_FAILURE;
    }
    fs::EchoServer *echo_service = new EchoServerImpl();
    if (!rpc_server.RegisterService(echo_service))
    {
        SLOG(ERROR, "register server failed");
        return EXIT_FAILURE;
    }
    rpc_server.Run();
    rpc_server.Stop();

    base_handle->zk_close(zk_handle);
    delete echo_service;
    delete base_handle;
    delete buf;
    delete child_node_name;
    return EXIT_SUCCESS;
}

void get_node_name(char *buf, char *node_name)
{

    const char *p = buf;
    int i;
    for (i = strlen(buf) - 1; i >= 0; i--)
    {
        if (*(p + i) == '/')
        {
            break;
        }
    }

    strcpy(node_name, p + i + 1);
}
void is_leader(zhandle_t *zk_handle, const char *father_node_name, const char *child_node, const char *set_registry_info)
{
    struct String_vector child_infos;
    zk_base *base_handle = new zk_base();
    base_handle->zk_getchild(zk_handle, father_node_name, 0, &child_infos);
    for (int i = 0; i < child_infos.count; i++)
    {
        if (strcmp(child_node, child_infos.data[i]) > 0) //�ڵ�ԽС��Խ��leader
        {
            std::cout << "this is " << child_node << std::endl;
            std::cout << "I am a follower" << std::endl;
            return;
        }
    }
    std::cout << "this is " << child_node << std::endl;
    std::cout << "I am a leader" << std::endl;

    std::cout << "child lists:" << std::endl;
    std::string reg_node;
    for (int i = 0; i < child_infos.count; i++)
    {
        // std::cout<<child_infos.data[i]<<std::endl;
        int pos = std::string(child_infos.data[i]).find("registry");
        if (pos != -1)
        {
            //��ȡ���ڵ����б��ҵ�registry�ڵ�
            reg_node = std::string(child_infos.data[i]).substr(pos);
            break;
        }
    }
    //�������ýڵ�
    std::string path = std::string(father_node_name) + "/" + reg_node;

    std::cout << "registry path:" << path << std::endl;
    struct Stat stat;
    char *get_node_info = new char[256];
    int get_node_len;
    base_handle->zk_get(zk_handle, path.c_str(), 1, get_node_info, &get_node_len, &stat);
    // std::cout <<"get_node:"<<std::endl;
    // std::cout<<"info:"<<get_node_info<<std::endl;

    // std::cout<<"stat.version"<<stat.version<<std::endl;�޸ĵİ汾�ã�����dataversion
    //��registry�ڵ��ip��ַ�����޸ģ�����ʱ�̱������µ�leader ip��
    base_handle->zk_set(zk_handle, path.c_str(), set_registry_info, strlen(set_registry_info), stat.version);
    delete base_handle;
    delete get_node_info;
}
void election_child_watcher(zhandle_t *zk_handle, int type, int state, const char *path, void *watcherCtx)
{
    struct watcher_node_info *para = (struct watcher_node_info *)watcherCtx;
    struct String_vector child_infos;
    struct Stat stat;
    zk_base *base_handle = new zk_base();
    //���¼���
    base_handle->zk_wgetchild2(para->handle, para->father_node_name.c_str(), election_child_watcher, watcherCtx, &child_infos, &stat);
    is_leader(para->handle, (para->father_node_name).c_str(), (para->child_node_name).c_str(), (para->set_registry_info).c_str());
    delete base_handle;
}
std::string get_translate(std::string key)
{
    std::cout << "################before new################" << std::endl;
    Redis *rd_handle = new Redis();
    std::cout << "################before rd_connect################" << std::endl;
    if (!rd_handle->rd_connect("127.0.0.1", 6379))
    {
        std::cout << "server create rd_connect error" << std::endl;
    }
    std::cout << "################before rd_get################" << std::endl;
    std::string rd_value = rd_handle->rd_get(key);
    std::cout << "#################after rd_get###############" << std::endl;
    std::cout << "get redis value:" << rd_value << std::endl;
    return rd_value;
}
