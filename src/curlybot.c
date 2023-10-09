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

#include <stdio.h>

#include "astring.h"
#include "querystring.h"

int main(int argc, char** argv) {
    querystring_t* qs = querystring_new();
    astring_t* querystring;

    qs = querystring_addfrom(qs, "action", "query");
    qs = querystring_addfrom(qs, "titles", "Main Page");
    qs = querystring_addfrom(qs, "prop", "revisions");
    qs = querystring_addfrom(qs, "rvprop", "content");
    qs = querystring_addfrom(qs, "format", "json");
    qs = querystring_addfrom(qs, "formatversion", "2");
    querystring = querystring_tostring(qs);

    printf("%s\n", querystring->raw);
    querystring_free(qs, true);

    return 0;
}