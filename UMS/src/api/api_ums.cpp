/**
 * \file api_ums.cpp
 * \brief This file contains the VISHNU api functions.
 * \author Daouda Traore (daouda.traore@sysfera.com) and Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 * \date February 2011
 */

#include "api_ums.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "SessionProxy.hpp"
#include "MachineProxy.hpp"
#include "LocalAccountProxy.hpp"
#include "ConfigurationProxy.hpp"
#include "OptionValueProxy.hpp"
#include "QueryProxy.hpp"
#include "UtilsProxy.hpp"
#include "utilVishnu.hpp"
#include "NetrcReader.hpp"

using namespace std;

/**
 * \brief Function to open a session
 * \param userId The VISHNU user identifier
 * \param password The password of the user
 * \param session is an object containing the encrypted identifier of the session generated by VISHNU
 * \param connectOpt To encapsulate the options available for the connect method. It allows the user
 *  to choose the way for way for closing the session automatically on TIMEOUT or on DISCONNECT and the
 *  possibility for an admin to open a session as she was a specific user
 *  \return raises an exception on error
 */
int
vishnu::connect(const string& userId,
                const string& password,
                UMS_Data::Session& session,
                const UMS_Data::ConnectOptions& connectOpt)
                                                          throw(UserException, SystemException)
{

  if((connectOpt.getClosePolicy() < 0) || (connectOpt.getClosePolicy() > 2)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_CLOSURE_MODE, "Invalid ClosePolicy value: its value must be 0, 1 or 2");
  }

  string connectLogin;
  string connectPassword;

  //If the userId and the password is undefined the netrc file is used
  if ((userId.empty()) && (password.empty())) {
    NetrcReader netrcReader;
    netrcReader.read(connectLogin, connectPassword);
  } else {
   connectLogin = userId;
   connectPassword = password;
  }

  std::string encryptedPassword = vishnu::cryptPassword(connectLogin, connectPassword);

  UserProxy userProxy(connectLogin, encryptedPassword);
  SessionProxy sessionProxy;
  int res = sessionProxy.connect(userProxy, connectOpt);

  session = sessionProxy.getData();

  return res;

}

/**
 * \brief Function to return the sessionKey of a session in which the user was disconnected previously without closing it
 * \param userId represents the VISHNU user identifier
 * \param password represents the password of the user
 * \param sessionId is the identifier of the session defined in the database
 * \param session is an object containing the encrypted identifier of the session generated by VISHNU and the close policy value
 * \return raises an exception on error
 */
int
vishnu::reconnect(const string& userId,
                  const string& password,
                  const string& sessionId,
                  UMS_Data::Session& session)
                                            throw(UserException, SystemException)
{

  string connectLogin;
  string connectPassword;

  //If the userId and the password is undefined the netrc file is used
  if ((userId.empty()) && (password.empty())) {
    NetrcReader netrcReader;
    netrcReader.read(connectLogin, connectPassword);
  } else {
   connectLogin = userId;
   connectPassword = password;
  }

  std::string encryptedPassword = vishnu::cryptPassword(connectLogin, connectPassword);

  UserProxy userProxy(connectLogin, encryptedPassword);
  session.setSessionId(sessionId);
  SessionProxy sessionProxy(session);

  int res = sessionProxy.reconnect(userProxy);

  session = sessionProxy.getData();

  return res;
}

/**
 * \brief Function to close the session identfied by the session key
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \return raises an exception on error
 */
int
vishnu::close(const string&  sessionKey)
                                       throw(UserException, SystemException)
{

  return SessionProxy(sessionKey).close();
}

/**
 * \brief Function to add a new user in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newUser is an object containing the new user information
 * \return raises an exception on error
 */
int
vishnu::addUser(const string& sessionKey, UMS_Data::User& newUser)
                                                                 throw(UserException, SystemException)
{

  if((newUser.getPrivilege() < 0) || (newUser.getPrivilege() > 1)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_OPTION, "Invalid Privilege value: its value must be 0 or 1");
  }
  if((newUser.getStatus() < 0) || (newUser.getStatus() > 1)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_OPTION, "Invalid Status value: its value must be 0 or 1");
  }

  checkIfTextIsEmpty(newUser.getFirstname(), "The user firstname is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newUser.getLastname(), "The user lastname is empty", ERRCODE_INVALID_PARAM);
  checkEmail(newUser.getEmail());

  SessionProxy sessionProxy(sessionKey);
  UserProxy userProxy(sessionProxy);
  int res = userProxy.add(newUser);

  return res;
}

/**
 * \brief Function to update the user information except the userId and the password
                                       std::cout << "type "  << newAuthSys.getType() << "\n";                                 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param user is an object containing the new user information
 * \return raises an exception on error
 */
int
vishnu::updateUser(const string& sessionKey,
                   const UMS_Data::User& user)
                                             throw(UserException, SystemException)
{

  if((user.getPrivilege() < 0) || (user.getPrivilege() > 1)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_OPTION, "Invalid Privilege value: its value must be 0 or 1");
  }

  SessionProxy sessionProxy(sessionKey);
  UserProxy userProxy(sessionProxy);

  return userProxy.update(user);
}

/**
 * \brief Function to remove a user from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param userId represents the VISHNU user identifier of the user who will be deleted from VISHNU
 * \return raises an exception on error
 */
int
vishnu::deleteUser(const string& sessionKey,
                   const string& userId)
                                       throw(UserException, SystemException)
{

  UMS_Data::User user;
  user.setUserId(userId);
  SessionProxy sessionProxy(sessionKey);
  UserProxy userProxy(sessionProxy);

  return userProxy.deleteUser(user);
}

/**
 * \brief Function to change the password
 * \param userId represents the VISHNU user identifier
 * \param password represents the password of the user
 * \param passwordNew represents the new password of the user
 * \return raises an exception on error
 */
int
vishnu::changePassword(const std::string& userId,
                       const std::string& password,
                       const std::string& passwordNew)
                                                     throw(UserException, SystemException)
{

  checkIfTextIsEmpty(passwordNew, "The new password is empty", ERRCODE_INVALID_PARAM);

  UMS_Data::User user;
  user.setUserId(userId);
  UserProxy userProxy(user);

  std::string encryptedPassword = vishnu::cryptPassword(userId, password);
  std::string encryptedPasswordNew = vishnu::cryptPassword(userId, passwordNew);

  return userProxy.changePassword(encryptedPassword, encryptedPasswordNew);
}

/**
 * \brief Function to reset the password of a user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param userId represents represents the VISHNU user identifier of the user whose password will be reset
 * \return raises an exception on error
 */
int
vishnu::resetPassword(const std::string& sessionKey,
                      const std::string& userId,
                      std::string& tmpPassword)
                                             throw(UserException, SystemException)
{

  UMS_Data::User user;
  user.setUserId(userId);
  SessionProxy sessionProxy(sessionKey);
  UserProxy userProxy(sessionProxy);

  int res = userProxy.resetPassword(user);
  tmpPassword = (userProxy.getData()).getPassword();
  return res;
}

/**
 * \brief Function to add a new machine in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newMachine is an object which encapsulates the information of the machine which will be added in VISHNU except the
 * machine id which will be created automatically by VISHNU
 * \return raises an exception on error
 */
int
vishnu::addMachine(const std::string& sessionKey,
                   UMS_Data::Machine& newMachine)
                                                throw(UserException, SystemException)
{

  if((newMachine.getStatus() < 0) || (newMachine.getStatus() > 1)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_OPTION, "Invalid Status value: its value must be 0 or 1");
  }

  checkIfTextIsEmpty(newMachine.getName(), "The machine name is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newMachine.getSite(), "The machine site is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newMachine.getLanguage(), "The machine language is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newMachine.getSshPublicKey(), "The machine sshPublicKeyFile is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newMachine.getMachineDescription(), "The machine description is empty", ERRCODE_INVALID_PARAM);

  SessionProxy sessionProxy(sessionKey);
  MachineProxy machineProxy(newMachine, sessionProxy);
  int res = machineProxy.add();
  newMachine = machineProxy.getData();

  return res;
}

/**
 * \brief Function to update machine description
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param machine is an existing machine information
 * \return raises an exception on error
 */
int
vishnu::updateMachine(const std::string& sessionKey,
                      const UMS_Data::Machine& machine)
                                                      throw(UserException, SystemException)
{

  if((machine.getStatus() < 0) || (machine.getStatus() > 1)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_OPTION, "Invalid Status value: its value must be 0 or 1");
  }

  SessionProxy sessionProxy(sessionKey);
  MachineProxy machineProxy(machine, sessionProxy);

  return machineProxy.update();
}

/**
 * \brief Function to remove a machine from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param machineId represents the identifier of the machine
 * \return raises an exception on error
 */
int
vishnu::deleteMachine(const std::string& sessionKey,
                      const std::string& machineId)
                                                  throw(UserException, SystemException)
{

  UMS_Data::Machine machine;
  machine.setMachineId(machineId);
  SessionProxy sessionProxy(sessionKey);
  MachineProxy machineProxy(machine, sessionProxy);

  return machineProxy.deleteMachine();
}

/**
 * \brief Function to add a new local user configuration
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newLocalAccount is is the object which encapsulates the new local user configuration
 * \param sshPublicKey the SSH public key generated by VISHNU for accessing a local account
 * \return raises an exception on error
 */
int
vishnu::addLocalAccount(const std::string& sessionKey,
                        const UMS_Data::LocalAccount& newLocalAccount,
                        std::string& sshPublicKey)
                                                 throw(UserException, SystemException)
{

  checkIfTextIsEmpty(newLocalAccount.getUserId(), "The local account userId is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newLocalAccount.getMachineId(), "The local account machineId is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newLocalAccount.getAcLogin(), "The local account acLogin is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newLocalAccount.getSshKeyPath(), "The local sshPublicKeyPath is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(newLocalAccount.getHomeDirectory(), "The local account home directory is empty", ERRCODE_INVALID_PARAM);

  SessionProxy sessionProxy(sessionKey);
  LocalAccountProxy localAccountProxy(newLocalAccount, sessionProxy);

  int  res = localAccountProxy.add();
  sshPublicKey = localAccountProxy.getSshPublicKey();

  return res;
}

/**
 * \brief Function to update a local user configuration
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param localAccount is an object which encapsulates the local user configuration changes except the machineId and the userId
 * \return raises an exception on error
 */
int
vishnu::updateLocalAccount(const std::string& sessionKey,
                           const UMS_Data::LocalAccount& localAccount)
                                                                     throw(UserException, SystemException)
{

  SessionProxy sessionProxy(sessionKey);
  LocalAccountProxy localAccountProxy(localAccount, sessionProxy);

  return localAccountProxy.update();
}

/**
 * \brief Function to removes a local user configuration (for a given user on a given machine) from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param userId represents the VISHNU user identifier of the user whose local configuration will be deleted for the given machine
 * \param machineId represents the identifier of the machine whose local configuration will be deleted for the given user
 * \return raises an exception on error
 */
int
vishnu::deleteLocalAccount(const std::string& sessionKey,
                           const std::string& userId,
                           const std::string& machineId)
                                                      throw(UserException, SystemException)
{

  UMS_Data::LocalAccount localAccount;
  localAccount.setUserId(userId);
  localAccount.setMachineId(machineId);
  SessionProxy sessionProxy(sessionKey);
  LocalAccountProxy localAccountProxy(localAccount, sessionProxy);

  return localAccountProxy.deleteLocalAccount();
}

/**
 * \brief Function to save the configuration of VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param config is an object which encapsulates the configuration description
 * \return raises an exception on error
 */
int
vishnu::saveConfiguration(const std::string& sessionKey,
                          UMS_Data::Configuration& config)
                                                        throw(UserException, SystemException)
{

  //the current time
  boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();

  //To get the current time as a string
  std::string nowToString = to_simple_string(now.date());
  nowToString.append("-"+to_simple_string(now.time_of_day()));

  //To construct the file to save
  boost::filesystem::path home_dir = getenv("HOME");
  boost::filesystem::path  config_dir = home_dir;
  config_dir /= ".vishnu";
  config_dir /= "configurationSaved";

  if(!boost::filesystem::exists(config_dir)){
    boost::filesystem::create_directories(config_dir);
  }

  std::string filePath;
  filePath.append(config_dir.string()+"/");
  filePath.append(nowToString);

  SessionProxy sessionProxy(sessionKey);
  ConfigurationProxy configurationProxy(filePath, sessionProxy);

  int res = configurationProxy.save();
  if(!res) {
    UMS_Data::Configuration *configData = configurationProxy.getData();
    if(configData!=NULL) {
      UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
      //To set the user list
      for(unsigned int i = 0; i < configData->getListConfUsers().size(); i++) {
        UMS_Data::User_ptr user = ecoreFactory->createUser();
        //To copy the content and not the pointer
        *user = *configData->getListConfUsers().get(i);
        config.getListConfUsers().push_back(user);
      }
      //To set the machine list
      for(unsigned int i = 0; i < configData->getListConfMachines().size(); i++) {
        UMS_Data::Machine_ptr machine = ecoreFactory->createMachine();
        //To copy the content and not the pointer
        *machine = *configData->getListConfMachines().get(i);
        config.getListConfMachines().push_back(machine);
      }
      //To set the LocalAccounts list
      for(unsigned int i = 0; i < configData->getListConfLocalAccounts().size(); i++) {
        UMS_Data::LocalAccount_ptr localAccount = ecoreFactory->createLocalAccount();
        //To copy the content and not the pointer
        *localAccount = *configData->getListConfLocalAccounts().get(i);
        config.getListConfLocalAccounts().push_back(localAccount);
      }
      config.setFilePath(configData->getFilePath());

      delete configData;
    }
  }

  return res;
}

/**
 * \brief Function to restore the configuration of VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param filePath is the path of the file used to restore VISHNU configuration
 * \return raises an exception on error
 */
int
vishnu::restoreConfiguration(const std::string& sessionKey,
                             const std::string& filePath)
                                                       throw(UserException, SystemException)
{

  if(false==boost::filesystem::exists(filePath)) {
    throw UMSVishnuException(ERRCODE_INVALID_PARAM, "can't open file "+filePath);
  }
  if(false==boost::filesystem::is_regular_file(filePath)){
    throw UMSVishnuException(ERRCODE_INVALID_PARAM, filePath+" is not a regular file");
  }

  SessionProxy sessionProxy(sessionKey);
  ConfigurationProxy configurationProxy(filePath, sessionProxy);

  return configurationProxy.restoreFromFile();
}

/**
 * \brief Function to configure an option of the user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param optionValue is an object which encapsulates the option information
 * \return raises an exception on error
 */
int
vishnu::configureOption(const std::string& sessionKey,
                        const UMS_Data::OptionValue& optionValue)
                                                                throw(UserException, SystemException)
{

  checkIfTextIsEmpty(optionValue.getOptionName(), "The name of the option is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(optionValue.getValue(), "The value of the option is empty", ERRCODE_INVALID_PARAM);

  SessionProxy sessionProxy(sessionKey);
  OptionValueProxy optionValueProxy(optionValue, sessionProxy);

  return optionValueProxy.configureOption();
}

/**
 * \brief Function to configure a default option value
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param optionValue is an object which encapsulates the option information
 * \return raises an exception on error
 */
int
vishnu::configureDefaultOption(const std::string& sessionKey,
                               const UMS_Data::OptionValue& optionValue)
                                                                      throw(UserException, SystemException)
{
  checkIfTextIsEmpty(optionValue.getOptionName(), "The name of the option is empty", ERRCODE_INVALID_PARAM);
  checkIfTextIsEmpty(optionValue.getValue(), "The value of the option is empty", ERRCODE_INVALID_PARAM);

  SessionProxy sessionProxy(sessionKey);
  OptionValueProxy optionValueProxy(optionValue, sessionProxy);

  return optionValueProxy.configureDefaultOption();
}

/**
 * \brief Function to list all sessions of the user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listSession is an object which encapsulates the list of sessions
 * \param options allows the user to list sessions using several optional criteria such as: the state of sessions (actives or
 * inactives, by default, all sessions are listed), a period, a specific session or for admin to list all sessions of all
 * users or sessions of a specific user.
 * \return raises an exception on error
 */
int
vishnu::listSessions(const std::string& sessionKey,
                     UMS_Data::ListSessions& listSession,
                     const UMS_Data::ListSessionOptions& options)
                                                               throw(UserException, SystemException)
{
  if((options.getSessionClosePolicy() < 0) || (options.getSessionClosePolicy() > 2)) {
    throw UMSVishnuException(ERRCODE_UNKNOWN_CLOSURE_MODE, "Invalid ClosePolicy value: its value must be 0, 1 or 2");
  }

  if((options.getStatus() < 0) || (options.getStatus() > 1)) {
    throw UserException(ERRCODE_INVALID_PARAM, "Invalid Privilege value: its value must be 0 or 1");
  }

  SessionProxy sessionProxy(sessionKey);
  QueryProxy<UMS_Data::ListSessionOptions, UMS_Data::ListSessions> query(options, sessionProxy, "sessionList");

  UMS_Data::ListSessions* listSession_ptr = query.list();

  if(listSession_ptr!=NULL) {
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listSession_ptr->getSessions().size(); i++) {
      UMS_Data::Session_ptr session = ecoreFactory->createSession();
      //To copy the content and not the pointer
      *session = *listSession_ptr->getSessions().get(i);
      listSession.getSessions().push_back(session);
    }
    delete  listSession_ptr;
  }

  return 0;
}

/**
 * \brief Function to list the local user configurations
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listLocalAcc is an object which encapsulates the list of the local user configuations
 * \param options allows an admin to list all local configurations of all users or a simple user to list his/her local user configurations on a
 * specific machine
 * \return raises an exception on error
 */
int
vishnu::listLocalAccounts(const std::string& sessionKey,
                         UMS_Data::ListLocalAccounts& listLocalAcc,
                         const UMS_Data::ListLocalAccOptions& options)
                                                                     throw(UserException, SystemException)
{

  SessionProxy sessionProxy(sessionKey);
  QueryProxy<UMS_Data::ListLocalAccOptions, UMS_Data::ListLocalAccounts> query(options, sessionProxy, "localAccountList");

  UMS_Data::ListLocalAccounts* listLocalAcc_ptr = query.list();

  if(listLocalAcc_ptr!=NULL) {
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listLocalAcc_ptr->getAccounts().size(); i++) {
      UMS_Data::LocalAccount_ptr account = ecoreFactory->createLocalAccount();
      //To copy the content and not the pointer
      *account = *listLocalAcc_ptr->getAccounts().get(i);
      listLocalAcc.getAccounts().push_back(account);
    }
    delete listLocalAcc_ptr;
  }

  return 0;
}

/**
 * \brief Function to list the machines in which the local user configurations are defined for the given user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listMachine is an object which encapsulates the list of the machines
 * \param options allows a user to list all VISHNU machines or information about a specific machine and an admin to list machines used by
 * a specific user
 * \return raises an exception on error
 */
int
vishnu::listMachines(const std::string& sessionKey,
                    UMS_Data::ListMachines& listMachine,
                    const UMS_Data::ListMachineOptions& options)
                                                               throw(UserException, SystemException)
{

  SessionProxy sessionProxy(sessionKey);
  QueryProxy<UMS_Data::ListMachineOptions, UMS_Data::ListMachines> query(options, sessionProxy, "machineList");

  UMS_Data::ListMachines* listMachine_ptr = query.list();

  if(listMachine_ptr!=NULL) {
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listMachine_ptr->getMachines().size(); i++) {
      UMS_Data::Machine_ptr machine = ecoreFactory->createMachine();
      //To copy the content and not the pointer
      *machine = *listMachine_ptr->getMachines().get(i);
      listMachine.getMachines().push_back(machine);
    }
    delete listMachine_ptr;
  }
  return 0;
}

/**
 * \brief Function to list the commands
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listCommands is an object which encapsulates the list of commands
 * \param options allows the user to list commands by using several optional criteria: a period, specific session and for admin
 * to list all commands of all VISHNU users or commands from a specific user
 * \return raises an exception on error
 */
int
vishnu::listHistoryCmd(const std::string& sessionKey,
                       UMS_Data::ListCommands& listCommands,
                       const UMS_Data::ListCmdOptions& options)
                                                             throw(UserException, SystemException)
{
  SessionProxy sessionProxy(sessionKey);
  QueryProxy<UMS_Data::ListCmdOptions, UMS_Data::ListCommands> query(options, sessionProxy, "commandList");

  UMS_Data::ListCommands* listCommands_ptr = query.list();

  if(listCommands_ptr!=NULL) {
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listCommands_ptr->getCommands().size(); i++) {
      UMS_Data::Command_ptr command = ecoreFactory->createCommand();
      //To copy the content and not the pointer
      *command = *listCommands_ptr->getCommands().get(i);
      listCommands.getCommands().push_back(command);
    }
    delete listCommands_ptr;
  }

  return 0;
}

/**
 * \brief Function to list the options of the user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listOptValues is an object which encapsulates the list of options
 * \param options allows to list a specific option or all default options values or for an admin to list options of a specific user
 * \return raises an exception on error
 */
int
vishnu::listOptions(const std::string& sessionKey,
                    UMS_Data::ListOptionsValues& listOptValues,
                    const UMS_Data::ListOptOptions& options)
                                                          throw(UserException, SystemException)
{

  SessionProxy sessionProxy(sessionKey);
  QueryProxy<UMS_Data::ListOptOptions, UMS_Data::ListOptionsValues> query(options, sessionProxy, "optionValueList");

  UMS_Data::ListOptionsValues* listOptValues_ptr = query.list();

  if(listOptValues_ptr!=NULL) {
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listOptValues_ptr->getOptionValues().size(); i++) {
      UMS_Data::OptionValue_ptr optionValue = ecoreFactory->createOptionValue();
      //To copy the content and not the pointer
      *optionValue = *listOptValues_ptr->getOptionValues().get(i);
      listOptValues.getOptionValues().push_back(optionValue);
    }
    delete listOptValues_ptr;
  }

  return 0;
}

/**
 * \brief Function to list VISHNU users
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listUsers is an object which encapsulates the list of users
 * \param options allows an admin to get information about a specific user identified by his/her userId
 * \return raises an exception on error
 */

int
  vishnu::listUsers(const std::string& sessionKey, 
            UMS_Data::ListUsers& listUsers, 
            const UMS_Data::ListUsersOptions& listOptions )
                                                     throw(UserException, SystemException)

{
  /*
  
  SessionProxy sessionProxy(sessionKey);
  QueryProxy<std::string, UMS_Data::ListUsers> query(listOptions, sessionProxy, "userList");

  UMS_Data::ListUsers* listUsers_ptr = query.list();

  if(listUsers_ptr!=NULL) {
    UMS_Data::UMS_DataFactory_ptr ecoreFactory = UMS_Data::UMS_DataFactory::_instance();
    for(unsigned int i = 0; i < listUsers_ptr->getUsers().size(); i++) {
      UMS_Data::User_ptr user = ecoreFactory->createUser();
      //To copy the content and not the pointer
      *user = *listUsers_ptr->getUsers().get(i);
      listUsers.getUsers().push_back(user);
    }
    delete listUsers_ptr;
  }

*/



  return 0;
}


/***
 * \brief Function to update a user-authentication system in VISHNU 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newAuthSys is an object which encapsulates the information of the
 * user-authentication system which will be added in
 * VISHNU
 * \param options is an object which encapsulates the information of the
 * user-authentication system which will be added in
 * VISHNU
 */


int
  vishnu::addAuthenticationSystem(const std::string& sessionKey, UMS_Data::AuthSystems& newAuthSys)
                                     throw(UserException, SystemException){
                                     
                                       std::cout << "name "  << newAuthSys.getName() << "\n";                                 
                                       std::cout << "URI "  << newAuthSys.getURI() << "\n";                                 
                                       std::cout << "authLogin "  << newAuthSys.getAuthLogin() << "\n";                                 
                                       std::cout << "authPassword "  << newAuthSys.getAuthPassword() << "\n";                                 
                                       std::cout << "UserPasswordEncryption "  << newAuthSys.getUserPasswordEncryption() << "\n";                                 
                                       std::cout << "type "  << newAuthSys.getType() << "\n";                                 
                                       if (newAuthSys.getOptions() != NULL) {
                                         std::cout << "LdapBase "  << newAuthSys.getOptions()->getLdapBase() << "\n";                                 
                                       }

                                     }

/***
 * \brief Function to add a new user-authentication system in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authSysis an object which encapsulates the information of the
 * user-authentication system which will be added in
 * VISHNU 
 */


int
vishnu::updateAuthenticationSystem(const std::string& sessionKey,  UMS_Data::AuthSystems& AuthSys)
                                     throw(UserException, SystemException){
                                       std::cout << "name "  << AuthSys.getName() << "\n";                                 
                                       std::cout << "URI "  << AuthSys.getURI() << "\n";                                 
                                       std::cout << "authLogin "  << AuthSys.getAuthLogin() << "\n";                                 
                                       std::cout << "authPassword "  << AuthSys.getAuthPassword() << "\n";                                 
                                       std::cout << "UserPasswordEncryption "  << AuthSys.getUserPasswordEncryption() << "\n";                                 
                                       std::cout << "status "  << AuthSys.getStatus() << "\n";                                 
                                       std::cout << "type "  << AuthSys.getType() << "\n";                                 
                                    if (AuthSys.getOptions() != NULL) {
                                         std::cout << "LdapBase "  << AuthSys.getOptions()->getLdapBase() << "\n";                                 
                                       } 
                                     }

/***
 * \brief Function to remove a user-authentication system from VISHNU  
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authSystemId authSystemId is the identifier of the user-authentication
 * system 
 */

int
vishnu::deleteAuthenticationSystem(const std::string& sessionKey, const std::string& authSystemId)
                                    throw(UserException, SystemException){
                                    
                                    
                                       std::cout << "ID "  << authSystemId << "\n";                                 
                                    
                                    }
 

/***
 * \brief Function to lists VISHNU user-authentification systems 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listAuthSys is the list of the user-authentication systems 
 * \param options allows an admin to list all user-authentication systems
 * used by a specific user or a user to list all
 * user-authentication systems declared in VISHNU (and
 * not only those where a local user-authentication configs
 * are defined). It also allows to list user-authentication
 * systems of a specific type
 */


int 
vishnu::listAuthenticationSystems(const std::string& sessionKey, UMS_Data::ListAuthSystems& listAuthSys, const UMS_Data::ListAuthSysOptions& options )
                                     throw(UserException, SystemException){}


/***
 * \brief Function to add a new local user-authentication configuration 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authAccount is an object which encapsulates the information of the
 * local user-authentication configuration which will be
 * added in VISHNU
 */

int
vishnu::addAuthAccount(const std::string& sessionKey, const UMS_Data::AuthAccount& authAccount)
                                     throw(UserException, SystemException){
                                     
                                         std::cout << "authSystemId "  << authAccount.getAuthSystemId() << "\n";                                 
                                       std::cout << "UserId "  << authAccount.getUserId() << "\n";                                 
                                       std::cout << "acLogin "  << authAccount.getAcLogin() << "\n";                                 
                                    
                                     
                                     }


/***
 * \brief Function to add a new local user-authentication configuration 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authenAccount is an object which encapsulates the information of the
 * local user-authentication configuration which will be
 * updated
 */

int 
vishnu::updateAuthAccount(const std::string& sessionKey, const UMS_Data::AuthAccount& authenAccount)
                                     throw(UserException, SystemException){
                                     
                                      
                                         std::cout << "authSystemId "  << authenAccount.getAuthSystemId() << "\n";                                 
                                       std::cout << "UserId "  << authenAccount.getUserId() << "\n";                                 
                                       std::cout << "acLogin "  << authenAccount.getAcLogin() << "\n";                                 
                                    

                                     
                                     }


/***
 * \brief Function to removes a local user-authentication configuration from
 * VISHNU 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authSystemId authSystemId is the identifier of the user-authentication
 * system
 * \param userIdOption is an admin option which represents the VISHNU
 * identifier of the user whose local user-authentication
 * configuration will be deleted 
 */


int 
vishnu::deleteAuthAccount(const std::string& sessionKey, const std::string& authSystemId, const std::string& userIdOption )
                                     throw(UserException, SystemException){
                                     
                                       
                                         std::cout << "authSystemId "  << authSystemId<< "\n";                                 
                                       std::cout << "UserIdOption "  << userIdOption << "\n";                                 
                                     
                                     
                                     
                                     }

/***
 * \brief Function to lists local user-authentication configurations 
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listAuthAccounts is the list of the local user-authentication
 * configurations 
 * \param options allows an admin to list all local user-authentication
 * configurations or to list local user-authentication
 * configurations of a specific user or for a user to list local
 * user-authentication configuration defined for a specific
 * user-authentication system
 */


int 
vishnu::listAuthAccounts(const std::string& sessionKey, UMS_Data::ListAuthAccounts& listAuthAccounts, const UMS_Data::ListAuthAccOptions& options)
                            throw(UserException, SystemException){
                            
                              std::cout << "userId :" <<  options.getUserId() << "\n";
                              std::cout << "AuthSystemId: " <<  options.getAuthSystemId() << "\n";
                              std::cout << "listAll: " << std::boolalpha <<  options.isListAll() << "\n";

                            
                            }


/**
 * \brief Function to initialize the SYSFERA-DS configuration
 * \param cfg The SYSFERA-DS configuration file
 * \param argc The number of arguments of the program
 * \param argv The list of arguments
 * \return an error code
 */
int
vishnu::vishnuInitialize(char* cfg, int argc, char** argv)
{

  return UtilsProxy(cfg, argc, argv).initialize();
}

/**
 * \brief Function to finalize
 * \return an error code
 */
void
vishnu::vishnuFinalize()
{

  UtilsProxy().finalize();
}

#ifdef BUILD_TESTING
/**
 * \brief Function to initialize the database
 * \param filePath the file
 * \return an error code
 */
int
vishnu::restore(const std::string& filePath)
{

  UtilsProxy utilsProxy(filePath) ;

  return utilsProxy.restore();
}
#endif
