/*
 * Copyright (c) 2018, Sunanda Bose (Neel Basu) (neel.basu.z@gmail.com) 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#ifndef RUMAL_H
#define RUMAL_H

#include <string>
#include <boost/format.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/algorithm/string/join.hpp>

#define DEFINE_HTML_ATTRIBUTE(name) template <typename T> auto name(T value){return rumal::html::attr(#name, value);}
#define DEFINE_LABELED_HTML_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::html::attr(label, value);}
#define DEFINE_HTML_TAG(name)                                   \
    template <typename Args, typename... T>                     \
    auto name(Args args, const T&... elems){                    \
        return tag<Args, T...>(#name, args, elems...);          \
    }                                                           \
    template <typename... T>                                    \
    auto name(const T&... elems){                               \
        return tag<void, T...>(#name, elems...);                \
    }

namespace rumal{
   
/**
 * @brief generic key value pair
 * @details
 * Usage: Generic key value pairs used for html attributes as well as for CSS properties, <tt>key</tt> is always `std::string`
 * @tparam P presentation trait
 * @tparam T type of the value
 */
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

/**
 * @brief chain of multiple atributes
 * @details
 * Usage: used for HTML tag attributes as well as for CSS properties
 * @note read in the reverse order
 * @tparam U head type
 * @tparam V tail type 
 */
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

/**
 * @brief writes folded attribute to a stream
 * @see folded_attribute
 * @tparam P presentation trait
 * @tparam F folded attribute
 */
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

/**
 * @brief concatenate two attributes 
 * @param left lhs attribute
 * @param right rhs attribute
 * @return folded_attribute
 */
template <typename P, typename U, typename V>
auto operator/(const attribute<P, U>& left, const attribute<P, V>& right){
    return folded_attribute<attribute<P, V>, folded_attribute<attribute<P, U>, void>>(right, folded_attribute<attribute<P, U>, void>(left));
}

/**
 * @brief concatenate a folded attribute with an attributes
 * @param left lhs folded_attribute
 * @param right rhs attribute
 * @return folded_attribute
 */
template <typename P, typename H, typename T, typename V>
auto operator/(const folded_attribute<H, T>& left, const attribute<P, V>& right){
    return folded_attribute<attribute<P, V>, folded_attribute<H, T>>(right, left);
}

namespace html{
   
/**
 * @brief html attribute printing trait
 */
struct html_attribute_trait{
    template <typename StreamT, typename T>
    static StreamT& write(StreamT& stream, const std::string& key, T value){
        stream << boost::format("%1%='%2%'") % key % value;
        return stream;
    }
    static auto sep(){
        return " ";
    }
};

/**
 * @brief generate an attribute from key and value
 * @tparam T value type
 */   
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
    static StreamT& write(StreamT& stream, const ElemT& elem, int indent = 0){
        for(int i = 0; i < indent; ++i){
            stream << "\t";
        }
        stream << elem << std::endl;
        return stream;
    }
};

template <typename StreamT, typename U>
StreamT& write(StreamT& stream, const U& elem, int indent = 0){
    writer<StreamT, U>::write(stream, elem, indent);
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
    StreamT& write(StreamT& stream, const std::string& name, int indent = 0) const{
        for(int i = 0; i < indent; ++i){
            stream << "\t";
        }
        stream << "<" << name << ">" << std::endl;
        boost::hana::for_each(_children, [&](const auto& elem) {
            helper::write(stream, elem, indent+1);
        });
        for(int i = 0; i < indent; ++i){
            stream << "\t";
        }
        stream << "</" << name << ">" << std::endl;
        return stream;
    }
};

template <typename U, typename V, typename... T>
struct stripped_parameters<folded_attribute<U, V>, T...>{
    typedef folded_attribute<U, V>   arguments_type;
    typedef boost::hana::tuple<T...> children_type;
    
    arguments_type _arguments;
    children_type  _children;
    
    stripped_parameters(const arguments_type& args, T... children): _arguments(args), _children(children...){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, const std::string& name, int indent = 0) const{
        for(int i = 0; i < indent; ++i){
            stream << "\t";
        }
        stream << "<" << name << " ";
        folded_attribute_writer<html_tag_trait, arguments_type>::write(stream, _arguments);
        stream << ">"  << std::endl;
        boost::hana::for_each(_children, [&](const auto& elem) {
            helper::write(stream, elem, indent+1);
        });
        for(int i = 0; i < indent; ++i){
            stream << "\t";
        }
        stream << "</" << name << ">" << std::endl;
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

    html_tag(const std::string& name, const T&... params): _name(name), base_type(params...){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, int indent = 0) const{
        base_type::write(stream, _name, indent);
        return stream;
    }
};

namespace helper{

template <typename StreamT, typename... T>
struct writer<StreamT, html_tag<T...>>{
    static StreamT& write(StreamT& stream, const html_tag<T...>& elem, int indent = 0){
        elem.write(stream, indent);
        return stream;
    }
};

}

template <typename U, typename V, typename... T>
auto tag(const std::string& name, const folded_attribute<U, V>& args, T... elems){
    return html_tag<folded_attribute<U, V>, T...>(name, args, elems...);
}

template <typename... T>
auto tag(const std::string& name, const T&... elems){
    return html_tag<T...>(name, elems...);
}

namespace tags{
    DEFINE_HTML_TAG(div)
    DEFINE_HTML_TAG(h1)
    DEFINE_HTML_TAG(h2)
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
attribute<css_attribute_trait, T> prop(const std::string& key, T value){
    return attribute<css_attribute_trait, T>(key, value);
}

// { folder tag writer

template <typename U, typename V = void>
struct folded_tag{
    typedef U head_type;
    typedef V tail_type;

    head_type _head;
    tail_type _tail;

    folded_tag(const head_type& head, const tail_type& tail): _head(head), _tail(tail){}
    std::ostream& write(std::ostream& stream) const {
        stream << _head;
        stream << _tail;
        return stream;
    }
};

template <typename U>
struct folded_tag<U, void>{
    typedef U head_type;
    typedef void tail_type;

    head_type _head;

    folded_tag(const head_type& head): _head(head){}
    std::ostream& write(std::ostream& stream) const {
        stream << _head;
        return stream;
    }
};
//
template <typename U, typename V>
std::ostream& operator<<(std::ostream& stream, const folded_tag<U, V>& tag){
    tag.write(stream);
    return stream;
}

// }

template <typename... T>
struct css_selector: html::html_tag<T...>{
    typedef html::html_tag<T...> base_type;
    
    css_selector(const std::string& name, const T&... args): base_type(name, args...){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream, std::vector<std::string>& ancestors) const{
        ancestors.push_back(base_type::_name);
        stream << boost::algorithm::join(ancestors, " > ") << "{" << std::endl << "\t";
        folded_attribute_writer<css_tag_trait, typename base_type::arguments_type>::write(stream, base_type::_arguments);
        stream << std::endl << "}" << std::endl;
        boost::hana::for_each(base_type::_children, [&](const auto& elem) {
            elem.write(stream, ancestors);
        });
        ancestors.pop_back();
        return stream;
    }
    template <typename... V>
    auto operator/(const css_selector<V...>& other){
        typedef css_selector<V...> other_type;
        typedef folded_tag<css_selector<T...>, void> self_type;
        return folded_tag<other_type, self_type>(other, self_type(*this));
    }
};

template <typename U, typename V, typename... T>
auto operator/(const folded_tag<U, V>& left, const css_selector<T...>& right){
    typedef css_selector<T...> right_type;
    typedef folded_tag<U, V> left_type;
    return folded_tag<right_type, left_type>(right, left_type(left));
}

template <typename U, typename V, typename... T>
auto select(const std::string& name, const folded_attribute<U, V>& args, const T&... elems){
    return css_selector<folded_attribute<U, V>, T...>(name, args, elems...);
}

template <typename... T>
std::ostream& operator<<(std::ostream& stream, const css_selector<T...>& elem){
    std::vector<std::string> ancestors;
    elem.write(stream, ancestors);
    return stream;
}
    
}

}

#endif // RUMAL_H
