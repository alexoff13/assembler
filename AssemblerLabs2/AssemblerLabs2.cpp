#include <iostream>

static void Calculate() {
    short x,a,res,y1, y2;
    std::cout << "Please, enter a:";
    std::cin >> a;
    std::cout << "Please, enter x:";
    std::cin >> x;
    _asm {
        mov ax, a;
        cmp x, ax;
        JA higher;
    lower:
        mov y1, 5;
        jmp compare2;
    higher:
        mov ax, x;
        mov dx, a;
        sub ax, dx;
        mov y1, ax;
    compare2:
        mov ax, a;
        cmp x, ax;
        JA higher2;
    lower2:
        mov ax, a;
        mov y2, ax;
        jmp CalculateRes;
    higher2:
        mov ax, x;
        mov bx, a;
        mul bx;
        mov y2, ax;
    CalculateRes:
        mov ax, y1;
        mov bx, y2;
        mul bx;
        mov res, ax;
    }
    std::cout << res;
}

int main()
{
    Calculate();
}

