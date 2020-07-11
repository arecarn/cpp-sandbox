#include "tagged_union.hpp"
#include <cassert>

Value::Tag Value::tag() const
{
    return m_tag;
}

Value::Value(float x)
{
    m_tag = Tag::Float;
    f = x;
}

const float* Value::as_float() const
{
    if (m_tag != Tag::Float)
    {
        assert(false);
        return nullptr;
    }
    return &f;
}

void Value::as_float(float ff)
{
    m_tag = Tag::Float;
    f = ff;
}

Value::Value(int x)
{
    m_tag = Tag::Int;
    i = x;
}

const int* Value::as_int() const
{
    if (m_tag != Tag::Int)
    {
        assert(false);
        return nullptr;
    }
    return &i;
}

void Value::as_int(int ii)
{
    m_tag = Tag::Int;
    i = ii;
}
