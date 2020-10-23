# C++ Style Guide

## Naming

### Type Names

* applies to classes, structs, enums, template type parameters
```cpp
class ClassName;
struct StructName;
enum EnumName;
enum class EnumClassName;
template <typename T, typename Type>
```

### Variable Names

#### Automatic Variables

Applies to constants with a non-static storage durations like automatic variables.
```cpp
uint32_t variable_name;
volatile uint32_t variable_name;
uint32_t& variable_name;
uint32_t* variable_name;
const uint32_t variable_name;
const uint32_t* variable_name;
```

#### Static Constant Variables

This Applies to constants with a static storage duration
```cpp
const uint32_t* Variable_Name;
const uint32_t Variable_Name;
constexpr uint32_t Variable_Name;
```

#### Static Global Variables

```cpp
static uint32_t g_static_global_name;
```

#### Global Variables

```cpp
uint32_t g_global_name;
```

#### Struct and Class Member Variable Names

```cpp
// class member variables
class ClassName
{
    priavate:
    static static_variable_name;

    const uint32_t Private_Const_Name;
    static constexpr uint32_t Private_Static_Constexpr_Name = 42;

    uint32_t m_variable_name;
    volatile uint32_t m_volatile_variable_name;
    uint32_t& m_reference_name;
    uint32_t* m_pointer_name;
    const uint32_t* m_pointer_to_const_name;
    uint32_t *const m_const_pointer_to_variable_name;

    ...

    public:
    static static_variable_name;

    const uint32_t Private_Const_Name;
    static constexpr uint32_t Private_Static_Constexpr_Name = 42;

    uint32_t variable_name;
    volatile uint32_t volatile_variable_name;
    uint32_t& reference_name;
    uint32_t* pointer_name;
    const uint32_t* pointer_to_const_name;
    uint32_t *const const_pointer_to_variable_name;

    ...
};
```

### Free Function Names

* command or query

```cpp
void bake_bread();
bool is_bread_done();
static bool s_name_bread();
```

### Class Member Functions

```cpp
class ClassName
{
public:
    uint32_t run_query();
    static uint32_t instance_count;
    void member_var(uint32_t value);
    uint32_t member_var();

private:
    uint32_t m_member_var;
    uint32_t m_count;
}
```

* Getter or Setters should have the same name as the member, without any m_ prefix.

### Namespace Names

* specifies a project name

```cpp
namespace Style
{
namespace Guide
{

...

}
}
```

### Enums and Enumerations

```cpp
enum EnumName
{
    Enumerator_Name_A;
    Enumerator_Name_B;
    Enumerator_Name_Max;
}
```

```cpp
enum class EnumName
{
    Enumerator_Name_A;
    Enumerator_Name_B;
    Enumerator_Name_Max;
}
```

### Macro / #define Names

* Parenthesize all macro parameters
```cpp
#define DEFINE_NAMES 5
#define SUM(a, b) ((a)+(b))
```

### File Names

```txt
source_file_name.cpp
header_file_name.test.cpp
header_file_name.other.test.cpp
header_file_name.hpp
```

### Source Layout

Project that has one or more non-text executables, and might also provide a library:
```txt
src
+-lib/
| +-dog/
| | |-bark.cpp
| | |-bark.hpp
| | `-bark.test.cpp
| +-cat/
|   |-meow.cpp
|   |-meow.hpp
|   `-meow.test.cpp
+-bin/
  |-pets.main.cpp
  `-stray.main.cpp
```

* src is the top level directory containing directories with code below it
* bin is inside src and contains executable entry points (optional)
* lib is inside src and contains code used in executables or as libraries

Project that is a Library:
```txt
src
+-dog/
| |-bark.cpp
| |-bark.hpp
| `-bark.test.cpp
+-cat/
  |-meow.cpp
  |-meow.hpp
  `-meow.test.cpp
```
* src is the top level directory containing directories with code below it

### Exceptions to Naming Rules

* replicating standard library functionality
* test names

### General Naming Guidelines

* Type information should not be encoded into a variables name e.g. using hungarian notation.
* limit abbreviating to widely used abbreviations like those found in Wikipedia.
* the length of a name should be proportional to its scope
* acronyms will always use capitol letters regardless of naming rules
* when applicable include the unit of measure
    * megaamps
    * megatons
    * volts
    * RPM
    * hertz
    * MPH
    * lbs
    * milliseconds
    * kilometers

## Formatting

### Indentation
* Use 4 spaces per indentation level and do not use tabs
* no indent inside namespaces
* no indent inside switch statement cases inside switch statement
* no indent after access specifiers private, protected, public

```cpp
void function_name(
    Type parameter_2,
    int parameter_1,
);
```

### Line Length
* 80 characters
    * split screens
    * side by side diffs
* exceptions
    * URLs
    * string literals
    * slight deviations
