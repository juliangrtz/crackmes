/*
 * A crackme I've written to try out the C programming language.
 * To obtain an optimal binary you'd need to compile with the following flags:
 *      gcc crackme.c -o crackme -pedantic -Wall -s -pthread -static
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <pthread.h>
#include <unistd.h>

// Black anti-disassembler magic to thwart the IDA disassembler
#define deathrays \
    __asm__ volatile(".byte 0x48, 0xB8, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0x08, 0xFF, 0xFF, 0x48, 0x31, 0xC0, 0xEB, 0xF7, 0xE8");

// This is a XOR-ed ASCII art skull
int skull[] = {0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x8c, 0xe3, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef,
               0xef, 0xef, 0xef, 0xef, 0xe3, 0x8c, 0xa8, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x8c, 0xe3, 0xf4,
               0x8c, 0x82, 0x98, 0x98, 0x98, 0x8c, 0x98, 0x8c, 0x98, 0x8c, 0x98, 0x98, 0xef, 0xe3, 0x8c, 0xa8, 0x82,
               0x82, 0x82, 0x82, 0x82, 0x82, 0xe3, 0x85, 0x82, 0x98, 0x8c, 0x8c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,
               0x82, 0x82, 0x98, 0x82, 0x8c, 0x98, 0xc2, 0xe3, 0xa8, 0x82, 0x82, 0x82, 0x82, 0x82, 0xe3, 0x85, 0x8c,
               0x8c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x8c, 0x82,
               0xc2, 0xe3, 0x8c, 0xa8, 0x82, 0x82, 0x82, 0x82, 0xe3, 0x85, 0x82, 0x98, 0x8c, 0x82, 0x82, 0x82, 0x82,
               0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x82, 0x82, 0x98, 0x82, 0x98, 0xc2, 0xe3, 0xa8,
               0x82, 0x82, 0x82, 0x82, 0xef, 0x82, 0x82, 0x8c, 0x82, 0x82, 0x82, 0x82, 0x98, 0x98, 0x98, 0x8c, 0x98,
               0x8c, 0x98, 0x8c, 0x98, 0x98, 0x98, 0x82, 0x82, 0x8c, 0x82, 0x8c, 0xef, 0xa8, 0x82, 0x82, 0x82, 0x82,
               0xef, 0x82, 0x82, 0x98, 0x82, 0x82, 0x82, 0x98, 0x98, 0x8c, 0x98, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x98,
               0x98, 0x8c, 0x98, 0x82, 0x82, 0x82, 0x8c, 0xef, 0xa8, 0x82, 0x82, 0x82, 0x82, 0xf4, 0x82, 0x98, 0x82,
               0x98, 0x8c, 0x98, 0x98, 0x8c, 0x98, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x98, 0x8c, 0x98,
               0x82, 0x82, 0x98, 0xf4, 0xa8, 0x82, 0x82, 0x82, 0xe3, 0x82, 0x82, 0xe3, 0x98, 0x82, 0x82, 0x82, 0x82,
               0x8c, 0x8c, 0x98, 0x8c, 0x8c, 0x8c, 0x98, 0x8c, 0x8c, 0x8c, 0x98, 0x8c, 0x82, 0x82, 0x82, 0xe3, 0x82,
               0xe3, 0xa8, 0x82, 0x82, 0x8c, 0xf4, 0x82, 0x82, 0xef, 0xe3, 0x98, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x98,
               0xef, 0x8c, 0x98, 0x98, 0x8c, 0x98, 0x98, 0x8c, 0x82, 0x8c, 0x98, 0xe3, 0xef, 0x8c, 0xef, 0xa8, 0x82,
               0xe3, 0x85, 0x82, 0x82, 0x8c, 0xf4, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0x98, 0x8c,
               0x98, 0xe3, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xf4, 0x98, 0x82, 0xe3, 0xa8, 0x98, 0xef, 0x82,
               0x8c, 0x82, 0x82, 0x8c, 0xc2, 0xf4, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xf4, 0x8c, 0x98, 0xe3, 0x82,
               0xc2, 0xf4, 0xef, 0xef, 0xef, 0xef, 0xf4, 0x82, 0x8c, 0x98, 0xef, 0x98, 0xa8, 0x82, 0xf4, 0x8c, 0x98,
               0x8c, 0x82, 0x82, 0x8c, 0x8c, 0xc2, 0xf4, 0xef, 0xef, 0xef, 0xf4, 0x8c, 0x98, 0xe3, 0xef, 0x8c, 0x8c,
               0xc2, 0xf4, 0xef, 0xf4, 0x85, 0x82, 0x8c, 0x98, 0x82, 0xf4, 0xa8, 0x82, 0x82, 0xf4, 0x8c, 0x82, 0x82,
               0x8c, 0x98, 0x8c, 0x82, 0x8c, 0x8c, 0x8c, 0x8c, 0x8c, 0x98, 0xe3, 0xef, 0xef, 0xe3, 0x8c, 0x82, 0x8c,
               0x82, 0x8c, 0x98, 0x8c, 0x82, 0x8c, 0xf4, 0xa8, 0x82, 0x82, 0x82, 0xf4, 0xef, 0xef, 0x8c, 0x8c, 0x8c,
               0x98, 0x82, 0x8c, 0x8c, 0x8c, 0x98, 0x8c, 0xef, 0xef, 0xef, 0xef, 0x8c, 0x98, 0x82, 0x8c, 0x98, 0x82,
               0xef, 0xef, 0xf4, 0xa8, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xc2, 0xf4, 0xef, 0x98, 0x82, 0x8c,
               0x82, 0x8c, 0x8c, 0xef, 0x8c, 0x98, 0xef, 0x8c, 0x8c, 0x98, 0x98, 0x98, 0xef, 0x85, 0xa8, 0x82, 0x82,
               0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xc2, 0xef, 0x98, 0x98, 0x8c, 0x82, 0x8c, 0x98, 0x8c, 0x8c,
               0x8c, 0x8c, 0x82, 0x8c, 0x98, 0x98, 0xef, 0xa8, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,
               0x82, 0xef, 0x98, 0x8c, 0x82, 0x82, 0x98, 0x8c, 0x82, 0x8c, 0x8c, 0x8c, 0x8c, 0x82, 0x8c, 0x8c, 0xef,
               0xa8, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xf4, 0x98, 0x82, 0x82, 0xef, 0x98,
               0x8c, 0x82, 0xef, 0x8c, 0x82, 0x98, 0xef, 0x82, 0x8c, 0xf4, 0xa8, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,
               0x82, 0x82, 0x82, 0x82, 0xc2, 0xf4, 0x8c, 0x98, 0xef, 0x8c, 0x8c, 0x82, 0xef, 0x8c, 0x82, 0x98, 0xef,
               0x8c, 0xf4, 0x85
};

// Even blacker anti-debugging magic using shellcode
// https://packetstormsecurity.com/files/157562/Linux-x64-Anti-Debug-Trick-INT3-Trap-Shellcode.html
char shellcode[] = "\xeb\x63\x48\x89\xe6\x6a\x0d\x59"\
                           "\x6a\x01\xfe\x0c\x24\xe2\xf9\x80"\
                           "\xc9\x0d\x54\x48\x89\xe2\x0f\x05"\
                           "\xcc\x48\x31\xc0\x48\x89\xc7\xb0"\
                           "\x3c\xeb\xf3\x6a\x0d\x59\x4d\x31"\
                           "\xc9\x41\x51\xe2\xfc\x49\x89\xe1"\
                           "\x49\x83\xc1\x03\x41\x80\x09\x14"\
                           "\x49\x83\xc1\x0d\x66\x41\x83\x09"\
                           "\xff\xe8\xbc\xff\xff\xff\x99\x48"\
                           "\x31\xc0\xb0\x3b\x52\x48\xbf\x2f"\
                           "\x62\x69\x6e\x2f\x2f\x73\x68\x57"\
                           "\x54\x5f\x4d\x31\xc9\x4c\x89\xce"\
                           "\x48\x89\xf2\xeb\xb1\x6a\x0d\x58"\
                           "\x6a\x05\x5f\x6a\x08\x41\x5a\xeb"\
                           "\xb2";

void printErrorMessage(char *msg) {
    deathrays;
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

#define SYS_PTRACE 101
long my_ptrace(long request, long pid, void *addr, void *data)
{
   long ret;
    __asm__ volatile(
    "mov %0, %%rdi\n"
    "mov %1, %%rsi\n"
    "mov %2, %%rdx\n"
    "mov %3, %%r10\n"
    "mov $SYS_PTRACE, %%rax\n"
    "syscall" : : "g"(request), "g"(pid),
    "g"(addr), "g"(data));
    __asm__ volatile("mov %%rax, %0" : "=r"(ret));
    return ret;
}

void annoyReverseEngineerAndExit() {
    char betterLuckMsg[56];
    betterLuckMsg[24] = 73 + 32;
    betterLuckMsg[8] = 116;
    betterLuckMsg[1] = L'v' - 7;
    betterLuckMsg[40] = 52 + 49;
    betterLuckMsg[23] = L'x' - 4;
    betterLuckMsg[38] = 79 + 33;
    betterLuckMsg[52] = 108;
    betterLuckMsg[27] = 33 + 0;
    betterLuckMsg[51] = L'u' - 2;
    betterLuckMsg[26] = L'T' + 17;
    betterLuckMsg[42] = L'q' - 0;
    betterLuckMsg[50] = 81 + 19;
    betterLuckMsg[15] = 99;
    betterLuckMsg[47] = 105;
    betterLuckMsg[12] = 32 + 0;
    betterLuckMsg[55] = L'd' + 5;
    betterLuckMsg[53] = 55 + 46;
    betterLuckMsg[39] = 56 + 51;
    betterLuckMsg[11] = L'S' + 31;
    betterLuckMsg[49] = L'c' - 0;
    betterLuckMsg[6] = 66;
    betterLuckMsg[3] = L'@' + 51;
    betterLuckMsg[25] = 109;
    betterLuckMsg[31] = 108;
    betterLuckMsg[10] = 98 + 3;
    betterLuckMsg[48] = L'z' - 1;
    betterLuckMsg[22] = 32;
    betterLuckMsg[5] = L'Z' - 58;
    betterLuckMsg[54] = L'e' - 3;
    betterLuckMsg[32] = L'j' - 9;
    betterLuckMsg[0] = L'r' - 35;
    betterLuckMsg[9] = 93 + 23;
    betterLuckMsg[43] = 100 + 15;
    betterLuckMsg[41] = 122;
    betterLuckMsg[18] = 110;
    betterLuckMsg[30] = 112;
    betterLuckMsg[33] = L't' - 6;
    betterLuckMsg[7] = 84 + 17;
    betterLuckMsg[4] = 46;
    betterLuckMsg[28] = 0;
    betterLuckMsg[20] = 98 + 22;
    betterLuckMsg[21] = L'P' + 36;
    betterLuckMsg[35] = 106;
    betterLuckMsg[16] = L'z' - 15;
    betterLuckMsg[37] = L'9' + 52;
    betterLuckMsg[34] = L't' - 18;
    betterLuckMsg[19] = L'b' + 3;
    betterLuckMsg[14] = 58 + 59;
    betterLuckMsg[44] = L'n' - 0;
    betterLuckMsg[46] = L'r' - 4;
    betterLuckMsg[13] = 108;
    betterLuckMsg[36] = 115;
    betterLuckMsg[45] = L'l' - 7;
    betterLuckMsg[2] = 95 + 17;
    betterLuckMsg[29] = 106;
    betterLuckMsg[17] = 32;

    deathrays;

    printErrorMessage(betterLuckMsg);

    for (int i = 0; i < (sizeof(skull) / sizeof(skull[0])); i++) {
        printf("%c ", skull[i] ^ 0xa2); // Todo: Utilize a stronger XOR key
    }
    printf("\n");

    exit(-1);
}

/*
 * Not exactly a strong anti-debugging function but probably sufficient to confuse the most reverse engineers
 * Todo: Check /proc/self/status for GDB and other debuggers
 */
void *antiDebuggingThread() {
    deathrays;
    while (1) {
        if (my_ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
            annoyReverseEngineerAndExit();
        }

        int (*shellcodec)() = (int (*)()) shellcode;
        shellcodec();

        sleep(50);
    }
    deathrays;
}

void usage(char *fileName) {
    char usageMessage[50];
    usageMessage[16] = L'$' - 4;
    usageMessage[30] = 105 + 12;
    usageMessage[7] = 37;
    usageMessage[41] = L'D' + 43;
    usageMessage[37] = 116;
    usageMessage[3] = L'h' - 1;
    usageMessage[33] = 98;
    usageMessage[45] = L'<' + 41;
    usageMessage[9] = 32 + 0;
    usageMessage[8] = 92 + 23;
    usageMessage[21] = 76 + 29;
    usageMessage[38] = 78 + 42;
    usageMessage[22] = L'2' + 47;
    usageMessage[46] = L'J' + 36;
    usageMessage[6] = 32;
    usageMessage[13] = L'n' - 1;
    usageMessage[18] = 115;
    usageMessage[0] = L's' - 30;
    usageMessage[12] = L'O' + 18;
    usageMessage[5] = 58;
    usageMessage[10] = 60;
    usageMessage[24] = L'^' - 32;
    usageMessage[48] = L'm' + 12;
    usageMessage[2] = 97;
    usageMessage[36] = 101 + 19;
    usageMessage[20] = L'g' + 11;
    usageMessage[49] = 64 + 36;
    usageMessage[34] = 67 + 37;
    usageMessage[31] = 58 + 46;
    usageMessage[27] = 86 + 36;
    usageMessage[17] = 57 + 3;
    usageMessage[28] = 105;
    usageMessage[43] = 105;
    usageMessage[14] = L'A' + 36;
    usageMessage[35] = 72 + 28;
    usageMessage[1] = L'2' + 65;
    usageMessage[19] = L'R' + 19;
    usageMessage[44] = 95 + 6;
    usageMessage[39] = 109;
    usageMessage[23] = L'z' - 14;
    usageMessage[42] = 100;
    usageMessage[29] = L'Y' + 18;
    usageMessage[40] = 71 + 26;
    usageMessage[15] = L'>' + 0;
    usageMessage[11] = 110;
    usageMessage[25] = 0;
    usageMessage[26] = 103;
    usageMessage[32] = 90 + 29;
    usageMessage[4] = 101;
    usageMessage[47] = 96 + 18;

    // "Usage: %s <name> <serial>\n"
    printf(usageMessage, fileName);
    printf("\n");

    deathrays;

    // Note: There is only one correct solution.
    char noteMessage[82];
    noteMessage[80] = 117 - 2;
    noteMessage[78] = L'q' - 12;
    noteMessage[33] = L'w' - 8;
    noteMessage[52] = 121 - 19;
    noteMessage[46] = 102;
    noteMessage[73] = 74 + 34;
    noteMessage[68] = L'W' + 12;
    noteMessage[74] = L'x' - 3;
    noteMessage[57] = L'D' + 34;
    noteMessage[7] = 51 + 53;
    noteMessage[45] = 77 + 21;
    noteMessage[49] = 108;
    noteMessage[1] = 122 - 11;
    noteMessage[25] = L'q' - 2;
    noteMessage[10] = L's' - 14;
    noteMessage[66] = 87 + 12;
    noteMessage[28] = 101;
    noteMessage[35] = L'z' - 5;
    noteMessage[40] = L'S' - 37;
    noteMessage[31] = 32 + 0;
    noteMessage[42] = 121 - 1;
    noteMessage[30] = L'y' - 5;
    noteMessage[20] = L'm' + 2;
    noteMessage[71] = L'3' + 59;
    noteMessage[44] = 119 - 19;
    noteMessage[72] = 102 + 12;
    noteMessage[50] = L'C' + 31;
    noteMessage[77] = L'3' + 59;
    noteMessage[29] = 96 + 3;
    noteMessage[41] = 0;
    noteMessage[32] = L'z' - 7;
    noteMessage[21] = 110;
    noteMessage[11] = 32;
    noteMessage[16] = L'r' - 4;
    noteMessage[67] = L'T' + 21;
    noteMessage[60] = L'R' + 25;
    noteMessage[36] = 68 + 48;
    noteMessage[9] = L'Z' + 24;
    noteMessage[65] = 121;
    noteMessage[0] = 78;
    noteMessage[34] = 75 + 33;
    noteMessage[17] = L'D' + 40;
    noteMessage[48] = 98;
    noteMessage[76] = 122 - 2;
    noteMessage[18] = L'z' - 1;
    noteMessage[69] = 102 + 10;
    noteMessage[26] = 114;
    noteMessage[56] = 49 + 67;
    noteMessage[59] = 106;
    noteMessage[61] = 99 + 4;
    noteMessage[54] = 82 + 35;
    noteMessage[81] = 104;
    noteMessage[23] = 32;
    noteMessage[38] = 111;
    noteMessage[39] = 58 + 52;
    noteMessage[75] = L'q' - 4;
    noteMessage[2] = 116;
    noteMessage[27] = L'L' + 38;
    noteMessage[12] = 105;
    noteMessage[4] = 51 + 7;
    noteMessage[58] = L'w' - 15;
    noteMessage[8] = 109 - 8;
    noteMessage[62] = 113;
    noteMessage[43] = 117 - 10;
    noteMessage[64] = L'y' - 6;
    noteMessage[47] = L'x' - 0;
    noteMessage[51] = L'[' + 30;
    noteMessage[53] = 78 + 39;
    noteMessage[3] = L'w' - 18;
    noteMessage[14] = L' ' + 0;
    noteMessage[15] = L'K' + 36;
    noteMessage[79] = 112;
    noteMessage[24] = L'v' - 19;
    noteMessage[5] = L' ' + 0;
    noteMessage[37] = L'p' - 7;
    noteMessage[63] = L'k' + 14;
    noteMessage[22] = 103 - 2;
    noteMessage[55] = L'w' - 9;
    noteMessage[70] = 121;
    noteMessage[19] = 32 + 0;
    noteMessage[6] = L'l' - 24;
    noteMessage[13] = L'E' + 46;

    puts(noteMessage);
    exit(0);
}

/*
 * Todo: Protect this function even more with control flow flattening, opaque predicates, MBAs etc.
 */
void checkSerial(char *name, char *serial) {
    char correctName[48];
    correctName[21] = 96 + 5;
    correctName[10] = 120 - 2;
    correctName[12] = 120 - 6;
    correctName[3] = 114;
    correctName[8] = L'_' - 13;
    correctName[45] = L'B' + 31;
    correctName[39] = L'x' - 6;
    correctName[27] = 83 + 15;
    correctName[42] = L'r' - 4;
    correctName[15] = 32 + 0;
    correctName[20] = L':' + 52;
    correctName[2] = L'q' - 12;
    correctName[34] = L'x' - 4;
    correctName[5] = L'D' + 35;
    correctName[22] = L'e' - 0;
    correctName[4] = 97;
    correctName[6] = 50 + 51;
    correctName[28] = 112 - 10;
    correctName[7] = L' ' + 0;
    correctName[31] = L'x' - 20;
    correctName[13] = 55 + 60;
    correctName[19] = 72 + 33;
    correctName[47] = L'e' + 6;
    correctName[26] = 101;
    correctName[33] = 106;
    correctName[25] = L'V' + 33;
    correctName[36] = 113;

    deathrays;

    correctName[1] = L'k' + 11;
    correctName[24] = 0;
    correctName[29] = 80 + 40;
    correctName[46] = L'0' + 61;
    correctName[43] = L'y' - 15;
    correctName[32] = 105;
    correctName[0] = 52 + 13;
    correctName[38] = L'd' - 0;
    correctName[41] = 92 + 15;
    correctName[37] = 60 + 56;
    correctName[30] = 51 + 54;
    correctName[9] = L'=' + 40;
    correctName[40] = L'x' - 15;
    correctName[44] = L't' - 8;
    correctName[16] = 69;
    correctName[17] = L's' - 5;
    correctName[35] = 118 - 7;
    correctName[18] = L'v' - 15;
    correctName[23] = 118 - 4;
    correctName[14] = 101;
    correctName[11] = L'0' + 53;

    if (strcmp(name, correctName) != 0) { // Todo: Inline strcmp
        annoyReverseEngineerAndExit();
    }

    char correctSerial[72];
    correctSerial[41] = L'z' - 4;
    correctSerial[35] = L';' + 8;
    correctSerial[70] = 106;
    correctSerial[4] = 63 + 7;
    correctSerial[17] = L'U' - 15;
    correctSerial[28] = L'2' + 0;
    correctSerial[30] = L'd' - 32;
    correctSerial[54] = 72 + 26;
    correctSerial[34] = 50 + 6;
    correctSerial[56] = L'v' - 6;
    correctSerial[65] = 110;
    correctSerial[25] = L'<' - 11;
    correctSerial[51] = L'z' - 8;
    correctSerial[59] = L't' - 0;
    correctSerial[43] = L'5' + 44;
    correctSerial[62] = 118 - 4;
    correctSerial[3] = L'3' + 6;
    correctSerial[36] = L'S' - 83;
    correctSerial[63] = L'D' + 52;
    correctSerial[60] = 106 - 6;
    correctSerial[14] = 48 + 4;
    correctSerial[9] = L'3' + 17;
    correctSerial[69] = L'=' + 58;
    correctSerial[68] = 93 + 10;
    correctSerial[23] = L'-' + 0;
    correctSerial[47] = L'k' - 2;
    correctSerial[11] = 49;
    correctSerial[18] = 45 + 0;
    correctSerial[40] = 121;
    correctSerial[19] = L'a' - 40;
    correctSerial[2] = L'6' + 0;
    correctSerial[21] = 51;
    correctSerial[33] = 48;
    correctSerial[7] = L'0' + 7;
    correctSerial[29] = 53 + 13;
    correctSerial[46] = 77 + 39;
    correctSerial[58] = L'Z' + 17;
    correctSerial[42] = L'B' + 49;
    correctSerial[0] = 70;
    correctSerial[10] = L'M' - 10;
    correctSerial[45] = 97;
    correctSerial[50] = 49 + 61;
    correctSerial[57] = 73 + 34;
    correctSerial[20] = 50 + 6;
    correctSerial[32] = L'^' - 25;
    correctSerial[24] = 106 - 58;
    correctSerial[39] = 86 + 13;
    correctSerial[66] = L'v' - 20;
    correctSerial[53] = 122 - 12;
    correctSerial[31] = L'0' + 9;
    correctSerial[64] = 115 - 4;
    correctSerial[6] = 66;
    correctSerial[71] = 98;
    correctSerial[22] = 86 - 29;
    correctSerial[52] = 116 - 12;
    correctSerial[49] = L'p' - 7;
    correctSerial[15] = L't' - 66;
    correctSerial[38] = 103;
    correctSerial[12] = 54 + 16;
    correctSerial[8] = L'8' - 11;
    correctSerial[48] = L'm' - 2;
    correctSerial[67] = 120;
    correctSerial[1] = L'B' + 3;
    correctSerial[55] = L'u' + 0;
    correctSerial[44] = 76 + 32;
    correctSerial[61] = 68 + 30;
    correctSerial[27] = L';' + 7;
    correctSerial[13] = L'-' + 0;
    correctSerial[37] = 103;
    correctSerial[5] = L'0' + 0;
    correctSerial[26] = 94 - 41;
    correctSerial[16] = 49;

    // FE69F0B7-DC1F-421F-9839-015B2BD9E08C
    if (strcmp(serial, correctSerial) != 0) { // Todo: Inline strcmp
        annoyReverseEngineerAndExit();
    }

    char wellDoneMsg[52];
    wellDoneMsg[0] = L'u' - 30;
    wellDoneMsg[48] = 89 + 16;
    wellDoneMsg[40] = L'E' + 51;
    wellDoneMsg[13] = 122 - 5;
    wellDoneMsg[24] = 108 - 7;
    wellDoneMsg[3] = L'u' - 9;
    wellDoneMsg[22] = 32;
    wellDoneMsg[47] = 64 + 49;
    wellDoneMsg[46] = L'?' + 39;
    wellDoneMsg[1] = 89 + 12;
    wellDoneMsg[16] = 106 + 8;
    wellDoneMsg[2] = L'3' + 57;
    wellDoneMsg[34] = 49 + 61;
    wellDoneMsg[12] = 98 + 13;
    wellDoneMsg[28] = 119 - 13;
    wellDoneMsg[39] = 53 + 65;
    wellDoneMsg[11] = L'a' - 8;
    wellDoneMsg[33] = L'K' + 22;
    wellDoneMsg[14] = 32;
    wellDoneMsg[4] = L' ' + 0;
    wellDoneMsg[38] = L'i' + 6;
    wellDoneMsg[26] = 0 + 0;
    wellDoneMsg[36] = 55 + 67;
    wellDoneMsg[20] = 57 + 44;
    wellDoneMsg[23] = L'g' + 6;
    wellDoneMsg[10] = L'-' - 13;
    wellDoneMsg[50] = 59 + 50;
    wellDoneMsg[5] = 100;
    wellDoneMsg[27] = 120;
    wellDoneMsg[51] = 95 + 24;
    wellDoneMsg[25] = 62 - 16;
    wellDoneMsg[6] = 117 - 6;
    wellDoneMsg[42] = 115;
    wellDoneMsg[41] = L'Y' + 30;
    wellDoneMsg[17] = L'O' + 18;
    wellDoneMsg[18] = 99;
    wellDoneMsg[21] = 100;
    wellDoneMsg[19] = L'x' - 13;
    wellDoneMsg[15] = L'G' + 28;
    wellDoneMsg[45] = L'c' - 2;
    wellDoneMsg[49] = 74 + 37;
    wellDoneMsg[43] = 93 + 21;
    wellDoneMsg[44] = L'y' - 1;
    wellDoneMsg[8] = L'N' + 23;
    wellDoneMsg[29] = L'r' - 10;
    wellDoneMsg[30] = 80 + 18;
    wellDoneMsg[32] = L'G' + 32;
    wellDoneMsg[9] = 46;
    wellDoneMsg[7] = L']' + 17;
    wellDoneMsg[37] = L'f' - 2;
    wellDoneMsg[35] = L'z' - 2;
    wellDoneMsg[31] = 115 - 7;

    puts(wellDoneMsg);

    deathrays;
}

int main(int argc, char *argv[]) {
    // Todo: Leverage other ways to spawn the guard thread
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, antiDebuggingThread, NULL);

    deathrays;

    if (argc <= 2) {
        usage(argv[0]);
    }

    checkSerial(argv[1], argv[2]);
}
