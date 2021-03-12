.386
.model flat, stdcall
option casemap: none

include C:\masm32\include\windows.inc
include C:\masm32\include\kernel32.inc
includelib C:\masm32\lib\kernel32.lib
include C:\masm32\include\gdi32.inc
includelib C:\masm32\lib\gdi32.lib
include C:\masm32\include\masm32.inc
include C:\masm32\include\user32.inc
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\gdi32.lib
includelib C:\masm32\lib\masm32.lib 

.data

COORD STRUCT
x WORD ?
y WORD ?
COORD ENDS

Message1 db "Input string "
Message2 db "Your string "
ConsoleTitle db 'Assembler Lab 5', 0
xyPos COORD <13, 3>
attributes WORD 0Fh, 0Eh, 0Dh, 0Ch, 0Bh, 0Ah

.code

Main proc

LOCAL InputBufer[128] :BYTE ;����� ��� �����
LOCAL hOutPut :DWORD ;���������� ��� ������
LOCAL hInput :DWORD ;���������� ��� �����
LOCAL nRead :DWORD ;��������� ����
LOCAL nWritten :DWORD ;���������� ����

;��������� ��������� ����
invoke SetConsoleTitle, addr ConsoleTitle

;��������� ����������� ��� ������
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov hOutPut, eax

;����� ������� "Input string "
invoke WriteConsole, hOutPut, addr Message1, 13, addr nWritten, 0

;��������� ����������� ��� �����
invoke GetStdHandle, STD_INPUT_HANDLE
mov hInput, eax

;���� ������
invoke ReadConsole, hInput, addr InputBufer, 10, addr nRead, 0

;����� ������� "Your string "
invoke WriteConsole, hOutPut, addr Message2, 12, addr nWritten, 0

;����� �������� ������
invoke WriteConsole, hOutPut, addr InputBufer, nRead, addr nWritten, 0

;��������
invoke Sleep, 2000d

;��������� ��������� ����
invoke SetConsoleTitle, addr ConsoleTitle

;��������� ����������� ��� ������
invoke GetStdHandle, STD_OUTPUT_HANDLE
mov hOutPut, eax

;����� ������� "Input string "
invoke WriteConsole, hOutPut, addr Message1, 13, addr nWritten, 0

;��������� ����������� ��� �����
invoke GetStdHandle, STD_INPUT_HANDLE
mov hInput, eax

;���� ������
invoke ReadConsole, hInput, addr InputBufer, 10, addr nRead, 0

;����� ������� "Your string "
invoke WriteConsole, hOutPut, addr Message2, 12, addr nWritten, 0

mov edx, [xyPos]
;����� �������� ������
invoke WriteConsoleOutputCharacter, hOutPut, addr InputBufer, nRead, edx, addr nWritten

mov edx, [xyPos]
;������� ����� ������� ����� �� ������
invoke WriteConsoleOutputAttribute, hOutPut, addr attributes, nRead, edx, addr nWritten

;��������
invoke Sleep, 10000d

;�����
invoke ExitProcess,0
Main endp

end Main
