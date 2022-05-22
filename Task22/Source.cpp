#include <utility>
#include <memory>
#include <string>
#include <vector>

template<class T, class V>
std::pair<T*, V*> fun1()
{
    return std::make_pair(new T, new V);
}

template<class T, class V>
std::pair<std::unique_ptr<T>, std::unique_ptr<V>> fun2()
{
    return std::make_pair(
        std::unique_ptr<T>(new T),
        std::unique_ptr<V>(new V));
}

// строгая гарантия
template<class T, class V>
std::pair<std::unique_ptr<T>, std::unique_ptr<V>> fun3()
{
    std::unique_ptr<T> pt(new T);
    std::unique_ptr<V> pv(new V);
    return std::make_pair(std::move(pt), std::move(pv));
}

// строгая гарантия
template<class T, class V>
void fun4(std::vector<std::string>& v)
{
    std::reverse(v.begin(), v.end());
}

template<class T, class V>
void fun5(std::vector<std::string>& v, std::string const& s)
{
    std::fill(v.begin(), v.end(), s);
}

// строгая гарантия
template<class T, class V>
void fun6(std::vector<std::string>& v, std::string const& s)
{
    std::vector<std::string>(v.size(), s).swap(v);
}

int main()
{
    return 0;
}