/*


╭━━━╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━━━╮╱╱╱╭╮╭╮
┃╭━━╯╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃╭━╮┃╱╱╱┃┃┃┃
┃╰━━┳╮╭┳━━┳━━┳━╮╭┳━━╮┃┃╱╰╋┳╮╭┫┃┃┃╭━━╮
┃╭━━┫┃┃┃╭╮┃┃━┫╭╮╋┫╭╮┃┃┃╱╭╋┫┃┃┃┃┃┃┃╭╮┃
┃╰━━┫╰╯┃╰╯┃┃━┫┃┃┃┃╰╯┃┃╰━╯┃┃╰╯┃╰┫╰┫╰╯┃
╰━━━┻━━┻━╮┣━━┻╯╰┻┻━━╯╰━━━┻┻━━┻━┻━┻━━╯
╱╱╱╱╱╱╱╭━╯┃
╱╱╱╱╱╱╱╰━━╯


███████╗░█████╗░  ██╗░░░░░░█████╗░  ██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██████╗░░█████╗░██╗░░██╗███████╗
██╔════╝██╔══██╗  ██║░░░░░██╔══██╗  ██║░░██║██╔══██╗████╗░██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║░██╔╝██╔════╝
█████╗░░██║░░╚═╝  ██║░░░░░██║░░╚═╝  ███████║███████║██╔██╗██║██║░░██║██████╦╝██████╔╝███████║█████═╝░█████╗░░
██╔══╝░░██║░░██╗  ██║░░░░░██║░░██╗  ██╔══██║██╔══██║██║╚████║██║░░██║██╔══██╗██╔══██╗██╔══██║██╔═██╗░██╔══╝░░
███████╗╚█████╔╝  ███████╗╚█████╔╝  ██║░░██║██║░░██║██║░╚███║██████╔╝██████╦╝██║░░██║██║░░██║██║░╚██╗███████╗
╚══════╝░╚════╝░  ╚══════╝░╚════╝░  ╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝

Version 1.0
Copyright (c) 2020 Eugenio Ciullo


Questo sketch è stato creato da Eugenio Ciullo

Installare nella Documents/Arduino directory la libreria ArduinoJoystickLibrary creata da MHeironimus reperibile al seguente link:
https://github.com/MHeironimus/ArduinoJoystickLibrary


Lo sketch per la Pedaliera è stato configurato per ricevere il segnale da 3 amplificatori HX711 per loadcell

Collegare come segue:
Cella Acceleratore:
VCC -> VCC
GND -> GND
DOUT -> PIN3
Clock -> PIN2


*/

#include "HX711.h"
#include <Joystick.h>

const int LOADCELL_DOUT_PIN1 = 3;
const int LOADCELL_SCK_PIN1 = 2;

long handbrake = 0;


// Se volete calibrare il range degli assi, sostituire i seguenti valori
const long Zonainferiorehandbrake = 0;
const long Zonasuperiorehandbrake = 32768;

// Modificare questo valore sino a che la pressione massima non restituisca valori maggiori di 32768
const long calibration_factor1 = 120;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  false, false, true,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

HX711 scale1;

void setup() {
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale1.set_scale(calibration_factor1);
  Joystick.begin();
  Joystick.setZAxisRange(Zonainferiorehandbrake, Zonasuperiorehandbrake);
 
//decommentare eliminando i // nel prossimo valore se si vuole aprire la monitor seriale
 // Serial.begin(9600);
    }
const bool initAutoSendState = true;


void loop() {
  handbrake = scale1.get_units();
  Joystick.setZAxis(handbrake);
  
// Decommentare le seriali eliminando /* e */ alla fine dei Serial.print

 //   Serial.print("handbrake : \t");
 //   Serial.println(handbrake);

  delay(0);
}
