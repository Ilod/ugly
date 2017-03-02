#pragma once
#include <type_traits>
#include <memory>
#include "LibraryHandler.h"

namespace ugly
{
    namespace loader
    {
        template<typename T> class unique_ptr;
        template<typename T> class shared_ptr;
        template<typename T, typename... Args> unique_ptr<T> make_unique(const std::shared_ptr<LibraryHandler>& library, Args&&... args);
        template<typename T, typename... Args> shared_ptr<T> make_shared(const std::shared_ptr<LibraryHandler>& library, Args&&... args);

        template<typename T> class unique_ptr
        {
        public:
            unique_ptr()
                : object(nullptr)
                , deleter(nullptr)
            {}
            unique_ptr(std::nullptr_t)
                : object(nullptr)
                , deleter(nullptr)
            {}
            unique_ptr(const unique_ptr<T>&) = delete;
            unique_ptr(unique_ptr<T>&& other)
                : object(other.object)
                , deleter(other.deleter)
                , library(std::move(other.library))
            {
                other.object = nullptr;
                other.deleter = nullptr;
            }

            template<class V, typename = typename std::enable_if<std::is_base_of<T, V>::value>::type> unique_ptr(unique_ptr<V>&& other)
                : object(other.object)
                , deleter(other.deleter)
                , library(std::move(other.library))
            {
                other.object = nullptr;
                other.deleter = nullptr;
            }

            unique_ptr& operator=(const unique_ptr<T>&) = delete;
            unique_ptr& operator=(unique_ptr<T>&& other)
            {
                reset();
                object = other.object;
                other.object = nullptr;
                deleter = other.deleter;
                other.deleter = nullptr;
                library = std::move(other.library);
                return *this;
            }
            template<class V, typename = typename std::enable_if<std::is_base_of<T, V>::value>::type> unique_ptr&& operator=(unique_ptr<V>&& other)
            {
                reset();
                object = other.object;
                other.object = nullptr;
                deleter = other.deleter;
                other.deleter = nullptr;
                library = std::move(other.library);
            }

            void reset()
            {
                if (object)
                {
                    (*deleter)(object);
                    object = nullptr;
                    deleter = nullptr;
                }
                library.reset();
            }

            ~unique_ptr()
            {
                reset();
            }

            operator bool() const
            {
                return !!object;
            }

            T* operator->()
            {
                return object;
            }

            const T* operator->() const
            {
                return object;
            }

            T& operator*()
            {
                return *object;
            }

            const T& operator*() const
            {
                return *object;
            }
        private:
            unique_ptr(T* obj, void(*del)(void*), const std::shared_ptr<LibraryHandler>& lib)
                : object(obj)
                , deleter(del)
                , library(lib)
            { }

            T* object;
            void(*deleter)(void*);
            std::shared_ptr<LibraryHandler> library;

            template<typename... Args> static T* Create(Args&&... args)
            {
                return new T(std::forward<Args>(args)...);
            }

            static void Delete(void* obj)
            {
                delete (T*)obj;
            }

            template<typename R> friend class unique_ptr;
            template<typename R, typename... Args> friend unique_ptr<R> make_unique(const std::shared_ptr<LibraryHandler>& library, Args&&... args);
            template<typename R, typename... Args> friend shared_ptr<R> make_shared(const std::shared_ptr<LibraryHandler>& library, Args&&... args);
            friend class shared_ptr<T>;
        };

        template<typename T> class shared_ptr
        {
        public:
            shared_ptr() {}
            shared_ptr(const shared_ptr<T>&) = delete;
            shared_ptr(shared_ptr<T>&&) = default;
            template<class V, typename = typename std::enable_if<std::is_base_of<T, V>::value>::type> shared_ptr(shared_ptr<V>&& other)
                : ptr(std::move(other.ptr))
                , library(std::move(other.library))
            {
            }
            shared_ptr(unique_ptr<T>&& other)
                : ptr(other.object, other.deleter)
                , library(std::move(other.library))
            {
                other.reset();
            }

            shared_ptr& operator=(const shared_ptr<T>&) = delete;
            shared_ptr& operator=(shared_ptr<T>&&) = default;
            template<class V, typename = typename std::enable_if<std::is_base_of<T, V>::value>::type> shared_ptr& operator=(shared_ptr<V>&& other)
            {
                ptr = std::move(other.ptr);
                library = std::move(other.library);
            }
            shared_ptr&& operator=(unique_ptr<T>&& other)
            {
                reset();
                ptr = std::shared_ptr<T>(other.ptr, other.deleter);
                library = std::move(other.library);
                other.reset();
            }

            void reset()
            {
                ptr.reset();
                library.reset();
            }

            ~shared_ptr()
            {
                reset();
            }

            operator bool() const
            {
                return ptr;
            }

            T* operator->()
            {
                return ptr;
            }

            const T* operator->() const
            {
                return ptr;
            }

            T& operator*()
            {
                return *ptr;
            }

            const T& operator*() const
            {
                return *ptr;
            }
        private:
            std::shared_ptr<T> ptr;
            std::shared_ptr<LibraryHandler> library;
            template<typename R> friend class shared_ptr;
        };

        template<typename T, typename... Args> unique_ptr<T> make_unique(const std::shared_ptr<LibraryHandler>& library, Args&&... args)
        {
            return unique_ptr<T>(unique_ptr<T>::Create(std::forward<Args>(args)...), &unique_ptr<T>::Delete, library);
        }

        template<typename T, typename... Args> shared_ptr<T> make_shared(const std::shared_ptr<LibraryHandler>& library, Args&&... args)
        {
            return shared_ptr<T>(make_unique<T>(library, std::forward<Args>(args)...));
        }
    }
}