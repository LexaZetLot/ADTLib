/*tree.h -- двоичное дерево поиска                                              */
/*дублированные элементы в этом дереве не разрешены                             */
#ifndef _TREE_Н
#define _TREE_Н
#include <stdbool.h>
#include "adtlib.h"

#define SLEN 20 
#define МAXITEMS 10

typedef struct trnode
{
    Item item;
    struct trnode * left;   /*указатель на левую ветвь                          */ 
    struct trnode * right;  /*указатель на правую ветвь                         */
}Trnode;

typedef struct tree
{
    Trnode * root;        /*указатель на корень дерева                          */ 
    int size;             /*количеcтво элементов в дереве                       */
}Tree;

/*                        прототипы функций                                     */

/*операция:               инициализация дерева пустым значением                 */
/*начальные условия:      ptree указывает на дерево                             */
/*конечные условия:       дерево инициализировано пустое состояние              */
void InitializeTree (Tree * ptree);

/*операция:               определение, является ли дерево пустым                */
/*начальные условия:      ptree указывает на дерево                             */
/*конечные условия:       функция возвращает true, если дерево пусто, и false - */
/*                        в противном случае                                    */
bool TreeIsEmpty (const Tree * ptree);

/*операция:               определение количества элементов в дереве             */
/*начальные условия:      ptree указывает на дерево                             */
/*конечные условия:       функция возвращает true, если дерево полное, и false -*/
/*                        в противном случае                                    */
bool TreeIsFull (const Tree * ptree);

/*операция:               определение количества элементов в дереве             */
/*начальные условия:      ptree указывает на дерево                             */
/*конечные условия:       функция возвращает количество элементов в дереве      */
int TreeItemCount (const Tree * ptree);

/*операция:               добавление элемента в дерево                          */
/*начальные условия:      pi - адрес добавляемого элемента ptree указывает на   */
/*                        инициализированное дерево                             */
/*конечные условия:       если возможно, функция добавляет элемент к дереву и   */
/*                        и возвращает true; в противном случае она возвращает  */
/*                        false                                                 */
bool AddItem (const Item * pi, Tree * ptree);

/*операция:               поиск элемента в дереве                               */
/*начальные условия:      pi - указывает на элемент ptree указывает на          */
/*                        инициализированное дерево                             */
/*конечные условия:       функция возвращает true, если элемент присутствует    */
/*                        в дереве, и false - в противном случае                */
bool InTree (const Item * pi, const Tree * ptree);

/*операция:               удаление элемента из дерева                           */
/*начальные условия:      pi - адрес добавляемого элемента ptree указывает на   */
/*                        инициализированное дерево                             */
/*конечные условия:       если возможно, функция удаляет элемент из дерева и    */
/*                        возвращает true; в противном случае функция           */
/*                        возвращает false                                      */
bool DeleteItem (const Item * pi, Tree * ptree);

/*операция:               применение указаной функции к каждому элементу в      */
/*                        дереве                                                */
/*начальные условия:      ptree указывает на дерево pfun указывает на функцию,  */
/*                        которая принимает аргумент Item и не имеет            */
/*                        твозвращаемого значения                               */
/*конечные условия:       функция, указанная с помощью pfun, выполняется один   */
/*                        раз для каждого элемента в дереве                     */
void Traverse (const Tree * ptree, void (* pfun) (Item item));

/*операция:               удаление всех элементов из дерева                     */
/*начальные условия:      ptree указывает на инициализированное дерево          */
/*конечные условия:       дерево является пусто                                 */
void DeleteAll (Tree * ptree); 

#endif