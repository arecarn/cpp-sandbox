# C++ Style Guide

## Naming

### Type Names

* applies to classes, structs, enums, template type parameters
```cpp
class ClassName;
class StructName;
enum EnumName;
enum class EnumClassName;
template <typename Type>
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
static uint32_t s_static_global_name;
```

#### Global Variables

```cpp
uint32_t g_global_name;
```

#### Class Member Variables

Note that const and constexpr member variables are static storage duration and
follow the same rules as `Static Constant Variables`.
```cpp
// class member variables
class ClassName
{
    static s_variable_name;
    uint32_t m_variable_name;
    volatile uint32_t m_variable_name;
    uint32_t& m_variable_name;
    uint32_t* m_variable_name_;
    const uint32_t* Variable_Name;
    const uint32_t Variable_Name;
    constexpr uint32_t Variable_Name;
}

```

#### Struct Member Variables

Struct member variables are named like normal variables without `m_` prefix.

```cpp
uint32_t variable_name;
uint32_t& variable_name;
uint32_t* variable_name;
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

* Getter or Setters should have the same name as the member, without any scope prefix.

### Namespace Names

* specifies a project name

```cpp
namespace style
{
namespace guide
{

...

}
}
```

### Enums and Enumerations

```cpp

Non-class plain enums shall be prefixed with the enum name if they are in the global namespace.

enum EnumName
{
    EnumName_Enumerator_Name_A;
    EnumName_Enumerator_Name_B;
    EnumName_Enumerator_Name_Max;
}

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

replicating standard library functionality

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
    * when clarity is removed
