#include <iostream>

#include <string>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/format.hpp>

template <typename T>
struct attribute{
    typedef T value_type;
    
    std::string _key;
    value_type _value;
};

/**
 * folded_attribute<Attr1, folded_attribute<Attr2, folded_attribute<Attr3, void>>>
 */
template <typename U, typename V = void>
struct folded_attribute{
    typedef U head_type;
    typedef V tail_type;
    
    head_type _head;
    tail_type _tail;
};



template <typename ArgsT, typename... T> 
struct tag{
    std::string      _name;
    ArgsT            _args;
    boost::hana::tuple<T...> _tuple;

    tag(const std::string& name, ArgsT args, T... children): _name(name), _args(args), _tuple(children...){}
    template <typename StreamT>
    void write(StreamT& stream) const{
        stream << boost::format("<%1%>") % _name;
        boost::hana::for_each(_tuple, [&](const auto& elem) {
            elem.write(stream);
        });
        stream << boost::format("</%1%>") % _name;
    }
};

template <typename... T>
std::ostream& operator<<(std::ostream& stream, const tag<T...>& elem){
    elem.write(stream);
    return stream;
}

template <typename... T>
auto html(const std::string& name, T... elems){
    return tag<T...>(name, elems...);
}

/**
 * 
 * html("div",
 *      html("h1") << a("id", "head") << a("class", "heading"),
 *      html("div") << a("id", "central") << a("class", "central")
 * ) << a("id", 42) << a("class", "content")
 * 
 * html("div", (attr("id", 42), attr("class", "content"))
 *      html("h1", (attr("id", "head"), attr("class", "heading"))),
 *      html("div", (attr("id", "central"), attr("class", "central")))
 * )
 * 
 */

int main(int argc, char **argv) {
    auto content = html("div", html("span"));
    std::cout << content << std::endl;
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
