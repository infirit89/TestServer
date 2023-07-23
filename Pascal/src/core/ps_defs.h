//
// Created by georg on 6/8/2023.
//

#ifndef PASCAL_PS_DEFS_H
#define PASCAL_PS_DEFS_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef  unsigned int u32;
typedef  unsigned long long u64;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN  (-9223372036854775807LL - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define UINT8_MAX 255
#define UINT16_MAX 65535
#define UINT32_MAX 0xffffffffU  /* 4294967295U */
#define UINT64_MAX 0xffffffffffffffffULL /* 18446744073709551615ULL */

#define PS_TRUE 1
#define PS_FALSE 0

typedef u32 ps_socket;
#define PS_INVALID_SOCKET (ps_socket)~0

#define PS_HTTP_REQUEST_INITIAL_BUF_SIZE 1024
#define PS_HTTP_MAX_REQUEST_BUF_SIZE 8388608

#endif //PASCAL_PS_DEFS_H
