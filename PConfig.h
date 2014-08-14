/*
Copyright (c) 2012 Gaspar Fernández

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <glibmm.h>
#include <string>
#include <vector>

using namespace std;

class PConfig
{
 public:
  enum InputType
  {
    INPUT_FILE,
    INPUT_STRING
  };

  enum ErrorType
  {
    ERROR_LIB,			/* Error triggered by used library */
    ERROR_PCONFIG		/* Error triggered by this class */
  };

  static const char* DEFAULT_GROUP;

  PConfig(std::string s, PConfig::InputType inputType=INPUT_FILE, const char* appendGroup=DEFAULT_GROUP);
  ~PConfig();

  void setDefaultValues(std::string s, PConfig::InputType inputType=INPUT_FILE, const char* appendGroup=DEFAULT_GROUP);

  inline int ok()
  {
    return (this->_error==0);
  }

  inline int errorCode()
  {
    return this->_error;
  }

  inline string errorStr()
  {
    return this->_errorStr;
  }

  inline ErrorType errorType()
  {
    return this->_errorType;
  }

  bool getValue(string key, string &value, string group="");
  bool getValue(string key, int &value, string group="");
  bool getValue(string key, bool &value, string group="");
  bool getValue(string key, gint64 &value, string group="");
  bool getValue(string key, guint64 &value, string group="");
  bool getValue(string key, double &value, string group="");
  bool getValue(string key, vector<string> &value, string group="");
  bool getValue(string key, vector<bool> &value, string group="");
  bool getValue(string key, vector<int> &value, string group="");
  bool getValue(string key, vector<double> &value, string group="");

  string getValue(string key, string group="");
  int getInt(string key, string group="");
  double getDouble(string key, string group="");
  gint64 getInt64(string key, string group="");
  guint64 getUint64(string key, string group="");
  bool getBoolean(string key, string group="");
  vector<string> getStringList(string key, string group="");
  vector<bool> getBooleanList(string key, string group="");
  vector<int> getIntList(string key, string group="");
  vector<double> getDoubleList(string key, string group="");

  vector<string> notFoundKeysList();

  template <typename T>
    T getValue(string key, string group="")
    {
      T temp;
      getValue(key, temp, group);
      return temp;
    }

 private:

  typedef void(PConfig::*GetterCallback)(Glib::KeyFile*, string, void*, string);

  ErrorType _errorType;
  int _error;
  string _errorStr;
  string defaultGroup;

  Glib::KeyFile *kf;
  Glib::KeyFile *defaultskf;
  vector<Glib::ustring> groups;
  vector<string> notFoundKeys;

  bool loadKeyFile(Glib::KeyFile *kf, string s, PConfig::InputType inputType, const char* appendGroup, bool makeDefaultAppendGroup);
  void generateError(ErrorType et, int code, string errorStr);
  bool _getValue(string key, void *value, string group, PConfig::GetterCallback gcb);
  void _getString(Glib :: KeyFile * kf, string key, void *value, string group);
  void _getInteger(Glib :: KeyFile * kf, string key, void *value, string group);
  void _getInt64(Glib :: KeyFile * kf, string key, void *value, string group);
  void _getUint64(Glib :: KeyFile * kf, string key, void *value, string group);
  void _getBoolean(Glib :: KeyFile * kf, string key, void *value, string group);
  void _getDouble(Glib :: KeyFile * kf, string key, void *value, string group);
  void _getStringList(Glib::KeyFile *kf, string key, void *value, string group);
  void _getBooleanList(Glib::KeyFile *kf, string key, void *value, string group);
  void _getIntList(Glib::KeyFile *kf, string key, void *value, string group);
  void _getDoubleList(Glib::KeyFile *kf, string key, void *value, string group);
};

