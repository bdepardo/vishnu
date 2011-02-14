/**
* \file utilServer.cpp
* \brief This file implements the utils functions of server objects
* \author Eugène PAMBA CAPO-CHICHI (eugene.capochichi@sysfera.com)
* \date 31/01/2001 
*/

#include "utilServer.hh"
#include "UMSVishnuException.hh"

std::string Vishnuid::mvishnuid = "";
/**
* \brief Function to convert a string to int 
* \fn    std::string convertToString(const T& val);
* \param  val a value to convert to string
* \return int value of the corresponding string
*/
int utilServer::convertToInt(std::string val) {
  int intValue;
  std::istringstream str(val); 
  str >> intValue;
  return static_cast<int> (intValue);
}
