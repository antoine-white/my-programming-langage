# my-programming-langage

A far from finish small programming langage

Has a interpreter and a compiler (it's more a transpiller to c++ ...)

## exemple (fibonaci):
```js
var u0 = 0;
var u1 = 1;

var fibo_n = 10;
var i = 0;

var tmp;
while(i < fibo_n){
    i = i + 1;
    u1 = u0 + u1;
    u0 = u1 - u0;
}

print u0;
```
