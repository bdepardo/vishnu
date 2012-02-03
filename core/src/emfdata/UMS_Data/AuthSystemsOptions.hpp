// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * UMS_Data/AuthSystemsOptions.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file AuthSystemsOptions.hpp
 * \brief The AuthSystemsOptions class
 * \author Generated file
 * \date 31/03/2011
 */

#ifndef UMS_DATA_AUTHSYSTEMSOPTIONS_HPP
#define UMS_DATA_AUTHSYSTEMSOPTIONS_HPP

#include <UMS_Data_forward.hpp>
#include <ecorecpp/mapping_forward.hpp>

#include <ecore_forward.hpp>

#include <ecore/EObject.hpp>

/*PROTECTED REGION ID(AuthSystemsOptions_pre) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

namespace UMS_Data
{

    /**
     * \class AuthSystemsOptions
     * \brief Implementation of the AuthSystemsOptions class
     */
    class AuthSystemsOptions: public virtual ::ecore::EObject

    {
    public:
        /**
         * \brief The default constructor for AuthSystemsOptions
         */
        AuthSystemsOptions();
        /**
         * \brief The destructor for AuthSystemsOptions
         */
        virtual ~AuthSystemsOptions();

        /**
         * \brief Internal method
         */
        virtual void _initialize();

        // Operations


        // Attributes
        /**
         * \brief To get the ldapBase
         * \return The ldapBase attribute value
         **/
        ::ecore::EString const& getLdapBase() const;
        /**
         * \brief To set the ldapBase
         * \param _ldapBase The ldapBase value
         **/
        void setLdapBase(::ecore::EString const& _ldapBase);

        // References


        /*PROTECTED REGION ID(AuthSystemsOptions) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

        // EObjectImpl
        virtual ::ecore::EJavaObject eGet(::ecore::EInt _featureID,
                ::ecore::EBoolean _resolve);
        virtual void eSet(::ecore::EInt _featureID,
                ::ecore::EJavaObject const& _newValue);
        virtual ::ecore::EBoolean eIsSet(::ecore::EInt _featureID);
        virtual void eUnset(::ecore::EInt _featureID);
        virtual ::ecore::EClass_ptr _eClass();

        /*PROTECTED REGION ID(AuthSystemsOptionsImpl) START*/
        // Please, enable the protected region if you add manually written code.
        // To do this, add the keyword ENABLED before START.
        /*PROTECTED REGION END*/

    protected:
        // Attributes

        ::ecore::EString m_ldapBase;

        // References

    };

} // UMS_Data

#endif // UMS_DATA_AUTHSYSTEMSOPTIONS_HPP