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

#ifndef RUMAL_JS_JQUERY_H
#define RUMAL_JS_JQUERY_H

#include "js.hpp"
#include "types.hpp"
#include "dom.hpp"

namespace rumal{
namespace js{
namespace jquery{
 
namespace jq_{
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(add)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(addBack)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(addClass)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(after)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ajaxComplete)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ajaxError)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ajaxSend)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ajaxStart)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ajaxStop)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ajaxSuccess)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(andSelf)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(animate)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(append)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(appendTo)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(attr)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(before)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(bind)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(blur)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(change)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(children)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(clearQueue)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(click)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(clone)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(closest)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(contents)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(conte)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(contextmenu)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(css)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(data)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(dblclick)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(delay)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(delegate)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(dequeue)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(detach)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(die)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(each)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(empty)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(end)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(eq)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(error)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(fadeIn)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(fadeOut)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(fadeTo)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(fadeToggle)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(filter)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(find)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(finish)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(first)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(focus)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(focusin)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(focusout)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(get )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(has)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(hasClass )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(height )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(hide)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(hover)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(html )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(index)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(innerHeight )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(innerWidth )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(insertAfter)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(insertBefore)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(is )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(jque)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(keydown)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(keypress)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(keyup)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(last)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(leng)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(live)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(load)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(map)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mousedown)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mouseenter)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mouseleave)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mousemove)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mouseout)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mouseover)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(mouseup)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(next)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(nextAll)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(nextUntil)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(off)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(offset)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(offsetParent)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(on)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(one)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(outerHeight )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(outerWidth )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(parent)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(parents)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(parentsUntil)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(prepend)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(prependTo)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(prev)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(prevAll)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(prevUntil)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(promise )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(ready)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(remove)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(removeAttr)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(removeClass)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(removeData)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(removeProp)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(replaceAll)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(replaceWith)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(resize)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(scroll)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(scrollLeft )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(scrollTop )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(select)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(serialize)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(serializeArray)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(show)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(siblings)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(size)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(slice)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(slideDown)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(slideToggle)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(slideUp)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(stop)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(submit)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(text )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(toggle)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(toggleClass)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(trigger)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(unbind)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(undelegate)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(unload)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(unwrap)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(val )
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(width)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(wrap)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(wrapAll)
    RUMAL_JS_DECLARE_FOLLOWING_CALLABLE(wrapInner)
}
template <typename T>
struct jq{
   rumal::js::method_<jq_::add_<jq>, T> add;
   rumal::js::method_<jq_::addBack_<jq>, T> addBack;
   rumal::js::method_<jq_::addClass_<jq>, T> addClass;
   rumal::js::method_<jq_::after_<jq>, T> after;
   rumal::js::method_<jq_::ajaxComplete_<jq>, T> ajaxComplete;
   rumal::js::method_<jq_::ajaxError_<jq>, T> ajaxError;
   rumal::js::method_<jq_::ajaxSend_<jq>, T> ajaxSend;
   rumal::js::method_<jq_::ajaxStart_<jq>, T> ajaxStart;
   rumal::js::method_<jq_::ajaxStop_<jq>, T> ajaxStop;
   rumal::js::method_<jq_::ajaxSuccess_<jq>, T> ajaxSuccess;
   rumal::js::method_<jq_::andSelf_<jq>, T> andSelf;
   rumal::js::method_<jq_::animate_<jq>, T> animate;
   rumal::js::method_<jq_::append_<jq>, T> append;
   rumal::js::method_<jq_::appendTo_<jq>, T> appendTo;
   rumal::js::method_<jq_::attr_<jq>, T> attr;
   rumal::js::method_<jq_::before_<jq>, T> before;
   rumal::js::method_<jq_::bind_<jq>, T> bind;
   rumal::js::method_<jq_::blur_<jq>, T> blur;
   rumal::js::method_<jq_::change_<jq>, T> change;
   rumal::js::method_<jq_::children_<jq>, T> children;
   rumal::js::method_<jq_::clearQueue_<jq>, T> clearQueue;
    rumal::js::method_<jq_::click_<jq>, T> click;
   rumal::js::method_<jq_::clone_<jq>, T> clone;
   rumal::js::method_<jq_::closest_<jq>, T> closest;
   rumal::js::method_<jq_::contents_<jq>, T> contents;
   rumal::js::method_<jq_::conte_<jq>, T> conte;
   rumal::js::method_<jq_::contextmenu_<jq>, T> contextmenu;
   rumal::js::method_<jq_::css_<jq>, T> css;
   rumal::js::method_<jq_::data_<jq>, T> data;
   rumal::js::method_<jq_::dblclick_<jq>, T> dblclick;
   rumal::js::method_<jq_::delay_<jq>, T> delay;
   rumal::js::method_<jq_::delegate_<jq>, T> delegate;
   rumal::js::method_<jq_::dequeue_<jq>, T> dequeue;
   rumal::js::method_<jq_::detach_<jq>, T> detach;
   rumal::js::method_<jq_::die_<jq>, T> die;
   rumal::js::method_<jq_::each_<jq>, T> each;
   rumal::js::method_<jq_::empty_<jq>, T> empty;
   rumal::js::method_<jq_::end_<jq>, T> end;
   rumal::js::method_<jq_::eq_<jq>, T> eq;
   rumal::js::method_<jq_::error_<jq>, T> error;
   rumal::js::method_<jq_::fadeIn_<jq>, T> fadeIn;
   rumal::js::method_<jq_::fadeOut_<jq>, T> fadeOut;
   rumal::js::method_<jq_::fadeTo_<jq>, T> fadeTo;
   rumal::js::method_<jq_::fadeToggle_<jq>, T> fadeToggle;
   rumal::js::method_<jq_::filter_<jq>, T> filter;
   rumal::js::method_<jq_::find_<jq>, T> find;
   rumal::js::method_<jq_::finish_<jq>, T> finish;
   rumal::js::method_<jq_::first_<jq>, T> first;
   rumal::js::method_<jq_::focus_<jq>, T> focus;
   rumal::js::method_<jq_::focusin_<jq>, T> focusin;
   rumal::js::method_<jq_::focusout_<jq>, T> focusout;
   rumal::js::method_<jq_::get_<rumal::js::dom::Element>, T> get ;
   rumal::js::method_<jq_::has_<jq>, T> has;
   rumal::js::method_<jq_::hasClass_< rumal::js::types::Boolean>, T> hasClass ;
   rumal::js::method_<jq_::height_<rumal::js::types::Number>, T> height ;
    rumal::js::method_<jq_::hide_<jq>, T> hide;
   rumal::js::method_<jq_::hover_<jq>, T> hover;
   rumal::js::method_<jq_::html_<rumal::js::types::String>, T> html ;
   rumal::js::method_<jq_::index_<jq>, T> index;
   rumal::js::method_<jq_::innerHeight_<rumal::js::types::Number>, T> innerHeight ;
   rumal::js::method_<jq_::innerWidth_<rumal::js::types::Number>, T> innerWidth ;
   rumal::js::method_<jq_::insertAfter_<jq>, T> insertAfter;
   rumal::js::method_<jq_::insertBefore_<jq>, T> insertBefore;
   rumal::js::method_<jq_::is_<rumal::js::types::Boolean>, T> is ;
   rumal::js::method_<jq_::jque_<jq>, T> jque;
   rumal::js::method_<jq_::keydown_<jq>, T> keydown;
   rumal::js::method_<jq_::keypress_<jq>, T> keypress;
   rumal::js::method_<jq_::keyup_<jq>, T> keyup;
   rumal::js::method_<jq_::last_<jq>, T> last;
   rumal::js::method_<jq_::leng_<jq>, T> leng;
   rumal::js::method_<jq_::live_<jq>, T> live;
   rumal::js::method_<jq_::load_<jq>, T> load;
   rumal::js::method_<jq_::map_<jq>, T> map;
   rumal::js::method_<jq_::mousedown_<jq>, T> mousedown;
   rumal::js::method_<jq_::mouseenter_<jq>, T> mouseenter;
   rumal::js::method_<jq_::mouseleave_<jq>, T> mouseleave;
   rumal::js::method_<jq_::mousemove_<jq>, T> mousemove;
   rumal::js::method_<jq_::mouseout_<jq>, T> mouseout;
   rumal::js::method_<jq_::mouseover_<jq>, T> mouseover;
   rumal::js::method_<jq_::mouseup_<jq>, T> mouseup;
   rumal::js::method_<jq_::next_<jq>, T> next;
   rumal::js::method_<jq_::nextAll_<jq>, T> nextAll;
   rumal::js::method_<jq_::nextUntil_<jq>, T> nextUntil;
   rumal::js::method_<jq_::off_<jq>, T> off;
   rumal::js::method_<jq_::offset_<jq>, T> offset;
   rumal::js::method_<jq_::offsetParent_<jq>, T> offsetParent;
   rumal::js::method_<jq_::on_<jq>, T> on;
   rumal::js::method_<jq_::one_<jq>, T> one;
   rumal::js::method_<jq_::outerHeight_<rumal::js::types::Number>, T> outerHeight ;
   rumal::js::method_<jq_::outerWidth_<rumal::js::types::Number>, T> outerWidth ;
   rumal::js::method_<jq_::parent_<jq>, T> parent;
   rumal::js::method_<jq_::parents_<jq>, T> parents;
   rumal::js::method_<jq_::parentsUntil_<jq>, T> parentsUntil;
   rumal::js::method_<jq_::prepend_<jq>, T> prepend;
   rumal::js::method_<jq_::prependTo_<jq>, T> prependTo;
   rumal::js::method_<jq_::prev_<jq>, T> prev;
   rumal::js::method_<jq_::prevAll_<jq>, T> prevAll;
   rumal::js::method_<jq_::prevUntil_<jq>, T> prevUntil;
//     rumal::js::method_<jq_::promise_<Deffered>, T> promise ;
    rumal::js::method_<jq_::ready_<jq>, T> ready;
   rumal::js::method_<jq_::remove_<jq>, T> remove;
   rumal::js::method_<jq_::removeAttr_<jq>, T> removeAttr;
   rumal::js::method_<jq_::removeClass_<jq>, T> removeClass;
   rumal::js::method_<jq_::removeData_<jq>, T> removeData;
   rumal::js::method_<jq_::removeProp_<jq>, T> removeProp;
   rumal::js::method_<jq_::replaceAll_<jq>, T> replaceAll;
   rumal::js::method_<jq_::replaceWith_<jq>, T> replaceWith;
   rumal::js::method_<jq_::resize_<jq>, T> resize;
   rumal::js::method_<jq_::scroll_<jq>, T> scroll;
   rumal::js::method_<jq_::scrollLeft_<rumal::js::types::Number>, T> scrollLeft ;
   rumal::js::method_<jq_::scrollTop_<rumal::js::types::Number>, T> scrollTop ;
   rumal::js::method_<jq_::select_<jq>, T> select;
   rumal::js::method_<jq_::serialize_<jq>, T> serialize;
   rumal::js::method_<jq_::serializeArray_<jq>, T> serializeArray;
   rumal::js::method_<jq_::show_<jq>, T> show;
   rumal::js::method_<jq_::siblings_<jq>, T> siblings;
   rumal::js::method_<jq_::size_<jq>, T> size;
   rumal::js::method_<jq_::slice_<jq>, T> slice;
   rumal::js::method_<jq_::slideDown_<jq>, T> slideDown;
   rumal::js::method_<jq_::slideToggle_<jq>, T> slideToggle;
   rumal::js::method_<jq_::slideUp_<jq>, T> slideUp;
   rumal::js::method_<jq_::stop_<jq>, T> stop;
   rumal::js::method_<jq_::submit_<jq>, T> submit;
   rumal::js::method_<jq_::text_<rumal::js::types::String>, T> text ;
   rumal::js::method_<jq_::toggle_<jq>, T> toggle;
   rumal::js::method_<jq_::toggleClass_<jq>, T> toggleClass;
   rumal::js::method_<jq_::trigger_<jq>, T> trigger;
   rumal::js::method_<jq_::unbind_<jq>, T> unbind;
   rumal::js::method_<jq_::undelegate_<jq>, T> undelegate;
   rumal::js::method_<jq_::unload_<jq>, T> unload;
   rumal::js::method_<jq_::unwrap_<jq>, T> unwrap;
   rumal::js::method_<jq_::val_<rumal::js::types::String>, T> val ;
   rumal::js::method_<jq_::width_<jq>, T> width;
   rumal::js::method_<jq_::wrap_<jq>, T> wrap;
   rumal::js::method_<jq_::wrapAll_<jq>, T> wrapAll;
   rumal::js::method_<jq_::wrapInner_<jq>, T> wrapInner;
    
    jq(const T& pkt): 
       add(pkt),
       addBack(pkt),
       addClass(pkt),
       after(pkt),
       ajaxComplete(pkt),
       ajaxError(pkt),
       ajaxSend(pkt),
       ajaxStart(pkt),
       ajaxStop(pkt),
       ajaxSuccess(pkt),
       andSelf(pkt),
       animate(pkt),
       append(pkt),
       appendTo(pkt),
       attr(pkt),
       before(pkt),
       bind(pkt),
       blur(pkt),
       change(pkt),
       children(pkt),
       clearQueue(pkt),
       click(pkt),
       clone(pkt),
       closest(pkt),
       contents(pkt),
       conte(pkt),
       contextmenu(pkt),
       css(pkt),
       data(pkt),
       dblclick(pkt),
       delay(pkt),
       delegate(pkt),
       dequeue(pkt),
       detach(pkt),
       die(pkt),
       each(pkt),
       empty(pkt),
       end(pkt),
       eq(pkt),
       error(pkt),
       fadeIn(pkt),
       fadeOut(pkt),
       fadeTo(pkt),
       fadeToggle(pkt),
       filter(pkt),
       find(pkt),
       finish(pkt),
       first(pkt),
       focus(pkt),
       focusin(pkt),
       focusout(pkt),
       get (pkt),
       has(pkt),
       hasClass (pkt),
       height (pkt),
       hide(pkt),
       hover(pkt),
       html (pkt),
       index(pkt),
       innerHeight (pkt),
       innerWidth (pkt),
       insertAfter(pkt),
       insertBefore(pkt),
       is (pkt),
       jque(pkt),
       keydown(pkt),
       keypress(pkt),
       keyup(pkt),
       last(pkt),
       leng(pkt),
       live(pkt),
       load(pkt),
       map(pkt),
       mousedown(pkt),
       mouseenter(pkt),
       mouseleave(pkt),
       mousemove(pkt),
       mouseout(pkt),
       mouseover(pkt),
       mouseup(pkt),
       next(pkt),
       nextAll(pkt),
       nextUntil(pkt),
       off(pkt),
       offset(pkt),
       offsetParent(pkt),
       on(pkt),
       one(pkt),
       outerHeight (pkt),
       outerWidth (pkt),
       parent(pkt),
       parents(pkt),
       parentsUntil(pkt),
       prepend(pkt),
       prependTo(pkt),
       prev(pkt),
       prevAll(pkt),
       prevUntil(pkt),
//         promise (pkt),
        ready(pkt),
        remove(pkt),
        removeAttr(pkt),
        removeClass(pkt),
        removeData(pkt),
        removeProp(pkt),
        replaceAll(pkt),
        replaceWith(pkt),
        resize(pkt),
        scroll(pkt),
        scrollLeft (pkt),
        scrollTop (pkt),
        select(pkt),
        serialize(pkt),
        serializeArray(pkt),
        show(pkt),
        siblings(pkt),
        size(pkt),
        slice(pkt),
        slideDown(pkt),
        slideToggle(pkt),
        slideUp(pkt),
        stop(pkt),
        submit(pkt),
        text (pkt),
        toggle(pkt),
        toggleClass(pkt),
        trigger(pkt),
        unbind(pkt),
        undelegate(pkt),
        unload(pkt),
        unwrap(pkt),
        val (pkt),
        width(pkt),
        wrap(pkt),
        wrapAll(pkt),
        wrapInner(pkt){
                
        }

};
struct jQuery_: rumal::js::callable_<jQuery_, jq>{
    jQuery_(): rumal::js::callable_<jQuery_, jq>("jQuery"){}
};
    
}    
}
}

// ["currentTarget","data","delegateTarget","isDefaultPrevented()","isImmediatePropagationStopped()","isPropagationStopped()","metaKey","namespace","pageX","pageY","preventDefault()","relatedTarget","result","stopImmediatePropagation()","stopPropagation()","target","timeStamp","type","which"]

#endif // RUMAL_JS_JQUERY_H
