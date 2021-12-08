#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h> 

void gotoxy(short x, short y) 
{
   COORD pos = {x, y};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
#define LONGITUD_FOLIO_MUNICIPIO 4
#define POBLACION_MAXIMA 820888
#define POBLACION_MINIMA 102
#define POBLACION_CARACTER_MAXIMA "820,888"
#define POBLACION_CARACTER_MINIMA "102"
#define TOTAL_ENTIDADES 32
#define TOTAL_MUNICIPIOS 512
#define LONGITUD_FOLIO_ESTADO 3
#define LONGITUD_DESCRIPCION_ESTADO 26
#define LONGITUD_DESCRIPCION_MUNICIPIO 30
#define LONGITUD_POBLACION 8
#define FOLIO_MINIMO 1
#define FOLIO_MAXIMO 32
#define CIERTO 1
#define FALSO 0

typedef struct {
		  char DescripcionEstado_E[LONGITUD_DESCRIPCION_ESTADO];
	    char DescripcionMunicipio_E[LONGITUD_DESCRIPCION_MUNICIPIO];
	    int DescripcionSuma_E;
	    char Comparar1[LONGITUD_DESCRIPCION_ESTADO];
	    char Comparar2[LONGITUD_DESCRIPCION_MUNICIPIO];
		} regEntidadFederativa;

typedef struct {
          int FolioEstado_S; 
          int FolioMunicipio_S;
          char DescripcionEstado_S[LONGITUD_DESCRIPCION_ESTADO]; 
          char DescripcionMunicipio_S[LONGITUD_DESCRIPCION_MUNICIPIO]; 
          long int Total_s;
		} regTotal;  
		
typedef struct {
			  int FolioEstado_E;
		  int FolioMunicipio_E;
		  long int PoblacionEstatal2020_E;
		  int FolioSuma_E;
}regFolio;
		
FILE *ptfEntrada, *ptfEntrada2, *ptfSalida;

regEntidadFederativa vtrEntrada;
regTotal vtrSalida; 
regFolio vtrEntrada2;

void vCICLO_MENU();
void vINICIAR();
void vALTAS( regEntidadFederativa vtrEntrada, regFolio vtrEntrada2);
int iCAPTURAR_FOLIO();
int iCAPTURAR_FOLIO_MUNICIPIO();
char cCAPTURAR_ESTADO(char EstadoReceptor[], char EstadoLocal[]);
char cCAPTURAR_MUNICIPIO(char MunicipioReceptor[], char MunicipioLocal[]);

long int liCAPTURAR_POBLACION_2020(); 
void vREPORTE( regEntidadFederativa vtrEntrada,regFolio vtrEntrada2, regTotal vtrSalida);
void vIMPRIME( regTotal vtrSalida);
int iSELECCIONA_OPCION( int OpcionMenor , int OpcionMayor );
void ORDENAR_REGISTROS( regEntidadFederativa vtrEntrada, regFolio vtrEntrada2 );
void vARCHIVO_HACIA_ARREGLOS();
void vORDENAMIENTO( int auFolio_t[], int auFolioMunicipio_t[], char auEstado_t[][LONGITUD_DESCRIPCION_ESTADO], char auMunicipio_t[][LONGITUD_DESCRIPCION_MUNICIPIO] , long auPoblacion_t[], int Registros );	
void vARREGLO_HACIA_ARCHIVO( int auF_t[],int auFM_t[], char auE_t[][LONGITUD_DESCRIPCION_ESTADO], char auM_t[][LONGITUD_DESCRIPCION_MUNICIPIO] , long auP_t[], int Registros, regEntidadFederativa vtrEntrada, regFolio vtrEntrada2);
int iVALIDAR_FOLIO(regFolio vtrEntrada2);
int iVALIDAR_DESCRIPCION(regEntidadFederativa vtrEntrada); 

main()
{	
   vCICLO_MENU();
} 

void vCICLO_MENU()
{
   int OpcionMenu;
   int OpcionMenor = 1, OpcionMayor = 4;  
   do{
   	system("cls");
     printf("Menu principal.\n");
	 printf("1.-Iniciar \n");
     printf("2.-Altas \n");
     printf("3.-Reporte \n");
	 printf("4.-Salir \n");
     printf("Cual opcion deseas? : ");
     OpcionMenu = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );   
	 switch( OpcionMenu )
	 {
	    case 1:
		     
		      vINICIAR();
		      break;
	    case 2:
              
		      vALTAS(vtrEntrada, vtrEntrada2);
		      break;
	    case 3:
             
		      vREPORTE(vtrEntrada,vtrEntrada2, vtrSalida);
              break;
        case 4:
              printf("Usted ha elegido la opcion para salir del Programa. Gracias!\n");                      		  
              system("pause");
              break;
        default:
              printf("La opcion elegida esta fuera de rango\n");
              printf("El programa concluira su funcion\n");             
              system("pause");
              break;              
	 } 
   }while( OpcionMenu >= OpcionMenor && OpcionMenu < OpcionMayor );
} 

void vALTAS( regEntidadFederativa vtrEntrada, regFolio vtrEntrada2 )
{
system("cls");
   int Continuar, OpcionMenor = 1, OpcionMayor = 2;
   ptfEntrada = fopen("c:corte_de_control.dat","a+");
   ptfEntrada2 = fopen("c:corte_de_control2.dat","a+");
   if( ptfEntrada == NULL || ptfEntrada2 == NULL )
   {
      printf( "El archivo de entrada NO existe ; favor de revisar su proceso \n" );
   } 

   if( ptfEntrada != NULL|| ptfEntrada2 != NULL)
   {
      do{
	      printf( "Este es el apartado de altas: \n" );
	      do{
          vtrEntrada2.FolioEstado_E = iCAPTURAR_FOLIO();
          vtrEntrada2.FolioMunicipio_E = iCAPTURAR_FOLIO_MUNICIPIO();
          vtrEntrada2.FolioSuma_E = iVALIDAR_FOLIO(vtrEntrada2);
      	  }while( vtrEntrada2.FolioSuma_E == CIERTO );
		  do{
		  cCAPTURAR_ESTADO(vtrEntrada.DescripcionEstado_E, vtrEntrada.DescripcionEstado_E);
		  cCAPTURAR_MUNICIPIO(vtrEntrada.DescripcionMunicipio_E, vtrEntrada.DescripcionMunicipio_E);
		  vtrEntrada.DescripcionSuma_E = iVALIDAR_DESCRIPCION(vtrEntrada);
	      }while( vtrEntrada.DescripcionSuma_E == CIERTO);
		  vtrEntrada2.PoblacionEstatal2020_E = liCAPTURAR_POBLACION_2020();		  	      
	      fwrite(&vtrEntrada, sizeof(regEntidadFederativa), 1, ptfEntrada);
	      fwrite(&vtrEntrada2, sizeof(regFolio), 1, ptfEntrada2);
	      printf( "Deseas continuar 1.-SI; 2.-NO : " );
          Continuar = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );	      
      }while( Continuar == 1 );
   } 
   fclose(ptfEntrada);
   fclose(ptfEntrada2);
} 

int iVALIDAR_FOLIO(regFolio vtrEntrada2){
	
    int Busqueda, NoValido, FolioBuscado, FolioBuscado2;
    FolioBuscado = vtrEntrada2.FolioMunicipio_E; 
    FolioBuscado2 = vtrEntrada2.FolioEstado_E;
    NoValido=FALSO;

    Busqueda = 0;
    rewind( ptfEntrada2 ); 
    do{
	     fread(&vtrEntrada2 , sizeof( regFolio ), 1, ptfEntrada2 ); 
	     if( FolioBuscado == vtrEntrada2.FolioEstado_E )
	     {
	     	if( FolioBuscado2 == vtrEntrada2.FolioMunicipio_E ){
			Busqueda = Busqueda+1;
			if(Busqueda==1){
				NoValido= CIERTO;
			}    
	        break;
			}
	     } 
    }while( ! feof( ptfEntrada2 ) );  
    rewind( ptfEntrada2 );
    return( NoValido );
} 

int iVALIDAR_DESCRIPCION( regEntidadFederativa vtrEntrada )
{
	char DescripcionBuscada, DescripcionBuscada2;
    int Busqueda, NoValido;
    strcpy(vtrEntrada.Comparar1, vtrEntrada.DescripcionEstado_E);
    strcpy(vtrEntrada.Comparar2, vtrEntrada.DescripcionMunicipio_E);
    NoValido=FALSO;

    Busqueda = 0;
    rewind( ptfEntrada ); 
    do{
	     fread(&vtrEntrada , sizeof( regEntidadFederativa ), 1, ptfEntrada ); 
	     if( ! strcmp( vtrEntrada.DescripcionEstado_E, vtrEntrada.Comparar1 ) )
	     {
	     	if( ! strcmp( vtrEntrada.DescripcionMunicipio_E,vtrEntrada.Comparar2  ) ){
			Busqueda = Busqueda+1;
			if(Busqueda>1){
				NoValido= CIERTO;
			}    
	        break;
			}
	     } 
    }while( ! feof( ptfEntrada ) );  
    rewind( ptfEntrada ); 
    return( NoValido );
} 
	

void vINICIAR()
{
   int OpcionMenor = 1, OpcionMayor = 2;     
   int Opcion;    
   	   
   printf( "Iniciar\n" );
   printf( "Esta rutina destruye los archivos de entrada anteriores. Advertencia. \n" );
   printf( "Deseas destruirlo? 1.-SI; 2.-NO : " );
   Opcion = iSELECCIONA_OPCION( OpcionMenor, OpcionMayor );
   if( Opcion == CIERTO )
   {
      ptfEntrada = fopen("c:corte_de_control.dat","r"); 
      ptfEntrada2 = fopen("c:corte_de_control2.dat","r"); 
      if( ptfEntrada == NULL || ptfEntrada2 == NULL)
      {
	      printf( "No se pudo destruir el archivo porque no existe \n" );
	      system( "pause" );
       }
       else
       {
	      fclose( ptfEntrada );
	      remove("c:corte_de_control.dat");
	      fclose( ptfEntrada2 );
	      remove("c:corte_de_control2.dat");
       } 
    }
    system( "cls" );
}


void vREPORTE( regEntidadFederativa vtrEntrada, regFolio vtrEntrada2 , regTotal vtrSalida)
{
    long int FolioEstado_T;
    long int FolioMunicipio_T;
    long int Total_t = 0;
    char DescripcionEstado_T[LONGITUD_DESCRIPCION_ESTADO];
    char DescripcionMunicipio_T[LONGITUD_DESCRIPCION_MUNICIPIO];
    
	    
    ORDENAR_REGISTROS( vtrEntrada , vtrEntrada2);    
    ptfEntrada = fopen("c:corte_de_control.dat","r"); 
    ptfEntrada2 = fopen("c:corte_de_control2.dat","r");
    ptfSalida = fopen("c:total.sal","w");  
    if( ptfEntrada == NULL && ptfEntrada2 == NULL)
    {
	   printf("Los archivos de entrada NO existen; favor de revisar su proceso \n");
    } 
    
    if( ptfEntrada != NULL && ptfEntrada2 != NULL)
    {
       fread(&vtrEntrada, sizeof(regEntidadFederativa), 1, ptfEntrada);
       fread(&vtrEntrada2, sizeof(regFolio), 1, ptfEntrada2);
       FolioEstado_T = vtrEntrada2.FolioEstado_E;
       FolioMunicipio_T = vtrEntrada2.FolioEstado_E;
       strcpy(DescripcionEstado_T, vtrEntrada.DescripcionEstado_E);
       strcpy(DescripcionMunicipio_T, vtrEntrada.DescripcionMunicipio_E);
       do{
       do{
	        if( FolioEstado_T == vtrEntrada2.FolioEstado_E)
	        {
	           Total_t = Total_t + vtrEntrada2.PoblacionEstatal2020_E;
	           fread(&vtrEntrada2, sizeof(regFolio), 1, ptfEntrada2);
	        }
	        else
	        {
	           vtrSalida.FolioEstado_S = FolioEstado_T;
	           vtrSalida.FolioMunicipio_S = FolioMunicipio_T;
               strcpy(vtrSalida.DescripcionEstado_S,DescripcionEstado_T);
			   strcpy(vtrSalida.DescripcionMunicipio_S,DescripcionMunicipio_T);	       
	           vtrSalida.Total_s = Total_t;
	           fwrite(&vtrSalida, sizeof(regTotal), 1, ptfSalida);
	           
	           FolioEstado_T = vtrEntrada2.FolioEstado_E;
	           FolioMunicipio_T = vtrEntrada2.FolioEstado_E;
               strcpy(DescripcionEstado_T,vtrEntrada.DescripcionEstado_E);
			   strcpy(DescripcionMunicipio_T,vtrEntrada.DescripcionMunicipio_E);		       
	           Total_t = 0;
            }
       }while(!feof(ptfEntrada));
       }while( !feof(ptfEntrada2));
       
       vtrSalida.FolioEstado_S = FolioEstado_T;
       vtrSalida.FolioMunicipio_S = FolioMunicipio_T;
       strcpy(vtrSalida.DescripcionEstado_S,DescripcionEstado_T);
	   strcpy(vtrSalida.DescripcionMunicipio_S,DescripcionMunicipio_T);      
       vtrSalida.Total_s = Total_t;

       fwrite(&vtrSalida, sizeof(regTotal), 1, ptfSalida);

       fclose(ptfEntrada);
       fclose(ptfEntrada2);
       fclose(ptfSalida);
       vIMPRIME(vtrSalida);
    } 
       system("pause");
}

int iSELECCIONA_OPCION( int LimiteMenor , int LimiteMayor )
{
   int OpcionSeleccionada;
   char Opcion[2];        
     
   do{
      scanf( "%s", Opcion );  
      OpcionSeleccionada = atoi( Opcion );
      if( OpcionSeleccionada == FALSO )
      {
          printf("La opcion seleccionada NO ES CORRECTA !!!\n");
          printf("El rango de opciones es de %d a %d, favor de intentar de nuevo \n", LimiteMenor, LimiteMayor );          
      }    
      else
      {
         if( OpcionSeleccionada < LimiteMenor || OpcionSeleccionada > LimiteMayor )
         {
            printf("La opcion seleccionada NO ES CORRECTA !!!\n");
            printf("El rango de opciones es de %d a %d, favor de intentar de nuevo \n", LimiteMenor, LimiteMayor );
         } 
      }    
   }while( OpcionSeleccionada < LimiteMenor || OpcionSeleccionada > LimiteMayor );
   system("cls");
   return(OpcionSeleccionada);
}

int iCAPTURAR_FOLIO()
{	
   long int FolioLocal;
   char FolioCadena[LONGITUD_FOLIO_ESTADO];	     
   do{
		printf("Capture el numero de folio: \n");     
        scanf(" %[^\n]",FolioCadena);
		FolioLocal = atol(FolioCadena);	
        if( FolioLocal == 0 || FolioLocal < 1 || FolioLocal > 32 )
        {
        	printf( "El dato capturado para el n%cmero de folio no cumple con los requisitos \n", 163);
        	printf( "favor de capturar un dato con %d digitos ( de preferencia. ), entre %d y %d \n",2, 1, 32); 			       	
        	strset( FolioCadena, ' ' );  
		} 
   }while( FolioLocal == 0 || FolioLocal < 1 || FolioLocal > 32 );
return( FolioLocal );
} 

int iCAPTURAR_FOLIO_MUNICIPIO()
{	
   long int FolioLocal;
   char FolioCadena[LONGITUD_FOLIO_MUNICIPIO];	     
   do{
		printf("Capture el numero de folio del municipio: \n");     
        scanf(" %[^\n]",FolioCadena);
		FolioLocal = atol(FolioCadena);	
        if( FolioLocal == 0 || FolioLocal < 1 || FolioLocal > 32 )
        {
        	printf( "El dato capturado para el n%cmero de folio no cumple con los requisitos \n", 163);
        	printf( "favor de capturar un dato con %d digitos ( de preferencia. ), entre %d y %d \n",2, 1, 32); 			       	
        	strset( FolioCadena, ' ' );  
		} 
   }while( FolioLocal == 0 || FolioLocal < 1 || FolioLocal > 32 );
return( FolioLocal );
} 

char cCAPTURAR_ESTADO(char DescripcionReceptor[], char DescripcionLocal[])
{
   int Longitud, i, NoCumple;	   
   do{
      NoCumple = FALSO;      
      printf( "Captura el nombre del estado : "  );
      scanf( " %[^\n]", DescripcionLocal );
      Longitud = strlen( DescripcionLocal );   
   
      for( i = 0; i < Longitud; i++ )
      {
         if( !isalpha(DescripcionLocal[i]) && !isspace(DescripcionLocal[i]) || Longitud > LONGITUD_DESCRIPCION_ESTADO-1 )
         {
	        NoCumple = CIERTO;
         }  
       } 
       
      if( NoCumple == CIERTO)
      {
         printf( "ERROR...!!!     El dato capturado no cumple con los requisitos \n", LONGITUD_DESCRIPCION_ESTADO-1 );      	
         printf( "Favor de capturar únicamente letras y espacios en blanco, máximo %d   !!! \n", LONGITUD_DESCRIPCION_ESTADO-1 );
         printf( "Favor de intentar de nuevo\n" );
         strset(DescripcionLocal, ' ');
         system( "pause" );
       }     
   }while(NoCumple == CIERTO);
return( DescripcionLocal[LONGITUD_DESCRIPCION_ESTADO] );	   
}

char cCAPTURAR_MUNICIPIO(char MunicipioReceptor[], char MunicipioLocal[])
{
   int Longitud, i, NoCumple;	   
   do{
      NoCumple = FALSO;      
      printf( "Captura el nombre del municipio : "  );
      scanf( " %[^\n]", MunicipioLocal );
      Longitud = strlen( MunicipioLocal );   
   
      for( i = 0; i < Longitud; i++ )
      {
         if( !isalpha(MunicipioLocal[i]) && !isspace(MunicipioLocal[i]) || Longitud > LONGITUD_DESCRIPCION_MUNICIPIO-1 )
         {
	        NoCumple = CIERTO;
         }  
       } 
       
      if( NoCumple == CIERTO)
      {
         printf( "ERROR...!!!     El dato capturado no cumple con los requisitos \n", LONGITUD_DESCRIPCION_MUNICIPIO-1 );      	
         printf( "Favor de capturar únicamente letras y espacios en blanco, máximo %d   !!! \n", LONGITUD_DESCRIPCION_MUNICIPIO-1 );
         printf( "Favor de intentar de nuevo\n" );
         strset( MunicipioLocal, ' ');
         system( "pause" );
       }     
   }while(NoCumple == CIERTO);
return( MunicipioLocal[LONGITUD_DESCRIPCION_MUNICIPIO] );	   
}


long int liCAPTURAR_POBLACION_2020() 
{
   int Longitud, i, NoCumple;
   long int PoblacionNumerica;
   char PoblacionNoNumerica[10];
   
		   
   do{
      NoCumple = FALSO;      
      printf( "Capture la población del estado : " );
      scanf( " %[^\n]", PoblacionNoNumerica );
      Longitud = strlen( PoblacionNoNumerica );   
      PoblacionNumerica = atoi(PoblacionNoNumerica);
      for( i = 0; i < Longitud; i++ )
      {
         if( !isdigit(PoblacionNoNumerica[i]) || PoblacionNoNumerica <= 0 || Longitud > LONGITUD_POBLACION  )
         {
	        NoCumple = CIERTO;
         }  
       } 
       
      if( PoblacionNumerica < POBLACION_MINIMA || PoblacionNumerica > POBLACION_MAXIMA ) 
      {
        NoCumple = CIERTO;
      }  
       
      if( NoCumple == CIERTO)
      {
         printf( "ERROR...!!!     El dato capturado no cumple con los requisitos \n" );
         printf( "Favor de capturar un valor entero y positivo sin puntos ni comas, máximo %d digitos \n", LONGITUD_POBLACION );
         printf( "La población debe estar dentro del siguiente rango:  %s a %s \n", POBLACION_CARACTER_MINIMA, POBLACION_CARACTER_MAXIMA );         
         strset(PoblacionNoNumerica, ' ');
         system( "pause" );
       }     
   }while(NoCumple == CIERTO);
return( PoblacionNumerica );
}

void vIMPRIME(regTotal vtrSalida)
{
  system("cls");
   int Linea;
   
   ptfSalida = fopen("c:total.sal","r");
   system("cls");
   if( ptfSalida == NULL )
   {
      printf("no puedo abrir archivo; favor de revisar su proceso \n");
   } 

   
   printf("Num.Folio (Est)     Num.Folio (Mun)      Nombre del estado          Nombre del municipio         Poblacion 2020\n");
   Linea=2;
   fread(&vtrSalida, sizeof(regTotal), 1, ptfSalida);
   do{
       gotoxy( 1, Linea ); 
       printf( "%d", vtrSalida.FolioEstado_S );
       gotoxy( 14, Linea ); 
       printf( "%d", vtrSalida.FolioMunicipio_S);        
       gotoxy( 41, Linea ); 
       printf( "%s", vtrSalida.DescripcionEstado_S );
       gotoxy( 70, Linea) ;
       printf( "%s", vtrSalida.DescripcionMunicipio_S );
       gotoxy( 100, Linea) ;
       printf( "%ld", vtrSalida.Total_s);
       
       Linea++;
       fread(&vtrSalida, sizeof(regTotal), 1, ptfSalida);
   }while(!feof(ptfSalida));
   fclose(ptfSalida);
   printf("\n");
}

void ORDENAR_REGISTROS( regEntidadFederativa vtrEntrada, regFolio vtrEntrada2 )
{  
   vARCHIVO_HACIA_ARREGLOS();   
} 

void vARCHIVO_HACIA_ARREGLOS()
{
   int auFolioEstado_T[1000];
   int auFolioMunicipio_T[1000];
   char auDescripcionEstado_T[1000][LONGITUD_DESCRIPCION_ESTADO];
   char auDescripcionMunicipio_T[1000][LONGITUD_DESCRIPCION_MUNICIPIO];
   long int auPoblacionEstatal2020_T[1000];
   int i = 0, Registros;
   
   /* 6.2 Instrucciones que forman el cuerpo o bloque de la función definida por el programador */	   
   ptfEntrada = fopen("c:corte_de_control.dat","r");
   ptfEntrada2 = fopen("c:corte_de_control2.dat","r");
   

   fread(&vtrEntrada, sizeof(regEntidadFederativa), 1, ptfEntrada);
   fread(&vtrEntrada2, sizeof(regFolio), 1, ptfEntrada2);
   do{
        auFolioEstado_T[i] = vtrEntrada2.FolioEstado_E;
        auFolioMunicipio_T[i] = vtrEntrada2.FolioMunicipio_E;
	    strcpy( auDescripcionEstado_T[i], vtrEntrada.DescripcionEstado_E );
	    strcpy( auDescripcionMunicipio_T[i], vtrEntrada.DescripcionMunicipio_E );
	    auPoblacionEstatal2020_T[i] = vtrEntrada2.PoblacionEstatal2020_E;
	     
        i = i + 1;
        fread(&vtrEntrada, sizeof(regEntidadFederativa), 1, ptfEntrada);
        fread(&vtrEntrada2, sizeof(regFolio), 1, ptfEntrada2);
	}while( !feof( ptfEntrada) && !feof(ptfEntrada2) );
	Registros = i;

	fclose( ptfEntrada );
	fclose( ptfEntrada2 );
    vORDENAMIENTO( auFolioEstado_T, auFolioMunicipio_T, auDescripcionEstado_T, auDescripcionMunicipio_T, auPoblacionEstatal2020_T, Registros );	
} 


void vORDENAMIENTO( int auF_t[],int auFM_t[], char auE_t[][LONGITUD_DESCRIPCION_ESTADO],char auM_t[][LONGITUD_DESCRIPCION_MUNICIPIO], long int auP_t[], int R )
{
   /* 6.1 Declaración de identificadores con alcance de bloque */
   int i, j, AuxiliarFolio, AuxiliarFolioMunicipio;
   char AuxiliarEstado[LONGITUD_DESCRIPCION_ESTADO];
   char AuxiliarMunicipio[LONGITUD_DESCRIPCION_MUNICIPIO];
   long int AuxiliarPoblacion;

  
   for ( i = 1; i < R; i++)
   {
      for ( j = 0; j < R-i; j++)
      {
         if (auF_t[j] >= auF_t[j+1] )
         {
            
            AuxiliarFolio = auF_t[j];
            auF_t[j] = auF_t[j+1];
            auF_t[j+1] = AuxiliarFolio;
            
            AuxiliarFolioMunicipio = auFM_t[j];
            auFM_t[j] = auFM_t[j+1];
            auFM_t[j+1] = AuxiliarFolioMunicipio;
            
            strcpy(AuxiliarEstado, auE_t[j]);
            strcpy(auE_t[j], auE_t[j+1]);
            strcpy(auE_t[j+1], AuxiliarEstado);
                        
            strcpy(AuxiliarMunicipio, auM_t[j]);
            strcpy(auM_t[j], auM_t[j+1]);
            strcpy(auM_t[j+1], AuxiliarMunicipio);

            AuxiliarPoblacion = auP_t[j];
            auP_t[j] = auP_t[j+1];
            auP_t[j+1] = AuxiliarPoblacion;
            
         } 
      }
   } 
   vARREGLO_HACIA_ARCHIVO( auF_t,auFM_t, auE_t, auM_t, auP_t, R, vtrEntrada, vtrEntrada2 );
} 

void vARREGLO_HACIA_ARCHIVO( int auF_t[],int auFM_t[], char auE_t[][LONGITUD_DESCRIPCION_ESTADO],char auM_t[][LONGITUD_DESCRIPCION_MUNICIPIO], long int auP_t[], int R , regEntidadFederativa vtrEntrada, regFolio vtrEntrada2)
{
   FILE *ptfNuevoArchivo;
   int i;

   ptfEntrada = fopen("c:corte_de_control.dat","w");  
   ptfEntrada2 = fopen("c:corte_de_control2.dat","w");  
   
   for( i = 0; i < R; i++ )
   {

       vtrEntrada2.FolioEstado_E = auF_t[i];
       vtrEntrada2.FolioMunicipio_E = auFM_t[i];
       strcpy( vtrEntrada.DescripcionEstado_E, auE_t[i] );
	   strcpy( vtrEntrada.DescripcionMunicipio_E, auM_t[i] );       
       vtrEntrada2.PoblacionEstatal2020_E = auP_t[i];
   
       fwrite(&vtrEntrada, sizeof(regEntidadFederativa), 1, ptfEntrada);
       fwrite(&vtrEntrada2, sizeof(regFolio), 1, ptfEntrada2);
    } 
   	fclose( ptfEntrada );
   	fclose( ptfEntrada2 );
   	return;
} 
