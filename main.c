#include <stdio.h>
#include <stdlib.h>

struct tree_el {
    int val;
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
        printf("%d, padre de %d, y hermano de %d \n", tree->val, (tree->child)->val, (tree->sibling)->val);
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

int main()
{
    node *curr, *root;
    int i, num_of_nodes, *node_values, temp, choice, exit=1, order_choice, print_choice;
    root = NULL;

    while (exit)
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


    return 0;
}
