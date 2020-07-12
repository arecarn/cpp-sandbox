#include "c_style_template.h"
#include <stdbool.h>

// TYPES & CONSTANTS
////////////////////////////////////////////////////////////////////////////////

typedef enum EnumName
{
    EnumName_Name_One,
    EnumName_Name_two,
    EnumName_Name_Three,
} EnumName;

static const uint8_t Maximum_Value = 55;

// GLOBAL VARIABLES
////////////////////////////////////////////////////////////////////////////////

int g_global_array[GLOBAL_ARRAY_SIZE] = {0};

// STATIC VARIABLES
////////////////////////////////////////////////////////////////////////////////

static bool s_is_initalized = false;

// STATIC FUNCTION DECLARATIONS
////////////////////////////////////////////////////////////////////////////////

static int s_function_name(
    uint8_t parameter);

// FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

void function_name(
    TypeName* const parameter_one,
    int parameter_two)
{

    while (parameter_two != 0)
    {
    }

    for (
        int descriptive_variable = 0;
        descriptive_variable < Maximum_Value;
        ++descriptive_variable)
    {
    }

    switch (parameter_two)
    {
        case 1:
            ++parameter_one->name_one;
            break;

        case 2:
        {
            --parameter_one->name_one;
            --parameter_one->name_two;
        }
        break;

        default:
            break;
    };
}

int function_with_many_parameters(
    int parameter1,
    int parameter2,
    int parameter3,
    int parameter4)
{
    return parameter1 + parameter2 + parameter3 + parameter4;
}

int main()
{
    int function_argument_1;
    if (true)
    {
        function_argument_1 = 1;
    }
    else
    {
        function_argument_1 = -1;
    }

    const int function_argument_2 = 2;
    const int function_argument_3 = 3;
    const int function_argument_4 = 4;
    int a_result = function_with_many_parameters(
        function_argument_1,
        function_argument_2,
        function_argument_3,
        function_argument_4);

    TypeName a_type = {
        .name_one = 5,
        .name_two = 'c',
        .name_three = 5.5};
    function_name(&a_type, 1);
    const int b_int = s_function_name(5 + a_result);
    const int result = (10 + 5) - (5 / 100) * a_type.name_one * b_int;
    return result;
}

// STATIC FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

static int s_function_name(
    uint8_t parameter)
{
    int j = 0;
    for (int i = 0; i < parameter; ++i)
    {
        ++j;
    }

    s_is_initalized = true;

    return j;
}
