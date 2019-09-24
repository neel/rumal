#include <iostream>

#include <string>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/format.hpp>

#define DEFINE_ATTRIBUTE(name) template <typename T> auto name(T value){return rumal::attr(#name, value);}
#define DEFINE_LABELED_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::attr(label, value);}
#define DEFINE_HTML_TAG(name)                                   \
    template <typename Args, typename... T>                     \
    auto name(Args args, T... elems){                           \
        return tag<Args, T...>(#name, args, elems...);          \
    }                                                           \
    template <typename... T>                                    \
    auto name(T... elems){                                      \
        return tag<void, T...>(#name, elems...);                \
    }

namespace rumal{

template <typename T>
struct attribute{
    typedef T value_type;
    
    std::string _key;
    value_type _value;
    
    attribute(const std::string& key, value_type value): _key(key), _value(value){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, std::string quote="\"", std::string assign="=") const{
        stream << _key << assign << quote << _value << quote;
        return stream;
    }
};

template <typename T>
attribute<T> attr(const std::string& key, T value){
    return attribute<T>(key, value);
}

template <typename U, typename V = void>
struct folded_attribute{
    typedef U head_type;
    typedef V tail_type;
    
    head_type _head;
    tail_type _tail;
    
    folded_attribute(const head_type& head, const tail_type& tail): _head(head), _tail(tail){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, std::string sep=" ", std::string quote="\"", std::string assign="=") const{
        _head.write(stream);
        stream << sep;
        _tail.write(stream);
        return stream;
    }
};

template <typename U>
struct folded_attribute<U, void>{
    typedef U head_type;
    typedef void tail_type;
    
    head_type _head;
    
    folded_attribute(const head_type& head): _head(head){}
    template <typename StreamT>
    void write(StreamT& stream, std::string sep=" ", std::string quote="\"", std::string assign="=") const{
        _head.write(stream);
    }
};

template <typename U, typename V>
auto operator/(attribute<U> left, attribute<V> right){
    return folded_attribute<attribute<V>, folded_attribute<attribute<U>, void>>(right, folded_attribute<attribute<U>, void>(left));
}

template <typename H, typename T, typename V>
auto operator/(folded_attribute<H, T> left, attribute<V> right){
    return folded_attribute<attribute<V>, folded_attribute<H, T>>(right, left);
}

struct keyed_attr{
    std::string _key;
    keyed_attr(const std::string& key): _key(key){}
    
    template <typename T>
    attribute<T> operator()(T value) const{
        return attr(_key, value);
    }
};

namespace attrs{
    DEFINE_ATTRIBUTE(id)
    DEFINE_LABELED_ATTRIBUTE(klass, "class")
    DEFINE_ATTRIBUTE(width)
    DEFINE_ATTRIBUTE(height)
    DEFINE_ATTRIBUTE(src)
    DEFINE_ATTRIBUTE(type)
    DEFINE_ATTRIBUTE(style)
}
namespace html{
    
namespace helper{

template <typename StreamT, typename ElemT>
struct writer{
    static StreamT& write(StreamT& stream, const ElemT& elem){
        stream << elem;
        return stream;
    }
};

template <typename StreamT, typename U>
StreamT& write(StreamT& stream, const U& elem){
    writer<StreamT, U>::write(stream, elem);
    return stream;
}
   
}
    
template <typename ArgsT, typename... T> 
struct html_tag{
    std::string _name;
    ArgsT _args;
    boost::hana::tuple<T...> _tuple;

    html_tag(const std::string& name, ArgsT args, T... children): _name(name), _args(args), _tuple(children...){}
    template <typename StreamT>
    void write(StreamT& stream) const{
        stream << boost::format("<%1% %2%>") % _name % _args;
        boost::hana::for_each(_tuple, [&](const auto& elem) {
            // elem.write(stream);
            helper::write(stream, elem);
        });
        stream << boost::format("</%1%>") % _name;
    }
};

template <typename... T>
struct html_tag<void, T...>{
    std::string _name;
    boost::hana::tuple<T...> _tuple;
    
    html_tag(const std::string& name, T... children): _name(name), _tuple(children...){}
    template <typename StreamT>
    void write(StreamT& stream) const{
        stream << boost::format("<%1%>") % _name;
        boost::hana::for_each(_tuple, [&](const auto& elem) {
            // elem.write(stream);
            helper::write(stream, elem);
        });
        stream << boost::format("</%1%>") % _name;
    }
};

namespace helper{

template <typename StreamT, typename... T>
struct writer<StreamT, html_tag<T...>>{
    static StreamT& write(StreamT& stream, const html_tag<T...>& elem){
        elem.write(stream);
        return stream;
    }
};

}

template <typename Args, typename... T>
auto tag(const std::string& name, Args args, T... elems){
    return html_tag<Args, T...>(name, args, elems...);
}

template <typename... T>
auto tag(const std::string& name, T... elems){
    return html_tag<void, T...>(name, elems...);
}

namespace tags{
    DEFINE_HTML_TAG(div)
    DEFINE_HTML_TAG(span)
}

}

template <typename... T>
std::ostream& operator<<(std::ostream& stream, const html::html_tag<T...>& elem){
    elem.write(stream);
    return stream;
}

template <typename H, typename T>
std::ostream& operator<<(std::ostream& stream, const rumal::folded_attribute<H, T>& attributes){
    attributes.write(stream);
    return stream;
}

}

int main(int argc, char **argv){
    using namespace rumal::attrs;
    using namespace rumal::html::tags;
    
    auto content = div(id(42) / klass("test"), 
                        span(id(42) / width(42.042) / height(42.042) / klass("test"),
                            42
                        )
                    );
    std::cout << content << std::endl;
    
    
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
