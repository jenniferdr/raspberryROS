#include "AprendizajeQ.hpp"

//#include "Arbotix.hpp"

namespace AprendizajeQ {

  // estado anterior	
	int estadoViejo = 0 ; // por defecto
  // accion anterior es -1 si es la primera vez
  int accion = -1;
	
	int Q[NUM_ESTADOS][NUM_ACCION];

  /*
   * @Descripcion: Funcion que lee del archivo tabla.txt los valores Aprendidos
   * @Parametros: Ninguno 
   * Formato del Archivo:
   * a0 a1 a2 a3 a4 a5 a6 [ e1 ]
   * a0 a1 a2 a3 ...      [ e2 ]
   * .
   * .
   * .
   * Matriz : Q[14][7]
   */
  void leerValores(){
	
    std::ifstream entrada("tabla.txt");
	
	std::string linea;
    char* separar = NULL;
	
    for (int j = 0 ; j < NUM_ESTADOS; j++){
    
      getline(entrada, linea);
	  
      char* aux = new char[linea.length() + 1];
      strcpy(aux, linea.c_str());
	  
	  separar = strtok(aux, " ");

      for (int i = 0 ; i < NUM_ACCION  ; i++)
	  {
		  
		  Q[j][i]= atof(separar);
		  
		  separar = strtok (NULL, " ");
		  std:: cout << "separar" << separar<< std::endl;	  				
	  }
	  std:: cout << "por aqui" << j << std::endl;	  				
    }
  }

	
  /*
   * @Descripcion: Funcion que escribe en el archivo salida.txt los
   * valores Aprendidos
   * @Parametros: Ninguno 
   * Formato del Archivo:
   * a0 a1 a2 a3 a4 a5 a6 [ e1 ]
   * a0 a1 a2 a3 ...      [ e2 ]
   * .
   * .
   * .
   * Matriz : Q[14][7]
   */
	
  void escribirValores(void){
    std::string linea;
    std::ifstream salida ("salida.txt");
    if (salida.is_open())
      {
	for (int i = 0 ; i < NUM_ESTADOS; i++){
	  //for (int j = 0 ; j < NUM_ACCION ; j++ )
	  //	salida << Q[i][j] ;
	  //salida << std::endl;
				
	}
			
	salida.close();
      }
    else std::cout << "No abri el archivo ";
  }

  /*
   * @Descripcion: Actualiza el estado anterior con el nuevo VALUE que posee en
   * la tabla Q-learning
   * @Parametros: estado: estado actual 
   */
  void actualizarValor(int estado){
    if (accion != -1)
      Q[estadoViejo][accion] = recompensa(estadoViejo, estado) + maxQ(estado);
  }
  /*
   * @Descripcion: Dada la funcion de probabilidad
   * P(ai/s) = (k ^ Q(ai,s))/ sum,j(k ^ Q(aj,s) ) se elige la accion 
   * para equilibrar la explotacion y exploracion. Ademas se envia la peticion 
   * al servidor de servicios en la Arbotix
   * @Parametros: estado: estado actual
   *
   */
  void tomarAccion(int estado){
    int k = K;
    int aux[NUM_ACCION];
    int suma;
		
    for (int i = 0; i < NUM_ACCION; i++)
      suma += pow(k , Q[estado][i]); 
		
    for(int i = 0 ; i < NUM_ACCION; i++)
      aux[i] = (pow(k , Q[estado][i]))/suma;
		
    int max = 0;
		
    for(int i = 0; i < NUM_ACCION; i++ ){
      if (aux[i] > max)
	max = aux[i];
      accion = i;
    }
    estadoViejo = estado;
    //std::string peticion = std::to_string(accion);
    // VERIFICAR SI ES ASI DE VERDAD
    //		Arbotix::peticion(peticion);  
		
  }
  /*
   * @Descripcion: Dado el estado anterior y el actual se otorga un recompensa
   * que se define por la siguiente relacion:
   * Zonas de la camara [1 - 10] valores descritos en "Funcion distancia" 
   * Castigo : - (distanciaEstadoNuevo / 10) , maximo castigo = -1 
   * Premio : 1 / distanciaEstadoNuevo,  maximo premio = 1
   * @Parametros: estadoViejo: Estado anterior 
   *              estadoNuevo: Estado Actual  
   */
  double recompensa(int estadoViejo , int estadoNuevo){
    double R;
    int dV = distancia(estadoViejo);
    int dN = distancia(estadoNuevo);
    if (dV < dN)
      // Castigo
      R = -( dN/10);
    else
      // Premio
		R = 1/dN;
    return R;
  }

  /*
   * @Descripcion: Otorga el maximo VALUE de las accion segun un estado
   * @Parametros: estado: estadoActual 
   * @Retorno: max: maximo VALUE de un estado
   *
   */
	
  int maxQ(int estado){
    int max = 0 ; 
    for(int i = 0; i < NUM_ACCION; i++ ){
      if (Q[estado][i] > max)
	max = Q[estado][i];
    }
    return max;
  }

	/*
	 * @Descripcion: Asigna una distancia segun el estado actual
	 * la asignacion viene dada por :
	 * e1 , e2 = 1
	 * e3 = 2
	 * e4 , e5 = 3 
	 * e6 = 6
	 * e7 = 8
	 * e8 , e9 = 9
	 * e10 , e11 = 10
	 * e12 , e13 = 7
	 * @Parametros: estado: estado actual
	 */
	
  int distancia (int estado){
    switch (estado){
    case 1:
    case 2:
      return 1;
      break;
    case 3:
      return 2;
      break;
    case 4:
    case 5:
      return 3;
      break;
    case 6:
      return 6;
      break;
    case 7:
      return 8;
      break;
    case 8:
    case 9:
      return 9;
      break;
    case 10:
    case 11:
      return 10;
      break;
    case 12:
    case 13:
      return 7;
      break;
    } 
  }
	
}
