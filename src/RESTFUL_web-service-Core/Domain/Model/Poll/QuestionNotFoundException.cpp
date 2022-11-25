/**
 * @file QuestionNotFoundException.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * @copyright Copyright (c) 2022
 * 
 */
#include "Domain/Model/Poll/QuestionNotFoundException.h"

namespace Domain {
namespace Model {
namespace Poll {

      QuestionNotFoundException::QuestionNotFoundException()  
            : Exception("Question Not Found", 404)  

      { }

      QuestionNotFoundException::QuestionNotFoundException(const std::string & questionIdentity)    
            : Exception("Question Not Found", "There is any question with id " + questionIdentity, 404)    
      
      { }

      } 
   }
}

