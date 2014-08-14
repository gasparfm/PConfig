/**
*************************************************************
* @file main.cpp
* @brief Breve descripción
* Pequeña documentación del archivo
*
*
*
*
*
* @author Gaspar Fernández <blakeyed@totaki.com>
* @version
* @date 16 sep 2013
* Historial de cambios:
*
*
*
*
*
*
*
*************************************************************/

#include <iostream>
#include "PConfig.h"

int main(int argc, char *argv[])
{
  PConfig pcfg(
"Logging = 1\n"
"URL = http://totaki.com/poesiabinaria\n"
"Author = Gaspar Fernández\n"
"[Database]\n"
"Host=localhost\n"
"Username=root\n"
"Password=12345\n"
"Port=5555\n"
"Tables=Users;Mailing;Queue;Jobs\n"
"[Lottery]\n"
"Numbers=6;5;1;9;10;33;23;43;1", PConfig::INPUT_STRING);
  if (pcfg.ok())
    {
      vector<int>numbers = pcfg.getIntList("Numbers", "Lottery");
      vector<string>tables = pcfg.getStringList("Tables", "Database");
      cout << "URL: "<<pcfg.getValue("URL")<<endl;
      cout << "Logging: "<<pcfg.getInt("Logging")<<endl;
      cout << "Tables: ";
      for (int i=0; i<tables.size(); ++i)
	cout << ((i>0)?", ":"") << (i+1) << " ("<<tables[i]<<")";
      cout << endl;
      cout << "Numbers: ";
      for (int i=0; i<numbers.size(); ++i)
	cout << ((i>0)?", ":"") << (i+1) << " ("<<numbers[i]<<")";
      cout << endl;
    }
  else
    cout << "Fail: "<<pcfg.errorType()<<" "<<pcfg.errorCode()<<": "<<pcfg.errorStr()<<endl;

  return EXIT_SUCCESS;
}

