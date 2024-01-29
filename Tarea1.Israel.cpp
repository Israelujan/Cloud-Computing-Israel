#include <iostream>
#include <omp.h>


#define N 10000  //n�mero de elementos en el arreglo
#define chunk 1000 //cuantos elementos tomar� cada hilo, por lo que la cantidad de hilos ser�an= N/ chunk
#define mostrar 50 //cuantos elementos se van a mostrar

void imprimeArreglo(float* d); //Prototipo de funci�n que se encarga de imprimir los arreglos, se declara que el tipo de dato al que apuntar� el puntero ser� float, el puntero es "d"

int main()
{
    std::cout << "Verificando la ejecuci�n de las directivas OMP!\n";

        # ifdef _OPENMP
            std::cout << "OMP disponible y funcionando" << std::endl;
        # endif
    std::cout << "sumando arreglos en paralelo!\n";

    float a[N], b[N], c[N]; //arreglos de tama�o N

    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 15;  //asiganci�n de valores
        b[i] = (i + 3) * 5;
    }

    //for paralelo con OpenMP, se indican que los arreglos estar�n en un �rea de memoria compartida, para que los diferentes hilos puedan accesar a los valores, la variable "i" de cada hilo debe de ser privada para que no se mezcle
    //con la otra variable
    //pedazos ser� el tama�o de los pedazos que debe de tomar cada hilo
    //la planificaci�n ser� est�tica y se le indica el tama�o de pedazos que debe de tomar

    int pedazos = chunk;


    #pragma omp parallel for \
    shared (a, b, c, pedazos) private(i) \
    schedule (static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a:" << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b:" << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c:" << std::endl;
    imprimeArreglo(c);


}

void imprimeArreglo(float* d) //se imprime parte de los arreglos (variable mostrar), a y b, y el resultado que es la variable c

{
    for (int x = 0; x < mostrar; x++)

        std::cout << d[x] << " - ";
    std::cout << std::endl;

}
