/**
 * MIT License
 * 
 * Copyright (c) 2023 Abish Young
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __QUERYSTRING_H__
#define __QUERYSTRING_H__

#include <stdlib.h>

#include "astring.h"

typedef struct {
    astring_t* key;
    astring_t* value;
} querypair_t;

typedef struct {
    querypair_t** pairs;
    size_t len;
    size_t cap;
} querystring_t;

querypair_t* querypair_new(astring_t* key, astring_t* value);
querypair_t* querypair_from(const char* key, const char* value);
void querypair_free(querypair_t* qp);
void querypair_freeall(querypair_t* qs);

querystring_t* querystring_new();
void querystring_free(querystring_t* qs, bool all);
querystring_t* querystring_add(querystring_t* qs, querypair_t* qp);
querystring_t* querystring_addfrom(querystring_t* qs, const char* key, const char* value);
querystring_t* querystring_remove(querystring_t* qs, const char* key, bool all);
querystring_t* querystring_set(querystring_t* qs, const char* key, astring_t* value);
astring_t* querystring_get(const querystring_t* qs, const char* key);
astring_t* querystring_tostring(const querystring_t* qs);

#endif // __QUERYSTRING_H__