#pragma once

#include <stdio.h>
#include <stdlib.h>

#define LINKT_INIT(T) \
    typedef struct { \
        void* prev; \
        void* next; \
        T data; \
    } Linkt_##T; \
    typedef Linkt_##T* LinktRef_##T; \
    \
    static Linkt_##T* linkt_new_##T() { \
        Linkt_##T* l = malloc(sizeof(Linkt_##T)); \
        l->next = NULL; \
        l->prev = NULL; \
        return l; \
    } \
    \
    static void linkt_before_##T(Linkt_##T* x, Linkt_##T* y) { \
        x->prev = y; \
        y->next = x; \
    } \
    \
    static void linkt_after_##T(Linkt_##T* x, Linkt_##T* y) { \
        x->next = y; \
        y->prev = x; \
    } \
    \
    static Linkt_##T* linkt_destroy_##T(Linkt_##T* x) { \
        Linkt_##T* p = x->prev; \
        Linkt_##T* n = x->next; \
        \
        if (p != NULL && n != NULL) { \
            p->next = p; \
            n->prev = n; \
        } else if (n == NULL && p != NULL) { \
            p->next = NULL; \
        } else if (p == NULL && n != NULL) { \
            n->prev = NULL; \
        } \
        \
        free(x); \
        \
        if (p == NULL) { \
            if (n != NULL) { \
                return n; \
            } \
        } \
        \
        return NULL; \
    } \
    \
    static void linkt_pushfront_##T(Linkt_##T** x, Linkt_##T* y) { \
        if (*x == NULL) { \
            *x = y; \
        } else { \
            Linkt_##T* xx = *x; \
            y->next = *x; \
            xx->prev = y; \
            *x = y; \
        } \
    } \
    \
    static Linkt_##T* linkt_popfront_##T(Linkt_##T** x) { \
        if (*x == NULL) { \
            return NULL; \
        } else { \
            Linkt_##T* xx = *x; \
            \
            if (xx->next != NULL) { \
                Linkt_##T* next = xx->next; \
                xx->next = NULL; \
                next->prev = NULL; \
                *x = next; \
            } else {\
                *x = NULL; \
            } \
            return xx; \
        } \
    } \
    \

#define linkt_new(T) linkt_new_##T() 
#define linkt_before(T, X, Y) linkt_before_##T(X, Y) 
#define linkt_after(T, X, Y) linkt_after_##T(X, Y) 
#define linkt_destroy(T, X) linkt_destroy_##T(X) 
#define linkt_pushfront(T, X, Y) linkt_pushfront_##T(X, Y)
#define linkt_popfront(T, X) linkt_popfront_##T(X)
