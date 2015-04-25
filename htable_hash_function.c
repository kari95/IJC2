// htable_hash_function.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include "htable.h"

unsigned int hash_function(const char *str, unsigned htab_size) {
	unsigned int h=0;
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
	  	h = 65599*h + *p;
	return h % htab_size;
}