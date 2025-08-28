#ifndef KVADR_H
#define KVADR_H

#include <stdio.h>

const double NUMBER_CLOSE_TO_ZERO  = 10e-12;
const int    SIZE_OF_TESTS_ARRAY   = 100;
const int    MAX_LEN_STR_NUM_ROOTS = 14;
const int    MAX_LEN_STR_COEFS     = 7;
const int    NUM_OF_COEFFICIENTS   = 3;

enum number_of_roots
{
    ERROR_SOLUTIONS = -2,
    INF_SOLUTIONS   = -1,
    NO_SOLUTIONS    =  0,
    ONE_SOLUTION    =  1,
    TWO_SOLUTIONS   =  2
};

enum program_what_to_do
{
    PROGRAM_QUIT        = -1,
    PROGRAM_START_AGAIN =  0,
    PROGRAM_CONTINUE    =  1
};

struct coefficients_data
{
    double a, b, c;
};

struct answers_data
{
    double x1, x2;
    number_of_roots number_of_answers;
};

struct test_equation_data
{
    struct coefficients_data coefficients;
    struct answers_data reference_answers;
};

void display_a_greeting(void);

bool test_one_equation(struct test_equation_data* test_equation, struct answers_data* answers, FILE* file_pointer);
void run_test_solver(struct answers_data* answers);
void display_failed_message(struct test_equation_data* test, struct answers_data* answers);
number_of_roots str_to_enum(char* number_of_answers);
void swap_value(double* answer_1, double* answer_2);

void input_coefficient(struct coefficients_data* coefficients, struct answers_data* answers, int* program_status);
void clear_input_buffer(void);
void request_re_entry(int* program_status);

void equation_solver(struct coefficients_data* coefficients, struct answers_data* answers);
void linear_equation_solver(struct coefficients_data* coefficients, struct answers_data* answers);
void quadratic_equation_solver(struct coefficients_data* coefficients, struct answers_data* answers);
void is_not_special_value(double coefficient);

int  is_close_to_zero(double number_being_checked);
void check_minus_before_zero (double* number_being_checked);

void output_answer(struct answers_data* answers);

void program_completed(void);

#endif // KVADR_H

