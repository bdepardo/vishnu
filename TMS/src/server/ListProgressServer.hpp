/**
 * \file ListProgressServer.hpp
 * \brief This file contains the VISHNU ListProgressServer class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#ifndef _LIST_PROGRESS_SERVER_
#define _LIST_PROGRESS_SERVER_

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/posix_time_zone.hpp>
#include <boost/date_time/date_facet.hpp>
#include <locale>
#include <memory>
#include <sstream>

#include "QueryServer.hpp"
#include "SessionServer.hpp"
#include "TMS_Data.hpp"
#include "BatchServer.hpp"
#include "BatchFactory.hpp"

/**
 * \class ListProgressServer
 * \brief ListProgressServer class implementation
 */
class ListProgressServer: public QueryServer<TMS_Data::ProgressOptions, TMS_Data::ListProgression> {

public:

  /**
   * \fn ListProgressServer(const SessionServer session)
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \param machineId The identifier of the machine on which the jobs whill be listed  
   * \brief Constructor, raises an exception on error
   */
  ListProgressServer(const SessionServer session, const std::string& machineId):
    QueryServer<TMS_Data::ProgressOptions, TMS_Data::ListProgression>(session)
  {
   mcommandName = "vishnu_get_job_progress";
   mmachineId = machineId;
  }
  /**
   * \fn ListProgressServer(const UMS_Data::ListSessionOptions_ptr params,
   *                        const SessionServer& session)
   * \param params The object which encapsulates the information of ListProgressServer options
   * \param session The object which encapsulates the session information (ex: identifier of the session)
   * \brief Constructor, raises an exception on error
   */
  ListProgressServer(TMS_Data::ProgressOptions_ptr params, const SessionServer& session, const std::string& machineId):
    QueryServer<TMS_Data::ProgressOptions, TMS_Data::ListProgression>(params, session)
  {
    mcommandName = "vishnu_get_job_progress";
    mmachineId = machineId;
  }

  /**
   * \brief Function to list sessions information
   * \fn UMS_Data::ListSessions* list()
   * \return The pointer to the UMS_Data::ListSessions containing sessions information
   * \return raises an exception on error
   */
  TMS_Data::ListProgression*
  list() {
    
    /*BatchFactory factory;
    BatchType batchType  = ServerTMS::getInstance()->getBatchType();
    BatchServer* batchServer = factory.getBatchServerInstance(batchType);
    mlistObject = batchServer->getJobProgress(*mparameters);
    delete batchServer;
    */
    //To check the sessionKey
    msessionServer.check();

    std::vector<std::string> results;
    std::vector<std::string>::iterator  iter;
    std::string batchJobId;
    int status;
    long startTime;
    long walltime;

    TMS_Data::Job job;
    JobServer jobServer(msessionServer, mmachineId, job, UNDEFINED);
    std::string acLogin = jobServer.getUserAccountLogin();

    std::string machineName = jobServer.getMachineName();

    TMS_Data::TMS_DataFactory_ptr ecoreFactory = TMS_Data::TMS_DataFactory::_instance();
    mlistObject = ecoreFactory->createListProgression();

    std::string sqlRequest = "SELECT jobId, jobName, wallClockLimit, endDate, status, batchJobId from vsession, job where"
            " vsession.numsessionid=job.vsession_numsessionid";

    if(mparameters->getJobId().size()!=0) {
      std::string jobId = mparameters->getJobId();
      sqlRequest.append(" and jobId='"+jobId+"'");
      boost::scoped_ptr<DatabaseResult> sqlResult(ServerTMS::getInstance()->getDatabaseVishnu()->getResult(sqlRequest.c_str()));
      if(sqlResult->getNbTuples() == 0) {
        throw TMSVishnuException(ERRCODE_UNKNOWN_JOBID);        
      }
    } else {
      if(mparameters->getJobOwner().size()!=0) {
        acLogin = mparameters->getJobOwner(); //TODO: check acLogin
      }
      sqlRequest.append(" and owner='"+acLogin+"'");
    }

    sqlRequest.append("  and status < 5 order by jobId");
    
    boost::scoped_ptr<DatabaseResult> sqlResult(ServerTMS::getInstance()->getDatabaseVishnu()->getResult(sqlRequest.c_str()));

    if (sqlResult->getNbTuples() != 0){
      for (size_t i = 0; i < sqlResult->getNbTuples(); ++i) {

        results.clear();
        results = sqlResult->get(i);
        iter = results.begin();

        TMS_Data::Progression_ptr job = ecoreFactory->createProgression();

        job->setJobId(*iter);
        job->setJobName(*(++iter));
        walltime = convertToInt(*(++iter));
        job->setWallTime(walltime);
        job->setEndTime(convertToTimeType(*(++iter)));
        status = convertToInt(*(++iter));
        job->setStatus(status);
        batchJobId = *(++iter);    

        BatchFactory factory;
        BatchType batchType  = ServerTMS::getInstance()->getBatchType(); 
        boost::scoped_ptr<BatchServer> batchServer(factory.getBatchServerInstance(batchType));

        startTime = batchServer->getJobStartTime(batchJobId); 
        if(startTime!=0) {
          job->setStartTime(startTime);

          if(status==5) {
            job->setPercent(100);  
          } else {
            time_t currentTime = vishnu::getCurrentTimeInUTC();
            double percent = 0;
            time_t gap = currentTime-startTime;
            if(walltime==0) {
               walltime = 60;
            }

            if(gap < walltime) {
              percent = 100*(double(gap)/walltime);
            } else {
              gap /= 2; 
              while(gap >= (walltime)) {
                gap /= 2;
              }
              if(gap < walltime/2) {
                gap = 3*walltime/4;
              } 
              percent = 100*(double(gap)/walltime);
            }
            job->setPercent(percent);
          } 
        } else {
          job->setPercent(0.0);
        }
        mlistObject->getProgress().push_back(job); 
      }
    }
    
    mlistObject->setNbJobs(mlistObject->getProgress().size());
   
    return mlistObject;

  }


  /**
   * \brief Function to get the name of the ListProgressServer command line
   * \fn std::string getCommandName()
   * \return The the name of the ListProgressServer command line
   */
  std::string getCommandName()
  {
    return mcommandName;
  }

  /**
   * \fn ~ListProgressServer()
   * \brief Destructor, raises an exception on error
   */
  ~ListProgressServer()
  {
  }

  private:

  /////////////////////////////////
  // Attributes
  /////////////////////////////////


  /**
  * \brief The name of the ListProgressServer command line
  */
  std::string mcommandName;
   /**
  * \brief The identifier of the machine in which the jobs whill be listed
  */
  std::string mmachineId; 
};

#endif
