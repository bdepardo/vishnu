/**
 * \file userUtils.hpp
 * \brief This file declares useful functions and types for the VISHNU user commands
 *  command
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */


#ifndef USERUTILS__HH
#define USERUTILS__HH


#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>  // for shared_ptr
#include <string>                       // for string

#include "UMS_Data.hpp"

class Options;

/**
 * \brief A convenient function type taking a string parameter and
 * without return value
 */

typedef
boost::function1<void,std::string> StringcallBackType;

/**
 * \brief The privilege option callback type
 */
typedef
boost::function1<void,UMS_Data::PrivilegeType> PrivilegeCallBackType;
/**
 * \brief The status option callback type
 */
typedef
boost::function1<void,UMS_Data::StatusType> StatusCallBackType;

/**
 * \brief To build options for the VISHNU user commands
 * \param pgName : The name of the command
 * \param configFile: Represents the VISHNU config file
 * \param fUserId: The user id option callback
 * \param fStatus: The status option callback
 * \param fPrivilege: The privilege option callback
 * \param fFirstname: The user first name option callback
 * \param fLastName: The user last name option callback
 * \param fEmail: The user email option callback
 * \param type: Indicates if it is an add or an update command, 0 means update, and 1 means add
 * \return The description of all options allowed by the command
 */


boost::shared_ptr<Options>
makeUserOptions(std::string pgName,
                std::string& configFile,
                StringcallBackType& fUserId,
                StatusCallBackType& fStatus,
                PrivilegeCallBackType& fPrivilege,
                StringcallBackType& fFirstname,
                StringcallBackType& fLastname,
                StringcallBackType& fEmail,
                int type);


#endif
