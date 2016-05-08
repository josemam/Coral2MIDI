// Cabeceras de la clase Voice

#ifndef _VOICE_H_
#define _VOICE_H_

class Voice
{
  /*
     En cada elemento del vector data se almacena la altura y la figura de una nota.
     0x(00/01/02/03) indican ligadura de la nota anterior con longitud semicorchea/corchea/negra/blanca
     Valores entre 0x04 y 0xFF guardan en los 6 primeros bits la altura (0000 01 es sol1, 1111 11 es la6)
     y en los 2 últimos la longitud (semicorchea 00~blanca 11)
     Las redondas se harán ligando dos blancas, qué remedio.
  */
  static const unsigned short int MAX_LENGTH = 8192;   // Límite arbitrario y tal vez excesivo
  static const char NOTES[7][4];
  unsigned char data[MAX_LENGTH];
  unsigned short int length;

  // Obtiene los 6 primeros bits: la altura
  unsigned char Pitch(char* &input) const;

  // Obtiene los 2 últimos bits: la duración
  unsigned char Note(char input) const;

public:
  // Rellena los datos de la instancia a partir de datos leídos desde entrada estándar
  void Set(char input[]);

  // Devuelve la duración en semicorcheas
  unsigned short int Length(unsigned int pos) const;

  // Devuelve la posición en la que la nota empezó a sonar
  unsigned short int Source(unsigned short int pos) const;

  // Devuelve el caracter de la altura MIDI de la nota (do central = 60) 0 30 si es ligadura
  char MIDIpitch(unsigned int pos) const;
};

#endif
