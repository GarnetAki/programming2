#ifndef ALGO
#define ALGO

template <class InputIterator, class Prediacte>
bool all_of(InputIterator begin, InputIterator end, Prediacte predicate)
{
    for(auto i = begin; i != end; i++){
        if(!prediacte(*i))
            return false;
    }
    return true;
}

template <class InputIterator, class Prediacte>
bool any_of(InputIterator begin, InputIterator end, Prediacte predicate)
{
    for(auto i = begin; i != end; i++){
        if(prediacte(*i))
            return true;
    }
    return false;
}

template <class InputIterator, class Prediacte>
bool none_of(InputIterator begin, InputIterator end, Prediacte predicate)
{
    for(auto i = begin; i != end; i++){
        if(prediacte(*i))
            return false;
    }
    return true;
}

template <class InputIterator, class Prediacte>
bool one_of(InputIterator begin, InputIterator end, Prediacte predicate)
{
    int k = 0;
    for(auto i = begin; i != end; i++){
        if(prediacte(*i))
            k++;
    }
    return k==1;
}

template <class InputIterator, class Comparator>
bool is_sorted(InputIterator begin, InputIterator end, Comparator comp)
{
    for(auto i = begin; i != end;){
        auto j = *i;
        i++;
        if(i!=end){
            if(comp(j, *i))
                return false;
        }
    }
    return true;
}

template <class InputIterator, class Prediacte>
bool is_partitioned(InputIterator begin, InputIterator end, Prediacte predicate)
{   
    bool key = 0;
    for(auto i = begin; i != end; i++){
        if(key){
            if(!predicate(*i)){
                return false;
            }
        }
        if(!key){
            if(predicate(*i)){
                key = 1;
            }
        }
    }
    return true;
}

template <class InputIterator, class Element>
InputIterator find_not(InputIterator begin, InputIterator end, Element element)
{   
    for(auto i = begin; i != end; i++){
        if(element != *i){
            return i;
        }
    }
    return end;
}

template <class InputIterator, class Element>
InputIterator find_backwrd(InputIterator begin, InputIterator end, Element element)
{   
    for(auto i = end; i != begin; i--){
        if(i!=end){
            if(element == *i){
                return i;
            }
        }
    }
    if(*begin == element)return begin;
    return end;
}

template <class InputOpertor, class Predicate>
bool is_palindrome(InputOpertor begin, InputOpertor end, Predicate predicate)
{
    --end;
    while(std::distance(begin, end) > 0){
        if(!predicate(*begin, *end))
            return false;
        --end;
        ++begin;
    }
    return true;
}

#endif