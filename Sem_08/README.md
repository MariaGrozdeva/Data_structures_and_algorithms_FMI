# Самобалансиращи се дървета

Дървета, които се пренареждат така, че да поддържат логаритмична височина.  

# AVL дървета

AVL дърво представлява самобалансиращо се двоично дърво за търсене (BST), при което разликата между височините на лявото и дясното поддърво за всеки възел не може да бъде повече от едно. Разликата между височините на лявото поддърво и дясното поддърво за даден възел се нарича коефициент на баланс на възела (balance factor).  
`bf(node) = height(tree->right) - height(tree->left)`; bf $\in \\{-1,0,1\\}$

Операциите за добавяне, търсене и премахване в AVL дърво са винаги със сложност $\Theta(\log n)$ в **най- лошия случай**.  

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/avl.png)

## Ротации

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/rotation.png)

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/detailedRotation.png)

### `left left case`

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/leftLeftCase.png)

### `left right case`

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/leftRightCase.png)

### `right left case`

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/rightLeftCase.png)

### `right right case`

![alt text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Sem_08/images/rightRightCase.png)
