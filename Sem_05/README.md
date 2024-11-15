## Задачи

### Задача 1
Даден е списък **l** с елементи стекове.  
Да се дефинира функция *equalize(l)*, която размества елементите на стековете така, че *да няма два стека в l с разлика в броя на елементите, по-голяма от 1*.  

*Пример:*  
*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
5 -> 4 -> 3 -> 2 -> 1         5 -> 4 -> 3
|                             |
v                             v
7 -> 6                        7 -> 6 -> 1
|                             |
v                             v
11 -> 10 -> 9 -> 8            11 -> 10 -> 9
|                             |
v                             v
12                            12 -> 2 -> 8
```

### Задача 2
Даден е списък **l** с елементи опашки от естествени числа.  
Да се дефинира функция, която връща *дали последователната конкатенация на всички опашки образува сортирана редица.*  
**Да се реши с константна памет и да не се променят входните данни!**  

*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
1 -> 2 -> 3                   yes 
|                             1 -> 2 -> 3 -> 6 -> 9 -> 10 -> 
v                             11 -> 22 -> 33
6 -> 9 -> 10
|
v
11 -> 22 -> 33
|
v
empty
```
*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
1                             no
|
v
6 -> 9 -> 10
|
v
9 -> 22
```
*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
1 -> 2 -> 3                   no
|
v
4 -> 5 -> 4
```

### Задача 3
Даден е списък **l** с елементи опашки от естествени числа.  
- Ако **n** последователни опашки са с равна големина, то те са "подобни" и *трябва да се конкатенират*.  
- Ако **две** последователни опашки не са с равен брой елементи, *то той трябва да се изравни с разлика до единица*.  

*Вход:* &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Изход:*
```c++
2 -> 4 -> 6                   2 -> 4 -> 6 -> 8 -> 0 -> 7
|                             |
v                             v
8 -> 0 -> 7                   7 -> 9 -> 23 -> 22
|                             |
v                             v
5 -> 7 -> 9 -> 23 -> 22       9 -> 1 -> 5
|                             |
v                             v
9 -> 1                        2 -> 1 -> 33 -> 44
|
V
2
|
v
1
|
v
33 -> 44
```
