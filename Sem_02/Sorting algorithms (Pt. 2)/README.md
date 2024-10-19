# Рекурсивни сортиращи алгоритми

## Merge sort
Рекурсивен сортиращ алгоритъм, изграден по алгоритмичната схема "**Разделяй и владей**".
![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/MergeSort.png)
![alt_text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/MergeSortComplexity.png)

---
 
## Quick sort
Рекурсивен сортиращ алгоритъм, изграден по алгоритмичната схема "**Разделяй и владей**".
![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/QuickSort.png)

### Сложност по памет на Quick Sort:
$\displaystyle \Theta(1)$

### Сложност по време на Quick Sort:
**Best case и Average case** (пивотът е среден по големина елемент в масива):  
$\displaystyle T(n) = 2 \cdot T\left(\frac{n}{2}\right) + \Theta(n) = \Theta(n\log n)$  
**Worst case** (пивотът е минимален/максимален елемент в масива):  
$\displaystyle T(n) = T(n-1) + T(0) + \Theta(n) = T(n-1) + \Theta(n) = T(n-2) + 2\cdot \Theta(n) = ... = n\cdot \Theta(n) = \Theta(n^2)$  

---

||Merge sort|Quick sort|  
|--|--|--|  
|Най-добър случай (Best case) |$\Theta(n\log n)$ |$\Theta(n\log n)$ |  
|Среден случай (Average case) |$\Theta(n\log n)$ |$\Theta(n\log n)$ |  
|Най-лош случай (Worst case) |$\Theta(n\log n)$ |$\Theta(n^2)$ |  
|Памет |$\Theta(n)$ |$\Theta(1)$ |  
|Стабилност |:heavy_check_mark: |:x: |  
|Недостатъци |Допълнителна памет| Възможност за квадратична по време сложност |

**Теорема** - Не съществува сортиращ алгоритъм, **базиран на директни сравнения**, който в най- лошия случай прави < $n\log n$ стъпки.  

---

## Сортиране в линейно време. Counting sort
Сортирането на произволни елементи, при които не можем да четем конкретните им стойности, а можем само да ги сравняваме помежду им, не може да се извършва асимптотично по-бързо от $\Theta(n \log n)$. Тази долна граница обаче не важи, когато има ограничения върху възможните стойности на елементите.  

Пример за сортиращ алгоритъм, който работи за време $\Theta(n)$, е **сортирането чрез броене (Counting Sort)**. Алгоритъмът работи, като първо обхожда входния масив и създава масив за броене (или хистограма), който проследява колко пъти се среща всяка стойност. След това този масив се използва, за да се изчислят позициите, на които елементите трябва да бъдат поставени в сортирания масив. Накрая, елементите се преместват на правилните им позиции в новия изходен масив, което води до сортиран резултат. Този метод е особено ефективен, когато диапазонът от възможни стойности е сравнително малък спрямо размера на входния масив.  

||Counting sort|  
|--|--|  
|Най-добър случай (BC) |$\Theta(n + m)$ |  
|Среден случай (AC) |$\Theta(n + m)$ | 
|Най-лош случай (WC) |$\Theta(n + m)$ | 
|Памет |$\Theta(n + m)$ | 
|Стабилност |:heavy_check_mark: |

