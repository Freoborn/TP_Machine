// Definition der Endstopstasterpins
const int endstop1in = 41;
const int endstop1out = 43;
const int endstop2in = 41;
const int endstop2out = 43;
const int endstop3in = 41;
const int endstop3out = 47;
const int endstop4in = 41;
const int endstop4out = 43;
const int endstop5in = 41;
const int endstop5out = 43;
const int endstop6in = 41;
const int endstop6out = 43;
const int endstop7in = 41;
const int endstop7out = 43;
const int endstop8in = 41;
const int endstop8out = 43;

// Definition der Kap- und Drahtschalter
const int cap1 = 42;
const int cap2 = 44;
const int cap3 = 46;
const int wire1 = 43;

// Definition der Signaleausgangspins and die Magnetschalter/Papiermotor
const int signalDropIn = 30;
const int signalDropOut = 32;
const int signalFold2 = 28;
const int signalFold1 = 27;
const int signalMark = 26;
const int signalSuck = 25;
const int signalCut = 24;
const int signalPerfo = 23;
const int signalPaper = 22;

// Definition der LEDpins
const int ledProcess1 = 51;
const int ledProcess2 = 51;
const int ledProcess3 = 51;
const int ledProcess4 = 51;
const int ledProcess5 = 51;
const int ledProcess6 = 51;
const int ledProcess7 = 51;
const int ledProcess8 = 51;
const int ledProcessPaper = 51;

const int fehlersignalPin = 51; // Fehlersignal-Pin beibehalten

// Globale Variablen, um den Startzeitpunkt des Loslassens von Endstop (in) zu speichern
unsigned long endstop1inT = 0;
unsigned long endstop2inT = 0;
unsigned long endstopFold2InT = 0;
unsigned long endstopFold1InT = 0;
unsigned long endstopMarkInT = 0;
unsigned long endstopSuckInT = 0;
unsigned long endstopCutInT = 0;
unsigned long endstopPerfoInT = 0;
unsigned long paperOutT = 0;

int count = 0;

// Zustand des Perforationsprozesses
enum PaperState {
  CHECK_SENSOR1,
  PAPER_SERVE,
  PAPER_FINISH,
  PAPER_ERROR
};
PaperState paperStateIS = PAPER_FINISH;

// Zustand des Perforationsprozesses
enum PerfoState {
  CHECK_PERFO_IN,
  PERFORATE,
  PERFO_FINISH,
  PERFO_ERROR
};
PerfoState perfoStateIS = CHECK_PERFO_IN;

// Zustand des Schneideprozesses
enum CutState {
  CHECK_CUT_IN,
  CUT,
  CUT_FINISH,
  CUT_ERROR
};
CutState cutStateIS = CHECK_CUT_IN;

// Zustand des ersten Faltprozesses
enum Fold1State {
  CHECK_FOLD1_IN,
  FOLD1,
  FOLD1_FINISH,
  FOLD1_ERROR
};
Fold1State fold1StateIS = CHECK_FOLD1_IN;

// Zustand des zweiten Faltprozesses
enum Fold2State {
  CHECK_FOLD2_IN,
  FOLD2,
  FOLD2_FINISH,
  FOLD2_ERROR
};
Fold2State fold2StateIS = CHECK_FOLD2_IN;

// Zustand des Markierungsprozesses
enum MarkState {
  CHECK_MARK_IN,
  MARK,
  MARK_FINISH,
  MARK_ERROR
};
MarkState markStateIS = CHECK_MARK_IN;

// Zustand des 1. Ansaugprozesses An
enum Suck1State {
  CHECK_SUCK1_IN,
  SUCK1,
  SUCK1_FINISH,
  SUCK1_ERROR
};
Suck1State suck1StateIS = CHECK_SUCK1_IN;

// Zustand des 2.Ansaugprozesses An
enum Suck2State {
  CHECK_SUCK2_IN,
  SUCK2,
  SUCK2_FINISH,
  SUCK2_ERROR
};
Suck2State suck2StateIS = CHECK_SUCK2_IN;

// Zustand des Ansaugprozesses Aus
enum SuckOffState {
  CHECK_SUCK_OUT,
  SUCKOFF,
  SUCKOFF_FINISH,
  SUCKOFF_ERROR
};
SuckOffState suckOffStateIS = CHECK_SUCK_OUT;

// Zustand des Auswerfprozesses
enum DropState {
	DROP,
	DROP_FINISH,
	DROP_ERROR
};
DropState dropStateIS = DROP;

bool startUp = true;


void setup() {
  // Setze die Endstopstaster als Eingänge mit Pull-up-Widerständen
  pinMode(endstop1in, INPUT_PULLUP);
  pinMode(endstop1out, INPUT_PULLUP);
  pinMode(endstop2in, INPUT_PULLUP);
  pinMode(endstop2out, INPUT_PULLUP);
  pinMode(endstop3in, INPUT_PULLUP);
  pinMode(endstop3out, INPUT_PULLUP);
  pinMode(endstop4in, INPUT_PULLUP);
  pinMode(endstop4out, INPUT_PULLUP);
  pinMode(endstop5in, INPUT_PULLUP);
  pinMode(endstop5out, INPUT_PULLUP);
  pinMode(endstop6in, INPUT_PULLUP);
  pinMode(endstop6out, INPUT_PULLUP);
  pinMode(endstop7in, INPUT_PULLUP);
  pinMode(endstop7out, INPUT_PULLUP);
  pinMode(endstop8in, INPUT_PULLUP);
  pinMode(endstop8out, INPUT_PULLUP);

  // Setze die Signalausgangs-Pins als Ausgänge
  pinMode(signalDropIn, OUTPUT);
  pinMode(signalDropOut, OUTPUT);
  pinMode(signalFold2, OUTPUT);
  pinMode(signalFold1, OUTPUT);
  pinMode(signalMark, OUTPUT);
  pinMode(signalSuck, OUTPUT);
  pinMode(signalCut, OUTPUT);
  pinMode(signalPerfo, OUTPUT);
  pinMode(signalPaper, OUTPUT);


  // Setze die LED-Pins als Ausgänge
  pinMode(ledProcess1, OUTPUT);
  pinMode(ledProcess2, OUTPUT);
  pinMode(ledProcess3, OUTPUT);
  pinMode(ledProcess4, OUTPUT);
  pinMode(ledProcess5, OUTPUT);
  pinMode(ledProcess6, OUTPUT);
  pinMode(ledProcess7, OUTPUT);
  pinMode(ledProcess8, OUTPUT);
  pinMode(ledProcessPaper, OUTPUT);


  // Initialisiere die Signalausgänge und LEDs mit LOW
  digitalWrite(signalDropIn, HIGH);
  digitalWrite(signalDropOut, HIGH);
  digitalWrite(signalFold2, HIGH);
  digitalWrite(signalFold1, HIGH);
  digitalWrite(signalMark, HIGH);
  digitalWrite(signalSuck, HIGH);
  digitalWrite(signalCut, HIGH);
  digitalWrite(signalPerfo, HIGH);
  digitalWrite(signalPaper, HIGH);

  digitalWrite(ledProcess1, LOW);
  digitalWrite(ledProcess2, LOW);
  digitalWrite(ledProcess3, LOW);
  digitalWrite(ledProcess4, LOW);
  digitalWrite(ledProcess5, LOW);
  digitalWrite(ledProcess6, LOW);
  digitalWrite(ledProcess7, LOW);
  digitalWrite(ledProcess8, LOW);
  digitalWrite(ledProcessPaper, LOW);
  Serial.begin(9600); // Starte die serielle Kommunikation für Debugging
  Serial.println("Start");
}



void loop() {
	
	start();
	
	if (digitalRead(cap3) == HIGH) { // Wenn das Magazin noch nicht voll ist
	// Führe den ersten Prozess aus
	paper();

	// Führe den zweiten Prozess aus, wenn der erste abgeschlossen ist
	if (paperStateIS == PAPER_FINISH) {
		perfo();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (perfoStateIS == PERFO_FINISH) {
		cut();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (cutStateIS == CUT_FINISH) {
		suck1On();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (suck1StateIS == SUCK1) {
		mark();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (markStateIS == MARK_FINISH) {
		fold1();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (fold1StateIS == FOLD1_FINISH) {
		suck1Off();
		delay(2000);
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (suck1StateIS == SUCK1_FINISH) {
		suck2On();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (suck2StateIS == SUCK2) {
		fold2();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (fold2StateIS == FOLD2_FINISH) {
		suck2Off();
		delay(2000);
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (suck2StateIS == SUCK2_FINISH) {
		drop();
	}

	// Führe den dritten Prozess aus, wenn der zweite abgeschlossen ist
	if (dropStateIS == DROP_FINISH) {
		reset();
	}
	

	// Wenn irgendein Fehler aufgetreten ist, stoppe den gesamten Ablauf und zeige Fehlersignal
	if (paperStateIS == PAPER_ERROR || perfoStateIS == PERFO_ERROR || cutStateIS == CUT_ERROR || fold1StateIS == FOLD1_ERROR || fold2StateIS == FOLD2_ERROR || markStateIS == MARK_ERROR || suck1StateIS == SUCK1_ERROR || suck2StateIS == SUCK2_ERROR || dropStateIS == DROP_ERROR) {
		Serial.println("Fehler im Ablauf! Stoppe.");
		digitalWrite(fehlersignalPin, HIGH); // Gib ein Fehlersignal aus
		while (true) {
		// Endlosschleife, um den Ablauf zu stoppen
		}
	}

  delay(10); // Kurze Pause für Entprellung und zur Reduzierung der CPU-Last
  
	} else {
		Serial.println("Magazin Voll");
		while (true) {
			      // Endlosschleife, um den Ablauf zu stoppen
		}
	}
}

void start() {
	if (startUp == true) {
		digitalWrite(ledProcess1, HIGH);
		delay(250);
		digitalWrite(ledProcess2, HIGH);
		delay(250);
		digitalWrite(ledProcess3, HIGH);
		delay(250);
		digitalWrite(ledProcess4, HIGH);
		delay(250);
		digitalWrite(ledProcess5, HIGH);
		delay(250);
		digitalWrite(ledProcess6, HIGH);
		delay(250);
		digitalWrite(ledProcess7, HIGH);
		delay(250);
		digitalWrite(ledProcess8, HIGH);
		delay(1000);
		digitalWrite(ledProcess1, LOW);
		digitalWrite(ledProcess2, LOW);
		digitalWrite(ledProcess3, LOW);
		digitalWrite(ledProcess4, LOW);
		digitalWrite(ledProcess5, LOW);
		digitalWrite(ledProcess6, LOW);
		digitalWrite(ledProcess7, LOW);
		digitalWrite(ledProcess8, LOW);
		startUp = false;
		Serial.println("Start");
		Serial.println(digitalRead(cap2));
	}
}


void paper () {
	switch (paperStateIS) {
		case CHECK_SENSOR1:
			if (digitalRead(cap1) == HIGH) {
				Serial.println("Paper");
				digitalWrite(signalPaper, HIGH); // Papier wird ausgeben
				paperStateIS = PAPER_SERVE;
				paperOutT = millis(); // Zeitpunkt des Papierausgebenstart
			}
			break;
		case PAPER_SERVE:
			if (digitalRead(cap1) == LOW) { // Papier hat Sensor erreicht
				Serial.println("Paper stop");
				digitalWrite(signalPaper, LOW); // Papier stoppen
				digitalWrite(ledProcessPaper, HIGH); // LED einschalten
				paperStateIS = PAPER_FINISH;
			} else if (millis() - paperOutT > 10000) {
				Serial.println("Paper Fehler");
				paperStateIS = PAPER_ERROR;
			}
			break;
		
		case PAPER_FINISH:
			break;  //Papier bis Sensor ausgegeben
			
		case PAPER_ERROR:
			break;  // Fehler beim Papierausgeben
	}
}

void perfo() {
	switch (perfoStateIS) {
		case CHECK_PERFO_IN:
			if (digitalRead(endstop1in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
				Serial.println("Perforation Start");
				digitalWrite(signalPerfo, LOW); // Perforation ausfahren
				perfoStateIS = PERFORATE;
				endstopPerfoInT = millis();				
			} else {
				Serial.println("Perforation Fehler");
				perfoStateIS = PERFO_ERROR;
			}
			break;
			
		case PERFORATE:
			while (digitalRead(endstop1out) == HIGH) {
				if (millis() - endstopPerfoInT > 5000){
				Serial.println("Zeitüberschreitung bei Perforieren");
				perfoStateIS = PERFO_ERROR;
				break;
				}
			}
			if (digitalRead(endstop1out) == LOW) {
				Serial.println("Perforation Ende");
				digitalWrite(signalPerfo, HIGH); // Perforation einfahren
				digitalWrite(ledProcess1, HIGH); // LED einschalten
				perfoStateIS = PERFO_FINISH;
			} else {
				Serial.println("Perforation Fehler");
				perfoStateIS = PERFO_ERROR;
			}
			break;
		
		case PERFO_FINISH:
			break;  //Papier bis Sensor ausgegeben
			
		case PERFO_ERROR:
			break;  // Fehler beim Papierausgeben 
	}
}

void cut() {
	switch (cutStateIS) {
		case CHECK_CUT_IN:
			if (digitalRead(endstop2in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
				Serial.println("Schneiden Start");
				digitalWrite(signalCut, LOW); // Schneiden ausfahren
				cutStateIS = CUT;
				endstopCutInT = millis();				
			} else {
				Serial.println("Schneiden Fehler");
				cutStateIS = CUT_ERROR;
			}
			break;
			
		case CUT:
			while (digitalRead(endstop2out) == HIGH) {
				if (millis() - endstopCutInT > 5000){
				Serial.println("Zeitüberschreitung beim Schneiden");
				cutStateIS = CUT_ERROR;
				break;
				}
			}
			if (digitalRead(endstop2out) == LOW) {
				Serial.println("Schneiden Ende");
				digitalWrite(signalCut, HIGH); // Perforation einfahren
				digitalWrite(ledProcess2, HIGH); // LED einschalten
				cutStateIS = CUT_FINISH;
			} else {
				Serial.println("Schneiden Fehler");
				cutStateIS = CUT_ERROR;
			}
			break;
		
		case CUT_FINISH:
			break;  //Papier bis Sensor ausgegeben
			
		case CUT_ERROR:
			break;  // Fehler beim Papierausgeben 
	}
}

void suck1On() {
	switch (suck1StateIS) {
		case CHECK_SUCK1_IN:
			if (digitalRead(endstop3in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
				Serial.println("Luft 1 Start");
				digitalWrite(signalSuck, LOW); // Luft ausfahren
				suck1StateIS = SUCK1;
				endstopSuckInT = millis();				
			} else {
				Serial.println("Luft 1 Fehler");
				suck1StateIS = SUCK1_ERROR;
			}
			break;
		
		case SUCK1_ERROR:
			break;  // Fehler beim Papierausgeben 
	}
}

void suck2On() {
	switch (suck2StateIS) {
		case CHECK_SUCK2_IN:
			if (digitalRead(endstop3in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
				Serial.println("Luft 2 Start");
				digitalWrite(signalSuck, LOW); // Luft ausfahren
				suck2StateIS = SUCK2;
				endstopSuckInT = millis();				
			} else {
				Serial.println("Luft 2 Fehler");
				suck2StateIS = SUCK2_ERROR;
			}
			break;
		
		case SUCK2_ERROR:
			break;  // Fehler beim Papierausgeben 
	}
}

void suck1Off() {
	switch (suck1StateIS) {
		case SUCK1:
			if (digitalRead(endstop3out) == LOW) {
				Serial.println("Luft 1 Aus");
				digitalWrite(signalSuck, HIGH);
				digitalWrite(ledProcess2, HIGH); // LED einschalten
				suck1StateIS = SUCK1_FINISH;
			} else {
				Serial.println("Luft 1 Fehler");
				suck1StateIS = SUCK1_ERROR;
			}
			break;
		
		case SUCK1_FINISH:
			break;  //Papier bis Sensor ausgegeben
			
		case SUCK1_ERROR:
			break;  // Fehler beim Papierausgeben 
	}
}

void suck2Off() {
	switch (suck2StateIS) {
		case SUCK2:
			if (digitalRead(endstop3out) == LOW) {
				Serial.println("Luft 2 Aus");
				digitalWrite(signalSuck, LOW);
				digitalWrite(ledProcess2, HIGH); // LED einschalten
				suck2StateIS = SUCK2_FINISH;
			} else {
				Serial.println("Luft 2 Fehler");
				suck2StateIS = SUCK2_ERROR;
			}
			break;
		
		case SUCK2_FINISH:
			break;  //Papier bis Sensor ausgegeben
			
		case SUCK2_ERROR:
			break;  // Fehler beim Papierausgeben 
	}
}

void mark() {
	switch (markStateIS) {
		case CHECK_MARK_IN:
			if (digitalRead(endstop4in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
				Serial.println("Markieren Start");
				digitalWrite(signalMark, LOW); // Markieren ausfahren
				markStateIS = MARK;
				endstopMarkInT = millis();				
			} else {
				Serial.println("Markieren Fehler");
				markStateIS = MARK_ERROR;
			}
			break;
			
		case MARK:
			while (digitalRead(endstop4out) == HIGH) {
				if (millis() - endstopMarkInT > 5000){
				Serial.println("Zeitüberschreitung beim Markieren");
				markStateIS = MARK_ERROR;
				break;
				}
			}
			if (digitalRead(endstop4out) == LOW) {
				Serial.println("Markieren Ende");
				digitalWrite(signalMark, HIGH); // Markieren einfahren
				digitalWrite(ledProcess2, HIGH); // LED einschalten
				markStateIS = MARK_FINISH;
			} else {
				Serial.println("Markieren Fehler");
				markStateIS = MARK_ERROR;
			}
			break;
		
		case MARK_FINISH:
			break;  
			
		case MARK_ERROR:
			break;  
	}
}

void fold1() {
	switch (fold1StateIS) {
		case CHECK_FOLD1_IN:
			if (digitalRead(endstop5in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
				Serial.println("Falten 1 Start");
				digitalWrite(signalFold1, LOW); // Falten ausfahren
				fold1StateIS = FOLD1;
				endstopFold1InT = millis();				
			} else {
				Serial.println("Falten 1 Fehler es");
				fold1StateIS = FOLD1_ERROR;
			}
			break;
			
		case FOLD1:
			while (digitalRead(endstop5out) == HIGH) {
				if (millis() - endstopPerfoInT > 5000){
				Serial.println("Zeitüberschreitung bei Falten 1");
				fold1StateIS = FOLD1_ERROR;
				break;
				}
			}
			if (digitalRead(endstop5out) == LOW) {
				Serial.println("Falten 1 Ende");
				digitalWrite(signalFold1, HIGH); // Falten 1 einfahren
				digitalWrite(ledProcess2, HIGH); // LED einschalten
				fold1StateIS = FOLD1_FINISH;
			} else {
				Serial.println("Falten 1 Fehler ne");
				fold1StateIS = FOLD1_ERROR;
			}
			break;
		
		case FOLD1_FINISH:
			break;  
			
		case FOLD1_ERROR:
			break;  
	}
}

void fold2() {
	switch (fold2StateIS) {
		case CHECK_FOLD2_IN:
			if (digitalRead(cap2) == LOW) {
				if (digitalRead(endstop6in) == LOW) { // Endstop (in) gedrückt (LOW wegen Pull-Up)
					Serial.println("Falten 2 Start");
					digitalWrite(signalFold2, LOW); // Falten 2 ausfahren
					fold2StateIS = FOLD2;
					endstopFold2InT = millis();				
				} else {
					Serial.println("Falten 2 Fehler es");
					fold2StateIS = FOLD2_ERROR;
				} 
			} else {
				Serial.println("Falten 2 Fehler cap");
				fold2StateIS = FOLD2_ERROR;
			}	
			break;
			
		case FOLD2:
		while (digitalRead(endstop6out) == HIGH) {
				if (millis() - endstopPerfoInT > 5000){
				Serial.println("Zeitüberschreitung bei Falten 2");
				fold2StateIS = FOLD2_ERROR;
				break;
				}
			}
			if (digitalRead(endstop6out) == LOW) {
				Serial.println("Falten 2 Ende");
				digitalWrite(signalFold2, HIGH); 
				digitalWrite(ledProcess2, HIGH); 
				fold2StateIS = FOLD2_FINISH;
			} else {
				Serial.println("Falten 2 Fehler ne");
				fold2StateIS = FOLD2_ERROR;
			}
			break;
		
		case FOLD2_FINISH:
			break;  
			
		case FOLD2_ERROR:
			break;  
	}
}

void drop() {
	switch (dropStateIS) {
		case DROP:
			if (digitalRead(cap2) == LOW) {
				if (digitalRead(cap3) == HIGH) {
					Serial.println("Auswerfen");
					digitalWrite(signalDropIn, LOW);
					digitalWrite(signalDropOut, HIGH);
					dropStateIS = DROP_FINISH;
					delay (1000);
					digitalWrite(signalDropOut, LOW);
					digitalWrite(signalDropIn, HIGH);
				} else {
					Serial.println("Magazin Voll");
					dropStateIS = DROP_ERROR;
				} 
			} else {
				Serial.println("Falten Fehler");
				dropStateIS = DROP_ERROR;
			}	
			break;
	}
}

void reset () {
	paperStateIS = CHECK_SENSOR1;
	perfoStateIS = CHECK_PERFO_IN;
	cutStateIS = CHECK_CUT_IN;
	fold1StateIS = CHECK_FOLD1_IN;
	fold2StateIS = CHECK_FOLD2_IN;
	markStateIS = CHECK_MARK_IN;
	suck1StateIS = CHECK_SUCK1_IN;
	suck2StateIS = CHECK_SUCK2_IN;
	dropStateIS = DROP;
	count = ++count;
	Serial.print(count);
	Serial.println(" im Magazin");
}
