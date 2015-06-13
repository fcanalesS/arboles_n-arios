#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** Declarativa del arbol n-ario ***/
struct tree_el {
    int val;
    char *ruta;
    char *peso;
    char *path;
    struct tree_el *sibling, *child;
};
typedef struct tree_el node;
/*** *********** *** ***** ****** ***/

/*** Variables globales para calcular el tamaño de los directorios y total ***/
float size_total = 0;
float size_folder = 0;
/*** ********************************************************************* ***/

/*** Funciones propias del Árbol N-Ario ***/
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

/*** ********* ********** **** **** **** ***/
void print_argument(node *tree, char *p2)
{
    if (tree->sibling)
    {
        if (strstr(tree->sibling->ruta, p2) != NULL)
            printf("%s %s\n", tree->sibling->ruta, tree->sibling->peso);
    }
    else
    {
        if (strstr(tree->ruta, p2) != NULL)
            printf("%s %s\n", tree->ruta, tree->peso);
    }
}

void in_order1(node * tree, char * p2)
{
    if(tree->child) in_order1(tree->child, p2);
    print_argument(tree, p2);
    if(tree->sibling) in_order1(tree->sibling, p2);
}
/*** ********* ********** **** **** **** ***/

/*** ********* ********** **** **** **** ***/
void print_size(node *tree)
{
    if (tree->sibling)
    {
        size_total = size_total + atoi(tree->sibling->peso);
    }
    else
    {
        size_total = size_total + atoi(tree->peso);
    }
}

void in_order2(node * tree)
{
    if(tree->child) in_order2(tree->child);
    print_size(tree);
    if(tree->sibling) in_order2(tree->sibling);
}
/*** ********* ********** **** **** **** ***/

/*** ********* ********** **** **** **** ***/
void print_size_carpeta(node *tree, char *p2)
{
    if (tree->sibling)
    {
        if (strchr(p2, '.') == NULL)
        {
            if (strstr(tree->sibling->ruta, p2) != NULL)
                size_folder = size_folder + atoi(tree->sibling->peso);
        }
    }
    else
    {
        if (strchr(p2, '.') == NULL)
        {
            if (strstr(tree->ruta, p2) != NULL)
                size_folder = size_folder + atoi(tree->peso);
        }
    }
}

void in_order3(node * tree, char * p2)
{
    if(tree->child) in_order3(tree->child, p2);
    print_size_carpeta(tree, p2);
    if(tree->sibling) in_order3(tree->sibling, p2);
}
/*** ********* ********** **** **** **** ***/

/*** ********* ********** **** **** **** ***/
void print_archivo(node *tree, char *p2)
{
    if (tree->sibling)
    {
        if (strchr(p2, '.') != NULL)
        {
            if (strstr(tree->sibling->ruta, p2) != NULL)
                printf("%s\n", tree->sibling->path);
        }
    }
    else
    {
        if (strchr(p2, '.') != NULL)
        {
            if (strstr(tree->ruta, p2) != NULL)
                printf("%s\n", tree->path);
        }
    }
}

void in_order4(node * tree, char *p2)
{
    if(tree->child) in_order4(tree->child, p2);
    print_archivo(tree, p2);
    if(tree->sibling) in_order4(tree->sibling, p2);
}
/*** ********* ********** **** **** **** ***/
void print_extension(node *tree, char *p2)
{
    if (tree->sibling)
    {
        if (strstr(tree->sibling->ruta, p2) != NULL)
            printf("%s\n", tree->sibling->ruta);
    }
    else
    {
        if (strstr(tree->ruta, p2) != NULL)
            printf("%s\n", tree->ruta);
    }
}

void in_order5(node * tree, char *p2)
{
    if(tree->child) in_order5(tree->child, p2);
    print_extension(tree, p2);
    if(tree->sibling) in_order5(tree->sibling, p2);
}
/*** ********* ********** **** **** **** ***/

/*** ********* ********** **** **** **** ***/
int print_delete(node *tree, char *p2)
{
    if (tree->sibling)
    {
        if (strstr(tree->sibling->ruta, p2) != NULL)
        {
            printf("%s\n", tree->sibling->ruta);
            tree->sibling = tree->sibling->sibling;
            free(tree->sibling);
        }
    }
    else
    {
        if (strstr(tree->ruta, p2) != NULL)
        {
            printf("%s\n", tree->ruta);
            tree->child = tree->child->child;
        }
    }
}

void in_order6(node * tree, char *p2)
{
    if(tree->child) in_order6(tree->child, p2);
    print_delete(tree, p2);
    if(tree->sibling) in_order6(tree->sibling, p2);
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
    in_order_print(root);
}

void comando_L2(char *p2, node *root)
{
    in_order1(root, p2);
}

void comando_T(node *root)
{
    in_order2(root);
    printf("Tama\xA4o ocupado\n");
    printf("Tama\xA4o total: %f B <> %f MB <> %f GB\n", size_total, size_total/1048576, size_total/1073741824);
    size_total = 0;
}

void comando_T2(char *p2, node *root)
{
    in_order3(root, p2);
    printf("Tama\xA4o ocupado\n");
    printf("Tama\xA4o total: %f B <> %f MB <> %f GB\n", size_folder, size_folder/1048576, size_folder/1073741824);
    size_folder = 0;
}

void comando_R(char *p2, node *root)
{
    in_order4(root, p2);
}

void comando_E(char *p2, node *root)
{
    printf("--->Comando no implementado<---\n");
}

void comando_I(char *p2, node *root)
{
    char *aux;
    if (strlen(p2) == 1)
    {
        aux = (char *)malloc(3);
        aux[0] = '.';
        strcat(aux, p2);
        aux[3] = '\0';
    }
    else if (strlen(p2) == 2)
    {
        aux = (char *)malloc(4);
        aux[0] = '.';
        strcat(aux, p2);
        aux[4] = '\0';
    }
    else if (strlen(p2) == 3)
    {
        aux = (char *)malloc(5);
        aux[0] = '.';
        strcat(aux, p2);
        aux[5] = '\0';
    }

    in_order5(root, aux);
}
/*** ******** ******* ***/


int main()
{
    node *curr, *root;
    int i, j, temp, exit=1, punto, espacio;
    /********************/
    int c=1;
    char chara[150], op[50];
    char *ruta, *size, *p1, *p2, *path, *ptr, *ex, *ptr2;
    strcpy(chara, "");
    /********************/
    root = NULL;
    FILE *ptr_file;
    ptr_file = fopen("raiz.txt", "r");

    while (fgets(chara, 150, ptr_file) != NULL)
    {
        for (i = 0; i < strlen(chara); i++)
        {
            if (chara[i] == ' ')
            {
                size = substr(chara, i+1, strlen(chara));
                for (j=0; j< strlen(chara); j++)
                {
                    if (size[j] == '\n')
                    {
                        size[j] = '\0';
                    }
                }

                ptr = strrchr(chara, '\\');
                if (ptr)
                {
                    //printf("%d\n", ptr-chara);
                    path = substr(chara, 0, ptr-chara+1);
                    path[ptr-chara+1] = '\0';

                }
                curr = (node *)malloc(sizeof(node));
                curr->child = curr->sibling = NULL;
                ruta = substr(chara, 0, i+1);
                ruta[i+1] = '\0';
                curr->ruta = ruta;
                curr->path = path;
                curr->peso = size;
                curr->val = c;
                insert(&root, curr);
                c++;
            }
        }

    }

    while(exit)
    {
        printf("[mcanales_usach@Console_command]$ ");
        fgets(op, 50, stdin);
        fflush(stdin);

        for (i=0; i< strlen(op); i++)
        {
            if (op[i] == '\n')
                op[i] = '\0';
        }

        if (strchr(op, ' ') == NULL)
        {
            if (strcmp("L", op) == 0 || strcmp("l", op) == 0)
                comando_L1(root);
            else if (strcmp("T", op) == 0 || strcmp("t", op) == 0)
                    comando_T(root);
            else if (strcmp("F", op) == 0 || strcmp("f", op) == 0)
                {
                    system("cls");
                    printf("\n\n\n\n\n\n\n\n\n\t\tAutor: Matias Javier Canales Saavedra\n\n\n\n\n\n\n\n\n");
                    delete_tree(root); // Elimina el árbol
                    system("pause"); // Si se revisa en Linux, cambiar por system("sleep 15");
                    exit = 0;
                }
            else if (strcmp("clear", op) == 0 || strcmp("CLEAR", op) == 0)
                system("cls"); // Si se revisa en Linux cmabiar por system("clear");
            else
                printf("Comando desconocido\n");
        }
        else
        {
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
            else if (strcmp("T", p1) == 0)
                    comando_T2(p2, root);
            else if (strcmp("R", p1) == 0 && strlen(p2) > 0)
                    comando_R(p2, root);
            else if (strcmp("E", p1) == 0 && strlen(p2) > 0)
                    comando_E(p2, root);
            else if (strcmp("I", p1) == 0 && (strlen(p2) > 0) && strlen(p2) <= 3)
                    comando_I(p2, root);
            else
                printf("Comando desconocido\n");
        }
    }

    return 0;
}
