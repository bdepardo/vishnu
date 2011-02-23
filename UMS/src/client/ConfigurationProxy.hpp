/**
  * \file configurationProxy.hpp
  * \brief This file contains the VISHNU configurationProxy class.
  * \authors Daouda Traore (daouda.traore@sysfera.com)
  * \date February 2011
  */
#ifndef _CONFIGURATION_PROXY_H_
#define _CONFIGURATION_PROXY_H_

#include <string>
#include <vector>
#include <list>
#include <iostream>

#include "SessionProxy.hpp"
#include "Configuration.hpp"

/**
 * \class ConfigurationProxy 
 * \brief ConfigurationProxy class implementation 
 */
class ConfigurationProxy
{
 
public:
  
   /**
   * \fn ConfigurationProxy(const std::string& filePath,
   *                        const SessionProxy& session)
   * \param filePath The file containing the configuration (serialized)
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \brief Constructor, raises an exception on error
   */
  ConfigurationProxy(const std::string& filePath, const SessionProxy& session);
  /**
   * \fn ConfigurationProxy(UMS_Data::Configuration* config,
   *                        const SessionProxy& session)
   * \param config The object which encapsulates the configuration description 
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \brief Constructor, raises an exception on error
   */
  ConfigurationProxy(UMS_Data::Configuration* config, const SessionProxy& session);
  /**
   * \brief Function to save the configuration of VISHNU 
   * \fn  int save()
   * \return raises an exception on error
   */
  int save();
  /**
   * \brief Function to restore the configuration of VISHNU from a file 
   * \fn  int restoreFromFile()
   * \return raises an exception on error
   */
  int restoreFromFile();
  /**
   * \brief Function to restore the configuration of VISHNU from an object (Data) 
   * \fn  int restoreFromFile()
   * \return raises an exception on error
   */
  int restoreFromData();
  /**
   * \brief Function get the saved configuration of VISHNU 
   * \fn  UMS_Data::Configuration* getData()
   * \return saved configuration 
   * \return raises an exception on error
   */
  UMS_Data::Configuration* getData();
  /**
   * \brief Function get SessionProxy object which contains the VISHNU session identifier 
   * \fn SessionProxy getSessionProxy() 
   * \return a SessionProy object which contains the VISHNU session information 
   * \return raises an exception on error
   */
  SessionProxy getSessionProxy();
  /**
   * \fn ~ConfigurationProxy()
   * \brief Destructor, raises an exception on error
   */
  ~ConfigurationProxy();

private:
  /**
   * \brief Function to combine restoreFromFile() and restoreFromData() into one function 
   * \fn  int restore(bool fromFile=true)
   * \param fromFile To select the call of restoreFromFile or restoreFromData function 
   * \return raises an exception on error
   */
  int restore(bool fromFile=true);
     
  /////////////////////////////////
  // Attributes
  /////////////////////////////////

 /**
  * \brief A pointer on the Configuration object
  */ 
  UMS_Data::Configuration *mconfiguration;
 /**
  * \brief The SessionProxy object containing the encrypted identifier of the session
  *  generated by VISHNU
  */
  SessionProxy msessionProxy;
 /**
  * \brief the file containing the configuration (serialized)
  */
  std::string mfilePath;
};
#endif
