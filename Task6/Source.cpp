#include <utility>
#include <string>

template<class T>
struct Array
{
    // ��� ����������� ���� ������ ��� �����������
    explicit Array(size_t size = 0);
    Array(Array const& a);
    Array& operator=(Array const& a);
    ~Array();

    size_t size() const;
    T& operator[](size_t i);
    T const& operator[](size_t i) const;

    void swap(Array& array)
    {
        std::swap(data_, array.data_);
        std::swap(size_, array.size_);
    }

    // ���������� ������������ �����������
    Array(Array&& array)
    {
        swap(array);
    }
    // ���������� ������������ �������� ������������
    Array& operator = (Array&& array)
    {
        swap(array);
        return *this;
    }

private:
    size_t  size_ = 0;
    T* data_ = nullptr;
};


int main()
{
    return 0;
}
