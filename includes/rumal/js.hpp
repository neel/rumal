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

#include <boost/hana/tuple.hpp>

namespace rumal{
namespace js{
    
template <typename LeftT, typename RightT>
struct assignment{
    typedef LeftT  left_type;
    typedef RightT right_type;
    typedef assignment<LeftT, RightT> self_type;
    
    left_type  _var;
    right_type _val;
    
    assignment(const left_type& lhs, const right_type& val): _var(lhs), _val(val){}
    template <typename RhsT>
    assignment<self_type, RhsT> operator=(const RhsT& val){ // lgtm[cpp/assignment-does-not-return-this]
        return assignment<self_type, RhsT>(*this, val);
    }
};
    
/**
 * \brief a generic variable needs an access specifier like var, let, const. 
 */
template <typename AccessT>
struct assignable{
    typedef assignable<AccessT> self_type;
    
    const char* _name;
    
    explicit assignable(const char* name): _name(name){}
       
    template <typename RightT>
    assignment<self_type, RightT> operator=(const RightT& val){ // lgtm[cpp/assignment-does-not-return-this]
        return assignment<self_type, RightT>(*this, val);
    }
};

template <typename StreamT, typename AccessT>
StreamT& operator<<(StreamT& stream, const assignable<AccessT>& var){
    stream << AccessT::specifier << " " << var._name;
    return stream;
}

template <typename StreamT, typename LeftT, typename RightT>
StreamT& operator<<(StreamT& stream, const assignment<LeftT, RightT>& assign){
    stream << assign._var << " = " << assign._val;
    return stream;
}

struct let_{
    inline static const char* specifier = "let";
};

struct const_{
    inline static const char* specifier = "const";
};

struct var_{
    inline static const char* specifier = "var";
};

typedef assignable<let_>   _let;
typedef assignable<const_> _const;
typedef assignable<var_>    _var;

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

template <typename A>
struct value_wrapper_<assignable<A>>{
    typedef assignable<A> value_type;
    
    value_type _val;
    
    value_wrapper_(const value_type& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _val._name;
        return stream;
    }
};

template <int N>
struct value_wrapper_<char[N]>{
    typedef const char* value_type;
    
    value_type _val;
    
    value_wrapper_(const value_type& val): _val(val){}    
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << "'" << _val << "'";
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
        stream << "'" << _val << "'";
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
        stream << "\"" << _val << "\"";
        return stream;
    }
};

template <typename T>
struct trans{
    typedef typename std::decay<T>::type type;
};
template <int N>
struct trans<char[N]>{
    typedef const char* type;
};

template <typename T>
using trans_t = typename trans<T>::type;

template <typename T>
struct dot{
    template <typename StreamT>
    static StreamT& write(StreamT& stream){
        stream << ".";
        return stream;
    }
};

template <typename ParentT, typename... Args>
struct call_packet{
    typedef ParentT parent_type;
    typedef boost::hana::tuple<trans_t<Args>...> tuple_type;
    typedef call_packet<ParentT, Args...> self_type;
    
    const char* _name;
    parent_type _parent;
    tuple_type  _args;
    
    call_packet(const char* name, const parent_type& parent, const Args&... args): _name(name), _parent(parent), _args(args...){}
    call_packet(const self_type& other): _name(other._name), _parent(other._parent), _args(other._args){}
    self_type& operator=(const self_type& other){
        _name   = other._name;
        _parent = other._parent;
        _args   = other._args;
        return *this;
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _parent;
        dot<parent_type>::write(stream);
        stream << _name << "(";
        unsigned short int counter = 0;
        boost::hana::for_each(_args, [&stream, &counter](const auto& x){
            if(counter++){
                stream << ",";
            }
            stream << value_wrapper_(x);
        });
        stream << ")";
        return stream;
    }
};
template <typename StreamT, typename... T>
StreamT& operator<<(StreamT& stream, const call_packet<T...>& packet){
    packet.write(stream);
    return stream;
}

struct none_type{};
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
    meta_void(const T&... value){}
};

template <typename PacketT, typename FollowT=void>
struct returned_: public FollowT{
    typedef PacketT packet_type;
    typedef FollowT followed_type;
    
    packet_type _packet;
    
    explicit returned_(const packet_type& packet): FollowT(packet), _packet(packet){}
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _packet;
        return stream;
    }
};
template <typename StreamT, typename PacketT, typename FollowT>
StreamT& operator<<(StreamT& stream, const returned_<PacketT, FollowT>& r){
    r.write(stream);
    return stream;
}
template <typename PacketT>
struct returned_<PacketT, void>{
    typedef PacketT packet_type;
    
    packet_type _packet;
    
    explicit returned_(const packet_type& packet): _packet(packet){}
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _packet;
        return stream;
    }
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
struct callable_{
    typedef DerivedT derived_type;
    typedef callable_<DerivedT, RetT> self_type;
    template <typename PacketT> using follow = RetT<PacketT>;
    const char* _name;
    
    explicit callable_(const char* name): _name(name){}
    const char* name() const {return _name;}
    template <typename... Args>
    returned_<call_packet<none_type, Args...>, follow<call_packet<none_type, Args...>>> operator()(const Args&... args){  
        call_packet<none_type, Args...> pckt(_name, none_type(), args...);
        return returned_<call_packet<none_type, Args...>, follow<call_packet<none_type, Args...>>>(pckt);
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _name;
        return stream;
    }
};

template <typename DerivedT>
struct callable_<DerivedT, meta_void>{
    typedef DerivedT derived_type;
    typedef callable_<DerivedT, meta_void> self_type;
    typedef bool leaf_type;
    
    const char* _name;
    
    explicit callable_(const char* name): _name(name){}
    const char* name() const {return _name;}
    template <typename... Args>
    returned_<call_packet<none_type, Args...>, void> operator()(const Args&... args){  
        call_packet<none_type, Args...> pckt(_name, none_type(), args...);
        return returned_<call_packet<none_type, Args...>, void>(pckt);
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _name;
        return stream;
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
struct method_{
    typedef CallableT callable_type;
    typedef PacketT   packet_type;
    
    callable_type _callable;
    PacketT _packet;
    
    explicit method_(const packet_type& pkt): _packet(pkt){}
    template <typename... Args>
    returned_<call_packet<PacketT, Args...>, typename CallableT::template follow<call_packet<PacketT, Args...>> > operator()(const Args&... args){
        call_packet<PacketT, Args...> pckt(_callable.name(), _packet, args...);
        return returned_<call_packet<PacketT, Args...>, typename CallableT::template follow<call_packet<PacketT, Args...>> >(pckt);
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _callable;
        return stream;
    }
};

template <typename CallableT, typename PacketT>
struct method_<CallableT, PacketT, typename void_<typename CallableT::leaf_type>::type>{
    typedef CallableT callable_type;
    typedef PacketT   packet_type;
    
    callable_type _callable;
    PacketT _packet;
    
    explicit method_(const packet_type& pkt): _packet(pkt){}
    template <typename... Args>
    returned_<call_packet<PacketT, Args...>, void> operator()(const Args&... args){
        call_packet<PacketT, Args...> pckt(_callable.name(), _packet, args...);
        return returned_<call_packet<PacketT, Args...>, void>(pckt);
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _packet;
        dot<packet_type>::write(stream);
        stream << _callable;
        return stream;
    }
};
template <typename StreamT, typename CallableT, typename PacketT>
StreamT& operator<<(StreamT& stream, const method_<CallableT, PacketT>& pkt){
    pkt.write(stream);
    return stream;
}

template <typename ParentT, typename T>
struct index_packet{
    typedef ParentT parent_type;
    typedef trans_t<T> value_type;
    typedef index_packet<ParentT, T> self_type;
    
    parent_type _parent;
    value_type  _value;
    
    index_packet(const parent_type& parent, const value_type& value):_parent(parent), _value(value){}
    index_packet(const self_type& other): _parent(other._parent), _value(other._value){}
    self_type& operator=(const self_type& other){
        _parent = other._parent;
        _value   = other._value;
        return *this;
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _parent;
        stream << "[" << value_wrapper_(_value) << "]";
        return stream;
    }
};
template <typename StreamT, typename ParentT, typename T>
StreamT& operator<<(StreamT& stream, const index_packet<ParentT, T>& idx_pkt){
    idx_pkt.write(stream);
    return stream;
}

template <typename PacketT, template<typename> class FollowT=meta_void>
struct iterable_{
    typedef PacketT packet_type;
    packet_type _packet;
    
    explicit iterable_(const packet_type& pkt): _packet(pkt){}
    template <typename T>
    returned_<index_packet<packet_type, T>, FollowT<index_packet<packet_type, T>> > operator[](const T& value){
        index_packet<packet_type, T> pckt(_packet, value);
        return returned_<index_packet<packet_type, T>, FollowT<index_packet<packet_type, T>> >(pckt);
    }
};

template <typename ParentT>
struct access_packet{
    typedef ParentT parent_type;
    typedef access_packet<ParentT> self_type;
    
    parent_type _parent;
    const char* _name;
    
    access_packet(const parent_type& parent, const char* name):_parent(parent), _name(name){}
    access_packet(const self_type& other): _parent(other._parent), _name(other._name){}
    self_type& operator=(const self_type& other){
        _parent = other._parent;
        _name   = other._name;
        return *this;
    }
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _parent;
        dot<parent_type>::write(stream);
        stream << _name ;
        return stream;
    }
};
template <typename StreamT, typename ParentT>
StreamT& operator<<(StreamT& stream, const access_packet<ParentT>& pkt){
    pkt.write(stream);
    return stream;
}

template <template<typename> class FollowT, typename PacketT>
struct property_: FollowT<access_packet<PacketT>>{
    typedef access_packet<PacketT> packet_type;
    typedef FollowT<access_packet<PacketT>> follow_type;
    
    const char* _name;
    packet_type _packet;
    
    property_(const char* name, const PacketT& pkt): follow_type(packet_type(pkt, name)), _name(name), _packet(packet_type(pkt, name)){}
    template <typename StreamT>
    StreamT& write(StreamT& stream) const{
        stream << _packet;
        return stream;
    }
};
template <typename StreamT, template<typename> class FollowT, typename PacketT>
StreamT& operator<<(StreamT& stream, const property_<FollowT, PacketT>& prop){
    prop.write(stream);
    return stream;
}

template <typename Packet, typename LeftT, typename RightT>
struct binary_operation_packet{
    typedef typename LeftT::packet_type  left_packet_type;
    typedef typename RightT::packet_type right_packet_type;
    
    const char*       _op;
    left_packet_type  _left;
    right_packet_type _right;
    
    binary_operation_packet(const char* op, const left_packet_type& left, const right_packet_type& right): _op(op), _left(left), _right(right){}
};


}
}

#endif // RUMAL_JS_H
