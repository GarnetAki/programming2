#ifndef C_BUF
#define C_BUF

size_t norm_pos(size_t x, size_t m){
    if(x>m)x %= m;
    while(x<0)x+=m;
    return x;
}

template <typename T>
class Circular_buffer
{
private:
    T *arr;
    size_t head;
    size_t size;
    size_t max_capacity;
    size_t capacity;

public:
    Circular_buffer(size_t new_capacity)
    {
        capacity = new_capacity;
        head = 0;
        size = 0;
        max_capacity = INT_MAX;
        arr = new T[new_capacity];
    }

    Circular_buffer() : Circular_buffer(2) {}
    ~Circular_buffer()
    {
        delete[] arr;
    }

    void capacity_change(size_t new_capacity)
    {
        new_capacity = std::min(new_capacity, max_capacity);
        T *arr_tmp = new T[new_capacity];
        for (int i = 0; i < std::min(new_capacity, capacity); ++i)
        {
            arr_tmp[i] = arr[(head + i) % capacity];
        }
        delete[] arr;
        arr = arr_tmp;
        capacity = new_capacity;
        head = 0;
    }

    T &operator[](int x)
    {
        return arr[(head + x) % capacity];
    }

    T &front()
    {
        return arr[head];
    }

    T &back()
    {
        return arr[(head + size) % capacity];
    }

    size_t length(){
        return size;
    }

    void push_front(const T &x)
    {
        head = (head - 1 + capacity) % capacity;
        arr[head] = x;
        size++;
        if (size > capacity)size = capacity;
    }

    void pop_front()
    {
        head = (head + 1) % capacity;
        size--;
        if (size < 0)
            size = 0;
    }

    void push_end(const T &x)
    {
        if (size == capacity)
        {
            pop_front();
        }
        arr[(head + size) % capacity] = x;
        size++;
    }

    void pop_end()
    {
        size--;
        if (size < 0)size = 0;
    }

    class iterator
    {
    private:
        const Circular_buffer<T> *base;
        size_t position;

    public:
        using difference_type = size_t;
        using value_type = T;
        using pointer = T*;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

        iterator(const Circular_buffer<T> *new_base, size_t new_position){
            base = new_base;
            position = new_position;
        }
        ~iterator() = default;

        inline iterator &operator+=(difference_type operated)
        {
            position += operated;
            return *this;
        }
        inline iterator &operator-=(difference_type operated)
        {
            position = position - operated;
            while (position < 0)
            {
                position += base->capacity;
            }
            return *this;
        }
        inline T &operator*() const
        {
            return base->arr[(base->head + position) % base->capacity];
        }
        inline T *operator->() const
        {
            return base->arr + ((base->head + position) % base->capacity);
        }
        inline T &operator[](difference_type operated) const
        {
            size_t tmp = (base->head + position + operated);
            while (tmp < 0)
            {
                tmp += base->capacity;
            }
            tmp %= base->capacity;
            return base->arr + tmp;
        }

        inline iterator &operator++()
        {
            position = norm_pos(position + 1, this->base->capacity);
            return *this;
        }
        inline iterator &operator--()
        {
            position = norm_pos(position - 1, this->base->capacity);
            return *this;
        }
        inline iterator operator++(int) const
        {
            iterator tmp(*this);
            tmp.position = norm_pos(position + 1, this->base->capacity);
            return tmp;
        }
        inline iterator operator--(int) const
        {
            iterator tmp(*this);
            tmp.position = norm_pos(position - 1, this->base->capacity);
            return tmp;
        }

        inline difference_type operator-(const iterator &operated) const
        {
            size_t tmp = norm_pos(position - operated.position, operated.base->capacity);
            return tmp;
        }
        inline iterator operator+(difference_type operated) const
        {
            return iterator(this->base, norm_pos(position + operated, this->base->capacity));
        }
        inline iterator operator-(difference_type operated) const
        {
            return iterator(this->base, norm_pos(position - operated, this->base->capacity));
        }
        friend inline iterator operator+(difference_type operated1, const iterator &operated2)
        {
            return iterator(operated2->base, norm_pos(operated1 + operated2.position, operated2->base->capacity));
        }
        friend inline iterator operator-(difference_type operated1, const iterator &operated2)
        {
            return iterator(operated2->base, norm_pos(operated1 - operated2.position, operated2->base->capacity));
        }

        inline bool operator==(const iterator &operated) const
        {
            return (position == operated.position) && (base == operated.base);
        }
        inline bool operator!=(const iterator &operated) const
        {
            return (position != operated.position) && (base != operated.base);
        }
        inline bool operator>(const iterator &operated) const
        {
            return (position > operated.position) && (base == operated.base);
        }
        inline bool operator<(const iterator &operated) const
        {
            return (position < operated.position) && (base == operated.base);
        }
        inline bool operator>=(const iterator &operated) const
        {
            return (position >= operated.position) && (base == operated.base);
            ;
        }
        inline bool operator<=(const iterator &operated) const
        {
            return (position <= operated.position) && (base == operated.base);
            ;
        }
    };

    iterator begin()
    {
        return iterator(this, 0);
    }

    iterator end()
    {
        return iterator(this, size);
    }
};

#endif