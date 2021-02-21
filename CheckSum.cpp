// CheckSum.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <Windows.h>

int g_Total = 0;
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
   
    int byteTotal = 0;
    while (true)
    {
        int address = 0x00401000;
        for (int i = 0; i < 0x10000; i++)
        {
            byte byteRead = 0;
            ReadProcessMemory((HANDLE)-1, (LPCVOID)address, &byteRead, 1, NULL);
            byteTotal += byteRead;
            address++;
        }
        if (byteTotal != g_Total)
        {
            printf("CheckSum\n");
            exit(0);
        }
    }
    return 0;
}
int main()
{
    int address = 0x00401000;
    for (int i = 0; i < 0x10000; i++)
    {
        byte byteRead = 0;
        ReadProcessMemory((HANDLE)-1, (LPCVOID)address, &byteRead, 1, NULL);
        g_Total += byteRead;
    }
    CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
    printf("CheckSum\n");
    system("pause");
    return 0;
}
