#include "C:/Users/latsu/GitHub_projects/geometry/geometry-danyowoj/src/libgeometry/check.h"
#include "C:/Users/latsu/GitHub_projects/geometry/geometry-danyowoj/thirdparty/ctest.h"

#include <stdio.h>

/* ====================== TEST ======================
CTEST(suite, test1)
{
    ASSERT_STR("foo", "foo");
}

CTEST(suite, test2)
{
    ASSERT_EQUAL(1, 2);
}

CTEST(suite, test_dbl)
{
    ASSERT_DBL_NEAR(0.0001, 0.00011);
    ASSERT_DBL_NEAR_TOL(0.0001, 0.00011, 1e-5);
}
 ====================== TEST ====================== */

CTEST(INPUT_CHECK, OPEN_BRACKET_INDEX)
{
    // correct input check
    char* a = "circle(4 2, 8)";
    char* b = "circle";

    int expec = 6;
    int real = check_word(a, b, 0);

    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, SEARCH_CLOSE_BRACKET)
{
    char* a = "circle(4 2, 8)";
    int length = 14;

    int expec = 13;
    int real = search_close_bracket_index(a, &length);

    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, FIRST_NUMBER)
{
    char* a = "circle(4 2, 8)";
    int open_bracket_index = 6;
    int error = 0;

    int expec = 7;
    int real = check_first_number(a, &open_bracket_index, &error);

    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, SECOND_NUMBER)
{
    char* a = "circle(4 2, 8)";
    int first_num_elem_index = 7;
    int error = 0;

    int expec = 9;
    int real = check_second_number(a, &first_num_elem_index, &error);

    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, THIRD_NUMBER)
{
    char* a = "circle(4 2, 8)";
    int second_num_elem_index = 9;
    int close_bracket_index = 13;
    int error = 0;

    int expec = 12;
    int real = check_third_number(
            a, &second_num_elem_index, &close_bracket_index, &error);

    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, CHECK_CLOSE_BRACKET)
{
    char* a = "circle(4 2, 8)";
    int third_num_elem_index = 12;
    int length = 14;
    int error = 0;

    int expec = 13;
    int real = check_close_bracket_index(
            a, &third_num_elem_index, &length, &error);

    ASSERT_EQUAL(expec, real);
}

CTEST(INPUT_CHECK, UNEXPECTED_TOKENS)
{
    char* a = "circle(4 2, 8)";
    int close_bracket_index = 13;
    int length = 14;
    int error = 0;

    int expec = 0;
    int real
            = check_unexpected_tokens(a, &close_bracket_index, &length, &error);

    ASSERT_EQUAL(expec, real);
}