#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
// Função para obter o uso da CPU
double get_cpu_usage() {
    FILE *fp;
    char buffer[1024];
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    static unsigned long long prev_user, prev_nice, prev_system, prev_idle, prev_iowait, prev_irq, prev_softirq, prev_steal;
    static int initialized = 0;

    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Falha ao abrir /proc/stat");
        exit(EXIT_FAILURE);
    }

    fgets(buffer, sizeof(buffer), fp);
    sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);
    fclose(fp);

    if (!initialized) {
        prev_user = user;
        prev_nice = nice;
        prev_system = system;
        prev_idle = idle;
        prev_iowait = iowait;
        prev_irq = irq;
        prev_softirq = softirq;
        prev_steal = steal;
        initialized = 1;
        return 0.0; // Na primeira leitura, não há dados anteriores para calcular o uso
    }

    unsigned long long prev_idle_all_time = prev_idle + prev_iowait;
    unsigned long long idle_all_time = idle + iowait;

    unsigned long long prev_total_time = prev_user + prev_nice + prev_system + prev_idle_all_time + prev_irq + prev_softirq + prev_steal;
    unsigned long long total_time = user + nice + system + idle_all_time + irq + softirq + steal;

    unsigned long long total_diff = total_time - prev_total_time;
    unsigned long long idle_diff = idle_all_time - prev_idle_all_time;

    double cpu_usage = (1.0 - ((double)idle_diff / (double)total_diff)) * 100.0;

    prev_user = user;
    prev_nice = nice;
    prev_system = system;
    prev_idle = idle;
    prev_iowait = iowait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;

    return cpu_usage;
}

// Função para obter o uso da RAM
void get_ram_usage(double *total, double *used, double *free, double *available) {
    FILE *fp;
    char buffer[256];
    unsigned long mem_total = 0, mem_free = 0, mem_available = 0, buffers = 0, cached = 0;

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Falha ao abrir /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "MemTotal: %lu kB", &mem_total) == 1 ||
            sscanf(buffer, "MemFree: %lu kB", &mem_free) == 1 ||
            sscanf(buffer, "MemAvailable: %lu kB", &mem_available) == 1 ||
            sscanf(buffer, "Buffers: %lu kB", &buffers) == 1 ||
            sscanf(buffer, "Cached: %lu kB", &cached) == 1) {
            continue;
        }
    }
    fclose(fp);

    unsigned long mem_used = mem_total - mem_free - buffers - cached;
    *total = mem_total / 1024.0 / 1024.0;
    *free = mem_free / 1024.0 / 1024.0;
    *used = mem_used / 1024.0 / 1024.0;
    *available = mem_available / 1024.0 / 1024.0;
}

int main() {
    setlocale(LC_ALL,"Portuguese");
    while (1) {
        double cpu_usage = get_cpu_usage();
        double total_ram, used_ram, free_ram, available_ram;
        get_ram_usage(&total_ram, &used_ram, &free_ram, &available_ram);

        printf("\nUso da CPU: %.2f%%\n", cpu_usage);
        printf("Total de RAM: %.2f GB\n", total_ram);
        printf("RAM Usada: %.2f GB\n", used_ram);
        printf("RAM Livre: %.2f GB\n", free_ram);
        printf("RAM Disponivel: %.2f GB\n", available_ram);

        sleep(1); // Pausa de 1 segundo antes de atualizar as informações
    }

    return 0;
}
