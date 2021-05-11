#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

template<class T>
struct is_one_type_tuple{
    static const bool value = false;
};

template<class T, class... Types>
struct is_one_type_tuple<std::tuple<T, Types...>>{
    using CurrentType = T;
    static const bool value = std::is_integral<T>::value &&
                              std::is_same<T, typename is_one_type_tuple<std::tuple<Types...>>::CurrentType>::value &&
                              is_one_type_tuple<std::tuple<Types...>>::value;
};

template<class T>
struct is_one_type_tuple<std::tuple<T>>{
    using CurrentType = T;
    static const bool value = true;
};

template<int INDEX = 0, class... Types>
void PrintIpTuple(const std::tuple<Types...>& t, std::ostream& out = std::cout){
    if constexpr(INDEX == std::tuple_size<std::tuple<Types...>>{} - 1){
        out << std::get<INDEX>(t);
    }else{
        out << std::get<INDEX>(t) << ".";
        PrintIpTuple<INDEX + 1, Types...>(t, out);    
    }        
}

template<class T>
void PrintIpTuple(const std::tuple<T>& t, std::ostream& out = std::cout){
    out << std::get<0>(t);
}

template<class T>
struct is_integral_list{
    static const bool value = false;
};

template<class T>
struct is_integral_list<std::list<T>>{
    static const bool value = std::is_integral<T>::value;
};

template<class T>
struct is_integral_vector{
    static const bool value = false;
};

template<class T>
struct is_integral_vector<std::vector<T>>{
    static const bool value = std::is_integral<T>::value;
};

template<class T>
void print_ip(const T& ip_address, std::ostream& out = std::cout){
    if constexpr(std::is_integral<T>::value){
        
        for(int i = sizeof(T) - 1;i >= 0;i--){
            if(i)
                out << ((ip_address >> (i * 8)) & 0xFF) << ".";
            else
                out << (ip_address & 0xFF);
        }
    }else if constexpr(is_integral_vector<T>::value || is_integral_list<T>::value){        
        for(auto it = ip_address.begin();it != ip_address.end();it++){
            if(it == std::prev(ip_address.end())){
                out << (*it);
            }else{
                out << (*it) << ".";
            }
        }        
    }else if constexpr(is_one_type_tuple<T>::value){
        PrintIpTuple(ip_address, out);
    }else{        
        static_assert(std::is_integral<T>::value, "Ivalid types");
    }
}