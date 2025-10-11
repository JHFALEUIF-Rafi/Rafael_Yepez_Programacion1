/*INTEGRANTES
 1. Jurado Alan
 2. Yépez Rafael
 
 VERSION CORREGIDA */

#include <stdio.h>

int main()
{
    int id, stock, cantidad, opcion;
    char nombre[30];
    float precio, ganancias = 0;

    printf("### SISTEMA DE GESTION ###\n");

    do
    {
        printf("Ingrese el ID del producto: ");
        if (scanf("%d", &id) != 1)
        {
            printf("Error: Ingrese un numero valido.\n");
            while (getchar() != '\n')
                ;
            id = -1;
        }
    } while (id <= 0);

    do
    {
        printf("Ingrese el nombre del producto: ");
        if (scanf(" %29s", nombre) != 1 || nombre[0] == '\0')
        {
            printf("Error: Ingrese un nombre valido.\n");
            while (getchar() != '\n')
                ;
        }
    } while (nombre[0] == '\0');

    do
    {
        printf("Ingrese la cantidad inicial en stock: ");
        if (scanf("%d", &stock) != 1)
        {
            printf("Error: Ingrese un numero valido.\n");
            while (getchar() != '\n')
                ;
            stock = -1;
        }
    } while (stock < 0);

    do
    {
        printf("Ingrese el precio unitario: ");
        if (scanf("%f", &precio) != 1)
        {
            printf("Error: Ingrese un precio valido.\n");
            while (getchar() != '\n')
                ;
            precio = -1;
        }
    } while (precio <= 0);

    do
    {
        printf("\n*** MENU PRINCIPAL ***\n");
        printf("1. Vender producto\n");
        printf("2. Reabastecer producto\n");
        printf("3. Consultar informacion\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nIngrese la cantidad a vender: ");
            scanf("%d", &cantidad);
            if (cantidad <= stock && cantidad > 0)
            {
                stock -= cantidad;
                ganancias += cantidad * precio;
                printf("Venta realizada. Stock restante: %d\n", stock);
            }
            else
            {
                printf("\nNo se puede realizar la venta.\n");
            }
            break;

        case 2:
            printf("\nIngrese la cantidad a reabastecer: ");
            scanf("%d", &cantidad);
            if (cantidad > 0)
            {
                stock += cantidad;
                printf("Stock actualizado: %d\n", stock);
            }
            else
            {
                printf("\nCantidad invalida.\n");
            }
            break;

        case 3:
            printf("\n=== INFORMACION ACTUAL ===\n");
            printf("Producto: %s\n", nombre);
            printf("ID: %d\n", id);
            printf("Stock: %d\n", stock);
            printf("Precio unitario: %.2f\n", precio);
            printf("Ganancias acumuladas: %.2f\n", ganancias);
            break;

        case 4:
            printf("\nSaliendo del sistema...\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}