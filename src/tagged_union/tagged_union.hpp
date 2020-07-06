#ifndef TAGGED_UNION
#define TAGGED_UNION

class Value
{
public:
    Value& operator=(const Value& rhs) = default;
    Value& operator=(Value&& rhs) = default;
    Value(const Value& x) = default;
    Value(Value&& x) = default;
    Value() = default;
    ~Value() = default;

    explicit Value(float x);
    explicit Value(int x);

    const int* const int_type() const;
    const float* const float_type() const;

    void set_int_type(int ii);
    void set_float_type(float ff);

private:
    enum class Tag
    {
        int_type,
        float_type
    };
    Tag type;

    union {
        int i;
        float f;
    };
};

#endif // TAGGED_UNION
