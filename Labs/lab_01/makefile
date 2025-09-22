CXX := g++
CXXFLAGS := -std=c++23 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -Iinc -MMD -MP
LDFLAGS :=
EXEFLAGS :=

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=out/%.o)
DEP := $(OBJ:.o=.d)

$(shell if not exist out mkdir out)

ifeq ($(mode),release)
  CXXFLAGS += -O2 -DNDEBUG
endif

ifeq ($(mode),debug)
  CXXFLAGS += -g -O0
endif

ifeq ($(mode),memory)
  CXXFLAGS += -fsanitize=memory -fPIE -fno-omit-frame-pointer -g -O0
  LDFLAGS += -fsanitize=memory -pie
  CXX := clang++
endif

ifeq ($(mode),address)
  CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer -g -O0
  LDFLAGS += -fsanitize=address
  CXX := clang++
endif

ifeq ($(mode),ubsan)
  CXXFLAGS += -fsanitize=undefined -fno-omit-frame-pointer -g -O0
  LDFLAGS += -fsanitize=undefined
  CXX := clang++
endif

ifeq ($(mode),coverage)
  CXXFLAGS += --coverage
  LDFLAGS += --coverage
endif

app.exe: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) $(EXEFLAGS)

out/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q out\* 2>nul
	del /Q *.exe 2>nul
	del /Q *.txt 2>nul

run: app.exe
	app.exe

debug: mode=debug
debug: app.exe

release: mode=release
release: app.exe

address: mode=address
address: app.exe

-include $(DEP)
