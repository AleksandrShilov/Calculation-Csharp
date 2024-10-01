CPP = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm

# Конфигурация сборки Avalonia (Debug или Release)
CONFIGURATION := Debug

ifeq ($(OS),Windows_NT)
STD = clang++ --std=c++17

# Visual Studio 16 2019 -A x64 "D:\Projects\Calculation C#\Calculation-C-\CalcWrapper"
# MinGW Makefiles ..
CMAKE = cmake -G "Visual Studio 17 2022" ..

TESTCOVERAGE = 

WASH=del -recurse *.o *.a *.exe CalcWrapper\build publish

# Путь к файлу решения Avalonia
SOLUTION_FILE := SimpleCalc\SimpleCalc.sln

# Папка для сборки
BUILD_DIR := CalcWrapper\build

SRC_DIR := CalcWrapper\build\CalcWrapper\Release

COPY= xcopy /y /i $(SRC_DIR)\CalcWrapper.dll publish

NAME_DLL = CalcWrapper.dll

DELETE_BUILD = 

else # Linux
STD = g++ --std=c++17

CMAKE = cmake ..

TESTCOVERAGE = -fprofile-arcs -ftest-coverage

WASH=rm -rf *.o *.a *.out *.log *.aux *.dvi *.toc *css *gcno *gcda CPPLINT.cfg *tgz *.html man_ru report .clang-format CalcWrapper\build publish

# Путь к файлу решения Avalonia
SOLUTION_FILE := SimpleCalc/SimpleCalc.sln

# Папка для сборки
BUILD_DIR := CalcWrapper/build

SRC_DIR := CalcWrapper/build/CalcWrapper

COPY = cp $(SRC_DIR)/libCalcWrapper.so publish

NAME_DLL = libCalcWrapper.so

LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s

TEST = -lgtest -lgmock -pthread --coverage

DELETE_BUILD = rm -rf

# MACOS
#LEAKS=CK_FORK=no leaks --atExit --
#TEST =  -lgtest -fsanitize=address --coverage
endif

# Avalonia
buildCmake:
ifneq ($(OS),Windows_NT)
	$(DELETE_BUILD) $(BUILD_DIR)
endif
	mkdir $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(CMAKE)
	@cmake --build $(BUILD_DIR) --config Release

buildAvalonia:
	@dotnet build $(SOLUTION_FILE) -c $(CONFIGURATION)

# Установка проекта Avalonia Linux
installLinux: buildCmake
	@dotnet publish -r linux-x64 -p:TargetFramework=net7.0 $(SOLUTION_FILE) -c $(CONFIGURATION) -o publish
	chmod 777 publish
	$(COPY)

# Установка проекта Avalonia Windows
installWindows: buildCmake
	@dotnet publish -r win-x64 -p:TargetFramework=net7.0 $(SOLUTION_FILE) -c $(CONFIGURATION) -o publish
	$(COPY)


# C++ core
all: clean install


dvi:
	makeinfo --html --no-warn --no-validate --force ./man_ru.texi


dist:
	rm -rf MyCalc
	mkdir MyCalc
	cp Makefile CalcWrapper/CalcWrapper/Model/* *.h *.txt *.texi *.cpp *.user MyCalc/
	tar -zcvf ./MyCalc.tar.tgz ./MyCalc
	rm -rf MyCalc/


read: read.o parse.o validate.o calculate.o rpn.o calculatedeposit.o
	$(STD) $^ -o read.out && ./read.out


gcov_report: test
	./test.out
	mkdir report
	gcovr -r ../ -e ../googletest-1.10.x --html --html-details -o report/result.html
	open report/result.html


test: parse.o validate.o calculate.o rpn.o calculatedeposit.o
	g++ test.cpp $^ -o test.out $(TEST)
	./test.out


test.o: test.cpp
	g++ $(STD) $(TESTCOVERAGE) -c $^ -o $@ 


read.o: CalcWrapper/CalcWrapper/Model/read.cpp
	$(STD) $(TESTCOVERAGE) -c $^


rpn.o: CalcWrapper/CalcWrapper/Model/rpn.cpp
	$(STD) $(TESTCOVERAGE) -c $^


parse.o: CalcWrapper/CalcWrapper/Model/parse.cpp
	$(STD) $(TESTCOVERAGE) -c $^


calculate.o: CalcWrapper/CalcWrapper/Model/calculate.cpp
	$(STD) $(TESTCOVERAGE) -c $^


validate.o: CalcWrapper/CalcWrapper/Model/validate.cpp
	$(STD) $(TESTCOVERAGE) -c $^


calculatedeposit.o: CalcWrapper/CalcWrapper/Model/calculatedeposit.cpp
	$(STD) $(TESTCOVERAGE) -c $^


leaks:
	$(LEAKS) ./test.out


clang:
	cp ../../../materials/linters/.clang-format ./
	clang-format -i CalcWrapper/CalcWrapper/Model/*
	#clang-format -n Controller/* Model/*


cppcheck:
	-cppcheck --language=c++ --enable=all --std=c++17 CalcWrapper/CalcWrapper/Model/* $(CPP)


clean:
	$(WASH)
	rm -rf CalcWrapper/build