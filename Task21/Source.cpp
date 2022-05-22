#include <utility> // std::declval
#include <string>

// ������ do_math ������� ���� T
// - ����������
// - �������������
// - ������������ ���������� +
template<class T>
void do_math() noexcept(
    std::is_nothrow_copy_constructible<T>() && 
    std::is_nothrow_copy_assignable<T>() && 
    std::is_nothrow_move_constructible<T>() &&
    std::is_nothrow_move_assignable<T>() &&
    noexcept(std::declval<T>() + std::declval<T>()))
{
    // ���� ������� ����� �������� ������
}

int main()
{
    bool b1 = noexcept(do_math<int>()); // true
    bool b2 = noexcept(do_math<std::string>()); // false
    return 0;
}