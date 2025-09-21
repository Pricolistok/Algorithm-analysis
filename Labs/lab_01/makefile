CXX := g++
CXXFLAGS := -std=c++23 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -Iinc
LDFLAGS :=
EXEFLAGS :=

# Создание выходной директории (Windows-совместимое)
$(shell if not exist out mkdir out)

# Режимы сборки
ifeq ($(mode), release)
  CXXFLAGS += -O2 -DNDEBUG
endif

ifeq ($(mode), debug)
  CXXFLAGS += -g -O0
endif

ifeq ($(mode), memory)
  CXXFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer -g -O0
  LDFLAGS += -fsanitize=memory -pie
  CXX := clang++
endif

ifeq ($(mode), address)
  CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer -g -O0
  LDFLAGS += -fsanitize=address
  CXX := clang++
endif

ifeq ($(mode), ubsan)
  CXXFLAGS += -fsanitize=undefined -fno-omit-frame-pointer -g -O0
  LDFLAGS += -fsanitize=undefined
  CXX := clang++
endif

ifeq ($(mode), coverage)
  CXXFLAGS += --coverage
  LDFLAGS += --coverage
endif

# Основная цель
app.exe: out/main.o out/simple_multiplication.o out/vinograd_algorithm.o out/funcs.o
	$(CXX) -o app.exe out/main.o out/simple_multiplication.o out/vinograd_algorithm.o out/funcs.o $(LDFLAGS) $(EXEFLAGS)

out/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -o out/main.o -c src/main.cpp

out/simple_multiplication.o: src/simple_multiplication.cpp inc/errors.h
	$(CXX) $(CXXFLAGS) -o out/simple_multiplication.o -c src/simple_multiplication.cpp

out/vinograd_algorithm.o: src/vinograd_algorithm.cpp inc/errors.h
	$(CXX) $(CXXFLAGS) -o out/vinograd_algorithm.o -c src/vinograd_algorithm.cpp

out/funcs.o: src/funcs.cpp
	$(CXX) $(CXXFLAGS) -o out/funcs.o -c src/funcs.cpp

.PHONY: clean run

clean:
	del /Q out\* 2>nul
	del /Q *.exe 2>nul
	del /Q *.txt 2>nul
	del /Q func_tests\scripts\*.txt 2>nul

run: app.exe
	app.exe

# Дополнительные цели
debug: mode = debug
debug: app.exe

release: mode = release
release: app.exe

address: mode = address
address: app.exe