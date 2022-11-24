/**
 * @file IEndpoint.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-24 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

namespace systelab { namespace web_server {
	class Reply;
}}

namespace systelab { namespace rest_api_core {

	class EndpointRequestData;

	class IEndpoint
	{
	public:
		virtual ~IEndpoint() {};

		virtual std::unique_ptr<systelab::web_server::Reply> execute(const EndpointRequestData&) = 0;
	};

}}

