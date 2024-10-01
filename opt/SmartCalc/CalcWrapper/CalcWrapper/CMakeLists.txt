# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_library (CalcWrapper SHARED "CalcWrapper.cpp" "CalcWrapper.h" 
"Model/rpn.cpp" "Model/rpn.h"
"Model/calculate.cpp" "Model/calculate.h"
"Model/calculatedeposit.cpp" "Model/calculatedeposit.h"
"Model/parse.cpp" "Model/parse.h"
"Model/validate.cpp" "Model/validate.h"
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CalcWrapper PROPERTY CXX_STANDARD 17)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
