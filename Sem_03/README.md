# Структури от данни

"Having knowledge of different kinds of data structures available helps the programmer in choosing which data structure suits the best for solving a problem efficiently. It is not just important to make a problem work, it is important how efficiently you make it work."  

## Какво са структурите от данни?  
- В компютърните науки, *структура от данни* е фундаментална концепция, която е от ключово значение за създаването на алгоритми.  
- Тя е начин да организираме информация по начин, по който да можем да я използваме *ефикасно*.  

## Видове структури от данни:
### Линейни (списъчни) структури от данни (Linear Data Structures)
Това са структури, които имат **наредба** на елементите в тях.  
Можем да си ги представяме като "хартиен" списък, в който имаме някакво изброяване (1., 2., 3., ..). Точно както в хартиения списък, така и в списъчните структури, елементите ни са *подредени* по определен начин (имаме първи, след него втори, трети и т.н. до последния).

![alt text](https://i.ibb.co/QJYhwJ4/List.jpg)

#### Какви функционалности бихме очаквали да има една списъчна структура?
1. Добавяне на елемент на произволна позиция (в частност, в началото и в края)  
2. Премахване на елемент от произволна позиция (в частност, от началото и от края)  
3. "Преглед" на произволен елемент (в частност, в началото и в края)  

### Абстрактни структури от данни (Abstract Data Type, ADT)
Абстрактният тип данни (АТД) **дава определена дефиниция (абстракция) на конкретната структура**, т.е. определя допустимите опера­ции и свойства, без да се интересува от конкретната реализация.  
Това позволява една абстрактна структура от данни да има различни реализации и респективно различна ефикасност.  
**Контейнер** се нарича структурата, с която сме реализирали такъв *абстрактен тип данни*.  

![alt text](https://i.ibb.co/z6C7ysm/Data-structures.png)

# Динамичен масив (вектор)
 
 ### Сложност на операциите му:  
 - Добавяне на елемент на произволна позиция -> **O(n)**.  
В частност, добавяне на елемент в края -> **O(1) амортизирано** (константно амортизирано).  
-  Премахване на елемент от произволна позиция -> **O(n)**.  
В частност, премахване на елемент от края -> **O(1) амортизирано** (константно амортизирано).  
- "Преглед" на произволен елемент (в частност, в началото и в края)  -> **O(1)**.  

# Стек
Абстрактен тип данни, базиран на принципа **"Last In First Out (LIFO)"**.  
Обектите могат да се добавят/премахват и преглеждат единствено от горната страна на стека.  
Стекът има три операции:  
-  **push** – добавя нов елемент  най - отгоре  
-  **pop** – премахва най - горния елемент  
- **top** – показва най-горния елемент от стека, без да го премахва   

![alt text](https://i.ibb.co/tpwtT2p/Stack.png)

## Задачи

**Задача 1:** Въвежда се израз в **обратен полски запис**. Да се пресметне неговата стойност.  
Обратен полски запис е *постфиксен запис*. Неговото предимство е, че не се нуждаем от скоби и не е нужно да знаем приоритета на операторите, за да извършим операциите.  
*Примери:*  
|Инфиксен запис |Обратен полски запис |  
|--|--|  
|1 − (2 + 3) |1 2 3 + - |  
|9 - 3 * 4 - 2 * 5 |9 3 4 * - 2 5 * - |  

*Вход: 1 2 3 + -, Изход: -4  
Вход: 9 - 3 * 4 - 2 * 5, Изход: -13*


**Задача 2:** Даден е стринг, съдържащ символите `'(', ')'`, `'{', '}'`, `'['` и `']'`.  
Напишете функция, която проверява дали стрингът е валидно скобуван.  

```c++
Вход: [ ( ) ] { ( ) ( ) } [ { } ], Изход: true.
 ```

```c++
Вход: [ ( ] ), Изход: false.
 ```

```c++
Вход: ( ( ( [ ] ) ) ), Изход: true.
 ```

