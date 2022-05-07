#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
int main(int argc, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);
    system("pause");
    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }
    //nhận xâu chào Server gửi
    char buffer[256];

    while (true) {

        int retHello = recv(client, buffer, sizeof(buffer), 0);
        if (retHello < 0) {
            break;
        }
        buffer[retHello] = 0;
        printf("%s\n", buffer);
        break;
    }

    //nhập xâu và gửi cho server
    char buf[256];

    while (1)
    {
        printf("Nhap xau ky tu: ");
        fgets(buf, sizeof(buf), stdin);

        if (strncmp(buf, "exit", 4) == 0)
            break;

        send(client, buf, strlen(buf), 0);
    }

    closesocket(client);
    WSACleanup();
}