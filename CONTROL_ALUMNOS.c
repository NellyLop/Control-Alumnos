#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#define RESET_COLOR "\x1b[0m"
#define ROJO_T "\x1b[31m"
#define MAGENTA_T  "\x1b[35m"
#define MAGENTA_F  "\x1b[45m"
#define VERDE_T        "\x1b[32m"
#define CYAN_T     "\x1b[36m"
#define AMARILLO_T "\x1b[33m"
#define    AMARILLO_F  "\x1b[43m"
#define CYAN_F     "\x1b[46m"




typedef struct Alumno {
    int matricula; // Matrícula del alumno
    char nombre[50];
    int edad;
    int semestre;
    char carrera[50];
    struct Alumno* siguiente;
} Alumno;

Alumno* lista_alumnos = NULL; // Puntero al primer nodo de la lista

void margen();
void fecha();
void agregarAlumno();
void buscarAlumno();
void modificarAlumno();
void eliminarAlumno();
void cargarAlumnosDesdeArchivo();
int menu();
void gotoxy(int x, int y);
struct Alumno *ordenar(struct Alumno *p);
struct Alumno *leer(struct Alumno *p);
struct Alumno *guardar(struct Alumno *p);
char rutaArchivo[] = "C:\\Users\\lopez\\Downloads\\ESTRUCTURA\\alumnos.txt"; 


int main()
{
	struct Alumno* lista = NULL;
	int opcion;
	int otro;
	int matricula;
	do{
		margen();
		fecha();
		opcion=menu();
		system("cls");
		margen();
		switch(opcion)
		{
			
			fecha();
			case 1:{
				agregarAlumno(&lista,matricula);
				break;
			}
			case 2:{
				gotoxy(43,7);printf(AMARILLO_F"DAR DE BAJA A UN ALUMNO"RESET_COLOR);
				eliminarAlumno();
				gotoxy(33,26);system("pause");
				break;
			}
			case 3:{
				gotoxy(43,7);printf(AMARILLO_F"CONSULTAR DATOS DE UN ALUMNO"RESET_COLOR);
				buscarAlumno();
				gotoxy(33,27);system("pause");
				break;
			}
			case 4:{
				gotoxy(43,5);printf(AMARILLO_F"MODIFICAR DATOS DE UN ALUMNO"RESET_COLOR);
				modificarAlumno();
				break;
			}
			case 5:{
				gotoxy(48,7);printf(AMARILLO_F"ORDENAR LISTA"RESET_COLOR);
				ordenar(lista_alumnos);
				break;
			}
			case 6:{
				//guardar(lista_alumnos);
				guardarAlumnosArchivosTxt();
				gotoxy(33,27);system("pause");
				break;
			}
			case 7:{
				//leer(lista_alumnos);
				cargarAlumnosDesdeArchivo();
				gotoxy(33,27);system("pause");
				break;
			}
			case 8:{
				int i;
				for(i=0;i<3;i++)
				{
					gotoxy(43,16);printf("SALIENDO DEL PROGRAMA...");
					Sleep(800);
					gotoxy(43,16);printf(ROJO_T"SALIENDO DEL PROGRAMA..."RESET_COLOR);
					Sleep(800);
					gotoxy(43,16);printf("SALIENDO DEL PROGRAMA...");	
				}
				system("cls");
				return;
			}
		}
		system("cls");
	}while(opcion!=8);
}

void margen()
{
	gotoxy(45,3);printf(AMARILLO_T"~~ CONTROL DE ALUMNOS ~~"RESET_COLOR,181,233);
    int x, y;
    x = 15;
    gotoxy(x, 1);printf(MAGENTA_T "%c", 201);
    gotoxy(x, 28);printf("%c", 200);
    
    for (x = 16; x <= 90; x++)
    {
        gotoxy(x, 1);printf(MAGENTA_T "%c", 205);
        gotoxy(x, 28);printf("%c", 205);
    }
    for (y = 2; y <= 27; y++)
    {
        gotoxy(15, y);printf(MAGENTA_T "%c", 186);
        gotoxy(91, y);printf("%c", 186);
    }
    gotoxy(91, 1);printf(MAGENTA_T "%c", 187);
    gotoxy(91, 28);printf("%c", 188);
    x = 27;
    gotoxy(x, 2);printf("%c", 201);
    gotoxy(x, 4);printf("%c", 200);

    for (x = 28; x <= 83; x++)
    {
        gotoxy(x, 2);printf(MAGENTA_T "%c", 205);
        gotoxy(x, 4);printf("%c", 205);
    }

    gotoxy(27, 3);printf(MAGENTA_T "%c", 186);
    gotoxy(84, 3);printf("%c", 186);
    gotoxy(84, 2);printf("%c", 187);
    gotoxy(84, 4);printf("%c" RESET_COLOR, 188);
}
void fecha()
{
	// Obtener la fecha y hora actual
    time_t tiempo;
    struct tm * fecha;
    char fecha_actual[100];

    tiempo = time(NULL);
    fecha = localtime(&tiempo);

    // Formatear la fecha actual
     strftime(fecha_actual, sizeof(fecha_actual), "%d/%m/%Y", fecha);
    // Mostrar la fecha actual
    gotoxy(20,6);printf(CYAN_T"Fecha:"RESET_COLOR);
    gotoxy(17,7);printf(" %s", fecha_actual);
}
int menu(){
	char tecla;
	int opcion = 1;
	do{
		gotoxy(53,7);printf(MAGENTA_F" Men%c "RESET_COLOR,163);
		gotoxy(31,9);printf("[  ] Ingresar datos de un alumno (Alta)");
		gotoxy(31,11);printf("[  ] Eliminar un alumno (Baja)");
		gotoxy(31,13);printf("[  ] Buscar un alumno (Consulta)");
		gotoxy(31,15);printf("[  ] Modificar los datos de un alumno (Modificaciones)");
		gotoxy(31,17);printf("[  ] Ordenar lista (Ordenar)");
		gotoxy(31,19);printf("[  ] Almacenar datos en archivo (Guardar)");
		gotoxy(31,21);printf("[  ] Leer datos desde archivo (Abrir)");
		gotoxy(31,23);printf("[  ] Salir");
		gotoxy(33,7+(opcion*2)); printf("");
		tecla = getch();
        switch (tecla) {
            case 72:  
                if (opcion > 1) opcion--;
                break;
            case 80: 
                if (opcion < 8) opcion++;
                break;
            case 'a': 
				opcion = 1;
				tecla = 13;
				break;
            case 'b': 
				opcion = 2;
				tecla = 13;
				break;
            case 'c': 
				opcion = 3;
				tecla = 13;
				break;				
            case 'd': 
				opcion = 4;
				tecla = 13;
				break;
            case 'e': 
				opcion = 5;
				tecla = 13;
				break;
            case 'f': 
				opcion = 6;
				tecla = 13;
				break;											
        }	
	}while(tecla != 13);
	return opcion;
}


void agregarAlumno() {
	void mostrarLista();
    Alumno* nuevo_alumno = (Alumno*) malloc(sizeof(Alumno));
    nuevo_alumno->siguiente = NULL;
	int continuar;
	gotoxy(43,7);printf(AMARILLO_F"DAR DE ALTA A UN ALUMNO"RESET_COLOR);
    gotoxy(30,10);printf(CYAN_T"-> Ingrese la matricula del alumno: "RESET_COLOR);
    scanf("%d",&(nuevo_alumno->matricula));

	if (matriculaExisteEnArchivo(nuevo_alumno->matricula)) {
        gotoxy(30, 26);
        printf(ROJO_T"La matricula ya existe en el archivo."RESET_COLOR);
        sleep(3);
        return;
    }
    
    gotoxy(30,12);printf(CYAN_T"-> Ingrese el nombre del alumno: "RESET_COLOR);
    fflush(stdin);
    gets(nuevo_alumno->nombre);

    gotoxy(30,14);printf(CYAN_T"-> Ingrese la edad del alumno: "RESET_COLOR);
    scanf("%d", &(nuevo_alumno->edad));
    
    gotoxy(30,16);printf(CYAN_T"-> Ingrese el nombre de la carrera: "RESET_COLOR);
    scanf("%s", nuevo_alumno->carrera);
    
    gotoxy(30,18);printf(CYAN_T"-> Ingrese el semestre: "RESET_COLOR);
    gotoxy(55,18);scanf("%d", &(nuevo_alumno->semestre));

    if(lista_alumnos == NULL) {
        lista_alumnos = nuevo_alumno;
    } else {
        Alumno* actual = lista_alumnos;
        while(actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_alumno;
    }
    if (lista_alumnos != NULL) {
           mostrarLista();
        }
	gotoxy(43,26);printf(VERDE_T"Alumno agregado exitosamente."RESET_COLOR);
	sleep(2);
	gotoxy(30,26);printf("1[seguir registrando] / 2[Dejar de registar] :");
	scanf("%d",& continuar);
	if (continuar==1)
	{
		system("cls");
		margen();
		agregarAlumno();
	}	
}




//Buscar un alumno
void buscarAlumno() {
	void mostrarLista();
    if(lista_alumnos == NULL) {
        gotoxy(42,16);printf(ROJO_T"No hay alumnos registrados."RESET_COLOR);
        return;
    }
    if (lista_alumnos != NULL) 
	{
        mostrarLista();
    }
    
    int matricula;
    gotoxy(30,10);printf(CYAN_T"Ingrese la matricula del alumno a buscar: "RESET_COLOR);
    scanf("%d",& matricula);
    gotoxy(30,10);printf("                                                           ");

    Alumno* actual = lista_alumnos;
    while(actual != NULL) {
        if(actual->matricula==matricula) {
            gotoxy(47,11);printf(MAGENTA_T"Datos del alumno:"RESET_COLOR);
            gotoxy(47,13);printf(CYAN_T"Matricula:  "RESET_COLOR"%d", actual->matricula);
            gotoxy(47,15);printf(CYAN_T"Nombre:     "RESET_COLOR"%s", actual->nombre);
            gotoxy(47,17);printf(CYAN_T"Edad:       "RESET_COLOR"%d", actual->edad);
            gotoxy(47,19);printf(CYAN_T"Carrera:    "RESET_COLOR"%s", actual->carrera);
            gotoxy(47,21);printf(CYAN_T"Semestre:   "RESET_COLOR"%d", actual->semestre);
            return;
        }
        actual = actual->siguiente;

    }
    gotoxy(43,26);printf(ROJO_T"Alumno no encontrado."RESET_COLOR);
}

struct Alumno *ordenar(struct Alumno *p){
	struct Alumno *q,*pa,*aux;
	int band;
	void mostrarLista();
	q=p;
	if(q!=NULL){
		mostrarLista();
		sleep(1);
		do{	
			band=0;
			q=p;
			pa=q->siguiente;
			
			while(pa!=NULL){
				if(q->matricula > pa->matricula){
					aux->matricula= q->matricula;
					strcpy(aux->carrera,q->carrera);
					strcpy(aux->nombre,q->nombre);
					aux->edad=q->edad;
					aux->semestre=q->semestre;
					strcpy(q->carrera,pa->carrera);
					strcpy(q->nombre,pa->nombre);
					q->edad=pa->edad;
					q->matricula=pa->matricula;
					q->semestre=pa->semestre;
					strcpy(pa->carrera,aux->carrera);
					strcpy(pa->nombre,aux->nombre);
					pa->edad=aux->edad;
					pa->semestre=aux->semestre;
					pa->matricula=aux->matricula;
					band=1;
				}
				q=pa;
				pa=q->siguiente;
			}
		}while(band!=0); 		
	}
	else{
		gotoxy(48,12);printf("No hay datos para modificar");
	}
	system("cls");
	margen();
	//margen(1,0,117,29);
	gotoxy(53,14);printf("Datos Ordenados\n");
	mostrarLista();
	system("pause");
}
//ELiminar un alumno
void eliminarAlumno() {
	void mostrarLista();
	int elige;
    if(lista_alumnos == NULL) {
        gotoxy(45,16);printf(ROJO_T"No hay alumnos registrados."RESET_COLOR);
        return;
    }
    if (lista_alumnos != NULL) {
            mostrarLista();
        }

    int matricula;
    gotoxy(30,10);printf(CYAN_T"Ingrese la matricula del alumno a eliminar: "RESET_COLOR);
    scanf("%d",&matricula);

    Alumno* actual = lista_alumnos;
    Alumno* anterior = NULL;

    while(actual != NULL) {
        if(actual->matricula==matricula) {
        	gotoxy(30,10);printf("                                                       ");
        	gotoxy(45,10);printf(MAGENTA_T"Datos del alumno a eliminar "RESET_COLOR);
            gotoxy(47,12);printf(CYAN_T"Matricula:"RESET_COLOR" %d", actual->matricula);
            gotoxy(47,14);printf(CYAN_T"Nombre: "RESET_COLOR"%s", actual->nombre);
            gotoxy(47,16);printf(CYAN_T"Edad: "RESET_COLOR"%d", actual->edad);
            gotoxy(47,18);printf(CYAN_T"Carrera: "RESET_COLOR"%s", actual->carrera);
            gotoxy(47,20);printf(CYAN_T"Semestre:"RESET_COLOR" %d", actual->semestre);
            gotoxy(33,27);system("pause");
            
            if(anterior == NULL) {
                lista_alumnos = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
             if (lista_alumnos != NULL) {
             	system("cls");
             	margen();
             	gotoxy(43,16);printf(VERDE_T"Alumno eliminado exitosamente."RESET_COLOR);
           		 mostrarLista();
           		 sleep(3);
        	}
            	return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    gotoxy(43,26);printf(ROJO_T"Alumno no encontrado."RESET_COLOR);
}

//Encargado de modificar los datos de un alumno
void modificarAlumno() {
    void mostrarLista();
     if (lista_alumnos != NULL) {
            mostrarLista();
        }
    if (lista_alumnos == NULL) {
        gotoxy(43, 16);
        printf(ROJO_T"No hay alumnos registrados."RESET_COLOR);
        return;
    }

    gotoxy(43, 7);
    printf(ROJO_T"* La matricula no se modifica"RESET_COLOR);

    int matricula;
    gotoxy(30, 10);
    printf(CYAN_T"Ingrese la matricula del alumno a modificar: "RESET_COLOR);
    scanf("%d", &matricula);
    gotoxy(30, 10);
    printf("                                                   ");

    Alumno *actual = lista_alumnos;

    while (actual != NULL) {
        int opcion;
        if (actual->matricula == matricula) {
            do {
                gotoxy(22, 10);
                printf(VERDE_T"Datos actuales:"RESET_COLOR);
                gotoxy(22, 12);
                printf(CYAN_T"Matricula: "RESET_COLOR"%d", actual->matricula);
                gotoxy(22, 14);
                printf(CYAN_T"Nombre: "RESET_COLOR"%s", actual->nombre);
                gotoxy(22, 16);
                printf(CYAN_T"Edad: "RESET_COLOR"%d", actual->edad);
                gotoxy(22, 18);
                printf(CYAN_T"Carrera: "RESET_COLOR"%s", actual->carrera);
                gotoxy(22, 20);
                printf(CYAN_T"Semestre:"RESET_COLOR" %d", actual->semestre);
                do {
                    gotoxy(63, 22);
                    printf("  ");
                    gotoxy(55, 10);
                    printf(VERDE_T"Datos a modificar: "RESET_COLOR);
                    gotoxy(55, 12);
                    printf(CYAN_T"1.Nombre: ");
                    gotoxy(55, 14);
                    printf(CYAN_T"2.Edad: ");
                    gotoxy(55, 16);
                    printf(CYAN_T"3.Carrera: ");
                    gotoxy(55, 18);
                    printf(CYAN_T"4.Semestre: ");
                    gotoxy(55, 20);
                    printf(CYAN_T"5.Salir "RESET_COLOR);
                    gotoxy(55, 22);
                    printf(CYAN_T"Opcion: "RESET_COLOR);
                    gotoxy(63, 22);
                    scanf("%d", &opcion);

                    switch (opcion) {
                        case 1:
                            gotoxy(65, 12);
                            scanf("%s", actual->nombre);
                            break;
                        case 2:
                            gotoxy(65, 14);
                            scanf("%d", &(actual->edad));
                            break;
                        case 3:
                            gotoxy(67, 16);
                            scanf(" %s", actual->carrera);
                            break;
                        case 4:
                            gotoxy(65, 18);
                            scanf("%d", &(actual->semestre));
                            break;
                        case 5:
                            break;  // Salir del bucle
                        default:
                            gotoxy(55, 24);
                            printf(ROJO_T"Opción no válida. Intente nuevamente."RESET_COLOR);
                            break;
                    }
                } while (opcion != 5);
                if (lista_alumnos != NULL) {
                    system("cls");
                    margen();
                    gotoxy(35, 26);
                    printf(VERDE_T"Datos del alumno modificados exitosamente."RESET_COLOR);
                    mostrarLista();
                    sleep(3);
                }
                return;
            } while (opcion != 5);
        }

        actual = actual->siguiente;
    }

    gotoxy(43, 16);
    printf(ROJO_T"Alumno no encontrado."RESET_COLOR);
}

//Almacenar la información en archivos
struct Alumno *guardar(struct Alumno *p){
	FILE * flujo = fopen("alumnos.txt", "w+");
	if(flujo == NULL){
		perror("Error en la creacion del Archivo\n");
	}else{
		while(p!=NULL){
			fprintf(flujo,"%d",p->matricula);
			fputc('\n',flujo);
			fputs(p->nombre,flujo);
			fputc('\n',flujo);
			fprintf(flujo,"%d",p->edad);
			fputc('\n',flujo);
			fprintf(flujo,"%s",p->carrera);
			fputc('\n',flujo);
			fprintf(flujo,"%d",p->semestre);
			fputc('\n',flujo);
			p=p->siguiente;
		}

	}
	fflush(flujo);
	fclose(flujo);	
}

// Método encargado de comprobar si existe la matricula en el archivo de texto
int matriculaExisteEnArchivo(int matricula) {
    FILE *archivo;
    archivo = fopen(rutaArchivo, "r");
    if (archivo == NULL) {
        //printf("No se pudo abrir el archivo para lectura.\n");
        return 0; 
    }
    int matriculaArchivo;
    while (fscanf(archivo, "%d", &matriculaArchivo) == 1) {
        if (matriculaArchivo == matricula) {
            fclose(archivo);
            return 1;
        }
        fscanf(archivo, "%*[^\n]");
    }
    fclose(archivo);
    return 0;
}

//metodo encargado de guardar los alumnos en el archivo de texto 
void guardarAlumnosArchivosTxt(){
	FILE *archivo;
    Alumno *actual = lista_alumnos;
    archivo = fopen(rutaArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    while (actual != NULL) {
        fprintf(archivo, "%d %s %d %s %d\n",
                actual->matricula, actual->nombre, actual->edad,
                actual->carrera, actual->semestre);

        actual = actual->siguiente;
    }
    fclose(archivo);
    gotoxy(23,9);printf("Alumnos guardados en el archivo alumnos.txt.\n");
}

//metodo encargado de leer los alumnos desde el archivo de texto
void cargarAlumnosDesdeArchivo() {
    FILE *archivo;
    archivo = fopen(rutaArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }
    while (!feof(archivo)) {
        Alumno* nuevo_alumno = (Alumno*)malloc(sizeof(Alumno));

        if (fscanf(archivo, "%d %s %d %s %d", &(nuevo_alumno->matricula),
                   nuevo_alumno->nombre, &(nuevo_alumno->edad),
                   nuevo_alumno->carrera, &(nuevo_alumno->semestre)) != 5) {
            free(nuevo_alumno);  // Liberar memoria si no se leyeron todos los campos
            break;
        }

        nuevo_alumno->siguiente = NULL;

        if (lista_alumnos == NULL) {
            lista_alumnos = nuevo_alumno;
        } else {
            Alumno* actual = lista_alumnos;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo_alumno;
        }
    }
    fclose(archivo);
    gotoxy(23,9);printf("Alumnos cargados desde el archivo.\n");
}
void liberarMemoria() {
    Alumno* actual = lista_alumnos;

    while(actual != NULL) {
        Alumno* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}
//Mostrar la lista
void mostrarLista() {
	int i=0;
	int j=-1;
	int k=-1;
    Alumno* actual = lista_alumnos;
    
    while(actual != NULL) {
    	gotoxy(24+(j*12),23);printf(" ");
        
        gotoxy(17+(i*12),24);printf("%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196);
        gotoxy(17+(i*12),22);printf("%c%c%c%c%c%c%c%c",196,196,196,196,196,196,196,196);
        gotoxy(16+(i*12),23);printf("%c",179);
        gotoxy(16+(i*12),22);printf("%c",218);
        gotoxy(25+(i*12),22);printf("%c",191);
        gotoxy(25+(i*12),24);printf("%c",217);
        gotoxy(22+(i*12),22);printf("%c",194);
        gotoxy(16+(i*12),24);printf("%c",192);
        gotoxy(22+(i*12),24);printf("%c",193);
        gotoxy(18+(i*12),23);printf("%d     ", actual->matricula);
        gotoxy(22+(i*12),23);printf("%c",179);
        gotoxy(25+(i*12),23);printf("%c",179);
        if (k>=0)
		{
			gotoxy(24+(k*12),21);printf("%c",218);
        	gotoxy(24+(k*12),22);printf("%c",193);
        	gotoxy(25+(k*12),21);printf("%c%c%c%c%c%c%c",196,196,196,196,196,196,196);
        	gotoxy(32+(k*12),21);printf("%c",191);
        	gotoxy(32+(k*12),22);printf("%c",193);        	
        	
		}
        gotoxy(24+(i*12),23);printf("/");
        actual = actual->siguiente;
        i++; 
        j++;
        k++;
    }
}

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
