#ifndef TAGGED_UNION
#define TAGGED_UNION

#include <cstdint>

class Value
{
public:
    Value& operator=(const Value& rhs) = default; //NOLINT
    Value& operator=(Value&& rhs) = default;
    Value(const Value& x) = default;
    Value(Value&& x) = default;
    ~Value() = default;

    explicit Value(float x);
    explicit Value(int x);

    const int* as_int() const;
    const float* as_float() const;

    void as_int(int ii);
    void as_float(float ff);

    enum Tag : uint32_t
    {
        Int,
        Float
    };

    Tag tag() const;

private:
    Tag m_tag = Int;

    union
    {
        int i;
        float f;
    };
};

#endif // TAGGED_UNION
