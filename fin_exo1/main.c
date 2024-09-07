#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ip.h"
int main()
{
    char adresse[100];
    char* msr=alloc(50);

    char* ip_binaire=alloc(50);
    strcpy(ip_binaire,enter_verify_adress_ip(adresse));
    debug_adress_ip(adresse);
    strcpy(msr,enter_and_binary_msr(msr));
    adresse_reseau_broad_cast(msr,ip_binaire);
    return 0;
}