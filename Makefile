
CPP = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm
NAMELIB = calc.dll
CFLAGSFORLIB = -shared -o



ifeq ($(OS),Windows_NT)
STD = clang++ --std=c++17
TESTCOVERAGE = 
WASH=del *.o *.a *.exe 

# Путь к файлу решения или проекту Avalonia
SOLUTION_FILE := SimpleCalc\SimpleCalc.sln

# Конфигурация сборки Avalonia (Debug или Release)
CONFIGURATION := Debug

# Папка для сборки для Windows
BUILD_DIR := CalcWrapper\build

SRC_DIR := CalcWrapper\build\CalcWrapper\Release
DEST_DIR1 := SimpleCalc\SimpleCalc\bin\x64\Debug\net7.0
DEST_DIR2 := SimpleCalc\SimpleCalc.Desktop\bin\x64\Debug\net7.0

else
STD = g++ --std=c++17
TESTCOVERAGE = -fprofile-arcs -ftest-coverage
WASH=rm -rf *.o *.a *.out *.log *.aux *.dvi *.toc *css *gcno *gcda CPPLINT.cfg *tgz *.html man_ru report .clang-format

# Папка для сборки
BUILD_DIR := CalcWrapper/build
endif


OS=$(shell uname)

ifeq ($(OS), Linux)
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s
	TEST =  -lgtest --coverage
else ifeq ($(OS),Windows_NT)

else
	LEAKS=CK_FORK=no leaks --atExit --
	TEST =  -lgtest -fsanitize=address --coverage
endif

# сборка для Windows
# Visual Studio 16 2019 -A x64 "D:\Projects\Calculation C#\Calculation-C-\CalcWrapper"
# MinGW Makefiles ..
buildCmakeWind:
	mkdir $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -G "Visual Studio 17 2022" ..
	@cmake --build $(BUILD_DIR) --config Release

# для Windows
copyFiles: copyFilesSimpleCalc copyFilesSimpleCalcDesktop

# для Windows (возможно для Linux придется поменять название dll)
copyFilesSimpleCalc:
	@xcopy /y /i $(SRC_DIR)\CalcWrapper.dll $(DEST_DIR1)\

# для Windows
copyFilesSimpleCalcDesktop:
	@xcopy /y /i $(SRC_DIR)\CalcWrapper.dll $(DEST_DIR2)\

# для Windows
buildAvalonia:
	@dotnet build $(SOLUTION_FILE) -c $(CONFIGURATION)

# Публикация проекта Avalonia
createExeAvalonia: buildCmakeWind
	@dotnet publish $(SOLUTION_FILE) -c $(CONFIGURATION) -o publish
	@xcopy /y /i $(SRC_DIR)\CalcWrapper.dll publish



all: clean install


install: build clean


build:
	mkdir build
	cd build; cmake ..
	make -C build


uninstall:
	rm -rf build


dvi:
	makeinfo --html --no-warn --no-validate --force ./man_ru.texi


dist:
	rm -rf MyCalc
	mkdir MyCalc
	cp Makefile Model/* View/* Controller/* *.h *.txt *.texi *.cpp *.user MyCalc/
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


read.o: Model/read.cpp
	$(STD) $(TESTCOVERAGE) -c $^


rpn.o: Model/rpn.cpp
	$(STD) $(TESTCOVERAGE) -c $^


parse.o: Model/parse.cpp
	$(STD) $(TESTCOVERAGE) -c $^


calculate.o: Model/calculate.cpp
	$(STD) $(TESTCOVERAGE) -c $^


validate.o: Model/validate.cpp
	$(STD) $(TESTCOVERAGE) -c $^


calculatedeposit.o: Model/calculatedeposit.cpp
	$(STD) $(TESTCOVERAGE) -c $^


leaks:
	$(LEAKS) ./test.out


clang:
	cp ../materials/linters/.clang-format ./
	 clang-format -i Controller/* Model/* View/*.cpp View/*.h test.cpp main.cpp
	#clang-format -n Controller/* Model/* View/*.cpp View/*.h test.cpp main.cpp


cppcheck:
	-cppcheck --language=c++ --enable=all --std=c++17 Model/* Controller/* View/*.cpp *.h test.cpp $(CPP)


clean:
	$(WASH)