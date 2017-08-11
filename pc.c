#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cv1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv2 = PTHREAD_COND_INITIALIZER;
int cola = 0;
int t_prod;
int t_cons;
int max;
int tam_cola;
int cont_p = 0;
int done = 0;

void *producir(void *arg) {
    while (1) {
        if (!done) {
            pthread_mutex_lock(&mutex);
            while (cola == tam_cola) {
                pthread_cond_wait(&cv1, &mutex);
            }
            sleep(t_prod);
            if (cont_p == max) {
                done = 1;
                pthread_mutex_unlock(&mutex);
            } else {
                cola++;
                printf("El hilo %lu ha producido 1 item, tamaño de la cola = %d.\n", pthread_self(), cola);
                pthread_mutex_unlock(&mutex);
                pthread_cond_broadcast(&cv2);
                cont_p++;
                printf("MAX: %d cont_p: %d\n", max, cont_p);
            }
        } else {
            pthread_cond_broadcast(&cv2);
            return (void *) 0;
        }
    }
}

void *consumir(void *arg) {
    while (1) {
        // if (!done) {
        pthread_mutex_lock(&mutex);
        while (cola == 0) {
            pthread_cond_wait(&cv2, &mutex);
        }
        sleep(t_cons);
        cola--;
        printf("El hilo %lu ha consumido 1 item, tamaño de la cola = %d.\n", pthread_self(), cola);
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cv1);

        if (cont_p == max && cola == 0) {
            done = 1;
        }
        if (cont_p == max && cola != 0) {
            done = 0;
        }
        // pthread_mutex_unlock(&mutex);
        // pthread_cond_broadcast(&cv1);
        if (done) {
            return (void *) 0;
        }
        // } else {
        //     pthread_cond_broadcast(&cv1);
        //     return (void *) 0;
        // }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("USO: ./pc <num_hilos_prod> <tiempo_prod> <num_hilos_cons> <tiempo_cons> <tam_cola> <total_items>\n");
        exit(-1);
    }

    t_prod = atoi(argv[2]);
    t_cons = atoi(argv[4]);
    max = atoi(argv[6]);
    int num_hilos_p = atoi(argv[1]);
    int num_hilos_c = atoi(argv[3]);
    tam_cola = atoi(argv[5]);
    int status;

    pthread_t *threads_p = malloc(num_hilos_p * sizeof(pthread_t));
    pthread_t *threads_c = malloc(num_hilos_c * sizeof(pthread_t));

    for (int i = 0; i < num_hilos_p; i++) {
        status = pthread_create(&threads_p[i], NULL, producir, NULL);
        if (status != 0) {
            printf("Error al crear el hilo %d\n.", i + 1);
        }
    }

    for (int i = 0; i < num_hilos_c; i++) {
        status = pthread_create(&threads_c[i], NULL, consumir, NULL);
        if (status != 0) {
            printf("Error al crear el hilo consumidor %d\n.", i + 1);
        }
    }

    for (int i = 0; i < num_hilos_p; i++) {
        status = pthread_join(threads_p[i], NULL);
        if (status != 0) {
            printf("Error al esperar por el hilo %d\n.", i + 1);
            exit(-1);
        }
    }

    for (int i = 0; i < num_hilos_c; i++) {
        status = pthread_join(threads_c[i], NULL);
        if (status != 0) {
            printf("Error al esperar por el hilo %d\n.", i + 1);
            exit(-1);
        }
    }

    return 0;
}
