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
  cout << "" << x << endl;
  cout << y << endl;
  return 0;
}

void MyEncryption(char InS[64], unsigned short OutCoding[64], int row) {
  unsigned char c;
  unsigned short r, t, b;
  short j;
  for (int i = 0; i < 64; i++) {
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

int MyDecryption(char OutS[64], unsigned short InCoding[64]) {
  unsigned char c;
  unsigned short r, t, i, b, p, w;
  short j;
  for (i = 0; i < 64; i++) //
  {
    // Перевірка парності
    r = InCoding[i];
    bitset<16> x(r);
    cout << x << '\n';
    t = r & 0b1111011111111111; //  0xf7ff			1111 0111 1111
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
    if (p != b)
      return -i;
    t = r & 0b1111000000000000; // 0xf000
    t >>= 12;
    w = r & 0b0000000000001111; // 0x000f
    w <<= 4;
    t |= w;
    p = r & 0b0000011111110000; // 0x07f
    p >>= 4;
    OutS[p] = (unsigned char)t;
  }
  return 1;
}

void task2() {
  // Шифрування даних з використання побітових операцій
  // Data encryption using bitwise operations
  // cout << " Data encryption using bitwise operations  \n";
  // char S2[4][32] = {'\0'};
  // unsigned short Rez[32];
  // unsigned short i, f;
  // cout << " Input string (size <=64) \n";
  // for (int i = 0; i < 4; i++) {
  //   cin >> S2[i];
  // }

  // for (int i = 0; i < 4; i++) {

  //   int n = strlen(S2[i]);
  //   MyEncryption(S2[i], Rez, i);
  //   ofstream ofsb("outb.bin", ios::app | ios::binary);
  //   if (!ofsb) {
  //     cout << "File outb.bin not open" << endl;
  //   } else {
  //     ofsb.write((char*)Rez, 32 * sizeof(unsigned short));
  //     ofsb.close();
  //     cout << "Data write to outb.bin " << endl;
  //   }
  //   for (int i = 0; i < n; i++) {
  //     bitset<16> x(Rez[i]);
  //     cout << x << '\n';
  //   };


  //   cout << endl;
  // }

  char S[65];
  unsigned short InBin[64]{};
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
  ifsb.read((char *)InBin, 64 * sizeof(unsigned short));
  ifsb.close();
  cout << "Data read from outb.bin " << endl;

  int r;
  r = MyDecryption(S, InBin);
  if (r < 1) {
    cout << "Error  read  " << r << " row " << endl;
  }
  cout << "String  " << S << endl;
  ofs << S << endl;
}

void task3() {
  // Шифрування даних з використання стуктур з бітовими полями
  // Data encryption using structures with bit fields
  cout << "  Data encryption using structures with bit fields \n";
}

void task4() { // Задача із використання побітових операцій
  // The problem of using bitwise operations
  cout << " Data encryption using structures with bit fields \n";
}
