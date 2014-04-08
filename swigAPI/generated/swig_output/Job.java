/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class Job extends EObject {
  private long swigCPtr;

  public Job(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.Job_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Job obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_Job(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Job() {
    this(VISHNUJNI.new_Job(), true);
  }

  public void _initialize() {
    VISHNUJNI.Job__initialize(swigCPtr, this);
  }

  public String getSessionId() {
    return VISHNUJNI.Job_getSessionId(swigCPtr, this);
  }

  public void setSessionId(String _sessionId) {
    VISHNUJNI.Job_setSessionId(swigCPtr, this, _sessionId);
  }

  public String getSubmitMachineId() {
    return VISHNUJNI.Job_getSubmitMachineId(swigCPtr, this);
  }

  public void setSubmitMachineId(String _submitMachineId) {
    VISHNUJNI.Job_setSubmitMachineId(swigCPtr, this, _submitMachineId);
  }

  public String getSubmitMachineName() {
    return VISHNUJNI.Job_getSubmitMachineName(swigCPtr, this);
  }

  public void setSubmitMachineName(String _submitMachineName) {
    VISHNUJNI.Job_setSubmitMachineName(swigCPtr, this, _submitMachineName);
  }

  public String getJobId() {
    return VISHNUJNI.Job_getJobId(swigCPtr, this);
  }

  public void setJobId(String _jobId) {
    VISHNUJNI.Job_setJobId(swigCPtr, this, _jobId);
  }

  public String getJobName() {
    return VISHNUJNI.Job_getJobName(swigCPtr, this);
  }

  public void setJobName(String _jobName) {
    VISHNUJNI.Job_setJobName(swigCPtr, this, _jobName);
  }

  public String getJobPath() {
    return VISHNUJNI.Job_getJobPath(swigCPtr, this);
  }

  public void setJobPath(String _jobPath) {
    VISHNUJNI.Job_setJobPath(swigCPtr, this, _jobPath);
  }

  public String getOutputPath() {
    return VISHNUJNI.Job_getOutputPath(swigCPtr, this);
  }

  public void setOutputPath(String _outputPath) {
    VISHNUJNI.Job_setOutputPath(swigCPtr, this, _outputPath);
  }

  public String getErrorPath() {
    return VISHNUJNI.Job_getErrorPath(swigCPtr, this);
  }

  public void setErrorPath(String _errorPath) {
    VISHNUJNI.Job_setErrorPath(swigCPtr, this, _errorPath);
  }

  public int getJobPrio() {
    return VISHNUJNI.Job_getJobPrio(swigCPtr, this);
  }

  public void setJobPrio(int _jobPrio) {
    VISHNUJNI.Job_setJobPrio(swigCPtr, this, _jobPrio);
  }

  public int getNbCpus() {
    return VISHNUJNI.Job_getNbCpus(swigCPtr, this);
  }

  public void setNbCpus(int _nbCpus) {
    VISHNUJNI.Job_setNbCpus(swigCPtr, this, _nbCpus);
  }

  public String getJobWorkingDir() {
    return VISHNUJNI.Job_getJobWorkingDir(swigCPtr, this);
  }

  public void setJobWorkingDir(String _jobWorkingDir) {
    VISHNUJNI.Job_setJobWorkingDir(swigCPtr, this, _jobWorkingDir);
  }

  public int getStatus() {
    return VISHNUJNI.Job_getStatus(swigCPtr, this);
  }

  public void setStatus(int _status) {
    VISHNUJNI.Job_setStatus(swigCPtr, this, _status);
  }

  public long getSubmitDate() {
    return VISHNUJNI.Job_getSubmitDate(swigCPtr, this);
  }

  public void setSubmitDate(long _submitDate) {
    VISHNUJNI.Job_setSubmitDate(swigCPtr, this, _submitDate);
  }

  public long getEndDate() {
    return VISHNUJNI.Job_getEndDate(swigCPtr, this);
  }

  public void setEndDate(long _endDate) {
    VISHNUJNI.Job_setEndDate(swigCPtr, this, _endDate);
  }

  public String getOwner() {
    return VISHNUJNI.Job_getOwner(swigCPtr, this);
  }

  public void setOwner(String _owner) {
    VISHNUJNI.Job_setOwner(swigCPtr, this, _owner);
  }

  public String getJobQueue() {
    return VISHNUJNI.Job_getJobQueue(swigCPtr, this);
  }

  public void setJobQueue(String _jobQueue) {
    VISHNUJNI.Job_setJobQueue(swigCPtr, this, _jobQueue);
  }

  public long getWallClockLimit() {
    return VISHNUJNI.Job_getWallClockLimit(swigCPtr, this);
  }

  public void setWallClockLimit(long _wallClockLimit) {
    VISHNUJNI.Job_setWallClockLimit(swigCPtr, this, _wallClockLimit);
  }

  public String getGroupName() {
    return VISHNUJNI.Job_getGroupName(swigCPtr, this);
  }

  public void setGroupName(String _groupName) {
    VISHNUJNI.Job_setGroupName(swigCPtr, this, _groupName);
  }

  public String getJobDescription() {
    return VISHNUJNI.Job_getJobDescription(swigCPtr, this);
  }

  public void setJobDescription(String _jobDescription) {
    VISHNUJNI.Job_setJobDescription(swigCPtr, this, _jobDescription);
  }

  public int getMemLimit() {
    return VISHNUJNI.Job_getMemLimit(swigCPtr, this);
  }

  public void setMemLimit(int _memLimit) {
    VISHNUJNI.Job_setMemLimit(swigCPtr, this, _memLimit);
  }

  public int getNbNodes() {
    return VISHNUJNI.Job_getNbNodes(swigCPtr, this);
  }

  public void setNbNodes(int _nbNodes) {
    VISHNUJNI.Job_setNbNodes(swigCPtr, this, _nbNodes);
  }

  public String getNbNodesAndCpuPerNode() {
    return VISHNUJNI.Job_getNbNodesAndCpuPerNode(swigCPtr, this);
  }

  public void setNbNodesAndCpuPerNode(String _nbNodesAndCpuPerNode) {
    VISHNUJNI.Job_setNbNodesAndCpuPerNode(swigCPtr, this, _nbNodesAndCpuPerNode);
  }

  public String getBatchJobId() {
    return VISHNUJNI.Job_getBatchJobId(swigCPtr, this);
  }

  public void setBatchJobId(String _batchJobId) {
    VISHNUJNI.Job_setBatchJobId(swigCPtr, this, _batchJobId);
  }

  public String getOutputDir() {
    return VISHNUJNI.Job_getOutputDir(swigCPtr, this);
  }

  public void setOutputDir(String _outputDir) {
    VISHNUJNI.Job_setOutputDir(swigCPtr, this, _outputDir);
  }

  public long getWorkId() {
    return VISHNUJNI.Job_getWorkId(swigCPtr, this);
  }

  public void setWorkId(long _workId) {
    VISHNUJNI.Job_setWorkId(swigCPtr, this, _workId);
  }

  public String getUserId() {
    return VISHNUJNI.Job_getUserId(swigCPtr, this);
  }

  public void setUserId(String _userId) {
    VISHNUJNI.Job_setUserId(swigCPtr, this, _userId);
  }

  public String getVmId() {
    return VISHNUJNI.Job_getVmId(swigCPtr, this);
  }

  public void setVmId(String _vmId) {
    VISHNUJNI.Job_setVmId(swigCPtr, this, _vmId);
  }

  public String getVmIp() {
    return VISHNUJNI.Job_getVmIp(swigCPtr, this);
  }

  public void setVmIp(String _vmIp) {
    VISHNUJNI.Job_setVmIp(swigCPtr, this, _vmIp);
  }

  public String getRelatedSteps() {
    return VISHNUJNI.Job_getRelatedSteps(swigCPtr, this);
  }

  public void setRelatedSteps(String _relatedSteps) {
    VISHNUJNI.Job_setRelatedSteps(swigCPtr, this, _relatedSteps);
  }

  public String getSubmitError() {
    return VISHNUJNI.Job_getSubmitError(swigCPtr, this);
  }

  public void setSubmitError(String _submitError) {
    VISHNUJNI.Job_setSubmitError(swigCPtr, this, _submitError);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.Job_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.Job_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.Job_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.Job_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.Job__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
