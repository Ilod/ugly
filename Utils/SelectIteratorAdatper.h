#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdint>

namespace ugly
{
    namespace util
    {
        template<class Itr, class UnaryFunction = decltype(*Itr())> class SelectIteratorAdapter
        {
        public:
            using Iterator = Itr;
            using iterator_category = std::input_iterator_tag;

            using value_type = decltype(std::declval<UnaryFunction>()(*(Itr())));
            using difference_type = typename Itr::difference_type;
            using pointer = std::remove_reference_t<value_type>*;
            using reference = std::remove_reference_t<value_type>&;

            explicit SelectIteratorAdapter() {}
            SelectIteratorAdapter(const Iterator& itr) : func([](const Iterator& it) { return *it }), iterator(itr) {}
            explicit SelectIteratorAdapter(const Itr& itr, const UnaryFunction& f) : func(f), iterator(itr) {}
            SelectIteratorAdapter& operator=(const Iterator& itr)
            {
                iterator = itr;
                return *this;
            }

            value_type operator*() { return func(*iterator); }
            bool operator==(const SelectIteratorAdapter& other) { return iterator == other.iterator; }
            bool operator!=(const SelectIteratorAdapter& other) { return iterator != other.iterator; }
            bool operator==(const Itr& other) { return iterator == other; }
            bool operator!=(const Itr& other) { return iterator != other; }
            SelectIteratorAdapter& operator++() { ++iterator; return *this; }
            SelectIteratorAdapter operator++(int) { SelectIteratorAdapter<Itr, UnaryFunction> adapter = *this; ++iterator; return adapter; }
        private:
            UnaryFunction func;
            Iterator iterator;
        };
    }
}