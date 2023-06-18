#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int iferror(int rec_data,long long int error_data,char* showinfo)
{
    if(rec_data == error_data)
    {
        perror(showinfo);
        getchar();
        return -1;
    }
    return 0;
}

int main()
{
    printf("欢迎使用该服务器！");
    WSADATA wsdata;
    int isok = WSAStartup(MAKEWORD(2,2),&wsdata);
    char* wrong = (char*)"错误";
    iferror(isok,WSAEINVAL,wrong);
    SOCKET server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//ipv4,tcp协议
    wrong = (char*)"创建socket失败";
    iferror(server,INVALID_SOCKET,wrong);


    getchar();
    return 0;
}