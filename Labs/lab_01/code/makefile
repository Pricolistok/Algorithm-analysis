CXX := g++
CXXFLAGS := -std=c++23 -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-conversion -Wfloat-equal -Iinc -MMD -MP
LDFLAGS :=

OUT_DIR = ./out
SRC_DIR = ./src
UNIT_TEST_DIR = ./unit_tests
INC_DIR = ./inc
UNIT_OUT_DIR = $(OUT_DIR)/unit

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)
DEP := $(OBJ:.o=.d)

TEST_SRC := $(wildcard $(UNIT_TEST_DIR)/*.cpp)
TEST_OBJ := $(TEST_SRC:$(UNIT_TEST_DIR)/%.cpp=$(UNIT_OUT_DIR)/%.o)
TEST_DEP := $(TEST_OBJ:.o=.d)

ifeq ($(mode),release)
  CXXFLAGS += -O2 -DNDEBUG
endif

ifeq ($(mode),debug)
  CXXFLAGS += -g -O0
endif

UNIT_CXXFLAGS = $(CXXFLAGS) -fprofile-arcs -ftest-coverage
UNIT_TEST_LIBS = -lcheck -lpthread -lrt -lsubunit -lgcov


$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UNIT_OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(UNIT_OUT_DIR)
	$(CXX) $(UNIT_CXXFLAGS) -c $< -o $@

$(UNIT_OUT_DIR)/%.o: $(UNIT_TEST_DIR)/%.cpp
	@mkdir -p $(UNIT_OUT_DIR)
	$(CXX) $(UNIT_CXXFLAGS) -I$(UNIT_TEST_DIR) -c $< -o $@

app.exe: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


unit_tests.exe: $(TEST_OBJ) $(filter-out $(UNIT_OUT_DIR)/main.o,$(OBJ:$(OUT_DIR)/%.o=$(UNIT_OUT_DIR)/%.o))
	$(CXX) $(UNIT_CXXFLAGS) -o $@ $^ $(UNIT_TEST_LIBS)

unit: unit_tests.exe
	@mkdir -p $(OUT_DIR)
	@./unit_tests.exe > $(OUT_DIR)/unit_output.txt || true
	@lcov --capture --directory $(UNIT_OUT_DIR) --output-file $(OUT_DIR)/coverage.info --rc branch_coverage=1
	@lcov --remove $(OUT_DIR)/coverage.info '*/unit_tests/*' -o $(OUT_DIR)/coverage.info --rc branch_coverage=1
	@COVERAGE_PERCENT=$$(lcov --summary $(OUT_DIR)/coverage.info 2>/dev/null | grep lines | awk '{print $$2}' | tr -d '%' | head -n 1); \
	COVERAGE_JSON=$$(awk "BEGIN {print $$COVERAGE_PERCENT / 100}"); \
	CHECK_LINE=$$(grep "Checks:" $(OUT_DIR)/unit_output.txt || echo ""); \
	CHECK_TOTAL=$$(echo $$CHECK_LINE | awk '{print $$3}' | tr -d ',' | sed 's/[^0-9]//g' || echo 0); \
	FAILURES=$$(echo $$CHECK_LINE | awk '{print $$5}' | tr -d ',' | sed 's/[^0-9]//g' || echo 0); \
	ERRORS=$$(echo $$CHECK_LINE | awk '{print $$7}' | tr -d ',' | sed 's/[^0-9]//g' || echo 0); \
	PASSED=$$((CHECK_TOTAL - FAILURES - ERRORS)); \
	FAILED=$$((FAILURES + ERRORS)); \
	TIMESTAMP=$$(date +"%Y-%m-%dT%H:%M:%S%:z"); \
	echo '{' > $(OUT_DIR)/temp.json; \
	echo '"timestamp": "'$$TIMESTAMP'",' >> $(OUT_DIR)/temp.json; \
	echo '"coverage": '$$COVERAGE_JSON',' >> $(OUT_DIR)/temp.json; \
	echo '"passed": '$$PASSED',' >> $(OUT_DIR)/temp.json; \
	echo '"failed": '$$FAILED >> $(OUT_DIR)/temp.json; \
	echo '}' >> $(OUT_DIR)/temp.json

clean:
	@rm -rf $(OUT_DIR) *.exe *.gcno *.gcda *.gcov *.info

all: app.exe
release: app.exe

.PHONY: clean all release unit
-include $(DEP)
-include $(TEST_DEP)
