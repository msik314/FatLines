#ifndef DEBUG_UTILS
#define DEBUG_UTILS

#ifndef NDEBUG
	#include <cstdio>
	#define ASSERT(expr, msg); if(!expr)\
	{\
		printf("Assertion failed at %s:%d: %s\n", __FILE__, __LINE__, msg);\
		int* ptr = 0;\
		*ptr = 1;\
	}
	#define DEBUG_BREAK(); __asm\
	{\
		int 3;\
	}
#else //NDEBUG
	#define ASSERT(expr, msg);
	#define DEBUG_BREAK();
#endif //NDEBUG
#endif //DEBUG_UTILS