#define _USE_MATH_DEFINES
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/check.h>

void token(char* a, float* x, float* y, float* radius) // change
{
    float square, perimeter;
    char del[] = "circle( ,)";
    *x = atof(strtok(a, del));                                      // change
    *y = atof(strtok(NULL, del));                                   // change
    *radius = atof(strtok(NULL, del));                              // change
    square = M_PI * *radius * *radius;                              // change
    perimeter = 2 * M_PI * *radius;                                 // change
    printf("x = %.3f\ty = %.3f\tradius = %.3f\n", *x, *y, *radius); // change
    printf("square = %.3f\tperimeter = %.3f\n", square, perimeter);
}

// change
int intersects(float* x_arr, float* y_arr, float* radius_arr, int figure_amount)
{
    printf("\nIntersections:\n");
    for (int i = 0; i < figure_amount; i++) {
        printf("\ncircle %d. intersects circle(s) ", i);
        for (int j = 0; j < figure_amount && j != i; j++) {
            double dist_btw_centers = sqrt(
                    pow(x_arr[j] - x_arr[i], 2) + pow(y_arr[j] - y_arr[i], 2));
            if (dist_btw_centers == 0 && radius_arr[i] == radius_arr[j]) {
                printf("%d. ", j);
                // intersects
                return 0;
            }

            if (radius_arr[i] + radius_arr[j] >= dist_btw_centers
                && radius_arr[i] + dist_btw_centers >= radius_arr[j]
                && radius_arr[j] + dist_btw_centers >= radius_arr[i]) {
                printf("%d. ", j);
                // intersects
                return 0;
            } else {
                // does not intersect
                return 1;
            }
        }
    }
    return 1;
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

    int figure_amount = 0;                                             // change
    float* x_arr = (float*)malloc(figure_amount * sizeof(float));      // change
    float* y_arr = (float*)malloc(figure_amount * sizeof(float));      // change
    float* radius_arr = (float*)malloc(figure_amount * sizeof(float)); // change

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
            float x = 0, y = 0, radius = 0;     // change
            token(a, &x, &y, &radius);          // change
            x_arr[figure_amount] = x;           // change
            y_arr[figure_amount] = y;           // change
            radius_arr[figure_amount] = radius; // change
            figure_amount += 1;                 // change
        }

        error = 0;
        printf("\n");
    }

    intersects(x_arr, y_arr, radius_arr, figure_amount); // change
    puts("\n");                                          // change

    free(x_arr);      // change
    free(y_arr);      // change
    free(radius_arr); // change

    return 0;
}