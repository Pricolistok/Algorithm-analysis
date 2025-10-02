CXX := g++
CXXFLAGS := -std=c++23 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -Iinc -MMD -MP
LDFLAGS :=

$(shell mkdir -p out)

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%,out/%,$(SRC:.cpp=.o))
DEP := $(OBJ:.o=.d)

TEST_SRC := $(wildcard unit_tests/*.cpp)
TEST_OBJ := $(patsubst unit_tests/%,out/%,$(TEST_SRC:.cpp=.o))
TEST_DEP := $(TEST_OBJ:.o=.d)

ifeq ($(mode),release)
  CXXFLAGS += -O2 -DNDEBUG
endif

ifeq ($(mode),debug)
  CXXFLAGS += -g -O0
endif

app.exe: $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

out/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: out/test
	./out/test

out/test: $(TEST_OBJ) out/funcs.o out/input_output.o out/simple_multiplication.o out/vinograd_algorithm.o out/vinograd_update.o
	$(CXX) -o $@ $^ -lcheck -lsubunit -lpthread -lrt

out/%.o: unit_tests/%.cpp
	$(CXX) $(CXXFLAGS) -Iunit_tests -c $< -o $@

clean:
	rm -f out/*.o out/*.d app.exe out/test

-include $(DEP)
-include $(TEST_DEP)
