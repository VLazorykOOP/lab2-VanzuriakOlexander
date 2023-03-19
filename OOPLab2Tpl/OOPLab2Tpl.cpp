// OOPLab2Tpl.cpp : Этот файл содержит функцию "main". Здесь начинается и
// заканчивается выполнение программы.
//

#include "Tasks.h"
#include <iostream>

using namespace std;

/// @brief
/// @return
int main() {
  cout << "OOP. Template for laboratory work #2.\n";

  char ch = '5';
  do {
    system("cls");
    MenuTask();
    ch = cin.get();

    cin.get();

    switch (ch) {
    case '1':
      task1();
      return 0;
      break;
    case '2':
      task2();
      return 0;
      break;
    case '3':
      task1();
      break;
    case '4':
      task1();
      break;
    case '5':
      break;
    case '6':
      return 0;
    }
    cout << " Press any key and enter\n";
    ch = cin.get();
  } while (ch != '6');

  return 0;
}
