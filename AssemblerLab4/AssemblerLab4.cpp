#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <cstdio>
#include <conio.h>
#include <windows.h>
#include <intrin.h>
#include <time.h>

#pragma intrinsic(rdtsc)

unsigned _int64 rdtsc() {
	return rdtsc();
}

using namespace std;

float function(float);
float x(int, int, float);

const int a = 0;
const float b = 3.14159;
const int N = 10000000;//

float t1, t2, t;

int main()
{
	freopen("output.txt", "w", stdout);

	int minCTime = 0;
	int minAsmTime = 0;

	for (int z = 0; z < 15; z++)
	{
		int StartMs = GetTickCount();

		int begin_eax, begin_edx, dif_lo, dif_hi;
		_asm {
			rdtsc
			mov begin_eax, eax
			mov begin_edx, edx
		}
		t1 = clock();
		float sum = 0.0;
		float h = (b - a) / N;

		for (int i = 0; i < N; i++)
		{
			sum += ((function(x(i, a, h)) + function(x(i + 1, a, h))) / 2) * (x(i + 1, a, h) - x(i, a, h));
		}

		printf("C++: %f\n", sum);

		_asm {
			rdtsc
			sub eax, begin_eax
			sbb edx, begin_edx
			mov dif_lo, eax
			mov dif_hi, edx
		}
		t2= clock();
		int EndMs = GetTickCount();

		printf("Количество тактов(в 16СС): %X%X\n", dif_hi, dif_lo);
		cout << "В секундах rdtsc" << (t2 - t1) / CLOCKS_PER_SEC << endl;
		cout << "В секундах: " << ((float)(EndMs - StartMs)) / 1000 << '(' << EndMs - StartMs << ')' << endl;

		if (minCTime == 0)
		{
			minCTime = EndMs - StartMs;
		}
		else if (minCTime > (EndMs - StartMs))
		{
			minCTime = EndMs - StartMs;
		}

		sum = 0.0;
		h = 0.0;

		float funct1, funct2, x1, x2, temp;

		int StartMs2 = GetTickCount();
		t1 = clock();
		_asm
		{
			finit

			rdtsc

			mov begin_eax, eax
			mov begin_edx, edx

			mov eax, b
			push eax
			fld dword ptr[esp]
			mov eax, a
			push eax
			fisub dword ptr[esp]
			pop eax
			fstp dword ptr[esp]
			pop eax
			//eax = (b-a)

			push eax
			fld dword ptr[esp]
			mov eax, N
			push eax
			fidiv dword ptr[esp]
			pop eax
			fstp dword ptr[esp]
			pop h
			//h = (b-a)/N

			//ecx-счётчик количества выполнения команд

			mov ecx, 0
			for_loop:
			jmp x_pointer
			end_x_pointer :
			jmp function_pointer
			end_function_pointer :
			//окончание просчёта для первой функции
			inc ecx

				jmp x_pointer2
				end_x_pointer2 :
			jmp function_pointer2
				end_function_pointer2 :

			dec ecx
				//окончание просчёта для второй функции
				//теперь известны func1, func2, x1, x2

			jmp sumfunc1func2_anddiv2
			end_sumfunc1func2_anddiv2 :
			jmp subx2x1
				end_subx2x1 :
			jmp mul_func_and_x
				end_mul_func_and_x :
			jmp summator
				end_summator :

			inc ecx
				cmp ecx, N
				jne for_loop
				jmp finish

				x_pointer :

			    mov eax, ecx
				push eax
				fild dword ptr[esp]
				push h
				fmul dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				//eax=i*h

				push eax
				fld dword ptr[esp]
				push a
				fiadd dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				mov x1, eax
				//x=a+i*h
				jmp end_x_pointer

				function_pointer :

				mov eax, x1
				push eax
				fld dword ptr[esp]
				fsin
				fstp dword ptr[esp]
				pop eax
				//eax=sin(x)

				fld	x1
				fldl2e //Загружаем константу log2(e) 
				fmulp st(1), st(0)
				fld     st(0)
				frndint // округляем к целому
				fsub    st(1), st(0)
				fxch    st(1) // меняем местами st(0) и st(1)
				f2xm1 // 2^st(0)-1
				fld1
				faddp   st(1), st(0)
				fscale 
				fstp    st(1)
				fstp temp
				//temp=e^x

				push temp
				fld dword ptr[esp]
				push eax
				fmul dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop funct1
				//eax==sin(x)*e^(x)

				jmp end_function_pointer

				x_pointer2 :

			mov eax, ecx
				push eax
				fild dword ptr[esp]
				push h
				fmul dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				//eax=i*h

				push eax
				fld dword ptr[esp]
				push a
				fiadd dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				mov x2, eax
				//x=a+i*h
				jmp end_x_pointer2

				function_pointer2 :

			mov eax, x2
				push eax
				fld dword ptr[esp]
				fsin
				fstp dword ptr[esp]
				pop eax
				//eax=sin(x)

				fld	x2
				fldl2e
				fmulp st(1), st(0)
				fld     st(0)
				frndint
				fsub    st(1), st(0)
				fxch    st(1)
				f2xm1
				fld1
				faddp   st(1), st(0)
				fscale
				fstp    st(1)
				fstp temp
				//temp=e^x

				push temp
				fld dword ptr[esp]
				push eax
				fmul dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop funct2
				//eax==sin(x)*e^(x)

				jmp end_function_pointer2

				sumfunc1func2_anddiv2 :
				mov eax, funct1
				push eax
				fld dword ptr[esp]
				mov eax, funct2
				push eax
				fadd dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				//eax==funct1+funct2

				push eax
				fld dword ptr[esp]
				mov eax, 2
				push eax
				fidiv dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				//eax==(funct1+funct2)/2

				jmp end_sumfunc1func2_anddiv2

				subx2x1 :
			mov ebx, x2
				push ebx
				fld dword ptr[esp]
				mov ebx, x1
				push ebx
				fsub dword ptr[esp]
				pop ebx
				fstp dword ptr[esp]
				pop ebx
				//ebx==x2-x1

				jmp end_subx2x1

				mul_func_and_x :

			push eax
				fld dword ptr[esp]
				push ebx
				fmul dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop eax
				//eax == (funct1+funct2)/2 * (x2-x1)

				jmp end_mul_func_and_x

				summator :
			push eax
				fld dword ptr[esp]
				mov eax, sum
				push eax
				fadd dword ptr[esp]
				pop eax
				fstp dword ptr[esp]
				pop sum

				jmp end_summator

				finish :
		}

		printf("Ассемблер: %f\n", sum);

		_asm {
			rdtsc
			sub eax, begin_eax
			sbb edx, begin_edx
			mov dif_lo, eax
			mov dif_hi, edx
		}
		t2 = clock();
		int EndMs2 = GetTickCount();

		printf("Количество тактов(в 16СС): %X%X\n", dif_hi, dif_lo);
		cout << "В секундах rdtsc" << (t2 - t1) / CLOCKS_PER_SEC << endl;
		cout << "В секундах: " << ((float)(EndMs2 - StartMs2)) / 1000 << '(' << EndMs2 - StartMs2 << ')' << endl;

		if (minAsmTime == 0)
		{
			minAsmTime = EndMs2 - StartMs2;
		}
		else if (minAsmTime > (EndMs2 - StartMs2))
		{
			minAsmTime = EndMs2 - StartMs2;
		}

		cout << endl;
	}

	cout << "Мин. время на С++: " << ((float)minCTime) / 1000 << '(' << minCTime << ')' << endl;

	cout << "Мин.время на Ассемблере: " << ((float)minAsmTime) / 1000 << '(' << minAsmTime << ')' << endl;

	return 0;

}

float x(int i, int a, float h)
{
	return (a + i * h);
}

float function(float x)
{
	return (exp(x) * sin(x));
}
