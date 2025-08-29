const int MAX_LEN_STR_NUM_ROOTS = 14;

enum number_of_roots
{
    ERROR_SOLUTIONS = -2,
    INF_SOLUTIONS   = -1,
    NO_SOLUTIONS    =  0,
    ONE_SOLUTION    =  1,
    TWO_SOLUTIONS   =  2
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

void run_test_solver(struct answers_data* answers, FILE* file_pointer);
bool test_one_equation(struct test_equation_data* test, struct answers_data* answers, FILE* file_pointer);
void equation_solver(struct coefficients_data* coefficients, struct answers_data* answers);

void display_failed_message(struct test_equation_data* test, struct answers_data* answers);
number_of_roots str_to_enum(char* number_of_answers);
void swap_value(double* answer_1, double* answer_2);
int  is_close_to_zero(double number_being_checked);
