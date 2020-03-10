class Value {
    public:
        Value& operator=(const Value&);
        Value(const Value&);
        ~Value() = default;

        const int * const integer() const;
        const float * const single() const;

        void set_integer(int n);
        void set_single(float n);

    private:
        enum class Tag {
            integer,
            single
        };
        Tag type;

        union {
            int i;
            float f;
        };
};

const int * const  Value::integer() const
{
    if (type != Tag::integer) {
        return nullptr;
    }
    return &i;
}

const float * const Value::single() const
{
    if (type != Tag::single) {
        return nullptr;
    }
    return &f;
}

void Value::set_integer(int ii) {
    type = Tag::integer;
    i = ii;
}

void Value::set_single(float ff) {
    type = Tag::single;
    f = ff;
}

Value& Value::operator=(const Value& e)   // necessary because of the string variant
{
    switch (e.type) {
    case Tag::number:
        i = e.i;
        break;
    case Tag::single:
        f = e.f;
        break;
    }

    type = e.type;
    return *this;
}
