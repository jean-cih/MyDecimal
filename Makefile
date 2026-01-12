GCC = gcc

FLAGS = -Wall -Werror -Wextra -lm -std=c11

FILES_LIB = $(shell find lib -name "*.c")

FILES_TEST = $(shell find tests -name "*.c")
FILES_TEST := $(filter-out \
			  tests/s21_main_leak.c \
			  tests/helpers/%, \
			  $(FILES_TEST))

all: clean s21_decimal.a


s21_decimal.a: s21_decimal.o
	ar r s21_decimal.a *.o
	rm -f *.o

s21_decimal.o:
	@$(GCC) $(FLAGS) -c $(FILES_LIB)

test:
	@$(GCC) -o test_decimal $(FILES_TEST) $(FILES_LIB) -lcheck -lm -pthread -lsubunit
	@./test_decimal
	@rm test_decimal

test.o:
	@$(GCC) -c $(FILES_TEST)

gcov_test: test.o
	@$(GCC) $(FLAGS) -c  $(FILES_LIB) --coverage
	ar r s21_decimal_gcov.a s21_*.o
	@$(GCC) $(FILES_TEST) -o gcov_test -L. -l:s21_decimal_gcov.a -lcheck -lsubunit -lrt -lpthread -lm -lgcov
	@./gcov_test

gcov_report: gcov_test
	rm -rf report
	mkdir report
	@gcovr -r . --html --html-details --html-self-contained -o coverage_report.html
	mv coverage_report* report
	rm -f *.gcda *.gcno *.o

clean:
	rm -f *.a test_decimal gcov_test
	rm -f *.o *.gcda *.gcno
	rm -rf report

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES_LIB) $(FILES_TEST) tests/*.c

leak:
	@$(GCC) tests/s21_main_leak.c $(FILES_LIB) $(FLAGS) -o test_leak
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_leak
	@rm test_leak

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(FILES_LIB) $(FILES_TEST) tests/*.c tests/helpers/*.c
	rm .clang-format


