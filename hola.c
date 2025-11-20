/* ING.Jonathan
Media y varianza
29/9/25 
*/

/**
 * char: 8 bits, %c.
 * int: 16 bits, %i.
 * float: 32 bits, %f.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>


void main(){
    /*char mensaje[11]= "Hola mundo";
    char *letra = mensaje;

    do
    {
        printf("Letra: %c\n", *letra);
        letra ++;
    } while (letra);*/

    FILE *archivo = fopen("texto.txt", "r"); // Abre el archivo en modo lectura

    if (archivo == NULL) { // Verifica si el archivo existe o se puede abrir
        printf("No se pudo abrir el archivo.\n");
        return; // Sale del programa si no se puede abrir
    }

    char *contenido = NULL; // Puntero que almacenará el texto leído (memoria dinámica)
    size_t tam = 0;         // Contador de caracteres leídos
    int c;                  // Variable para almacenar cada carácter leído

    /* Lee el archivo carácter por carácter hasta llegar al final (EOF)
    OEF: Es una constante definida en la librería estándar de C (stdio.h) que indica que ya no hay más datos que leer de un archivo o flujo de entrada.*/

    while ((c = fgetc(archivo)) != EOF) {
        // Redimensiona la memoria para incluir el nuevo carácter y el '\0' final
        contenido = realloc(contenido, tam + 2);
        contenido[tam++] = (char)c; // Guarda el carácter leído
    }

    contenido[tam] = '\0'; // Agrega el carácter nulo al final para formar una cadena válida

    printf("Contenido del archivo:\n%s\n", contenido);

    /*char Texto[] = "Este es el primer parrafo con varias palabras.\n\n"
                   "Este es el segundo parrafo, que tambien tiene algunas palabras.\n\n"
                   "Y este es el tercer parrafo con pocas palabras.";*/

    char *letra = contenido;
    int parrafo = 0, palabra = 0, saltos = 0, enPalabra = 0, palabrasParrafo = 0, sumaAux = 0;
    float media = 0, porcentaje = 0, suma = 0;
    int *pila = NULL;
    int top = -1;

    while (*letra) {
        if(*letra == '\n'){
            if(saltos){
                parrafo ++;
                suma += palabrasParrafo;
                /*realloc() redimensiona (amplía o reduce) un bloque de memoria previamente reservado.
                Si pila es NULL, realloc se comporta como malloc, es decir, reserva nueva memoria.
                Si pila ya tenía memoria, la amplía o reduce al nuevo tamaño indicado.*/
                pila = realloc(pila, parrafo * sizeof(int));
                pila[parrafo - 1] = palabrasParrafo;

                palabrasParrafo = 0;
                saltos = 0;
            } else {
                saltos = 1;
            }    
        } else {
            saltos = 0;
        } 

        if (*letra == ' ' || *letra == '\n' || *letra == '.' || *letra == ',') {
            enPalabra = 0; 
        } else if (!enPalabra) {
            palabra++; 
            palabrasParrafo ++;    
            enPalabra = 1; 
        }    
    letra ++;
    }

    if (palabrasParrafo > 0) {
        parrafo ++;
        suma += palabrasParrafo;

        pila = realloc(pila, parrafo * sizeof(int));
        pila[parrafo - 1] = palabrasParrafo;
    }

    media = suma/parrafo;
    double desviacion = 0.0;

    for(int i = 0; i < parrafo; i++){
        porcentaje = (pila[i] / suma) * 100;
        printf("\nPorcentaje de palabras en el parrafo %d: %.2f%%\n", i + 1, porcentaje);
    }

    for(int i = 0; i < parrafo; i++){
        sumaAux += pow(pila[i] - media,2);     
    }
    desviacion = sumaAux / (parrafo - 1);

    printf("Palabras: %i\n", palabra);    
    printf("Parrafos: %i\n", parrafo);  
    printf("Media de palabras por parrafo: %.2f\n", media);
    printf("Desviacion estandar: %.2f\n", desviacion);

    free(contenido);
    free(pila);
    fclose(archivo);
    //liberacion de memoria dinamica y cierre de archivo/
}