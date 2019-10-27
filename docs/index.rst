rumal (রুমাল)
=============

**rumal** (রুমাল) is a tiny header only single file HTML/CSS generator C++ library.

|BSD license| |Pipeline Status| |ReadTheDocs| |Codacy Badge| |Total Alerts| |Language grade: C/C++|

.. |BSD license| image:: https://img.shields.io/badge/License-BSD%202--Clause-orange.svg
    :target: https://opensource.org/licenses/BSD-2-Clause

.. |Pipeline Status| image:: https://gitlab.com/neel.basu/rumal/badges/master/pipeline.svg
    :target: https://gitlab.com/neel.basu/rumal/commits/master

.. |Codacy Badge| image:: https://api.codacy.com/project/badge/Grade/6a8f875202b14287ab4261a44227b7b1
    :target: https://www.codacy.com/manual/neel.basu.z/rumal?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=neel/rumal&amp;utm_campaign=Badge_Grade

.. |Total Alerts| image:: https://img.shields.io/lgtm/alerts/g/neel/rumal.svg?logo=lgtm&logoWidth=18
    :target: https://lgtm.com/projects/g/neel/rumal/alerts/

.. |Language grade: C/C++| image:: https://img.shields.io/lgtm/grade/cpp/g/neel/rumal.svg?logo=lgtm&logoWidth=18
    :target: https://lgtm.com/projects/g/neel/rumal/context:cpp
    
.. |ReadTheDocs| image:: https://readthedocs.org/projects/rumal/badge/?version=latest
    :target: https://rumal.readthedocs.io/en/latest/?badge=latest


----

    Composing HTML/CSS fragments do not involve any heap memory allocation. Both HTML and CSS blocks can be nested. 
    An HTML block refers to an HTML tag whereas a CSS block refers to a CSS declarations block. Nesting a CSS block
    inside another results into nested CSS declaration.

Basic Example
--------------

.. code-block:: c++

    #include <iostream>
    #include <rumal/rumal.hpp>

    int main(int argc, char **argv){
        using namespace rumal::html::attrs;
        using namespace rumal::html::tags;
        using namespace rumal::css;
        using namespace rumal::css::props;
    
        std::cout << div(_id(42) / _class("test"),
                        span(_id(43) / _class("test"), "Hello"),
                        span("World")
                    ) << std::endl;
        
        std::cout << select(".heading", 
                        position("relative") / 
                        display("block"), 
                    ) << std::endl;
        return 0;
    }

Nested CSS
-----------

.. code-block:: c++

    using namespace rumal::css;
    using namespace rumal::css::props;

    select(".main", 
        display("block") 
        / position("relative"), 
        select(".heading", 
            display("block") 
            / position("relative")
        )
    ) / select(".container", 
        display("block") 
        / position("relative")
    );

The above example produces the following CSS.

.. code-block:: css

    .container{
        position: relative; 
        display: block;
    }

    .main{
        position: relative;
        display: block;
    }

    .main > .heading{
        position: relative;
        display: block;
    }

HTML Tag
---------

To declare HTML tags use the macro `DEFINE_HTML_TAG` 

.. code-block:: c++

    namespace rumal{
        namespace html{
            namespace tags{
                DEFINE_HTML_TAG(div) 
            }
        }
    }

The above example will declare a tag named `div`. The macro results into two function overloads named `div`

.. code-blocks:: c++

    template <typename Args, typename... T>                     
    auto div(const Args& args, const T&... elems){             
        return tag<Args, T...>("div", args, elems...);          
    }                                                           
    template <typename... T>                                    
    auto div(const T&... elems){                               
        return tag<void, T...>("div", elems...);                
    }

HTML Attributes
----------------

HTML attributes are declared through two macros `DEFINE_HTML_ATTRIBUTE` and `DEFINE_LABELED_HTML_ATTRIBUTE`

.. code-block:: c++

    namespace rumal{
        namespace html{
            namespace attrs{
                DEFINE_HTML_ATTRIBUTE(id)
                DEFINE_LABELED_HTML_ATTRIBUTE(klass, "class")
            }
        }
    }

The above results into the following functions

.. code-blocks:: c++

    template <typename T> 
    auto _id(T value){
        return rumal::html::attr("id", value);
    }
    template <typename T> 
    auto klass(T value){
        return rumal::html::attr("class", value);
    }

Use `DEFINE_HTML_ATTRIBUTE` to define attributes that do not conflict with C++ keywords or existing functions. 
Use `DEFINE_LABELED_HTML_ATTRIBUTE` when there is a conflict (e.g. class). Or use `html::attr("attribute_name", value);` directly
