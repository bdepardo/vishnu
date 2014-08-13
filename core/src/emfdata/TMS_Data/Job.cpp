// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * TMS_Data/Job.cpp
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

#include "Job.hpp"
#include <ecore/EObject.hpp>
#include <ecore/EClass.hpp>
#include "TMS_Data/TMS_DataPackage.hpp"
#include <ecorecpp/mapping.hpp>

#ifdef ECORECPP_NOTIFICATION_API
#include <ecorecpp/notify.hpp>
#endif

using namespace ::TMS_Data;

// Default constructor
Job::Job() :
    m_nbCpus(-1), m_status(-1), m_submitDate(-1), m_endDate(-1),
            m_wallClockLimit(-1), m_memLimit(-1), m_nbNodes(-1), m_batchJobId(
                    ""), m_workId(0), m_userId(""), m_vmId(""), m_vmIp(""),
            m_priority(-1)
{

    /*PROTECTED REGION ID(JobImpl__JobImpl) START*/
    // Please, enable the protected region if you add manually written code.
    // To do this, add the keyword ENABLED before START.
    /*PROTECTED REGION END*/
}

Job::~Job()
{
}

/*PROTECTED REGION ID(Job.cpp) START*/
// Please, enable the protected region if you add manually written code.
// To do this, add the keyword ENABLED before START.
/*PROTECTED REGION END*/

// Attributes

::ecore::EString const& Job::getSessionId() const
{
    return m_sessionId;
}

void Job::setSessionId(::ecore::EString const& _sessionId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_sessionId = m_sessionId;
#endif
    m_sessionId = _sessionId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__sessionId(),
                _old_sessionId,
                m_sessionId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getMachine() const
{
    return m_machine;
}

void Job::setMachine(::ecore::EString const& _machine)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_machine = m_machine;
#endif
    m_machine = _machine;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__machine(),
                _old_machine,
                m_machine
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getId() const
{
    return m_id;
}

void Job::setId(::ecore::EString const& _id)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_id = m_id;
#endif
    m_id = _id;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__id(),
                _old_id,
                m_id
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getName() const
{
    return m_name;
}

void Job::setName(::ecore::EString const& _name)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_name = m_name;
#endif
    m_name = _name;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__name(),
                _old_name,
                m_name
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getPath() const
{
    return m_path;
}

void Job::setPath(::ecore::EString const& _path)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_path = m_path;
#endif
    m_path = _path;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__path(),
                _old_path,
                m_path
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getOutputPath() const
{
    return m_outputPath;
}

void Job::setOutputPath(::ecore::EString const& _outputPath)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_outputPath = m_outputPath;
#endif
    m_outputPath = _outputPath;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__outputPath(),
                _old_outputPath,
                m_outputPath
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getErrorPath() const
{
    return m_errorPath;
}

void Job::setErrorPath(::ecore::EString const& _errorPath)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_errorPath = m_errorPath;
#endif
    m_errorPath = _errorPath;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__errorPath(),
                _old_errorPath,
                m_errorPath
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Job::getNbCpus() const
{
    return m_nbCpus;
}

void Job::setNbCpus(::ecore::EInt _nbCpus)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_nbCpus = m_nbCpus;
#endif
    m_nbCpus = _nbCpus;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__nbCpus(),
                _old_nbCpus,
                m_nbCpus
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getWorkingDir() const
{
    return m_workingDir;
}

void Job::setWorkingDir(::ecore::EString const& _workingDir)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_workingDir = m_workingDir;
#endif
    m_workingDir = _workingDir;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__workingDir(),
                _old_workingDir,
                m_workingDir
        );
        eNotify(&notification);
    }
#endif
}

::TMS_Data::JobStatus Job::getStatus() const
{
    return m_status;
}

void Job::setStatus(::TMS_Data::JobStatus _status)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::TMS_Data::JobStatus _old_status = m_status;
#endif
    m_status = _status;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__status(),
                _old_status,
                m_status
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong Job::getSubmitDate() const
{
    return m_submitDate;
}

void Job::setSubmitDate(::ecore::ELong _submitDate)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_submitDate = m_submitDate;
#endif
    m_submitDate = _submitDate;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__submitDate(),
                _old_submitDate,
                m_submitDate
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong Job::getEndDate() const
{
    return m_endDate;
}

void Job::setEndDate(::ecore::ELong _endDate)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_endDate = m_endDate;
#endif
    m_endDate = _endDate;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__endDate(),
                _old_endDate,
                m_endDate
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getLocalAccount() const
{
    return m_localAccount;
}

void Job::setLocalAccount(::ecore::EString const& _localAccount)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_localAccount = m_localAccount;
#endif
    m_localAccount = _localAccount;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__localAccount(),
                _old_localAccount,
                m_localAccount
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getQueue() const
{
    return m_queue;
}

void Job::setQueue(::ecore::EString const& _queue)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_queue = m_queue;
#endif
    m_queue = _queue;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__queue(),
                _old_queue,
                m_queue
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong Job::getWallClockLimit() const
{
    return m_wallClockLimit;
}

void Job::setWallClockLimit(::ecore::ELong _wallClockLimit)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_wallClockLimit = m_wallClockLimit;
#endif
    m_wallClockLimit = _wallClockLimit;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__wallClockLimit(),
                _old_wallClockLimit,
                m_wallClockLimit
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getGroupName() const
{
    return m_groupName;
}

void Job::setGroupName(::ecore::EString const& _groupName)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_groupName = m_groupName;
#endif
    m_groupName = _groupName;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__groupName(),
                _old_groupName,
                m_groupName
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getDescription() const
{
    return m_description;
}

void Job::setDescription(::ecore::EString const& _description)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_description = m_description;
#endif
    m_description = _description;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__description(),
                _old_description,
                m_description
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Job::getMemLimit() const
{
    return m_memLimit;
}

void Job::setMemLimit(::ecore::EInt _memLimit)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_memLimit = m_memLimit;
#endif
    m_memLimit = _memLimit;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__memLimit(),
                _old_memLimit,
                m_memLimit
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EInt Job::getNbNodes() const
{
    return m_nbNodes;
}

void Job::setNbNodes(::ecore::EInt _nbNodes)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EInt _old_nbNodes = m_nbNodes;
#endif
    m_nbNodes = _nbNodes;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__nbNodes(),
                _old_nbNodes,
                m_nbNodes
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getNbNodesAndCpuPerNode() const
{
    return m_nbNodesAndCpuPerNode;
}

void Job::setNbNodesAndCpuPerNode(::ecore::EString const& _nbNodesAndCpuPerNode)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_nbNodesAndCpuPerNode = m_nbNodesAndCpuPerNode;
#endif
    m_nbNodesAndCpuPerNode = _nbNodesAndCpuPerNode;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__nbNodesAndCpuPerNode(),
                _old_nbNodesAndCpuPerNode,
                m_nbNodesAndCpuPerNode
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getBatchJobId() const
{
    return m_batchJobId;
}

void Job::setBatchJobId(::ecore::EString const& _batchJobId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_batchJobId = m_batchJobId;
#endif
    m_batchJobId = _batchJobId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__batchJobId(),
                _old_batchJobId,
                m_batchJobId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getOutputDir() const
{
    return m_outputDir;
}

void Job::setOutputDir(::ecore::EString const& _outputDir)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_outputDir = m_outputDir;
#endif
    m_outputDir = _outputDir;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__outputDir(),
                _old_outputDir,
                m_outputDir
        );
        eNotify(&notification);
    }
#endif
}

::ecore::ELong Job::getWorkId() const
{
    return m_workId;
}

void Job::setWorkId(::ecore::ELong _workId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::ELong _old_workId = m_workId;
#endif
    m_workId = _workId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__workId(),
                _old_workId,
                m_workId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getUserId() const
{
    return m_userId;
}

void Job::setUserId(::ecore::EString const& _userId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_userId = m_userId;
#endif
    m_userId = _userId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__userId(),
                _old_userId,
                m_userId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getVmId() const
{
    return m_vmId;
}

void Job::setVmId(::ecore::EString const& _vmId)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_vmId = m_vmId;
#endif
    m_vmId = _vmId;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__vmId(),
                _old_vmId,
                m_vmId
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getVmIp() const
{
    return m_vmIp;
}

void Job::setVmIp(::ecore::EString const& _vmIp)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_vmIp = m_vmIp;
#endif
    m_vmIp = _vmIp;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__vmIp(),
                _old_vmIp,
                m_vmIp
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getRelatedSteps() const
{
    return m_relatedSteps;
}

void Job::setRelatedSteps(::ecore::EString const& _relatedSteps)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_relatedSteps = m_relatedSteps;
#endif
    m_relatedSteps = _relatedSteps;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__relatedSteps(),
                _old_relatedSteps,
                m_relatedSteps
        );
        eNotify(&notification);
    }
#endif
}

::ecore::EString const& Job::getSubmitError() const
{
    return m_submitError;
}

void Job::setSubmitError(::ecore::EString const& _submitError)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::ecore::EString _old_submitError = m_submitError;
#endif
    m_submitError = _submitError;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__submitError(),
                _old_submitError,
                m_submitError
        );
        eNotify(&notification);
    }
#endif
}

::TMS_Data::JobStatus Job::getPriority() const
{
    return m_priority;
}

void Job::setPriority(::TMS_Data::JobStatus _priority)
{
#ifdef ECORECPP_NOTIFICATION_API
    ::TMS_Data::JobStatus _old_priority = m_priority;
#endif
    m_priority = _priority;
#ifdef ECORECPP_NOTIFICATION_API
    if (eNotificationRequired())
    {
        ::ecorecpp::notify::Notification notification(
                ::ecorecpp::notify::Notification::SET,
                (::ecore::EObject_ptr) this,
                (::ecore::EStructuralFeature_ptr) ::TMS_Data::TMS_DataPackage::_instance()->getJob__priority(),
                _old_priority,
                m_priority
        );
        eNotify(&notification);
    }
#endif
}

// References

