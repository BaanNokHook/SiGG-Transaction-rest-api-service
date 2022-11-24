/**
 * @file IUserRoleService.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-24 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <string>
#include <vector>


namespace systelab { namespace rest_api_core {
	
	class IUserRoleService
	{
	public:
		virtual ~IUserRoleService() = default;

		virtual std::vector<std::string> getUserRoles(const std::string& username) const = 0;
	};

}}
