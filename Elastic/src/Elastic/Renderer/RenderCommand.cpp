#include "elpch.h"
#include "Elastic/Renderer/RenderCommand.h"

namespace Elastic {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}