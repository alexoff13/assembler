#include <iostream>

int main() {
    const int N = 64;
    char line[N] = "        One      two  three    four five   six  6 seven";
    char outline[N]{};
    int lineLength = strlen(line);
    int wordCount, wordLength, searchingWordLength, lineIndex, outlineIndex, noUse, noUse1, noUse2;

    _asm {
        // будем двигаться по строке только слева направо, поэтому очищаем флаг
        cld

        // это означает, что сейчас во время цикла будем просто считать количество слов
        mov ah, 0
        mov wordCount, 0

        // инициализируем все нужные параметры для цикла
        LOOP_INIT:
            mov ecx, lineLength // счетчик циклов
            mov lineIndex, 0    // индекс символа во входной строке
            lea edi, line       // загрузка адреса исходной строки
            mov edx, edi        // предыдущее значение edi
            mov al, ' '         // символ разделителя слов

            MAIN_LOOP :
            repne scasb

            WORD_CHECK :
            mov wordLength, edi
            sub wordLength, edx
            cmp ecx, 0
            // нам не нужно уменьшать индекс на единицу, если это конец строки
            je PASS_DEC_WORD_LENGTH
            dec wordLength

            PASS_DEC_WORD_LENGTH :
            // смотрим, какая цель этого цикла
            cmp ah, 0
            // если равно, то мы считаем количество слов
            je COUNT_WORD
            // иначе нас интересуют слова нужной нам длины
            mov noUse, eax
            mov eax, searchingWordLength
            cmp wordLength, eax
            mov eax, noUse
            // если слово нужной длины, тогда добавляем в выходную строку
            je ADD_WORD
            // иначе проверяем условие для продолжения цикла
            jmp CHECK_MAIN_LOOP

            ADD_WORD :
        // получаем индекс начала слова в исходной строке
            mov noUse, eax
            mov eax, lineLength
            mov lineIndex, eax
            sub lineIndex, ecx
            mov eax, wordLength
            sub lineIndex, eax
            cmp ecx, 0
            je SKIP_DEC_LINE_INDEX
            dec lineIndex

            SKIP_DEC_LINE_INDEX :
            mov eax, noUse

            // нам нужно поместить в ecx нужное количество ветков цикла, то есть количество букв в слове,
            // но при этом ecx нужно куда-нибудь сохранить
            mov noUse, ecx
            mov ecx, wordLength
            mov noUse1, eax
            mov eax, outlineIndex
            mov noUse2, ebx
            mov ebx, lineIndex

            // добавляем слово в выходную строку
            ADDING_WORD :
            mov ch, line[ebx]
            mov outline[eax], ch
            xor ch, ch
            inc eax
            inc ebx
            loop ADDING_WORD

            mov outlineIndex, eax
            mov lineIndex, ebx

            // проверяем, нужно ли нам ставить пробел после добавления слова
            mov ebx, noUse2
            cmp ebx, wordCount
            je SKIP_ADD_SPACE
            mov eax, outlineIndex
            mov outline[eax], ' '
            inc outlineIndex

            SKIP_ADD_SPACE :
            inc ebx
            mov ecx, noUse
            mov eax, noUse1
            jmp CHECK_MAIN_LOOP

            COUNT_WORD :
            cmp wordLength, 0
            je SKIP_INC_WORD_COUNT
            inc wordCount

            SKIP_INC_WORD_COUNT :
            jmp CHECK_MAIN_LOOP

            CHECK_MAIN_LOOP :
            cmp ecx, 0
            mov edx, edi
            jne MAIN_LOOP
            cmp ah, 1
            je CHECK_SECOND_LOOP

            // это означает, что теперь мы будем искать слова нужной длины и добавлять их
            mov ah, 1

            xor ebx, ebx                // количество вставленных слов
            mov outlineIndex, 0         // индекс символа выходной строки
            mov searchingWordLength, 1  // количество букв, что мы ищем в словах
            jmp LOOP_INIT

            CHECK_SECOND_LOOP :
            inc searchingWordLength
            cmp ebx, wordCount
            jne LOOP_INIT
    }

    std::cout << outline << std::endl;
    return 0;
}