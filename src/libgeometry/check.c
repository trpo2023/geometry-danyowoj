#include "check.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_word(char* a, char* b, int* error)
{
    int open_bracket_index;

    for (int i = 0; i < 7; i++) {
        if (a[i] != b[i] && i < 6) {
            printf("Error at column %d: expected 'circle'\n", i);
            *error = 1;
            break;
        }
        open_bracket_index = i;
    }
    return open_bracket_index;
}

int search_close_bracket_index(char* a, int* length)
{
    int close_bracket_index;

    for (int i = 0; i < *length && a[i] != '\n'; i++) {
        if (a[i] == ')') {
            close_bracket_index = i;
        } else {
            close_bracket_index = *length - 1;
        }
    }
    return close_bracket_index;
}

int check_first_number(char* a, int* open_bracket_index, int* error)
{
    int first_num_elem_index = 0;

    for (int i = *open_bracket_index + 1; a[i] != ' '; i++) {
        if (*error == 0) {
            if (a[i] == ',') {
                *error = 1;
                printf("\nError at column %d: expected '<space>' and "
                       "'<double>'",
                       i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-'
                && a[i] != ' ') {
                *error = 1;
                printf("\nError at column %d: expected '<double>'", i);
                break;
            }
            first_num_elem_index = i;
        } else
            break;
    }
    return first_num_elem_index;
}

int check_second_number(char* a, int* first_num_elem_index, int* error)
{
    int second_num_elem_index = 0;
    for (int i = *first_num_elem_index + 2; a[i] != ','; i++) {
        if (*error == 0) {
            if (a[i] == ')') {
                *error = 1;
                printf("\nError at column %d: expected ',' and '<double>'", i);
                break;
            }
            if (isdigit(a[i]) == 0 && a[i] != '.' && a[i] != '-') {
                *error = 1;
                printf("\nError at column %d: expected '<double>' or ',' "
                       "token",
                       i);
                break;
            }
            second_num_elem_index = i;
        } else
            break;
    }
    return second_num_elem_index;
}

int check_third_number(
        char* a,
        int* second_num_elem_index,
        int* close_bracket_index,
        int* error)
{
    int third_num_elem_index = 0;

    for (int i = *second_num_elem_index + 3; i < *close_bracket_index; i++) {
        if (*error == 0) {
            if ((isdigit(a[i]) == 0 && a[i] != '.') || a[i] == '0') {
                if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                    break;
                }
                *error = 1;
                printf("\nError at column %d: expected '<double>'", i);
                break;
            }
            third_num_elem_index = i;
        } else
            break;
    }
    return third_num_elem_index;
}

int check_close_bracket_index(
        char* a, int* third_num_elem_index, int* length, int* error)
{
    int close_bracket_index = 0;

    for (int i = *third_num_elem_index + 1; i < *length; i++) {
        if (*error == 0) {
            if (a[i] != ')') {
                *error = 1;
                printf("\nError at column %d: expected ')'", i);
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

int check_unexpected_tokens(
        char* a, int* close_bracket_index, int* length, int* error)
{
    for (int i = *close_bracket_index + 1; i < *length; i++) {
        if (*error == 0) {
            if (a[i] == '\n') {
                break;
            }

            if (a[i] != ' ') {
                *error = 1;
                printf("\nError at column %d: unexpected token", i);
                break;
            }
        } else
            break;
    }
    return *error;
}