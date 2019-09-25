rumal (রুমাল) is a tiny header only single file HTML/CSS generator C++ library
---

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
