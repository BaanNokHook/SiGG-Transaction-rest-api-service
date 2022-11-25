/**
 * @file JsonAPIAbstractRelatedResourceBuilder.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * @copyright Copyright (c) 2022
 * 
 */
#include "Interface/Handling/JSONAPI/JsonAPIAbstractRelatedResourceBuilder.h"

namespace Interface {
namespace Handling {

    JsonAPIAbstractRelatedResourceBuilder::JsonAPIAbstractRelatedResourceBuilder(
        const std::string & identifier,  
        const std::string & url  
    )

        : JsonAPIAbstractRelatedResourceBuilder(url),  
        _identifier(identifier)   
    { }  

    std::string JsonAPIAbstractRelatedResourceBuilder::identifier() const  
    {
        return _identifier;   
    }

  }
}


