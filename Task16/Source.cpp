#include <vector>
#include <list>

template<class T>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
{
private:
    using Vector = std::vector<T>;
    using List = std::list<Vector>;
    using VectorIter = typename Vector::const_iterator;
    using ListIter = typename List::const_iterator;

    const List* list_;
    const Vector* vector_;
    ListIter list_pointer_;
    VectorIter vector_pointer_;

public:
    Iterator() = default;
    Iterator(const List* list, ListIter l_point, const Vector* vector, VectorIter v_point) :
        list_(list),
        list_pointer_(l_point),
        vector_(vector),
        vector_pointer_(v_point) {}

    typename Iterator::reference operator*() const { return *vector_pointer_; }

    typename Iterator::pointer operator->() const { return &(*vector_pointer_); }

    Iterator& operator++()
    {
        if (std::next(vector_pointer_) != vector_->end())
        {
            ++vector_pointer_;
        }
        else if (std::next(list_pointer_) != list_->end())
        {
            ++list_pointer_;
            vector_ = &(*list_pointer_);
            vector_pointer_ = vector_->begin();
        }
        else
        {
            ++vector_pointer_;
        }
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator temp(*this);
        operator++();
        return temp;
    }

    Iterator& operator--()
    {
        if (vector_pointer_ != vector_->begin())
        {
            --vector_pointer_;
        }
        else if (list_pointer_ != list_->begin())
        {
            --list_pointer_;
            vector_ = &(*list_pointer_);
            vector_pointer_ = std::prev(vector_->end());
        }
        else
        {
            --vector_pointer_;
        }
        return *this;
    }

    Iterator operator--(int)
    {
        Iterator temp(*this);
        operator--();
        return temp;
    }

    bool operator==(Iterator const& other) const
    {
        return list_pointer_ == other.list_pointer_ && vector_pointer_ == other.vector_pointer_;
    }

    bool operator!=(Iterator const& other) const
    {
        return !operator==(other);
    }
};

template<class T>
class VectorList
{
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const&) = default;
    VectorList(VectorList&&) = default;

    VectorList& operator=(VectorList&&) = default;
    VectorList& operator=(VectorList const&) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q); // определена снаружи
/*  {
        if (p != q)
            data_.push_back(VectT(p,q));
    }
*/

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t s = 0;
        for (auto const& d : data_)
            s += d.size();
        return s;
    }

    // определите const_iterator
    using const_iterator = Iterator<T>;

    // определите методы begin / end
    const_iterator begin() const
    {
        return const_iterator(
            &data_,
            data_.begin(),
            &(*data_.begin()),
            (*data_.begin()).begin()
        );
    }
    const_iterator end() const
    {
        if (empty()) return begin();
        return const_iterator(
            &data_,
            std::prev(data_.end()),
            &(*std::prev(data_.end())),
            (*std::prev(data_.end())).end()
        );
    }

    // определите const_reverse_iterator
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

private:
    ListT data_;
};