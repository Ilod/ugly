#pragma once

namespace ugly
{
    namespace FreeMarket
    {
        template<typename T> struct IsFlagEnum : std::false_type {};
    
        template<typename T> struct EnumBoolAutoCast
        {
        public:
            explicit EnumBoolAutoCast(T val) : value(val) {}
            operator T() { return value; }
            explicit operator bool() { return static_cast<typename std::underlying_type<T>::type>(value) != 0; };
            bool operator!() { return !value; }
            EnumBoolAutoCast<T> operator&(T val) { return value & val; }
            EnumBoolAutoCast<T> operator|(T val) { return value | val; }
            EnumBoolAutoCast<T> operator^(T val) { return value ^ val; }
            EnumBoolAutoCast<T> operator~() { return ~value; }
        private:
            T value;
        };
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, EnumBoolAutoCast<T>>::type operator&(T val, T oVal)
        {
            return EnumBoolAutoCast<T>(static_cast<T>(static_cast<typename std::underlying_type<T>::type>(val) & static_cast<typename std::underlying_type<T>::type>(oVal)));
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, EnumBoolAutoCast<T>>::type operator|(T val, T oVal)
        {
            return EnumBoolAutoCast<T>(static_cast<T>(static_cast<typename std::underlying_type<T>::type>(val) | static_cast<typename std::underlying_type<T>::type>(oVal)));
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, EnumBoolAutoCast<T>>::type operator^(T val, T oVal)
        {
            return EnumBoolAutoCast<T>(static_cast<T>(static_cast<typename std::underlying_type<T>::type>(val) ^ static_cast<typename std::underlying_type<T>::type>(oVal)));
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, EnumBoolAutoCast<T>>::type operator~(T val)
        {
            return EnumBoolAutoCast<T>(static_cast<T>(~static_cast<typename std::underlying_type<T>::type>(val)));
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, bool>::type operator!(T val)
        {
            return static_cast<typename std::underlying_type<T>::type>(val) != 0;
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, T&>::type operator&=(T& val, T oVal)
        {
            val = static_cast<T>(static_cast<typename std::underlying_type<T>::type>(val) & static_cast<typename std::underlying_type<T>::type>(oVal));
            return val;
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, T&>::type operator|=(T& val, T oVal)
        {
            val = static_cast<T>(static_cast<typename std::underlying_type<T>::type>(val) | static_cast<typename std::underlying_type<T>::type>(oVal));
            return val;
        }
        
        template<typename T> typename std::enable_if<IsFlagEnum<T>::value, T&>::type operator^=(T& val, T oVal)
        {
            val = static_cast<T>(static_cast<typename std::underlying_type<T>::type>(val) ^ static_cast<typename std::underlying_type<T>::type>(oVal));
            return val;
        }
    }
}
