#include "AprendizajeQ.hpp"
#include "Arbotix.hpp"

/*
 * Aprendizaje por Reforzamiento
 * Las recompensas se definen de [0-1]
 * Los Castigos se defien de [0-1]
 * Las Acciones se definen de la siguiente manera:
 * a0 = caminar poco
 * a1 = caminar
 * a2 = caminar mucho
 * a3 = girar derecha
 * a4 = girar izquierda
 * a5 = girar poco derecha
 * a6 = girar poco izquierda
 */

#define K 3
#define Y 0.1
#define NUM_ESTADOS 19
#define NUM_ACCION 7
#define PRECISION 4


namespace AprendizajeQ {

  // estado anterior	
  int estadoViejo = 0 ; // por defecto
  // accion anterior es -1 si es la primera vez
  int accion = -1;	
  float Q[NUM_ESTADOS][NUM_ACCION];
	
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

    std::ifstream entrada;
    entrada.open("tabla.txt", std::ios_base::binary);
    std::string linea;
    char* separar = NULL;

    for (int j = 0 ; j < NUM_ESTADOS; j++){
    
      getline(entrada, linea);

      char aux[linea.length() + 1];
      strcpy(aux, linea.c_str());
	   
      separar = strtok(aux, " ");

      for (int i = 0 ; i < NUM_ACCION  ; i++)
	{	 

	  if(separar!= NULL){
	    Q[j][i] = atof(separar);
	  }

	  //  printf ("es cosa de impresion??%f" , Q[j][i] );
  	 
	  separar = strtok (NULL, " ");
		 
	}
	  
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
	
  void escribirValores(){
    std::string linea;
		
    std::ofstream salida ;
    salida.open("tabla.txt", std::ios_base::binary);
    if (salida.is_open())
      {
	
			
	for (int i = 0 ; i < NUM_ESTADOS; i++){
	  for (int j = 0 ; j < NUM_ACCION ; j++ )
	    salida << std::fixed << std::setprecision(PRECISION)
		   << Q[i][j] << " ";
	
	  salida << std::endl;
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
    float y = Y;
    
    //std::cout << "Valor y= " << y << std::endl;
    if (accion != -1)
      Q[estadoViejo][accion] = recompensa(estadoViejo, estado) + y*maxQ(estado);

    //std::cout << "Y*maxQ("<<estado<<")= "<< Y*maxQ(estado);
    std::cout << "Q["<<estadoViejo<<"]["<<accion<<"]: " 
	      << Q[estadoViejo][accion] << std::endl;
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
    // LA constante K debe variar si es < a 1 favorece a la exploracion
    // si es > 1 favorece la explotacion
    // si es = 1 todo queda igual
    float k = K;
    float probabilidad[NUM_ACCION];
    float suma = 0.0 ;

    for (int i = 0; i < NUM_ACCION; i++)
      suma += pow(k , Q[estado][i]); 
    //std::cout << "Hizo suma " << suma << std::endl;

    std::cout << "probabilidades [ " ;
    for(int i = 0 ; i < NUM_ACCION; i++){
      probabilidad[i] = (pow(k , Q[estado][i]))/suma;
      std::cout << probabilidad[i] << ", " ;
    }
    std::cout << " ]" << std::endl;
	
    srand(time(NULL));

    float aleatorio = 0.0; 
    aleatorio = (float ) rand()/ (float) RAND_MAX ; // Entre [0,1]
    std::cout << "Aleatorio: " << aleatorio << std::endl;
    
    float inf = 0;
    float sup = probabilidad[0];
    std::cout << "rangos : [" << inf << ", " << sup << "] " ;
    
    for(int i=0; i< NUM_ACCION; i++){
      if(inf<aleatorio<=sup){
	accion = i;
	std::cout << " " << accion << " " ;
	break;
      }
      
      inf= sup;
      sup= inf + probabilidad[i+1];
      std::cout << "[" << inf << ", " << sup << "] " ;
    }
    std::cout << std::endl;
    /*
    //Max de aux
    float max = 0;		
    for(int i = 0; i < NUM_ACCION; i++ ){
      if (probabilidad[i] > max){
	max = probabilidad[i];
	accion = i;
      }
    }  
    */
    
    std::cout << "En el estado " << estado << std::endl;
    std::cout << "Hizo elegir accion " << accion << std::endl;

    estadoViejo = estado;
    
    // Enviar peticion a la Arbotix con la acción  
    char peticion[2];
    sprintf(peticion,"%d",accion);
    Arbotix::peticion(peticion);

    	
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

  float recompensa(int estadoViejo , int estadoNuevo){
    float R;
    float dV = distancia(estadoViejo);
    float dN = distancia(estadoNuevo);
    R = (dV - dN)/10;
    std::cout << "recompensa fue:" << R << std::endl;
    return R;
  }

  /*
   * @Descripcion: Otorga el maximo VALUE de las accion segun un estado
   * @Parametros: estado: estadoActual 
   * @Retorno: max: maximo VALUE de un estado
   *
   */
	
  float maxQ(int estado){
    float max = 0 ; 
    for(int i = 0; i < NUM_ACCION; i++ ){
      if (Q[estado][i] > max)
	max = Q[estado][i];
    }
    std::cout << "maxQ("<<estado<<"): "<<max << std::endl;
    return max;
  }

  /*
   * @Descripcion: Asigna una distancia segun el estado actual
   * la asignacion viene dada por :
   * e0 , e1 = 1
   * e2 = 2
   * e3 , e4 = 3 
   * e5 = 6
   * e6 = 8
   * e7 , e8 = 9
   * e9 , e10, e13 = 10
   * e11 , e12 = 7
   * 
   * @Parametros: estado: estado actual
   */
	
  float distancia (int estado){
    switch (estado){
    case 0: 
    case 1:
      return 1.0;
      break;
    case 2:
      return 2.0;
      break;
    case 3:
    case 4:
    case 5:
      return 3.0;
      break;
    case 6:
      return 5.0;
      break;
    case 7:
      return 6.0;
      break;
    case 8:
    case 9:
    case 15:
    case 17:
      return 8.0;
      break;
    case 18:
    case 11:
    case 13:
      return 10.0;
      break;
    case 10:
    case 12:
      return 9.0;
      break;
    case 14:
    case 16:
      return 7.0;
      break;
    } 
  }
  
}
