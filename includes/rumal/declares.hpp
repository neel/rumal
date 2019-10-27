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

#define DEFINE_HTML_ATTRIBUTE(name) template <typename T> auto _##name(T value){return rumal::html::attr(#name, value);}
#define DEFINE_LABELED_HTML_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::html::attr(label, value);}
#define DEFINE_CSS_ATTRIBUTE(name) template <typename T> auto name(T value){return rumal::css::prepared(#name, value);}
#define DEFINE_LABELED_CSS_ATTRIBUTE(name, label) template <typename T> auto name(T value){return rumal::css::prop(label, value);}
#define DEFINE_HTML_TAG(name)                                   \
    template <typename Args, typename... T>                     \
    auto name(const Args& args, const T&... elems){             \
        return tag<Args, T...>(#name, args, elems...);          \
    }                                                           \
    template <typename... T>                                    \
    auto name(const T&... elems){                               \
        return tag<void, T...>(#name, elems...);                \
    }

namespace rumal{
    namespace html{
        namespace attrs{
            DEFINE_HTML_ATTRIBUTE(accept)
            DEFINE_HTML_ATTRIBUTE(accesskey)
            DEFINE_HTML_ATTRIBUTE(action)
            DEFINE_HTML_ATTRIBUTE(align)
            DEFINE_HTML_ATTRIBUTE(allow)
            DEFINE_HTML_ATTRIBUTE(alt)
            DEFINE_HTML_ATTRIBUTE(async)
            DEFINE_HTML_ATTRIBUTE(autocapitalize)
            DEFINE_HTML_ATTRIBUTE(autocomplete)
            DEFINE_HTML_ATTRIBUTE(autofocus)
            DEFINE_HTML_ATTRIBUTE(autoplay)
            DEFINE_HTML_ATTRIBUTE(background)
            DEFINE_HTML_ATTRIBUTE(bgcolor)
            DEFINE_HTML_ATTRIBUTE(border)
            DEFINE_HTML_ATTRIBUTE(buffered)
            DEFINE_HTML_ATTRIBUTE(challenge)
            DEFINE_HTML_ATTRIBUTE(charset)
            DEFINE_HTML_ATTRIBUTE(checked)
            DEFINE_HTML_ATTRIBUTE(cite)
            DEFINE_HTML_ATTRIBUTE(class)
            DEFINE_HTML_ATTRIBUTE(code)
            DEFINE_HTML_ATTRIBUTE(codebase)
            DEFINE_HTML_ATTRIBUTE(color)
            DEFINE_HTML_ATTRIBUTE(cols)
            DEFINE_HTML_ATTRIBUTE(colspan)
            DEFINE_HTML_ATTRIBUTE(content)
            DEFINE_HTML_ATTRIBUTE(contenteditable)
            DEFINE_HTML_ATTRIBUTE(contextmenu)
            DEFINE_HTML_ATTRIBUTE(controls)
            DEFINE_HTML_ATTRIBUTE(coords)
            DEFINE_HTML_ATTRIBUTE(crossorigin)
            DEFINE_HTML_ATTRIBUTE(csp)
            DEFINE_HTML_ATTRIBUTE(data)
            DEFINE_HTML_ATTRIBUTE(datetime)
            DEFINE_HTML_ATTRIBUTE(decoding)
            DEFINE_HTML_ATTRIBUTE(default)
            DEFINE_HTML_ATTRIBUTE(defer)
            DEFINE_HTML_ATTRIBUTE(dir)
            DEFINE_HTML_ATTRIBUTE(dirname)
            DEFINE_HTML_ATTRIBUTE(disabled)
            DEFINE_HTML_ATTRIBUTE(download)
            DEFINE_HTML_ATTRIBUTE(draggable)
            DEFINE_HTML_ATTRIBUTE(dropzone)
            DEFINE_HTML_ATTRIBUTE(enctype)
            DEFINE_HTML_ATTRIBUTE(enterkeyhint)
            DEFINE_HTML_ATTRIBUTE(for)
            DEFINE_HTML_ATTRIBUTE(form)
            DEFINE_HTML_ATTRIBUTE(formaction)
            DEFINE_HTML_ATTRIBUTE(formenctype)
            DEFINE_HTML_ATTRIBUTE(formmethod)
            DEFINE_HTML_ATTRIBUTE(formnovalidate)
            DEFINE_HTML_ATTRIBUTE(formtarget)
            DEFINE_HTML_ATTRIBUTE(headers)
            DEFINE_HTML_ATTRIBUTE(height)
            DEFINE_HTML_ATTRIBUTE(hidden)
            DEFINE_HTML_ATTRIBUTE(high)
            DEFINE_HTML_ATTRIBUTE(href)
            DEFINE_HTML_ATTRIBUTE(hreflang)
            DEFINE_LABELED_HTML_ATTRIBUTE(http_equiv, "http-equiv")
            DEFINE_HTML_ATTRIBUTE(icon)
            DEFINE_HTML_ATTRIBUTE(id)
            DEFINE_HTML_ATTRIBUTE(importance)
            DEFINE_HTML_ATTRIBUTE(integrity)
            DEFINE_HTML_ATTRIBUTE(intrinsicsize)
            DEFINE_HTML_ATTRIBUTE(inputmode)
            DEFINE_HTML_ATTRIBUTE(ismap)
            DEFINE_HTML_ATTRIBUTE(itemprop)
            DEFINE_HTML_ATTRIBUTE(keytype)
            DEFINE_HTML_ATTRIBUTE(kind)
            DEFINE_HTML_ATTRIBUTE(label)
            DEFINE_HTML_ATTRIBUTE(lang)
            DEFINE_HTML_ATTRIBUTE(language)
            DEFINE_HTML_ATTRIBUTE(loading)
            DEFINE_HTML_ATTRIBUTE(list)
            DEFINE_HTML_ATTRIBUTE(loop)
            DEFINE_HTML_ATTRIBUTE(low)
            DEFINE_HTML_ATTRIBUTE(manifest)
            DEFINE_HTML_ATTRIBUTE(max)
            DEFINE_HTML_ATTRIBUTE(maxlength)
            DEFINE_HTML_ATTRIBUTE(minlength)
            DEFINE_HTML_ATTRIBUTE(media)
            DEFINE_HTML_ATTRIBUTE(method)
            DEFINE_HTML_ATTRIBUTE(min)
            DEFINE_HTML_ATTRIBUTE(multiple)
            DEFINE_HTML_ATTRIBUTE(muted)
            DEFINE_HTML_ATTRIBUTE(name)
            DEFINE_HTML_ATTRIBUTE(novalidate)
            DEFINE_HTML_ATTRIBUTE(open)
            DEFINE_HTML_ATTRIBUTE(optimum)
            DEFINE_HTML_ATTRIBUTE(pattern)
            DEFINE_HTML_ATTRIBUTE(ping)
            DEFINE_HTML_ATTRIBUTE(placeholder)
            DEFINE_HTML_ATTRIBUTE(poster)
            DEFINE_HTML_ATTRIBUTE(preload)
            DEFINE_HTML_ATTRIBUTE(radiogroup)
            DEFINE_HTML_ATTRIBUTE(readonly)
            DEFINE_HTML_ATTRIBUTE(referrerpolicy)
            DEFINE_HTML_ATTRIBUTE(rel)
            DEFINE_HTML_ATTRIBUTE(required)
            DEFINE_HTML_ATTRIBUTE(reversed)
            DEFINE_HTML_ATTRIBUTE(rows)
            DEFINE_HTML_ATTRIBUTE(rowspan)
            DEFINE_HTML_ATTRIBUTE(sandbox)
            DEFINE_HTML_ATTRIBUTE(scope)
            DEFINE_HTML_ATTRIBUTE(scoped)
            DEFINE_HTML_ATTRIBUTE(selected)
            DEFINE_HTML_ATTRIBUTE(shape)
            DEFINE_HTML_ATTRIBUTE(size)
            DEFINE_HTML_ATTRIBUTE(sizes)
            DEFINE_HTML_ATTRIBUTE(slot)
            DEFINE_HTML_ATTRIBUTE(span)
            DEFINE_HTML_ATTRIBUTE(spellcheck)
            DEFINE_HTML_ATTRIBUTE(src)
            DEFINE_HTML_ATTRIBUTE(srcdoc)
            DEFINE_HTML_ATTRIBUTE(srclang)
            DEFINE_HTML_ATTRIBUTE(srcset)
            DEFINE_HTML_ATTRIBUTE(start)
            DEFINE_HTML_ATTRIBUTE(step)
            DEFINE_HTML_ATTRIBUTE(style)
            DEFINE_HTML_ATTRIBUTE(summary)
            DEFINE_HTML_ATTRIBUTE(tabindex)
            DEFINE_HTML_ATTRIBUTE(target)
            DEFINE_HTML_ATTRIBUTE(title)
            DEFINE_HTML_ATTRIBUTE(translate)
            DEFINE_HTML_ATTRIBUTE(type)
            DEFINE_HTML_ATTRIBUTE(usemap)
            DEFINE_HTML_ATTRIBUTE(value)
            DEFINE_HTML_ATTRIBUTE(width)
            DEFINE_HTML_ATTRIBUTE(wrap)
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
    namespace css{
        namespace props{
            DEFINE_LABELED_CSS_ATTRIBUTE(background, "background")
            DEFINE_LABELED_CSS_ATTRIBUTE(backgroundAttachment, "background-attachment")
            DEFINE_LABELED_CSS_ATTRIBUTE(backgroundColor, "background-color")
            DEFINE_LABELED_CSS_ATTRIBUTE(backgroundImage, "background-image")
            DEFINE_LABELED_CSS_ATTRIBUTE(backgroundPosition, "background-position")
            DEFINE_LABELED_CSS_ATTRIBUTE(backgroundRepeat, "background-repeat")
            DEFINE_LABELED_CSS_ATTRIBUTE(border, "border")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderBottom, "border-bottom")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderBottomColor, "border-bottom-color")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderBottomStyle, "border-bottom-style")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderBottomWidth, "border-bottom-width")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderColor, "border-color")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderLeft, "border-left")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderLeftColor, "border-left-color")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderLeftStyle, "border-left-style")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderLeftWidth, "border-left-width")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderRight, "border-right")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderRightColor, "border-right-color")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderRightStyle, "border-right-style")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderRightWidth, "border-right-width")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderStyle, "border-style")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderTop, "border-top")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderTopColor, "border-top-color")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderTopStyle, "border-top-style")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderTopWidth, "border-top-width")
            DEFINE_LABELED_CSS_ATTRIBUTE(borderWidth, "border-width")
            DEFINE_LABELED_CSS_ATTRIBUTE(clear, "clear")
            DEFINE_LABELED_CSS_ATTRIBUTE(clip, "clip")
            DEFINE_LABELED_CSS_ATTRIBUTE(color, "color")
            DEFINE_LABELED_CSS_ATTRIBUTE(cursor, "cursor")
            DEFINE_LABELED_CSS_ATTRIBUTE(display, "display")
            DEFINE_LABELED_CSS_ATTRIBUTE(filter, "filter")
            DEFINE_LABELED_CSS_ATTRIBUTE(cssFloat, "float")
            DEFINE_LABELED_CSS_ATTRIBUTE(font, "font")
            DEFINE_LABELED_CSS_ATTRIBUTE(fontFamily, "font-family")
            DEFINE_LABELED_CSS_ATTRIBUTE(fontSize, "font-size")
            DEFINE_LABELED_CSS_ATTRIBUTE(fontVariant, "font-variant")
            DEFINE_LABELED_CSS_ATTRIBUTE(fontWeight, "font-weight")
            DEFINE_LABELED_CSS_ATTRIBUTE(height, "height")
            DEFINE_LABELED_CSS_ATTRIBUTE(left, "left")
            DEFINE_LABELED_CSS_ATTRIBUTE(letterSpacing, "letter-spacing")
            DEFINE_LABELED_CSS_ATTRIBUTE(lineHeight, "line-height")
            DEFINE_LABELED_CSS_ATTRIBUTE(listStyle, "list-style")
            DEFINE_LABELED_CSS_ATTRIBUTE(listStyleImage, "list-style-image")
            DEFINE_LABELED_CSS_ATTRIBUTE(listStylePosition, "list-style-position")
            DEFINE_LABELED_CSS_ATTRIBUTE(listStyleType, "list-style-type")
            DEFINE_LABELED_CSS_ATTRIBUTE(margin, "margin")
            DEFINE_LABELED_CSS_ATTRIBUTE(marginBottom, "margin-bottom")
            DEFINE_LABELED_CSS_ATTRIBUTE(marginLeft, "margin-left")
            DEFINE_LABELED_CSS_ATTRIBUTE(marginRight, "margin-right")
            DEFINE_LABELED_CSS_ATTRIBUTE(marginTop, "margin-top")
            DEFINE_LABELED_CSS_ATTRIBUTE(opacity, "opacity")
            DEFINE_LABELED_CSS_ATTRIBUTE(overflow, "overflow")
            DEFINE_LABELED_CSS_ATTRIBUTE(padding, "padding")
            DEFINE_LABELED_CSS_ATTRIBUTE(paddingBottom, "padding-bottom")
            DEFINE_LABELED_CSS_ATTRIBUTE(paddingLeft, "padding-left")
            DEFINE_LABELED_CSS_ATTRIBUTE(paddingRight, "padding-right")
            DEFINE_LABELED_CSS_ATTRIBUTE(paddingTop, "padding-top")
            DEFINE_LABELED_CSS_ATTRIBUTE(pageBreakAfter, "page-break-after")
            DEFINE_LABELED_CSS_ATTRIBUTE(pageBreakBefore, "page-break-before")
            DEFINE_LABELED_CSS_ATTRIBUTE(position, "position")
            DEFINE_LABELED_CSS_ATTRIBUTE(strokeDasharray, "stroke-dasharray")
            DEFINE_LABELED_CSS_ATTRIBUTE(strokeDashoffset, "stroke-dashoffset")
            DEFINE_LABELED_CSS_ATTRIBUTE(strokeWidth, "stroke-width")
            DEFINE_LABELED_CSS_ATTRIBUTE(textAlign, "text-align")
            DEFINE_LABELED_CSS_ATTRIBUTE(textDecoration, "text-decoration")
            DEFINE_LABELED_CSS_ATTRIBUTE(textIndent, "text-indent")
            DEFINE_LABELED_CSS_ATTRIBUTE(textTransform, "text-transform")
            DEFINE_LABELED_CSS_ATTRIBUTE(top, "top")
            DEFINE_LABELED_CSS_ATTRIBUTE(verticalAlign, "vertical-align")
            DEFINE_LABELED_CSS_ATTRIBUTE(visibility, "visibility")
            DEFINE_LABELED_CSS_ATTRIBUTE(width, "width")
            DEFINE_LABELED_CSS_ATTRIBUTE(zIndex, "z-index")
        }
    }
}

#endif //RUMAL_DECLARES_H
