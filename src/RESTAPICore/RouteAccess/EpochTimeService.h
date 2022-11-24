/**
 * @file EpochTimeService.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-24 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "IEpochTimeService.h"


namespace systelab { namespace time {
	class ITimeAdapter;
}}

namespace systelab { namespace rest_api_core {

	class EpochTimeService : public IEpochTimeService
	{
	public:
		EpochTimeService(const systelab::time::ITimeAdapter&);
		virtual ~EpochTimeService();

		long long getCurrentEpochTime() const override;

	private:
		const systelab::time::ITimeAdapter& m_timeAdapter;
	};

}}
