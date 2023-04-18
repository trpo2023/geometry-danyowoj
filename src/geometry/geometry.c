#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_word(char a[], int* error)
{
    char b[6] = "circle";
    int open_bracket_index;
    for (int i = 0; i < 7; i++) {
        if (a[i] != b[i] && i < 6) {
            open_bracket_index = 0;
            printf("\nError at column %d: expected 'circle'", i);
            *error = 1;
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
    return close_bracket_index;
}

int check_first_number(char a[], int open_bracket_index, int* error)
{
    int first_num_elem_index = 0;
    for (int i = open_bracket_index + 1; a[i] != ' '; i++) {
        if (*error == 0) {
            if (a[i] == ',') {
                printf("\nError at column %d: expected '<space>' and "
                       "'<double>'",
                       i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
                printf("\nError at column %d: expected '<double>'", i);
                *error = 1;
                break;
            }
            first_num_elem_index = i;
        } else
            break;
    }
    return first_num_elem_index;
}

int check_second_number(char a[], int first_num_elem_index, int* error)
{
    int second_num_elem_index = 0;
    for (int i = first_num_elem_index + 2; a[i] != ','; i++) {
        if (*error == 0) {
            if (a[i] == ')') {
                printf("\nError at column %d: expected ',' and '<double>'", i);
                *error = 1;
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
                printf("\nError at column %d: expected '<double>' or ',' "
                       "token",
                       i);
                *error = 1;
                break;
            }
            second_num_elem_index = i;
        } else
            break;
    }
    return second_num_elem_index;
}

int #define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/check.h>

        void
        token(char* a)
{
    float x, y, radius, square, perimeter;
    char del[] = "circle( ,)";
    x = atof(strtok(a, del));
    y = atof(strtok(NULL, del));
    radius = atof(strtok(NULL, del));
    square = M_PI * radius * radius;
    perimeter = 2 * M_PI * radius;
    printf("x = %.3f\ty = %.3f\tradius = %.3f\n", x, y, radius);
    printf("square = %.3f\tperimeter = %.3f\n", square, perimeter);
}

int main()
{
    FILE* file1;
    FILE* file;

    file1 = fopen("geometry.txt", "r");

    if (!file1) {
        printf("Error! Cannot open file. Check file name.\n");
        return 0;
    }

    int ind_open_bracket = 0, ind_close_bracket = 0, ind_last_num_elm = 0,
        ind_first_num_elm = 0, ind_second_num_elm = 0;
    int length = 0, count = 0, element = 0, error = 0;

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

    char a[length], b[6] = "circle";
    file = fopen("geometry.txt", "r");
    while (fgets(a, length + 1, file)) {
        printf("%s", a);

        // check 'circle and finding index of '(' symbol
        check_word(a, b, &error, &ind_open_bracket);

        // printf("error = %d\tind_open_bracket = %d\n", error,
        // ind_open_bracket);

        // find index of ')' token
        find_close_bracket(a, &length, &ind_close_bracket);
        // printf("ind_close_bracket = %d\n", ind_close_bracket);

        // check first number
        check_first_num(a, &ind_open_bracket, &ind_first_num_elm, &error);
        // printf("ind_first_num_elm = %d\n", ind_first_num_elm);

        // check second number
        check_second_num(a, &ind_first_num_elm, &ind_second_num_elm, &error);
        // printf("ind_second_num_elm = %d\n", ind_second_num_elm);

        // check last number
        check_third_num(
                a,
                &ind_second_num_elm,
                &ind_last_num_elm,
                &error,
                &ind_close_bracket);
        // printf("ind_last_num_elm = %d\n", ind_last_num_elm);

        // check ')' symbol
        check_close_bracket(
                a, &ind_last_num_elm, &length, &ind_close_bracket, &error);
        // printf("ind_close_bracket = %d\n", ind_close_bracket);

        // check unexpected tokens
        check_unexpected_token(a, &ind_close_bracket, &length, &error);

        if (error == 0) {
            printf("No Errors!\n");
            token(a);
        }

        error = 0;
        printf("\n");
    }
    return 0;
}
check_third_number(
        char a[],
        int second_num_elem_index,
        int close_bracket_index,
        int* error)
{
    int third_num_elem_index = 0;
    for (int i = second_num_elem_index + 3; i < close_bracket_index; i++) {
        if (*error == 0) {
            if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0') {
                if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                    break;
                }
                printf("\nError at column %d: expected '<double>'", i);
                *error = 1;
                break;
            }
            third_num_elem_index = i;
        } else
            break;
    }
    return third_num_elem_index;
}

int check_close_bracket_index(
        char a[], int third_num_elem_index, int length, int* error)
{
    int close_bracket_index = 0;
    for (int i = third_num_elem_index + 1; i < length; i++) {
        if (*error == 0) {
            if (a[i] != ')') {
                printf("\nError at column %d: expected ')'", i);
                *error = 1;
                break;
            } else {
                close_bracket_index = i;
                break;
            }
        } else
            break;
    }
    return close_bracket_index;
}

void check_unexpected_tokens(
        char a[], int close_bracket_index, int length, int* error)
{
    for (int i = close_bracket_index + 1; i < length; i++) {
        if (*error == 0) {
            if (a[i] == '\n') {
                break;
            }

            if (a[i] != ' ') {
                printf("\nError at column %d: unexpected token", i);
                *error = 1;
                break;
            }
        } else
            break;
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

    int open_bracket_index = 0, close_bracket_index = 0,
        first_num_elem_index = 0, second_num_elem_index = 0,
        third_num_elem_index = 0, error;
    int length = 0, count = 0, element = 0;
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
        error = 0;

        open_bracket_index = check_word(a, &error);

        close_bracket_index = search_close_bracket_index(a, length);

        first_num_elem_index
                = check_first_number(a, open_bracket_index, &error);

        second_num_elem_index
                = check_second_number(a, first_num_elem_index, &error);

        third_num_elem_index = check_third_number(
                a, second_num_elem_index, close_bracket_index, &error);

        close_bracket_index = check_close_bracket_index(
                a, third_num_elem_index, length, &error);

        check_unexpected_tokens(a, close_bracket_index, length, &error);

        if (error == 0)
            printf("\nNo Errors!");
        puts("\n\n");
    }
    return 0;
}
