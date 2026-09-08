#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <utility>
//#pragma once
#include <string>
#include <tuple>



namespace Impl
{
template <typename NotString> inline constexpr bool isString  = false;
template <> inline constexpr bool isString<std::string>       = true;
template <> inline constexpr bool isString<char*>             = true;
template <> inline constexpr bool isString<const char*>       = true;
template <> inline constexpr bool isString<const char* const> = true;
template <> inline constexpr bool isString<std::string_view>  = true;

template <std::size_t N> inline constexpr bool isString<char[N]> = true;
}


/*template <typename Object,
          typename = decltype(std::declval<Object>().to_string())>
std::string makeString(const Object& object)
{
    return object.to_string();
}*/

namespace Impl { bool acceptNumber(int); }

// (2)
template <typename Numeric>
auto makeString(Numeric value,
                       decltype(Impl::acceptNumber(value))* = nullptr)
{

    std::vector<unsigned int> vc;
    size_t count_byte = sizeof(Numeric);
    long long mask = 0xff;


    for(int l=0; l< count_byte;l++){

        unsigned per = (value & mask) >> (l*8);
        vc.push_back(per);
        mask = mask * 256;
    }
    std::string out_str;
    for(int l=vc.size()-1;l>=0;l--){
        out_str += std::to_string(vc.at(l));

        if(l!=0)out_str += ".";
    }

    std::cout << out_str << std::endl;
    //return out_str;
}

template <typename Iterable>
auto makeString(const Iterable& iterable)
    -> std::enable_if_t<!Impl::isString<Iterable>,
        decltype(makeString(*std::begin(iterable)))> //decltype(makeString(*std::begin(iterable)))
{
    std::string result;
    for (const auto& i : iterable)
    {
        if (!result.empty())
            result += '.';
        result += std::to_string(i);//makeString(i);
    }

    //return result;
    std::cout << result << std::endl;
}

template <typename String>
auto makeString(const String& s)
    -> std::enable_if_t<Impl::isString<String>, std::string>
{
    std::cout <<  std::string(s);
}


/*template <typename T>
void printElem(const T& x) {
    std::cout << std::to_string(x) << '.';
};

template <typename tuple, std::size_t... Is>
void printTupleManual(const tuple& tp, std::index_sequence<Is...>) {
    (printElem(std::get<Is>(tp)), ...);
}

template <typename tuple, std::size_t TupSize = std::tuple_size_v<tuple>>
void makeString(tuple tp){ //const tuple& tp) {
    printTupleManual(tp, std::make_index_sequence<TupSize>{});
}*/





int main(int argc, char** argv)
{


     //std::tuple<int> tp {123, 456, 789, 0};
    /*makeString<int8_t>(-1);
    makeString<int16_t>(0);
    makeString<int32_t>(2130706433);
    makeString<int64_t>(8875824491850138409);
    makeString("Hello, World!");*/
    //makeString(std::make_tuple(123, 456, 789, 0));//tp);


    makeString(argv[1]);




    return 0;
}
