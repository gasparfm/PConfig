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
#include <string>

using namespace std;

class Connection
{
public:
  Connection(string settings)
  {
    PConfig cfg(settings, PConfig::INPUT_STRING);
    cfg.setDefaultValues("Port=1234\nMethod=socket\nCompression=true", PConfig::INPUT_STRING);
    host = cfg.getValue("Host");
    port = cfg.getValue<int>("Port");
    method = cfg.getValue<string>("Method");
    compression = cfg.getValue<bool>("Compression");
  }

  ~Connection()
  {
  }

  string getHost()
  {
    return host;
  }

  int getPort()
  {
    return port;
  }

  string getMethod()
  {
    return method;
  }

  bool getCompression()
  {
    return compression;
  }

private:
  string host;
  int port;
  string method;
  bool compression;
};

int main(int argc, char *argv[])
{
  Connection conn("Port=4321\nHost=localhost");
  cout << "HOST: "<<conn.getHost()<<endl;
  cout << "PORT: "<<conn.getPort()<<endl;
  cout << "METHOD: "<<conn.getMethod()<<endl;
  cout << "COMPRESS: "<<conn.getCompression()<<endl;

  return EXIT_SUCCESS;
}

