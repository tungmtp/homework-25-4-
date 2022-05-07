#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    // Khoi tao thu vien
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // Tao socket
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);

    int ret;
    // Gan cau truc dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    // Chuyen sang trang thai cho ket noi
    listen(listener, 5);

    SOCKET client = accept(listener, NULL, NULL);

    //gửi file chào cho client
    char text[256];
    FILE* file_hello = fopen("C:/Users/Admin/source/repos/file_hello.txt","r");
    while (!feof(file_hello)) {
        ret = fread(text, 1, sizeof(text), file_hello);
        if (ret > 0)
        {
            send(client, text, ret, 0);
        }
    }
    fclose(file_hello);
    // ghi nội dung nhận được vào 1 file khác
    FILE* file = fopen("C:/Users/Admin/source/repos/file_inputFromServer.txt","a");
    char buf[256];
    while (1)
    {
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;

        // Them ky tu ket thuc xau va in ra man hinh
        buf[ret] = 0;
        printf("du lieu nhan dc: %s", buf);

        // Writing on file
        fwrite(buf, 1, ret, file);
       

    }
    fclose(file);

    // Dong ket noi va giai phong thu vien
    closesocket(client);
    closesocket(listener);
    WSACleanup();
}