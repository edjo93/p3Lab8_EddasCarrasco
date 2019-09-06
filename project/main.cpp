#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include<string>
using namespace std;

void listar();
void modificar();
void agregarAlumno();
void eliminar();

sqlite3 *conn;
sqlite3_stmt *res;
int error=0;
int rec_count =0;
const char *tail;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//agregarAlumno();
	//modificar();
	//listar();
	eliminar();
	system("pause");
	return 0;
}


void listar(){
	error=sqlite3_open("base1.db",&conn);
	error=sqlite3_prepare_v2(conn,
	        "select * from alumnos",1000,&res,&tail);
	while(sqlite3_step(res) == SQLITE_ROW){
		cout<<sqlite3_column_text(res,0)<<endl;
		cout<<sqlite3_column_text(res,1)<<endl;
		cout<<sqlite3_column_text(res,2)<<endl;
		cout<<"------"<<endl;
	}	
	sqlite3_close(conn);	
}


void agregarAlumno(){
	string query;
	string nombre;
	string carrera;
	string cuanta;
	error=sqlite3_open("base1.db",&conn);
	
	cout<<"\nadd alumno / query: ";
	
	cout<<"\ncuenta: ";
	getline(cin,cuanta);
	
	cout<<"\nnombre del alumno: ";
	getline(cin,nombre);
	
	cout<<"\ncarrera: ";
	getline(cin,carrera);
	
	query="insert into alumnos values('"+cuanta+"','"+nombre+"','"+carrera+"')";
	error=sqlite3_exec(conn,query.c_str(),0,0,0);
	sqlite3_close(conn);
}
		
		
void modificar(){
	error=sqlite3_open("base1.db",&conn);
	error=sqlite3_exec(conn,
	"update alumnos set nombre='Pedro' where cuanta='122'"
	,0,0,0);
	sqlite3_close(conn);
}		

		
void eliminar()	{//elimina datos null
	error=sqlite3_open("base1.db",&conn);
	error=sqlite3_exec(conn,"delete from alumnos where cuanta='344'",0,0,0);
	sqlite3_close(conn);	
}
