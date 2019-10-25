rumal (রুমাল) is a tiny header only HTML/CSS generator C++ library
---
[![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://opensource.org/licenses/BSD-2-Clause)
[![pipeline status](https://gitlab.com/neel.basu/rumal/badges/master/pipeline.svg)](https://gitlab.com/neel.basu/rumal/commits/master) 
[![Documentation Status](https://readthedocs.org/projects/rumal/badge/?version=latest)](https://rumal.readthedocs.io/en/latest/?badge=latest)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6a8f875202b14287ab4261a44227b7b1)](https://www.codacy.com/manual/neel.basu.z/rumal?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=neel/rumal&amp;utm_campaign=Badge_Grade)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/neel/rumal.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/neel/rumal/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/neel/rumal.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/neel/rumal/context:cpp)

Composing HTML/CSS fragments do not involve any heap memory allocation. Both HTML and CSS blocks can be nested.
An HTML block refers to an HTML tag whereas a CSS block refers to a CSS declarations block. Nesting a CSS block
inside another results into nested CSS declaration.

## Basic Example

```cpp
#include <iostream>
#include <rumal/rumal.h>

int main(int argc, char **argv){
    using namespace rumal::html::attrs;
    using namespace rumal::html::tags;
    using namespace rumal;
   
    std::cout << div(id(42) / klass("test"),
                    span(id(43) / klass("test"), "Hello"),
                    span("World")
                ) << std::endl;
    
    std::cout << css::select(".heading", 
                    css::prop("position", "relative") / 
                    css::prop("display", "block"), 
                ) << std::endl;
    return 0;
}

```
## Nested CSS

```cpp
using namespace rumal::css;

select(".main", 
      prop("display", "block") 
    / prop("position", "relative"), 
    select(".heading", 
          prop("display", "block") 
        / prop("position", "relative")
    )
) / select(".container", 
      prop("display", "block") 
    / prop("position", "relative")
);

```

The above example produces the following CSS.

```css
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
```

## HTML attributes

## HTML Tags