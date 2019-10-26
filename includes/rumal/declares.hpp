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

#ifndef RUMAL_DECLARES_H
#define RUMAL_DECLARES_H

#include <rumal/base.hpp>

#define DEFINE_HTML_ATTRIBUTE(name) template <typename T> auto name(T value){return rumal::html::attr(#name, value);}
#define DEFINE_LABELED_HTML_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::html::attr(label, value);}
#define DEFINE_HTML_TAG(name)                                   \
    template <typename Args, typename... T>                     \
    auto name(const Args& args, const T&... elems){                    \
        return tag<Args, T...>(#name, args, elems...);          \
    }                                                           \
    template <typename... T>                                    \
    auto name(const T&... elems){                               \
        return tag<void, T...>(#name, elems...);                \
    }

namespace rumal{
    namespace html{
        namespace attrs{
            DEFINE_HTML_ATTRIBUTE(id)
            DEFINE_LABELED_HTML_ATTRIBUTE(klass, "class")
            DEFINE_HTML_ATTRIBUTE(width)
            DEFINE_HTML_ATTRIBUTE(height)
            DEFINE_HTML_ATTRIBUTE(src)
            DEFINE_HTML_ATTRIBUTE(type)
            DEFINE_HTML_ATTRIBUTE(style)
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
    }
}

#endif //RUMAL_DECLARES_H