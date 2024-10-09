CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
LIB=s21_matrix_oop.a
CEXE=s21_test

#============= FLAGS FOR OS ======================================================== 
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck
	OPEN_CM=open
endif

#============= ALL ==================================================================
all: clean ${LIB} test

#============= LIBRIRY & TEST LIBRARY================================================
s21_matrix_oop.a: 
	${CC} ${CFLAGS} -c s21_*.c
	ar rc ${LIB} *.o
	ranlib ${LIB}
	rm -f *.o

gcov_s21_matrix_oop.a: clean
	${CC} ${CFLAGS} -c s21_*.c ${GCOV_FLAGS}
	ar rc ${LIB} *.o
	ranlib ${LIB}
	rm -f *.o

#============= TEST ==============================================================
test: clean s21_matrix_oop.a
	$(CC) ${CFLAGS} test/*.c  ${LIB} -o ${CEXE} ${LDFLAGS}
	./${CEXE}

gcov_report: clean gcov_s21_matrix_oop.a
	$(CC) ${CFLAGS} test/*.c ${LIB} -o ${CEXE} ${LDFLAGS} ${GCOV_FLAGS}
	mkdir report
	./${CEXE} >> report/s21_tests.txt
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.info

cppcheck:
	cppcheck --enable=all --std=c11 --language=c *.c

fsanitize: clean s21_matrix_oop.a
	$(CC) ${CFLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined test/*.c ${LIB} -o ${CEXE}_fsanitize ${LDFLAGS}
	./${CEXE}_fsanitize

valgrind: clean s21_matrix_oop.a
	$(CC) ${CFLAGS} test/*.c ${LIB} -o ${CEXE} ${LDFLAGS}
	valgrind -s --leak-check=full --track-origins=yes --show-reachable=yes ./$(CEXE)


#=========== STYLE ====================================================================
format_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n test/*.c test/*.h *.c *.h
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i test/*.c test/*.h *.c *.h
	rm -f .clang-format

#========== CLEAN ======================================================================
clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf *.a
	rm -rf s21_test
	rm -rf s21_test_fsanitize
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.log
	rm -rf *.html
	rm -rf *.css
	rm -rf report
	rm -rf *.dSYM
	rm -rf *.info