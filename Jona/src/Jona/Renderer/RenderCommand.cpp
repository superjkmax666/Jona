#include "jnpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Jona {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}