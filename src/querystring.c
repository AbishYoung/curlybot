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

#include <stdlib.h>

#include "querystring.h"

/**
 * @brief Create a new querypair_t object
 * 
 * @public
 * 
 * @param key The key of the querypair_t object
 * @param value The value of the querypair_t object
 * @return querypair_t* The new querypair_t object
*/
querypair_t* querypair_new(astring_t* key, astring_t* value) {
    if (key == NULL || value == NULL) return NULL;

    querypair_t* qp = malloc(sizeof(querypair_t));
    qp->key = key;
    qp->value = value;
    return qp;
}

/**
 * @brief Create a new querypair_t object
 * 
 * @public
 * 
 * @param key The key of the querypair_t object
 * @param value The value of the querypair_t object
 * @return querypair_t* The new querypair_t object
*/
querypair_t* querypair_from(const char* key, const char* value) {
    if (key == NULL || value == NULL) return NULL;

    querypair_t* qp = malloc(sizeof(querypair_t));
    qp->key = astring_from(key);
    qp->value = astring_from(value);
    return qp;
}

/**
 * @brief Free a querypair_t object
 * 
 * @note This function does not free the astring_t objects
 * 
 * @public
 * 
 * @param qp The querypair_t object to free
*/
void querypair_free(querypair_t* qp) {
    if (qp == NULL) return;
    if (qp->key == NULL || qp->value == NULL) return;

    free(qp);
}

/**
 * @brief Free a querypair_t object and also free the astring_t objects
 * 
 * @public
 * 
 * @param qp The querypair_t object to free
*/
void querypair_freeall(querypair_t* qp) {
    if (qp == NULL) return;
    if (qp->key == NULL || qp->value == NULL) return;

    astring_free(qp->key);
    astring_free(qp->value);
    free(qp);
}

/**
 * @brief Create a new querystring_t object
 * 
 * @public
 * 
 * @return querystring_t* The new querystring_t object
*/
querystring_t* querystring_new() {
    querystring_t* qs = malloc(sizeof(querystring_t));
    qs->len = 0;
    qs->cap = 8;
    qs->pairs = malloc(sizeof(querypair_t*) * qs->cap);
    return qs;
}

/**
 * @brief Free a querystring_t object
 * 
 * @public
 * 
 * @param qs The querystring_t object to free
 * @param all Whether or not to free the astring_t objects
*/
void querystring_free(querystring_t* qs, bool all) {
    if (qs == NULL) return;
    if (qs->pairs == NULL) return;

    size_t i = 0;

    for (; i < qs->len; i++) {
        if (all == true) querypair_freeall(qs->pairs[i]);
        else querypair_free(qs->pairs[i]);
    }

    free(qs->pairs);
    free(qs);
}

/**
 * @brief Add a querypair_t object to a querystring_t object
 * 
 * @public
 * 
 * @param qs The querystring_t object to add to
 * @param qp The querypair_t object to add
 * @return querystring_t* The querystring_t object
*/
querystring_t* querystring_add(querystring_t* qs, querypair_t* qp) {
    if (qs == NULL || qp == NULL) return NULL;

    if (qs->len == qs->cap) {
        qs->cap *= 2;
        querypair_t* tmp = realloc(qs->pairs, sizeof(querypair_t*) * qs->cap);
        if (tmp == NULL) return qs;
    }

    qs->pairs[qs->len] = qp;
    qs->len++;

    return qs;
}

/**
 * @brief Add a querypair_t object to a querystring_t object
 * 
 * @public
 * 
 * @param qs The querystring_t object to add to
 * @param key The key of the querypair_t object to add
 * @param value The value of the querypair_t object to add
 * @return querystring_t* The querystring_t object
*/
querystring_t* querystring_addfrom(querystring_t* qs, const char* key, const char* value) {
    if (qs == NULL || key == NULL || value == NULL) return NULL;

    querypair_t* qp = querypair_from(key, value);
    return querystring_add(qs, qp);
}

/**
 * @brief Remove a querypair_t object from a querystring_t object
 * 
 * @note This function does not free the astring_t objects
 * 
 * @public
 * 
 * @param qs The querystring_t object to remove from
 * @param key The key of the querypair_t object to remove
 * @return querystring_t* The querystring_t object
*/
querystring_t* querystring_remove(querystring_t* qs, const char* key, bool all) {
    if (qs == NULL || key == NULL) return NULL;

    size_t i = 0;
    size_t index = 0;

    for (; i < qs->len; i++) {
        if (astring_eqs(qs->pairs[i]->key, key) == true) {
            index = i;

            if (all == true) querypair_freeall(qs->pairs[i]);
            else querypair_free(qs->pairs[i]);

            qs->pairs[i] = NULL;

            break;
        }
    }

    // shift from index to end
    for (i = index; i < qs->len - 1; i++) {
        qs->pairs[i] = qs->pairs[i + 1];
    }

    qs->len--;

    return qs;
}

/**
 * @brief Set the value of a querypair_t object in a querystring_t object
 * 
 * @public
 * 
 * @param qs The querystring_t object to set the value in
 * @param key The key of the querypair_t object to set the value of
 * @param value The new value of the querypair_t object
 * @return querystring_t* The querystring_t object
*/
querystring_t* querystring_set(querystring_t* qs, const char* key, astring_t* value) {
    if (qs == NULL || key == NULL || value == NULL) return NULL;

    size_t i = 0;

    for (; i < qs->len; i++) {
        if (astring_eqs(qs->pairs[i]->key, key) == true) {
            astring_free(qs->pairs[i]->value);
            qs->pairs[i]->value = value;
            return qs;
        }
    }

    return qs;
}

/**
 * @brief Get the value of a querypair_t object in a querystring_t object
 * 
 * @public
 * 
 * @param qs The querystring_t object to get the value from
 * @param key The key of the querypair_t object to get the value of
 * @return astring_t* The value of the querypair_t object or NULL if not found
*/
astring_t* querystring_get(const querystring_t* qs, const char* key) {
    if (qs == NULL || key == NULL) return NULL;

    size_t i = 0;

    for (; i < qs->len; i++) {
        if (astring_eqs(qs->pairs[i]->key, key) == true) {
            return qs->pairs[i]->value;
        }
    }

    return NULL;
}

/**
 * @brief Convert a querystring_t object to a string
 * 
 * @public
 * 
 * @param qs The querystring_t object to convert
 * @return astring_t* The string representation of the querystring_t object
*/
astring_t* querystring_tostring(const querystring_t* qs) {
    if (qs == NULL) return NULL;

    astring_t* str = astring_new(32);
    size_t i = 0;

    for (; i < qs->len; i++) {
        str = astring_append(str, qs->pairs[i]->key->raw);
        str = astring_append(str, "=");
        str = astring_append(str, qs->pairs[i]->value->raw);

        if (i < qs->len - 1) astring_append(str, "&");
    }

    return astring_fit(str);
}