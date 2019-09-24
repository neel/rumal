#include <iostream>

#include <string>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/format.hpp>

#define DEFINE_HTML_ATTRIBUTE(name) template <typename T> auto name(T value){return rumal::html::attr(#name, value);}
#define DEFINE_LABELED_HTML_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::html::attr(label, value);}
#define DEFINE_CSS_ATTRIBUTE(name) template <typename T> auto name(T value){return rumal::css::attr(#name, value);}
#define DEFINE_LABELED_CSS_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::css::attr(label, value);}
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
   
template <typename P, typename T>
struct attribute{
    typedef T value_type;
   
    std::string _key;
    value_type _value;
   
    attribute(const std::string& key, value_type value): _key(key), _value(value){}
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        P::write(stream, _key, _value);
        return stream;
    }
};

template <typename U, typename V = void>
struct folded_attribute{
    typedef U head_type;
    typedef V tail_type;
   
    head_type _head;
    tail_type _tail;
   
    folded_attribute(const head_type& head, const tail_type& tail): _head(head), _tail(tail){}
};

template <typename U>
struct folded_attribute<U, void>{
    typedef U head_type;
    typedef void tail_type;
   
    head_type _head;
   
    folded_attribute(const head_type& head): _head(head){}
};

template <typename P, typename F>
struct folded_attribute_writer{
    template <typename StreamT>
    static StreamT& write(StreamT& stream, const F& folded_attribute){
        folded_attribute._head.write(stream);
        stream << P::end() << P::sep();
        folded_attribute_writer<P, typename F::tail_type>::write(stream, folded_attribute._tail);
        return stream;
    }
};

template <typename P, typename U>
struct folded_attribute_writer<P, folded_attribute<U, void>>{
    template <typename StreamT>
    static StreamT& write(StreamT& stream, const folded_attribute<U, void>& folded_attribute){
        folded_attribute._head.write(stream);
        stream << P::end();
        return stream;
    }
};


template <typename P, typename U, typename V>
auto operator/(attribute<P, U> left, attribute<P, V> right){
    return folded_attribute<attribute<P, V>, folded_attribute<attribute<P, U>, void>>(right, folded_attribute<attribute<P, U>, void>(left));
}

template <typename P, typename H, typename T, typename V>
auto operator/(folded_attribute<H, T> left, attribute<P, V> right){
    return folded_attribute<attribute<P, V>, folded_attribute<H, T>>(right, left);
}

namespace html{
   
struct html_attribute_trait{
    template <typename StreamT, typename T>
    static StreamT& write(StreamT& stream, const std::string& key, T value){
        stream << boost::format("%1%=%2%") % key % value;
        return stream;
    }
    static auto sep(){
        return " ";
    }
};

   
template <typename T>
attribute<html_attribute_trait, T> attr(const std::string& key, T value){
    return attribute<html_attribute_trait, T>(key, value);
}

struct keyed_attr{
    std::string _key;
    keyed_attr(const std::string& key): _key(key){}
   
    template <typename T>
    attribute<html_attribute_trait, T> operator()(T value) const{
        return attr(_key, value);
    }
};

namespace attrs{
    DEFINE_HTML_ATTRIBUTE(id)
    DEFINE_LABELED_HTML_ATTRIBUTE(klass, "class")
    DEFINE_HTML_ATTRIBUTE(width)
    DEFINE_HTML_ATTRIBUTE(height)
    DEFINE_HTML_ATTRIBUTE(src)
    DEFINE_HTML_ATTRIBUTE(type)
    DEFINE_HTML_ATTRIBUTE(style)
}
   
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

struct html_tag_trait{
    static auto end(){
        return "";
    }
    static auto sep(){
        return " ";
    }
};
   
template <typename... T>
struct stripped_parameters{
    typedef void arguments_type;
    typedef boost::hana::tuple<T...> children_type;
    
    children_type _children;
    
    stripped_parameters(T... children): _children(children...){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, const std::string& name) const{
        stream << "<" << name << ">";
        boost::hana::for_each(_children, [&](const auto& elem) {
            helper::write(stream, elem);
        });
        stream << "</" << name << ">";
        return stream;
    }
};

template <typename U, typename V, typename... T>
struct stripped_parameters<folded_attribute<U, V>, T...>{
    typedef folded_attribute<U, V>   arguments_type;
    typedef boost::hana::tuple<T...> children_type;
    
    arguments_type _arguments;
    children_type  _children;
    
    stripped_parameters(arguments_type args, T... children): _arguments(args), _children(children...){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, const std::string& name) const{
        stream << "<" << name << " ";
        folded_attribute_writer<html_tag_trait, arguments_type>::write(stream, _arguments);
        stream << ">";
        boost::hana::for_each(_children, [&](const auto& elem) {
            helper::write(stream, elem);
        });
        stream << "</" << name << ">";
        return stream;
    }
};

template <typename P, typename U, typename... T>
struct stripped_parameters<attribute<P, U>, T...>: stripped_parameters<folded_attribute<attribute<P, U>, void>, T...>{
    typedef stripped_parameters<folded_attribute<attribute<P, U>, void>, T...> base_type;

    stripped_parameters(attribute<P, U> arg, T... children): base_type(typename base_type::arguments_type(arg), children...){}
};

template <typename... T>
struct html_tag: stripped_parameters<T...>{
    typedef stripped_parameters<T...> base_type;
    
    std::string _name;

    html_tag(const std::string& name, T... params): _name(name), base_type(params...){}
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        base_type::write(stream, _name);
        return stream;
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

template <typename U, typename V, typename... T>
auto tag(const std::string& name, folded_attribute<U, V> args, T... elems){
    return html_tag<folded_attribute<U, V>, T...>(name, args, elems...);
}

template <typename... T>
auto tag(const std::string& name, T... elems){
    return html_tag<T...>(name, elems...);
}

namespace tags{
    DEFINE_HTML_TAG(div)
    DEFINE_HTML_TAG(span)
    DEFINE_HTML_TAG(img)
    DEFINE_HTML_TAG(script)
    DEFINE_HTML_TAG(link)
}

template <typename... T>
std::ostream& operator<<(std::ostream& stream, const html::html_tag<T...>& elem){
    elem.write(stream);
    return stream;
}

}

namespace css{
    
struct css_attribute_trait{
    template <typename StreamT, typename T>
    static StreamT& write(StreamT& stream, const std::string& key, T value){
        stream << boost::format("%1%: %2%") % key % value;
        return stream;
    }
    static auto sep(){
        return " ";
    }
};

struct css_tag_trait{
    static auto end(){
        return ";";
    }
    static auto sep(){
        return "\n\t";
    }
};

template <typename T>
attribute<css_attribute_trait, T> attr(const std::string& key, T value){
    return attribute<css_attribute_trait, T>(key, value);
}

namespace attrs{
    DEFINE_CSS_ATTRIBUTE(position)
    DEFINE_CSS_ATTRIBUTE(display)
}
    
template <typename... T>
struct css_selector: html::html_tag<T...>{
    typedef html::html_tag<T...> base_type;
    
    css_selector(const std::string& name, T... args): base_type(name, args...){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << base_type::_name << "{" << std::endl << "\t";
        folded_attribute_writer<css_tag_trait, typename base_type::arguments_type>::write(stream, base_type::_arguments);
        boost::hana::for_each(base_type::_children, [&](const auto& elem) {
            html::helper::write(stream, elem);
        });
        stream << std::endl << "}" << std::endl;
        return stream;
    }
};

template <typename U, typename V, typename... T>
auto select(const std::string& name, folded_attribute<U, V> args, T... elems){
    return css_selector<folded_attribute<U, V>, T...>(name, args, elems...);
}

template <typename... T>
std::ostream& operator<<(std::ostream& stream, const css_selector<T...>& elem){
    elem.write(stream);
    return stream;
}
    
}

}

int main(int argc, char **argv){
    using namespace rumal::html::attrs;
    using namespace rumal::html::tags;
    using namespace rumal::css::attrs;
   
    auto content = div(id(42) / klass("test"),
                        span(id(42) / width(42.042) / height(42.042) / klass("test"),
                            42
                        ),
                        span(
                            84
                        )
                    );
    std::cout << content << std::endl;
   
    std::cout << span(84) << std::endl;
    std::cout << span(id(42), 84) << std::endl;
    std::cout << span(id(42) / klass("test"), 84) << std::endl;
    std::cout << span(id(42) / width(42.042) / height(42.042) / klass("test"), 84) << std::endl;
    
    std::cout << rumal::css::select(".heading", position("relative") / display("block"), rumal::css::select(".content", position("relative") / display("block")));
   
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
