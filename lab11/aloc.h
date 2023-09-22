#ifndef ALOC
#define ALOC
#include <bits/stdc++.h>

template <typename T>
class shared_ptr
{
private:
    std::size_t *cnt;
    T *it;
    bool was_init;

public:
    shared_ptr(){
        cnt = new std::size_t(0);
        was_init = false;
    };
    shared_ptr(T *new_it)
    {
        it = new_it;
        cnt = new std::size_t(0);
        was_init = false;
    }
    void init (T* p) {
        if(was_init)this->~shared_ptr();
        was_init = true;
        it = p;
        ++(*cnt);
    }
    ~shared_ptr()
    {
        if (*cnt == 1)
        {
            free(it);
            delete cnt;
        }
        else
        {
            (*cnt)--;
        }
    }
    T* iter(){
        return it;
    }
    operator T *() const
    {
        return it;
    }
    shared_ptr& operator=(T *obj)
    {
        if(was_init)this->~shared_ptr();
        was_init = true;
        it = obj;
        return *this;
    }
    shared_ptr& operator=(const shared_ptr &obj)
    {
        if(was_init)this->~shared_ptr();
        was_init = true;
        it = obj.it;
        cnt = obj.cnt;
        (*cnt)++;
        return *this;
    }
};

class block
{
private:
    std::size_t len;
    std::size_t cnt;
    std::vector<bool> use;
    std::size_t all_use;
    void *it;

public:
    block() = default;
    block(std::size_t new_length, void *new_it, std::size_t new_cnt)
    {
        len = new_length;
        cnt = new_cnt;
        it = new_it;
        all_use = 0;
        use.resize(cnt);
        for (int i = 0; i < cnt; ++i)
            use[i] = false;
    }

    block(const block &obj)
    {
        len = obj.len;
        cnt = obj.cnt;
        it = obj.it;
        all_use = obj.all_use;
        use.resize(cnt);
        for (int i = 0; i < cnt; ++i)
            use[i] = obj.use[i];
    }

    ~block() = default;

    std::size_t length()
    {
        return len;
    }

    bool used(std::size_t n)
    {
        return use[n];
    }

    std::size_t count()
    {
        return cnt;
    }

    bool all_used()
    {
        return (all_use == cnt);
    }

    void *start()
    {
        return it;
    }

    char *make_used()
    {
        std::size_t i = 0;
        while (use[i])
            i++;
        use[i] = 1;
        all_use++;
        char *tmp = ((char *)it) + (i * len);
        return tmp;
    }

    void dealoc(int k)
    {
        k /= len;
        if (use[k])
            all_use--;
        use[k] = 0;
    }
};

template <typename T>
class ralloc
{
private:
    template <class U>
    friend class ralloc;
    shared_ptr<void> st;
    std::size_t max_siz;
    std::size_t siz;
    shared_ptr<block> arr;

public:
    typedef T value_type;
    ralloc(std::vector<std::size_t> a)
    {
        std::size_t sum = 0;
        max_siz = 0;
        std::sort(a.begin(), a.end());
        for (int i = 0; i < a.size(); ++i)
        {
            max_siz = std::max(max_siz, a[i]);
            sum += a[i];
        }
        st.init(malloc(sum));
        char *it = (char *)(st.iter());
        std::size_t k = 0;
        arr.init((block *)malloc(sizeof(block) * a.size()));
        std::size_t cnt_eq = 1;
        std::size_t mem = -1;
        std::size_t j = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            if (a[i] != mem)
            {
                if (mem != -1)
                {
                    new ((block*)arr + j) block(mem, it + k, cnt_eq);
                    k += mem * cnt_eq;
                    cnt_eq = 1;
                    j++;
                }
                mem = a[i];
            }
            else
            {
                cnt_eq++;
            }
        }
        new ((block*)arr + j) block(a[a.size() - 1], it + k, cnt_eq);
        arr = (block *)realloc((void *)arr, sizeof(block) * (j + 1));
        siz = j + 1;
    }
    template <class U>
    ralloc(const ralloc<U> &obj)
    {
        st = obj.st;
        max_siz = obj.max_siz;
        siz = obj.siz;
        arr = obj.arr;
    }

    ralloc(){
        st.init(malloc(1));
        max_siz = 1;
        siz = 1;
        arr.init((block *)malloc(sizeof(block)));
        new (arr) block(1, st, 1);
    }

    char *byte_start()
    {
        return (char *)(st.iter());
    }

    T *start()
    {
        return (T *)(st.iter());
    }

    T *allocate(std::size_t n)
    {
        if (n * sizeof(T) > max_siz)
            throw std::invalid_argument("There is not existing block with so much memory in allocator.");
        for (std::size_t i = 0; i < siz; ++i)
        {
            if (((block*)arr + i)->length() >= n * sizeof(T) && !((block*)arr + i)->all_used())
            {
                T *tmp = (T *)((block*)arr + i)->make_used();
                return tmp;
            }
        }
        throw std::invalid_argument("Can not find block with so much memory in allocator.");
    }

    void deallocate(T *p, std::size_t n)
    {
        int k = p - start();
        std::size_t l = 0;
        while (k >= 0)
        {
            k -= ((arr + l)->count() * (arr + l)->length());
            l++;
        }
        l--;
        k += (arr + l)->count() * (arr + l)->length();
        (arr + l)->dealoc(k * sizeof(T));
    }

    template <class U>
    bool const operator==(const ralloc<U> &obj) const
    {
        return (arr == obj.arr) && (st == obj.st);
    }

    template <class U>
    bool const operator!=(const ralloc<U> &obj) const
    {
        return !(*this == obj);
    }
};

#endif