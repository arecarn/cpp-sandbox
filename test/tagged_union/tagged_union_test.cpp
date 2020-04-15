#include "gtest/gtest.h"

class Value {
    public:
        Value& operator=(const Value& rhs) = default;
        Value& operator=(Value&& rhs) = default;
        Value(const Value& x) = default;
        Value(Value&& x) = default;
        Value() = default;
        ~Value() = default;

        explicit Value(float x);
        explicit Value(int x);

        const int * const int_type() const;
        const float * const float_type() const;

        void set_int_type(int ii);
        void set_float_type(float ff);

    private:
        enum class Tag {
            int_type,
            float_type
        };
        Tag type;

        union {
            int i;
            float f;
        };
};


Value::Value(float x) { // NOLINT
    type = Tag::float_type;
    f = x; // NOLINT
}

Value::Value(int x) { // NOLINT
    type = Tag::int_type;
    i = x; // NOLINT
}

const int * const  Value::int_type() const
{
    if (type != Tag::int_type) {
        return nullptr;
    }
    return &i; // NOLINT
}

const float * const Value::float_type() const
{
    if (type != Tag::float_type) {
        return nullptr;
    }
    return &f; // NOLINT
}

void Value::set_int_type(int ii) {
    type = Tag::int_type;
    i = ii; // NOLINT
}

void Value::set_float_type(float ff) {
    type = Tag::float_type;
    f = ff; // NOLINT
}

TEST(basic, pizza) // NOLINT
{
    Value v{5};
}
