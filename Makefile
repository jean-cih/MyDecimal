GCC = gcc

FLAGS = -Wall -Werror -Wextra -std=c11

FILES_TESTS = $(shell find tests/cases -name "*.c") tests/test_string.c

FILES_LIB = $(shell find lib -name "*.c")

all: clean s21_string.a

s21_string.a: s21_string.o
	ar r s21_string.a *.o
	rm -f *.o

s21_string.o:
	@$(GCC) $(FLAGS) -c $(FILES_LIB)

test:
	@$(GCC) -o test_string $(FILES_TESTS) $(FILES_LIB) -lcheck -lm -pthread -lsubunit
	@./test_string
	@rm test_string

test.o:
	@$(GCC) -c $(FILES_TESTS)

gcov_test: test.o
	@$(GCC) $(FLAGS) -c $(FILES_LIB) --coverage
	ar r s21_string_gcov.a s21_*.o
	@$(GCC) $(FILES_TESTS) -o gcov_test -L. -l:s21_string_gcov.a -lcheck -lsubunit -lrt -lpthread -lm -lgcov
	@./gcov_test


gcov_report: gcov_test
	rm -rf report
	mkdir report
	@gcovr -r . --html --html-details --html-self-contained -o coverage_report.html
	mv coverage_report* report
	rm -f *.gcda *.gcno *.o

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES_LIB) tests/cases/*.c tests/test_string.c

test_leaks:
	@$(GCC) tests/test_leaks.c $(FILES_LIB) $(FLAGS) -lm -o test_leaks
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_leaks
	@rm test_leaks

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(FILES_LIB) $(FILES_TESTS)
	rm .clang-format

clean:
	rm -f *.a test_string gcov_test
	rm -f *.o *.gcda *.gcno
	rm -rf report
