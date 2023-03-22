#include "Tasks.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

void MenuTask() {
  cout << "     Menu Task   \n";
  cout << "    1.  Exersice 1  \n";
  cout << "    2.  Exersice 2 \n";
  cout << "    3.  Exersice 3 \n";
  cout << "    4.  Exersice 4 \n";
  cout << "    5.  Exit \n";
}

// (15 * a + 312 * b)/64 - c * 120 + d * 121
// (a * 2^4 - a + 2^8 * b + 56 * b)/ 2^6 - c * 2^7 + c * 2^3 + d * 2^7 - d * 2^3
// + d (a * 2^4 - a + 2^8 * b + 2^6 * b - 2^3 * b)/ 2^6 - c * 2^7 + c * 2^3 + d
// * 2^7 - d * 2^3 + d
// ((a<<4) - a + (b<<8) + (b<<6) - (b<<3))>>6 - (c<<7) + (c<<3) + (d<<7) -
// (d<<3) + d

int task1() {
  // Обчислення виразів з використанням побітових операцій
  int a, b, c, d;
  double x, y;
  cout << "Enter a, b, c, d:";
  cin >> a >> b >> c >> d;
  x = (((a << 4) - a + (b << 8) + (b << 6) - (b << 3)) >> 6) - (c << 7) +
      (c << 3) + (d << 7) - (d << 3) + d;
  y = (15 * a + 312 * b) / 64 - c * 120 + d * 121;
  cout << "Result with bit operation:" << x << endl;
  cout << "Result:" << y << endl;
  return 0;
}


/*Задано текст ASCII (текстовий рядок), який складається з 64 букв.
Написати функції шифрування та розшифрування заданого тексту.
Кожна при шифруванні буква тексту буде записана у елемент,
який складається з двох байтів та має структуру:
  -  у бітах 0-1 знаходиться номер рядка символу букви (2 біти),
  -  у бітах 2-6 позиція символу в рядку (5 біти),
  -  у бітах 7-14 ASCII - код символу (8 біт),
  - 15 біт - біт парності (1 біт). */

void MyEncryption(char InS[32], unsigned short OutCoding[32], int row) {
  unsigned char c;
  unsigned short r, t, b;
  short j;
  for (int i = 0; i < 32; i++) {
    r = 0;      // 0000 0000 0000 0000
    c = InS[i]; // s - 0x73 = 0111 0011
    t = c;
    r |= t << 1; // 0000 0000 1110 0110
    r |= i << 9; // 0000 0000 1110 0110  if i=5 -> 0000 1010 1110 0110
    t = c;
    t = 1;
    b = 0;
    for (j = 0; j < 16; j++) // обчислення біта парності
    {
      if (r & t) {
        if (b == 0)
          b = 1;
        else
          b = 0;
      }
      t <<= 1;
    }
    r |= row << 14;
    r |= b; // 0000 1010 1110 0110 if i=5 0000 1010 1110 0111
    OutCoding[i] = r;
  }
}

void MyDecryption(char OutS[32], unsigned short InCoding[32]) {
  unsigned char c;
  unsigned short r, t, i, b, p, w;
  short j;
  for (i = 0; i < 32; i++) //
  {
    // Перевірка парності
    r = InCoding[i];

    t = r & 0b1111111111111111; //  0xf7ff			1111 0111 1111
                                //  1111
    p = r & 0b0000100000000000; //  0x0800			0000 1000 0000
                                //  0000
    w = 1;
    b = 0;
    for (j = 0; j < 16; j++) // обчислення біта парності
    {
      if (t & w) {
        if (b == 0)
          b = 1;
        else
          b = 0;
      }
      w <<= 1;
    }
    p >>= 11;
    t = r & 0b1110000000000000; // 0xf000
    t >>= 13;
    w = r & 0b0001111000000000; // 0x000f
    w <<= 3;
    t |= w;
    p = r & 0b0000000111111110; // 0x07f
    p >>= 1;
    OutS[i] = (unsigned char)p;
  }
}

/*Задано 4 рядки тексту. У рядку до 32 символів. Доповнити пробілами рядки до 32 символів.
Шифрувати тексти таким чином, щоб кожний символ тексту записувався у два байти. Два байти
мають таку структуру:
  -  у бітах 0-1 знаходиться номер рядка символу букви (2 біти),
  -  у бітах 2-6 позиція символу в рядку (5 біти),
  -  у бітах 7-14 ASCII - код символу (8 біт),
  - 15 біт - біт парності (1 біт). */

void task2() {
  // Шифрування даних з використання побітових операцій
  // Data encryption using bitwise operations

  char choice;
  cout << " Data encryption using bitwise operations  \n";
  char S2[4][32] = {'\0'};
  unsigned short Rez[32];
  unsigned short i, f;
  cout << "1. Enter the into bin file \n";
  cout << "2. Read from bin file \n";
  cin >> choice;

  switch (choice) {
  case '1': {
    cout << " Input string (size <=32) \n";
    for (int i = 0; i < 4; i++) {
      cin >> S2[i];
    }

    ofstream ofsb("outb.bin", ios::app | ios::binary);
    for (int i = 0; i < 4; i++) {
      int n = strlen(S2[i]);
      cout << S2[i] << endl;
      MyEncryption(S2[i], Rez, i);
      ofsb.write((char *)Rez, 32 * sizeof(unsigned short));
      cout << "Data write to outb.bin " << endl;
      for (int i = 0; i < n; i++) {
        bitset<16> x(Rez[i]);
        cout << x << '\n';
      };

      for (int i = 0; i < 32; i++) {
        Rez[i] = '\0';
      }

      cout << endl;
    }
    ofsb.close();
    break;
  }
  case '2': {
    char S[32]{'\0'};
    ofstream ofs("out.txt");
    if (!ofs) {
      cout << "File out.txt not open" << endl;
      return;
    }
    ifstream ifsb("outb.bin", ios::in | ios::binary);
    if (!ifsb) {
      cout << "File outb.bin not open" << endl;
      return;
    }
    for (int i = 0; i < 4; i++) {
      unsigned short InBin[32]{'\0'};
      if (i) {
        ifsb.seekg(64 * i);
      }
      ifsb.read((char *)InBin, 32 * sizeof(unsigned short));

      MyDecryption(S, InBin);
      cout << "String  " << S << endl;
      ofs << S << endl;
    }
    ifsb.close();
    break;
  }
  default:
    break;
  }
}

//   1          2        3       4
// 01001111 01111011 10000000 01000000 01000000 01000000 01000000 01000000
// 01000000
//                    0        1        1        1        1        0         1 1

void task3() {
  // Шифрування даних з використання стуктур з бітовими полями
  // Data encryption using structures with bit fields
  cout << "  Data encryption using structures with bit fields \n";
}

void task4() { // Задача із використання побітових операцій
  // The problem of using bitwise operations
  cout << " Data encryption using structures with bit fields \n";
}
