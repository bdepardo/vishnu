/**
* \file utilVishnu.cpp
* \brief This file implements the utils functions of the vishnu system
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 15/02/2011
*/

#include "utilVishnu.hpp"
#include "POSTGREDatabase.hpp"
#include "DbFactory.hpp"
#include "DatabaseResult.hpp"

/**
* \brief Function to convert a string to int
* \fn    std::string convertToString(const T& val);
* \param  val a value to convert to string
* \return int value of the corresponding string
*/
int
vishnu::convertToInt(std::string val) {
  int intValue;
  std::istringstream str(val);
  str >> intValue;
  return intValue;
}

std::string
vishnu::cryptPassword(const std::string& salt, const std::string password) {

  std::string saltTmp="$6$"+salt+"$";
  std::string encryptedPassword=crypt(password.c_str(),saltTmp.c_str());

 return encryptedPassword.substr(saltTmp.size());
}

/**
* \brief Function to get a random number
* \fn    int generate_numbers()
* \return the number generated
*/
int
vishnu::generate_numbers() {

  boost::mt19937 gen;
  gen.seed(static_cast<boost::uint32_t>(std::time(0)));
  boost::uniform_int<> dist(1, 100000);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);
  return die();
}

/**
* \brief Function to get a random number
* \fn    int isMonth (const char * s)
* \return
*/
int
vishnu::isMonth (const char * s) {
  return (s[0]=='M' && s[1]=='O' && s[2]=='N' && s[3]=='T' && s[4]=='H');
}
int
vishnu::isYear (const char * s) {
  return (s[0]=='Y' && s[1]=='E' && s[2]=='A' && s[3]=='R');
}
int
vishnu::isSite (const char * s) {
  return (s[0]=='S' && s[1]=='I' && s[2]=='T' && s[3]=='E');
}
int
vishnu::isType (const char * s) {
  return (s[0]=='T' && s[1]=='Y' && s[2]=='P' && s[3]=='E');
}
int
vishnu::isUName (const char * s) {
  return (s[0]=='U' && s[1]=='N' && s[2]=='A' && s[3]=='M' && s[4]=='E');
}
int
vishnu::isMaName (const char * s) {
  return (s[0]=='M' && s[1]=='A' && s[2]=='N' && s[3]=='A' && s[4]=='M' && s[5]=='E');
}
int
vishnu::isDay (const char * s) {
  return (s[0]=='D' && s[1]=='A' && s[2]=='Y');
}
int
vishnu::isCpt (const char * s) {
  return (s[0]=='C' && s[1]=='P' && s[2]=='T');
}

/**
* \brief Parse the format and fill the array with the variable and their value
* \fn void getKeywords(int* size, Format_t* array,
*                      const char* format,
*                      int cpt, IdType type,
*                      std::string name,
*                      std::string site)
* \param size Size of the array (OUT)
* \param array Array to fill with variables and their value (OUT)
* \param format The string to parse
* \param cpt Value of the counter variable
* \param type Type of the id to generate
* \param name Name of the user or machine
* \param site Site of the machine
* \return 0 on success and -1 when an error occurs
*/
int
vishnu::getKeywords (int* size, Format_t* array, const char* format, int cpt, IdType type,
      std::string name, std::string site) {
  unsigned int i;
  *size = 0;

  char day[4];
  char month[4];
  char year[4];

  char buf[500];
  memset (buf, 0, 500);

  //the current time
  ptime now = microsec_clock::local_time();

  struct tm tmtime = to_tm(now);
  strftime (year, 3, "%y", &tmtime);
  strftime (month, 3, "%m", &tmtime);
  strftime (day, 3, "%d", &tmtime);

  // Loop parsing for the variables, setting their position and their value
  for (i=0;i<strlen (format);i++){
    if (format[i]=='$'){
      if (isDay (format+i+1)){
        array[*size].start = i;
        array[*size].end = i+3;
        array[*size].value.append (std::string (day));
        (*size) ++;
            }else if (isMonth (format+i+1)){
        array[*size].value = std::string (month);
        array[*size].start = i;
        array[*size].end = i+5;
        (*size) ++;
            }else if (isYear (format+i+1)){
        array[*size].start = i;
        array[*size].end = i+4;
        array[*size].value = std::string (year);
        (*size) ++;
            }else if (isCpt (format+i+1)){
        char tmp[10];
        sprintf (tmp, "%d", cpt);
        array[*size].value = std::string (tmp);
        array[*size].start = i;
        array[*size].end = i+3;
        (*size) ++;
            }else if (isSite (format+i+1)){
        array[*size].value = site;
        array[*size].start = i;
        array[*size].end = i+4;
        (*size) ++;
            }else if (isMaName (format+i+1)){
        array[*size].value = name;
        array[*size].start = i;
        array[*size].end = i+6;
        (*size) ++;
            }else if (isUName (format+i+1)){
        array[*size].value = name;
        array[*size].start = i;
        array[*size].end = i+5;
        (*size) ++;
      } else if (isType (format+i+1)) {
                switch (type){
                  case 0 :
                    array[*size].value = "M";
                    break;
                  case 1 :
                    array[*size].value = "U";
                    break;
                  case 2 :
                    array[*size].value = "J";
                    break;
                  case 3 :
                    array[*size].value = "F";
                    break;
                }
                array[*size].start = i;
                array[*size].end = i+4;
                (*size) ++;
      }
      else {
        return -1;
      }
    }
  }
  return 0;
}

/**
* \brief Function to generate an ID
* \fn std::string getGeneratedName (const char* format,
*                                   int cpt,
*                                   IdType type,
*                                   std::string name = "",
*                                   std::string site ="")
* \param format Format to use to generate the id
* \param cpt Value of the counter to use
* \param type Type of the id generated
* \param name Name of the user or machine (optionnal)
* \param site Site of the machine (optionnal)
*/
std::string
vishnu::getGeneratedName (const char* format, int cpt, IdType type,
      std::string name , std::string site ) {

  std::string res;
  res.clear ();
  res = std::string ("");
  int  i;
  int  size;
  Format_t *keywords;


  keywords = new Format_t[strlen(format)+1];
  int ret = getKeywords (&size, keywords, format, cpt, type, name, site); // Getting var and their value

  // if there is no error with the getKeywords function
  if (ret != -1) {
    // Building the id using the format and the values of the var
    if (size>0)
      res.append (format, keywords[0].start);
    else
      res = std::string (format);
    for (i=0;i<size;i++){
      res.append (keywords[i].value);
      // If other variables
      if (*(format+keywords[i].end+1) != '\0' && i!=size-1)
        res.append (format+keywords[i].end+1, keywords[i+1].start-keywords[i].end-1);
      // If text after the variable
      else if (*(format+keywords[i].end+1) != '\0' ){
        res.append (format+keywords[i].end+1, strlen (format)-keywords[i].end-1);
      }
    }
  }

  return res;
}

/**
* \brief Function to get information from the table vishnu
* \fn    string getAttrVishnu(string attrname, string vishnuid)
* \param attrname the name of the attribut
* \param vishnuid the id of the vishnu configuration
* \return the corresponding attribut
*/
std::string
vishnu::getAttrVishnu(std::string attrname, std::string vishnuid) {

  DbFactory factory;
  Database *databaseVishnu;
  DatabaseResult *result;

  std::string sqlCommand("SELECT "+attrname+" FROM vishnu where vishnuid="+vishnuid);

  databaseVishnu = factory.getDatabaseInstance();
  result = databaseVishnu->getResult(sqlCommand.c_str());
  return result->getFirstElement();

}
/**
* \brief Function to increment a counter of the table vishnu
* \fn    incrementCpt(std::string cptName, int cpt)
* \param cptName the name of the counter to increment
* \param cpt     the current value of the counter
* \return raises an exception
*/
void
vishnu::incrementCpt(std::string cptName, int cpt) {

  DbFactory factory;
  Database *databaseVishnu;

  cpt = cpt+1;

  std::string sqlCommand("UPDATE vishnu set "+cptName+"="+vishnu::convertToString(cpt));

  databaseVishnu = factory.getDatabaseInstance();
  databaseVishnu->process(sqlCommand.c_str());

}


