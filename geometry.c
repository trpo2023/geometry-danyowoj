#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_word(char a[], int length)
{
    char b[6] = "circle";
    int open_bracket_index = 0, i;
    for (i = 0; i < 7; i++) {
        if (a[i] != b[i] && i < 6) {
            printf("\nError at column %d: expected 'circle'", i);
            break;
        }
        open_bracket_index = i;
    }
    return open_bracket_index;
}

int search_close_bracket_index(char a[], int length)
{
    int close_bracket_index;
    for (int i = 0; i < length; i++) {
        if (a[i] == ')') {
            close_bracket_index = i;
        } else {
            close_bracket_index = length - 1;
        }
    }
}

int check_first_number(char a[], int open_bracket_index)
{
    int first_num_elem_index;
    for (int i = open_bracket_index + 1; a[i] != ' '; i++) {
        if (a[i] == ',') {
            printf("\nError at column %d: expected '<space>' and "
                   "'<double>'",
                   i);
            break;
        }
        if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
            printf("\nError at column %d: expected '<double>'", i);
            break;
        }
        first_num_elem_index = i;
    }
    return first_num_elem_index;
}

int check_second_number(char a[], int first_num_elem_index)
{
    int second_num_elem_index;
    for (int i = first_num_elem_index + 2; a[i] != ','; i++) {
        if (a[i] == ')') {
            printf("\nError at column %d: expected ',' and '<double>'", i);
            break;
        }
        if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
            printf("\nError at column %d: expected '<double>' or ',' "
                   "token",
                   i);
            break;
        }
        second_num_elem_index = i;
    }
    return second_num_elem_index;
}

int check_third_number(
        char a[], int second_num_elem_index, int close_bracket_index)
{
    int third_num_elem_index;
    for (int i = second_num_elem_index + 3; i < close_bracket_index; i++) {
        if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0') {
            if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                break;
            }
            printf("\nError at column %d: expected '<double>'", i);
            break;
        }
        third_num_elem_index = i;
    }
    return third_num_elem_index;
}

int check_close_bracket_index(char a[], int third_num_elem_index, int length)
{
    int close_bracket_index;
    for (int i = third_num_elem_index + 1; i < length; i++) {
        if (a[i] != ')') {
            printf("\nError at column %d: expected ')'", i);
            break;
        } else {
            close_bracket_index = i;
            break;
        }
    }
    return close_bracket_index;
}

void check_unexpected_tokens(char a[], int close_bracket_index, int length)
{
    for (int i = close_bracket_index + 1; i < length; i++) {
        if (a[i] == '\n') {
            printf("No Errors!");
            break;
        }

        if (a[i] != ' ') {
            printf("\nError at column %d: unexpected token", i);
            break;
        }
    }
}

int main()
{
    FILE* file1;
    FILE* file;

    file1 = fopen("geometry.txt", "r");

    if (!file1) {
        printf("\nError: cannot open file. Check file's name");
    }

    int i, open_bracket_index = 0, close_bracket_index = 0,
           first_num_elem_index = 0, second_num_elem_index = 0,
           third_num_elem_index = 0;
    int length = 0, count = 0, element = 0, error = 0;
    puts("\n");
    while (1) {
        element = fgetc(file1);
        if (element == EOF) {
            if (feof(file1) != 0) {
                break;
            }
        }
        count++;
    }
    length = count;
    fclose(file1);

    char a[length];
    file = fopen("geometry.txt", "r");
    while (fgets(a, length + 1, file)) {
        printf("%s", a);

        open_bracket_index = check_word(a, length);

        close_bracket_index = search_close_bracket_index(a, length);

        first_num_elem_index = check_first_number(a, open_bracket_index);

        second_num_elem_index = check_second_number(a, first_num_elem_index);

        third_num_elem_index = check_third_number(
                a, second_num_elem_index, close_bracket_index);

        close_bracket_index
                = check_close_bracket_index(a, third_num_elem_index, length);

        check_unexpected_tokens(a, close_bracket_index, length);

        puts("\n\n");
    }
    return 0;
}