/**
 * @file QuestionVotingServiceFactory.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * @copyright Copyright (c) 2022
 * 
 */
#include "Poco/SQL/MySQL/Connector.h"
#include "Infrastructure/Persistence/QuestionVotingService.h"
#include "Infrastructure/Persistence/Factory/QuestionVotingServiceFactory.h"

namespace Infrastructure {
namespace Persistence {

    Domain::Service::IQuestionVotingService * QuestionVotingServiceFactory::create()  
    {

        Infrastructure::Persistence::ConnectionManager connectionManager;  


        Poco::SQL::MySQL::Connector::registerConnector();
        auto session = connectionManager.getSession();   

        return new QuestionVotingService(session);     
    }   
  
  }  
}
