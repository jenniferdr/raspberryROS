
namespace AprendizajeQ {

  void leerValores(){

    std::ifstream entrada("tabla.txt");
    string linea;
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
	  }
    }
  }
  
  void actualizarValor(int estado){
    if (accion != -1)
      Q[estadoViejo][accion] = recompensa(estadoViejo, estado) + maxQ(estado);
  }

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

    // VERIFICAR SI ES ASI DE VERDAD
    Arbotix::peticion("i");  
    
  }

  int recompensa(int estadoViejo , int estadoNuevo){
    int R;
    int dV = distancia(estadoViejo);
    int dN = distancia(estadoNuevo);
    if (dV < dN)
      // Castigo
      R = -(dN/10);
    else
      // Premio
      R = 1/ dN;
  }
  int maxQ(int estado){
    int max = 0 ;
    for(int i = 0; i < NUM_ACCION; i++ ){
      if (Q[estado][i] > max)
	max = Q[estado][i];
    }
    return max;
  }
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
