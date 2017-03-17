#pragma once
#include "SelectIteratorAdatper.h"

namespace ugly
{
    namespace util
    {
        template<class Itr, class UnaryFunction> SelectIteratorAdapter<Itr, UnaryFunction> CreateSelectIteratorAdapter(const Itr& itr, const UnaryFunction& func)
        {
            return SelectIteratorAdapter<Itr, UnaryFunction>(itr, func);
        }
        template<class Itr> SelectIteratorAdapter<Itr> CreateDummySelectIteratorAdapter(const Itr& itr)
        {
            return SelectIteratorAdapter<Itr>(itr);
        }
        template<class Adapter> Adapter CopyWithIterator(const Adapter& adapter, const typename Adapter::Iterator& iterator)
        {
            Adapter other = adapter;
            other = iterator;
            return other;
        }
    }
}