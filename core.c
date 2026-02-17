#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MATRIX_SIZE 64
#define BIRTH_SEED 131019861200L

typedef struct {
    int id;
    double frequency;
    double stability;
} Pillar;

double wave_library[64] = {14.2, 24.5, 5.3, 9.3, 8.2, 11.2, 14.5, 13.6, 17.4, 12.1, 15.7, 5.1, 7.6, 5.9, 8.1, 10.3, 12.9, 15.7, 21.5, 4.3, 6.1, 6.5, 6.7, 6.7, 7.4, 7.9, 7.8, 8.6, 8.9, 9.3, 6.0, 5.7, 7.5, 9.8, 10.4, 12.1, 13.9, 4.1, 5.6, 6.2, 6.7, 7.1, 7.5, 8.3, 8.9, 9.1, 11.4, 15.0, 3.8, 5.2, 6.1, 6.2, 6.6, 7.2, 7.5, 8.4, 9.2, 10.0, 10.4, 5.5, 6.8, 7.4, 11.3, 12.0};

int main() {
    Pillar matrix[MATRIX_SIZE];
    for(int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i].id = i + 1;
        matrix[i].frequency = wave_library[i];
        matrix[i].stability = 1.0;
    }

    // Симуляция 100 тактов для одного запуска Actions
    for(int cycle = 0; cycle < 100; cycle++) {
        FILE *f = fopen("matrix_state.log", "w");
        fprintf(f, "{\"ts\":%ld,\"pillars\":[", (long)time(NULL));
        for(int i = 0; i < MATRIX_SIZE; i++) {
            matrix[i].stability -= (double)(rand() % 100) / 100000.0;
            if (matrix[i].stability < 0.13) matrix[i].stability = 1.0; 
            fprintf(f, "{\"id\":%d,\"f\":%.2f,\"st\":%.3f}%s", i+1, matrix[i].frequency, matrix[i].stability, (i==63?"":","));
        }
        fprintf(f, "]}");
        fclose(f);
        usleep(100000); 
    }
    return 0;
}
