#ifndef __URLENCODE_H__
#define __URLENCODE_H__

#include "astring.h"

astring_t* urlencode(CURL* curl, astring_t* str);

#endif // __URLENCODE_H__