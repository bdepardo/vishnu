/**
 * \file OptionValueProxy.hpp
 * \brief This file contains the VISHNU OptionValueProxy class.
 * \author Daouda Traore (daouda.traore@sysfera.com)
 * \date February 2011
 */
#ifndef _OPTION_VALUE_PROXY_H_
#define _OPTION_VALUE_PROXY_H_

#include "SessionProxy.hpp"
#include "OptionValue.hpp"

/**
 * \class OptionValueProxy
 * \brief OptionValueProxy class implementation
 */
class OptionValueProxy
{

  public:

    /**
     * \brief Constructor, raises an exception on error
     * \param optionValue The object which encapsulates the information of the option
     * \param session The object which encapsulates the session information (ex: identifier of the session)
     */
    OptionValueProxy(const UMS_Data::OptionValue& optionValue, const SessionProxy& session);
    /**
     * \brief Function to configure an option of the user
     * \return raises an exception on error
     */
    int configureOption();
    /**
     * \brief Function to configure a default option value
     * \return raises an exception on error
     */
    int configureDefaultOption();
    /**
     * \brief Function get option information
     * \return OptionValue object encapsulates the information of the machine
     * \return raises an exception on error
     */
    UMS_Data::OptionValue getData();
    /**
     * \brief Function get SessionProxy object which contains the VISHNU session identifier
     * \return a SessionProy object which contains the VISHNU session information
     * \return raises an exception on error
     */
    SessionProxy getSessionProxy();
    /**
     * \brief Destructor, raises an exception on error
     */
    ~OptionValueProxy();

  private:

    /**
     * \brief Function to combine configureOption() and configureDefaultOption() into one function
     * \param defaultValue to select the call of configureOption() or configureOption() function
     * \return raises an exception on error
     */
    int setOptionValue(bool defaultValue=true);

    /////////////////////////////////
    // Attributes
    /////////////////////////////////

    /**
     * \brief The object which encapsulates the option information
     */
    UMS_Data::OptionValue moptionValue;
    /**
     * \brief The SessionProxy object containing the encrypted identifier of the session
     *  generated by VISHNU
     */
    SessionProxy msessionProxy;
};
#endif