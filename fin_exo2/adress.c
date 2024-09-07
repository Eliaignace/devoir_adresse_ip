
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adress.h"
void int_to_binary(int num, char *binary_str) 
{   
    int i;
    for (i = 31; i >= 0; i--) {
        binary_str[31 - i] = (num & (1 << i)) ? '1' : '0';
    }
    binary_str[32] = '\0';
}


void print_decimal_mask(int subnet_bits) 
{
    int mask = 0;
    int i;
    for (i = 0; i < subnet_bits; i++) 
    {
        mask |= (1 << (31 - i));
    }

    
    int mask_parts[4];
    for (i = 0; i < 4; i++) 
    {
        mask_parts[i] = (mask >> (24 - i * 8)) & 255; 
    }

    printf("Masque sous-réseau en format décimal : %d.%d.%d.%d\n",
           mask_parts[0], mask_parts[1], mask_parts[2], mask_parts[3]); //mamoka anle mask forme decimal
}


void calculate_network_address(const char *ip, int subnet_bits) 
{   
    int mask = 0;
    int ip_parts[4];
    int mask_parts[4];
    int network_parts[4];

    
    sscanf(ip, "%d.%d.%d.%d", &ip_parts[0], &ip_parts[1], &ip_parts[2], &ip_parts[3]);

    int i;
    for (i = 0; i < subnet_bits; i++) 
    {
        mask |= (1 << (31 - i));
    }

    
   

    for (i = 0; i < 4; i++) 
    {
        mask_parts[i] = (mask >> (24 - i * 8)) & 255; 
    }

    
    
    
    for (i = 0; i < 4; i++) 
    {
        network_parts[i] = ip_parts[i] & mask_parts[i];  //calcul adresse reseau
    }

    
    printf("Adresse réseau : %d.%d.%d.%d\n",
           network_parts[0], network_parts[1], network_parts[2], network_parts[3]); //mi -affiche anle adresse reseau en forme decimal
}

void calculate_broadcast_address(const char *ip, int subnet_bits) 
{
    
    int mask = 0;
    int inverted_mask = 0;
    int i;

    int ip_parts[4];
    int broadcast_parts[4];

    
    sscanf(ip, "%d.%d.%d.%d", &ip_parts[0], &ip_parts[1], &ip_parts[2], &ip_parts[3]);

    
    for (i = 0; i < subnet_bits; i++) {
        mask |= (1 << (31 - i));
    }

    
    inverted_mask = ~mask;
    
    // Calculer l'adresse broadcast
    
    
    for (i = 0; i < 4; i++) {
        broadcast_parts[i] = (ip_parts[i] & (mask >> (24 - i * 8))) | ((~(mask >> (24 - i * 8))) & 255);
    }

    // Afficher l'adresse broadcast en format décimal
    printf("Adresse broadcast : %d.%d.%d.%d\n",
           broadcast_parts[0], broadcast_parts[1], broadcast_parts[2], broadcast_parts[3]);
}



void enter_ip_and_bits_reseau(char *adresse)    //mampiditra adresse ip sy bits reseau
{ 
    char *token = NULL;
    char *ip = NULL;
    int subnet_bits;

    printf("Entrez votre adresse IP avec le masque de sous-réseau (ex: 192.168.10.2/12) : ");
    scanf("%s", adresse);

   
    token = strtok(adresse, "/");  // Diviser l'adresse IP et le masque de sous-réseau
    if (token == NULL) 
    {
        printf("Format invalide\n");
        return;
    }

    
    token = strtok(NULL, "/");    // Lire le masque de sous-réseau
    if (token == NULL) 
    {
        printf("Format invalide\n");
        return;
    }

    ip =token;
    subnet_bits = atoi(token);
    if (subnet_bits < 0 || subnet_bits > 32) 
    {
        printf("Nombre de bits de sous-réseau invalide\n");
        return;
    }

    
    print_decimal_mask(subnet_bits);

    calculate_network_address(strtok(adresse, "/"), subnet_bits);

    calculate_broadcast_address(ip, subnet_bits);

}