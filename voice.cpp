// Clase para almacenar cada una de las voces

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
  unsigned char Pitch(char* &input)
  {
    short int note_pos = -1;
    short int j;
    for (short int i = 0; i < 7 && note_pos == -1; i++)
    {
      bool equal = true;
      for (j = 0; equal && NOTES[i][j] != '\0'; j++)
        equal = input[j] == NOTES[i][j];
      if (equal)
        note_pos = i;
    }

    input += j;

    unsigned char output = (1+2*note_pos-(note_pos > 2)-(note_pos == 6))*4;
    if (output == 0)
      return output;

    bool C_or_higher = output > 20;
    short int flsh = 0;
    if (input[0] == '#' || input[0] == 'b')
      while (flsh < 2 && input[flsh] == input[0])
        output += (input[flsh++] == '#' ? 4 : -4);
        
    input += flsh;

    short int index = output+48*(input[0] - '1' - (C_or_higher));
    if (index < 4 || index > 255)
      return 0;
    else
      output = index;

    input++;
    return output;
  }

  // Obtiene los 2 últimos bits: la duración
  unsigned char Note(char input)
  {
    unsigned char output = ((input == 'c') + 2*(input == 'n') + 3*(input == 'b') + 4*(input == 'r'));
    if (output == 0 && input != 's')
      return 5;

    return output;
  }

public:
  // Pasa a salida estándar los datos
  void Dump() { for (int i = 0; i < length; i++) std::cout << (int) data[i] << ' '; }

  // Rellena los datos de la instancia a partir de datos leídos desde entrada estándar
  bool Set(char input[])
  {
    length = 0;
    unsigned int i_pos = 0;
    unsigned char byte = 0;
    while (length < MAX_LENGTH && input[i_pos] != '\0')
    {
      if (input[i_pos] == '_')
      {
        byte = Note(input[++i_pos]);
        if (byte == 4)
          data[length++] = byte;
        if (byte == 5)
          return false;
        
        data[length++] = byte;
        i_pos++;
      }
      else if (input[i_pos] == '.')
      {
        if (length == 0)
          return false;
        byte = data[length-1]%4;
        if (byte == 0)
          return false;
        
          data[length++] = --byte;
        i_pos++;
      }
      else
      {
        char* rd_pos = input;
        rd_pos += i_pos;
        byte = Pitch(rd_pos);
        if (byte == 0)
          return false;
        i_pos += (rd_pos - input - i_pos);
        unsigned char byte2 = Note(input[i_pos++]);
        if (byte2 == 5)
          return false;
        else if (byte2 == 4)
        {
          byte2--;
          data[length++] = byte + byte2;
          data[length++] = byte2;
        }
        else
          data[length++] = byte + byte2;
      }
      while (input[i_pos] == ' ')
        i_pos++;
    }
    return input[i_pos] == '\0';
  }

  // Devuelve la duración en semicorcheas
  unsigned short int Length(unsigned int pos)
  {
    if (pos >= length)
      return 0;
    unsigned short int rem = data[pos]%4;
    unsigned short int output = 1;
    for (unsigned short int i = 0; i < rem; i++)
      output *= 2;

    return output;
  }

  // Devuelve la posición en la que la nota empezó a sonar
  unsigned short int Source(unsigned short int pos)
  {
    unsigned short int res;
    for (res = pos; res >= 0 && data[res]/4 == 0; res--);
    return res;
  }

  // Devuelve el caracter de la altura MIDI de la nota (do central = 60) 0 30 si es ligadura
  char MIDIpitch(unsigned int pos)
  {
    if (pos >= length)
      return 0;
    return data[pos]/4+30;
  }
};
const char Voice::NOTES[][4] = {"sol", "la", "si", "do", "re", "mi", "fa"};
