#pragma once

// 0x48, 0xB8, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0x08, 0xFF, 0xFF, 0x48, 0x31, 0xC0, 0xEB, 0xF7, 0xE8
#define DEATHRAYS __asm \
{ \
__asm _emit 0x48 \
__asm _emit 0xB8 \
__asm _emit 0xFF \
__asm _emit 0xFF \
__asm _emit 0xFF \
__asm _emit 0xFF \
__asm _emit 0xEB \
__asm _emit 0x08 \
__asm _emit 0xFF \
__asm _emit 0xFF \
__asm _emit 0x48 \
__asm _emit 0x31 \
__asm _emit 0xC0 \
__asm _emit 0xEB \
__asm _emit 0xF7 \
__asm _emit 0xE8 \
}

#define ROGUE_BYTE __asm \
{ \
__asm push eax \
__asm mov eax, 0 \
__asm sub eax, 0x54CA6 \
__asm xor eax, 0xA9975 \
__asm mov ebx, eax \
__asm not ebx \
__asm and ebx, 1 \
__asm shl ebx, 1 \
__asm xor eax, ebx \
__asm sub eax, eax \
__asm jz lbl \
__asm _emit 0xE8 \
__asm lbl: \
__asm lea edx, [edx] \
__asm pop eax \
}

#define ROGUE_BYTE_2 __asm \
{ \
__asm push eax \
__asm mov eax, 0 \
__asm sub eax, 0x54CA6 \
__asm xor eax, 0xA9975 \
__asm mov ebx, eax \
__asm not ebx \
__asm and ebx, 1 \
__asm shl ebx, 1 \
__asm xor eax, ebx \
__asm sub eax, eax \
__asm jz lbl2 \
__asm _emit 0xE8 \
__asm lbl2: \
__asm lea edx, [edx] \
__asm pop eax \
}