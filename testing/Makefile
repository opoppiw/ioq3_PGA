CC=gcc
ARCH_STRING=x86_64
CFLAGS=-DARCH_STRING=${ARCH_STRING} -w
KLEIN_LIB=../code/klein/libklein_c.a
OUTPUT=run_tests.out
# UNITY=unity/unity.c
# SRC_OBJS= \
# 	../code/qcommon/q_math.c \
# 	../code/qcommon/q_shared.c \
# 	ioquake/q_shared_definitions.c \
# 	${KLEIN_LIB}

# OBJS = ${SRC_OBJS} ${UNITY} tests/q_shared.spec.c

default: test

test: ${OBJS}
	@echo "CC q_shared.spec.c"
	@$(CC) ${CFLAGS} -o tests/q_shared.spec.o -c tests/q_shared.spec.c
	@$(CC) ${CFLAGS} -o unity/unity.o -c unity/unity.c
	@$(CC) ${CFLAGS} -o code-qcommon-q_math.o -c ../code/qcommon/q_math.c
	@$(CC) ${CFLAGS} -o code-qcommon-q_shared.o -c ../code/qcommon/q_shared.c
	@$(CC) ${CFLAGS} -o ioquake/q_shared_definitions.o -c ioquake/q_shared_definitions.c
	@$(CXX) unity/unity.o tests/q_shared.spec.o code-qcommon-q_math.o code-qcommon-q_shared.o ioquake/q_shared_definitions.o ${KLEIN_LIB} -lm -o ${OUTPUT}
	@${MAKE} clean.o

clean.o:
	rm -f *.o tests/*.o unity/*.o ioquake/*.o

clean: clean.o
	rm -f *.out

run:
	./${OUTPUT}