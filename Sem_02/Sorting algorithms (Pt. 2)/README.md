# Рекурсивни сортиращи алгоритми

## Merge sort
Рекурсивен сортиращ алгоритъм, изграден по алгоритмичната схема "**Разделяй и владей**".
![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/MergeSort.png)
![alt_text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/MergeSortComplexity.png)

---
 
## Quick sort
Рекурсивен сортиращ алгоритъм, изграден по алгоритмичната схема "**Разделяй и владей**".
![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/QuickSort.png)
![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_02/Sorting%20algorithms%20(Pt.%202)/images/QuickSortComplexity.png)

---

||Merge sort|Quick sort|  
|--|--|--|  
|Най-добър случай (Best case) |$\Theta(n\log(n))$ |$\Theta(n\log(n))$ |  
|Среден случай (Average case) |$\Theta(n\log(n))$ |$\Theta(n\log(n))$ |  
|Най-лош случай (Worst case) |$\Theta(n\log(n))$ |$\Theta(n^2)$ |  
|Памет |$\Theta(n)$ |$\Theta(1)$ |  
|Стабилност |:heavy_check_mark: |:x: |  
|Недостатъци |Допълнителна памет| Възможност за квадратична по време сложност |

**Теорема** - Не съществува сортиращ алгоритъм, **базиран на директни сравнения**, който в най- лошия случай прави < $nlog(n)$ стъпки.  

---

## Сортиране в линейно време. Counting sort
Сортирането на **прозволни** елементи, чиито индивидуални стойности не можем четем, а само можем да сравняваме елементите един с друг, не може да става асимптотично по-бързо от $nlog(n)$. Но тази долна граница не е в сила, ако има някакви **ограничения за възможните стойности на елементите**.  

Пример за сортиращ алгоритъм, който работи за време $\Theta(n)$ е Counting sort (Или така нареченият, "Сортиране чрез броене").  
Най - общо казано, алгоритъмът обхожда елементите, създавайки хистограма на броя пъти, в които даден ключ се среща във входните данни.  
След това за всеки елемент от входния масив се определя позиция, на която трябва да бъде поставен в изходния масив.  
Накрая елементите се обхождат отново, като се преместват на сортираните позиции в изходния масив.  

||Counting sort|  
|--|--|  
|Най-добър случай (BC) |$\Theta(n + m)$ |  
|Среден случай (AC) |$\Theta(n + m)$ | 
|Най-лош случай (WC) |$\Theta(n + m)$ | 
|Памет |$\Theta(n + m)$ | 
|Стабилност |:heavy_check_mark: |

