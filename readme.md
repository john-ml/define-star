## Multi-line C macros

Replaces

```C
#define* F(A1, .., An) {
  S1
  .
  .
  Sn
}
```

With

```C
#define F(A1, .., An) \
  S1 \
  . \
  . \
  Sn
```

