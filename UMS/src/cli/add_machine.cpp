/**
 * \file add_machine.cpp
 * This file defines the VISHNU add machine command 
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */

#include "common.hpp"
#include "utils.hpp"
#include "cliUtil.hpp"
#include "machineUtils.hpp"
#include "sessionUtils.hpp"
#include <boost/bind.hpp>

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

int main (int ac, char* av[]){


  /******* Parsed value containers ****************/

  string dietConfig;

  std::string sessionKey;

  std::string sshPublicKeyPath;


  /********** EMF data ************/

  UMS_Data::Machine newMachine;


  /**************** Callback functions *************/

  boost::function1<void,string> fName( boost::bind(&UMS_Data::Machine::setName,boost::ref(newMachine),_1));
  boost::function1<void,string> fSite( boost::bind(&UMS_Data::Machine::setSite,boost::ref(newMachine),_1));
  boost::function1<void,string> fLanguage( boost::bind(&UMS_Data::Machine::setLanguage,boost::ref(newMachine),_1));
  boost::function1<void,string> fMachineDescription( boost::bind(&UMS_Data::Machine::setMachineDescription,boost::ref(newMachine),_1));

  boost::shared_ptr<Options> opt= makeMachineOptions(av[0], fName,dietConfig, fSite,fLanguage,sshPublicKeyPath,fMachineDescription,1);


  try{
    /**************  Parse to retrieve option values  ********************/

    opt->parse_cli(ac,av);

    opt->parse_env(env_name_mapper());

    opt->notify();


    /********  Process **************************/


    checkVishnuConfig(*opt);

    // read the public key file from the public key path and set the neMachine

    newMachine.setSshPublicKey(get_file_content(sshPublicKeyPath));


    /************** Call UMS add machine service *******************************/

    // initializing DIET

    if (vishnuInitialize(const_cast<char*>(dietConfig.c_str()), ac, av)) {
      
      errorUsage(av[0],dietErrorMsg,EXECERROR);

      return  CLI_ERROR_DIET ;

    }


    // get the sessionKey

    sessionKey=getLastSessionKey(getppid());

    if(false==sessionKey.empty()){

      printSessionKeyMessage();

      addMachine(sessionKey,newMachine);
  
      cout << "The machine identifier is " << newMachine.getMachineId() << endl;
      
      printSuccessMessage();

    }



  }// End of try bloc


  catch(po::required_option& e){// a required parameter is missing

    usage(*opt," name site language sshPublicKeyFile machineDescription ",requiredParamMsg);
  
    return CLI_ERROR_MISSING_PARAMETER;
  }


  // {{RELAX<CODEREDUCER> The error handling is the same in all command

  catch(po::error& e){ // catch all other bad parameter errors

    errorUsage(av[0], e.what());

    return CLI_ERROR_INVALID_PARAMETER;
  }

  catch(VishnuException& e){// catch all Vishnu runtime error

    std::string  msg = e.getMsg()+" ["+e.getMsgComp()+"]";

    errorUsage(av[0], msg,EXECERROR);

    //check the bad session key
    if (checkBadSessionKeyError(e)){

      removeBadSessionKeyFromFile(getppid());
    }


    return e.getMsgI() ;
  }

  catch(std::exception& e){//// catch all std runtime error

    errorUsage(av[0],e.what());

    return CLI_ERROR_RUNTIME;
  }

  return 0;

  // }}RELAX<CODEREDUCER>

}// end of main


