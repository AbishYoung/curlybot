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

#include "astring.h"

/**
 * Creates a new astring with the given capacity.
 *
 * @public
 *
 * @param cap The initial capacity of the astring.
 * @return The new astring, or NULL if an error occurred.
 */
astring_t* astring_new(size_t cap) {
    if (cap == 0) return NULL; // avoid UB/IDB

    astring_t* tmp = malloc(sizeof(astring_t));
    if (tmp == NULL) return NULL;

    tmp->raw = calloc(cap, sizeof(char));
    if (tmp->raw == NULL) return NULL;

    tmp->len = 0;
    tmp->cap = cap;

    return tmp;    
}

/**
 * Frees the memory used by an astring.
 *
 * @public
 *
 * @param astr The astring to free.
 */
void astring_free(astring_t* astr) {
    if (astr != NULL) {
        if (astr->raw != NULL) {
            free(astr->raw);
            astr->raw = NULL;
        }

        free(astr);
    }
}

/**
 * Resizes the capacity of an astring.
 *
 * @public
 *
 * @param astr The astring to resize.
 * @param cap The new capacity of the astring.
 * @return The resized astring, or NULL if an error occurred.
 */
astring_t* astring_resize(astring_t* astr, size_t cap) {
    if (astr == NULL) return NULL;
    if (astr->raw == NULL) return NULL;
    if (cap == 0) return astr; // avoid UB/IDB

    char* tmp = realloc(astr->raw, cap);
    if (tmp == NULL) return astr; // if realloc returns null the initial pointer is valid

    if (cap < astr->len) {
        astr->raw[cap - 1] = '\0';
        astr->len = cap - 1;
    }

    astr->raw = tmp;
    astr->cap = cap;

    return astr;
}

/**
 * Resizes the capacity of an astring to fit its length.
 *
 * @public
 *
 * @param astr The astring to fit.
 * @return The fitted astring, or NULL if an error occurred.
 */
astring_t* astring_fit(astring_t* astr) {
    if (astr->cap == (astr->len + 1)) return astr;

    astr = astring_resize(astr, astr->len + 1);

    return astr;
}

/**
 * Creates a new astring from a null-terminated string.
 *
 * @public
 *
 * @param str The null-terminated string to create the astring from.
 * @return The new astring, or NULL if an error occurred.
 */
astring_t* astring_from(const char* str) {
    if (str == NULL) return NULL;

    size_t str_len = strlen(str);
    astring_t* tmp = astring_new(str_len + 1);
    if (tmp == NULL) return NULL;

    memcpy(tmp->raw, str, str_len);

    tmp->len = str_len;
    tmp->cap = str_len + 1;

    return tmp;
}

/**
 * Copies a null-terminated string into an astring.
 *
 * @public
 *
 * @param astr The astring to copy the string into.
 * @param str The null-terminated string to copy.
 * @return The updated astring, or NULL if an error occurred.
 */
astring_t* astring_into(astring_t* astr, const char* str) {
    if (astr == NULL || str == NULL || astr->raw == NULL) return NULL;
    size_t str_len = strlen(str);

    if (astr->cap < strlen(str) + 1) {
        astr = astring_resize(astr, strlen(str) + 1);
        if (astr == NULL) return NULL;
    }
    
    memcpy(astr->raw, str, str_len);
    astr->raw[str_len] = '\0';

    astr->len = str_len;

    return astr;
}

/**
 * Appends a null-terminated string to an astring.
 *
 * @internal
 * 
 * @param dest The astring to append to.
 * @param src The null-terminated string to append.
 * @param src_len The length of the null-terminated string to append.
 * @return The updated astring, or NULL if an error occurred.
 */
astring_t* append_impl(astring_t* dest, const char* src, size_t src_len) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    if (dest->cap < (dest->len + src_len)) {
        dest = astring_resize(dest, (dest->cap + src_len));
        if (dest == NULL) {
            return NULL;
        }
    }

    memcpy((dest->raw + dest->len), src, src_len);
    dest->raw[dest->cap - 1] = '\0';

    dest->len += src_len;

    return dest;
}

/**
 * Prepends a null-terminated string to an astring.
 *
 * @internal
 * 
 * @param dest The astring to prepend to.
 * @param src The null-terminated string to prepend.
 * @param src_len The length of the null-terminated string to prepend.
 * @return The updated astring, or NULL if an error occurred.
 */
astring_t* prepend_impl(astring_t* dest, const char* src, size_t src_len) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    if (dest->cap < (dest->len + src_len)) {
        dest = astring_resize(dest, (dest->cap + src_len));
        if (dest == NULL) {
            return NULL;
        }
    }

    // shift the string to the right
    memmove((dest->raw + src_len), dest->raw, dest->len);
    memcpy(dest->raw, src, src_len);
    dest->raw[dest->cap - 1] = '\0';

    dest->len += src_len;

    return dest;
}

/**
 * Appends a null-terminated string to an astring.
 *
 * @public
 * 
 * @param astr The astring to append to.
 * @param str The null-terminated string to append.
 * @return The updated astring, or NULL if an error occurred.
 */
astring_t* astring_append(astring_t* astr, const char* str) {
    size_t str_len = strlen(str);
    return append_impl(astr, str, str_len);
}

/**
 * Prepends a null-terminated string to an astring.
 *
 * @public
 * 
 * @param astr The astring to prepend to.
 * @param str The null-terminated string to prepend.
 * @return The updated astring, or NULL if an error occurred.
 */
astring_t* astring_prepend(astring_t* astr, const char* str) {
    size_t str_len = strlen(str);
    return prepend_impl(astr, str, str_len);
}

/**
 * Appends an astring to another astring.
 *
 * @public
 * 
 * @param dest The destination astring to append to.
 * @param src The source astring to append.
 * @return The updated destination astring, or NULL if an error occurred.
 */
astring_t* astring_appenda(astring_t* dest, const astring_t* src) {
    return append_impl(dest, src->raw, src->len);
}

/**
 * Prepends an astring to another astring.
 *
 * @public
 * 
 * @param dest The destination astring to prepend to.
 * @param src The source astring to prepend.
 * @return The updated destination astring, or NULL if an error occurred.
 */
astring_t* astring_prependa(astring_t* dest, const astring_t* src) {
    return prepend_impl(dest, src->raw, src->len);
}

/**
 * Checks if two astrings are equal.
 *
 * @public
 *
 * @param astr1 The first astring to compare.
 * @param astr2 The second astring to compare.
 * @return True if the astrings are equal, false otherwise.
 */
bool astring_eq(const astring_t* astr1, const astring_t* astr2) {
    if (astr1 == NULL || astr2 == NULL) return false;
    if (astr1->len != astr2->len) return false;

    return (strcmp(astr1->raw, astr2->raw) == 0);
}

/**
 * Checks if an astring is equal to a null-terminated string.
 *
 * @public
 *
 * @param astr The astring to compare.
 * @param str The null-terminated string to compare.
 * @return True if the astring is equal to the string, false otherwise.
 */
bool astring_eqs(const astring_t* astr, const char* str) {
    if (astr == NULL || str == NULL) return false;
    if (astr->len != strlen(str)) return false;

    return (strcmp(astr->raw, str) == 0);
}

/**
 * Creates a new astring from a slice of another astring.
 *
 * @public
 *
 * @param astr The astring to slice.
 * @param start The starting index of the slice.
 * @param end The ending index of the slice.
 * @return The new astring, or NULL if an error occurred.
 */
astring_t* astring_slice(const astring_t* astr, size_t start, size_t end) {
    if (astr == NULL || astr->raw == NULL) return NULL;
    if (start > end || end > astr->len) return NULL;

    size_t cap = (end - start) + 1;
    astring_t* tmp = astring_new(cap);
    if (tmp == NULL) return NULL;

    memcpy(tmp->raw, (astr->raw + start), cap);
    tmp->raw[cap - 1] = '\0';

    tmp->len = cap - 1;
    tmp->cap = cap;

    return tmp;
}

/**
 * Checks if a null-terminated string contains another null-terminated string.
 *
 * @internal
 * 
 * @param astr The null-terminated string to search in.
 * @param src The null-terminated string to search for.
 * @param astr_len The length of the null-terminated string to search in.
 * @param src_len The length of the null-terminated string to search for.
 * @return True if the string contains the other string, false otherwise.
 */
bool contains_impl(const char* astr, const char* src, size_t astr_len, size_t src_len) {
    if (astr_len < src_len) return false;
    
    const char* result = strstr(astr, src);
    return (result != NULL);
}

/**
 * Checks if an astring contains another astring.
 *
 * @public
 * 
 * @param astr The astring to search in.
 * @param src The astring to search for.
 * @return True if the astring contains the other astring, false otherwise.
 */
bool astring_contains(const astring_t* astr, const astring_t* src) {
    if (astr == NULL || src == NULL) return false;

    return contains_impl(astr->raw, src->raw, astr->len, src->len);
}

/**
 * Checks if an astring contains a character.
 *
 * @public
 * 
 * @param astr The astring to search in.
 * @param c The character to search for.
 * @return True if the astring contains the character, false otherwise.
 */
bool astring_containsc(const astring_t* astr, char c) {
    if (astr == NULL) return false;

    char src[2] = {c, '\0'};
    return contains_impl(astr->raw, src, astr->len, 1);
}

/**
 * Checks if an astring contains a null-terminated string.
 *
 * @public
 * 
 * @param astr The astring to search in.
 * @param str The null-terminated string to search for.
 * @return True if the astring contains the string, false otherwise.
 */
bool astring_containss(const astring_t* astr, const char* str) {
    if (astr == NULL || str == NULL) return false;

    return contains_impl(astr->raw, str, astr->len, strlen(str));
}
