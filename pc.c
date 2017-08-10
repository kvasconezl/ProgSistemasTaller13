#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
	
	int num_hilos_prod= atoi(argv[1]);

	float tiempo_prod= (float)atoi(argv[2]);
	int num_hilos_cons= atoi(argv[3]);
	float tiempo_cons= (float)atoi(argv[4]);
	int tam_cola= atoi(argv[5]);
	int total_items=atoi(argv[6]);

	
	if (argc == 7){
		system("clear");
		printf("________________________________________________\n\n");
		printf("<<<<Simulador productor-consumidor>>>>>>\n");
		printf("________________________________________________\n\n");
		printf("\tNumero de Productores: %d\n",num_hilos_prod );
		printf("\tNumero de Consumidores: %d\n",num_hilos_cons);
		printf("\tTamaño de la Cola: %d\n",tam_cola );
		printf("\tTiempo de Consumo: %.2f\n",tiempo_cons );
		printf("\tTiempo del producción: %.2f\n",tiempo_prod);
		
		printf("\tTotal de Items a producir: %d\n\n",total_items );
		printf("____________________________________________________\n");
	}

	else
	{
		printf("El formato a ingresar es: <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items>\n");
		exit(-1);
		
	}

	return 0;
}
