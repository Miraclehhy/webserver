#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int iferror(int rec_data,int error_data,char* showinfo)
{
    if(rec_data == error_data)
    {
        //perror(showinfo);
        getchar();
        return -1;
    }
    return 0;
}

int main()
{
    printf("欢迎使用该服务器！\n");
    WSADATA wsdata;
    int isok = WSAStartup(MAKEWORD(2,2),&wsdata);
    iferror(isok,WSAEINVAL,"申请socket错误");
    SOCKET server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//ipv4,tcp协议
    iferror(server,INVALID_SOCKET,"创建socket失败");


    getchar();
    return 0;
}