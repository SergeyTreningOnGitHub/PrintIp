/*!
    \file print_ip.h
*/
#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <type_traits>


/*!
    Структура для определения того, является ли передаваемый тип кортежем.
*/

template<class T>
struct is_one_type_tuple{
    static const bool value = false;
};

/*!
    Структура, параметризованная типом кортежа. Используется для определения того, \n
     вляются ли тип элементов кортежа одинаковым для всех элементов, а также, что этот \n
     тип - интегральный. 
*/

template<class T, class... Types>
struct is_one_type_tuple<std::tuple<T, Types...>>{
    using CurrentType = T;
    static const bool value = std::is_integral<T>::value &&
                              std::is_same<T, typename is_one_type_tuple<std::tuple<Types...>>::CurrentType>::value &&
                              is_one_type_tuple<std::tuple<Types...>>::value;
};

/*!
    Структура определяет конец рекурсивного инстанцирования
*/

template<class T>
struct is_one_type_tuple<std::tuple<T>>{
    using CurrentType = T;
    static const bool value = true;
};

/*!
    Обобщенная функция для вывода элементов кортежа в поток вывода.
*/

template<int INDEX = 0, class... Types>
void PrintIpTuple(const std::tuple<Types...>& t, std::ostream& out = std::cout){
    if constexpr(INDEX == std::tuple_size<std::tuple<Types...>>{} - 1){
        out << std::get<INDEX>(t);
    }else{
        out << std::get<INDEX>(t) << ".";
        PrintIpTuple<INDEX + 1, Types...>(t, out);    
    }        
}

/*!
    Структура для проверки того, является ли передаваемый тип списком
*/

template<class T>
struct is_integral_list{
    static const bool value = false;
};

/*!
    Структура для определения того, является ли тип элементов списка интегральным
*/

template<class T>
struct is_integral_list<std::list<T>>{
    static const bool value = std::is_integral<T>::value;
};

/*!
    Структура для проверки того, является ли передаваемый тип вектором
*/

template<class T>
struct is_integral_vector{
    static const bool value = false;
};

/*!
    Структура для определения того, является ли тип элементов вектора интегральным
*/

template<class T>
struct is_integral_vector<std::vector<T>>{
    static const bool value = std::is_integral<T>::value;
};

/*!
    Обобщенная функция печати ip адреса в поток вывода. \n
    ip адрес может принадлежать к следующим типам: \n
    любой интегральный тип (char, short, int и т.д.), \n
    vector<T>, где Т любой интегральный тип, \n
    list<T>, где T любой интегральный тип, \n
    string, \n
    tuple<Types...>, где Types... любые интегральные типы и Types...  - одинаковые типы. \n
    Если тип ip адреса не относится к вышеперечисленным, то будет вызвана ошибка компиляции. \n
*/

template<class T>
void print_ip(const T& ip_address, std::ostream& out = std::cout){
    if constexpr(std::is_integral<T>::value){
        
        for(int i = sizeof(T) - 1;i >= 0;i--){
            if(i)
                out << ((ip_address >> (i * 8)) & 0xFF) << ".";
            else
                out << (ip_address & 0xFF);
        }
    }else if constexpr(std::is_same<T, std::string>::value){
        out << ip_address;
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