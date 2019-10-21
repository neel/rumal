rumal (রুমাল)
=============

rumal (রুমাল) is a tiny header only single file HTML/CSS generator C++ library

|BSD license| |Pipeline Status| |Codacy Badge| |Total Alerts| |Language grade: C/C++|

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


Example
-------

.. code-block:: c++

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
