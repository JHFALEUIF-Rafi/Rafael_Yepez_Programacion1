/*INTEGRANTES
 1. Jurado Alan
 2. Yépez Rafael*/
 
#include <stdio.h>

int main()
{
    int id, stock, cantidad, opcion;
    char nombre[30];
    float precio, ganancias = 0;

    printf("### SISTEMA DE GESTION ###\n");

    printf("Ingrese el ID del producto: ");
    scanf("%d", &id);

    printf("Ingrese el nombre del producto: ");
    scanf(" %s", nombre);

    printf("Ingrese la cantidad inicial en stock: ");
    scanf("%d", &stock);

    printf("Ingrese el precio unitario: ");
    scanf("%f", &precio);

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
                printf("No se puede realizar la venta.\n");
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
                printf("Cantidad invalida.\n");
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
            printf("Saliendo del sistema...\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}