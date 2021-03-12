#include <iostream>
#include <conio.h>



static void Calculate() {
    int buf;
    _asm
    {
        mov eax, 16;
        mov edx, 0;
        mov ebx, 3;
        div ebx;
        mov buf, eax;
        mov eax, 8;
        mov ebx, 2;
        mul ebx;
        mov  edx, buf;
        sub eax, edx;
        mov buf, eax;
        mov eax, 3;
        mov ebx, 5;
        mul ebx;
        mov ebx, buf;
        sub eax, ebx;
        mov buf, eax;
        mov eax, 15;
        mov ebx, 6;
        div ebx;
        mov ebx, eax;
        mov eax, buf;
        mov edx, 0;
        div ebx;
        mov buf, eax;
    }

    std::cout << buf << std::endl;

}

static void Inverse() {
    unsigned short y;
    _asm {
        mov ax, 1110111101010101b;
        mov bh, ah;
        mov ah, al;
        mov al, bh;
        shr ax, 5;
        not ax;
        mov y, ax;
    }
    for (int i = 0; i < 16; i++)
        std::cout << (y & (256 >> i + 1) ? '1' : '0');
    std::cout << std::endl;
}



int main()
{
    std::cout << "First:" << std::endl;
    Calculate();
    std::cout << "Second:" << std::endl;
    Inverse();
    return 0;
}

