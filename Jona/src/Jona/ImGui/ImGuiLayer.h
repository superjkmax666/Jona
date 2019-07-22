#pragma once

#include "Jona/Layer.h"

#include "Jona/Events/ApplicationEvent.h"
#include "Jona/Events/KeyEvent.h"
#include "Jona/Events/MouseEvent.h"

namespace Jona {

	class JONA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}