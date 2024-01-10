#include <iostream>
#include <initializer_list>
#include <iterator>

template <typename T> class DequeBasedOnArray
{
public:
    using Iterator = T*;

    DequeBasedOnArray();

    explicit DequeBasedOnArray(int _size);

    DequeBasedOnArray(const DequeBasedOnArray& _object);

    DequeBasedOnArray(DequeBasedOnArray&& _object);

    DequeBasedOnArray(std::initializer_list<int> _ilist);

    ~DequeBasedOnArray();

    DequeBasedOnArray& operator=(const DequeBasedOnArray& _object);

    DequeBasedOnArray& operator=(DequeBasedOnArray&& _object);

    DequeBasedOnArray& operator=(std::initializer_list<int> _ilist);

    DequeBasedOnArray::Iterator begin();
    const DequeBasedOnArray::Iterator begin() const;
    DequeBasedOnArray::Iterator end();
    const DequeBasedOnArray::Iterator end() const;

    const int& operator[](int _index) const;
    int& operator[](int _index);

    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const DequeBasedOnArray<T>& _object);

    unsigned GetSize() const;
    bool PushFront(const T& _element);
    bool PopFront(T& _element);
    bool PushBack(const T& _element);
    bool PopBack(T& _element);
    bool PeekFront(T& _element) const;
    bool PeekBack(T& _element) const;


private:
    T* arr;
    int size;
};

template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray()
{
    size = 0;
    arr = new int(size);
}
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(int _size) : size(_size)
{
    arr = new int[_size];
}
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(const DequeBasedOnArray& _object)
{
    arr = new int[_object.size];
    size = _object.size;
    for (int i = 0; i < size; ++i)
    {
        arr[i] = _object.arr[i];
    }
}
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(DequeBasedOnArray&& _object)
{
    arr = _object.arr;
    size = _object.size;
    _object.arr = nullptr;
}
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(std::initializer_list<int> _ilist)
    : arr(new int[_ilist.size()]), size(_ilist.size())
{
    int i = 0;
    for (const auto& element : _ilist)
    {
        arr[i++] = element;
    }
}
template <typename T>
DequeBasedOnArray<T>::~DequeBasedOnArray() {
    delete[] arr;
}
template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(const DequeBasedOnArray& _object)
{
    if (this == &_object)
    {
        return *this;
    }
    delete[] arr;
    arr = new int[_object.size];
    size = _object.size;
    for (int i = 0; i < size; ++i)
    {
        arr[i] = _object.arr[i];
    }
    return *this;
}
template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(DequeBasedOnArray&& _object)
{
    if (this == &_object)
    {
        return *this;
    }
    delete[] arr;
    arr = _object.arr;
    size = _object.size;
    _object.arr = nullptr;
}

template<typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(std::initializer_list<int> _ilist)
{
    delete[] arr;
    arr = new int[_ilist.size()];
    size = _ilist.size();
    int i = 0;
    for (const auto& element : _ilist)
    {
        arr[i++] = element;
    }
    return *this;
}


template<typename T>
typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::begin()
{
    return Iterator(arr);
}

template<typename T>
const typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::begin() const
{
    return Iterator(arr);
}

template<typename T>
typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::end()
{
    return Iterator(arr + size);
}

template<typename T>
const typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::end() const
{
    return Iterator(arr + size);
}

const int& DequeBasedOnArray<int>::operator[](int _index) const
{
    return _index;
}

int& DequeBasedOnArray<int>::operator[](int _index)
{
    return _index;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const DequeBasedOnArray<T>& _object)
{
    for (int* i1 = _object.begin(); i1 != _object.end(); i1++)
        stream << *i1 << " ";
    stream << std::endl;
    return stream;
}


template <typename T>
unsigned DequeBasedOnArray<T>::GetSize() const
{
    return size;
}

template<typename T>
bool DequeBasedOnArray<T>::PushFront(const T& _element)
{
    int* arr2 = arr;
    try {
        arr = new int[size + 1];
        arr[0] = _element;
        for (int i = 0; i < size; i++)
            arr[i + 1] = arr2[i];
        size++;
        if (size > 1)
            delete[] arr2;
        return true;
    }
    catch (...)
    {
        arr = arr2;
        return false;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PopFront(T& _element)
{
    if (size == 0)
        return false;
    else {
        int* arr2;
        _element = arr[0];
        arr2 = new int[size - 1];
        size--;
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i + 1];
        if (size > 0)
            delete[] arr;
        arr = arr2;
        return true;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PushBack(const T& _element)
{
    int* arr2 = arr;
    try {
        arr = new int[size + 1];
        for (int i = 0; i < size; i++)
            arr[i] = arr2[i];
        arr[size] = _element;
        size++;
        if (size > 1)
            delete[] arr2;
        return true;
    }
    catch (...)
    {
        arr = arr2;
        return false;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PopBack(T& _element)
{
    if (size == 0)
        return false;
    else {
        int* arr2;
        _element = arr[size - 1];
        arr2 = new int[size - 1];
        size--;
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i];
        if (size > 0)
            delete[] arr;
        arr = arr2;
        return true;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PeekFront(T& _element) const
{
    if (size > 0)
    {
        _element = arr[0];
        return true;
    }
    else
        return false;
}

template<typename T>
bool DequeBasedOnArray<T>::PeekBack(T& _element) const
{
    if (size > 0)
    {
        _element = arr[size - 1];
        return true;
    }
    else
        return false;
}

int main()
{
    return 0;
}