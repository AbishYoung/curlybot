#include <curl/curl.h>

#include "astring.h"


/**
 * @brief Creates a new urlencoded astring.
 * 
 * @public
 * 
 * @param str The string to url encode
 * @return astring_t* The new urlencoded astring
*/
astring_t* urlencode(CURL* curl, astring_t* str) {
    if (curl == NULL) return NULL;

    char* encoded;
    astring_t* ret;
    
    encoded = curl_easy_escape(curl, str->raw, str->len);
    if (encoded == NULL) return NULL;

    ret = astring_from(encoded);
    curl_free(encoded);

    return ret;
}
