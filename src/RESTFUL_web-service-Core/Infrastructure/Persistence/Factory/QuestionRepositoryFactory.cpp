/**
 * @file QuestionRepositoryFactory.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * @copyright Copyright (c) 2022
 * 
 */
#include "Poco/SQL/MySQL/Connector.h"
#include "Infrastructure/Persistence/Factory/QuestionRepositoryFactory.h"
#include "Infrastructure/Persistence/QuestionRepository.h"

namespace Infrastructure {
namespace Persistence {

      Domain::Model::Poll::IQuestionRepository * QuestionRepositoryFactory::create()   
      {
          Infrastructure::Persistence::ConnectionManager connectionManager;  

          Poco::SQL::MySQL::Connector::registerConnector();   
          auto session = connectionManager.getSession();     
          return new Infrastructure::Persistence::QuestionRepository(session);  
      }  

   }
}

