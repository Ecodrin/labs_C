#include <stdio.h>
#include <ctype.h>

#define VOWELS (1u << ('a' - 'a') | 1u << ('e' - 'a') | 1u << ('i' - 'a') | 1u << ('o' - 'a') | 1u << ('u' - 'a'))

unsigned int char_to_set(char c) {
    c = tolower(c);
    if (c < 'a' || c > 'z') {
        return 0;
    } else {
        return 1u << (c - 'a');
    }
}

char c, p;
unsigned int letters_set = 0;
int fl = 0, count = 0, count_word = 0;


void Lett() {
    letters_set = letters_set & VOWELS;
    for (char a = 'a'; a <= 'z'; ++a) {
        if ((letters_set & char_to_set(a)) != 0) {
            count++;
            p = a;
        }
    }
}

int itog() {
    if (count == 1) {
        printf("%s %c. %s %d %s", "Да, единственная буква:", p, "Находится в", count_word, "слове.");
        fl = 1;
        return 1;
    }
    return 0;
}

int main() {
    char filename1[256];
    printf("%s", "Введите имя файла с тестом: ");
    scanf("%s", filename1);
    FILE *f = fopen(filename1, "r");
    while ((c = getc(f)) != EOF) {
        if (c == ' ' | c == '\n' | c == '\t' | c == ',' | c == '.') {
            ++count_word;
            Lett();
            if (itog() == 1)
                break;
            count = 0;
            letters_set = 0;
        } else
            letters_set = letters_set | char_to_set(c);
    }
    Lett();
    itog();
    if (fl == 0) {
        printf("%s", "Нет");
    }
    printf("%s", "\n");
}