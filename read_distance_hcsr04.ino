//// Leitura HC-SR04
//const uint8_t trig_pin = 0;
//const uint8_t echo_pin1 = 12;
//const uint8_t echo_pin2 = 15;
//uint32_t print_timer;
//
//int distancia2 = 0;
//int distancia3 = 0;
//
//void configPinsUltrassonicSensors() {
//    Serial.begin(9600); // Habilita Comunicação Serial a uma taxa de 9600 bauds.
//    // Configuração do estado inicial dos pinos Trig e Echo.
//    pinMode(trig_pin, OUTPUT);
//    pinMode(echo_pin1, INPUT);
//    pinMode(echo_pin2, INPUT);
//}
//
//void readDistanceUltrassonic() {
//    // Espera 0,5s (500ms) entre medições.
//    if (millis() - print_timer > 500) {
//        print_timer = millis();
//        // Pulso de 5V por pelo menos 10us para iniciar medição.
//        
//        digitalWrite(trig_pin, LOW);
//        delayMicroseconds(2);
//        digitalWrite(trig_pin, HIGH);
//        delayMicroseconds(5);
//        digitalWrite(trig_pin, LOW);
//        /* Mede quanto tempo o pino de echo ficou no estado alto, ou seja,
//        o tempo de propagação da onda. */
//        uint32_t pulse_time1 = pulseIn(echo_pin1, HIGH);
//        /* A distância entre o sensor ultrassom e o objeto será proporcional a velocidade
//        do som no meio e a metade do tempo de propagação. Para o ar na
//        temperatura ambiente Vsom = 0,0343 cm/us. */
//        double distance2 = (0.0343 / 2) * pulse_time1;
//        distancia2 = distance2 * 10;
//
//        digitalWrite(trig_pin, LOW);
//        delayMicroseconds(2);
//        digitalWrite(trig_pin, HIGH);
//        delayMicroseconds(5);
//        digitalWrite(trig_pin, LOW);
//        /* Mede quanto tempo o pino de echo ficou no estado alto, ou seja,
//        o tempo de propagação da onda. */
//        uint32_t pulse_time2 = pulseIn(echo_pin2, HIGH);
//        
//        double distance3 = (0.0343 / 2) * pulse_time2;
//        distancia3 = distance3 * 10;
//        
//    }
//          // Imprimimos o valor na porta serial;
//        Serial.print("--- 2: ");
//        Serial.print(distancia2);
//        Serial.print("--- ");
//        Serial.print("3: ");
//        Serial.println(distancia3);
//}
