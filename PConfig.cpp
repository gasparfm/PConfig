/**
*************************************************************
* @file PConfig.cpp
* @brief Reads ini file or inline data and allows access to it
*        Using Glib::KeyFile
*
*
*
* @author Gaspar Fernández <blakeyed@totaki.com>
* @version
* @date 1 sep 2012
* Changelog:
*
*
*
*************************************************************/

#include "PConfig.h"
#include <iostream>

const char *PConfig::DEFAULT_GROUP = "Default";

PConfig::PConfig(std :: string s, PConfig :: InputType inputType, const char * appendGroup)
{
  this->defaultskf=NULL;
  this->kf=NULL;
  this->_error = 0;
  try
    {
      kf = new Glib::KeyFile();
      if (!this->loadKeyFile(this->kf, s, inputType, appendGroup, true))
	return;

      this->groups = kf->get_groups();
    } 
  catch (Glib::FileError e)
    {
      generateError(ERROR_LIB, e.code(), e.what());
    }
  catch (Glib::KeyFileError e)
    {
      generateError(ERROR_LIB, e.code(), e.what());
    }
}

void PConfig::_getInteger(Glib :: KeyFile * kf, string key, void* value, string group)
{
  *(int*)value= kf->get_integer(group, key);
}

void PConfig::_getString(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(string*)value= kf->get_value(group, key);
}

void PConfig::_getInt64(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(gint64*)value= kf->get_int64(group, key);
}

void PConfig::_getUint64(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(guint64*)value= kf->get_uint64(group, key);
}

void PConfig::_getBoolean(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(bool*)value= kf->get_boolean(group, key);
}

void PConfig::_getDouble(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(double*)value= kf->get_double(group, key);
}

bool PConfig::_getValue(string key, void * value, string group, PConfig :: GetterCallback gcb)
{
  if (group.empty())
    group = this->defaultGroup;

  this->_error = 0;

  if (this->kf==NULL)
    {
      this->generateError(ERROR_PCONFIG, 2, "KeyFile not initialized");
      return false;
    }

  try
    {
      if (this->kf->has_key(group, key))
	{
	  (this->*gcb)(this->kf, key, value, group);
	  return true;
	}
      else if ( (this->defaultskf!=NULL) && (this->defaultskf->has_key(group, key)) )
	{
	  (this->*gcb)(this->defaultskf, key, value, group);
	  return true;
	}
      else
	{
	  notFoundKeys.push_back("["+group+"]"+key);
	  return false;
	}
    }
  catch (Glib::KeyFileError e)
    {
      this->generateError(ERROR_LIB, e.code(), e.what());
      return false;
    }
}

void PConfig::generateError(ErrorType et, int code, string errorStr)
{
  this->_errorType = et;
  this->_error = code;
  this->_errorStr = errorStr;
}

bool PConfig::getValue(string key, string & value, string group)
{
    return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getString);
}

bool PConfig::getValue(string key, int & value, string group)
{
    return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getInteger);
}

bool PConfig::getValue(string key, bool & value, string group)
{
  return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getBoolean);
}

bool PConfig::getValue(string key, double & value, string group)
{
  return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getDouble);
}

bool PConfig::getValue(string key, gint64 &value, string group)
{
  return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getInt64);
}

bool PConfig::getValue(string key, guint64 &value, string group)
{
  return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getUint64);
}

string PConfig::getValue(string key, string group)
{
    string value;

    return (getValue(key, value, group))?value:"";
}

int PConfig::getInt(string key, string group)
{
    int value;

    return (getValue(key, value, group))?value:0;
}

double PConfig::getDouble(string key, string group)
{
    double value;

    return (getValue(key, value, group))?value:0;
}

gint64 PConfig::getInt64(string key, string group)
{
    gint64 value;

    return (getValue(key, value, group))?value:0;
}

guint64 PConfig::getUint64(string key, string group)
{
    guint64 value;

    return (getValue(key, value, group))?value:0;
}

bool PConfig::getBoolean(string key, string group)
{
    bool value;

    return (getValue(key, value, group))?value:0;
}

vector < string > PConfig::notFoundKeysList()
{
  return this->notFoundKeys;
}

void PConfig::setDefaultValues(std :: string s, PConfig :: InputType inputType, const char * appendGroup)
{
  try
    {
      this->defaultskf= new Glib::KeyFile();
      this->loadKeyFile(this->defaultskf, s, inputType, appendGroup, false);
    }
  catch (Glib::KeyFileError e)
    {
      this->generateError(ERROR_LIB, e.code(), e.what());
    }
}

bool PConfig::loadKeyFile(Glib::KeyFile *kf, string s, PConfig :: InputType inputType, const char * appendGroup, bool makeDefaultAppendGroup)
{
  string apg;

  if (kf==NULL)
    return false;

  if (inputType==INPUT_FILE)
    kf->load_from_file(s);
  else
    {
      if (appendGroup!=NULL)
	{
	  apg=appendGroup;
	  if (apg.empty())
	    {
	      generateError(ERROR_PCONFIG, 1, "appendGroup cannot be empty");
	      return false;
	    }
	  s="["+apg+"]\n"+s;

	  if (makeDefaultAppendGroup)
	    this->defaultGroup=apg;
	}
      kf->load_from_data(s);
    }
  return true;
}

bool PConfig::getValue(string key, vector < string > & value, string group)
{
    return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getStringList);
}

vector < string > PConfig::getStringList(string key, string group)
{
  vector<string> value;

  if (!getValue(key, value, group))
    value.empty();
  return value;
}

void PConfig::_getStringList(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(vector<string>*)value= kf->get_string_list(group, key);
}

bool PConfig::getValue(string key, vector < bool > & value, string group)
{
    return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getBooleanList);
}

bool PConfig::getValue(string key, vector < int > & value, string group)
{
    return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getIntList);
}

bool PConfig::getValue(string key, vector < double > & value, string group)
{
    return _getValue(key, (void*)&value, group, (GetterCallback)&PConfig::_getDoubleList);
}

vector < bool > PConfig::getBooleanList(string key, string group)
{
  vector<bool> value;

  if (!getValue(key, value, group))
    value.empty();
  return value;
}

vector < int > PConfig::getIntList(string key, string group)
{
  vector<int> value;

  if (!getValue(key, value, group))
    value.empty();
  return value;
}

vector < double > PConfig::getDoubleList(string key, string group)
{
  vector<double> value;

  if (!getValue(key, value, group))
    value.empty();
  return value;
}

void PConfig::_getBooleanList(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(vector<bool>*)value= kf->get_boolean_list(group, key);
}

void PConfig::_getIntList(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(vector<int>*)value= kf->get_integer_list(group, key);
}

void PConfig::_getDoubleList(Glib :: KeyFile * kf, string key, void * value, string group)
{
  *(vector<double>*)value= kf->get_double_list(group, key);
}

PConfig::~PConfig()
{
  if (this->kf!=NULL)
    delete this->kf;
  if (this->defaultskf!=NULL)
    delete this->defaultskf;
}
