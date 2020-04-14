/* 
 * Great explanation of how to read syntax of pointers to functions  
 * https://stackoverflow.com/questions/10758811/c-syntax-for-functions-returning-function-pointers
 *
 */

/*
                 ComplexFunction                                      ComplexFunction
                *ComplexFunction                                      is a pointer
               (*ComplexFunction)(                    )               to a function
               (*ComplexFunction)(int                 )                   taking a int parameter
               (*ComplexFunction)(int,      *         )                   and a pointer
               (*ComplexFunction)(int,     (*)(      ))                   to a function
               (*ComplexFunction)(int,     (*)(double))                       taking a double
               (*ComplexFunction)(int, int (*)(double))                   returning int
              *(*ComplexFunction)(int, int (*)(double))                returning a pointer
             (*(*ComplexFunction)(int, int (*)(double)))(            ) to a function
             (*(*ComplexFunction)(int, int (*)(double)))(char const *)     taking a char const*
        int* (*(*ComplexFunction)(int, int (*)(double)))(char const *)     returning a int*
*/

typedef int* (*(*ComplexFunction)(int, int (*)(double)))(char const *);

// or

typedef int* (*Pfunc)(char const *);
typedef Pfunc (*ComplexFunction)(int, int (*) (double));

// or

typedef int * (*RetFunc)(char const *);
typedef int (*ParamFunc)(double);

typedef RetFunc (*ComplexFunction)(int, ParamFunc);


