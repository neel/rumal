#include <iostream>
#include <rumal/rumal.h>

int main(int argc, char **argv){
    using namespace rumal::html::attrs;
    using namespace rumal::html::tags;
    using namespace rumal;
   
    auto content = div(id(42) / klass("test"),
                        span(id(42) / width(42.042) / height(42.042) / klass("test"),
                            42
                        ),
                        span(
                            84
                        )
                    );
    std::cout << content << std::endl;
   
    std::cout << span(84) << std::endl;
    std::cout << span(id(42), 84) << std::endl;
    std::cout << span(id(42) / klass("test"), 84) << std::endl;
    std::cout << span(id(42) / width(42.042) / height(42.042) / klass("test"), 84) << std::endl;
//     std::cout << span() << std::endl;
    std::cout << span(id(42)) << std::endl;
    std::cout << span(id(42) / klass("test")) << std::endl;
    std::cout << span(id(42) / width(42.042) / height(42.042) / klass("test")) << std::endl;
    
    std::cout << css::select(".heading", 
                    css::prop("position", "relative") / 
                    css::prop("display", "block"), 
                    rumal::css::select(".content", 
                        css::prop("position", "relative") / 
                        css::prop("display", "block")
                    )
                );
   
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
