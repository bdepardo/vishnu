/**
 * \file delete_authentication_system.cpp
 * This file defines the VISHNU delete authentication system command
 * \author Ibrahima Cisse (ibrahima.cisse@sysfera.com)
 */

#include "common.hpp"
#include "cliUtil.hpp"
#include "utils.hpp"
#include "authenticationSystemUtils.hpp"
#include "sessionUtils.hpp"
#include "utilVishnu.hpp"
#include <boost/bind.hpp>

#include "GenericCli.hpp"

namespace po = boost::program_options;

using namespace std;
using namespace vishnu;

struct DeleteAuthenticationSystemFunc {

  std::string  mauthSystemId;

  DeleteAuthenticationSystemFunc(const std::string& authSystemId ):
     mauthSystemId(authSystemId)
  {};

  int operator()(std::string sessionKey) {


     int res=deleteAuthSystem(sessionKey,mauthSystemId);

    return res;
  }
};


int main (int ac, char* av[]){


  /******* Parsed value containers ****************/

  string configFile;

  /********** EMF data ************/

  UMS_Data::AuthSystem newAuthsystem;

  std::string authSystemId;
  /******** Callback functions ******************/


    boost::shared_ptr<Options> opt(new Options(av[0]));


  opt->add("configFile,c",
      "VISHNU configuration file",
      ENV,
      configFile);

  opt->add("authSystemId",
      "the identifier of the user-authentication system",
      HIDDEN,
      authSystemId,
      1);

  opt->setPosition("authSystemId",1);


  bool isEmpty;
  //To process list options
  GenericCli().processListOpt(opt, isEmpty, ac, av);

  DeleteAuthenticationSystemFunc apiFunc(authSystemId);
  return GenericCli().run(apiFunc, configFile, ac, av);

}// end of main
