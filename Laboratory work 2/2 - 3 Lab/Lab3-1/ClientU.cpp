#include <iostream>
#include <string>
#include "Winsock2.h"                // ���������  WS2_32.dll
#pragma comment(lib, "WS2_32.lib")   // �������  WS2_32.dll
#pragma warning (disable: 4996)

using namespace std;

string  SetErrorMsgText(string action, int code);  // c����������� ����� ������ 

int main()
{
    setlocale(LC_ALL, "rus");
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) throw  SetErrorMsgText("Startup:", WSAGetLastError());

        SOCKET  cC;

        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) throw  SetErrorMsgText("socket:", WSAGetLastError());

        SOCKADDR_IN serv;              // ���������  ������ �������
        serv.sin_family = AF_INET;    // ������������ ip-���������  
        serv.sin_port = htons(2000);   // ���� 2000
        serv.sin_addr.s_addr = inet_addr("127.0.0.1"); // ����� �������
        int  lobuf = 0;                         //���������� ������������  
        int lc = sizeof(serv);
        int libuf = 0,                     //���������� �������� ����
            count = 0;                      //���������� ���������

        cout << "Enter a number of itterations: ", cin >> count;

        char num[10],
            in[50]{};

        int t = clock();
        do
        {
            char out[50] = "Hello from ClientU ";
            _itoa(count, num, 10);
            strcat(out, num);

            if ((lobuf = sendto(cC, out, strlen(out) + 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR) throw  SetErrorMsgText("recv: ", WSAGetLastError());

            if (lobuf = recvfrom(cC, out, sizeof(out), NULL, (sockaddr*)&serv, &lc) == SOCKET_ERROR) throw  SetErrorMsgText("recv:", WSAGetLastError());


        } while (--count);

        if ((lobuf = sendto(cC, "", 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR) throw  SetErrorMsgText("recv: ", WSAGetLastError());

        if (closesocket(cC) == SOCKET_ERROR) throw  SetErrorMsgText("closesocket: ", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR) throw  SetErrorMsgText("Cleanup: ", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << errorMsgText << endl;
    }
    return 0;

}

string  SetErrorMsgText(string action, int code)
{
    string msgText;
    switch (code)                      // �������� ���� ��������  
    {
        case WSAEINTR: msgText = "������ ������� �������� "; break;
        case WSAEACCES: msgText = "���������� ����������"; break;
        case WSAEFAULT: msgText = "��������� �����"; break;
        case WSAEINVAL: msgText = "������ � ��������� "; break;
        case WSAEMFILE: msgText = "������� ����� ������ �������"; break;
        case WSAEWOULDBLOCK: msgText = "������ �������� ����������"; break;
        case WSAEINPROGRESS: msgText = "�������� � �������� ��������"; break;
        case WSAEALREADY: msgText = "�������� ��� ����������� "; break;
        case WSAENOTSOCK: msgText = "����� ����� �����������   "; break;
        case WSAEDESTADDRREQ: msgText = "��������� ����� ������������ "; break;
        case WSAEMSGSIZE: msgText = "��������� ������� ������� "; break;
        case WSAEPROTOTYPE: msgText = "������������ ��� ��������� ��� ������ "; break;
        case WSAENOPROTOOPT: msgText = "������ � ����� ���������"; break;
        case WSAEPROTONOSUPPORT: msgText = "�������� �� �������������� "; break;
        case WSAESOCKTNOSUPPORT: msgText = "��� ������ �� �������������� "; break;
        case WSAEOPNOTSUPP: msgText = "�������� �� �������������� "; break;
        case WSAEPFNOSUPPORT: msgText = "��� ���������� �� �������������� "; break;
        case WSAEAFNOSUPPORT: msgText = "��� ������� �� �������������� ����������"; break;
        case WSAEADDRINUSE: msgText = "����� ��� ������������ "; break;
        case WSAEADDRNOTAVAIL: msgText = "����������� ����� �� ����� ���� �����������"; break;
        case WSAENETDOWN: msgText = "���� ��������� "; break;
        case WSAENETUNREACH: msgText = "���� �� ���������"; break;
        case WSAENETRESET: msgText = "���� ��������� ����������"; break;
        case WSAECONNABORTED: msgText = "����������� ����� ����� "; break;
        case WSAECONNRESET: msgText = "����� ������������� "; break;
        case WSAENOBUFS: msgText = "�� ������� ������ ��� �������"; break;
        case WSAEISCONN: msgText = "����� ��� ���������"; break;
        case WSAENOTCONN: msgText = "����� �� ���������"; break;
        case WSAESHUTDOWN: msgText = "������ ��������� send: ����� �������� ������"; break;
        case WSAETIMEDOUT: msgText = "���������� ���������� ��������  �������"; break;
        case WSAECONNREFUSED: msgText = "���������� ���������  "; break;
        case WSAEHOSTDOWN: msgText = "���� � ����������������� ���������"; break;
        case WSAEHOSTUNREACH: msgText = "��� �������� ��� ����� "; break;
        case WSAEPROCLIM: msgText = "������� ����� ��������� "; break;
        case WSASYSNOTREADY: msgText = "���� �� �������� "; break;
        case WSAVERNOTSUPPORTED: msgText = "������ ������ ���������� "; break;
        case WSANOTINITIALISED: msgText = "�� ��������� ������������� WS2_32.DLL"; break;
        case WSAEDISCON: msgText = "����������� ����������"; break;
        case WSATYPE_NOT_FOUND: msgText = "����� �� ������ "; break;
        case WSAHOST_NOT_FOUND: msgText = "���� �� ������"; break;
        case WSATRY_AGAIN: msgText = "������������������ ���� �� ������ "; break;
        case WSANO_RECOVERY: msgText = "��������������  ������ "; break;
        case WSANO_DATA: msgText = "��� ������ ������������ ���� "; break;
        case WSA_INVALID_HANDLE: msgText = "��������� ���������� �������  � �������   "; break;
        case WSA_INVALID_PARAMETER: msgText = "���� ��� ����� ���������� � �������   "; break;
        case WSA_IO_INCOMPLETE: msgText = "������ �����-������ �� � ���������� ���������"; break;
        case WSA_IO_PENDING: msgText = "�������� ���������� �����  "; break;
        case WSA_NOT_ENOUGH_MEMORY: msgText = "�� ���������� ������ "; break;
        case WSA_OPERATION_ABORTED: msgText = "�������� ���������� "; break;
        case WSASYSCALLFAILURE: msgText = "��������� ���������� ���������� ������ "; break;
        default:                msgText = "***ERROR***";      break;
    };
    return action + msgText;
};