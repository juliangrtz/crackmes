#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int key[] = {193,
192,
195,
194,
197,
196,
199,
198,
201,
200,
203,
202,
205,
204,
207,
206,
209,
208,
211,
210,
213,
212,
215,
214,
};

int len() {
  return 24;
}

unsigned int hexlify(const char * s) {
 unsigned int result = 0;
 int c ;
 if ('0' == *s && 'x' == *(s+1)) { s+=2;
  while (*s) {
   result = result << 4;
   if (c=(*s-'0'),(c>=0 && c <=9)) result|=c;
   else if (c=(*s-'A'),(c>=0 && c <=5)) result|=(c+10);
   else if (c=(*s-'a'),(c>=0 && c <=5)) result|=(c+10);
   else break;
   ++s;
  }
 }
 return result;
}

char *xorencrypt(char * message, char * key) {
    size_t messagelen = strlen(message);
    size_t keylen = strlen(key);

    char * encrypted = malloc(messagelen+1);

    int i;
    for(i = 0; i < messagelen; i++) {
        encrypted[i] = message[i] ^ key[i % keylen];
    }
    encrypted[messagelen] = '\0';

    return encrypted;
}

int main (int argc, char* argv[]) {
	if(argc <= 1) {
		printf("Usage: %s <flag>\n", argv[0]);
		exit(1);
	} else {
		// Convert the hex back to a string.
		char* string[50];
		char* hex = argv[1];
		int len = strlen(hex);
		for (int i = 0, j = 0; j < len; ++i, j += 2) {
			int val[1];
			sscanf(hex + j, "%2x", val);
			string[i] = val[0];
			string[i + 1] = '\0';
		}
		
		printf("%s as a string is '%s'.\n", hex, string);
		
		
		//char hex[100]
		
		//printf("%08x\n", hexlify(xorencrypt("flag{https://www.youtube.com/watch?v=v1POP-m76ac}", "y0ure_cl0se"));
		
		// char* flag = argv[1];
		// int length = len();
		
		// if(strlen(flag) != length)
			// goto wrongFlag;
		
		// char* result = xor(key, 0xC1);
		
		// if(strcmp(flag, result)) {
				// puts("Well done!");
				// exit(0);
		// }
		
		// wrongFlag:
			// puts("Nope. Try again.");
	}
	return 1;
}