/**
 * @file Vote.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * @copyright Copyright (c) 2022
 * 
 */
#include "Poco/Exception.h"
#include "Domain/Model/Poll/Vote.h"

namespace Domain {
namespace Model {
namespace Poll {

   Vote::Vote()
       : _optionIdentity(""),  
         _createdAt()   
      { }   

      Vote::Vote(const std::string & identity, Poco::DateTime createdAt)    
          : _optionIdentity(identity),  
            _createdAt(createdAt)   
      {

            if ( _optionIdentity.empty() ) {
                  throw Poco::InvalidArgumentException("invalid Option Identity");  
            }
      }  

      std::string Vote::optionIdentity() const    
      {
            return _optionIdentity;  
      }   


      Poco::DateTime Vote::createdAt() const   
      {
            return _createdAt;
      }

    }
  }
}






