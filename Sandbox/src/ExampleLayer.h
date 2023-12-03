#pragma once

#include "Elastic.h"

class ExampleLayer : public Elastic::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Elastic::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Elastic::Event& e) override;
private:
	Elastic::ShaderLibrary m_ShaderLibrary;
	Elastic::Ref<Elastic::Shader> m_Shader;
	Elastic::Ref<Elastic::VertexArray> m_VertexArray;

	Elastic::Ref<Elastic::Shader> m_FlatColorShader;
	Elastic::Ref<Elastic::VertexArray> m_SquareVA;

	Elastic::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

