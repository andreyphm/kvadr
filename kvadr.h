// #ifndef KVADR_H
// #define KVADR_H

const double NUMBER_CLOSE_TO_ZERO = 10e-12;

enum num_of_roots
{
    INF_NUM_OF_SOLUTIONS = -1,
    NO_SOLUTIONS         =  0,
    ONE_SOLUTION         =  1,
    TWO_SOLUTIONS        =  2
};

enum program_what_to_do
{
    PROGRAM_QUIT         = -1,
    PROGRAM_START_AGAIN  =  0,
    PROGRAM_CONTINUE     =  1
};

struct test_reference_answers_data
{
    double x1_ref, x2_ref;
};

struct test_coefficients_data
{
    double a, b, c;
};

struct test_answers_data
{
    double x1, x2;
};

struct test_equation_data
{
    struct test_coefficients_data coefficients;
    struct test_answers_data answers;
    int number_of_answers;

    struct test_reference_answers_data reference_answers;
    int reference_number_of_answers;
};

struct coefficients_data
{
    double a, b, c;
};

struct answers_data
{
    double x1, x2;
};

struct equation_data
{
    struct coefficients_data coefficients;
    struct answers_data answers;
    int number_of_answers;
};

int test_one_equation(struct test_equation_data* test_equation);
int run_test_solver();
void test_equation_solver(struct test_equation_data* test_equation);
void test_linear_equation_solver(struct test_equation_data* test_equation);
void test_quadratic_equation_solver(struct test_equation_data* test_equation);
void test_check_minus_before_zero (double* number_being_checked);
int test_is_close_to_zero (double number_being_checked);

void input_coefficient(double* coefficient, int* program_status);
void clear_input_buffer(void);
void request_re_entry(int* program_status);

void equation_solver(struct equation_data* equation);
void linear_equation_solver(struct equation_data* equation);
void quadratic_equation_solver(struct equation_data* equation);

int  is_close_to_zero(double number_being_checked);
void check_minus_before_zero (double* number_being_checked);

void output_answer(struct equation_data* equation);

// #endif // KVADR_H

