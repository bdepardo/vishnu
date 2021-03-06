/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sysfera.vishnu.api.vishnu.internal;

public class CpFileOptions extends EObject {
  private long swigCPtr;

  public CpFileOptions(long cPtr, boolean cMemoryOwn) {
    super(VISHNUJNI.CpFileOptions_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(CpFileOptions obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        VISHNUJNI.delete_CpFileOptions(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public CpFileOptions() {
    this(VISHNUJNI.new_CpFileOptions(), true);
  }

  public void _initialize() {
    VISHNUJNI.CpFileOptions__initialize(swigCPtr, this);
  }

  public boolean isIsRecursive() {
    return VISHNUJNI.CpFileOptions_isIsRecursive(swigCPtr, this);
  }

  public void setIsRecursive(boolean _isRecursive) {
    VISHNUJNI.CpFileOptions_setIsRecursive(swigCPtr, this, _isRecursive);
  }

  public int getTrCommand() {
    return VISHNUJNI.CpFileOptions_getTrCommand(swigCPtr, this);
  }

  public void setTrCommand(int _trCommand) {
    VISHNUJNI.CpFileOptions_setTrCommand(swigCPtr, this, _trCommand);
  }

  public SWIGTYPE_p_ecorecpp__mapping__any eGet(int _featureID, boolean _resolve) {
    return new SWIGTYPE_p_ecorecpp__mapping__any(VISHNUJNI.CpFileOptions_eGet(swigCPtr, this, _featureID, _resolve), true);
  }

  public void eSet(int _featureID, SWIGTYPE_p_ecorecpp__mapping__any _newValue) {
    VISHNUJNI.CpFileOptions_eSet(swigCPtr, this, _featureID, SWIGTYPE_p_ecorecpp__mapping__any.getCPtr(_newValue));
  }

  public boolean eIsSet(int _featureID) {
    return VISHNUJNI.CpFileOptions_eIsSet(swigCPtr, this, _featureID);
  }

  public void eUnset(int _featureID) {
    VISHNUJNI.CpFileOptions_eUnset(swigCPtr, this, _featureID);
  }

  public SWIGTYPE_p_ecore__EClass _eClass() {
    long cPtr = VISHNUJNI.CpFileOptions__eClass(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_ecore__EClass(cPtr, false);
  }

}
