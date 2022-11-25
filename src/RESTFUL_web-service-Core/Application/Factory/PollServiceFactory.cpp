/**
 * @file PollServiceFactory.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * @copyright Copyright (c) 2022
 * 
 */
#include "Application/Factory/PollServiceFactory.h"
#include "Infrastructure/Persistence/Factory/QuestionVotingServiceFactory.h"
#include "Infrastructure/Persistence/Factory/QuestionRepositoryFactory.h"
#include "Application/PollService.h"

namespace Application {


    PollServiceFactory::PollServiceFactory()
    { }

    Application::IPollService * PollServiceFactory::createService()
    {
        return new PollService(
            Infrastructure::Persistence::QuestionRepositoryFactory::create(),
            Infrastructure::Persistence::QuestionVotingServiceFactory::create()
        );
    }


}
