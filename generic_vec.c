#include <stdlib.h>
#include <stdio.h>

#define* MAKE_VEC(T) {
                                                                          
typedef struct {
  size_t capacity;
  size_t length;
  T *contents;
} T##_vec_t;
                                                                        
T##_vec_t T##_vec_new(size_t capacity) {
  return
    (T##_vec_t)
      { .length = 0
      , .capacity = capacity > 1 ? capacity : 1
      , .contents = malloc(capacity * sizeof(T))
      };
}
                                                                        
T T##_vec_get(T##_vec_t *v, size_t i) { return v->contents[i]; }        
                                                                        
void T##_vec_set(T##_vec_t *v, size_t i, T x) { v->contents[i] = x; }   
                                                                        
void T##_vec_resize(T##_vec_t *v) {                                     
  v->capacity *= 2;                                                     
  v->contents = realloc(v->contents, v->capacity * sizeof(T));          
}                                                                       
                                                                        
// comments { are ignored
/* block comments too */
void T##_vec_push(T##_vec_t *v, T x) {                                  
  if (v->length == v->capacity)                                         
    T##_vec_resize(v);                                                  
  v->contents[v->length++] = x;                                         
}

}

MAKE_VEC(int);

typedef char *str;
MAKE_VEC(str);

typedef int (*int_fn)(int);
MAKE_VEC(int_fn);

int square(int x) { return x * x; }
int triple(int x) { return x + x + x; }
int popcnt(int x) { return x ? 1 + popcnt(x & (x - 1)) : 0; }
int factorial(int n) { return n <= 1 ? 1 : n * factorial(n - 1); }

// Aggregate types work fine too
typedef struct { str name; int_fn f; } named_fn;
MAKE_VEC(named_fn);

void main(void) {
  int_vec_t v = int_vec_new(0);
  int_vec_push(&v, 3);
  int_vec_push(&v, 4);
  int_vec_push(&v, 5);
  int_vec_push(&v, 6);
  int_vec_push(&v, 7);
  int_vec_push(&v, 8);
  for (size_t i = 0; i < v.length; ++i)
    printf("v[%lu] = %d\n", i, int_vec_get(&v, i));

  str_vec_t w = str_vec_new(0);
  str_vec_push(&w, "hello");
  str_vec_push(&w, "world");
  str_vec_push(&w, "this");
  str_vec_push(&w, "is");
  str_vec_push(&w, "a");
  str_vec_push(&w, "stack");
  str_vec_push(&w, "of");
  str_vec_push(&w, "strings");
  #define print_strings(u)                \
    for (size_t i = 0; i < u.length; ++i) \
      printf("%s ", str_vec_get(&u, i));  \
    printf("\n");
  print_strings(w);
  str_vec_set(&w, 5, "vector");
  print_strings(w);
  str_vec_push(&w, "now");
  str_vec_push(&w, "with");
  str_vec_push(&w, "more");
  str_vec_push(&w, "words");
  print_strings(w);

  int_fn_vec_t fs = int_fn_vec_new(4);
  fs.length = 4;
  int_fn_vec_set(&fs, 0, square);
  int_fn_vec_set(&fs, 1, triple);
  int_fn_vec_set(&fs, 2, popcnt);
  int_fn_vec_set(&fs, 3, factorial);
  for (size_t i = 0; i < fs.length; ++i)
    printf("fs[%lu](6) = %d\n", i, int_fn_vec_get(&fs, i)(6));

  named_fn_vec_t nfs = named_fn_vec_new(0);
  named_fn_vec_push(&nfs, (named_fn) { .name = "square", .f = square });
  named_fn_vec_push(&nfs, (named_fn) { .name = "triple", .f = triple });
  named_fn_vec_push(&nfs, (named_fn) { .name = "popcnt", .f = popcnt });
  named_fn_vec_push(&nfs, (named_fn) { .name = "factorial", .f = factorial });
  for (size_t i = 0; i < nfs.length; ++i) {
    named_fn fn = named_fn_vec_get(&nfs, i);
    printf("%s[%lu](6) = %d\n", fn.name, i, fn.f(6));
  }
}
