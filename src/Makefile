CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
LIB=s21_matrix_oop.a
CEXE=s21_test

# CC := gcc
# CFLAGS := -ggdb -std=c++17 -Wall -Werror -Wextra -lstdc++
# C_LIBS :=
# TST_LIBS := -lgtest -lgmock -pthread
# $(CC) s21_matrix_oop.o test.cpp -o s21_test $(TST_LIBS) $(CFLAGS)


#============= FLAGS FOR OS ========================================================
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lgtest -lgtest_main -pthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lgtest
	OPEN_CM=open
endif

#============= ALL ==================================================================
all: clean ${LIB} test

#============= LIBRARY & TEST LIBRARY================================================
s21_matrix_oop.a: 
	${CC} ${CFLAGS} -c s21_*.cpp
	ar rc ${LIB} *.o
	ranlib ${LIB}
	rm -f *.o

gcov_s21_matrix_oop.a: clean
	${CC} ${CFLAGS} ${GCOV_FLAGS} -c s21_*.cpp
	ar rc ${LIB} *.o
	ranlib ${LIB}
	rm -f *.o

#============= TEST ================================================================
test: clean s21_matrix_oop.a
	$(CC) ${CFLAGS} test/test_s21_matrix.cpp ${LIB} -o ${CEXE} ${LDFLAGS}
	./${CEXE}

gcov_report: clean gcov_s21_matrix_oop.a
	$(CC) ${CFLAGS} ${GCOV_FLAGS} test/test_s21_matrix.cpp ${LIB} -o ${CEXE} ${LDFLAGS}
	mkdir report
	./${CEXE} >> report/s21_tests.txt
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	$(OPEN_CM) report/index.html
	rm -rf *.gcda *.gcno *.info

cppcheck:
	cppcheck --enable=all --std=c++11 --language=c++ *.cpp

fsanitize: clean s21_matrix_oop.a
	$(CC) ${CFLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined test_s21_matrix.cpp ${LIB} -o ${CEXE}_fsanitize ${LDFLAGS}
	./${CEXE}_fsanitize

valgrind: clean s21_matrix_oop.a
	$(CC) ${CFLAGS} test_s21_matrix.cpp ${LIB} -o ${CEXE} ${LDFLAGS}
	valgrind -s --leak-check=full --track-origins=yes --show-reachable=yes ./$(CEXE)

#=========== STYLE ===================================================================
format_check:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n test_s21_matrix.cpp *.cpp *.h
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i test_s21_matrix.cpp *.cpp *.h
	rm -f .clang-format

#=========== CLEAN ===================================================================
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
