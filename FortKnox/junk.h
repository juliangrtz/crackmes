#pragma once

#define TWO_BYTE_NOP __asm \
{ \
__asm mov ecx, ecx \
}
#define THREE_BYTE_NOP __asm \
{ \
__asm lea ebx,[ebx] \
}

#define FUCK_YOU_MSG __asm \
{ \
__asm push esi \
__asm push edi \
__asm mov esi, 0x4675636B \
__asm mov edi, 0x796F75 \
__asm pop esi \
__asm pop edi \
}


#define PUSH_POP_GARBAGE __asm \
{ \
__asm push esi \
__asm push edi \
__asm push ecx \
__asm pop edi \
__asm pop esi \
__asm pop ecx \
}
