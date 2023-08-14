/*queue.h -- интерфейс очереди*/
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
#include "adtlib.h"

#define МAXQUEUE 10
ITEM;
typedef struct node
{
    Item item;
    struct node * next;
}Node; 

typedef struct queue
{
    Node * front;                                                               /*указатель на начало очереди*/
    Node * rear;                                                                /*указатель на конец очереди*/ 
    int items;                                                                  /*количество элементов в очереди*/
}Queue;

/*операция:                инициализация очереди                                */
/*начальное условие:       pq указывает на очередь                              */
/*конечное условие:        очередь инициализирована пустым значением            */
void InitializeQueue (Queue * pq);

/*операция:                проверка того, является ли очередь полной            */
/*начальное условие:       pq указывает на ранее инициализированную очередь     */
/*конечное условие:        возвращает значение True, если очередь полна;        */
/*                         иначе возвращает значение False                      */
bool QueueIsFull (const Queue * pq); 

/*операция:                проверка того, является ли очередь пустой            */
/*начальное условие:       pq указывает на ранее инициализированную очередь     */
/*конечное условие:        возвращает значение True, если очередь пуста;        */
/*                         иначе возвращает значение False                      */
bool QueueIsEmpty (const Queue *pq);

/*операция:                определение количества элементов в очереди           */
/*начальное условие:       pq указывает на ранее инициализированную очередь     */
/*конечное условие:        возвращает число элементов в очереди                 */
int QueueItemCount (const Queue * pq);

/*операция:                добавление элемента в конец очереди                  */
/*начальное условие:       pq указывает на ранее инициализированную очередь     */
/*                         элемент должен быть помещен в конец очереди          */
/*конечное условие:        если очередь не пуста, элемент помещается в конец    */
/*                         очереди и функция возвращает значение True;          */
/*                         в противном случае очередь остается неизменной,      */
/*                         и функция возвращает значение False                  */
bool EnQueue (Item item, Queue * pq);

/*операция:                удаление элемента из начала очереди                  */
/*начальное условие:       pq указывает на ранее инициализированную очередь     */
/*конечное условие:        если очередь не пуста, элемент в начале очереди      */
/*                         копируетсяв *pitem и удаляется из очереди, и функция */
/*                         возвращает значение True; если операцияопустошает    */
/*                         очередь, очередь переустанавливается в пустое        */
/*                         состояние. Если очередь пуста с самого начала,       */
/*                         очередь остается неизменной, и функция возвращает    */
/*                         значение False                                       */
bool DeQueue (Item *pitem, Queue * pq);

/*операция:                опустошение очереди                                  */
/*начальное условие:       pq указывает на ранее инициализированную очередь     */
/*конечное условие:        очередь пуста                                        */
void EmptyTheQueue (Queue * pq);
#endif