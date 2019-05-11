# `#define*`

Multi-line macros for C.

Replaces ```C
#define* F(A1, .., An) {
  S1
  .
  .
  Sn
}
```

With ```c
#define F(A1, .., An) \
  S1 \
  . \
  . \
  Sn
```

