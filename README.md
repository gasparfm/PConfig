PConfig
=======

Read and parse ini file or inline data and allows access to its members using Glib::KeyFile
Usefull to load configuration files or passing lots of arguments (even optional arguments) to a function.

## Dependencies
Glibmm-2.4 as it uses Glib::KeyFile to load data

## Example (example2.cpp)
```c++
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
```

## Default values
  You can make a default values configuration using setDefaultValues, so
when a value is not found in the main configuration structure it will
search for it in the default values structure.

## Compilation 

$ g++ -o example example.cpp PConfig.cpp `pkg-config --cflags glibmm-2.4` `pkg-config --libs glibmm-2.4`
