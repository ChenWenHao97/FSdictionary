#include"utils/common.hpp"
#include"utils/zk_base.hpp"
#include"utils/echo_service.pb.h"
int main(int argc,char** argv)
{
    if (argc < 2)
    {
        std::cout << "please input word!" << std::endl;
    }
    std::string word(argv[1]);
    zk_base *base_handle = new zk_base();
    const char *zk_host = "127.0.0.1:2181";
    int timeout = 3000;
    const char *context = "client_query";
    zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
    zhandle_t *zk_handle = base_handle->zk_init(zk_host,
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
            //��ȡ���ڵ����б��ҵ�registry�ڵ�
            reg_node = std::string(child_infos.data[i]).substr(pos);
            break;
        }
    }
    //�������ýڵ�
    std::string path = std::string(father_node_name) + "/" + reg_node;
    char *get_node_info = new char[256];
    int get_node_len;
    base_handle->zk_get(zk_handle, path.c_str(), 1, get_node_info, &get_node_len, &stat);
    // std::cout<<"################################################"<<std::endl;
    // std::cout<<"###############get_node_info####################"<<std::endl;
    // std::cout<<get_node_info<<std::endl;
    const char* server_host = get_node_info;//��ȡ���ṩ�����ip��ַ�Լ��˿�



    //rpc
    // SOFA_PBRPC_SET_LOG_LEVEL(NOTICE);

    // ����RpcClient���󣬹���RPC��������Դ
    // ͨ����˵��һ��client����ֻ��Ҫһ��RpcClientʵ��
    // ����ͨ��RpcClientOptionsָ��һЩ���ò�����Ʃ���߳��������ص�
    sofa::pbrpc::RpcClientOptions client_options;
    client_options.work_thread_num = 2;
    sofa::pbrpc::RpcClient rpc_client(client_options);

    // ����RpcChannel���󣬴���һ����Ϣͨ�����贫��Server�˷����ַ
    sofa::pbrpc::RpcChannel rpc_channel(&rpc_client, server_host);
 
    // ����EchoServer�����׮����EchoServer_Stub��ʹ�����涨�����Ϣͨ����������
    fs::EchoServer_Stub stub(&rpc_channel);
 
    // ����������÷�����������Ϣ
    fs::EchoRequest request;

    request.set_message(word);
 
    // ���巽���Ļ�Ӧ��Ϣ�����ڵ��÷��غ����
    fs::EchoResponse response;
 
    // ����RpcController�������ڿ��Ʊ��ε���
    // �������ó�ʱʱ�䡢ѹ����ʽ�ȣ�Ĭ�ϳ�ʱʱ��Ϊ10�룬Ĭ��ѹ����ʽΪ��ѹ��
    sofa::pbrpc::RpcController controller;
    controller.SetTimeout(3000);
 
    // ������ã����һ������ΪNULL��ʾΪͬ������
    stub.Echo(&controller, &request, &response, NULL);

    // ������ɺ󣬼���Ƿ�ʧ��
    if (controller.Failed()) {
        // ����ʧ�ܺ�Ĵ�����Ʃ����Խ�������
        SLOG(ERROR, "request failed: %s", controller.ErrorText().c_str());
    }
   std::cout<<"################################################"<<std::endl;
    std::cout<<"translate result:"<<response.message()<<std::endl;

    delete base_handle;
    delete get_node_info;
    return EXIT_SUCCESS;

}