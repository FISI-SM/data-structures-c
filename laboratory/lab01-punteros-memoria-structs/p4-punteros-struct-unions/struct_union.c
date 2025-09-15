#include <stdio.h>

// ------------------ Constantes ------------------
#define LIFE  1
#define AUTO  2
#define HOME  3

// ------------------ Estructura Dirección ------------------
struct addr {
    char street[50];
    char city[10];
    char zip[5];
};

// ------------------ Estructura Fecha ------------------
struct date {
    int month;
    int day;
    int year;
};

// ------------------ Estructura de la Póliza ------------------
struct str_policy {
    int pol_number;             // Número de póliza
    char name[30];              // Nombre del asegurado
    struct addr address;        // Dirección
    int amount;                 // Monto asegurado
    float premium;              // Prima
    int kind;                   // Tipo de póliza (LIFE, AUTO, HOME)

    // Unión: solo uno de estos bloques se usará según 'kind'
    union {
        // --- Póliza de Vida ---
        struct {
            char beneficiary[30];
            struct date birthday;
        } life;

        // --- Póliza de Automóvil ---
        struct {
            char license[10];
            char state[3];
            char model[15];
            int year;
        } auto;

        // --- Póliza de Residencia ---
        struct {
            int yearbuilt;
            int security; // 1 = sí, 0 = no
        } home;
    };
};

// ------------------ Programa de Ejemplo ------------------
int main() {
    struct str_policy policyinfo;

    // Ejemplo: póliza de vida
    policyinfo.pol_number = 1001;
    policyinfo.kind = LIFE;
    snprintf(policyinfo.name, sizeof(policyinfo.name), "Juan Perez");
    snprintf(policyinfo.address.street, sizeof(policyinfo.address.street), "Av. Principal 123");
    snprintf(policyinfo.address.city, sizeof(policyinfo.address.city), "Lima");
    snprintf(policyinfo.address.zip, sizeof(policyinfo.address.zip), "15001");
    policyinfo.amount = 50000;
    policyinfo.premium = 350.75;

    // Datos específicos de vida
    snprintf(policyinfo.life.beneficiary, sizeof(policyinfo.life.beneficiary), "Maria Perez");
    policyinfo.life.birthday.day = 10;
    policyinfo.life.birthday.month = 5;
    policyinfo.life.birthday.year = 1980;

    // Imprimir ejemplo
    printf("Póliza #%d - Tipo: VIDA\n", policyinfo.pol_number);
    printf("Asegurado: %s\n", policyinfo.name);
    printf("Dirección: %s, %s (%s)\n", policyinfo.address.street,
                                        policyinfo.address.city,
                                        policyinfo.address.zip);
    printf("Monto: %d - Prima: %.2f\n", policyinfo.amount, policyinfo.premium);
    printf("Beneficiario: %s\n", policyinfo.life.beneficiary);
    printf("Fecha Nac. Beneficiario: %02d/%02d/%d\n",
           policyinfo.life.birthday.day,
           policyinfo.life.birthday.month,
           policyinfo.life.birthday.year);

    return 0;
}
