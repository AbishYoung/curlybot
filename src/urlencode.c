#include <curl/urlapi.h>

#include "astring.h"


/**
 * @brief Creates a new urlencoded astring.
 * 
 * @public
 * 
 * @param str The string to url encode
 * @return astring_t* The new urlencoded astring
*/
astring_t* urlencode(astring_t* str) {
    if (str == NULL) return NULL;

    
    size_t i = 0;

    for(; i < str->len; i++) {

    }
}
