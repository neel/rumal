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

#ifndef RUMAL_JS_TYPES_H
#define RUMAL_JS_TYPES_H

#define RUMAL_JS_DECLARE_CALLABLE(name)                                         \
    struct name##_: rumal::js::callable_<name##_>{                              \
        name##_(): rumal::js::callable_<name##_>(#name){}                       \
    };
#define RUMAL_JS_DECLARE_RETURNING_CALLABLE(name, follow)                       \
    struct name##_: rumal::js::callable_<name##_, follow>{                      \
        name##_(): rumal::js::callable_<name##_, follow>(#name){}               \
    };
#define RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(name)                               \
    template <template<typename> class FollowT>                                 \
    struct name##_: rumal::js::callable_<name##_<FollowT>, FollowT>{            \
        name##_(): rumal::js::callable_<name##_<FollowT>, FollowT>(#name){}     \
    };

#include "js.hpp"

namespace rumal{
namespace js{
    
namespace types{
template <typename T>
struct terminal_{
    
};

template <typename T>
struct Number;

template <typename T>
struct Boolean{
    rumal::js::property_<Number, T> length;
    
    Boolean(const T& pkt): length("length", pkt){}
};

namespace Number_{
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(parseInt)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(parseFloat)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(toFixed)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(toPrecision)
    RUMAL_JS_DECLARE_CALLABLE(isNaN)
    RUMAL_JS_DECLARE_CALLABLE(isFinite)
    RUMAL_JS_DECLARE_CALLABLE(isInteger)
    RUMAL_JS_DECLARE_CALLABLE(isSafeInteger)
}
template <typename T>
struct Number{
    rumal::js::method_<Number_::isNaN_, T> isNAN;
    rumal::js::method_<Number_::isFinite_, T> isFinite;
    rumal::js::method_<Number_::isInteger_, T> isInteger;
    rumal::js::method_<Number_::isSafeInteger_, T> isSafeInteger;
    rumal::js::method_<Number_::parseFloat_<Number>, T> parseFloat;
    rumal::js::method_<Number_::parseInt_<Number>, T> parseInt;
    rumal::js::method_<Number_::toFixed_<Number>, T> toFixed;
    rumal::js::method_<Number_::toPrecision_<Number>, T> toPrecision;
    
    Number(const T& pkt): isNAN(pkt), isFinite(pkt), isInteger(pkt), isSafeInteger(pkt), parseFloat(pkt), parseInt(pkt), toFixed(pkt), toPrecision(pkt){}
};
namespace Array_{
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(fill)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(reverse)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(sort)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(concat)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(join)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(slice)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(filter)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(forEach)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(map)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(reduce)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(reduceRight)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(values)
    RUMAL_JS_DECLARE_CALLABLE(pop)
    RUMAL_JS_DECLARE_CALLABLE(push)
    RUMAL_JS_DECLARE_CALLABLE(shift)
    RUMAL_JS_DECLARE_CALLABLE(splice)
    RUMAL_JS_DECLARE_CALLABLE(unshift)
    RUMAL_JS_DECLARE_CALLABLE(includes)
    RUMAL_JS_DECLARE_CALLABLE(every)
    RUMAL_JS_DECLARE_CALLABLE(find)
    RUMAL_JS_DECLARE_CALLABLE(some)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(indexOf, Number)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(lastIndexOf, Number)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(findIndex, Number)
}
template <typename T, template<typename> class FollowT=terminal_>
struct Array: rumal::js::iterable_<T, FollowT>{
    rumal::js::property_<Number, T> length;
    rumal::js::method_<Array_::fill_<Array>, T> fill;
    rumal::js::method_<Array_::reverse_<Array>, T> reverse;
    rumal::js::method_<Array_::sort_<Array>, T> sort;
    rumal::js::method_<Array_::concat_<Array>, T> concat;
    rumal::js::method_<Array_::join_<Array>, T> join;
    rumal::js::method_<Array_::slice_<Array>, T> slice;
    rumal::js::method_<Array_::filter_<Array>, T> filter;
    rumal::js::method_<Array_::forEach_<Array>, T> forEach;
    rumal::js::method_<Array_::map_<Array>, T> map;
    rumal::js::method_<Array_::reduce_<Array>, T> reduce;
    rumal::js::method_<Array_::reduceRight_<Array>, T> reduceRight;
    rumal::js::method_<Array_::values_<Array>, T> values;
    rumal::js::method_<Array_::pop_, T> pop;
    rumal::js::method_<Array_::push_, T> push;
    rumal::js::method_<Array_::shift_, T> shift;
    rumal::js::method_<Array_::splice_, T> splice;
    rumal::js::method_<Array_::unshift_, T> unshift;
    rumal::js::method_<Array_::includes_, T> includes;
    rumal::js::method_<Array_::every_, T> every;
    rumal::js::method_<Array_::find_, T> find;
    rumal::js::method_<Array_::some_, T> some;
    rumal::js::method_<Array_::indexOf_, T> indexOf;
    rumal::js::method_<Array_::lastIndexOf_, T> lastIndexOf;
    rumal::js::method_<Array_::findIndex_, T> findIndex;
    
    Array(const T& pkt): rumal::js::iterable_<T, FollowT>(pkt), length("length", pkt), 
        fill(pkt), reverse(pkt), sort(pkt), concat(pkt), join(pkt), slice(pkt), filter(pkt), forEach(pkt), map(pkt), reduce(pkt), reduceRight(pkt), values(pkt), pop(pkt),
        push(pkt), shift(pkt), splice(pkt), unshift(pkt), includes(pkt), every(pkt), find(pkt), some(pkt), indexOf(pkt), lastIndexOf(pkt), findIndex(pkt){}
};

namespace String_{
    RUMAL_JS_DECLARE_CALLABLE(includes)
    RUMAL_JS_DECLARE_CALLABLE(charAt)
    RUMAL_JS_DECLARE_CALLABLE(charCodeAt)
    RUMAL_JS_DECLARE_CALLABLE(codePointAt)
    RUMAL_JS_DECLARE_CALLABLE(startsWith)
    RUMAL_JS_DECLARE_CALLABLE(endsWith)
    RUMAL_JS_DECLARE_CALLABLE(search)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(indexOf, Number)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(lastIndexOf, Number)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(match, Array)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(matchAll, Array)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(normalize)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(repeat)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(replace)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(concat)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(split)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(slice)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(substring)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(toLowerCase)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(toUpperCase)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(trim)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(trimStart)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(trimLeft)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(trimEnd)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(trimRight)
}
template <typename T>
struct String{
    rumal::js::property_<Number, T> length;
    rumal::js::method_<String_::includes_, T> includes;
    rumal::js::method_<String_::charAt_, T> charAt;
    rumal::js::method_<String_::charCodeAt_, T> charCodeAt;
    rumal::js::method_<String_::codePointAt_, T> codePointAt;
    rumal::js::method_<String_::startsWith_, T> startsWith;
    rumal::js::method_<String_::endsWith_, T> endsWith;
    rumal::js::method_<String_::search_, T> search;
    rumal::js::method_<String_::indexOf_, T> indexOf;
    rumal::js::method_<String_::lastIndexOf_, T> lastIndexOf;
    rumal::js::method_<String_::match_, T> match;
    rumal::js::method_<String_::matchAll_, T> matchAll;
    rumal::js::method_<String_::normalize_<String>, T> normalize;
    rumal::js::method_<String_::repeat_<String>, T> repeat;
    rumal::js::method_<String_::replace_<String>, T> replace;
    rumal::js::method_<String_::concat_<String>, T> concat;
    rumal::js::method_<String_::split_<String>, T> split;
    rumal::js::method_<String_::slice_<String>, T> slice;
    rumal::js::method_<String_::substring_<String>, T> substring;
    rumal::js::method_<String_::toLowerCase_<String>, T> toLowerCase;
    rumal::js::method_<String_::toUpperCase_<String>, T> toUpperCase;
    rumal::js::method_<String_::trim_<String>, T> trim;
    rumal::js::method_<String_::trimStart_<String>, T> trimStart;
    rumal::js::method_<String_::trimLeft_<String>, T> trimLeft;
    rumal::js::method_<String_::trimEnd_<String>, T> trimEnd;
    rumal::js::method_<String_::trimRight_<String>, T> trimRight;
    
    String(const T& pkt): length("length", pkt), 
        includes(pkt), charAt(pkt), charCodeAt(pkt), codePointAt(pkt), startsWith(pkt), endsWith(pkt), search(pkt), indexOf(pkt), lastIndexOf(pkt),
        match(pkt), matchAll(pkt), normalize(pkt), repeat(pkt), replace(pkt), concat(pkt), split(pkt), slice(pkt), substring(pkt), toLowerCase(pkt), toUpperCase(pkt),
        trim(pkt), trimStart(pkt), trimLeft(pkt), trimEnd(pkt), trimRight(pkt){}
};

template <typename T>
struct Object{
    
};

}
}
}

#endif // RUMAL_JS_TYPES_H
