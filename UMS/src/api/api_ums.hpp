
/**
 * \mainpage UMS
 *
 * <center><b>UMS is the module that deals with the authentication of the users and the machines in the VISHNU infrastructure</b></center>
 *
 * \image html logoSysFera.jpg
 *
 * \authors CAPOCHICHI Eugene
 * \authors CISSE      Ibrahima
 * \authors COULOMB    Kevin
 * \authors ISNARD     Benjamin
 * \authors TRAORE     Daouda
 *
 */

/**
 * \file api_ums.hpp
 * \brief This file contains the VISHNU api functions.
 * \author Daouda Traore (daouda.traore@sysfera.com) and Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 * \date February 2011
 */
#ifndef _API_UMS_H_
#define _API_UMS_H_

#include <iostream>
#include <string>

#include "UMS_Data.hpp"
#include "UserException.hpp"
#include "SystemException.hpp"


namespace vishnu {

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
connect(const std::string& userId,
        const std::string& password,
        UMS_Data::Session& session,
        const UMS_Data::ConnectOptions& connectOpt = UMS_Data::ConnectOptions())
  throw(UserException, SystemException);

/**
 * \brief Function to open a session
 * \param users The VISHNU users to try to connect as
 * \param session is an object containing the encrypted identifier of the session generated by VISHNU
 * \param connectOpt To encapsulate the options available for the connect method. It allows the user
 *  to choose the way for way for closing the session automatically on TIMEOUT or on DISCONNECT and the
 *  possibility for an admin to open a session as she was a specific user
 *  \return raises an exception on error
 */
int
connect(UMS_Data::ListUsers& users,
        UMS_Data::Session& session,
        const UMS_Data::ConnectOptions& connectOpt = UMS_Data::ConnectOptions())
  throw(UserException, SystemException);



/**
 * \brief Function to return the sessionKey of a session in which the user was disconnected previously without closing it
 * \param userId represents the VISHNU user identifier
 * \param password represents the password of the user
 * \param sessionId is the identifier of the session defined in the database
 * \param session is an object containing the encrypted identifier of the session generated by VISHNU and the close policy value
 * \return raises an exception on error
 */
int
reconnect(const std::string& userId,
          const std::string& password,
          const std::string& sessionId,
          UMS_Data::Session& session)
  throw(UserException, SystemException);

/**
 * \brief Function to return the sessionKey of a session in which the user was disconnected previously without closing it
 * \param users The VISHNU users to try to connect as
 * \param sessionId is the identifier of the session defined in the database
 * \param session is an object containing the encrypted identifier of the session generated by VISHNU and the close policy value
 * \return raises an exception on error
 */
int
reconnect(UMS_Data::ListUsers& users,
          const std::string& sessionId,
          UMS_Data::Session& session)
  throw(UserException, SystemException);

/**
 * \brief Function to close the session identfied by the session key
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \return raises an exception on error
 */
int
close(const std::string& sessionKey)
  throw(UserException, SystemException);

/**
 * \brief Function to add a new user in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newUser is an object containing the new user information
 * \return raises an exception on error
 */
int
addUser(const std::string& sessionKey,
        UMS_Data::User& newUser)
  throw(UserException, SystemException);

/**
 * \brief Function to update the user information except the userId and the password
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param user is an object containing the new user information
 * \return raises an exception on error
 */
int
updateUser(const std::string& sessionKey,
           const UMS_Data::User& user)
  throw(UserException, SystemException);

/**
 * \brief Function to remove a user from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param userId represents the VISHNU user identifier of the user who will be deleted from VISHNU
 * \return raises an exception on error
 */
int
deleteUser(const std::string& sessionKey,
           const std::string& userId)
  throw(UserException, SystemException);

/**
 * \brief Function to change the password
 * \param userId represents the VISHNU user identifier
 * \param password represents the password of the user
 * \param passwordNew represents the new password of the user
 * \return raises an exception on error
 */
int
changePassword(const std::string& userId,
               const std::string& password,
               const std::string& passwordNew)
  throw(UserException, SystemException);

/**
 * \brief Function to reset the password of a user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param userId represents represents the VISHNU user identifier of the user whose password will be reset
 * \param tmpPassword New password of the user, temporary
 * \return raises an exception on error
 */
int
resetPassword(const std::string& sessionKey,
              const std::string& userId,
              std::string& tmpPassword)
  throw(UserException, SystemException);

/**
 * \brief Function to add a new machine in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newMachine is an object which encapsulates the information of the machine which will be added in VISHNU except the
 * machine id which will be created automatically by VISHNU
 * \return raises an exception on error
 */
int
addMachine(const std::string& sessionKey,
           UMS_Data::Machine& newMachine)
  throw(UserException, SystemException);

/**
 * \brief Function to update machine description
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param machine is an existing machine information
 * \return raises an exception on error
 */
int
updateMachine(const std::string& sessionKey,
              const UMS_Data::Machine& machine)
  throw(UserException, SystemException);

/**
 * \brief Function to remove a machine from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param machineId represents the identifier of the machine
 * \return raises an exception on error
 */
int
deleteMachine(const std::string& sessionKey,
              const std::string& machineId)
  throw(UserException, SystemException);

/**
 * \brief Function to add a new local user configuration
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newLocalAccount is is the object which encapsulates the new local user configuration
 * \param sshPublicKey the SSH public key generated by VISHNU for accessing a local account (deprecated)
 * \return raises an exception on error
 */
int
addLocalAccount(const std::string& sessionKey,
                const UMS_Data::LocalAccount& newLocalAccount,
                std::string&  sshPublicKey)
  throw(UserException, SystemException);

/**
 * \brief Function to update a local user configuration
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param localAccount is an object which encapsulates the local user configuration changes except the machineId and the userId
 * \return raises an exception on error
 */
int
updateLocalAccount(const std::string& sessionKey,
                   const UMS_Data::LocalAccount& localAccount)
  throw(UserException, SystemException);

/**
 * \brief Function to removes a local user configuration (for a given user on a given machine) from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param userId represents the VISHNU user identifier of the user whose local configuration will be deleted for the given machine
 * \param machineId represents the identifier of the machine whose local configuration will be deleted for the given user
 * \return raises an exception on error
 */
int
deleteLocalAccount(const std::string& sessionKey,
                   const std::string& userId,
                   const std::string& machineId)
  throw(UserException, SystemException);

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
listSessions(const std::string& sessionKey,
             UMS_Data::ListSessions& listSession,
             const UMS_Data::ListSessionOptions& options = UMS_Data::ListSessionOptions())
  throw(UserException, SystemException);

/**
 * \brief Function to list the local user configurations
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listLocalAcc is an object which encapsulates the list of the local user configuations
 * \param options allows an admin to list all local configurations of all users or a simple user to list his/her local user configurations on a
 * specific machine
 * \return raises an exception on error
 */
int
listLocalAccounts(const std::string& sessionKey,
                  UMS_Data::ListLocalAccounts& listLocalAcc,
                  const UMS_Data::ListLocalAccOptions& options = UMS_Data::ListLocalAccOptions())
  throw(UserException, SystemException);

/**
 * \brief Function to list the machines in which the local user configurations are defined for the given user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listMachine is an object which encapsulates the list of the machines
 * \param options allows a user to list all VISHNU machines or information about a specific machine and an admin to list machines used by
 * a specific user
 * \return raises an exception on error
 */
int
listMachines(const std::string& sessionKey,
             UMS_Data::ListMachines& listMachine,
             const UMS_Data::ListMachineOptions& options = UMS_Data::ListMachineOptions())
  throw(UserException, SystemException) ;

/**
 * \brief Function to list the commands
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listCommands is an object which encapsulates the list of commands
 * \param options allows the user to list commands by using several optional criteria: a period, specific session and for admin
 * to list all commands of all VISHNU users or commands from a specific user
 * \return raises an exception on error
 */
int
listHistoryCmd(const std::string& sessionKey,
               UMS_Data::ListCommands& listCommands,
               const UMS_Data::ListCmdOptions& options = UMS_Data::ListCmdOptions())
  throw(UserException, SystemException);

/**
 * \brief Function to list the options of the user
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listOptValues is an object which encapsulates the list of options
 * \param options allows to list a specific option or all default options values or for an admin to list options of a specific user
 * \return raises an exception on error
 */
int
listOptions(const std::string& sessionKey,
            UMS_Data::ListOptionsValues& listOptValues,
            const UMS_Data::ListOptOptions& options = UMS_Data::ListOptOptions())
  throw(UserException, SystemException) ;

/**
 * \brief Function to list VISHNU users
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listUsers is an object which encapsulates the list of users
 * \param listOptions allows an admin to get information about a specific user identified by his/her userId
 * \return raises an exception on error
 */
int
listUsers(const std::string& sessionKey,
          UMS_Data::ListUsers& listUsers,
          const UMS_Data::ListUsersOptions& listOptions = UMS_Data::ListUsersOptions ())
  throw(UserException, SystemException);


/**
 * \brief Function to add a new user-authentication system in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param newAuthSys is an object which encapsulates the information of the
 * user-authentication system which will be added in
 * VISHNU
 * \return an error code
 */
int
addAuthSystem(const std::string& sessionKey,
              UMS_Data::AuthSystem& newAuthSys)
  throw(UserException, SystemException);

/**
 * \brief Function to update a user-authentication system in VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param AuthSys an object which encapsulates the information of the
 * user-authentication system which will be updated in
 * VISHNU
 * \return an error code
 */
int
updateAuthSystem(const std::string& sessionKey,
                 UMS_Data::AuthSystem& AuthSys)
  throw(UserException, SystemException);

/**
 * \brief Function to remove a user-authentication system from VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authSystemId authSystemId is the identifier of the user-authentication
 * system
 * \return an error code
 */
int
deleteAuthSystem(const std::string& sessionKey,
                 const std::string& authSystemId)
  throw(UserException, SystemException);



/**
 * \brief Function to lists VISHNU user-authentification systems
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listAuthSys is the list of the user-authentication systems
 * \param options allows an admin to list all user-authentication systems
 * used by a specific user or a user to list all
 * user-authentication systems declared in VISHNU (and
 * not only those where a local user-authentication configs
 * are defined). It also allows to list user-authentication
 * systems of a specific type
 * \return an error code
 */
int
listAuthSystems(const std::string& sessionKey,
                UMS_Data::ListAuthSystems& listAuthSys,
                const UMS_Data::ListAuthSysOptions& options =  UMS_Data::ListAuthSysOptions())
  throw(UserException, SystemException);


/**
 * \brief Function to add a new local user-authentication configuration
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authAccount is an object which encapsulates the information of the
 * local user-authentication configuration which will be
 * added in VISHNU
 * \return an error code
 */
int
addAuthAccount(const std::string& sessionKey,
               const UMS_Data::AuthAccount& authAccount)
  throw(UserException, SystemException);


/**
 * \brief Function to add a new local user-authentication configuration
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authenAccount is an object which encapsulates the information of the
 * local user-authentication configuration which will be
 * updated
 * \return an error code
 */
int
updateAuthAccount(const std::string& sessionKey,
                  const UMS_Data::AuthAccount& authenAccount)
  throw(UserException, SystemException);


/**
 * \brief Function to removes a local user-authentication configuration from
 * VISHNU
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param authSystemId authSystemId is the identifier of the user-authentication
 * system
 * \param userIdOption is an admin option which represents the VISHNU
 * identifier of the user whose local user-authentication
 * configuration will be deleted
 * \return an error code
 */
int
deleteAuthAccount(const std::string& sessionKey,
                  const std::string& authSystemId,
                  const std::string& userIdOption = "")
  throw(UserException, SystemException);

/**
 * \brief Function to lists local user-authentication configurations
 * \param sessionKey is the encrypted identifier of the session generated by VISHNU
 * \param listAuthAccounts is the list of the local user-authentication
 * configurations
 * \param options allows an admin to list all local user-authentication
 * configurations or to list local user-authentication
 * configurations of a specific user or for a user to list local
 * user-authentication configuration defined for a specific
 * user-authentication system
 * \return an error code
 */
int
listAuthAccounts(const std::string& sessionKey,
                 UMS_Data::ListAuthAccounts& listAuthAccounts,
                 const UMS_Data::ListAuthAccOptions& options = UMS_Data::ListAuthAccOptions())
  throw(UserException, SystemException);


/**
 * \brief Function to initialize the SYSFERA-DS configuration
 * \param cfg The SYSFERA-DS configuration file
 * \param argc The number of arguments of the program
 * \param argv The list of arguments
 * \return an error code
 */
int
vishnuInitialize(char* cfg, int argc, char** argv);

/**
 * \brief Function to finalize, currently useless
 */
void
vishnuFinalize();

/**
 * \brief To export the commands made during a session in a format
 * \param sessionKey: The session key gotten after connection
 * \param oldSessionId: The session id of the session the user wants to export the commands. This session must be closed.
 * \param filename: The file to export the data
 * \param op: The options for the export, currently the export type as shell format is the only possibility
 * \return int : an error code
 */
int
exportCommands(const std::string& sessionKey,
               const std::string& oldSessionId,
               const std::string& filename)
  throw (UserException, SystemException);

}

#endif
