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

#ifndef RUMAL_JS_H
#define RUMAL_JS_H

#include <type_traits>
#include <boost/hana/tuple.hpp>

typedef std::string string_type;

#define RUMAL_JS_INDENTATION_TAB    "\t"
#define RUMAL_JS_PARENTHESIS_OPEN   "("
#define RUMAL_JS_PARENTHESIS_CLOSE  ")"
#define RUMAL_JS_CURLYBRACE_OPEN    "{"
#define RUMAL_JS_CURLYBRACE_CLOSE   "}"
#define RUMAL_JS_SQUAREBRACE_OPEN   "["
#define RUMAL_JS_SQUAREBRACE_CLOSE  "]"
#define RUMAL_JS_QUOTE_SINGLE       "'"
#define RUMAL_JS_QUOTE_DOUBLE       "\""
#define RUMAL_JS_NEWLINE            "\n"
#define RUMAL_JS_DOT                "."
#define RUMAL_JS_COMMA              ","
#define RUMAL_JS_SEMICOLON          ";"
#define RUMAL_JS_SPACE              " "

namespace rumal{
namespace js{
    
template <typename StreamT>
StreamT& indent(StreamT& stream, int level){
    for(int i =0; i < level; ++i){
        stream << RUMAL_JS_INDENTATION_TAB;
    }
    return stream;
}

template <typename T>
struct value_wrapper_{
    T _val;
    
    explicit value_wrapper_(const T& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _val;
        return stream;
    }
};

template <typename StreamT, typename T>
StreamT& operator<<(StreamT& stream, const value_wrapper_<T>& v){
    v.write(stream);
    return stream;
}

template <int N>
struct value_wrapper_<char[N]>{
    typedef string_type value_type;
    
    value_type _val;
    
    value_wrapper_(const value_type& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << RUMAL_JS_QUOTE_DOUBLE << _val << RUMAL_JS_QUOTE_DOUBLE;
        return stream;
    }
};

template <>
struct value_wrapper_<const char*>{
    typedef const char* value_type;
    
    value_type _val;
    
    explicit value_wrapper_(const value_type& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << RUMAL_JS_QUOTE_DOUBLE << _val << RUMAL_JS_QUOTE_DOUBLE;
        return stream;
    }
};
template <>
struct value_wrapper_<char>{
    typedef char value_type;
    
    value_type _val;
    
    explicit value_wrapper_(const value_type& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << RUMAL_JS_QUOTE_SINGLE << _val << RUMAL_JS_QUOTE_SINGLE;
        return stream;
    }
};

template <>
struct value_wrapper_<std::string>{
    typedef std::string value_type;
    
    value_type _val;
    
    explicit value_wrapper_(const value_type& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << RUMAL_JS_QUOTE_DOUBLE << _val << RUMAL_JS_QUOTE_DOUBLE;
        return stream;
    }
};

template <typename T>
struct trans{
    typedef typename std::decay<T>::type type;
};
template <int N>
struct trans<char[N]>{
    typedef string_type type;
};

template <typename T>
using trans_t = typename trans<T>::type;

template <typename T>
struct dot{
    template <typename StreamT>
    static StreamT& write(StreamT& stream){
        stream << RUMAL_JS_DOT;
        return stream;
    }
};

template <typename PacketT>
struct expression_{
    typedef PacketT packet_type;
    typedef expression_<PacketT> self_type;
    
    packet_type _packet;
    
    explicit expression_(const packet_type& pkt): _packet(pkt){}
    expression_(const self_type& other): _packet(other._packet){}
    template <typename StreamT>
    StreamT& write(StreamT& stream, int level = 0) const{
        // stream << level;
        _packet.write(stream, level);
        return stream;
    }
};

namespace packets{
    template <typename ParentT, typename... Args>
    struct call{
        typedef ParentT parent_type;
        typedef boost::hana::tuple<trans_t<Args>...> tuple_type;
        typedef call<ParentT, Args...> self_type;
        
        string_type _name;
        parent_type _parent;
        tuple_type  _args;
        
        call(string_type name, const parent_type& parent, const Args&... args): _name(name), _parent(parent), _args(args...){}
        call(const self_type& other): _name(other._name), _parent(other._parent), _args(other._args){}
        self_type& operator=(const self_type& other){
            _name   = other._name;
            _parent = other._parent;
            _args   = other._args;
            return *this;
        }
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            _parent.write(stream, level);
            dot<parent_type>::write(stream);
            stream << _name << RUMAL_JS_PARENTHESIS_OPEN;
            unsigned short int counter = 0;
            boost::hana::for_each(_args, [&stream, &counter](const auto& x){
                if(counter++){
                    stream << RUMAL_JS_COMMA;
                }
                stream << value_wrapper_(x);
            });
            stream << RUMAL_JS_PARENTHESIS_CLOSE;
            return stream;
        }
    };
    template <typename ParentT>
    struct access{
        typedef ParentT parent_type;
        typedef access<ParentT> self_type;
        
        parent_type _parent;
        string_type _name;
        
        access(const parent_type& parent, string_type name):_parent(parent), _name(name){}
        access(const self_type& other): _parent(other._parent), _name(other._name){}
        self_type& operator=(const self_type& other){
            _parent = other._parent;
            _name   = other._name;
            return *this;
        }
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            _parent.write(stream, level);
            dot<parent_type>::write(stream);
            stream << _name ;
            return stream;
        }
    };
    template <typename ParentT, typename T>
    struct index{
        typedef ParentT parent_type;
        typedef trans_t<T> value_type;
        typedef index<ParentT, T> self_type;
        
        parent_type _parent;
        value_type  _value;
        
        index(const parent_type& parent, const value_type& value):_parent(parent), _value(value){}
        index(const self_type& other): _parent(other._parent), _value(other._value){}
        self_type& operator=(const self_type& other){
            _parent = other._parent;
            _value   = other._value;
            return *this;
        }
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            _parent.write(stream, level);
            stream << RUMAL_JS_SQUAREBRACE_OPEN << value_wrapper_(_value) << RUMAL_JS_SQUAREBRACE_CLOSE;
            return stream;
        }
    };
    template <typename LeftT, typename RightT>
    struct binary{
        typedef LeftT left_packet_type;
        typedef RightT right_packet_type;
        
        string_type       _op;
        left_packet_type  _left;
        right_packet_type _right;
        
        binary(string_type op, const left_packet_type& left, const right_packet_type& right): _op(op), _left(left), _right(right){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            _left.write(stream, level);
            stream << RUMAL_JS_SPACE << _op << RUMAL_JS_SPACE;
            _right.write(stream, level);
            return stream;
        }
    };
    
    template <typename T>
    struct print_terminal{
        enum {value = true};
    };
    template <typename P>
    struct print_terminal<expression_<P>>{
        enum {value = print_terminal<P>::value};
    };
    /**
     * @brief the first serial in the serial chain
     *
     * @tparam LeftT
     * @tparam RightT
     */
    template <typename LeftT, typename RightT>
    struct serial{
        typedef LeftT left_packet_type;
        typedef RightT right_packet_type;
        
        left_packet_type  _left;
        right_packet_type _right;
        
        serial(const left_packet_type& left, const right_packet_type& right): _left(left), _right(right){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            indent(stream, level);
            _left.write(stream, level);
            if(print_terminal<left_packet_type>::value)
                stream << RUMAL_JS_SEMICOLON << RUMAL_JS_NEWLINE ;
            indent(stream, level);
            _right.write(stream, level);
            return stream;
        }
    };

    namespace helper{
        template <typename T>
        struct scope_should_indent{
            enum {value = true};
        };
    }

    /**
     * @brief from second to last serial in the serial chain
     *
     * @tparam L
     * @tparam R
     * @tparam RightT
     */
    template <typename L, typename R, typename RightT>
    struct serial<serial<L, R>, RightT>{
        typedef serial<L, R> left_packet_type;
        typedef RightT right_packet_type;

        left_packet_type  _left;
        right_packet_type _right;

        serial(const left_packet_type& left, const right_packet_type& right): _left(left), _right(right){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            // do not indent because _left is also a serial
            _left.write(stream, level);
            if(print_terminal<left_packet_type>::value)
                stream << RUMAL_JS_SEMICOLON << RUMAL_JS_NEWLINE ;
            indent(stream, level);
            _right.write(stream, level);
            return stream;
        }
    };

    template <typename HeadT, typename BodyT>
    struct scope{
        typedef HeadT head_type;
        typedef BodyT body_type;
        
        head_type _head;
        body_type _body;
        string_type _name;
        
        scope(string_type name, const head_type& head, const body_type& body): _head(head), _body(body), _name(name){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            stream << _name << RUMAL_JS_PARENTHESIS_OPEN;
            _head.write(stream, 0);
            stream << RUMAL_JS_PARENTHESIS_CLOSE << RUMAL_JS_CURLYBRACE_OPEN << RUMAL_JS_NEWLINE;
            if(helper::scope_should_indent<body_type>::value)
                indent(stream, level+1);
            _body.write(stream, level+1);
            if(print_terminal<body_type>::value)
                stream << RUMAL_JS_SEMICOLON; 
            stream << RUMAL_JS_NEWLINE;
            indent(stream, level);
            stream << RUMAL_JS_CURLYBRACE_CLOSE << RUMAL_JS_NEWLINE;
            return stream;
        }
    };
    template <typename H, typename B>
    struct print_terminal<packets::scope<H, B>>{
        enum {value = false};
    };
    template <typename BodyT>
    struct scope<void, BodyT>{
        typedef BodyT body_type;

        body_type _body;
        string_type _name;
        
        scope(string_type name, const body_type& body): _body(body), _name(name){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, int level = 0) const{
            stream << _name << RUMAL_JS_CURLYBRACE_OPEN << RUMAL_JS_NEWLINE;
            if(helper::scope_should_indent<body_type>::value)
                indent(stream, level+1);
            _body.write(stream, level +1);
            if(print_terminal<body_type>::value)
                stream << RUMAL_JS_SEMICOLON; 
            stream << RUMAL_JS_NEWLINE << RUMAL_JS_CURLYBRACE_CLOSE << RUMAL_JS_NEWLINE;
            return stream;
        }
    };
    template <typename T, typename std::enable_if<std::is_pod<T>::value, bool>::type = true>
    struct constant{
        typedef T value_type;
        
        trans_t<value_type> _val;
        
        constant(const value_type& val): _val(val){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, [[maybe_unused]] int level = 0) const{
            stream << value_wrapper_(_val);
            return stream;
        }
    };
}

struct none_type{
    template <typename StreamT>
    StreamT& write(StreamT& stream, [[maybe_unused]] int level = 0) const{
        return stream;
    }
};
template <typename StreamT>
StreamT& operator<<(StreamT& stream, const none_type& /*none*/){
    return stream;
}

template <>
struct dot<none_type>{
    template <typename StreamT>
    static StreamT& write(StreamT& stream){
        return stream;
    }
};

template <typename... T>
struct meta_void{
    meta_void(){}
    meta_void(const T&... /*value*/){}
};

template <typename PacketT, typename FollowT=void>
struct returned_: public FollowT, public expression_<PacketT>{
    typedef PacketT packet_type;
    typedef FollowT followed_type;
    typedef expression_<PacketT> expression_type;
     
    explicit returned_(const packet_type& packet): FollowT(packet), expression_type(packet){}
};
template <typename StreamT, typename PacketT, typename FollowT>
StreamT& operator<<(StreamT& stream, const returned_<PacketT, FollowT>& r){
    r.write(stream);
    return stream;
}
template <typename PacketT>
struct returned_<PacketT, void>: public expression_<PacketT>{
    typedef PacketT packet_type;
    typedef expression_<PacketT> expression_type;
    
    explicit returned_(const packet_type& packet): expression_type(packet){}
};

/**
 * \brief a function stub inherits from `callable_`.
 * \details If the function returns an object or another callable of type `X` then the function inherits from `callable_<X>`. 
 *          The constructor of the stub must have a no argument default constructor. type `X` if passed must also have a no argument default constructor.
 *          The stub have `operator()` function call operator overloaded to accept any number of arguments of any type
 * \code
 * struct log_: rumal::js::callable_<>{
 *      log_(): rumal::js::callable_<>("log"){}
 * };
 * auto log = log_();
 * std::cout << log(1, 2.5, "Hallo World"); 
 * // prints log(1,2.5,'Hallo World')
 * \endcode
 * 
 * \tparam RetT return stub type
 **/
template <typename DerivedT, template<typename> class RetT=meta_void>
struct callable_: public expression_<packets::access<none_type>>{
    typedef DerivedT derived_type;
    typedef callable_<DerivedT, RetT> self_type;
    typedef expression_<packets::access<none_type>> expression_type;
    template <typename PacketT> using follow = RetT<PacketT>;
    
    string_type _name;
    
    explicit callable_(string_type name): expression_type(packets::access<none_type>(none_type(), name)), _name(name){}
    string_type name() const {return _name;}
    template <typename... Args>
    returned_<packets::call<none_type, Args...>, follow<packets::call<none_type, Args...>>> operator()(const Args&... args){  
        packets::call<none_type, Args...> pckt(_name, none_type(), args...);
        return returned_<packets::call<none_type, Args...>, follow<packets::call<none_type, Args...>>>(pckt);
    }
};

template <typename DerivedT>
struct callable_<DerivedT, meta_void>: public expression_<packets::access<none_type>>{
    typedef DerivedT derived_type;
    typedef callable_<DerivedT, meta_void> self_type;
    typedef expression_<packets::access<none_type>> expression_type;
    typedef bool leaf_type;
    
    string_type _name;
    
    explicit callable_(string_type name): expression_type(packets::access<none_type>(none_type(), name)), _name(name){}
    string_type name() const {return _name;}
    template <typename... Args>
    returned_<packets::call<none_type, Args...>, void> operator()(const Args&... args){  
        packets::call<none_type, Args...> pckt(_name, none_type(), args...);
        return returned_<packets::call<none_type, Args...>, void>(pckt);
    }
};

template <typename StreamT, typename DerivedT, template<typename> class RetT>
StreamT& operator<<(StreamT& stream, const callable_<DerivedT, RetT>& call){
    call.write(stream);
    return stream;
}

template<typename T>
struct void_ {typedef void type;};

template <typename CallableT, typename PacketT, typename = void>
struct method_: public expression_<packets::access<PacketT>>{
    typedef CallableT callable_type;
    typedef PacketT   packet_type;
    typedef expression_<packets::access<PacketT>> expression_type;
    
    callable_type _callable;
    PacketT _packet;
    
    explicit method_(const packet_type& pkt): expression_type(packets::access<PacketT>(pkt, callable_type().name())), _packet(pkt){}
    template <typename... Args>
    returned_<packets::call<PacketT, Args...>, typename CallableT::template follow<packets::call<PacketT, Args...>> > operator()(const Args&... args){
        packets::call<PacketT, Args...> pckt(_callable.name(), _packet, args...);
        return returned_<packets::call<PacketT, Args...>, typename CallableT::template follow<packets::call<PacketT, Args...>> >(pckt);
    }
};

/**
 * \brief void returning function
 */
template <typename CallableT, typename PacketT>
struct method_<CallableT, PacketT, typename void_<typename CallableT::leaf_type>::type>: public expression_<packets::access<PacketT>>{
    typedef CallableT callable_type;
    typedef PacketT   packet_type;
    typedef expression_<packets::access<PacketT>> expression_type;
    
    callable_type _callable;
    PacketT _packet;
    
    explicit method_(const packet_type& pkt): expression_type(packets::access<PacketT>(pkt, callable_type().name())), _packet(pkt){}
    template <typename... Args>
    returned_<packets::call<PacketT, Args...>, void> operator()(const Args&... args){
        packets::call<PacketT, Args...> pckt(_callable.name(), _packet, args...);
        return returned_<packets::call<PacketT, Args...>, void>(pckt);
    }
};
template <typename StreamT, typename CallableT, typename PacketT>
StreamT& operator<<(StreamT& stream, const method_<CallableT, PacketT>& pkt){
    pkt.write(stream);
    return stream;
}

template <typename PacketT, template<typename> class FollowT=meta_void>
struct iterable_{
    typedef PacketT packet_type;
    
    explicit iterable_(const packet_type& pkt): _pkt(pkt){}
    template <typename T>
    returned_<packets::index<packet_type, T>, FollowT<packets::index<packet_type, T>> > operator[](const T& value){
        packets::index<packet_type, T> pckt(_pkt, value);
        return returned_<packets::index<packet_type, T>, FollowT<packets::index<packet_type, T>> >(pckt);
    }
    private:
        packet_type _pkt;
};

template <template<typename> class FollowT, typename PacketT>
struct property_: public FollowT<packets::access<PacketT>>, public expression_<packets::access<PacketT>>{
    typedef packets::access<PacketT> packet_type;
    typedef FollowT<packets::access<PacketT>> follow_type;
    typedef expression_<packets::access<PacketT>> expression_type;
     
    property_(string_type name, const PacketT& pkt): follow_type(packet_type(pkt, name)), expression_type(packet_type(pkt, name)){}
};
template <typename StreamT, template<typename> class FollowT, typename PacketT>
StreamT& operator<<(StreamT& stream, const property_<FollowT, PacketT>& prop){
    prop.write(stream);
    return stream;
}

template <template<typename> class FollowT, typename PacketT>
struct member_: public expression_<packets::access<PacketT>>{
    typedef packets::access<PacketT> packet_type;
    typedef FollowT<packets::access<PacketT>> follow_type;
    typedef expression_<packets::access<PacketT>> expression_type;
     
    member_(string_type name, const PacketT& pkt): expression_type(packet_type(pkt, name)){}
    returned_<packets::access<PacketT>, follow_type> operator()(){
        auto pkt = expression_type::_packet;
        return returned_<packets::access<PacketT>, follow_type>(pkt);
    }
};
template <typename StreamT, template<typename> class FollowT, typename PacketT>
StreamT& operator<<(StreamT& stream, const member_<FollowT, PacketT>& prop){
    prop.write(stream);
    return stream;
}

template <typename L, typename R>
struct binary_expression: public expression_<packets::binary<typename L::packet_type, typename R::packet_type>>{
    typedef L left_expr_type;
    typedef R right_expr_type;
    typedef typename L::packet_type left_packet_type;
    typedef typename R::packet_type right_packet_type;
    typedef packets::binary<typename L::packet_type, typename R::packet_type> packet_type;
    typedef expression_<packet_type> expression_type;
    
    binary_expression(string_type op, const L& left, const R& right): expression_type(packet_type(op, left._packet, right._packet)){}
};

template <typename StreamT, typename L, typename R>
StreamT& operator<<(StreamT& stream, const binary_expression<L, R>& binex){
    binex.write(stream);
    return stream;
}

template <typename L, typename R>
struct serial_expression: public expression_<packets::serial<typename L::packet_type, typename R::packet_type>>{
    typedef L left_expr_type;
    typedef R right_expr_type;
    typedef typename L::packet_type left_packet_type;
    typedef typename R::packet_type right_packet_type;
    typedef packets::serial<typename L::packet_type, typename R::packet_type> packet_type;
    typedef expression_<packet_type> expression_type;
    
    serial_expression(const L& left, const R& right): expression_type(packet_type(left._packet, right._packet)){}
};

template <typename StreamT, typename L, typename R>
StreamT& operator<<(StreamT& stream, const serial_expression<L, R>& binex){
    binex.write(stream);
    return stream;
}

namespace packets {
namespace helper {
    template<typename L, typename R>
    struct scope_should_indent<serial_expression<L, R>> {
        enum {
            value = false
        };
    };
}
template <typename L, typename R>
struct print_terminal<serial_expression<L, R>>{
    enum {value = print_terminal<R>::value};
};
template <typename L, typename R>
struct print_terminal<packets::serial<L, R>>{
    enum {value = print_terminal<R>::value};
};
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator&&(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("&&", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator&&(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("&&", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator&&(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("&&", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator||(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("||", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator||(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("||", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator||(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("||", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator+(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("+", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator+(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("+", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator+(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("+", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator-(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("-", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator-(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("-", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator-(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("-", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator*(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("*", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator*(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("*", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator*(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("*", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator/(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("/", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator/(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("/", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator/(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("/", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator==(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("==", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator==(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("==", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator==(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("==", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator<=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("<=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator<=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("<=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator<=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("<=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator>=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>(">=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator>=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>(">=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator>=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>(">=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator<(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("<", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator<(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("<", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator<(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("<", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator>(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>(">", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator>(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>(">", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator>(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>(">", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator+=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("+=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator+=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("+=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator+=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("+=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator-=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("-=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator-=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("-=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator-=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("-=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator*=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("*=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator*=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("*=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator*=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("*=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator/=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("/=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator/=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("/=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator/=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("/=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator%=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("%=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator%=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("%=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<L>, bool> = true>
binary_expression<expression_<packets::constant<L>>, expression_<R>> operator%=(const L& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<packets::constant<L>>, expression_<R>>("%=", expression_<packets::constant<L>>(packets::constant<L>(leftex)), rightex);
}

template <typename L, typename R>
binary_expression<expression_<L>, expression_<R>> operator<<=(const expression_<L>& leftex, const expression_<R>& rightex){
    return binary_expression<expression_<L>, expression_<R>>("=", leftex, rightex);
}
template <typename L, typename R, std::enable_if_t<std::is_pod_v<R>, bool> = true>
binary_expression<expression_<L>, expression_<packets::constant<R>>> operator<<=(const expression_<L>& leftex, const R& rightex){
    return binary_expression<expression_<L>, expression_<packets::constant<R>>>("=", leftex, expression_<packets::constant<R>>(packets::constant<R>(rightex)));
}

template <typename L, typename R>
serial_expression<expression_<L>, expression_<R>> operator,(const expression_<L>& leftex, const expression_<R>& rightex){
    return serial_expression<expression_<L>, expression_<R>>(leftex, rightex);
}

/**
 * \brief a generic variable 
 */
template <template<typename> class FollowT=meta_void>
struct assignable: public expression_<packets::access<none_type>>, public FollowT<packets::access<none_type>>{
    typedef assignable<FollowT> self_type;
    typedef expression_<packets::access<none_type>> expression_type;
    typedef FollowT<packets::access<none_type>> follow_type;
    
//     string_type _name;
    
    explicit assignable(string_type name): expression_type(packets::access<none_type>(none_type(), name)), FollowT<packets::access<none_type>>(packets::access<none_type>(none_type(), name))/*, _name(name)*/{}
};
template <typename StreamT, template<typename> class FollowT>
StreamT& operator<<(StreamT& stream, const assignable<FollowT>& var){
    var.write(stream);
    return stream;
}

namespace packets{ 
    template <typename AccessT>
    struct declaration{
        packets::access<none_type> _access;
        
        declaration(const packets::access<none_type>& access): _access(access){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, [[maybe_unused]] int level = 0) const{
            stream << AccessT::specifier << RUMAL_JS_SPACE;
            _access.write(stream);
            return stream;
        }
    };
    
    template <typename AssignmentT, typename RightT>
    struct assignment;
    
    template <template<typename> class FollowT, typename RightT>
    struct assignment<assignable<FollowT>, RightT>: public binary<assignable<FollowT>, RightT>{
        assignment(const assignable<FollowT>& lhs, const RightT& rhs): binary<assignable<FollowT>, RightT>("=", lhs, rhs){}
    };
    
    template <typename... A>
    struct arguments{
        boost::hana::tuple<A...> _args;
        
        arguments(A... a): _args(a...){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, [[maybe_unused]] int level = 0) const{
            unsigned short int counter = 0;
            boost::hana::for_each(_args, [&stream, &counter](const auto& x){
                if(counter++){
                    stream << RUMAL_JS_COMMA;
                }
                stream << x;
            });
            return stream;
        }
    };
    template <typename... A>
    struct for_arguments{
        boost::hana::tuple<A...> _args;
        
        for_arguments(A... a): _args(a...){}
        template <typename StreamT>
        StreamT& write(StreamT& stream, [[maybe_unused]] int level = 0) const{
            unsigned short int counter = 0;
            boost::hana::for_each(_args, [&stream, &counter](const auto& x){
                if(counter++){
                    stream << RUMAL_JS_SEMICOLON;
                }
                stream << x;
            });
            return stream;
        }
    };
}

struct let_{
    inline static string_type specifier = "let";
};

struct const_{
    inline static string_type specifier = "const";
};

struct var_{
    inline static string_type specifier = "var";
};

template <typename AssignableT, typename AccessT>
struct declaration_expression;

template <typename StreamT, typename AssignableT, typename AccessT>
StreamT& operator<<(StreamT& stream, const declaration_expression<AssignableT, AccessT>& declxp){
    declxp.write(stream);
    return stream;
}

template <template<typename> class FollowT, typename AccessT>
struct declaration_expression<assignable<FollowT>, AccessT>: public expression_<packets::declaration<AccessT>>{
    declaration_expression(const assignable<FollowT>& assgn): expression_<packets::declaration<AccessT>>(packets::declaration<AccessT>(assgn._packet)){}
};

namespace packets{ 
    template <template<typename> class FollowT, typename AccessT, typename RightT>
    struct assignment<declaration_expression<assignable<FollowT>, AccessT>, RightT>: public binary<declaration_expression<assignable<FollowT>, AccessT>, RightT>{
        assignment(const declaration_expression<assignable<FollowT>, AccessT>& lhs, const RightT& rhs): binary<declaration_expression<assignable<FollowT>, AccessT>, RightT>("=", lhs, rhs){}
    };
}

template <template<typename> class FollowT=meta_void>
declaration_expression<assignable<FollowT>, let_> _let(const assignable<FollowT>& assgn){
    return declaration_expression<assignable<FollowT>, let_>(assgn);
}
template <template<typename> class FollowT=meta_void>
declaration_expression<assignable<FollowT>, const_> _const(const assignable<FollowT>& assgn){
    return declaration_expression<assignable<FollowT>, const_>(assgn);
}
template <template<typename> class FollowT=meta_void>
declaration_expression<assignable<FollowT>, var_> _var(const assignable<FollowT>& assgn){
    return declaration_expression<assignable<FollowT>, var_>(assgn);
}

template <typename HeadT, typename BodyT>
struct scope_expression: public expression_<packets::scope<HeadT, BodyT>>{
    scope_expression(string_type name, const HeadT& head, const BodyT& body): expression_<packets::scope<HeadT, BodyT>>(packets::scope<HeadT, BodyT>(name, head, body)){}
};
template <typename BodyT>
struct scope_expression<void, BodyT>: public expression_<packets::scope<void, BodyT>>{
    scope_expression(string_type name, const BodyT& body): expression_<packets::scope<void, BodyT>>(packets::scope<void, BodyT>(name, body)){}
};

template <typename StreamT, typename HeadT, typename BodyT>
StreamT& operator<<(StreamT& stream, const scope_expression<HeadT, BodyT>& pkt){
    pkt.write(stream);
    return stream;
}

template <typename ConditionT=void>
struct labeled_block_{
    typedef ConditionT condition_type;
    
    string_type _label;
    condition_type _condition;
    
    labeled_block_(string_type label, const condition_type& condition): _label(label), _condition(condition){}
    template <typename BodyT>
    scope_expression<ConditionT, BodyT> operator[](const BodyT& body){
        return scope_expression<ConditionT, BodyT>(_label, _condition, body);
    }
};
template <>
struct labeled_block_<void>{    
    string_type _label;
    
    labeled_block_(string_type label): _label(label){}
    template <typename BodyT>
    scope_expression<void, BodyT> operator[](const BodyT& body){
        return scope_expression<void, BodyT>(_label, body);
    }
};

template <typename ConditionT>
struct if_block: labeled_block_<ConditionT>{
    if_block(const ConditionT& condition): labeled_block_<ConditionT>("if", condition){}
};
template <typename ConditionT=void>
struct else_block: labeled_block_<ConditionT>{
    else_block(const ConditionT& condition): labeled_block_<ConditionT>("else if", condition){}
};
template <>
struct else_block<void>: labeled_block_<void>{
    else_block(): labeled_block_<void>("else"){}
};
template <typename ConditionT>
struct while_block: labeled_block_<ConditionT>{
    while_block(const ConditionT& condition): labeled_block_<ConditionT>("while", condition){}
};

template <typename T>
if_block<T> _if(const T& condition){
    return if_block<T>(condition);
}
template <typename T>
else_block<T> _else(const T& condition){
    return else_block<T>(condition);
}
else_block<void> _else(){
    return else_block<void>();
}
template <typename T>
while_block<T> _while(const T& condition){
    return while_block<T>(condition);
}

template <typename... ArgsT>
struct function_block: labeled_block_<packets::arguments<ArgsT...>>{
    function_block(const ArgsT&... args): labeled_block_<packets::arguments<ArgsT...>>("function", packets::arguments(args...)){}
};
template <typename... T>
function_block<T...> function(const T&... condition){
    return function_block<T...>(condition...);
}

template <typename... ArgsT>
struct for_block: labeled_block_<packets::for_arguments<ArgsT...>>{
    for_block(const ArgsT&... args): labeled_block_<packets::for_arguments<ArgsT...>>("for", packets::for_arguments(args...)){}
};
template <typename... T>
for_block<T...> _for(const T&... condition){
    return for_block<T...>(condition...);
}

}
}

#endif // RUMAL_JS_H
