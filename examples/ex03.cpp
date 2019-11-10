#include <iostream>
#include <rumal/rumal.hpp>
#include <boost/lexical_cast.hpp>
#include <rumal/types.hpp>
#include <rumal/dom.hpp>
#include <rumal/jquery.hpp>

using namespace rumal::js;
using namespace rumal::js::types;
using namespace rumal::js::dom;
using namespace rumal::js::jquery;

struct number_: rumal::js::callable_<number_, Number>{
    number_(): rumal::js::callable_<number_, Number>("num"){}
};

struct str_: rumal::js::callable_<str_, String>{
    str_(): rumal::js::callable_<str_, String>("str"){}
};

struct node_list_: rumal::js::callable_<node_list_, NodeList>{
    node_list_(): rumal::js::callable_<node_list_, NodeList>("node_list"){}
};

int main(){
//     number_ num;
//     str_ str;
//     node_list_ node_list;
    
//     
//     std::cout << num().toFixed(10) << std::endl;
//     std::cout << num().EPSILON().toFixed(12) << std::endl;
//     std::cout << str().toLowerCase() << std::endl;
//     std::cout << node_list().item(0).childNodes[0].childNodes.length << std::endl;
    
    assignable<Node> document("document");
    assignable<Node> y("y");
    jQuery_ jQuery;
//     std::cout <<
//         jQuery(document).ready(function()[
//             jQuery(".hallo").click(function()[
//                 jQuery(y).hide()
//                 // jQuery(".hello").hide()
//             ])
//         ])
//     << std::endl;
    
    auto script = jQuery(document).ready(function()[
            jQuery(".hallo").click(function()[
                jQuery(y).hide(),
                jQuery(".hello").hide()
            ])
        ]);
    
    std::cout << script << std::endl;
    
    return 0;
}
