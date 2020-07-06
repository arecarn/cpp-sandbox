#include "tagged_union.hpp"

Value::Value(float x)
{ // NOLINT(cppcoreguidelines-pro-type-member-init)
    type = Tag::float_type;
    f = x; // NOLINT(cppcoreguidelines-pro-type-union-access)
}

Value::Value(int x)
{ // NOLINT(cppcoreguidelines-pro-type-member-init)
    type = Tag::int_type;
    i = x; // NOLINT(cppcoreguidelines-pro-type-union-access)
}

const int* const Value::int_type() const
{
    if (type != Tag::int_type)
    {
        return nullptr;
    }
    return &i; // NOLINT(cppcoreguidelines-pro-type-union-access)
}

const float* const Value::float_type() const
{
    if (type != Tag::float_type)
    {
        return nullptr;
    }
    return &f; // NOLINT(cppcoreguidelines-pro-type-union-access)
}

void Value::set_int_type(int ii)
{
    type = Tag::int_type;
    i = ii; // NOLINT(cppcoreguidelines-pro-type-union-access)
}

void Value::set_float_type(float ff)
{
    type = Tag::float_type;
    f = ff; // NOLINT(cppcoreguidelines-pro-type-union-access)
}
