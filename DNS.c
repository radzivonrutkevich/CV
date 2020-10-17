/*************************************************************************
LAB 1

Edit this file ONLY!

*************************************************************************/

#include "dns.h"
#include "string.h"
#include "stdio.h"

#pragma warning ( disable : 4996 )  // Убирает ошибку предупреждающую о небезопасности методов scanf, printf

typedef struct Element {           // Typedef - любой из возможных типов языка C
    unsigned int ip;               // Ip адрес
    char* name;                 // Не знаем адреса сайте, поэтому в будущем по этому адресу будем выделять необходимую под него память
    struct Element* next;          // Указатель на следующий элемент по этому же индексу
} Element;

struct Element* hashTable[13000] = { NULL }; // Хеш таблица

unsigned int HashFunction(const char* str, unsigned int size) {      // Хеш функция, которая генерирует индекс элементу для хеш таблицы (str - адрес сайта, size = 15000)
    unsigned int hashValue = 0;                         
    while (*str != '\0') {
        hashValue += *str;                                           // К хеш значению добавляем коды элемента всей строки
        str++;
    }
    return hashValue % size; // Чтобы не было слишком и можно было добавить большим (Помещалось до 13000)
}

void AddToHashTable(DNSHandle hDNS, const char* name, unsigned int ip) {
    unsigned int ind = HashFunction(name, 13000);                           // Получаем индекс с помощью хеш функции
    Element* newNode = (Element*)malloc(sizeof(Element));                  // Выделяем память под элемент Element
    newNode->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));  // Выделяем память непосредственно под название сайта

    strcpy(newNode->name, name);           // В нашу память записывает название сайта
    newNode->ip = ip;                      // В нашу память записываем IP сайта
    newNode->next = NULL;                  // И указатель на следующий элемент приравниваем нулю
    if (hashTable[ind] == NULL) {         // Если индекс свободен, то добавляем
        hashTable[ind] = newNode;
    }
    else {                                                            // Если не свободен, то двигаемся до последнего элемента массива и добавляем в него
        short inTable = 0;
        Element* currNode = hashTable[ind];                              // Указатель на адрес элемента массива,предназначенного для хранения элементов с одинаковыми ключами
        int nameCmp = strcmp(name, currNode->name);                   // Если строки равны, то вернётся 0
        if (nameCmp != 0) {
            while (currNode->next != NULL) {
                nameCmp = strcmp(name, currNode->name);               // Двигаемся по элементам и сравниваем название сайта
                if (nameCmp == 0) {
                    inTable = 1;
                    break;
                }
                currNode = currNode->next;
            }
            if (!inTable) {                                           // Если совпаденией не было, то добавляем элемент в массив 
                currNode->next = newNode;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////
int FindIp(const char* name) {
    unsigned int ind = HashFunction(name, 13000);            // Находим необходимый нам индекс по названию сайта
    if (hashTable[ind] == NULL) {                       // если в адресе элемента хэш-таблицы ничего не записано ,то return 0;
        return 0;
    }
    short inTable = 0;
    Element* currNode = hashTable[ind];                     // указатель на адрес элемента массива,предназначенного для хранения элементов с одинаковыми ключами
    while (currNode != NULL) {                           // проходимся по всем элементам с одинаковым ключом и сравниваем название сайта
        int cmpName = strcmp(currNode->name, name);      // strcmp (строки совпадают -> return 0)
        if (cmpName == 0) {
            inTable = 1;                                 // Если совпадения есть ,то возвращаем адрес
            break;
        }
        currNode = currNode->next;
    }
    if (!inTable) {
        return 0;
    }
    return currNode->ip;
}
/////////////////////////////////////////////////////////////////////

DNSHandle InitDNS()
{
    return (DNSHandle)1;
}

void LoadHostsFile(DNSHandle hDNS, const char* hostsFilePath)
{
    int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0;       // Числа для IP адреса
    char name[70];                                // Массив для названия сайта
    char str[200];                                // Массив для названия сайта + IP адреса
    FILE* hostFile = fopen(hostsFilePath, "r");
    if (hostFile != NULL) {
        while (!feof(hostFile)) {                 // Проверяется достигнут ли конец файла
            fgets(str, 200, hostFile);            // Считывает символы
            if (sscanf(str, "%d.%d.%d.%d %s", &ip1, &ip2, &ip3, &ip4, name) == EOF) {
                break;
            }
            AddToHashTable(hostFile, name, (ip1 << 24) + (ip2 << 16) + (ip3 << 8) + ip4); 
        }
    }
    // IMPLEMENT ME =)
}

IPADDRESS DnsLookUp(DNSHandle hDNS, const char* hostName)
{
    // IMPLEMENT ME =)
    unsigned int ip = FindIp(hostName);   
    if (ip == 0)
        return 0;
    return ip;
}

void FreeSonNodes(Element* startNode) { // Освобождение памяти 
    if (startNode == NULL) {
        return;
    }
    if (startNode->next != NULL) {
        FreeSonNodes(startNode->next);
    }
    free(startNode->name);
    free(startNode);
}

void ShutdownDNS(DNSHandle hDNS) // Освобождение памяти 
{
    // IMPLEMENT ME =)
    for (int i = 0; i < 13000; i++) {
        FreeSonNodes(hashTable[i]);
    }
}
