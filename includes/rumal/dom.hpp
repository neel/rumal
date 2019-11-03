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

#ifndef RUMAL_JS_DOMS_H
#define RUMAL_JS_DOMS_H

#include "js.hpp"
#include "types.hpp"

namespace rumal{
namespace js{
namespace dom{
    
template <typename T>
struct Node;

template <typename T>
struct NodeList;

template <typename T>
struct Element;

template <typename T>
struct NamedNodeMap;

template <typename T>
struct DOMTokenList;

template <typename T>
struct HTMLCollection;

template <typename T>
struct Attr;

namespace NodeList_{
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(item, Node)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(entries, rumal::js::types::Array)
    RUMAL_JS_DECLARE_CALLABLE(forEach)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(keys, rumal::js::types::Array)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(values, rumal::js::types::Array)
}
template <typename T>
struct NodeList: rumal::js::iterable_<T, Node>{
    rumal::js::property_<rumal::js::types::Number, T> length;
    rumal::js::method_<NodeList_::item_, T> item;
    rumal::js::method_<NodeList_::entries_, T> entries;
    rumal::js::method_<NodeList_::forEach_, T> forEach;
    rumal::js::method_<NodeList_::keys_, T> keys;
    rumal::js::method_<NodeList_::values_, T> values;
    
    NodeList(const T& pkt): rumal::js::iterable_<T, Node>(pkt), 
        length("length", pkt), item(pkt), entries(pkt), forEach(pkt), keys(pkt), values(pkt){}
};
    
namespace Node_{
    RUMAL_JS_DECLARE_CALLABLE(appendChild)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(cloneNode, Node)
    RUMAL_JS_DECLARE_CALLABLE(contains)
    RUMAL_JS_DECLARE_CALLABLE(hasChildNodes)
    RUMAL_JS_DECLARE_CALLABLE(insertBefore)
    RUMAL_JS_DECLARE_CALLABLE(isEqualNode)
    RUMAL_JS_DECLARE_CALLABLE(isSameNode)
    RUMAL_JS_DECLARE_CALLABLE(normalize)
    RUMAL_JS_DECLARE_CALLABLE(removeChild)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(replaceChild, Node)
}
template <typename T>
struct Node{
    rumal::js::member_<Node, T> firstChild;
    rumal::js::property_<rumal::js::types::Number, T> isConnected;
    rumal::js::member_<Node, T> lastChild;
    rumal::js::member_<Node, T> previousSibling;
    rumal::js::member_<Node, T> nextSibling;
    rumal::js::property_<rumal::js::types::String, T> nodeName;
    rumal::js::property_<rumal::js::types::Number, T> nodeType;
    rumal::js::property_<rumal::js::types::String, T> nodeValue;
    rumal::js::member_<Node, T> parentNode;
    rumal::js::member_<Element, T> parentElement;
    rumal::js::property_<NodeList, T> childNodes;
    
    Node(const T& pkt): firstChild("firstChild", pkt), isConnected("isConnected", pkt), lastChild("lastChild", pkt), previousSibling("previousSibling", pkt), nextSibling("nextSibling", pkt), 
        nodeName("nodeName", pkt), nodeType("nodeType", pkt), nodeValue("nodeValue", pkt), parentNode("parentNode", pkt), parentElement("parentElement", pkt), childNodes("childNodes", pkt){}
};

namespace Element_{
    RUMAL_JS_DECLARE_CALLABLE(addEventListener)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(closest)
    RUMAL_JS_DECLARE_CALLABLE(dispatchEvent)
}
template <typename T>
struct Element: Node<T>{
    rumal::js::property_<NamedNodeMap, T> attributes;
    rumal::js::property_<DOMTokenList, T> classList;
    rumal::js::property_<rumal::js::types::String, T> className;
    rumal::js::property_<rumal::js::types::Number, T> clientHeight;
    rumal::js::property_<rumal::js::types::Number, T> clientLeft;
    rumal::js::property_<rumal::js::types::Number, T> clientTop;
    rumal::js::property_<rumal::js::types::Number, T> clientWidth;
    rumal::js::property_<rumal::js::types::String, T> computedName;
    rumal::js::property_<rumal::js::types::String, T> computedRole;
    rumal::js::property_<rumal::js::types::String, T> id;
    rumal::js::property_<rumal::js::types::String, T> innerHTML;
    rumal::js::property_<rumal::js::types::String, T> localName;
    rumal::js::member_<Element, T> nextElementSibling;
    rumal::js::property_<rumal::js::types::String, T> outerHTML;
    rumal::js::member_<Element, T> previousElementSibling;
    rumal::js::property_<rumal::js::types::Number, T> scrollHeight;
    rumal::js::property_<rumal::js::types::Number, T> scrollLeft;
    rumal::js::property_<rumal::js::types::Number, T> scrollTop;
    rumal::js::property_<rumal::js::types::Number, T> scrollWidth;
    rumal::js::property_<rumal::js::types::String, T> tagName;
    
    
    
    Element(const T& pkt): Node<T>(pkt), 
        attributes("attributes", pkt), classList("classList", pkt), className("className", pkt), clientHeight("clientHeight", pkt), clientLeft("clientLeft", pkt), clientTop("clientTop", pkt), clientWidth("clientWidth", pkt),
        computedName("computedName", pkt), computedRole("computedRole", pkt), id("id", pkt), innerHTML("innerHTML", pkt), localName("localName", pkt), nextElementSibling("nextElementSibling", pkt), outerHTML("outerHTML", pkt), previousElementSibling("previousElementSibling", pkt),
        scrollHeight("scrollHeight", pkt), scrollLeft("scrollLeft", pkt), scrollTop("scrollTop", pkt), scrollWidth("scrollWidth", pkt), tagName("tagName", pkt)
        {}
};

namespace NamedNodeMap_{
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(getNamedItem, Attr)
    RUMAL_JS_DECLARE_CALLABLE(setNamedItem)
    RUMAL_JS_DECLARE_CALLABLE(removeNamedItem)
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(item, Attr)
}
template <typename T>
struct NamedNodeMap: rumal::js::iterable_<T, Attr>{
    rumal::js::property_<rumal::js::types::Number, T> length;
    
    rumal::js::method_<NamedNodeMap_::getNamedItem_, T> getNamedItem;
    rumal::js::method_<NamedNodeMap_::setNamedItem_, T> setNamedItem;
    rumal::js::method_<NamedNodeMap_::removeNamedItem_, T> removeNamedItem;
    rumal::js::method_<NamedNodeMap_::item_, T> item;
    
    NamedNodeMap(const T& pkt): length("length", pkt), getNamedItem(pkt), setNamedItem(pkt), removeNamedItem(pkt), item(pkt){}
};

namespace DOMTokenList_{
    RUMAL_JS_DECLARE_RETURNING_CALLABLE(item, rumal::js::types::String)
    RUMAL_JS_DECLARE_CALLABLE(contains)
    RUMAL_JS_DECLARE_CALLABLE(add)
    RUMAL_JS_DECLARE_CALLABLE(remove)
    RUMAL_JS_DECLARE_CALLABLE(replace)
    RUMAL_JS_DECLARE_CALLABLE(supports)
    RUMAL_JS_DECLARE_CALLABLE(toggle)
    RUMAL_JS_DECLARE_CALLABLE(entries)
    RUMAL_JS_DECLARE_CALLABLE(keys)
    RUMAL_JS_DECLARE_CALLABLE(forEach)
    RUMAL_JS_DECLARE_CALLABLE(values)
}
template <typename T>
struct DOMTokenList: rumal::js::iterable_<T, rumal::js::types::String>{
    rumal::js::property_<rumal::js::types::Number, T> length;
    rumal::js::property_<rumal::js::types::String, T> value;
    
    rumal::js::method_<DOMTokenList_::item_, T> item;
    rumal::js::method_<DOMTokenList_::contains_, T> contains;
    rumal::js::method_<DOMTokenList_::add_, T> add;
    rumal::js::method_<DOMTokenList_::remove_, T> remove;
    rumal::js::method_<DOMTokenList_::replace_, T> replace;
    rumal::js::method_<DOMTokenList_::supports_, T> supports;
    rumal::js::method_<DOMTokenList_::toggle_, T> toggle;
    rumal::js::method_<DOMTokenList_::entries_, T> entries;
    rumal::js::method_<DOMTokenList_::keys_, T> keys;
    rumal::js::method_<DOMTokenList_::forEach_, T> forEach;
    rumal::js::method_<DOMTokenList_::values_, T> values;
    
    DOMTokenList(const T& pkt): rumal::js::iterable_<T, rumal::js::types::String>(pkt), length("length", pkt), value("value", pkt),
        item(pkt), contains(pkt), add(pkt), remove(pkt), replace(pkt), supports(pkt), toggle(pkt), entries(pkt), keys(pkt), forEach(pkt), values(pkt){}
};

template <typename T>
struct Attr{};
    
}
}
}

#endif // RUMAL_JS_DOMS_H
