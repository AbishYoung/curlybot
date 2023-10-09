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

#ifndef __ASTRING_H__
#define __ASTRING_H__

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* raw;      /**< The raw character buffer. */
    size_t len;     /**< The length of the string. */
    size_t cap;     /**< The capacity of the buffer. */
} astring_t;


astring_t* astring_new(size_t cap);
void astring_free(astring_t* astr);
astring_t* astring_resize(astring_t* astr, size_t cap);
astring_t* astring_fit(astring_t* astr);
astring_t* astring_from(const char* str);
astring_t* astring_into(astring_t* astr, const char* str);
astring_t* astring_append(astring_t* astr, const char* str);
astring_t* astring_prepend(astring_t* astr, const char* str);
astring_t* astring_appenda(astring_t* astr, const astring_t* other);
astring_t* astring_prependa(astring_t* astr, const astring_t* other);
bool astring_eq(const astring_t* astr1, const astring_t* astr2);
bool astring_eqs(const astring_t* astr, const char* str);
astring_t* astring_slice(const astring_t* astr, size_t start, size_t end);
bool astring_contains(const astring_t* astr, const astring_t* other);
bool astring_containsc(const astring_t* astr, char c);
bool astring_containss(const astring_t* astr, const char* str);
size_t** astring_findallc(const astring_t* astr, const char c);
bool astring_replaceindex(astring_t* astr, size_t index, const char c);

#endif /* ASTRING_H */
