//
// Created by georg on 7/15/2023.
//

#ifndef PASCAL_PS_DEBUGBREAK_H
#define PASCAL_PS_DEBUGBREAK_H

#if defined(__x86_64__)
    __inline__ static void debug_break(void)
    {
        __asm__ volatile("int $0x03");
    }
#endif

#endif //PASCAL_PS_DEBUGBREAK_H
