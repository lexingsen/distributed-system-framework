#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <iostream>
using namespace std;

#define LOG(str) \
  cout << __FILE__ << ":" << __LINE__ << __TIMESTAMP__ \
  << " " << str << endl;


#endif