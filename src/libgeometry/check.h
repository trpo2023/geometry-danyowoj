int check_word(char* a, char* b, int* error);
int search_close_bracket_index(char* a, int* length);
int check_first_number(char* a, int* open_bracket_index, int* error);
int check_second_number(char* a, int* first_num_elem_index, int* error);
int check_third_number(
        char* a,
        int* second_num_elem_index,
        int* close_bracket_index,
        int* error);
int check_close_bracket_index(
        char* a, int* third_num_elem_index, int* length, int* error);
int check_unexpected_tokens(
        char* a, int* close_bracket_index, int* length, int* error);
void intersects(
        float* x_arr, float* y_arr, float* radius_arr, int figure_amount);