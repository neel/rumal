#include <iostream>
#include <rumal/rumal.h>

int main(int argc, char **argv){
    using namespace rumal::html::attrs;
    using namespace rumal::html::tags;
    using namespace rumal;
   
    auto content = div(_id(42) / _class("test"),
                        span(_id(42) / _width(42.042) / _height(42.042) / _class("test"),
                            42
                        ),
                        span(
                            84
                        )
                    );
    std::cout << content << std::endl;
   
    std::cout << span(84) << std::endl;
    std::cout << span(_id(42), 84) << std::endl;
    std::cout << span(_id(42) / _class("test"), 84) << std::endl;
    std::cout << span(_id(42) / _width(42.042) / _height(42.042) / _class("test"), 84) << std::endl;
//     std::cout << span() << std::endl;
    std::cout << span(_id(42)) << std::endl;
    std::cout << span(_id(42) / _class("test")) << std::endl;
    std::cout << span(_id(42) / _width(42.042) / _height(42.042) / _class("test")) << std::endl;
    
    std::cout << css::select(".heading",
                    css::prop("position", "relative") /
                    css::props::display("block"),
                    css::select(".content",
                        css::prop("position", "relative") /
                        css::prop("display", "block")
                    )
                )/ css::select(".main",
                     css::prop("position", "relative") /
                     css::prop("display", "block")
                )/ css::select(".main2",
                               css::prop("position", "relative") /
                               css::prop("display", "block")
                );              

    std::cout << "Hello, world!" << std::endl;
    return 0;
}
