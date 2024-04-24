#pragma once

#define SEMANTIC_NOP_1 __asm \
{ \
__asm mov ecx, ecx \
}
#define SEMANTIC_NOP_2 __asm \
{ \
__asm lea ebx,[ebx] \
}

#define FUCK_YOU_MSG __asm \
{ \
__asm push esi \
__asm push edi \
__asm mov esi, 0x4675636B \ // 0x4675636B == "Fuck"
__asm mov edi, 0x796F75 \ // 0x796F75 == "you"
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
