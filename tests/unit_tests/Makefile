CC=gcc
ARCH_STRING=x86_64
CFLAGS=-DARCH_STRING=${ARCH_STRING} -w
KLEIN_LIB=../../code/klein/libklein_c.a
OUTPUT=run_tests.out
TEST_DIR=.
UNITY_DIR=unity
REPL_CODE_DIR=../replaced_code
CODE_DIR=../../code

default: test

test:
	@echo "CC q_shared.spec.c"
	@${CC} ${CFLAGS} -o ${TEST_DIR}/q_shared.spec.o -c ${TEST_DIR}/q_shared.spec.c
	@$(CC) ${CFLAGS} -o ${UNITY_DIR}/unity.o -c ${UNITY_DIR}/unity.c
	@$(CC) ${CFLAGS} -o ${TEST_DIR}/code-qcommon-q_math.o -c ${CODE_DIR}/qcommon/q_math.c
	@$(CC) ${CFLAGS} -o ${TEST_DIR}/code-qcommon-q_shared.o -c ${CODE_DIR}/qcommon/q_shared.c
	@$(CC) ${CFLAGS} -o ${REPL_CODE_DIR}/q_shared_definitions.o -c ${REPL_CODE_DIR}/q_shared_definitions.c
	@$(CC) ${CFLAGS} -o ${REPL_CODE_DIR}/old_functions.o -c ${REPL_CODE_DIR}/old_functions.c
	@${CXX} unity/unity.o ${TEST_DIR}/q_shared.spec.o ${TEST_DIR}/code-qcommon-q_math.o ${TEST_DIR}/code-qcommon-q_shared.o ${REPL_CODE_DIR}/q_shared_definitions.o ${REPL_CODE_DIR}/old_functions.o ${KLEIN_LIB} -lm -o ${OUTPUT}
	@${MAKE} clean.o

clean.o:
	rm -f ${TEST_DIR}/*.o ${REPL_CODE_DIR}/*.o ${UNITY_DIR}/*.o

clean: clean.o
	rm -f ${TEST_DIR}/*.out

run:
	./${OUTPUT}
