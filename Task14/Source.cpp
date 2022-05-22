#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>


// ������� ����� ������ (�����������)
struct Shape 
{
    virtual ~Shape() {};
};

// �������������
struct Rectangle : Shape { };

// �����������
struct Triangle : Shape { };

// ������� ��� �������� ����������� ���� ���������������
bool is_intersect_r_r(Shape* a, Shape* b)
{
    return true;
};

// ������� ��� �������� ����������� �������������� � ������������
bool is_intersect_r_t(Shape* a, Shape* b)
{
    return true;
};

// Base - ������� ����� ��������
// Result - ��� ������������� �������� ������������
// Commutative - ����, ������� ����������, ���
// ����������� ������������� (�.�. f(x,y) = f(y,x)).
template<class Base, class Result, bool Commutative>
struct Multimethod2
{
    using F = std::function<Result(Base*, Base*)>;

    // ������������� ���������� ������������
    // ��� ����� t1 � t2 �������� ����� typeid 
    // f - ��� ������� ��� �������������� ������
    // ����������� ��� ��������� �� Base 
    // � ������������ �������� ���� Result
    void addImpl(std::type_index t1, std::type_index t2, const F& f)
    {
        types.insert({ { t1, t2 }, f });
    }

    // ���������, ���� �� ���������� ������������
    // ��� ����� �������� a � b
    bool hasImpl(Base* a, Base* b) const
    {
        // ���������� true, ���� ���������� ����
        // ���� �������� �������������, �� ����� 
        // ��������� ���� �� ���������� ��� b � � 
        return hasHidden(a, b) || (Commutative && hasHidden(b, a));
    }

    // ��������� ����������� � ��������
    // �� ���������� a � b
    Result call(Base* a, Base* b) const
    {
        // ���������� ��������� ���������� ����������
        // ������������ � a � b
        return hasHidden(a, b) ? callHidden(a, b) : callHidden(b, a);
    }

private:
    mutable std::map<std::pair<std::type_index, std::type_index>, F> types;

    bool hasHidden(Base* a, Base* b) const
    {
        return types.count({typeid(*a), typeid(*b)});
    }

    Result callHidden(Base* a, Base* b) const
    {
        return types[{typeid(*a), typeid(*b)}](a, b);
    }
};

int main()
{
    // ����������� ��� ����������� Shape
    // ����������� bool � ���������� ������������� 
    Multimethod2<Shape, bool, true> is_intersect;

    // ��������� ���������� ������������ ��� ���� ���������������
    is_intersect.addImpl(typeid(Rectangle), typeid(Rectangle), is_intersect_r_r);

    // ��������� ���������� ������������ ��� �������������� � ������������
    is_intersect.addImpl(typeid(Rectangle), typeid(Triangle), is_intersect_r_t);

    // ������ ��� ������    
    Shape* s1 = new Triangle();
    Shape* s2 = new Rectangle();

    // ���������, ��� ���������� ��� s1 � s2 ����
    if (is_intersect.hasImpl(s1, s2))
    {
        // ���������� ������� is_intersect_r_t(s2, s1)
        bool res = is_intersect.call(s1, s2);

        // ���������: is_intersect_r_t �������,
        // ��� ������ ���������� ����� �������������
        // � ������ �����������, � ����� ���������
        // ���������� � �������� �������. 
        // ���� ���������� ������ �������������� 
        // �� ���� ������������
    }
}