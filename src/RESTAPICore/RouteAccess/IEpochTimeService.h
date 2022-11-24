/**
 * @file IEpochTimeService.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-24 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once


namespace systelab { namespace rest_api_core {
	
	class IEpochTimeService
	{
	public:
		virtual ~IEpochTimeService() = default;

		virtual long long getCurrentEpochTime() const = 0;
	};

}}
