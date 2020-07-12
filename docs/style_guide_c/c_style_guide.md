# C Style Guide

## Naming


### General Naming Guidelines
* Type information should not be encoded into a variables name e.g. using Hungarian notation.
* Avoid abbreviations if possible
* The length of a name should be proportional to its scope
* Acronyms will always use capitol letters regardless of naming rules (does this apply to types?)
    * Max_LED_Brightness
    * starting_PWM_duty_cycle
    * MSP430_ADC
* When applicable include the unit of measure
    * megaamps
    * megatons
    * volts
    * rpm
    * hertz
    * mph
    * lbs
    * milliseconds
    * kilometers
### Type Names

Applies struct, enum, union, and typedef

```c
typedef struct StructName StructName;
typedef int TypeDefName;
typedef enum EnumName;

```

### All struct, enum, and union Declarations Will Have A typedef Matching Their Tag Name

**Rational:**
* Avoids writing struct, enum, union all over the place
* Still enables forward declarations

**Example:**

```c
typedef struct Type
{
    int a;
    char b;
} Type;
```

```c
typedef enum EnumType
{
    EnumType_a;
    EnumType_b;
} EnumType;
```


### Local Variable Names

Local variables are all lower case with words separated by underscores.

**Example:**
```c
uint32_t variable_name;
volatile uint32_t variable_name;
uint32_t * variable_name;
const uint32_t variable_name;
const uint32_t * variable_name;
uint32_t *const variable_name;
const uint32_t *const variable_name;
```


### Static Global Variable Names

Static variables are all lower case with words separated by underscores and
prefixed with "s\_" to indicate the its static file scope.

**Example:**
```c
static uint32_t s_static_global_name;
static const uint32_t s_static_global_name;
static const uint32_t *const s_static_global_name;
```


### Global Variable Names

Global variables are all lower case with words separated by underscores and
prefixed with "g\_" to indicate the its global scope.

**Example:**

```c
uint32_t g_global_name;
const uint32_t g_global_name;
const uint32_t * g_global_name;
```


#### Struct Member Variables

Struct member variables are named like normal variables without `m_` prefix.

```c
uint32_t variable_name;
uint32_t* variable_name;
```


### Function Names

Function names are all lower case with words separated by underscores.

**Example:**
```c
void bake_bread(void);
bool is_bread_done(void);
bool get_volume_in_dB(void);
```


### Static Function Names

Static functions are named the same as normal functions, with the addition of a "s\_" prefix.

**Example:**
```c
static void s_bake_bread(void);
static bool s_is_bread_done(void);
```


### Constants

**Example:**
```C
static const uint8_t Maximum_Value = 55;
static const float Maximum_Value = 12345.678f;
```


### Enumerations

Are named like Constant but with the Enumeration name as a prefix.

**Example:**
```c
typedef enum EnumName
{
    EnumName_Name_One;
    EnumName_B;
    EnumName_Max;
} EnumName;
```


### Macro Names

Macro will be named with all capitol letters with words separated by underscores.

**Example:**
```c
#define DEFINE_NAMES 5
#define SUM(a, b) ((a) + (b))
```


### Source File Names
* Source and header file names will be names with all lowercase characters separated by underscores.
* Source files will use the `.c` extension, and header files will use the `.h` extension.
* Test files should have a `_test` before the file extension.

**Rational:**
Using all lower case names avoids issues with having two files that differ only in case being introduced into a case insensitive environment like Windows.

**Example:**
* source_file_name.c
* header_file_name.h
* source_file_name_test.c
* source_file_name_test.h


## Misc

* cases in a switch statement without a break should be followed with a `// fallthrough` comment
* ignored function return values should be cast to void


## Formatting


### Indentation

* Use 4 spaces for per indentation level, and do not use tabs.


### Line Length

* 80 characters is the maximum line length.

**Exceptions:**

* A comment who's readability would be harmed if split e.g. a URL longer than 80 characters.
* A string literal with content that exceeds 80 characters.

**Rational:**

* This aids in viewing two or three files side by side which is epically
  helpful for diffs merges.
* In some limited width views long lines that are soft wrapped can make reading code difficult
* shorter lines are easier for the eye to follow
* long lines can be a signal of a code smell

### Curly Braces

Open curly braces shall be vertically aligned with their matching close curly brace.
Except in the following cases:
* Assignment to an array or struct initializer the final curly braces
  follows the final value in the initializer
* Empty curly braces are right next to one another with no spaces between them.

**Example:**
```c
int a[3] = {
    3,
    5,
    1}

int a = 0;
while (a != 10)
{
    a++
}

void function_name(
    Type *const parameter2,
    int parameter1)
{
    ...
}

while(function(i)) {}
```

### Function Declaration and Definitions

* Return type should be on the same line as the function name.
* function parameters shall each be on their own line and be indented by one level of indentation.
* The closing parenthesis shall go on it's own line and is not indented.
* There is no space between the function name and open parenthesis.

**Rational:**
* This style of parameter alignment minimizes diffs for when function parameters change

**Example:**
```c
ReturnType function_name(
    Type *const parameter2,
    int parameter1
)
{

}
```

### Floating-point Literals

* Floating-point literals should always have a radix point, with digits on both sides
* the "e" in exponent form should always be lower case

**Example:**

```C
float f = 1.0f;
long double ld = -0.5L;
double d = 1248.0e6;
```

### Literal Suffixes

* literal suffixes "u", "f",  should be lower case.
* The integer literal "L" should always be capitalized, so not to be confused with the one digit "1"

**Example:**

```C
float f = 1.0f;
long double ld = -0.5L;
unsigned int ui = 500u;
long long unsigned int ui = 500uLL;
```

### Function Calls

* if it fits write the call all on a single line
* if it doesn't fit put each parameter on it's own line indented by 4 spaces
  with the closing parenthesis following the last argument name.

**Example:**

```C
float f = function_name(function_argument_1, function_argument_2);
int i = function_with_many_parameters(
        function_argument_1,
        function_argument_2,
        function_argument_3,
        function_argument_4);
```

### Conditionals

* the if or else condition should be on it's own line.
* Put a space after the conditional keywords else and if
* Don't put spaces inside parenthesis
* braces are always required for single statement if and else conditions

**Example:**

```C
if (condition)
{
    ...
}
else
{
    ...
}
```

### Switch Statements

* indent case labels by one level, then indent statements withing case labels
  by another level.

**Example:**

```C
switch (i)
{
    case 1:
        ++j
        break;
    case 2:
    {
        --j
        --k
    }
    break;

    default:
        break;
};
```

### Loops

* braces are always required for single statement loops
* braces are required for loops with no body, and each brace must be on it's own line.

**Example:**

```C
while (condition)
{
    ...
}

while (condition)
{
}

for (int i = 0; i < 100; ++i)
{
    ...
}

for (
    int descriptive_variable = 0;
    descriptive_variable < Maximum_Value;
    ++descriptive_variable)
{
    ...
}
```


### Pointer Expressions

* There is no space after the dereference operator "\*" and the pointer it is operating on
* There are no spaces before or after the arrow operator for accessing members of a pointed to object.
* prefer the arrow operator over dereferencing and using the dot operator

```C
x = *p;
x = r->y;
x = *(r).y; // BAD
```

### Dot Operator (Member Access)

* there should be no spaces before or after the dot operator

```C
x = y.z;
```

### Operators

* All binary operators (operators that take two parameters) should be
  surrounded by spaces. This includes the following:
    * Assignment (=)
    * Compound assignment (+=, -=, \*=, /=, %=, >>=, <<=, &=, ^=, |=)
    * Arithmetic (+, -, \*, /, %)
    * Relational and comparison operators (==, !=, >, <, >=, <=)
    * Logical operators (&&, ||)
    * Bitwise operators (&, |, ^, <<, >>)

```c
int a = (10 + 5) - (5 / 100);
uint32_t result = x ^ y;
```

* The comma operator shall not be preceded by a space, and shall be followed by a space.

* Unary operators shall not have any space between them and their parameter.
  This includes the following:
    * Increment and Decrement (++, --)
    * Logical not (!)
    * Bitwise not (~)


* sizeof() shall be formatted like a function and have it's parameter within parenthesis


### Casts

* casts shall not have space inside their parenthesis
* there shall be no spaces between the cast and the expression being casted

**Example:**

```c
int i = (int)function();
```
### Return Values

### Variable and Array Initialization

### Preprocessor Directives

### Extern "C" Formatting

### Horizontal Whitespace

### Vertical Whitespace


## References

* https://google.github.io/styleguide/cguide.html
* https://llvm.org/docs/CodingStandards.html#name-types-functions-variables-and-enumerators-properly
* https://github.com/isoc/cCoreGuidelines
