#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
#include<string>

using namespace std;

void listar();
void modificar();
void addDepartamento();
void eliminar();
void listarDepartamento();
void listarEmpleados();
void jefeEmpleados(string);
void depto(string);
void addEmpleado();
sqlite3 *conn;
sqlite3_stmt *res;
int error=0;
int rec_count =0;
const char *tail;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	char opcion;
	char opcion2;
	char opcion3;
	string dpto;
	string empno;
	do{
		cout<<"\n1-listar\n2-agregar\n3-eliminar\n4-listar jefe y empleado\n5-actualizar salario de empleados\n6-empleados de departamento\ns-salir\n?:";
		cin>>opcion;
		switch(opcion){
			case'1':
				do{
					cout<<"\n1-deptnos\n2-empleados\n3-regresar\n?:";
					cin>>opcion3;
					switch(opcion3){
						case'1':
							//listar departamento
							cout<<"\n---listar departamento--"<<endl;
							listarDepartamento();
							break;
						case'2':
							//listar empleados
							cout<<"\n---listar empleados--"<<endl;
							listarEmpleados();
							break;
						case'3':
							break;
						default:
							cout<<"\nno se ingreso una opcion correcta\n";	
								
					}
				}while(opcion3!='3');
				break;
			case'2':
				do{
					cout<<"\n1-deptno\n2-empleado\n3-regresar\n?:";
					cin>>opcion2;
					switch(opcion2){
						case'1':
							//add departamento
							cout<<"\n---add departamento--"<<endl;
							addDepartamento();
							break;
						case'2':
							//add empleados
							addEmpleado();
							break;
						case'3':
							break;
						default:
							cout<<"\nno se ingreso una opcion correcta\n";	
								
					}
				}while(opcion2!='3');
				
				break;
			case'3':
				eliminar();
				break;
			case'4':
				cout<<"\nempno: ";
				cin>>empno;
				jefeEmpleados(empno);
				break;
			case'5':
				cout<<"\nempno: ";
				cin>>empno;
				
				break;			
			case'6':
				cout<<"ndpto: ";
				cin>>dpto;
				depto(dpto);
				break;	
			case's':
				cout<<"\nhasta luego\n";
				break;	
			default:
				cout<<"\nno se ingreso una opcion correcta\n";
		}
		
	}while(opcion!='s');
	return 0;
}


void listarDepartamento(){
	error=sqlite3_open("oracle-sample.db",&conn);
	error=sqlite3_prepare_v2(conn,
	        "select * from dept",1000,&res,&tail);
	if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}	        
	while(sqlite3_step(res) == SQLITE_ROW){
		cout<<"deptno: "<<sqlite3_column_text(res,0)<<endl;
		cout<<"dname: "<<sqlite3_column_text(res,1)<<endl;
		cout<<"loc: "<<sqlite3_column_text(res,2)<<endl;
		cout<<endl<<endl<<endl;
	}	
	sqlite3_close(conn);	
}

void listarEmpleados(){
	error=sqlite3_open("oracle-sample.db",&conn);
	error=sqlite3_prepare_v2(conn,
	        "select * from emp",1000,&res,&tail);
    if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	while(sqlite3_step(res) == SQLITE_ROW){
		cout<<"emptno: "<<sqlite3_column_text(res,0)<<endl;
		cout<<"ename: "<<sqlite3_column_text(res,1)<<endl;
		cout<<"job: "<<sqlite3_column_text(res,2)<<endl;
		cout<<"mgr: "<<sqlite3_column_text(res,3)<<endl;
		cout<<"hiredate: "<<sqlite3_column_text(res,4)<<endl;
		cout<<"sal: "<<sqlite3_column_text(res,5)<<endl;
		cout<<"comm: "<<sqlite3_column_text(res,6)<<endl;
		cout<<"deptno: "<<sqlite3_column_text(res,7)<<endl;
		cout<<endl<<endl<<endl;
	}	
	sqlite3_close(conn);	
}
void addDepartamento(){
	string query;
	string deptno;
	string dname;
	string loc;
	error=sqlite3_open("oracle-sample.db",&conn);
	cin.ignore(100,'\n');
	cout<<"\ndeptno: ";
	getline(cin,deptno);
	
	cout<<"\nnombre del departamento: ";
	getline(cin,dname);
	
	cout<<"\nlocation: ";
	getline(cin,loc);
	
	query="insert into dept values('"+deptno+"','"+dname+"','"+loc+"')";
	error=sqlite3_exec(conn,query.c_str(),0,0,0);
	if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	
	sqlite3_close(conn);
}
		
void addEmpleado(){
	string query;
	string s1;
	string s2;
	string s3;
	string s4;
	string s5;
	string s6;
	string s7;
	string s8;//disculpa las variables no tenia tiempo
	error=sqlite3_open("oracle-sample.db",&conn);
	cin.ignore(100,'\n');
	cout<<"\nemptno: ";
	getline(cin,s1);
	cout<<"\nename: ";
	getline(cin,s2);
	cout<<"\njob: ";
	getline(cin,s3);
	cout<<"\nmgr: ";
	getline(cin,s4);
	cout<<"\nhiredate: ";
	getline(cin,s5);
	cout<<"\nsalario: ";
	getline(cin,s6);
	cout<<"comm: ";
	getline(cin,s7);
	cout<<"dptno: ";
	getline(cin,s8);
	query="insert into emp values('"+s1+"','"+s2+"','"+s3+"','"+s4+"','"+s5+"','"+s6+"','"+s7+"','"+s8+"')";
	error=sqlite3_exec(conn,query.c_str(),0,0,0);
	if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	
	sqlite3_close(conn);
}		
void modificar(){
	error=sqlite3_open("base1.db",&conn);
	error=sqlite3_exec(conn,
	"update alumnos set nombre='Pedro' where cuanta='122'"
	,0,0,0);
	sqlite3_close(conn);
}		

		
void eliminar()	{//elimina datos
	cout<<"---eliminar empleados---"<<endl;
	string empno;
	cin.ignore(100,'\n');
	cout<<"\nempno: ";
	getline(cin,empno);
	error=sqlite3_open("oracle-sample.db",&conn);
	string query="delete from emp where empno='"+empno+"'";
	error=sqlite3_exec(conn,query.c_str(),0,0,0);
	if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	sqlite3_close(conn);	
}
/*
void jefeEmpleados(string empno){
	string jefe=;
	string query=;
	error=sqlite3_open("oracle-sample.db",&conn);
	query="select mgr from emp where empno='"+empno+"'";
	error=sqlite3_prepare_v2(conn,query.c_str(),1000,&res,&tail);
	if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
		return;
	}
	jefe=(char*)sqlite3_column_text(res,0);
	cout<<"jefe: "<<jefe;
	sqlite3_close(conn);        
}
*/
void jefeEmpleados(string empno){
	string query;
	string jefe;
	error=sqlite3_open("oracle-sample.db",&conn);
	query="select mgr from emp where empno='"+empno+"'";
	error=sqlite3_prepare_v2(conn,query.c_str(),query.length()+1,&res,&tail);
    if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	if(sqlite3_step(res) == SQLITE_ROW){
		cout<<"jefe: "<<sqlite3_column_text(res,0)<<endl;
		jefe=(char*)sqlite3_column_text(res,0);
		cout<<"\n--empleados de ese jefe-- "<<endl;
		query="select ename from emp where mgr='"+jefe+"'";
		error=sqlite3_prepare_v2(conn,query.c_str(),query.length()+1,&res,&tail);
		if(error!=SQLITE_OK){
			cout<<"\nsomething wrong /check query\n";
		}
		while(sqlite3_step(res) == SQLITE_ROW){
			cout<<sqlite3_column_text(res,0)<<endl;
		}
		
	}else{
		cout<<"no hay empleado";
	}	
	sqlite3_close(conn);
}
void depto(string ndepa){
	string query;
	error=sqlite3_open("oracle-sample.db",&conn);
	query="select dname from dept where deptno='"+ndepa+"'";
	error=sqlite3_prepare_v2(conn,query.c_str(),query.length()+1,&res,&tail);
    if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	cout<<"\n---nombre departamento--"<<endl;
	while(sqlite3_step(res) == SQLITE_ROW){
		cout<<sqlite3_column_text(res,0)<<endl;
	}
	cout<<"\n--empleados de ese departamento---"<<endl;
	query="select ename from emp where deptno='"+ndepa+"'";
	error=sqlite3_prepare_v2(conn,query.c_str(),query.length()+1,&res,&tail);
    if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	while(sqlite3_step(res) == SQLITE_ROW){
		cout<<sqlite3_column_text(res,0)<<endl;
	}
	cout<<"\n--salario total de todos los empleados---"<<endl;
	query="select sal from emp where deptno='"+ndepa+"'";
	error=sqlite3_prepare_v2(conn,query.c_str(),query.length()+1,&res,&tail);
    if(error!=SQLITE_OK){
		cout<<"\nsomething wrong /check query\n";
	}
	int sum=0;
	while(sqlite3_step(res) == SQLITE_ROW){
		sum+=atoi((char*)sqlite3_column_text(res,0));
	}
	cout<<"\nsum: "<<sum<<endl;
	sqlite3_close(conn);
	
}

void actualizarSalario(string empno){
	
}

