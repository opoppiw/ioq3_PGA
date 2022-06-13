/**
 * q_shared_definitions.c
 *
 * The definitions of the contents code/qcommon/q_shared.h are spread over multiple files.
 * If one wants to compile only code/qcommon/q_math.c for unit tests, then all the files that include q_shared.h have
 * to be compiled as well. If those files include other files, then those files have to be compiled as well.
 * To avoid all this complications, this file contains definitions for q_shared.h and includes only q_shared.h
 */
#include "../../code/qcommon/q_shared.h"

void QDECL Com_Printf( const char *fmt, ... ) {
  return;
}

void QDECL Com_Error( int code, const char *fmt, ... ) {
  return;
}