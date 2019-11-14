#include <iostream>
#include <rumal/rumal.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv){
    using namespace rumal::html::attrs;
    using namespace rumal::html::tags;
    using namespace rumal::css;
    using namespace rumal::css::props;
   
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
    
    std::cout << select(".heading",
                    position("relative") /
                    display("block"),
                    select(".content",
                        position("relative") /
                        display("block")
                    )
                )/ select(".main",
                    position("relative") /
                    display("block")
                )/ select(".main2",
                    position("relative") /
                    display("block")
                );              

    std::cout << "Hello, world!" << std::endl;
    
    return 0;
}
