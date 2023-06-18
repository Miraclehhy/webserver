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
    printf("欢迎使用该服务器！\n");
    WSADATA wsdata;

    int isok = WSAStartup(MAKEWORD(2,2),&wsdata);
    char* wrong = (char*)"错误...";
    iferror(isok,WSAEINVAL,wrong);
    SOCKET server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//ipv4,tcp协议
    wrong = (char*)"创建socket失败...\n";
    iferror(server,INVALID_SOCKET,wrong);

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;//和创建的一样
    seraddr.sin_port = htons(80);
    seraddr.sin_addr.s_addr = INADDR_ANY;

    isok = bind(server,(struct sockaddr *)&seraddr,sizeof(seraddr));
    wrong = (char*)"绑定失败...\n";
    iferror(isok,SOCKET_ERROR,wrong);

    listen(server,5);
    wrong = (char*)"监听失败...\n";
    iferror(isok,SOCKET_ERROR,wrong);

    struct sockaddr_in claddr;
    int cllen = sizeof(claddr);
    while(1)
    {
        SOCKET client = accept(server,(struct sockaddr* )&claddr,&cllen);
        wrong = (char*)"连接失败...\n";
        iferror(client,INVALID_SOCKET,wrong);

        char recdata[1024] ="";
        recv(client,recdata,1024,0); 
        printf("%s共接收到%d字节数据\n",recdata,strlen(recdata));

        char senddata[1024] = "hello,client!";
        send(client,senddata,strlen(senddata),0);
        closesocket(client);
        
    }
    

    closesocket(server);
    WSACleanup();

    getchar();
    return 0;
}