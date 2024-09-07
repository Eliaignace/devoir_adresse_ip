#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ip.h"

char* alloc(int dim)
{
    char* str=NULL;
    str=(char*)malloc(dim*sizeof(char));
    return str;
}

/*-------------------------------------------------------------*/

char* enter_verify_adress_ip(char *adresse)
{   
    char *token = NULL;
    char* binaire=alloc(50);
    int octets;
    int class;
    ask:
    sprintf(binaire," ");
    printf("Enter your address IP (ex:192.12.1.2): ");
    scanf("%s", adresse);

    if(!debug_adress_ip(adresse))
        goto ask;

    token = strtok(adresse, ".");
    class = atoi(adresse);

    if (token == NULL)
    {
        printf("Invalid IP address format\n");
        goto ask;
        
    }

    while(token != NULL)
    {
        octets = atoi(token);
        if (octets < 0 || octets > 255)
        {
            printf("=> Your address IP is invalid\n");
            goto ask;

        }
        strcat(binaire,transform_ip_binary(octets));
        token = strtok(NULL, ".");
    }
    printf("\n%s",binaire);
    return binaire;
   
}

/*-------------------------------------------------------------*/

int debug_adress_ip(char *adresse)
{   
     
    int i;
    for(i=0 ; i<strlen(adresse) ; i++)
    {
        if(adresse[i]!='.' && strchr("0123456789",adresse[i])==NULL)
        {
            printf("Invalid Adresse IP");
        }
    }
    return 1;
}
/*-------------------------------------------------------------*/

char* transform_ip_binary(int octets)
{   
    char* buffer;
    buffer=(char*)malloc(2*sizeof(char));
    char* binaire;
    binaire=malloc(8*sizeof(char));
    for (int i = 7; i >= 0; i--)
    {
        sprintf(buffer,"%d" ,(octets >> i) & 1);
        strcat(binaire,buffer);
    }
        strcat(binaire," ");
    return binaire;
}
/*-------------------------------------------------------------*/

void display_binary_ip(int octets)
{
    transform_ip_binary(octets);
    printf(" "); 
    
}
/*-------------------------------------------------------------*/

char* enter_and_binary_msr(char *msr)
{
    char* binaire=alloc(50);
    char *token = NULL;
    int octet;
    int class;
    ask:
    sprintf(binaire," ");
    printf("\nEnter your subnet mask: ");
    scanf("%s", msr);


    if(!debug_adress_msr(msr))
        goto ask;

    token = strtok(msr, ".");
    class=atoi(msr);
    
    if (token == NULL)
    {
        printf("Invalid mask subnet format\n");
        goto ask;
    }

    while(token != NULL)
    {
        octet = atoi(token);
        if (octet < 0 || octet > 255)
        {
            printf("=> Your subnet mask is invalid\n");
            goto ask;
        }
        strcat(binaire,transform_ip_binary(octet));
        token = strtok(NULL, ".");

    }
    int nisy1=0;
    int nisy0=0;
    printf("%s", binaire);
    for(int i=0 ; i<35 ; i++)
    {
        if(binaire[i]=='1')
    {
            if(nisy0!=0)
            {
                printf("invalide\n");
                goto ask;
            }
            nisy1++;
    }
        if(binaire[i]=='0')
        {
            nisy0++;
        }
    }
    return binaire;   
    
}

/*-------------------------------------------------------------*/

int debug_adress_msr(char *msr)
{   
     
    int i;
    for(i=0 ; i<strlen(msr) ; i++)
    {
        if(msr[i]!='.'&&strchr("0123456789",msr[i])==NULL)
        {
            printf("Invalid adresse msr\n");
        }
    }
    return 1;
}
/*-------------------------------------------------------------*/

void transform_msr_binary(int octet)
{   
    
    for (int i = 7; i >= 0; i--)
    {   
        printf("BINAIRE MSR  =>");
        printf("%d", (octet >> i) & 1);

    }
}
/*-------------------------------------------------------------*/

void display_binary_msr(char *msr,int octet)
{
    transform_msr_binary(octet);
    printf(" "); 
    
}
    
/*-------------------------------------------------------------*/

void validation_msr(char *msr)
{
    char *token=NULL;
    char verify_code[100];
    int octets;
    int valid = 1;
    int begin=0;

    strcpy(verify_code , msr);
    token=strtok(verify_code , ".");

    while(token != NULL)
    {
        octets=atoi(token);
        int i;
        for(i = 7 ; i >= 0 ; i--)
        {
            int bits = (octets >> i) & 1;
            if(bits == 1)
            {
                if(begin)
                {
                    valid=0;
                    break;
                }
            }

            else
            {
                begin = 1 ;
            }
            token=strtok(NULL, ".");
        }
    }
    if (valid)
    {
        printf("Subnet mask is valid\n");
    }
    else
    {
        printf("Subnet mask is invalid\n");
    }
}

void adresse_reseau_broad_cast(char* A,char* B)
{
    int i;
    char* broadcast=alloc(50);
    char* Adresse=alloc(50);
    for(i=0 ; i<37 ; i++)
    {
        if(A[i]=='1'&&B[i]=='1')
            Adresse[i]='1';

        else if(A[i]==' ')
            Adresse[i]=' ';

        else
            Adresse[i]='0';
    }
    printf("\nadresse_reseau:%s\n", Adresse);
    for(i=0 ; i<37 ; i++)
    {
        if(A[i]=='1')

        {
            A[i]='0';
        }

        else if(A[i]=='0')

        {
            A[i]='0';
        }
    }

    for(i=0 ; i<37 ; i++)
    {
        if(A[i]=='1'||Adresse[i]=='1')
            broadcast[i]='1';
        else if(A[i]==' ')
            broadcast[i]=' ';
        else
            broadcast[i]='0';
    }

    printf("\nbroadcast:%s", broadcast);
    
}
