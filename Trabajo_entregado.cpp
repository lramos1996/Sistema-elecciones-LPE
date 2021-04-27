#include<iostream>
//#include<gotoxy.h>
#include<cstring>
#include<algorithm>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<windows.h>
#include<ctime>
#include<vector>
//120/40//ventana

using namespace std;

char caso;
long long TotalP=0;
long long TotalE=0;

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  

struct departamento{
	char ubigeo[7];
	char ambito;
	char nombre[50];
	long long habiles;
	long long votantes;
	long long candidatos[2];
	char ganador[30];
	double ausentismo;
};

struct provincia{
	char ubigeo[7];
	char ambito;
	char nombre[50];
	long long habiles;
	long long votantes;
	long long candidatos[2];
	char ganador[30];
	double ausentismo;
};

struct distrito{
	char ubigeo[7];
	char ambito;
	char nombre[50];
	long long habiles;
	long long votantes;
	long long candidatos[2];
	char ganador[30];
	double ausentismo;
};

struct local{
	char local[5];
	char ubigeo[7];
	char nombre[150];
	//Numero de mesas asociadas a este local
	int n_mesas;
};

struct mesa{
	char mesa[7];
	char local[5];
	char ubigeo[7];
};

struct candidato{
	char ID[10];
	char nombre[30];
	long long votos;
	long long N;
	long long E;
};

struct ubicacion{
	int ID;
	string ambito;
	//para nacional ID_1: departamento ID_2: provincia ID_3:distrito
	//para internacional ID_1: continente ID_2: pais ID_3: ciudad
	string ID_1, ID_2, ID_3;
	//Numero de locales asociados a esta ubicacion
	int n_locales;
	
};

struct acta{
	char mesa[7];
	char ubigeo[7];
	int habiles;
	int votantes;
	int blancos;
	int nulos;
	int candidatos[2];//n=numero de candidato que va ha ser hallado en el archivo candidatos//C[i] votos para el candidato i

};

struct Item{
	char ambito;
	char departamento[50];
	char provincia[50];
	char distrito[50];
};

acta A[77299];
departamento D[30];
provincia P[500];
distrito Dis[2500];
candidato C[20];
local L[5357];
mesa M[77308];

//Funciones de ayuda-----------------------------------------------
int index_Nmax(long long X[], int l){
	int index=0;
	for(int i=0;i<l;i++){
		if(X[i]>X[index]){
			index=i;
		}
	}
	return index;
}

int index_Nmax_Ambito(candidato C[],int &c,char &ambito){
	int index=0;
	if(ambito='P'){
		for(int i=0;i<c;i++){
			if(C[i].N>C[index].N){
				index=i;
			}
		}
	}else if(ambito='E'){
		for(int i=0;i<c;i++){
			if(C[i].E>C[index].E){
				index=i;
			}
		}	
	}
	return index;
}

//Funciones de interfaz de usuario---------------------------------
void color(int x){
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),x);
}

void linea(int x,int d,int y){
	for(int i=x;i<=d+x;i++){
		gotoxy (i,y);
		putchar ('Í');
	}
}

void doblelinea(int x, int d,int y){
	linea(x,d,y);
	linea(x,d,y+1);
}

void fecha_hora(int x, int y){
	/* fecha/hora actual basado en el sistema actual */
	time_t now = time(0);
	 
	/* Objeto de una estructura tm con fecha/hora local */
	tm * time = localtime(&now);
	 
	vector<string> dia_semana;
	dia_semana.push_back("Domingo");
	dia_semana.push_back("Lunes");
	dia_semana.push_back("Martes");
	dia_semana.push_back("Miercoles");
	dia_semana.push_back("Jueves");
	dia_semana.push_back("Viernes");
	dia_semana.push_back("Sabado");
	vector<string> mes;
	mes.push_back("Enero");
	mes.push_back("Febrero");
	mes.push_back("Marzo");
	mes.push_back("Abril");
	mes.push_back("Mayo");
	mes.push_back("Junio");
	mes.push_back("Julio");
	mes.push_back("Agosto");
	mes.push_back("Septiembre");
	mes.push_back("Octubre");
	mes.push_back("Noviembre");
	mes.push_back("Diciembre");
	 
	int year = 1900 + time->tm_year;
	 
	//Formato=hoy miercoles, 27 de mayo del 2015
	gotoxy(x+1,y);cout << "Hoy " << dia_semana[time->tm_wday] << ", ";
	gotoxy(x+1,y+1);cout << time->tm_mday << " de " << mes[time->tm_mon] << " de " << year << endl;
	gotoxy(x+1,y+2);cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << endl;

}

void interfaz_de_admin(){
	system("cls");
	system("color F1");
	
	gotoxy(50,1);cout<<"                     ";
	gotoxy(50,2);cout<<"                     ";
	gotoxy(50,3);cout<<"          ";
	gotoxy(45,4);cout<<"  SISTEMA DE GESTION ELECTORAL            ";
	color(249);
	for(int i=20;i<=98;i++){
		gotoxy(i,6);cout<<"Í";
		gotoxy(i,10);cout<<"Í";
		gotoxy(i,22);cout<<"Í";
	}
	color(240);
 
	gotoxy(49,8);cout<<"      BIENVENIDO";
	gotoxy(46,12);cout<<"±±±±±±±±±±±±";
	gotoxy(46,13);cout<<"   USUARIO  ";
	gotoxy(46,14);cout<<"±±±±±±±±±±±±";
	gotoxy(58,12);cout<<"±±±±±±±±±±±±";
	gotoxy(58,13);cout<<"±±±±±±±±±±±±";
	gotoxy(58,14);cout<<"±±±±±±±±±±±±";
	gotoxy(46,16);cout<<"±±±±±±±±±±±±";
	gotoxy(46,17);cout<<" CONTRASE"<<(char)165<<"A";
	gotoxy(46,18);cout<<"±±±±±±±±±±±±";
	gotoxy(58,16);cout<<"±±±±±±±±±±±±";
	gotoxy(58,17);cout<<"±±±±±±±±±±±±";
	gotoxy(58,18);cout<<"±±±±±±±±±±±±";
}

void ingresar(){
	int nv=0,i,j,ni=0;
    char user[5],clave[5];
	
	do{
		ni++;
      	if(ni<=3){
		  interfaz_de_admin();
		  gotoxy(20,20);cout<<"Intento Numero "<<ni;
		  char c;
		  char cod[50];
		  int k;
		  k=0;
		  gotoxy(60,13);
	      while((c=getch())!=13){
			if(c==8){
				cout<<"\b ";
		    	cout<<"\b";
            	--k;
		    }else{
		    	cout<<"*";
				user[k]=c;
		    	user[++k]=0;
	     	}
		  }
		k=0;
	    gotoxy(60,17);
	    while((c=getch())!=13){
			if(c==8){
				cout<<"\b ";
				cout<<"\b";
	         	--k;
			}else{
				cout<<"*";
				clave[k]=c;
				clave[++k]=0;
			}
	 	}

      }
      else
       {gotoxy(10,24);
   cout<<" NO PUEDE ACCEDER AL SISTEMA PORQUE SUPERO LOS 3 INTENTENTOS ";
   getch();
    system("cls");system("color F4");
    color(252);
	gotoxy(38,2);cout<<"                      °°  _°°  _°°           ";
    gotoxy(38,3);cout<<"                     °°____°°____°°        ";
    gotoxy(38,4);cout<<"              °°    _ °°____°°____°°       ";
    gotoxy(38,5);cout<<"              °°°°_____°°____°°____°°      ";
    gotoxy(38,6);cout<<"          °°______°°_________________°°    ";
    gotoxy(38,7);cout<<"           °°°°_______________________°°   ";
    gotoxy(38,8);cout<<"             °°°____________°°_______°°°   ";
    gotoxy(38,9);cout<<"              °°______°°____°°______°°     ";
    gotoxy(38,10);cout<<"               °°_____°°____________°°     ";
    gotoxy(38,11);cout<<"               °°___________________°°     ";
    gotoxy(38,12);cout<<"               °°_______°°°°°_______°°     ";
    gotoxy(38,13);cout<<"               °°______°°___°°_____°°      ";
    gotoxy(38,14);cout<<"                °°____°°_____°°__°°       ";
    gotoxy(38,15);cout<<"                 °°______________°°        ";
    gotoxy(38,16);cout<<"      °°°°         °°°°°°°°°°°°°___°°      ";
    gotoxy(38,17);cout<<"     °°°°°°             °°___________°°    ";
    gotoxy(38,18);cout<<"     °°°°°°°°°°°°°°°°°°°°____________°°    ";
    gotoxy(38,19);cout<<"        °°             °°_____________°°   ";
    gotoxy(38,20);cout<<"         °             °°______________°°  ";
    gotoxy(38,21);cout<<"                       °°_______________°° ";
    color(249);
      gotoxy(5,5);cout<<"Ud. esta saliendo del programa...";
      gotoxy(5,7);cout<<"Ud. No ingreso datos correctos "<<endl<<"     (Tal ves no sea el admin)...";
      color(240);
      gotoxy(5,23);cout<<"Pulse una tecla para cerrar.."<<endl;
      getch();
      exit(0);
   	 }
    }while(strcmp(strupr(user),"TEAM")!=0 || strcmp(clave,"LPE")!=0);
    system("cls");
 }

void carga(){
   char s=char(219),e[2],letra2[2];
   char letra[2];
   int i,j,cont=0;
	color(240);	
   gotoxy(30,18);cout<<"CARGANDO EL SISTEMA DE GESTION ELECTORAL_UNI .. POR FAVOR ESPERE"<<endl;
   for(i=30;i<92;i=i+2){
      cont=++cont;
      color(153);
      for(j=0;j<=20000000;j++){
      }
      gotoxy(i,14);cout<<"Í"<<endl;
      gotoxy(i,15);cout<<"Í"<<endl;
      gotoxy(i,16);cout<<"Í"<<endl;
      color(240);
      switch(cont){
         case 3:
                  gotoxy(50,7); cout<<"  * ****     * "<<endl;
                  gotoxy(50,8); cout<<"  * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<"  * *  *   *   "<<endl;
                  gotoxy(50,10);cout<<"  * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<"  * **** *     "<<endl;
                  break;
         case 6:
                  gotoxy(50,7); cout<<" *** ****     * "<<endl;
                  gotoxy(50,8); cout<<"   * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" *** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<" *   *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<" *** **** *     "<<endl;
                  break;
         case 9:
                  gotoxy(50,7); cout<<" *** ****     * "<<endl;
                  gotoxy(50,8); cout<<"   * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" *** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<"   * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<" *** **** *     "<<endl;
                  break;
         case 12:
                  gotoxy(50,7); cout<<" * * ****     * "<<endl;
                  gotoxy(50,8); cout<<" * * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" *** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<"   * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<"   * **** *     "<<endl;
                  break;
         case 15:
                  gotoxy(50,7); cout<<" *** ****     * "<<endl;
                  gotoxy(50,8); cout<<" *   *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" *** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<"   * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<" *** **** *     "<<endl;
                  break;
         case 18:
                  gotoxy(50,7); cout<<" **** ****     * "<<endl;
                  gotoxy(50,8); cout<<" *    *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" **** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<" *  * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<" **** **** *     "<<endl;
                  break;
         case 21:
                  gotoxy(50,7); cout<<" **** ****     * "<<endl;
                  gotoxy(50,8); cout<<"    * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<"    * *  *   *   "<<endl;
                  gotoxy(50,10);cout<<"    * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<"    * **** *     "<<endl;
                  break;
         case 24:
                  gotoxy(50,7); cout<<" **** ****     * "<<endl;
                  gotoxy(50,8); cout<<" *  * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" **** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<" *  * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<" **** **** *     "<<endl;
                  break;
         case 27:
                  gotoxy(50,7); cout<<" **** ****     * "<<endl;
                  gotoxy(50,8); cout<<" *  * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" **** *  *   *   "<<endl;
                  gotoxy(50,10);cout<<"    * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<"    * **** *     "<<endl;
                  break;
         case 30:
                  gotoxy(50,7); cout<<" * **** ****     * "<<endl;
                  gotoxy(50,8); cout<<" * *  * *  * *  *  "<<endl;
                  gotoxy(50,9); cout<<" * *  * *  *   *   "<<endl;
                  gotoxy(50,10);cout<<" * *  * *  *  *  * "<<endl;
                  gotoxy(50,11);cout<<" * **** **** *     "<<endl;
                  color(240);
                  gotoxy(30,18);cout<<"   LA BASE DE DATOS ONPE_UNI HA CARGADA SATISFACTORIAMENTE                          "<<endl;
                  color(240);
				  break;
       }
      }

                 letra[0]=char(0);
                 letra[1]=char(13);

                 gotoxy(22,21);cout<<"                                            "<<endl;
                 gotoxy(40,22);cout<<"   Pulse cualquier tecla para continuar...  "<<endl;
                 gotoxy(22,23);cout<<"                                            "<<endl;
				 getch();

}

//por mejorar----
bool buscar(char busca[],char pal[]){
	int n=strlen(busca);
	char aux[100];
	int i=0;
	bool primero=true;
	while(i<n){
		if(busca[i]==' '){
			i++;
			primero=false;
		}
		if(!primero){
			for(int j=i;j<n;j++){
				aux[j-i]=busca[j];
			}
			break;
		}
		i++;
	}
	if(strcmp(aux,pal)==0){
		return true;
	}else{
		return false;
	}
}
//-------------
void proceso_quitar(char palabra[]){
	char registro[1000];
	ifstream eliminar("candidatos.txt",ios::in);
	ofstream copiar("auxiliar.txt",ios::out);
	char le[100];
	char cod[100];
	while(1){
		if(!eliminar){
			break;
		}
		eliminar.getline(registro,999);
		if(!buscar(registro,palabra)){
			copiar<<registro<<endl;
		}
	}
	eliminar.close();
	copiar.close();
	
	remove("candidatos.txt");
	rename("auxiliar.txt","candidatos.txt");
	
}

void panel_administracion(char &op){
		for(int i=20;i<=98;i++)
	 {
	  gotoxy(i,5);cout<<"Í";
	  gotoxy(i,9);cout<<"Í";
	  gotoxy(i,30);cout<<"Í";
	 }
	  color(176);
	 gotoxy(40,7);cout<<" BIENVENIDO AL PANEL DE ADMINISTRACIoN ";
	 color(248);
	 gotoxy(42,10);cout<<"-------------------------------------";
	 color(245);
	 gotoxy(42,11);cout<<" ELIGA EL CAMPO QUE DESEA ADMINISTRAR";
	 color(248);
	 gotoxy(42,12);cout<<"-------------------------------------";
	 
	 gotoxy(27,14);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 gotoxy(27,15);cout<<" UBICACIONES <1> ±±±±±";
	 gotoxy(27,16);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(27,19);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 gotoxy(27,20);cout<<" LOCALES     <3> ±±±±±";
	 gotoxy(27,21);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(72,14);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,15);cout<<" CANDIDATOS  <2> ±±±±±";
	 gotoxy(72,16);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(72,19);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,20);cout<<" MESAS       <4> ±±±±±";
	 gotoxy(72,21);cout<<"±±±±±±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(52,17);cout<<"±±±±±±±±±±±±±±±±±";
	 gotoxy(52,18);cout<<" ACTAS  <5> ±±±±±";
	 gotoxy(52,19);cout<<"±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(49,23);cout<<"----------------------";
	 color(245);
	 gotoxy(49,24);cout<<" OPCIONES DE SISTEMA  ";
	 color(248);
	 gotoxy(49,25);cout<<"----------------------";
	 
	 gotoxy(27,26);cout<<"*******************";
	 gotoxy(27,27);cout<<"*  RESTAURAR  <0> *";
	 gotoxy(27,28);cout<<"*******************";
	 
	 gotoxy(72,26);cout<<"*******************";
	 gotoxy(72,27);cout<<"*   VALIDAR   <6> *";
	 gotoxy(72,28);cout<<"*******************";
	 
	 do{
	 	gotoxy(55,22);op=getch();
	 }while(op<'0' || op>'6');
	 system("cls");
}

void back_panel(){
	linea(20,78,6);
	linea(20,78,22);
	gotoxy(37,13);cout<<"VOLVER AL MENU DE ADMIN <1>          SALIR <0>"<<endl;
	char seguir;
	do{
		gotoxy(50,15);seguir=getch();
		if(seguir=='0'){
			system("cls");
			linea(20,78,6);
			linea(20,78,22);
			gotoxy(40,8);cout<<"GRACIAS POR USAR ESTE PROGRAMA.."<<endl;
			gotoxy(40,20);system("pause");
			exit(0);
			break;
		}else if(seguir=='1'){
			system("cls");
		}
	}while(seguir!='1');
}

//Admin----Ubicaciones
void registrar_ubicaciones(){
	color(250);
	linea(15,88,0);
	linea(15,88,3);
	color(240);
	double ausentismo;
    gotoxy(15,1);cout<<"¿QUE TIPO DE UBICACIONES VA HA REGISTRAR ?"<<endl;
    gotoxy(65,1);cout<<"INDIQUE CANTIDAD "<<endl;
    char tipo[30];
    do{
	    gotoxy(15,2);gets(tipo);
	}while(strcmp(tipo,"DEPARTAMENTOS")!=0 && strcmp(tipo,"PROVINCIAS")!=0 && strcmp(tipo,"DISTRITOS")!=0);
    int n;
    gotoxy(65,2);cin>>n;
    if(strcmp(tipo,"DEPARTAMENTOS")==0){
    	ofstream File_1("departamentos.txt",ios::app);
	    color(250);
		linea(3,108,4);
	    color(240);
	    gotoxy(3,5);cout<<"UBIGEO "<<endl;
	 	gotoxy(12,5);cout<<"AMBITO "<<endl;
	 	gotoxy(21,5);cout<<"NOMBRE "<<endl;
		departamento nuevo[n];
	 	bool primero=true;
	 	for(int i=0;i<n;i++){
	 	   if(primero){
	 	     gotoxy(3,7+i);gets(nuevo[i].ubigeo);
	 	     primero=false;
	       }
			gotoxy(3,7+i);gets(nuevo[i].ubigeo);
			gotoxy(12,7+i);nuevo[i].ambito=getche();
			gotoxy(21,7+i);gets(nuevo[i].nombre);
			File_1<<endl;
			File_1<<nuevo[i].ubigeo<<" "<<nuevo[i].ambito<<" "<<nuevo[i].nombre;
	    }
	 	File_1.close();
	}else if(strcmp(tipo,"PROVINCIAS")==0){
		ofstream File_1("provincias.txt",ios::app);
		color(250);
		linea(3,108,4);
	    color(240);
	    gotoxy(3,5);cout<<"UBIGEO "<<endl;
	 	gotoxy(12,5);cout<<"AMBITO "<<endl;
	 	gotoxy(21,5);cout<<"NOMBRE "<<endl;
		provincia nuevo[n];
	 	bool primero=true;
	 	for(int i=0;i<n;i++){
	 	   if(primero){
	 	     gotoxy(3,7+i);gets(nuevo[i].ubigeo);
	 	     primero=false;
	       }
			gotoxy(3,7+i);gets(nuevo[i].ubigeo);
			gotoxy(12,7+i);nuevo[i].ambito=getche();
			gotoxy(21,7+i);gets(nuevo[i].nombre);
			File_1<<endl;
			File_1<<nuevo[i].ubigeo<<" "<<nuevo[i].ambito<<" "<<nuevo[i].nombre;
	    }
	 	File_1.close();
	}else if(strcmp(tipo,"DISTRITOS")==0){
		ofstream File_1("distritos.txt",ios::app);
		color(250);
		linea(3,108,4);
	    color(240);
	    gotoxy(3,5);cout<<"UBIGEO "<<endl;
	 	gotoxy(12,5);cout<<"AMBITO "<<endl;
	 	gotoxy(21,5);cout<<"NOMBRE "<<endl;
		distrito nuevo[n];
	 	bool primero=true;
	 	for(int i=0;i<n;i++){
	 	   if(primero){
	 	     gotoxy(3,7+i);gets(nuevo[i].ubigeo);
	 	     primero=false;
	       }
			gotoxy(3,7+i);gets(nuevo[i].ubigeo);
			gotoxy(12,7+i);nuevo[i].ambito=getche();
			gotoxy(21,7+i);gets(nuevo[i].nombre);
			File_1<<endl;
			File_1<<nuevo[i].ubigeo<<" "<<nuevo[i].ambito<<" "<<nuevo[i].nombre;
	    }
	 	File_1.close();
	}
 	system("cls");
}

void eliminar_ubicaciones(){
	cout<<"ubicaciones"<<endl;
}

void administrar_ubicaciones(){
	char op;
	for(int i=20;i<=98;i++){
		gotoxy(i,6);cout<<"Í";
		gotoxy(i,10);cout<<"Í";
		gotoxy(i,22);cout<<"Í";
 	}
	  color(176);
	 gotoxy(47,8);cout<<" ADMINISTRAR UBICACIONES ";
	 color(248);
	 gotoxy(50,11);cout<<"±±±±±±±±±±±±±±±±±";
	 color(245);
	 gotoxy(50,12);cout<<" ELIGA UNA TAREA ";
	 color(248);
	 gotoxy(50,13);cout<<"±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(29,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(29,16);cout<<" REGISTRAR <1> ±±±";
	 gotoxy(29,17);cout<<"±±±±±±±±±±±±±±±±±±";
	
	 gotoxy(72,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,16);cout<<" ELIMINAR <2> ±±±±";
	 gotoxy(72,17);cout<<"±±±±±±±±±±±±±±±±±±";
	 
	 do{
	 	gotoxy(35,20);op=getch();
	 }while(op!='1' && op!='2');

	system("cls");
	if(op=='1'){
		registrar_ubicaciones();
		back_panel();
	}else{
		eliminar_ubicaciones();
		back_panel();
	}
}

//Admin-----------Locales
void registrar_locales(){
	color(250);
	linea(20,78,0);
	linea(20,78,3);
	color(240);
	ofstream File_1("locales.txt",ios::app);
    gotoxy(21,1);cout<<"¿CUANTAS LOCALES VA HA REGISTRAR ?"<<endl;
    int n; 
    gotoxy(21,2);cin>>n;
    color(250);
	linea(3,108,4);
    color(240);
    gotoxy(3,5);cout<<"CODIGO LOCAL "<<endl;
 	gotoxy(16,5);cout<<"UBIGEO "<<endl;
 	gotoxy(25,5);cout<<"NOMBRE "<<endl;
	local nuevo[n];
 	bool primero=true;
 	for(int i=0;i<n;i++){
 	   if(primero){
 	     gotoxy(3,7+i);gets(nuevo[i].local);
 	     primero=false;
       }
		gotoxy(3,7+i);gets(nuevo[i].local);
		gotoxy(16,7+i);gets(nuevo[i].ubigeo);
		gotoxy(25,7+i);gets(nuevo[i].nombre);
		File_1<<nuevo[i].local<<" "<<nuevo[i].ubigeo<<" "<<nuevo[i].nombre<<endl;
    }
 	File_1.close();
 	system("cls");
}

void eliminar_locales(){
	cout<<"locales"<<endl;;
}

void administrar_locales(){
	char op;
	for(int i=20;i<=98;i++){
		gotoxy(i,6);cout<<"Í";
		gotoxy(i,10);cout<<"Í";
		gotoxy(i,22);cout<<"Í";
 	}
	  color(176);
	 gotoxy(47,8);cout<<" ADMINISTRAR LOCALES ";
	 color(248);
	 gotoxy(50,11);cout<<"±±±±±±±±±±±±±±±±±";
	 color(245);
	 gotoxy(50,12);cout<<" ELIGA UNA TAREA ";
	 color(248);
	 gotoxy(50,13);cout<<"±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(29,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(29,16);cout<<" REGISTRAR <1> ±±±";
	 gotoxy(29,17);cout<<"±±±±±±±±±±±±±±±±±±";
	
	 gotoxy(72,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,16);cout<<" ELIMINAR <2> ±±±±";
	 gotoxy(72,17);cout<<"±±±±±±±±±±±±±±±±±±";
	 
	 do{
	 	gotoxy(35,20);op=getch();
	 }while(op!='1' && op!='2');

	system("cls");
	if(op=='1'){
		registrar_locales();
		back_panel();
	}else{
		eliminar_locales();
		back_panel();
	}
}

//Admin------------Mesas
void registrar_mesas(){
	color(250);
	linea(20,78,0);
	linea(20,78,3);
	color(240);
	ofstream File_1("mesas.txt",ios::app);
    gotoxy(21,1);cout<<"¿CUANTAS MESAS VA HA REGISTRAR ?"<<endl;
    int n; 
    gotoxy(21,2);cin>>n;
    color(250);
	linea(3,108,4);
    color(240);
    gotoxy(3,5);cout<<"CODIGO MESA "<<endl;
 	gotoxy(16,5);cout<<"CODIGO LOCAL "<<endl;
 	gotoxy(30,5);cout<<"UBIGEO "<<endl;
	mesa nuevo[n];
 	bool primero=true;
 	for(int i=0;i<n;i++){
 	   if(primero){
 	     gotoxy(3,7+i);gets(nuevo[i].mesa);
 	     primero=false;
       }
		gotoxy(3,7+i);gets(nuevo[i].mesa);
		gotoxy(16,7+i);gets(nuevo[i].local);
		gotoxy(30,7+i);gets(nuevo[i].ubigeo);
		File_1<<nuevo[i].mesa<<" "<<nuevo[i].local<<" "<<nuevo[i].ubigeo<<endl;
    }
 	File_1.close();
 	system("cls");
}

void eliminar_mesas(){
	cout<<"mesas"<<endl;
}

void administrar_mesas(){
	char op;
	for(int i=20;i<=98;i++){
		gotoxy(i,6);cout<<"Í";
		gotoxy(i,10);cout<<"Í";
		gotoxy(i,22);cout<<"Í";
 	}
	  color(176);
	 gotoxy(47,8);cout<<" ADMINISTRAR MESAS ";
	 color(248);
	 gotoxy(50,11);cout<<"±±±±±±±±±±±±±±±±±";
	 color(245);
	 gotoxy(50,12);cout<<" ELIGA UNA TAREA ";
	 color(248);
	 gotoxy(50,13);cout<<"±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(29,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(29,16);cout<<" REGISTRAR <1> ±±±";
	 gotoxy(29,17);cout<<"±±±±±±±±±±±±±±±±±±";
	
	 gotoxy(72,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,16);cout<<" ELIMINAR <2> ±±±±";
	 gotoxy(72,17);cout<<"±±±±±±±±±±±±±±±±±±";
	 
	 do{
	 	gotoxy(35,20);op=getch();
	 }while(op!='1' && op!='2');

	system("cls");
	if(op=='1'){
		registrar_mesas();
		back_panel();
	}else{
		eliminar_mesas();
		back_panel();
	}
}

//Admin--------Candidatos
void registrar_candidatos(){
	color(250);
	linea(20,78,0);
	linea(20,78,3);
	color(240);
	ofstream File_1("candidatos.txt",ios::app);
    gotoxy(21,1);cout<<"¿CUANTOS CANDIDATOS VA HA REGISTRAR ?"<<endl;
    int n; 
    gotoxy(21,2);cin>>n;
    color(240);
    gotoxy(21,4);cout<<"CODIGO "<<endl;
 	gotoxy(45,4);cout<<"CANDIDATO "<<endl;
 	candidato nuevo[n];
 	bool primero=true;
 	for(int i=0;i<n;i++){
 	   if(primero){
 	     gotoxy(21,6+i);gets(nuevo[i].ID);
 	     primero=false;
       }
		gotoxy(21,6+i);gets(nuevo[i].ID);
		gotoxy(45,6+i);gets(nuevo[i].nombre);
		File_1<<endl;
		File_1<<nuevo[i].ID<<" "<<nuevo[i].nombre;
    }
 	File_1.close();
 	system("cls");
 }

void eliminar_candidatos(){
	ifstream leer("candidatos.txt",ios::in);
	linea(20,78,6);
	linea(20,78,22);
    char visual;
    gotoxy(21,8);cout<<"Quiere visualizar los nombres de los "<<endl;
    gotoxy(21,9);cout<<"candidatos registrados? "<<endl;
    gotoxy(21,11);cout<<"SI <1> "<<endl;
    gotoxy(21,12);cout<<"NO <2> "<<endl;
    visual=getch();
    system("cls");
    if(visual=='1'){
    	linea(20,78,6);
		linea(20,78,28);
		char cand[100];
		int i=0;
    	while(1){
	 		if(!leer){
	 			break;
			}
			leer.getline(cand,99);
			gotoxy(16,12+i);cout<<cand;
			i++;
		}
		gotoxy(20,30);system("pause");
		leer.close();
		system("cls");
	}
	linea(20,78,6);
	linea(20,78,22);
 	gotoxy(21,8);cout<<"Agrege el nombre del candidato que desea eliminar"<<endl;
 	char candidato[100];
    gotoxy(21,10);gets(candidato);
    proceso_quitar(candidato);
    system("cls");
    linea(20,78,6);
	linea(20,78,22);
	gotoxy(21,8);cout<<"El candidato se elimino correctamente "<<endl;
	gotoxy(21,23);system("pause");
	system("cls");
}

void administrar_candidatos(){
	char op;
	for(int i=20;i<=98;i++){
		gotoxy(i,6);cout<<"Í";
		gotoxy(i,10);cout<<"Í";
		gotoxy(i,22);cout<<"Í";
 	}
	  color(176);
	 gotoxy(47,8);cout<<" ADMINISTRAR CANDIDATOS ";
	 color(248);
	 gotoxy(50,11);cout<<"±±±±±±±±±±±±±±±±±";
	 color(245);
	 gotoxy(50,12);cout<<" ELIGA UNA TAREA ";
	 color(248);
	 gotoxy(50,13);cout<<"±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(29,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(29,16);cout<<" REGISTAR <1> ±±±±";
	 gotoxy(29,17);cout<<"±±±±±±±±±±±±±±±±±±";
	
	 gotoxy(72,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,16);cout<<" ELIMINAR <2> ±±±±";
	 gotoxy(72,17);cout<<"±±±±±±±±±±±±±±±±±±";
	 
	 do{
	 	gotoxy(35,20);op=getch();
	 }while(op!='1' && op!='2');

	system("cls");
	if(op=='1'){
		registrar_candidatos();
		back_panel();
	}else{
		eliminar_candidatos();
		back_panel();
	}
}

//Admin-----------Actas
void registrar_actas(int &c){
	color(250);
	linea(20,78,0);
	linea(20,78,3);
	color(240);
	ofstream File_1("actas.txt",ios::app);
    gotoxy(21,1);cout<<"¿CUANTAS ACTAS VA HA REGISTRAR ?"<<endl;
    int n; 
    gotoxy(21,2);cin>>n;
    color(250);
	linea(3,108,4);
    color(240);
    gotoxy(3,5);cout<<"MESA "<<endl;
 	gotoxy(12,5);cout<<"UBIGEO "<<endl;
 	gotoxy(21,5);cout<<"HABILES "<<endl;
 	gotoxy(30,5);cout<<"VOTANTES "<<endl;
 	gotoxy(39,5);cout<<"BLANCOS "<<endl;
 	gotoxy(48,5);cout<<"NULOS "<<endl;
 	for(int i=0;i<c;i++){
 		gotoxy(57+13*i,5);cout<<C[i].nombre<<endl;
	}
	acta nuevo[n];
 	bool primero=true;
 	for(int i=0;i<n;i++){
 	   if(primero){
 	     gotoxy(3,7+i);gets(nuevo[i].mesa);
 	     primero=false;
       }
		gotoxy(3,7+i);gets(nuevo[i].mesa);
		gotoxy(12,7+i);gets(nuevo[i].ubigeo);
		gotoxy(21,7+i);cin>>nuevo[i].habiles;
	 	gotoxy(30,7+i);cin>>nuevo[i].votantes;
	 	gotoxy(39,7+i);cin>>nuevo[i].blancos;
	 	gotoxy(48,7+i);cin>>nuevo[i].nulos;
	 	for(int j=0;j<c;j++){
	 		gotoxy(57+13*j,7+i);cin>>nuevo[i].candidatos[j];
		}
		File_1<<nuevo[i].mesa<<" "<<nuevo[i].ubigeo<<" "<<nuevo[i].habiles<<" "<<nuevo[i].votantes<<" "" "<<nuevo[i].blancos<<" "<<nuevo[i].nulos<<" ";
		for(int j=0;j<c;j++){
			File_1<<nuevo[i].candidatos[j]<<" ";
		}
		File_1<<endl;
    }
 	File_1.close();
 	system("cls");
 }

void eliminar_actas(){
	cout<<"hola"<<endl;
}

void administrar_actas(int &c){
	char op;
	for(int i=20;i<=98;i++){
		gotoxy(i,6);cout<<"Í";
		gotoxy(i,10);cout<<"Í";
		gotoxy(i,22);cout<<"Í";
 	}
	  color(176);
	 gotoxy(47,8);cout<<" ADMINISTRAR ACTAS ";
	 color(248);
	 gotoxy(50,11);cout<<"±±±±±±±±±±±±±±±±±";
	 color(245);
	 gotoxy(50,12);cout<<" ELIGA UNA TAREA ";
	 color(248);
	 gotoxy(50,13);cout<<"±±±±±±±±±±±±±±±±±";
	 
	 gotoxy(29,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(29,16);cout<<" REGISTRAR <1> ±±±";
	 gotoxy(29,17);cout<<"±±±±±±±±±±±±±±±±±±";
	
	 gotoxy(72,15);cout<<"±±±±±±±±±±±±±±±±±±";
	 gotoxy(72,16);cout<<" ELIMINAR <2> ±±±±";
	 gotoxy(72,17);cout<<"±±±±±±±±±±±±±±±±±±";
	 
	 do{
	 	gotoxy(35,20);op=getch();
	 }while(op!='1' && op!='2');

	system("cls");
	if(op=='1'){
		registrar_actas(c);
		back_panel();
	}else{
		eliminar_actas();
		back_panel();
	}
}

//Opciones de Sistema--------
void restaurar(){
	ofstream copiar("auxiliar.txt",ios::out);
	copiar.close();
	remove("actas.txt");
	rename("auxiliar.txt","actas.txt");
	ofstream copiar1("auxiliar.txt",ios::out);
	copiar1.close();
	remove("departamentos.txt");
	rename("auxiliar.txt","departamentos.txt");
	ofstream copiar2("auxiliar.txt",ios::out);
	copiar2.close();
	remove("provincias.txt");
	rename("auxiliar.txt","provincias.txt");
	ofstream copiar3("auxiliar.txt",ios::out);
	copiar3.close();
	remove("distritos.txt");
	rename("auxiliar.txt","distritos.txt");
	ofstream copiar4("auxiliar.txt",ios::out);
	copiar4.close();
	remove("locales.txt");
	rename("auxiliar.txt","locales.txt");
	ofstream copiar5("auxiliar.txt",ios::out);
	copiar5.close();
	remove("mesas.txt");
	rename("auxiliar.txt","mesas.txt");
	ofstream copiar6("auxiliar.txt",ios::out);
	copiar6.close();
	remove("candidatos.txt");
	rename("auxiliar.txt","candidatos.txt");
	back_panel();
}

void validar(int &dis, int &l, int &m){
	int cantU=0;
	bool aux;
	for(int i=0;i<dis;i++){
		aux=true;
		for(int j=0;j<l;j++){
			if(strcmp(Dis[i].ubigeo,L[j].ubigeo)==0){
				aux=false;
				break;
			}
		}
		if(aux){
			cantU++;
		}
	}
	
	int cantL=0;
	for(int i=0;i<l;i++){
		aux=true;
		for(int j=0;j<m;j++){
			if(strcmp(L[i].local,M[j].local)==0){
				aux=false;
				break;
			}
		}
		if(aux){
			cantL++;
		}
	}
	linea(20,78,6);
	linea(20,78,22);
	gotoxy(37,8);cout<<"Existen " << cantU <<"  ubicaciones con 0 locales de votacion"<<endl;
	gotoxy(37,11);cout<<"Existen " << cantL <<"  locales de votacion con 0 mesas de votacion"<<endl;
	
	back_panel();
}

void admin(int &c, int &dis, int &l,int &m){
	interfaz_de_admin();
	ingresar();
	char op;
	while(1){
		panel_administracion(op);
		switch(op){
			case '0':
				restaurar();
				break;
			case '1':
				administrar_ubicaciones();
				break;
			case '2':
				administrar_candidatos();
				break;
			case '3':
				administrar_locales();
				break;
			case '4':
				administrar_mesas();
				break;
			case '5':
				administrar_actas(c);
				break;
			case '6':
				validar(dis,l,m);
				break;
		}
	}
}

//Funciones de Procesos de Alamcenamiento de Datos---------------------------------------
void registroCandidatos(candidato C[], int &c){
	ifstream File_1("candidatos.txt");
	for(int i=0;i<c;i++){
		char line[30];
		File_1>> C[i].ID >> C[i].nombre;
		File_1.getline(line,30);
		strcat(C[i].nombre,line);
		C[i].votos=0;
		C[i].N=0;
		C[i].E=0;
	}
	File_1.close();
}

void registroMesas(mesa M[],int n){
	ifstream File_1("mesas.txt");
	for(int i=0;i<n;i++){
		File_1>>M[i].mesa>> M[i].local >> M[i].ubigeo;
	}
	File_1.close();
}

void registroLocales(local L[],int n){
	ifstream File_1("locales.txt");
	for(int i=0;i<n;i++){
		char line[100];
		File_1>> L[i].local >> L[i].ubigeo>> L[i].nombre;
		File_1.getline(line,100);
		strcat(L[i].nombre,line);
	}
	File_1.close();
}

void registroDistritos(distrito Dis[],int n, int &c){
	ifstream File_1("distritos.txt");
	for(int i=0;i<n;i++){
		char line[30];
		File_1>> Dis[i].ubigeo >> Dis[i].ambito >> Dis[i].nombre;
		File_1.getline(line,30);
		strcat(Dis[i].nombre,line);
		Dis[i].habiles=0;
		Dis[i].votantes=0;
		for(int j=0;j<c;j++){
			Dis[i].candidatos[j]=0;
		}
	}
	File_1.close();
}

void registroProvincias(provincia P[], int n, int &c){
	ifstream File_1("provincias.txt");
	for(int i=0;i<n;i++){
		char line[30];
		File_1>> P[i].ubigeo >> P[i].ambito >> P[i].nombre;
		File_1.getline(line,30);
		strcat(P[i].nombre,line);
		P[i].habiles=0;
		P[i].votantes=0;
		for(int j=0;j<c;j++){
			P[i].candidatos[j]=0;
		}
	}
	File_1.close();
}

void registroDepartamentos(departamento D[], int n, int &c){
	ifstream File_1("departamentos.txt");
	for(int i=0;i<n;i++){
		char line[30];
		File_1>> D[i].ubigeo >> D[i].ambito >> (D[i].nombre);
		File_1.getline(line,20);
		strcat(D[i].nombre,line);
		D[i].habiles=0;
		D[i].votantes=0;
		for(int j=0;j<c;j++){
			D[i].candidatos[j]=0;
		}
	}
	File_1.close();
}

void Win_ausentismoDepartamentos(departamento D[], int n, int &c){
	for(int i=0;i<n;i++){
		int index=index_Nmax(D[i].candidatos,c);
		strcpy(D[i].ganador,C[index].nombre);
		if(D[i].habiles>0){
			D[i].ausentismo =(double)D[i].votantes/D[i].habiles;
			D[i].ausentismo =1-D[i].ausentismo;
		}else{
			D[i].ausentismo=0;
		}
	}
}

void Win_ausentismoProvincias(provincia P[], int n,int &c){
	for(int i=0;i<n;i++){
		int index=index_Nmax(P[i].candidatos,c);
		strcpy(P[i].ganador,C[index].nombre);
		if(P[i].habiles>0){
			P[i].ausentismo =(double)P[i].votantes/P[i].habiles;
			P[i].ausentismo =1-P[i].ausentismo;
		}else{
			P[i].ausentismo=0;
		}
	}
}

void Win_ausentismoDistritos(distrito Dis[], int n, int &c){
	for(int i=0;i<n;i++){
		int index=index_Nmax(Dis[i].candidatos,c);
		strcpy(Dis[i].ganador,C[index].nombre);
		if(Dis[i].habiles>0){
			Dis[i].ausentismo =(double)Dis[i].votantes/Dis[i].habiles;
			Dis[i].ausentismo =1-Dis[i].ausentismo;
		}else{
			Dis[i].ausentismo=0;
		}
	}
}

void procesamientoActa(const acta &A, int &d,int &p,int &dis, int &c){
	//total de votos por candidatos
	for(int i=0;i<c;i++){
		C[i].votos +=A.candidatos[i];
	}
	//departamentos
	for(int i=0;i<d;i++){
		if(A.ubigeo[0]==D[i].ubigeo[0] && A.ubigeo[1]==D[i].ubigeo[1]){
			D[i].habiles += A.habiles;
			D[i].votantes +=A.votantes;
			for(int j=0;j<c;j++){
				D[i].candidatos[j] += A.candidatos[j];
			}
			//total por ambito segun candidato
			if(D[i].ambito=='P'){
				TotalP+=A.habiles;
				for(int i=0;i<c;i++){
					C[i].N+=A.candidatos[i];
				}
			}else if(D[i].ambito=='E'){
				TotalE+=A.habiles;
				for(int i=0;i<c;i++){
					C[i].E+=A.candidatos[i];
				}
			}
			
			break;
		}
	}
	//provincias
	for(int i=0;i<p;i++){
		if(A.ubigeo[0]==P[i].ubigeo[0] && A.ubigeo[1]==P[i].ubigeo[1] && A.ubigeo[2]==P[i].ubigeo[2] && A.ubigeo[3]==P[i].ubigeo[3]){
			P[i].habiles += A.habiles;
			P[i].votantes +=A.votantes;
			for(int j=0;j<c;j++){
				P[i].candidatos[j] += A.candidatos[j];
			}
			break;
		}
	}
	//distritos
	for(int i=0;i<dis;i++){
		if(strcmp(A.ubigeo,Dis[i].ubigeo)==0){
			Dis[i].habiles +=A.habiles;
			Dis[i].votantes +=A.votantes;
			for(int j=0;j<c;j++){
				Dis[i].candidatos[j] += A.candidatos[j];
			}
			break;
		}
	}
}

void registroActas(acta A[],int n, int &d, int &p, int &dis, int &c){
	ifstream File_1("actas.txt");
	for(int i=0;i<n;i++){
		File_1>> A[i].mesa >> A[i].ubigeo >> A[i].habiles >> A[i].votantes >> A[i].blancos >> A[i].nulos;
		for(int j=0;j<2;j++){
			File_1 >> A[i].candidatos[j];
		}
		procesamientoActa(A[i],d,p,dis,c);
		Win_ausentismoDepartamentos(D,d,c);
		Win_ausentismoProvincias(P,p,c);
		Win_ausentismoDistritos(Dis,dis,c);
	}
	File_1.close();
}

//Procedimientos de busqueda-------------------------------
bool buscarDepartamento(const char nombre[], char &ambito,int &d){
	bool esta=false;
	for(int i=0;i<d;i++){
		if(ambito==D[i].ambito){
			if(strcmp(D[i].nombre,nombre)==0){
				esta=true;
				break;
			}
		}
	}
	return esta;
}

bool buscarProvincia(const char nombre[], char &ambito,int &p){
	bool esta=false;
	for(int i=0;i<p;i++){
		if(ambito==P[i].ambito){
			if(strcmp(P[i].nombre,nombre)==0){
				esta=true;
				break;
			}
		}
	}
	return esta;
}

bool buscarDistrito(const char nombre[], char &ambito,int &dis){
	bool esta=false;
	for(int i=0;i<dis;i++){
		if(ambito==Dis[i].ambito){
			if(strcmp(Dis[i].nombre,nombre)==0){
				esta=true;
				break;
			}
		}
	}
	return esta;
}

//buscar indices
long long Index_buscarDepartamento(const char nombre[], char &ambito,int &d){
	int index;
	for(int i=0;i<d;i++){
		if(ambito==D[i].ambito){
			if(strcmp(D[i].nombre,nombre)==0){
				index=i;
				break;
			}
		}
	}
	return index;
}

long long Index_buscarProvincia(const char nombre[], char &ambito,int &p){
	int index;
	for(int i=0;i<p;i++){
		if(ambito==P[i].ambito){
			if(strcmp(P[i].nombre,nombre)==0){
				index=i;
				break;
			}
		}
	}
	return index;
}

long long Index_buscarDistrito(const char nombre[], char &ambito,int &dis){
	int index;
	for(int i=0;i<dis;i++){
		if(ambito==Dis[i].ambito){
			if(strcmp(Dis[i].nombre,nombre)==0){
				index=i;
				break;
			}
		}
	}
	return index;
}

//Pertenecia-------------------
bool Provincia_Departamento(provincia &P,departamento &D){
	if(D.ubigeo[0]==P.ubigeo[0] && D.ubigeo[1]==P.ubigeo[1]){
		return true;
	}else{
		return false;
	}
}

bool Distrito_Provincia(distrito &Dis,provincia &P){
	if(P.ubigeo[0]==Dis.ubigeo[0] && P.ubigeo[1]==Dis.ubigeo[1] && P.ubigeo[2]==Dis.ubigeo[2] && P.ubigeo[3]==Dis.ubigeo[3]){
		return true;
	}else{
		return false;
	}
}

//Proceso de filtrado-------------------------------------------------------------
void preguntafiltros(int n){
	char i;
	gotoxy(0,n);cout<<"¿Desea filtrar los resultados segun lugar de votacion? (1)Si  (2)Salir ";
	i=getch();
	if(i=='1'){
		system("cls");
	}else if(i=='2'){
		system("cls");
		exit(0);
	}else{
		preguntafiltros(n);
	}
}

void mostrarfiltros(int &c,int &d, int &p, int &dis){
	doblelinea(0,110,0);
	doblelinea(0,110,22);
	Item I;
	char ambito;
	do{
		gotoxy(40,2);cout<<"Plataforma de filtrado";
		gotoxy(0,4);cout<<"Ambito: "<<"  (N)Nacional"<<"  (E)Extranjero";
		gotoxy(37,4);cout<<"Elija: ";
		ambito=getche();
	}while(ambito!='N' && ambito!='E');
	
	if(ambito=='N'){
		I.ambito='P';
		do{
			gotoxy(0,6);cout<<"Departamento: "<<"(T)Todos"<<" o Ingrese el nombre del Departamento "<<endl;
			cin>>I.departamento;
			/*if(strcmp(I.departamento,"T")==0 || buscarDepartamento(I.departamento,d)){
				gotoxy(0,8);cout<<"Introdujo una opcion valida";
			}else{
				gotoxy(0,8);cout<<"Introdujo una opcion no valida";
			}*/
		}while(strcmp(I.departamento,"T")!=0 && !buscarDepartamento(I.departamento,I.ambito,d));
		
		if(strcmp(I.departamento,"T")==0){
			system("cls");
			doblelinea(0,110,0);
			gotoxy(35,2);cout<<"Resultados Generales en el Peru: "<<endl;
			int index=index_Nmax_Ambito(C,c,I.ambito);
			gotoxy(32,4);cout<<"Ganador en el ambito nacional: "<<C[index].nombre<<endl;
			gotoxy(2,6);cout<<"Ubigeo";
			gotoxy(10,6);cout<<"Departameto";
			
			for(int i=0;i<c;i++){
				gotoxy(28+13*i,6);cout<<C[i].nombre;
			}
			gotoxy(32+13*c,6);cout<<"Ganador"<<endl;
			gotoxy(35+13*(c+1),6);cout<<"% de ausentismo";
			cout<<endl;
			int pos=0;
			for(int i=0;i<d;i++){
				if(D[i].ambito=='P'){
					gotoxy(2,8+pos);cout<<D[i].ubigeo<<" ";
					gotoxy(10,8+pos);cout<<D[i].nombre<<" ";
					for(int j=0;j<c;j++){
						gotoxy(28+13*j,8+pos);cout<<D[i].candidatos[j]<<" ";
					}
					gotoxy(32+13*c,8+pos);cout<<D[i].ganador;
					gotoxy(35+13*(c+1),8+pos);cout<<D[i].ausentismo;
					pos++;
				}
			}
			gotoxy(12,9+pos);cout<<"Totales: ";
			for(int i=0;i<c;i++){
				linea(28+13*i,10,8+pos);
				gotoxy(28+13*i,9+pos);cout<<C[i].N;
			}
			doblelinea(0,110,13+pos);
			preguntafiltros(11+pos);
			mostrarfiltros(c,d,p,dis);
		}else{
			do{
				gotoxy(0,8);cout<<"Provincia: "<<"(T)Todos"<<" o Ingrese el nombre de la Provincia "<<endl;
				cin>>I.provincia;
				/*if(strcmp(I.departamento,"T")==0 || buscarDepartamento(I.departamento,d)){
					gotoxy(0,8);cout<<"Introdujo una opcion valida";
				}else{
					gotoxy(0,8);cout<<"Introdujo una opcion no valida";
				}*/
			}while(strcmp(I.provincia,"T")!=0 && !buscarProvincia(I.provincia,I.ambito,p));
			
			if(strcmp(I.provincia,"T")==0){
				system("cls");
				doblelinea(0,110,0);
				gotoxy(32,2);cout<<"Resultados Generales en el departamento de: "<<I.departamento<<endl;
				int index=Index_buscarDepartamento(I.departamento,I.ambito,d);
				gotoxy(32,4);cout<<"Ganador en "<<I.departamento<<": "<<D[index].ganador<<endl;
				gotoxy(2,6);cout<<"Ubigeo";
				gotoxy(10,6);cout<<"Provincia";
				
				for(int i=0;i<c;i++){
					gotoxy(32+13*i,6);cout<<C[i].nombre;
				}
				gotoxy(35+13*c,6);cout<<"Ganador"<<endl;
				gotoxy(37+13*(c+1),6);cout<<"% de ausentismo";
				cout<<endl;
				int pos=0;
				for(int i=0;i<p;i++){
					if(Provincia_Departamento(P[i],D[index])){
						gotoxy(2,8+pos);cout<<P[i].ubigeo<<" ";
						gotoxy(10,8+pos);cout<<P[i].nombre<<" ";
						for(int j=0;j<c;j++){
							gotoxy(32+13*j,8+pos);cout<<P[i].candidatos[j]<<" ";
						}
						gotoxy(35+13*c,8+pos);cout<<P[i].ganador;
						gotoxy(37+13*(c+1),8+pos);cout<<P[i].ausentismo;
						pos++;
					}
				}
				gotoxy(12,9+pos);cout<<"Totales: ";
				for(int i=0;i<c;i++){
					linea(32+13*i,10,8+pos);
					gotoxy(32+13*i,9+pos);cout<<D[index].candidatos[i];
				}
				doblelinea(0,110,13+pos);
				preguntafiltros(11+pos);
				mostrarfiltros(c,d,p,dis);
			}else{
				do{
					gotoxy(0,10);cout<<"Distrito: "<<"(T)Todos"<<" o Ingrese el nombre del Distrito"<<endl;
					cin>>I.distrito;
					/*if(strcmp(I.departamento,"T")==0 || buscarDepartamento(I.departamento,d)){
						gotoxy(0,8);cout<<"Introdujo una opcion valida";
					}else{
						gotoxy(0,8);cout<<"Introdujo una opcion no valida";
					}*/
				}while(strcmp(I.distrito,"T")!=0 && !buscarDistrito(I.distrito,I.ambito,dis));
				
				if(strcmp(I.distrito,"T")==0){
					system("cls");
					doblelinea(0,110,0);
					gotoxy(32,2);cout<<"Resultados Generales en la Provincia de: "<<I.provincia<<endl;
					int index=Index_buscarProvincia(I.provincia,I.ambito,p);
					gotoxy(32,4);cout<<"Ganador en "<<I.provincia<<": "<<P[index].ganador<<endl;
					gotoxy(2,6);cout<<"Ubigeo";
					gotoxy(10,6);cout<<"Distrito";
					
					for(int i=0;i<c;i++){
						gotoxy(32+13*i,6);cout<<C[i].nombre;
					}
					gotoxy(35+13*c,6);cout<<"Ganador"<<endl;
					gotoxy(37+13*(c+1),6);cout<<"% de ausentismo";
					cout<<endl;
					int pos=0;
					for(int i=0;i<dis;i++){
						if(Distrito_Provincia(Dis[i],P[index])){
							gotoxy(2,8+pos);cout<<Dis[i].ubigeo<<" ";
							gotoxy(10,8+pos);cout<<Dis[i].nombre<<" ";
							for(int j=0;j<c;j++){
								gotoxy(32+13*j,8+pos);cout<<Dis[i].candidatos[j]<<" ";
							}
							gotoxy(35+13*c,8+pos);cout<<Dis[i].ganador;
							gotoxy(37+13*(c+1),8+pos);cout<<Dis[i].ausentismo;
							pos++;
						}
					}
					gotoxy(12,9+pos);cout<<"Totales: ";
					for(int i=0;i<c;i++){
						linea(32+13*i,10,8+pos);
						gotoxy(32+13*i,9+pos);cout<<P[index].candidatos[i];
					}
					doblelinea(0,110,13+pos);
					preguntafiltros(11+pos);
					mostrarfiltros(c,d,p,dis);
				}else{
					color(249);
					gotoxy(32,12);cout<<"Resultados del Distrito de: "<<I.distrito;
					int index=Index_buscarDistrito(I.distrito,I.ambito,dis);
					gotoxy(35,14);cout<<"Ganador: "<<Dis[index].ganador<<endl;
					for(int i=0;i<c;i++){
						gotoxy(32+13*i,16);cout<<C[i].nombre;
					}
					for(int i=0;i<c;i++){
						gotoxy(32+13*i,18);cout<<Dis[index].candidatos[i]<<" ";
					}
					color(240);
					preguntafiltros(20);
					mostrarfiltros(c,d,p,dis);
				}
			}
		}
	
	}else if(ambito=='E'){
		I.ambito='E';
		do{
			gotoxy(0,6);cout<<"Continente: "<<"(T)Todos"<<" o Ingrese el nombre del Continente "<<endl;
			cin>>I.departamento;
			/*if(strcmp(I.departamento,"T")==0 || buscarDepartamento(I.departamento,d)){
				gotoxy(0,8);cout<<"Introdujo una opcion valida";
			}else{
				gotoxy(0,8);cout<<"Introdujo una opcion no valida";
			}*/
		}while(strcmp(I.departamento,"T")!=0 && !buscarDepartamento(I.departamento,I.ambito,d));
		
		if(strcmp(I.departamento,"T")==0){
			system("cls");
			doblelinea(0,110,0);
			gotoxy(35,2);cout<<"Resultados Generales en el extranjero: "<<endl;
			int index=index_Nmax_Ambito(C,c,I.ambito);
			gotoxy(32,4);cout<<"Ganador en el extranjero: "<<C[index].nombre<<endl;
			gotoxy(2,6);cout<<"Ubigeo";
			gotoxy(10,6);cout<<"Continente";
			
			for(int i=0;i<c;i++){
				gotoxy(28+13*i,6);cout<<C[i].nombre;
			}
			gotoxy(32+13*c,6);cout<<"Ganador"<<endl;
			gotoxy(35+13*(c+1),6);cout<<"% de ausentismo";
			cout<<endl;
			int pos=0;
			for(int i=0;i<d;i++){
				if(D[i].ambito=='E'){
					gotoxy(2,8+pos);cout<<D[i].ubigeo<<" ";
					gotoxy(10,8+pos);cout<<D[i].nombre<<" ";
					for(int j=0;j<c;j++){
						gotoxy(28+13*j,8+pos);cout<<D[i].candidatos[j]<<" ";
					}
					gotoxy(32+13*c,8+pos);cout<<D[i].ganador;
					gotoxy(35+13*(c+1),8+pos);cout<<D[i].ausentismo;
					pos++;
				}
			}
			gotoxy(12,9+pos);cout<<"Totales: ";
			for(int i=0;i<c;i++){
				linea(28+13*i,10,8+pos);
				gotoxy(28+13*i,9+pos);cout<<C[i].E;
			}
			doblelinea(0,110,13+pos);
			preguntafiltros(11+pos);
			mostrarfiltros(c,d,p,dis);
		}else{
			do{
				gotoxy(0,8);cout<<"Pais: "<<"(T)Todos o Ingrese el nombre del Pais "<<endl;
				cin>>I.provincia;
				/*if(strcmp(I.departamento,"T")==0 || buscarDepartamento(I.departamento,d)){
					gotoxy(0,8);cout<<"Introdujo una opcion valida";
				}else{
					gotoxy(0,8);cout<<"Introdujo una opcion no valida";
				}*/
			}while(strcmp(I.provincia,"T")!=0 && !buscarProvincia(I.provincia,I.ambito,p));
			
			if(strcmp(I.provincia,"T")==0){
				system("cls");
				doblelinea(0,110,0);
				gotoxy(32,2);cout<<"Resultados Generales en : "<<I.departamento<<endl;
				int index=Index_buscarDepartamento(I.departamento,I.ambito,d);
				gotoxy(32,4);cout<<"Ganador en "<<I.departamento<<": "<<D[index].ganador<<endl;
				gotoxy(2,6);cout<<"Ubigeo";
				gotoxy(10,6);cout<<"Pais";
				
				for(int i=0;i<c;i++){
					gotoxy(32+13*i,6);cout<<C[i].nombre;
				}
				gotoxy(35+13*c,6);cout<<"Ganador"<<endl;
				gotoxy(37+13*(c+1),6);cout<<"% de ausentismo";
				cout<<endl;
				int pos=0;
				for(int i=0;i<p;i++){
					if(Provincia_Departamento(P[i],D[index])){
						gotoxy(2,8+pos);cout<<P[i].ubigeo<<" ";
						gotoxy(10,8+pos);cout<<P[i].nombre<<" ";
						for(int j=0;j<c;j++){
							gotoxy(32+13*j,8+pos);cout<<P[i].candidatos[j]<<" ";
						}
						gotoxy(35+13*c,8+pos);cout<<P[i].ganador;
						gotoxy(37+13*(c+1),8+pos);cout<<P[i].ausentismo;
						pos++;
					}
				}
				gotoxy(12,9+pos);cout<<"Totales: ";
				for(int i=0;i<c;i++){
					linea(32+13*i,10,8+pos);
					gotoxy(32+13*i,9+pos);cout<<D[index].candidatos[i];
				}
				doblelinea(0,110,13+pos);
				preguntafiltros(11+pos);
				mostrarfiltros(c,d,p,dis);
			}else{
				do{
					gotoxy(0,10);cout<<"Ciudad: "<<"(T)Todos"<<" o Ingrese el nombre del Ciudad"<<endl;
					cin>>I.distrito;
					/*if(strcmp(I.departamento,"T")==0 || buscarDepartamento(I.departamento,d)){
						gotoxy(0,8);cout<<"Introdujo una opcion valida";
					}else{
						gotoxy(0,8);cout<<"Introdujo una opcion no valida";
					}*/
				}while(strcmp(I.distrito,"T")!=0 && !buscarDistrito(I.distrito,I.ambito,dis));
				
				if(strcmp(I.distrito,"T")==0){
					system("cls");
					doblelinea(0,110,0);
					gotoxy(32,2);cout<<"Resultados Generales en: "<<I.provincia<<endl;
					long long index=Index_buscarProvincia(I.provincia,I.ambito,p);
					gotoxy(32,4);cout<<"Ganador en "<<I.provincia<<": "<<P[index].ganador<<endl;
					gotoxy(2,6);cout<<"Ubigeo";
					gotoxy(10,6);cout<<"Ciudad";
					
					for(int i=0;i<c;i++){
						gotoxy(32+13*i,6);cout<<C[i].nombre;
					}
					gotoxy(35+13*c,6);cout<<"Ganador"<<endl;
					gotoxy(37+13*(c+1),6);cout<<"% de ausentismo";
					cout<<endl;
					int pos=0;
					for(int i=0;i<dis;i++){
						if(Distrito_Provincia(Dis[i],P[index])){
							gotoxy(2,8+pos);cout<<Dis[i].ubigeo<<" ";
							gotoxy(10,8+pos);cout<<Dis[i].nombre<<" ";
							for(int j=0;j<c;j++){
								gotoxy(32+13*j,8+pos);cout<<Dis[i].candidatos[j]<<" ";
							}
							gotoxy(35+13*c,8+pos);cout<<Dis[i].ganador;
							gotoxy(37+13*(c+1),8+pos);cout<<Dis[i].ausentismo;
							pos++;
						}
					}
					gotoxy(12,9+pos);cout<<"Totales: ";
					for(int i=0;i<c;i++){
						linea(32+13*i,10,8+pos);
						gotoxy(32+13*i,9+pos);cout<<P[index].candidatos[i];
					}
					doblelinea(0,110,13+pos);
					preguntafiltros(11+pos);
					mostrarfiltros(c,d,p,dis);
				}else{
					color(249);
					gotoxy(32,12);cout<<"Resultados de la Ciuadad de: "<<I.distrito;
					int index=Index_buscarDistrito(I.distrito,I.ambito,dis);
					gotoxy(35,14);cout<<"Ganador: "<<Dis[index].ganador<<endl;
					for(int i=0;i<c;i++){
						gotoxy(32+13*i,16);cout<<C[i].nombre;
					}
					for(int i=0;i<c;i++){
						gotoxy(32+13*i,18);cout<<Dis[index].candidatos[i]<<" ";
					}
					color(240);
					preguntafiltros(20);
					mostrarfiltros(c,d,p,dis);
				}
			}
		}
	}
}

void ResultadosGenerales(int &c, int &d, int &p, int &dis){
	doblelinea(0,110,0);
	gotoxy(40,2);cout<<"Resultados Generales"<<endl;
	gotoxy(2,4);cout<<"ID";
	gotoxy(10,4);cout<<"Nombre";
	gotoxy(30,4);cout<<"Votos";
	cout<<endl;
	for(int i=0;i<c;i++){
		gotoxy(2,5+i);cout<<C[i].ID;
		gotoxy(10,5+i);cout<<C[i].nombre;
		gotoxy(30,5+i);cout<<C[i].votos;
		cout<<endl;
	}
	cout<<endl;
	doblelinea(0,110,8+c);
	char i;
	bool seguir=false;
	do{
		gotoxy(0,6+c);cout<<"¿Desea filtrar los resultados segun lugar de votacion? (1)Si  (2)Salir ";
		i=getch();
		if(i=='1'){
			system("cls");
			mostrarfiltros(c,d,p,dis);
		}else if(i=='2'){
			system("cls");
			exit(0);
		}else{
			seguir=true;
		}
	}while(seguir);
	
	
}

void mostrarCandidatos(candidato C[],int &c){
	gotoxy(2,4);cout<<"ID";
	gotoxy(8,4);cout<<"Nombre";
	gotoxy(28,4);cout<<"Votos";
	for(int i=0;i<c;i++){
		gotoxy(2,5+i);cout<<C[i].ID;
		gotoxy(8,5+i);cout<<C[i].nombre;
		gotoxy(28,5+i);cout<<C[i].votos;
		cout<<endl;
	}
}

void mostrarDepartamentos(departamento D[], int n, int &c){
	for(int i=0;i<n;i++){
		cout<<D[i].ubigeo<<" ";
		cout<<D[i].ambito<<" ";
		cout<<D[i].nombre<<" ";
		cout<<D[i].habiles<<" ";
		cout<<D[i].votantes<<" ";
		for(int j=0;j<c;j++){
			cout<<D[i].candidatos[j]<<" ";
		}
		cout<<D[i].ausentismo<<" ";
		cout<<endl;
	}
}

void mostrarProvincias(provincia P[], int n, int &c){
	for(int i=0;i<n;i++){
		cout<<P[i].ubigeo<<" ";
		cout<<P[i].ambito<<" ";
		cout<<P[i].nombre<<" ";
		cout<<P[i].habiles<<" ";
		cout<<P[i].votantes<<" ";
		for(int j=0;j<c;j++){
			cout<<P[i].candidatos[j]<<" ";
		}
		cout<<P[i].ausentismo<<" ";
		cout<<endl;
	}
}

void mostrarDistritos(distrito Dis[], int n, int &c){
	for(int i=0;i<n;i++){
		cout<<Dis[i].ubigeo<<" ";
		cout<<Dis[i].ambito<<" ";
		cout<<Dis[i].nombre<<" ";
		cout<<Dis[i].habiles<<" ";
		cout<<Dis[i].votantes<<" ";
		for(int j=0;j<c;j++){
			cout<<Dis[i].candidatos[j]<<" ";
		}
		cout<<Dis[i].ausentismo<<" ";
		cout<<endl;
	}
}

void mostrarMesas(mesa M[],int n){
	for(int i=0;i<n;i++){
		cout<<M[i].mesa<<" ";
		cout<<M[i].local<<" ";
		cout<<M[i].ubigeo<<" ";
		cout<<endl;
	}
}

void mostrarLocales(local L[],int n){
	for(int i=0;i<n;i++){
		cout<<L[i].local<<" ";
		cout<<L[i].ubigeo<<" ";
		cout<<L[i].nombre<<" ";
		cout<<endl;
	}
}

void mostrarActas(acta A[],int n,int &c){
	for(int i=0;i<n;i++){
		cout<<A[i].mesa<<" ";
		cout<<A[i].ubigeo<<" ";
		cout<<A[i].habiles<<" ";
		cout<<A[i].votantes<<" ";
		cout<<A[i].blancos<<" ";
		cout<<A[i].nulos<<" ";
		for(int j=0;j<c;j++){
			cout<<A[i].candidatos[j]<<" ";
		}
		cout<<endl;
	}
}

//Orden
bool ordenCandidatos(const candidato &C1, const candidato &C2){
	if(C1.votos>C2.votos)return true;
	else return false;
}

//Inicializar Valores
int contarCandidatos(){
	int cant=0;
	ifstream File_1("candidatos.txt");
	while(File_1){
		char line[100];
		File_1.getline(line,99);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

int contarMesas(){
	int cant=0;
	ifstream File_1("mesas.txt");
	while(File_1){
		char line[101];
		File_1.getline(line,100);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

int contarLocales(){
	int cant=0;
	ifstream File_1("locales.txt");
	while(File_1){
		char line[300];
		File_1.getline(line,300);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

int contarDepartamentos(){
	int cant=0;
	ifstream File_1("departamentos.txt");
	while(File_1){
		char line[100];
		File_1.getline(line,99);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

int contarProvincias(){
	int cant=0;
	ifstream File_1("Provincias.txt");
	while(File_1){
		char line[100];
		File_1.getline(line,99);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

int contarDistritos(){
	int cant=0;
	ifstream File_1("distritos.txt");
	while(File_1){
		char line[100];
		File_1.getline(line,99);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

int contarActas(){
	int cant=0;
	ifstream File_1("actas.txt");
	while(File_1){
		char line[100];
		File_1.getline(line,99);
		cant++;
	}
	cant--;
	File_1.close();
	return cant;
}

//---------------------------MENU----------------------------------------------------------------------------------
void menu(int &d,int &p,int &dis,int &c,int &l,int &m){
	system("color F1");
 int i;
 char opcion;
  color(241);
  gotoxy(50,1);cout<<"                     ";
  gotoxy(50,2);cout<<"                     ";
  gotoxy(50,3);cout<<"          ";
  gotoxy(45,4);cout<<" SISTEMA DE GESTION ELECTORAL            ";
  color(245);
   for(i=20;i<=98;i++)
 {
  gotoxy(i,6);cout<<"Í";
  gotoxy(i,10);cout<<"Í";
  gotoxy(i,22);cout<<"Í";
 }
 color(176);
 gotoxy(54,8);cout<<" BIENVENIDO ";
 color(248);
 gotoxy(53,11);cout<<"±±±±±±±±±±±±±±±±";
 color(245);
 gotoxy(53,12);cout<<"   ELIGA MODO  ";
 color(248);
 gotoxy(53,13);cout<<"±±±±±±±±±±±±±±±±";
 
 gotoxy(29,15);cout<<"±±±±±±±±±±±±";
 gotoxy(29,16);cout<<" USER < 1 >";
 gotoxy(29,17);cout<<"±±±±±±±±±±±±";
 gotoxy(41,15);cout<<"±±±±±±±±±±±±";
 gotoxy(41,16);cout<<"   ±±±±±±±±±";
 gotoxy(41,17);cout<<"±±±±±±±±±±±±";

 gotoxy(72,15);cout<<"±±±±±±±±±±±±";
 gotoxy(72,16);cout<<"ADMIN < 2 >  ";
 gotoxy(72,17);cout<<"±±±±±±±±±±±±";
 gotoxy(83,15);cout<<"±±±±±±±±±±±±";
 gotoxy(83,16);cout<<"    ±±±±±±±±";
 gotoxy(83,17);cout<<"±±±±±±±±±±±±";

 gotoxy(30,15);cout<<"±±±±±±±±±±±±";
 gotoxy(30,16);
 gotoxy(30,17);cout<<"±±±±±±±±±±±±";
 
 gotoxy(68,15);cout<<"±±±±±±±±±±±±";
 
 gotoxy(68,17);cout<<"±±±±±±±±±±±±";
 do{
 	gotoxy(70,12);opcion=getch();
 }while(opcion!='1' && opcion!='2');
 caso=opcion;
 if(opcion=='1'){
 	system("cls");
 	carga();
 	system("cls");
 	ResultadosGenerales(c,d,p,dis);
 	system("cls");
 }else{
 	system("cls");
 	admin(c,dis,l,m);
	system("cls");
 }
}

int main(){
	//Contabilizacion
	int c=contarCandidatos();
//	cout<<c<<endl;
	//2077/274/30/77299
	int m=contarMesas();
//	cout<<m<<endl;
	int l=contarLocales();
//	cout<<l<<endl;
	int dis=contarDistritos();
//	cout<<dis<<endl;
	int p=contarProvincias();
//	cout<<p<<endl;
	int d=contarDepartamentos();
//	cout<<d<<endl;
	int a=contarActas();
//	cout<<a<<endl;
	//almacenar informacion de candidatos
	registroCandidatos(C,c);
//	mostrarCandidatos(C,c);
//	system("pause");
	//almacenar informacion de distritos
	registroMesas(M,m);
//	mostrarMesas(M,m);
//	system("pause");
	registroLocales(L,l);
//	mostrarLocales(L,l);
//	system("pause");
	registroDistritos(Dis,dis,c);
//	mostrarDistritos(Dis,dis,c);
//	system("pause");
	//almacenar informacion de provincias
	registroProvincias(P,p,c);
//	mostrarProvincias(P,p,c);
//	system("pause");
	//almacenar informacion de departamentos
	registroDepartamentos(D,d,c);
//	mostrarDepartamentos(D,d,c);
//	system("pause");
	//almacenar informacion de actas y subtotales
	registroActas(A,a,d,p,dis,c);
//	mostrarActas(A,a,c);
//	system("pause");
	//ordenar
	sort(C,C+c,ordenCandidatos);
	system("cls");
	menu(d,p,dis,c,l,m);
	system ("pause");
	//Al iniciar sesion en este modo debe advertir :
	//si hay ubicacion sin local de votacion
	//si es que hay algun local sin mesa de votacion
	//Para ello se propone: 
	//1.modificar dichas ubicaciones o locales
		//ubicaciones: sera enviado al administrador de ubicaciones
		//locales: sera enviado al administrador de locales
	//2.omitir y continuar
		
		//Se proponen cinco formas de administrar 
		//y 2 opciones de sistema: restaurar y validar el sistema
		
		//Administracion
		//Ubicaciones, locales y mesas de votacion por separado, asi como candidatos y actas
		
			//Registro de datos: Constara de dos formas
				//Registro manual
				//Registro mediante archivos
			//Modificacion
			//Eliminacion
		
		//Restaurar el sistema: este mostrara una advertencia, y al aceptar eliminara todo
		//caso contrario no hara nada en ambos casos volvera al menu de administracion
		
		//Validar: mostrara
		//si hay ubicacion sin local de votacion
		//si es que hay algun local sin mesa de votacion
		//permitiendo su modificacion
	
	//Al cerrar sesion en este modo debe advertir (igual que al inicio):
	//si hay ubicacion sin local de votacion
	//si es que hay algun local sin mesa de votacion 	
	return 0;
}
