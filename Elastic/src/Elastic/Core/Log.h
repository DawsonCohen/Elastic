#pragma once

#include "Elastic/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Elastic {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

// Core log macros
#define EL_CORE_TRACE(...)    ::Elastic::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EL_CORE_INFO(...)     ::Elastic::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EL_CORE_WARN(...)     ::Elastic::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EL_CORE_ERROR(...)    ::Elastic::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EL_CORE_CRITICAL(...) ::Elastic::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define EL_CORE_FATAL(...)    ::Elastic::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define EL_TRACE(...)	      ::Elastic::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EL_INFO(...)	      ::Elastic::Log::GetClientLogger()->info(__VA_ARGS__)
#define EL_WARN(...)	      ::Elastic::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EL_ERROR(...)	      ::Elastic::Log::GetClientLogger()->error(__VA_ARGS__)
#define EL_CRITICAL(...)      ::Elastic::Log::GetClientLogger()->critical(__VA_ARGS__)
#define EL_FATAL(...)	      ::Elastic::Log::GetClientLogger()->fatal(__VA_ARGS__)