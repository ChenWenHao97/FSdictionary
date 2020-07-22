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
    // std::cout<<"################################################"<<std::endl;
    // std::cout<<"###############get_node_info####################"<<std::endl;
    // std::cout<<get_node_info<<std::endl;
    const char* server_host = get_node_info;//获取到提供服务的ip地址以及端口



    //rpc
    // SOFA_PBRPC_SET_LOG_LEVEL(NOTICE);

    // 定义RpcClient对象，管理RPC的所有资源
    // 通常来说，一个client程序只需要一个RpcClient实例
    // 可以通过RpcClientOptions指定一些配置参数，譬如线程数、流控等
    sofa::pbrpc::RpcClientOptions client_options;
    client_options.work_thread_num = 2;
    sofa::pbrpc::RpcClient rpc_client(client_options);

    // 定义RpcChannel对象，代表一个消息通道，需传入Server端服务地址
    sofa::pbrpc::RpcChannel rpc_channel(&rpc_client, server_host);
 
    // 定义EchoServer服务的桩对象EchoServer_Stub，使用上面定义的消息通道传输数据
    fs::EchoServer_Stub stub(&rpc_channel);
 
    // 定义和填充调用方法的请求消息
    fs::EchoRequest request;

    request.set_message(word);
 
    // 定义方法的回应消息，会在调用返回后被填充
    fs::EchoResponse response;
 
    // 定义RpcController对象，用于控制本次调用
    // 可以设置超时时间、压缩方式等；默认超时时间为10秒，默认压缩方式为无压缩
    sofa::pbrpc::RpcController controller;
    controller.SetTimeout(3000);
 
    // 发起调用，最后一个参数为NULL表示为同步调用
    stub.Echo(&controller, &request, &response, NULL);

    // 调用完成后，检查是否失败
    if (controller.Failed()) {
        // 调用失败后的错误处理，譬如可以进行重试
        SLOG(ERROR, "request failed: %s", controller.ErrorText().c_str());
    }
   std::cout<<"################################################"<<std::endl;
    std::cout<<"translate result:"<<response.message()<<std::endl;

    delete base_handle;
    delete get_node_info;
    return EXIT_SUCCESS;

}