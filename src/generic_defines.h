#pragma once

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef TRUE
#define TRUE 0x01
#endif

#ifndef FALSE
#define FALSE 0x00
#endif

#ifndef NULL
#define NULL 0x00
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#ifndef TOUPPER
#define TOUPPER(c) ((c) & ~0x20)
#endif

#ifndef TOLOWER
#define TOLOWER(c) ((c) | 0x20)
#endif

// function pointer type for the callback function
typedef void (*callback_t)(void);
