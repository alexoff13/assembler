#include <iostream>

static void Calculate() {
    short x,a,res,y1, y2;
    std::cout << "Please, enter a:";
    std::cin >> a;
    std::cout << "Please, enter x:";
    std::cin >> x;
    _asm {

        cmp x, ax;
        JA higher;
    lower:
        mov y1, 5;
    higher:
        mov ax, x;
        mov dx, a;
        sub ax, dx;
        mov y1, ax;
        mov ax, a;
        cmp ax, x;
        JA higher2;
    lower2:
        mov ax, a;
        mov y2, ax;
    higher2:
        mov ax, x;
        mov bx, a;
        mul bx;
        mov y2, ax;
        mov ax, y1;
        mov dx, y2;
        sub ax, dx;
        mov res, ax;

    }
    std::cout << res;
}

int main()
{
    Calculate();
}

