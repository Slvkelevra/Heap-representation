#include <stdio.h>
#include <stdlib.h>

#define DIM_NOME 50
#define DIM_HEAP 50

//Estructura que representa un prontoSoccorso
typedef struct
{
    int numeroB;
    int numeroG;
    int numeroV;
    int numeroR;
} ProntoSoccorso;

//Enumeracion que representa los colores del pronto soccorso
typedef enum {BIANCO, VERDE, GIALLO, ROSSO} Codice;

//Estructura que representa un paciente
typedef struct
{
    char nome[DIM_NOME];    
    Codice codice;
    int ordine;
}Pacientes;

Pacientes codaPrio[DIM_HEAP];
int dim_coda=0;



//******************************************************************************
//                      FUNCION priority
//Esta funcion representa la prioridad del paciente
//******************************************************************************

//1 significa primero mayor que el segundo
int priority(Pacientes uno,Pacientes due){
    if(uno.codice==due.codice){
        if(uno.ordine<due.ordine){
            return 1;
        }
    }else{
        return 2;
    }
}

//******************************************************************************
//                      FUNCION insertarPaciente
//Inserta un paciente en la cola
//******************************************************************************

void inserirePaziente(Pacientes un_paziente,Pacientes coda[],int &dim_coda){
    
    //Insertamos el paciente al final
    coda[dim_coda]=un_paziente;
    //int auxt=dim_coda;
    
    while(coda[dim_coda].codice > coda[dim_coda].codice){
   
        
        Pacientes aux = coda[dim_coda/2];
        coda[dim_coda/2]=coda[dim_coda];
        coda[dim_coda]=aux;
        dim_coda=dim_coda/2;
    }
    dim_coda++;
    
}

int priorita(Pacientes *pz1, Pacientes *pz2){
    //si el paciente 1 tiene mayor prioridad
    if(pz1->codice > pz2->codice){
        return 1;
    }else if(pz1->codice < pz2->codice){
        return 2;
    }else{
        //Si el paciente 1 tiene mayor prioridad pero ha llegado antes
        if(pz1->ordine <= pz2->ordine){
            return 1;
        }else{
            return 2;
        }
    }
}

//******************************************************************************
//                      FUNCION insertHeap
//Esta funcion inserta en el heap dependiendo de la prioridad
//******************************************************************************


void insertHeap(Pacientes *pz){  
    int prioridad=0;
    int i=0;
    
    //El heap esta lleno
    if(dim_coda == DIM_HEAP-1){
        printf("\nEl heap esta lleno.\n");
        return;
    }
    
    dim_coda=dim_coda+1;
    i=dim_coda;
    
    //Controlamos la prioridad
    prioridad=priorita(pz,&codaPrio[i/2]);
    
    //Vamos buscando hasta insertar donde la prioridad sea mayor
    while((i != 1) && prioridad == 1){
        codaPrio[i]=codaPrio[i/2];
        i=i/2;
    }
    
    codaPrio[i]=*pz;
}

//******************************************************************************
//                      FUNCION nuevoPaziente
//Esta funcion aniade un nuevo paciente 
//******************************************************************************


Pacientes nuovoPaziente(ProntoSoccorso *ps){
    
    Pacientes p;

    printf("\nNombre del paciente -> ");
    scanf("%[^\n]s", p.nome);
    getchar();

    do
    {
        printf("\nCodigo de paciente (0 = blanco, 1 = verde, 2 = amarillo, "
                "3 = rojo)-> ");
        scanf("%u", &p.codice);
        getchar();

        if(p.codice < BIANCO || p.codice > ROSSO)
            printf("\nCodigo no valido");
    }while(p.codice < BIANCO || p.codice > ROSSO);

    if(p.codice == BIANCO)
    {
        ps->numeroB++;
        p.ordine = ps->numeroB;
    }
    else if(p.codice == GIALLO)
    {
        ps->numeroG++;
        p.ordine = ps->numeroG;

    }
    else if (p.codice == VERDE)
    {
        ps->numeroV++;
        p.ordine = ps->numeroV;
    }
    else
    {
        ps->numeroR++;
        p.ordine = ps->numeroR;
    }

    return p;
}


void printPaziente(Pacientes *pz){
    printf("\nNombre: %s", pz->nome);
    printf("\nCodigo: %u", pz->codice);
    printf("\nPosicion: %d\n", pz->ordine);
}

Pacientes cancelaPaziente(){
    Pacientes item=codaPrio[1];
    Pacientes temp=codaPrio[dim_coda];
    
    dim_coda=dim_coda-1;
    int padre=1;
    int hijo=2;
    
    int prioridad=priorita(&codaPrio[hijo], &codaPrio[hijo+1]);
    
    while(hijo <= dim_coda){
        if((hijo < dim_coda) && prioridad == 2)
            hijo++;
        
        if(priorita(&temp, &codaPrio[hijo]) == 1)
            break;
        
        codaPrio[padre]=codaPrio[hijo];
        padre=hijo;
        hijo=2*hijo;
    }
    
    codaPrio[padre]=temp;
    
    return item;
}

  
 int main(){
    //inizializzazione pronto soccorso
    ProntoSoccorso ps;
    ps.numeroB = ps.numeroG = ps.numeroV = ps.numeroR = 0;
    
    //menu
    int opcion=0, i;

    Pacientes pz1;

    while(1){
        system("pause");
        system("cls");
        
        printf("\n1.-Inserta un paciente\n"
               "\n2.-Atiende un paciente\n"
               "\n3.-Imprime lista de pacientes\n"
               "\n4.-Salir\n");
        scanf("%d", &opcion);
        getchar();

        if(opcion == 1){
            pz1=nuovoPaziente(&ps);
            insertHeap(&pz1);
        }else if(opcion == 2){
            pz1=cancelaPaziente();
        }else if(opcion == 3){
            for(i=1; i<=dim_coda; i++){
                printPaziente(&codaPrio[i]);
            }
        }else if(opcion == 4){
            
            return 0;
        }else{
            printf("\nNo es una opcion valida\n");
        }
    }
    

}



