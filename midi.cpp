// Definiciones del módulo para generar el archivo MIDI
#include "midi.h"
using namespace std;

// Genera el trozo de datos MIDI que almacena los sonidos
bool GetChunk(const Voice v[], char data[], unsigned int &chpos, int INPUT_LIMIT)
{
  /* Se leen simultáneamente las cuatro voces, añadiendo cuando es necesario
      caracteres que indican final o inicio de sonido
  */
  chpos = 0;
  unsigned short int pos[] = {0,0,0,0};

  unsigned short int nothingfor = 0;  // Semicorcheas en las que no ha habido cierre de sonidos
  
  unsigned short int countdown[] = {0,0,0,0};
  bool finish[] = {false, false, false, false};
  while (!(finish[0] && finish[1] && finish[2] && finish[3]))
  {
    bool nothing_happened = true;
    for (unsigned short int i = 0; i < 4; i++)
    {
      if (!finish[i] && countdown[i] == 0)
      {
        finish[i] = v[i].Length(pos[i]) == 0;
        if (!finish[i] && v[i].MIDIpitch(pos[i]) == 0)
          countdown[i] = v[i].Length(pos[i]++);
        else
        {
          if (nothing_happened)
          {
            nothing_happened = false;
            if (chpos > 0)
              data[chpos++] = (char) (128+2*nothingfor);
            nothingfor = 0;
          }
          if (pos[i] > 0)
          {
            data[chpos++] = 0x00;
            data[chpos++] = 0x80;
            data[chpos++] = v[i].MIDIpitch(v[i].Source(pos[i]-1));
            data[chpos++] = 0x00;
          }
          if (!finish[i])
          {
            data[chpos++] = 0x00;
            data[chpos++] = 0x90;
            data[chpos++] = v[i].MIDIpitch(pos[i]);
            data[chpos++] = 0x40;
            countdown[i] = v[i].Length(pos[i]++);
          }
        }
      }
      if (countdown[i] > 0)
        countdown[i]--;
    }
    nothingfor++;
  }
  return chpos < INPUT_LIMIT;
}

// Guarda en un archivo un fragmento junto con una cabecera y dos fragmentos fijos
bool Write(const char* name, const char* data, unsigned int chpos)
{
  ofstream f(name, ios::out|ios::binary);
  if (f)
  {
    // Se escribe la cabecera
    char header[52] = {0x4d, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x02, 0x04, 0x00, 0x4d, 0x54, 0x72, 0x6b, 0x00, 0x00, 0x00, 0x1a, 0x00, 0xff, 0x58, 0x04, 0x04, 0x02, 0x18, 0x08, 0x00, 0xff, 0x59, 0x02, 0x00, 0x00, 0x00, 0xff, 0x51, 0x03, 0x07, 0xa1, 0x20, 0xa0, 0x00, 0xff, 0x2f, 0x00, 0x4d, 0x54, 0x72, 0x6b};
    f.write(header, 52);

    // Se calcula la longitud del trozo y se escribe en hexadecimal
    unsigned int length = chpos + 12;
    for (short int x = 3; x > -1; x--)
      f << (char) ((length >> 8*x)%256);    

    // Se escribe el trozo y el final del fichero
    char instrument = 0x34; // Coro Aahs (52 en decimal)
    char middle[8] = {0x00, 0xff, 0x03, 0x01, 0xc7, 0x00, 0xc0, instrument};
    f.write(middle, 8);

    f.write(data, chpos);

    char end[4] = {0x00, 0xff, 0x2f, 0x00};
    f.write(end, 4);
  }
  return f;
}

// Llama a las dos funciones anteriores
bool Write(const char* name, const Voice v[], int INPUT_LIMIT)
{
  char data[INPUT_LIMIT];
  unsigned int chpos;
  return GetChunk(v, data, chpos, INPUT_LIMIT) && Write(name, data, chpos);
}
