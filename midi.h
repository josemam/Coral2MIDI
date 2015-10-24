// Módulo para generar el archivo MIDI
#ifndef _MIDI_H_
#define _MIDI_H_

#include <fstream>
#include "voice.h"

// Genera el trozo de datos MIDI que almacena los sonidos
bool GetChunk(const Voice v[], char data[], unsigned int &chpos, int INPUT_LIMIT);

// Guarda en un archivo un fragmento junto con una cabecera y dos fragmentos fijos
bool Write(const char* name, const char* data, unsigned int chpos, char instrument);

// Llama a las dos funciones anteriores
// 52 = Coro Aahs
bool Write(const char* name, const Voice v[], int INPUT_LIMIT, char instrument=52);

#endif
