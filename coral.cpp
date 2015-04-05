#include <iostream>
#include <fstream>
#include "voice.cpp"
using namespace std;

int main()
{
  const int INPUT_LIMIT = 65536;
  char input[INPUT_LIMIT];
  Voice v[4];
  char num[][8] = {"Primera", "Segunda", "Tercera", "Cuarta"};

  // Se leen las cuatro líneas de voces en formato "amigable"
  for (short int x = 0; x < 4; x++)
  {
    cout << num[x] << " voz: ";
    cin.getline(input, INPUT_LIMIT);
    if (!v[x].Set(input))
      return 1;
  }

  // Se genera el trozo de datos MIDI que almacena los sonidos. Podría pasarse a función
  char data[INPUT_LIMIT];
  unsigned int chpos = 0;
  unsigned short int pos[] = {0,0,0,0};

  unsigned short int nothingfor = 0;
  
  unsigned short int countdown[] = {0,0,0,0};
  bool finish[] = {false, false, false, false};
  while (!(finish[0] && finish[1] && finish[2] && finish[3]))
  {
    bool nothing_happened = true;
    for (unsigned short int i = 0; i < 4; i++)
    {
      if (!finish[i] && countdown[i] == 0)
      {
        if (v[i].Length(pos[i]) > 0 && v[i].Source(pos[i]) < pos[i])
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
          finish[i] = v[i].Length(pos[i]) == 0;
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

  // Guarda en un archivo los datos anteriores junto con una cabecera y dos fragmentos fijos
  ofstream f("salida.mid",ios::out|ios::binary);
  if (f)
  {
    char header[52] = {0x4d, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x02, 0x04, 0x00, 0x4d, 0x54, 0x72, 0x6b, 0x00, 0x00, 0x00, 0x1a, 0x00, 0xff, 0x58, 0x04, 0x04, 0x02, 0x18, 0x08, 0x00, 0xff, 0x59, 0x02, 0x00, 0x00, 0x00, 0xff, 0x51, 0x03, 0x07, 0xa1, 0x20, 0xa0, 0x00, 0xff, 0x2f, 0x00, 0x4d, 0x54, 0x72, 0x6b};
    f.write(header, 52);

    unsigned int length = chpos + 12;
    for (short int x = 3; x > -1; x--)
      f << (char) ((length >> 8*x)%256);    

    char middle[8] = {0x00, 0xff, 0x03, 0x01, 0xc7, 0x00, 0xc0, 0x34};
    f.write(middle, 8);

    f.write(data, chpos);

    char end[4] = {0x00, 0xff, 0x2f, 0x00};
    f.write(end, 4);
  }
}
