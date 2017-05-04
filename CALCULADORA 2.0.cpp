#include <cstdlib>
#include <iostream>
#include <sstream>

#include <fstream>
//estamos vivo!
//Cambio hecho
using namespace std;
class Token{
    private: 
        char dato;
        Token *next;
    public:
        Token() {next=NULL;};
        Token(char a) {dato=a; next=NULL;};
        void set_dato(char a) {dato=a; };
        void set_next(Token *n) {next=n; };
        char get_dato() {return dato; };
        Token *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
                      
                            
};
//----------------------------------------------------------------------------------------------------------
class ListaTokens{
    private: Token *czo;
    public:
            ListaTokens() {czo=new Token();};
            ListaTokens(Token *n) {czo=n;};
            //~ListaTokens(void);
            void add(int d);
            bool esvacia(void);
            int cabeza(void);
            ListaTokens *resto(void);
            string toPrint(string p);   
           
            void impre(void);
            
            int size();
            void borrar(void); //borra la cabeza
            void borrar_last();//borra el ultimo
           
           
            void del(void);
            int last();
          
            
            
           
};//                      2      0

      
  //se mueve hasta el ultimo elemento y lo muestra   
int ListaTokens::last(){ //
     if(!this->esvacia()){//si la lista no esta vacia entro
        if( this->resto()->esvacia() )//pregunta si el siguiente es vacia, si lo es devuelve cabeza
            return this->cabeza();
       return this->resto()->last();
     }
     return 0;
}

int ListaTokens::size()
{ 
     if (this->esvacia()) return 0;
     return 1+this->resto()->size();
}
void ListaTokens::impre(void)
{ Token *aux;
  aux=czo;
    while(aux->get_next()!=NULL){
         cout<<aux->get_dato()<<endl;
         aux=aux->get_next();
    }
}

void ListaTokens::add(int d)
{    if(d==43)
         d=-1;
     if(d==42)
         d=-2;   
     if(d==45)
         d=-3;  
      if(d==47)
         d=-4;        
     Token *nuevo=new Token(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool ListaTokens::esvacia(void)
{   
    return czo->es_vacio();
}
int ListaTokens::cabeza(void)
{ 
  if(this->esvacia()){
                cout<<" Error, Cabeza de ListaTokens vacia";
                return -1; 
  }
  return czo->get_dato();
}

ListaTokens *ListaTokens::resto(void)
{ //devuelve el resto menos la cabeza
      ListaTokens *l=new ListaTokens(czo->get_next());//czo->get_next() se mueve un paso
      return (l);
}

string ListaTokens::toPrint(string p)
{ 
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()<<" - "<< this->resto()->toPrint(p) << endl;
      //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
       return stm.str();
     }
}

void ListaTokens::borrar(void)
{ //borra el Token cabeza
  if(esvacia()){
  } else {
         Token *tmp=czo;
         czo=czo->get_next();
         delete tmp;
  }
}
void ListaTokens::borrar_last()
{ // borra el ultimo Token
   if(!this->esvacia()){
      if((czo->get_next())->get_next()==NULL){
         delete czo->get_next();
         czo->set_next(NULL);
      }
      else this->resto()->borrar_last(); 
   }  
}




//----------------------------------------------------------------------------------------------
class Pila:public ListaTokens{
      public:
             Pila(){ListaTokens();};
             void apilar(int x){ add( x ); };
             int tope(void){return cabeza();};
             void desapilar(void){del();};
             bool pilavacia(){return esvacia();};
             int apila2(ListaTokens *l,Pila *p);
             void cal(Pila *p);
             int sizep(){return size();};
};                  


void ListaTokens::del(void)
{    Token *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
/**
*toma una lista y una pila y retorna el tope resultado de la pila final
*
 */       
 int Pila::apila2(ListaTokens *l,Pila *p){
      bool ban=true;
      while(ban){
         if(l->last()==40){
           Pila *nuevaPila=new Pila();
           l->borrar_last();
           p->apilar(apila2(l,nuevaPila));
         
         }   
 //si el tamaño de la pila es igual a 3, llamamos cal(p)         
         if(p->sizep()==3)
            this->cal(p);
 // si es distinto de un parentesis cerrado y si la lista es distinto de vacio     
         if( !(l->last()==41)&& (l->size()!=0 )){
             p->apilar(l->last());
             l->borrar_last();
            
         }
         else {
             //verifica si el elemento siguiente es vacio, cambia ban=false, entonces termina el while y retorna p->tope()  
              if(l->last()==0)
                 ban=false;
              else { 
    //si tenemos elementos, borrar el actual y sigue                
                  l->borrar_last();
                   
                   } 
              }                      
                 
      }
     
    return p->tope();
  }
//recibe una pila que tiene tres elemento, desapila y devuelve el resultado apilado   
void Pila::cal(Pila *p){
    int A; int B; int C; int R=0;
  
   C= p->tope(); p->desapilar();
 
   B= p->tope();p->desapilar();
 
   A= p->tope();p->desapilar();
    
     if(B==-1)
      R= A+C;
     if(B==-2)
      R= A*C;
     if(B==-3)
      R=A-C;
      
     if(B==-4)
      { if(C!=0)
        R=A/C;
        else
           cout<<"error, no existe division por 0"<<endl;
           
        }
    p->apilar(R);
  
    }

//--------------------------------------------------------------------
int main()
{
    ListaTokens *l=new ListaTokens();
    Pila *p=new Pila();
 bool bandera=true;
 
std::string elemento ="";
 printf("Por Favor ingrese elemento: \n");  
 cin>> elemento;
 
 
 for(int i=0; i<elemento.length(); i++)
 {
 	
    char c=elemento.at(i);
 	int d=c-48;
 	
 	if(elemento.at(i)>=0/* || elemento.at(i)==43*/){
 	
 	
 	
 	if (elemento.at(i)==43||elemento.at(i)==45 || elemento.at(i)== 42 || elemento.at(i) == 47 || elemento.at(i)==40 || elemento.at(i) == 41 )
    	l->add(elemento.at(i)); 
    	else 
    		l->add(d);
    	
 }
 }

 int c=p->apila2(l,p);
  cout<<" Resultado= "<<c<<endl;
      system("PAUSE");
    return EXIT_SUCCESS;
    
}
