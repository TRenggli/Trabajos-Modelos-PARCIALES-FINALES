#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Operario
{
    int ID;
    char ape[30];
    char obra[30];
    char cat;
    float sueldo;
    int horas;
    float aCobrar;
    int Activo;
};



// Función para listar los datos de los operarios
void listarDatos(struct Operario empleados[], int numEmpleados) //  Si no abriera y/o cerrara el archivo afuera de las funciones y lo haria dentro de estas, tendria que pasarle como un parametro mas, el FILE *pArchivo
{
    printf("ID\tApellido\tObra\tCategoría\tSueldo\tHoras\tA Cobrar\tActivo\n");
    for (int i = 0; i < numEmpleados; i++)
    {
        printf("%d\t%s\t%s\t%c\t\t%.2f\t%d\t%.2f\t%d\n", empleados[i].ID, empleados[i].ape, empleados[i].obra, empleados[i].cat, empleados[i].sueldo, empleados[i].horas, empleados[i].aCobrar, empleados[i].Activo);
    }
}


// Función para agregar un nuevo operario
void altaOperario(struct Operario empleados[], int *numEmpleados)
{
    struct Operario nuevoOperario;
    printf("\nIngrese el ID del nuevo operario: ");
    scanf("%d", &nuevoOperario.ID);
    printf("\nIngrese el apellido del nuevo operario: ");
    scanf("%s", nuevoOperario.ape);
    printf("\nIngrese la obra del nuevo operario: ");
    scanf("%s", nuevoOperario.obra);
    printf("\nIngrese la categoría del nuevo operario: ");
    scanf(" %c", &nuevoOperario.cat);
    printf("\nIngrese el sueldo del nuevo operario: ");
    scanf("%.2f", &nuevoOperario.sueldo);
    printf("\nIngrese las horas trabajadas del nuevo operario: ");
    scanf("%d", &nuevoOperario.horas);
    nuevoOperario.aCobrar = 0.0;
    nuevoOperario.Activo = 1;

    empleados[*numEmpleados] = nuevoOperario;
    (*numEmpleados)++;

    printf("Operario dado de alta exitosamente.\n");
}


// Función para calcular el importe a cobrar por cada operario
void calcularImporte(struct Operario empleados[], int numEmpleados)
{
    for (int i = 0; i < numEmpleados; i++)
    {
        empleados[i].aCobrar = empleados[i].sueldo * empleados[i].horas;
        printf("Importe a cobrar para el operario %d: %.2f\n", empleados[i].ID, empleados[i].aCobrar);
    }
}


// Función para eliminar lógicamente datos de un operario buscado por apellido
void eliminarOperario(struct Operario empleados[], int *numEmpleados, char apellido[])
{
    int encontrado = 0;
    for (int i = 0; i < *numEmpleados; i++)
    {
        if (strcmp(empleados[i].ape, apellido) == 0)
        {
            for (int j = i; j < *numEmpleados - 1; j++)
            {
                empleados[j] = empleados[j + 1];
            }
            (*numEmpleados)--;
            encontrado = 1;
            break;
        }
    }

    if (encontrado)
    {
        printf("Operario eliminado exitosamente.\n");
    }
    else
    {
        printf("No se encontró ningún operario con ese apellido.\n");
    }

}



// Función principal
int main() {
    struct Operario empleados[20];
    int numEmpleados = 10; // Seria la cantidad de veces que se cargaran los diversos datos del struct. La cantidad que de personas, empresas etc que va a tener mi pArchivo.
                           // A su vez cada persona o empleado tendra sus respectivos datos. En este caso tenemos 10, por ende cargaremos los datos de 10 operarios

    int RecordarOperarios; // use esta variable para ver si queria ver devuelta la lista con los datos cargados. Si queria ver la lisita para saber que apellido eliminar, ponia 1 y si no queria verla ponia 0

    int ElijeMenu; // ElijeMenu que reprsenta que menu elije el usuario.
    char apellido[30];

    FILE *pArchivo;

    pArchivo = fopen("empleados2.dat", "w+b"); // Si el pArchivo no existe, crearlo
    // Cargar datos iniciales
    empleados[0] = (struct Operario) {1, "Apellido1", "Obra1", 'A', 1500.0, 40, 0.0, 1};
    empleados[1] = (struct Operario) {2, "Apellido2", "Obra2", 'B', 1800.0, 45, 0.0, 1};
    empleados[2] = (struct Operario) {3, "Apellido3", "Obra3", 'C', 1800.0, 45, 0.0, 1};
    empleados[3] = (struct Operario) {4, "Apellido4", "Obra4", 'D', 1800.0, 45, 0.0, 1};
    empleados[4] = (struct Operario) {5, "Apellido5", "Obra5", 'E', 1800.0, 45, 0.0, 1};
    empleados[5] = (struct Operario) {6, "Apellido6", "Obra6", 'F', 1800.0, 45, 0.0, 1};
    empleados[6] = (struct Operario) {7, "Apellido7", "Obra7", 'G', 1800.0, 45, 0.0, 1};
    empleados[7] = (struct Operario) {8, "Apellido8", "Obra8", 'H', 1800.0, 45, 0.0, 1};
    empleados[8] = (struct Operario) {9, "Apellido9", "Obra9", 'I', 1800.0, 45, 0.0, 1};
    empleados[9] = (struct Operario) {10, "Apellido10", "Obra10", 'J', 1800.0, 45, 0.0, 1};

    fwrite(empleados, sizeof(struct Operario), numEmpleados, pArchivo); // Escribe los datos en el archivo desde el arreglo empleados
    /*La función fwrite se utiliza para escribir bloques de datos en un archivo. Aquí está una explicación de cada uno de sus parámetros:
    empleados: Es el puntero al bloque de memoria desde donde se va a escribir en el archivo. En este caso, empleados parece ser un array de estructuras struct Operario, y fwrite escribirá los datos almacenados en este array en el archivo.
    sizeof(struct Operario): Indica el tamaño en bytes de cada elemento de la estructura struct Operario. sizeof es un operador en C que devuelve el tamaño en bytes del tipo de dato o estructura proporcionada como argumento. Esto se usa aquí para asegurar que se escriba la cantidad correcta de bytes en el archivo para cada elemento de tipo struct Operario.
    numEmpleados: Es la cantidad de elementos de tipo struct Operario que se van a escribir en el archivo. Este parámetro indica cuántos elementos se tomarán del array empleados para escribir en el archivo.
    pArchivo: Es un puntero al archivo donde se escribirán los datos. Este archivo debe haber sido abierto previamente con la función fopen en un modo que permita la escritura, como "w+b" o "r+b" (lectura y escritura binaria).
    */
    fclose(pArchivo); // Cierra el archivo



    do{
        printf("\n*** Menú ***\n");
        printf("1. Listar todos los datos del archivo\n");
        printf("2. Alta de un nuevo operario\n");
        printf("3. Calcular importe a cobrar por cada operario\n");
        printf("4. Eliminar lógicamente datos de un operario buscado por apellido\n");
        printf("0. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &ElijeMenu);

        switch (ElijeMenu) {
            case 1:
                pArchivo = fopen("empleados2.dat", "rb"); // abre un archivo en modo de lectura binaria, permitiendo solo operaciones de lectura
                if (pArchivo != NULL) {
                    listarDatos(empleados, numEmpleados);
                    fclose(pArchivo);
                    printf("\nVolviendo al menu principal...(aprete ENTER)\n");
                    system("pause");
                }
                else {
                    printf("Error en la creacion del archivo!");
                }
                break;


            case 2:
                if(pArchivo != NULL) {
                    pArchivo = fopen("empleados2.dat", "r+b"); // abre un archivo en modo de lectura y escritura binaria, permitiendo tanto operaciones de lectura como de escritura.
                                                                             // Este modo te permite leer y escribir en cualquier parte del archivo sin borrar su contenido previo.
                    fseek(pArchivo, 0, SEEK_END); // Esto mueve el puntero al final del archivo (SEEK_END) desplazándose 0 bytes desde el final del archivo, lo que esencialmente lo deja al final actual.
                    altaOperario(empleados,&numEmpleados);
                    fwrite(&empleados[numEmpleados - 1], sizeof(struct Operario), 1, pArchivo); // Escribir el último operario añadido al final del archivo
                                                                                                                    // &empleados[numEmpleados - 1]: Es el puntero al último elemento del arreglo empleados, que contiene los datos del nuevo operario que se quiere escribir en el archivo.
                                                                                                                    //sizeof(struct Operario): Es el tamaño en bytes de la estructura Operario, indicando cuántos bytes se van a escribir en el archivo por cada elemento.
                                                                                                                    //1: Indica que se está escribiendo un solo elemento.
                                                                                                                    //pArchivo: Es el puntero al archivo en el que se escribirán los datos del nuevo operario.
                    fclose(pArchivo); // Cerrar el archivo después de escribir
                }else {
                    printf("Error: el archivo no existe\n");
                }
                break;


            case 3:
                pArchivo = fopen("empleados2.dat", "rb");
                if (pArchivo != NULL) {
                    calcularImporte(empleados, numEmpleados);
                    fclose(pArchivo);

                    printf("\n¡IMPORTES CALCULADOS CON EXITO!");
                    printf("\nVolviendo al menu principal...(aprete ENTER para volver)\n");
                    system("pause");

                } else {
                    printf("Error al abrir el archivo para calcular el importe.\n");
                }
                break;


            case 4:
                pArchivo = fopen("empleados2.dat", "r+b"); // Abre el archivo en modo lectura y escritura binaria
                if (pArchivo != NULL) {
                    printf("Antes se eliminar al operario por apellido, desea ver la lista de los operarios nuevamente para asi evitar inconvenientes? (1 para SI o un 0 en el caso de que NO desee ver la lista nuevamente): \n");
                    scanf("%d", &RecordarOperarios);

                    if(RecordarOperarios == 1) {
                        listarDatos(empleados, numEmpleados);
                        printf("\nIngrese el apellido del operario a eliminar: ");
                        scanf("%s", apellido);
                        eliminarOperario(empleados, &numEmpleados, apellido);
                        // Ahora, reescribe los datos en el archivo después de la eliminación
                        fseek(pArchivo, 0, SEEK_SET); // Mueve el puntero al inicio del archivo. Esta línea se usó para asegurarse de que el puntero esté al principio del archivo antes de escribir los datos actualizados.
                        fwrite(empleados, sizeof(struct Operario), numEmpleados, pArchivo); // Escribe los datos actualizados
                    }
                    else {
                        printf("Ingrese el apellido del operario a eliminar: ");
                        scanf("%s", apellido);
                        eliminarOperario(empleados, &numEmpleados, apellido);
                        // Ahora, reescribe los datos en el archivo después de la eliminación
                        fseek(pArchivo, 0, SEEK_SET); // Mueve el puntero al inicio del archivo
                        fwrite(empleados, sizeof(struct Operario), numEmpleados, pArchivo); // Escribe los datos actualizados
                    }
                    fclose(pArchivo); // Cierra el archivo independientemente de la eleccion anterior
                } else {
                    printf("Error en la apertura del archivo.\n");
                }
                break;


            case 0:
                printf("Saliendo del programa...\n");
                break;


            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }
    } while (ElijeMenu != 0);

    return 0;
}
