#pragma once

#include "Elastic/Core/Base.h"

namespace Elastic {

	class UniformBuffer
	{
	public:
		UniformBuffer(uint32_t size, uint32_t binding);
		~UniformBuffer();
		void SetData(const void* data, uint32_t size, uint32_t offset = 0);

	private:
		uint32_t m_RendererID = 0;
	};

}
