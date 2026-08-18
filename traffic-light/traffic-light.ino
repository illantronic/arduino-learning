//DECLARACION DE VARIABLES
int rojo = 6;
int amarillo = 5;
int verde = 4;
int modo = 0;



//VARIABLES MODO NORMAL
int faseNormal = 0;
unsigned long tiempoNormal = 0;



//VARIABLES MODO INTERMITENTE
bool estadoIntermitente = false;
unsigned long tiempoIntermitente = 0;


//FUNCION PARPADEAR LED SIN DELAY(PIN, MODO Y ESTADO, TIEMPO ANTERIOR)
void parpadear(int pin, bool &estado, unsigned long &tiempoAnterior) {

  //SI MIDE UN TIEMPO QUE ES MENOR A 500, NO CAMBIA ESTADO, SINO CAMBIA Y SE ACTUALIZA A EL VALOR ACTUAL
  //NO SE RESETEA A 0 PORQUE MILLIS NUNCA DEJA DE AVANZAR
  if (millis() - tiempoAnterior >= 500) {

    estado = !estado;

    digitalWrite(pin, estado);

    tiempoAnterior = millis();
  }
}


//FUNCION PARA MOSTRAR MENU PRINCIPAL
void mostrarMenu() {

  Serial.println("--------------------");
  Serial.println("Selecciona nuevo modo:");
  Serial.println("0 - Salir, Apagado");
  Serial.println("1 - Normal");
  Serial.println("2 - Amarillo intermitente");
  Serial.println("3 - Manual simple");
  Serial.println("4 - Manual complejo");
}


//FUNCION PARA MOSTRAR MENU MANUAL SIMPLE
void mostrarMenuManualSimple() {

  Serial.println("--------------------");
  Serial.println("MODO MANUAL SIMPLE");
  Serial.println("Selecciona una luz:");
  Serial.println("1 - Rojo");
  Serial.println("2 - Amarillo");
  Serial.println("3 - Verde");
  Serial.println("0 - Salir, Apagado");
  Serial.println("--------------------");
}


//FUNCION PARA MOSTRAR MENU MANUAL COMPLEJO
void mostrarMenuManualComplejo() {

  Serial.println("--------------------");
  Serial.println("MODO MANUAL COMPLEJO");
  Serial.println("Selecciona una opcion:");
  Serial.println("1 - Rojo fijo");
  Serial.println("2 - Amarillo fijo");
  Serial.println("3 - Verde fijo");
  Serial.println("4 - Parpadeo rojo");
  Serial.println("5 - Parpadeo amarillo");
  Serial.println("6 - Parpadeo verde");
  Serial.println("0 - Salir, Apagado");
  Serial.println("--------------------");
  Serial.println("EXTRA:");
  Serial.println("Pulsa otra vez el mismo modo para apagar.");
  Serial.println("Otro modo del mismo LED sustituye al anterior.");
  Serial.println("--------------------");
}


void setup() {

  //PONER LOS PINES EN MODO OUTPUT
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);

  //COMENZAR COMUNICACION CON EL ORDENADOR
  Serial.begin(9600);

  //MIENTRAS MODO SIGA EN 0(MODO POR DEFECTO)
  while (modo == 0) {

    Serial.println(" ");
    Serial.println("Selecciona el modo:");
    Serial.println("0 - Apagado");
    Serial.println("1 - Normal");
    Serial.println("2 - Amarillo intermitente");
    Serial.println("3 - Manual simple");
    Serial.println("4 - Manual complejo");


    //MIENTRAS NO RECIBA NINGUN CARACTER, PERMANECER APAGADO
    while (Serial.available() == 0) {

      digitalWrite(rojo, LOW);
      digitalWrite(amarillo, LOW);
      digitalWrite(verde, LOW);
    }

    //CUANDO RECIBA UN CARACTER, SALE DEL WHILE, Y LO LEE
    char entrada = Serial.read();


    //COMPROBAR VALOR INVALIDO CON CODIGO ASCII(MAS EFICIENTE PARA CASOS DE INTRODUCIR LETRAS)
    if (entrada < '0' || entrada > '4') {

      Serial.println("--------------------");
      Serial.println("Valor invalido.");
      Serial.println("--------------------");

      modo = 0;
    }
    //SI ES VALIDO, MODO ES LO QUE LEYO DEL SERIAL MONITOR
    else {

      //COMO USAMOS CODIGO ASCII, PARA TRANSFORMAR EN EL NUMERO QUE QUEREMOS X - 48 (EL 0 EN ASCII VALE 48)
      modo = entrada - '0';


      if (modo == 0) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 0 - Apagado");
        Serial.println("--------------------");
      }


      else if (modo == 1) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 1 - Normal");

        //COMENZAR CICLO NORMAL EN EL COLOR ROJO
        faseNormal = 0;
        tiempoNormal = millis();

        digitalWrite(rojo, HIGH);
        digitalWrite(amarillo, LOW);
        digitalWrite(verde, LOW);

        mostrarMenu();
      }


      else if (modo == 2) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 2 - Amarillo intermitente");

        //MIRA EL MODO Y EL TIEMPO ACTUAL
        estadoIntermitente = false;
        tiempoIntermitente = millis();

        digitalWrite(rojo, LOW);
        digitalWrite(amarillo, LOW);
        digitalWrite(verde, LOW);

        mostrarMenu();
      }


      else if (modo == 3) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 3 - Manual simple");
      }


      else if (modo == 4) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 4 - Manual complejo");
      }
    }
  }
}



void loop() {


  //COMPROBAR SI HE ENVIADO UN NUEVO CODIGO POR EL SERIAL
  if (Serial.available() > 0) {

    char entrada = Serial.read();


    //COMPROBAR SI ES INVALIDA
    if (entrada < '0' || entrada > '4') {

      Serial.println("--------------------");
      Serial.println("Valor invalido.");
      Serial.println("--------------------");

      modo = 0;
    }

    else {

      modo = entrada - '0';


      if (modo == 0) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 0 - Apagado");

        mostrarMenu();
      }


      else if (modo == 1) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 1 - Normal");

        //REINICIAR SEMAFORO DESDE ROJO
        faseNormal = 0;
        tiempoNormal = millis();

        digitalWrite(rojo, HIGH);
        digitalWrite(amarillo, LOW);
        digitalWrite(verde, LOW);

        mostrarMenu();
      }


      else if (modo == 2) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 2 - Amarillo intermitente");

        //MIRAR MODO Y TIEMPO ACTUAL
        estadoIntermitente = false;
        tiempoIntermitente = millis();

        digitalWrite(rojo, LOW);
        digitalWrite(amarillo, LOW);
        digitalWrite(verde, LOW);

        mostrarMenu();
      }


      else if (modo == 3) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 3 - Manual simple");
      }


      else if (modo == 4) {

        Serial.println("--------------------");
        Serial.println("Modo seleccionado: 4 - Manual complejo");
      }
    }
  }




  // MODO 0: APAGADO

  if (modo == 0) {

    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
  }

  // MODO 1: NORMAL SIN DELAY

  else if (modo == 1) {


    // FASE 0: ROJO
    if (faseNormal == 0) {

      //PARA QUE SOLO CAMBIE DE COLOR UNA VEZ PASEN 3000MS DESDE EL MOMENTO ACTUAL MEDIDO ANTERIORMENTE
      if (millis() - tiempoNormal >= 3000) {

        digitalWrite(rojo, LOW);
        digitalWrite(verde, HIGH);

        faseNormal = 1;
        tiempoNormal = millis();
      }
    }


    // FASE 1: VERDE
    else if (faseNormal == 1) {

      if (millis() - tiempoNormal >= 3000) {

        digitalWrite(verde, LOW);
        digitalWrite(amarillo, HIGH);

        faseNormal = 2;
        tiempoNormal = millis();
      }
    }


    // FASE 2: AMARILLO
    else if (faseNormal == 2) {

      if (millis() - tiempoNormal >= 500) {

        digitalWrite(amarillo, LOW);
        digitalWrite(rojo, HIGH);

        faseNormal = 0;
        tiempoNormal = millis();
      }
    }
  }



  // MODO 2: AMARILLO INTERMITENTE SIN DELAY

  else if (modo == 2) {

    if (millis() - tiempoIntermitente >= 500) {

      estadoIntermitente = !estadoIntermitente;

      digitalWrite(amarillo, estadoIntermitente);

      tiempoIntermitente = millis();
    }
  }



  // MODO 3: MANUAL SIMPLE

  else if (modo == 3) {

    mostrarMenuManualSimple();


    while (modo == 3) {
      
      //LEER MENSAJE POR SERIAL MONITOR
      if (Serial.available() > 0) {

        char entradaLuz = Serial.read();

        //MIRAR VALORES INVALIDOS
        if (entradaLuz < '0' || entradaLuz > '3') {

          Serial.println("Valor invalido.");
        }

        else {

          int luz = entradaLuz - '0';


          // Rojo
          if (luz == 1) {

            digitalWrite(rojo, HIGH);
            digitalWrite(amarillo, LOW);
            digitalWrite(verde, LOW);
          }


          // Amarillo
          else if (luz == 2) {

            digitalWrite(rojo, LOW);
            digitalWrite(amarillo, HIGH);
            digitalWrite(verde, LOW);
          }


          // Verde
          else if (luz == 3) {

            digitalWrite(rojo, LOW);
            digitalWrite(amarillo, LOW);
            digitalWrite(verde, HIGH);
          }


          // Salir
          else if (luz == 0) {

            digitalWrite(rojo, LOW);
            digitalWrite(amarillo, LOW);
            digitalWrite(verde, LOW);

            modo = 0;
          }
        }
      }
    }

    mostrarMenu();
  }




  // MODO 4: MANUAL COMPLEJO


  else if (modo == 4) {

    mostrarMenuManualComplejo();


    //MODO ACTUAL DE CADA LED:
    // 0 = APOAGADO
    // 1 = FIJO
    // 2 = PARPADEO

    int modoRojo = 0;
    int modoAmarillo = 0;
    int modoVerde = 0;


    //ESTADO ACTUAL DE CADA LED
    bool estadoRojo = false;
    bool estadoAmarillo = false;
    bool estadoVerde = false;


    //ULTIMO CAMBIO DE CADA LED
    unsigned long tiempoRojo = 0;
    unsigned long tiempoAmarillo = 0;
    unsigned long tiempoVerde = 0;


    while (modo == 4) {

      //SI RECIBE INFORMACION POR EL SERIAL
      if (Serial.available() > 0) {

        char entradaCompleja = Serial.read();

        //VALOR INVALIDO
        if (entradaCompleja < '0' || entradaCompleja > '6') {

          Serial.println("Valor invalido.");
        }

        //VALOR VALIDO
        else {

          int opcion = entradaCompleja - '0';

          // ROJO FIJO
          if (opcion == 1) {

            //SI ESTA ENCENDIDO APAGARLO Y VICEVERSA
            if (modoRojo == 1) {

              modoRojo = 0;
            }

            else {

              modoRojo = 1;
            }
          }

          // AMARILLO FIJO
          else if (opcion == 2) {
            
            //SI ESTA ENCENDIDO APAGARLO Y VICEVERSA
            if (modoAmarillo == 1) {

              modoAmarillo = 0;
            }

            else {

              modoAmarillo = 1;
            }
          }

          // VERDE FIJO
          else if (opcion == 3) {

            //SI ESTA ENCENDIDO APAGARLO Y VICEVERSA
            if (modoVerde == 1) {

              modoVerde = 0;
            }

            else {

              modoVerde = 1;
            }
          }

          // PARPADEO ROJO
          else if (opcion == 4) {

            if (modoRojo == 2) {

              modoRojo = 0;
            }

            else {

              modoRojo = 2;
            }
          }

          // PARPADEO AMARILLO
          else if (opcion == 5) {

            if (modoAmarillo == 2) {

              modoAmarillo = 0;
            }

            else {

              modoAmarillo = 2;
            }
          }

          // PARPADEO VERDE
          else if (opcion == 6) {

            if (modoVerde == 2) {

              modoVerde = 0;
            }

            else {

              modoVerde = 2;
            }
          }

          // SALIR
          else if (opcion == 0) {

            digitalWrite(rojo, LOW);
            digitalWrite(amarillo, LOW);
            digitalWrite(verde, LOW);

            modo = 0;
          }
        }
      }

      //CONTROL ROJO

      if (modoRojo == 0) {

        digitalWrite(rojo, LOW);
        estadoRojo = false;
      }

      else if (modoRojo == 1) {

        digitalWrite(rojo, HIGH);
        estadoRojo = true;
      }

      else if (modoRojo == 2) {

        parpadear(rojo, estadoRojo, tiempoRojo);
      }

      //CONTROL AMARILLO

      if (modoAmarillo == 0) {

        digitalWrite(amarillo, LOW);
        estadoAmarillo = false;
      }

      else if (modoAmarillo == 1) {

        digitalWrite(amarillo, HIGH);
        estadoAmarillo = true;
      }

      else if (modoAmarillo == 2) {

        parpadear(amarillo, estadoAmarillo, tiempoAmarillo);
      }

      //CONTROL VERDE

      if (modoVerde == 0) {

        digitalWrite(verde, LOW);
        estadoVerde = false;
      }

      else if (modoVerde == 1) {

        digitalWrite(verde, HIGH);
        estadoVerde = true;
      }

      else if (modoVerde == 2) {

        parpadear(verde, estadoVerde, tiempoVerde);
      }
    }

    mostrarMenu();
  }
}