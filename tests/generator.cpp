#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "rumal Unit Test (rumal::generator)"
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <rumal/rumal.h>
#include <boost/lexical_cast.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(generator)

template <typename T>
void check(T html, std::string expected){
    std::string str = boost::lexical_cast<std::string>(html);
    boost::regex regx("[\\n\\t\\s]+");
    boost::replace_all_regex(str, regx, std::string(), boost::match_flag_type::match_default);
    boost::replace_all_regex(expected, regx, std::string(), boost::match_flag_type::match_default);
    BOOST_CHECK(str == expected);
}

BOOST_AUTO_TEST_CASE(html){
    using namespace rumal::html::attrs;
    using namespace rumal::html::tags;
    
    check(span(84), "<span>84</span>");
    check(span(id(42), 84), "<span id='42'>84</span>");
    check(div(id(42) / klass("test"), 84), "<div class='test' id='42'>84</div>");
}

BOOST_AUTO_TEST_CASE(css){
    using namespace rumal::css;
    
    auto style = select(".main", prop("display", "block") / prop("position", "relative"), select(".heading", prop("display", "block") / prop("position", "relative"))) / select(".container", prop("display", "block") / prop("position", "relative"));
    check(style, ".container{position: relative; display: block;}.main{position: relative;display: block;}.main > .heading{position: relative;display: block;}");
}

BOOST_AUTO_TEST_SUITE_END()