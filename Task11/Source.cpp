#include <iostream>

struct String
{
    // все объ€вленные ниже методы уже реализованы
    String() { };
    String(String const& s) { };
    String& operator=(String const& a) { return *this; };
    ~String() { };

    // реализуйте перемещающий конструктор
    String (String&& s)
    {
        std::cout << "Move Constructor" << std::endl;
    }

    // реализуйте перемещающий оператор присваивани€
    String& operator =(String&& s)
    {
        std::cout << "Move Operator = " << std::endl;
        return *this;
    }

};

String& fun1(String& s)
{
    return s;
}

String&& fun2(String& s)
{
    return std::move(s);
}

String fun3(String& s)
{
    return std::move(s);
}

String fun4(String s)
{
    return std::move(s);
}

String fun5(String s)
{
    return std::forward<String>(s);
}

String&& fun6(String&& s)
{
    return std::move(s);
}

String fun7(String&& s)
{
    return s;
}

int main()
{
    String str, str2;

    std::cout << "fun1" << std::endl;
    str2 = fun1(str);

    std::cout << "fun2" << std::endl;
    str2 = fun2(str);

    std::cout << "fun3" << std::endl;
    str2 = fun3(str);

    std::cout << "fun4" << std::endl;
    str2 = fun4(str);

    std::cout << "fun5" << std::endl;
    str2 = fun5(str);

    std::cout << "fun6" << std::endl;
    str2 = fun6(String());

    std::cout << "fun7" << std::endl;
    str2 = fun7(String());
}