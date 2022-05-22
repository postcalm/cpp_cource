// определение структуры Point уже подключено
struct Point
{
    constexpr Point(double x, double y)
        : x(x), y(y)
    {}

    double x = 0;
    double y = 0;
};


// сложение
constexpr Point operator+ (const Point &one, const Point &two)
{
    return Point(one.x + two.x, one.y + two.y);
}

// вычитание
constexpr Point operator- (const Point &one, const Point &two)
{
    return Point(one.x - two.x, one.y - two.y);
}

// скалярное произведение
constexpr double operator* (const Point &one, const Point &two)
{
    return (one.x * two.x) + (one.y * two.y);
}

int main()
{
    constexpr size_t size = static_cast<size_t>(Point(2, 4) * Point(4, 3));
    int m[size];
    return 0;
}