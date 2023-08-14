/*tree.c -- функции поддержки дерева*/ 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "adtlib.h"
/*локальный тип данных*/
typedef struct pair
{
    Trnode * parent;
    Trnode * child;
}Pair;

/*прототипы локальных функций*/
static Trnode * MakeTrnode (const Item * pi);
static bool ToLeft (const Item * i1, const Item * i2);
static bool ToRight (const Item * i1, const Item * i2);
static void AddTrnode (Trnode * new_node, Trnode * root);
static void InOrder (const Trnode * root, void (* pfun) (Item item));
static Pair SeekItem (const Item * pi, const Tree * ptree);
static void DeleteTrnode (Trnode ** ptr);
static void DeleteAllTrnode (Trnode * ptr);

/*определения функций*/
void InitializeTree (Tree * ptree)
{
    ptree -> root = NULL;
    ptree -> size = 0;
}

bool TreeIsEmpty (const Tree * ptree)
{
    if (ptree -> root == NULL)
        return true;
    else
        return false;
}

bool TreeIsFull (const Tree * ptree)
{
    if (ptree -> size == МAXITEMS)
        return true;
    else
        return false; 
}

int TreeItemCount (const Tree * ptree)
{
    return ptree -> size;
}

bool AddItem (const Item * pi, Tree * ptree)
{
    Trnode * new_node;
    
    if (TreeIsFull (ptree))
    {
        
        fprintf (stderr, "Дepeвo переполнено\n");
        return false;                                                           /*преждевременный возврат*/
    }
    if (SeekItem (pi, ptree).child != NULL)
    {
        fprintf (stderr, "Попытка добавления дублированного элемента\n");
        return false;                                                           /*преждевременный возврат*/
    }
    new_node = MakeTrnode (pi);                                                 /*указывает на новый узел*/
    if (new_node == NULL)
    {
        fprintf (stderr, "Не удалось создать узел\n");
        return false;                                                           /*преждевременным возврат*/ 
    }
    /*успешное создание нового узла*/
    ptree -> size++;
    
    if (ptree -> root == NULL)                                                  /*случай 1: дерево пустое*/
        ptree -> root = new_node;                                               /*новый узел - корень дерева*/
    else                                                                        /*случай 2: дерево не пустое*/
        AddTrnode (new_node, ptree -> root);                                    /*добавление узла в дерево*/
    
    return true;                                                                /*возврат в случае успеха*/
}

bool InTree (const Item * pi, const Tree * ptree)
{
    return (SeekItem (pi, ptree).child == NULL)? false: true;
}

bool DeleteItem (const Item * pi, Tree * ptree)
{
    Pair look;
    look = SeekItem (pi, ptree);
    
    if (look.child == NULL)
        return false;
    if (look.parent == NULL)                                                    /*удаление корневого элемента*/
        DeleteTrnode (&ptree -> root);
    else if (look.parent -> left == look.child)
        DeleteTrnode (&look.parent -> left);
    else
        DeleteTrnode (&look.parent -> right);
    
    ptree -> size--;
    
    return true;
}

void Traverse (const Tree * ptree, void (* pfun) (Item item ))
{
    if (ptree != NULL)
        InOrder (ptree -> root, pfun);
}

void DeleteAll (Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllTrnode (ptree -> root);
    ptree -> root = NULL;
    ptree -> size = 0;
}

/*локальные функции*/
static void InOrder (const Trnode * root, void (* pfun) (Item item))
{
    if (root != NULL)
    {
        InOrder (root -> left, pfun);
        (*pfun) (root -> item);
        InOrder (root -> right, pfun);
    }
}

static void DeleteAllTrnode (Trnode * root)
{
    Trnode * pright;
    
    if (root != NULL)
    {
        pright = root -> right;
        DeleteAllTrnode (root -> left);
        free (root);
        DeleteAllTrnode (pright);
    }
}

static void AddTrnode (Trnode * new_node, Trnode * root)
{
    if (ToLeft (&new_node -> item, &root -> item))
    {
        if (root -> left == NULL)                                               /*пустое поддерево*/
            root -> left = new_node;                                            /*поэтому добавить сюда узел*/
        else
            AddTrnode (new_node, root -> left);                                  /*иначе обработать дерево*/
    }
    else if (ToRight (&new_node -> item, &root -> item))
    {
        if (root -> right == NULL)
            root -> right = new_node;
        else
            AddTrnode (new_node, root -> right);
    }
    else
    {
        fprintf (stderr, "Ошибка  местоположения AddTrnode ()\n");
        exit (1); 
    }
}

static bool ToLeft (const  Item * i1, const Item * i2)
{
    int comp1;
    
    if ((comp1 = strcmp (i1 -> petname, i2 -> petname)) < 0)
        return true; 
    else if (comp1 == 0 && strcmp (i1 -> petkind, i2 -> petkind) < 0)
        return true;
    else 
        return false;
}

static bool ToRight (const Item * i1, const Item * i2)
{
    int comp1;
    
    if ((comp1 = strcmp (i1 -> petname, i2 -> petname)) > 0)
        return true;
    else if (comp1 == 0 && strcmp (i1 -> petkind, i2 -> petkind) > 0)
        return true;
    else
        return false;
}

static Trnode * MakeTrnode (const Item * pi)
{
    Trnode * new_node;
    
    new_node = (Trnode *) malloc (sizeof (Trnode));
    
    if (new_node != NULL)
    {
        new_node -> item = *pi;
        new_node -> left = NULL;
        new_node -> right = NULL;
    }
    return new_node; 
}

static Pair SeekItem (const Item * pi, const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree -> root;
    
    if (look.child == NULL)
        return look;                                                            /*преждевременный возврат*/
    
    while (look.child != NULL)
    {
        if (ToLeft (pi, &(look.child -> item)))
        {
            look.parent = look.child;
            look.child = look.child -> left;
        }
        else if (ToRight (pi, &(look.child -> item))) 
        {
            look.parent = look.child;
            look.child = look.child -> right;
        }
        else                                                                    /*если элемент не расположен ни слева, ни справа, он должен быть таким же*/
            break;                                                              /*look.child - это адрес узла, содержащего элемент*/
    }
    return look;                                                                /*возврат в случае успеха*/ 
}

static void DeleteTrnode (Trnode ** ptr)
/*адрес родительского элемента, указывающего на целевой узел*/
{
    Trnode * temp;
    
    //puts ((*ptr) -> item.petname);
    if ((*ptr) -> left == NULL)
    {
        temp = *ptr ;
        *ptr = (*ptr) -> right;
        free (temp); 
    }
    else if ((*ptr) -> right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr) -> left;
        free (temp); 
    }
    else                                                                        /*удаленный узел имеет два дочерних узла*/
    {
        /*выяснение места присоединения правого поддерева*/
        for (temp = (*ptr) -> left; temp -> right != NULL; temp = temp -> right) 
            continue; 
        
        temp -> right = (*ptr) -> right;
        temp = *ptr;
        *ptr = (*ptr) -> left;
        
        free (temp);
    }
}