#include <iostream>
#include <string>

struct Unit
{
    explicit Unit(size_t id)
        : id_(id)
    {}

    size_t id() const { return id_; }

private:
    size_t id_;
};

// ������� ����� ��� ��������
struct Animal : Unit
{
    // name ������ �������� ���������
    // "bear" ��� �������
    // "pig" ��� ������
    Animal(std::string const& name, size_t id)
        : Unit(id)
        , name_(name)
        , id_(id)
    {}

    size_t id() const { return id_; }

    std::string const& name() const
    {
        return name_;
    }

private:
    std::string name_;
    size_t id_;
};

// ����� ��� ��������
struct Man : virtual Unit
{
    explicit Man(size_t id)
        : Unit(id)
    {}

};

// ����� ��� �������
struct Bear : Animal, virtual Unit
{
    explicit Bear(size_t id)
        : Unit(id)
        , Animal("bear", id)
    {}

};

// ����� ��� ������
struct Pig : Animal, virtual Unit
{
    explicit Pig(size_t id)
        : Unit(id)
        , Animal("pig", id)
    {}

};

// ����� ��� ���������������
struct ManBearPig : Man, Bear, Pig, virtual Unit
{
    ManBearPig(size_t id) 
        : Unit(id)
        , Man(id)
        , Bear(id)
        , Pig(id)
    {}

};

int main()
{
    size_t id = 1;
    const ManBearPig *unit = nullptr;
    if (static_cast<Unit const*>(unit))
        return;
    return 1;
}