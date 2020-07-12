#ifndef C_STYLE_TEMPLATE_H
#define C_STYLE_TEMPLATE_H

#include <stdint.h>

#define GLOBAL_ARRAY_SIZE (10)

#ifdef __cplusplus
extern "C"
{
#endif

    // TYPES & CONSTANTS
    ////////////////////////////////////////////////////////////////////////////

    typedef struct TypeName
    {
        int name_one;
        char name_two;
        float name_three;
    } TypeName;

    extern int g_global_array[GLOBAL_ARRAY_SIZE];


    // FUNCTION DECLARATIONS
    ////////////////////////////////////////////////////////////////////////////

    void function_name(
        TypeName* const parameter_one,
        int parameter_two
    );


#ifdef __cplusplus
} // extern "C"
#endif

#endif // header guard
