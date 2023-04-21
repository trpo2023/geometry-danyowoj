#define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/check.h>

void token(char* a)
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

        // check for 'circle' and search for '(' index
        int open_bracket_index = check_word(a, b, &error);

        // serch for ')' index
        int close_bracket_index = search_close_bracket_index(a, &length);

        // check first number
        int first_num_elem_index
                = check_first_number(a, &open_bracket_index, &error);

        // check second number
        int second_num_elem_index
                = check_second_number(a, &first_num_elem_index, &error);

        // check third number
        int third_num_elem_index = check_third_number(
                a, &second_num_elem_index, &close_bracket_index, &error);

        // check for ')'
        close_bracket_index = check_close_bracket_index(
                a, &third_num_elem_index, &length, &error);

        // check for unexpected tokens
        error = check_unexpected_tokens(
                a, &close_bracket_index, &length, &error);

        if (error == 0) {
            printf("No Errors!\n");
            token(a);
        }

        error = 0;
        printf("\n");
    }
    return 0;
}