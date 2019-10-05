rumal (রুমাল) is a tiny header only single file HTML/CSS generator C++ library
---
[![pipeline status](https://gitlab.com/neel.basu/rumal/badges/master/pipeline.svg)](https://gitlab.com/neel.basu/rumal/commits/master) 
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6a8f875202b14287ab4261a44227b7b1)](https://www.codacy.com/manual/neel.basu.z/rumal?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=neel/rumal&amp;utm_campaign=Badge_Grade)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/neel/rumal.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/neel/rumal/alerts/)

## Example

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
