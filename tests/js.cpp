#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "rumal Unit Test (rumal::js)"
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <rumal/rumal.hpp>
#include <rumal/js.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

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

BOOST_AUTO_TEST_SUITE(js)

template <typename T>
void check(T js, std::string expected){
    std::string str = boost::lexical_cast<std::string>(js);
    boost::regex regx("[\\n\\t\\s]+");
    boost::replace_all_regex(str, regx, std::string(), boost::match_flag_type::match_default);
    boost::replace_all_regex(expected, regx, std::string(), boost::match_flag_type::match_default);
    BOOST_CHECK_MESSAGE(str == expected, str << " not " << expected);
}

BOOST_AUTO_TEST_CASE(chain){
    fn_ fn;
    m0_ m0;
    
    check(m0(1, 4.5), "m0(1, 4.5)");
    check(m0(1, 4.5).m1(4, 2.7), "m0(1, 4.5).m1(4, 2.7)");
    check(m0(1, 4.5).m3(4, 2.7), "m0(1, 4.5).m3(4, 2.7)");
    check(m0(1, 4.5).m3(4, 2.7).m4(4, 75.5), "m0(1, 4.5).m3(4, 2.7).m4(4, 75.5)");
    check(m0(1, 4.5).m3(4, 2.7, "hi")[1].m5("Hallo"), "m0(1, 4.5).m3(4, 2.7, 'hi')[1].m5('Hallo')");
    check(m0(1, 4.5).m3(4, 2.7, "hi")[1].o4, "m0(1, 4.5).m3(4, 2.7, 'hi')[1].o4");
    check(m0(1, 4.5).m3(4, 2.7, "hi")[1].o4.m5, "m0(1, 4.5).m3(4, 2.7, 'hi')[1].o4.m5");
    check(m0(1, 4.5).m3(4, 2.7, "hi")[1].o4.m5(42), "m0(1, 4.5).m3(4, 2.7, 'hi')[1].o4.m5(42)");
    check(m0(1, 4.5).m3(4, 2.7, "hi")[1].o4.m5(), "m0(1, 4.5).m3(4, 2.7, 'hi')[1].o4.m5()");
}

BOOST_AUTO_TEST_SUITE_END()
