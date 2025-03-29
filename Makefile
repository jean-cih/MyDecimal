GCC = gcc -Wall -Werror -Wextra -str=c11

FILES_LIB = # файлы

all: clean s21_decimal.a

s21_decimal.a: s21_decimal.o
	ar r s21_decimal.a *.o
	rm -f *.o

s21_decimal.o:
	@$(GCC) -c $(FILES_LIB)

test: s21_decimal.o test.o

test.o:

gcov_test: test.o

gcov_report: 

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem # файлы

clang:
	cp ../materials/linters/.clang-format ./
	rm .clang-format

clean:
