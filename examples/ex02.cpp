#include <iostream>
#include <rumal/rumal.hpp>
#include <boost/lexical_cast.hpp>

struct fn_: rumal::js::callable_<fn_>{
    fn_(): rumal::js::callable_<fn_>("fn"){}
};

struct m1_: rumal::js::callable_<m1_>{
    m1_(): rumal::js::callable_<m1_>("m1"){}
};

struct m2_: rumal::js::callable_<m2_>{
    m2_(): rumal::js::callable_<m2_>("m2"){}
};

struct m4_: rumal::js::callable_<m4_>{
    m4_(): rumal::js::callable_<m4_>("m4"){}
};

struct m5_: rumal::js::callable_<m5_>{
    m5_(): rumal::js::callable_<m5_>("m5"){}
};

template <typename T>
struct object4_{
    rumal::js::method_<m5_, T> m5;
    
    object4_(const T& pkt): m5(pkt){}
};

template <typename T>
struct object3_{
    rumal::js::method_<m5_, T> m5;
    rumal::js::property_<object4_, T> o4;
    
    object3_(const T& pkt): m5(pkt), o4("o4", pkt){}
};

template <typename T>
struct object2_: rumal::js::iterable_<T, object3_>{
    rumal::js::method_<m4_, T> m4;
    
    object2_(const T& pkt): rumal::js::iterable_<T, object3_>(pkt), m4(pkt){}
};

struct m3_: rumal::js::callable_<m3_, object2_>{
    m3_(): rumal::js::callable_<m3_, object2_>("m3"){}
};

template <typename T>
struct object1_{
    rumal::js::method_<m1_, T> m1;
    rumal::js::method_<m2_, T> m2;
    rumal::js::method_<m3_, T> m3;
    
    object1_(const T& pkt): m1(pkt), m2(pkt), m3(pkt){}
};

struct m0_: rumal::js::callable_<m0_, object1_>{
    m0_(): rumal::js::callable_<m0_, object1_>("m0"){}
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv){
    fn_ fn;
    std::cout << fn(1, 2.5) << std::endl;
    
    m0_ m0;
    std::cout << m0(1, 4.5) << std::endl;
    std::cout << m0(1, 4.5).m1(4, 2.7) << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7) << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7).m4(4, 75.5) << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7, "hi")[1].m5("Hallo") << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7, "hi")[1].o4 << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7, "hi")[1].o4.m5 << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7, "hi")[1].o4.m5(42) << std::endl;
    std::cout << m0(1, 4.5).m3(4, 2.7, "hi")[1].o4.m5() << std::endl;
    
    return 0;
}
