#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree_el {
    int val;
    int peso;
    char *ruta;
    struct tree_el *sibling, *child;
};
typedef struct tree_el node;

void insert(node **tree, node *item)
{
    if (!(*tree))
    {
        *tree = item;
        return;
    }

    if (item->val < (*tree)->val)
        insert(&(*tree)->child, item);
    else if (item->val > (*tree)->val)
            insert(&(*tree)->sibling, item);
}

void print_node_info (node *tree)
{
    if (tree->child && tree->sibling)
    {
        printf("%d, padre de %d, y hermano de %d \n", tree->val, (tree->child)->val, (tree->sibling)->val);
        printf("%s %d", tree->ruta, tree->peso);
    }
    else if (tree->child)
            printf("%d, padre de %d \n", tree->val, (tree->child)->val);
    else if (tree->sibling)
            printf("%d, hermano de %d \n", tree->val, (tree->sibling)->val);
    else
        printf("%d \n", tree->val);
}

void in_order_print(node * tree)
{
    if(tree->child) in_order_print(tree->child);
    print_node_info(tree);
    if(tree->sibling) in_order_print(tree->sibling);
}
void pre_order_print(node * tree)
{
    print_node_info(tree);
    if(tree->child) pre_order_print(tree->child);
    if(tree->sibling) pre_order_print(tree->sibling);
}
void post_order_print(node * tree)
{
    if(tree->child) post_order_print(tree->child);
    if(tree->sibling) post_order_print(tree->sibling);
    print_node_info(tree);
}

void delete_tree (node *tree)
{
    if (tree)
    {
        delete_tree(tree->child);
        delete_tree(tree->sibling);
        free(tree);
    }
}

char* substr(char* cadena, int comienzo, int longitud)
{
    if (longitud == 0) longitud = strlen(cadena)-comienzo-1;
    char *nuevo = (char*)malloc(sizeof(char) * longitud);
    strncpy(nuevo, cadena + comienzo, longitud);
    return nuevo;
}

int main()
{
    node *curr, *root;
    int i, j, num_of_nodes, *node_values, temp, choice, exit=1, order_choice, print_choice;
    /********************/
    int peso = 0, _peso = 0;
    char chara[150];
    char ext[2];
    char *ruta;
    strcpy(chara, "");
    strcpy(ext, "");
    /********************/
    root = NULL;
    FILE *ptr_file;
    ptr_file = fopen("raiz.txt", "r");


  //  printf("%s\n", fgets(chara, 150, ptr_file));


    while (fgets(chara, 150, ptr_file) != NULL)
    {

        //printf("%c  =>", chara[1]);
        //printf ("%d\n", strlen(chara));

        for (i = 0; i < strlen(chara); i++) //Obtiene el tamaño del archivo por separado
        {
            //printf("%c", chara[i]);
            if (chara[i] == ' ')
            {
                //printf("aqui hay un espacio, en %d\n", i);
                for (j = i+1; j < strlen(chara); j++)
                {
                    //printf("%c", chara[j]);
                    _peso = (chara[j] - '0');
                    //printf("%d", _peso);
                    if (_peso >= 0)
                        peso = peso*10 + _peso;
                }
                //printf("%d\n", peso);

                ruta = substr(chara, 0, i);

                curr = (node *)malloc(sizeof(node));
                curr->child = curr->sibling = NULL;
                curr->val = (int)(chara[1]);
                curr->peso = peso;
                curr->ruta = ruta;
                insert(&root, curr);
                //printf("%d <=> ", (int)(chara[1]));
                //printf("%s ", ruta);
                //printf("%d\n", peso);
            }
        }


        peso = 0;
    }
    print_node_info(root);

/*    while (exit)
    {
        print_choice=order_choice=choice=num_of_nodes=temp=0;

        printf ("1.- Crear nuevo arbol\n");
        printf ("2.- Imprime arbol\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                    if (root)   delete_tree(root);
                    root = NULL;
                    //Calcular numero nodos mediante archivo
                    num_of_nodes = 5;
                    node_values = calloc(num_of_nodes, sizeof(int));
                    for (i=1; i<=num_of_nodes; i++)
                    {
                        printf ("Valor de un nodo?: "); scanf ("%d", &node_values[i-1]);
                        if (node_values[0] < node_values[i-1])
                        {
                            temp = node_values[i-1];
                            node_values[i-1] = node_values[0];
                            node_values[0] = temp;
                        }
                    }

                    for(i=1; i<=num_of_nodes; i++) //Creando arbol n-ary segun data ingresada
                    {
                        curr = (node *)malloc(sizeof(node));
                        curr->child = curr->sibling = NULL;
                        curr->val = node_values[i-1];
                        insert(&root, curr);
                    }

                    //print_node_info(root);
                    break;
            case 2:
                    if(root != NULL)
                    {
                        printf ("Seleccione el orden\n");
                        printf("1.In-order\n");
                        printf("2.pre-order\n");
                        printf("3.post-order\n");
                        scanf("%d",&order_choice);

                        switch(order_choice)
                        {
                            case 1:
                                    in_order_print(root);   break;
                            case 2:
                                    pre_order_print(root);  break;
                            case 3:
                                    post_order_print(root); break;
                        }

                    }
                    else
                        printf("\nEl arbol no existe ! ! !\n");
            case 3:
                    delete_tree(root);
                    exit = 0;
        }
    }
    */

    return 0;
}
