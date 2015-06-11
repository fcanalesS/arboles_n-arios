#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** Declarativa del arbol n-ario ***/
struct tree_el {
    int val;
    char *ruta;
    char *peso;
    struct tree_el *sibling, *child;
};
typedef struct tree_el node;
/*** *********** *** ***** ****** ***/


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
        printf("%s %s\n", tree->ruta, tree->peso);
    }
    else if (tree->child)
            printf("%s %s\n", tree->child->ruta, (tree->child)->peso);
    else if (tree->sibling)
            printf("%s %s\n", (tree->sibling)->ruta, (tree->sibling)->peso);
    else
        printf("%s %s\n", tree->ruta, tree->peso);
}

/*** Busquedas exclusivas para cada raiz ***/
void print_node(node *tree, char *p2)
{
//    printf("asdqwerty: %s\n", aux);
//
//    if (tree->child && tree->sibling)
//    {
//        printf("%d, padre de %d, y hermano de %d \n", tree->val, (tree->child)->val, (tree->sibling)->val);
//        printf("asd%s\n", tree->ruta);
//    }
//    if (tree->child)
//    {
//        printf("%s\n", tree->child->ruta);
//    }
    if (tree->sibling)
    {
        //printf("%s\n", tree->sibling->ruta);
        if (strstr(tree->sibling->ruta, p2) != NULL)
            printf("%s %s\n", tree->sibling->ruta, tree->sibling->peso);
    }
    else
    {
        //printf("%s\n", tree->ruta);
        if (strstr(tree->ruta, p2) != NULL)
            printf("%s %s", tree->ruta, tree->peso);
    }
}

void in_order(node * tree, char * p2)
{
    if(tree->child) in_order(tree->child, p2);
    print_node(tree, p2);
    if(tree->sibling) in_order(tree->sibling, p2);
}

/*** ********* ********** **** **** **** ***/


void in_order_print(node * tree)
{
    if(tree->child) in_order_print(tree->child);
    print_node_info(tree);
    if(tree->sibling) in_order_print(tree->sibling);
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

/*** Comandos pedidos ***/
void comando_L1(node *root)
{
    //printf("Aqui se imprime todo ;D, Falta orden alfabético aquí y no se porque\nno imprime un registro (￣ー￣； ﾋﾔﾘ \n");
    in_order_print(root);
}

void comando_L2(char *p2, node *root)
{
    //printf("%s\n\n",p2);
    in_order(root, p2);


}

void comando_T(node *root)
{
    printf("Comando de los tamaños de los archivos");
}

void comando_T2(char *p1,char *p2, node *root)
{
    printf("%s %s", p1, p2);
}

void comando_R(char *p1,char *p2, node *root)
{
    printf("%s %s", p1, p2);
}

void comando_E(char *p1,char *p2, node *root)
{
    printf("%s %s", p1, p2);
}

void comando_I(char *p1,char *p2, node *root)
{
    printf("%s %s", p1, p2);
}
/*** ******** ******* ***/


int main()
{
    node *curr, *root;
    int i, j, num_of_nodes, *node_values, temp, choice, exit=1, order_choice, print_choice;
    /********************/
    int c=0;
    char chara[150], op[50];
    char *ruta, *size, *p1, *p2, *pch;
    strcpy(chara, "");
    /********************/
    root = NULL;
    FILE *ptr_file;
    ptr_file = fopen("raiz.txt", "r");

    while (fgets(chara, 150, ptr_file) != NULL)
    {
        for (i = 0; i < strlen(chara); i++) //Obtiene el tamaño del archivo por separado
        {
            if (chara[i] == ' ')
            {
                //for (j = i+1; j < strlen(chara); j++)
                //{
                    //_peso = (chara[j] - '0');
                    //if (_peso >= 0)
                    //    peso = peso*10 + _peso;
                //}

                size = substr(chara, i+1, strlen(chara));
                for (j=0; j< strlen(chara); j++)
                {
                    if (size[j] == '\n')
                    {
                        size[j] = '\0';
                    }
                }
                //printf("%s", size);
                curr = (node *)malloc(sizeof(node));
                curr->child = curr->sibling = NULL;
                curr->ruta = substr(chara, 0, i);
                curr->peso = size;
                curr->val = c;
                insert(&root, curr);
                c++;
            }
        }

    }
    //print_node_info(root);
    //in_order_print(root);

    while(exit)
    {
        printf("[mcanales@root]$ ");
        fgets(op, 81, stdin);

        for (i=0; i< strlen(op); i++)
        {
            if (op[i] == '\n')
                op[i] = '\0';
        }

        if (strchr(op, ' ') == NULL)
        {
            if (strcmp("L", op) == 0)
                comando_L1(root);
            else if (strcmp("T", op) == 0)
                    comando_T(root);
            else if (strcmp("F", op) == 0 || strcmp("f", op) == 0)  { delete_tree(root); exit = 0; }
        }
        else
        {
            //printf("Aqui van los comandos con argumentos\n");
            for (i=0; i< strlen(op); i++)
            {
                if (op[i] == ' ')
                {
                    p1 = substr(op, 0, i);
                    p2 = substr(op, i+1, strlen(op));
                }
            }

            if (strcmp("L", p1) == 0)
                comando_L2(p2, root);
            else if (strcmp("T", p1) == 0 && strlen(p2) > 0)
                    comando_T2(p1, p2, root);
            else if (strcmp("R", p1) == 0 && strlen(p2) > 0)
                    comando_R(p1, p2, root);
            else if (strcmp("E", p1) == 0 && strlen(p2) > 0)
                    comando_E(p1, p2, root);
            else if (strcmp("I", p1) == 0 && strlen(p2) > 0)
                    comando_I(p1, p2, root);


        }
        //printf("%s//", p1);
        //printf("%s", p1);

        //printf("%s", op);

        //exit = 0; //Dejar así para las pruebas =D
    }

    return 0;
}


























/*


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
    */
