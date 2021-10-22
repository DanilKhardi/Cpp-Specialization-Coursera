/*
Определите тип Incognizable, для которого
следующий код будет корректен:

 	 int main() {
  	 Incognizable a;
  	 Incognizable b = {};
  	 Incognizable c = {0};
  	 Incognizable d = {0, 1};
  	 return 0;
	 }
*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Incognizable {
	int first = 0;
	int second = 0;
};

//int main() {
//  Incognizable a;
//  Incognizable b = {};
//  Incognizable c = {0};
//  Incognizable d = {0, 1};
//  return 0;
//}
