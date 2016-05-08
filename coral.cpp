#include <iostream>
#include <stdexcept>
#include "voice.h"
#include "midi.h"
using namespace std;

int main(int argc, char* argv[])
{
  const char* file = "salida.mid";  // Nombre por defecto
  if (argc > 1)
    file = argv[1];

  const int INPUT_LIMIT = 65536;
  char input[INPUT_LIMIT];
  Voice v[4];
  char num[][8] = {"Primera", "Segunda", "Tercera", "Cuarta"};

  // Se leen las cuatro líneas de voces en formato "amigable"
  for (short int x = 0; x < 4; x++)
  {
    cout << num[x] << " voz: ";
    cin.getline(input, INPUT_LIMIT);
    try
    {
      v[x].Set(input);
    }
    catch (invalid_argument a)
    {
      cerr << "Error: " << a.what() << endl;
      x--;
    }
  }

  bool success = Write(file, v, INPUT_LIMIT);
  if (!success)
    cerr << "Error al intentar guardar el archivo";
  
  return !success;
}
