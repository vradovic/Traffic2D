#include "Renderer.h"
#include "GLError.h"

Renderer::~Renderer()
{
	delete m_VA;
	delete m_VB;
	delete m_IB;
	delete m_Shader;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(int mode) const
{
	m_Shader->Bind();
	m_VA->Bind();
	GLCall(glDrawElements(mode, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr));
}

StreetRenderer::StreetRenderer(const std::vector<StreetSegment>& segments, Shader* shader)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int next_index = 0;
	for (size_t i = 0; i < segments.size(); i++)
	{
		StreetSegment segment = segments[i];
		auto lanes = segment.GetLanes();

		for (auto lane : lanes)
		{
			vertices.push_back(lane->GetStart().x);
			vertices.push_back(lane->GetStart().y);
			vertices.push_back(lane->GetColor().x);
			vertices.push_back(lane->GetColor().y);
			vertices.push_back(lane->GetColor().z);
			vertices.push_back(lane->GetEnd().x);
			vertices.push_back(lane->GetEnd().y);
			vertices.push_back(lane->GetColor().x);
			vertices.push_back(lane->GetColor().y);
			vertices.push_back(lane->GetColor().z);
			indices.push_back(next_index);
			indices.push_back(next_index + 1);
			next_index += 2;
		}
	}

	m_VA = new VertexArray();
	m_VB = new VertexBuffer(vertices, 4 * vertices.size());
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	m_VA->AddBuffer(*m_VB, layout);
	m_IB = new IndexBuffer(indices.data(), indices.size());
	m_IB->Bind();
	m_Shader = shader;
}

void StreetRenderer::UpdateBuffer(const std::vector<StreetSegment>& segments)
{
	std::vector<float> vertices;
	for (size_t i = 0; i < segments.size(); i++)
	{
		StreetSegment segment = segments[i];
		auto lanes = segment.GetLanes();

		for (auto lane : lanes)
		{
			vertices.push_back(lane->GetStart().x);
			vertices.push_back(lane->GetStart().y);
			vertices.push_back(lane->GetColor().r);
			vertices.push_back(lane->GetColor().g);
			vertices.push_back(lane->GetColor().b);
			vertices.push_back(lane->GetEnd().x);
			vertices.push_back(lane->GetEnd().y);
			vertices.push_back(lane->GetColor().r);
			vertices.push_back(lane->GetColor().g);
			vertices.push_back(lane->GetColor().b);
		}
	}

	m_VB->Bind();
	m_VB->UpdateData(vertices, 4 * vertices.size());
}

TrafficLightRenderer::TrafficLightRenderer(const std::vector<StreetSegment>& segments, Shader* shader)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int next_index = 0;
	for (size_t i = 0; i < segments.size(); i++)
	{
		StreetSegment segment = segments[i];
		auto lanes = segment.GetLanes();

		for (auto lane : lanes)
		{
			if (lane->GetConnectedLanes().size() < 1) continue;

			Vertex position;
			if (lane->GetStart().x > lane->GetEnd().x)
			{
				position = { lane->GetEnd().x + 0.05f, lane->GetEnd().y + 0.05f };
			}
			else if (lane->GetStart().x < lane->GetEnd().x)
			{
				position = { lane->GetEnd().x - 0.05f, lane->GetEnd().y - 0.05f };
			}
			else if (lane->GetStart().y > lane->GetEnd().y)
			{
				position = { lane->GetEnd().x - 0.05f, lane->GetEnd().y + 0.05f };
			}
			else
			{
				position = { lane->GetEnd().x + 0.05f, lane->GetEnd().y - 0.05f };
			}

			glm::vec3 red = { 1.0f, 0.0f, 0.0f };
			vertices.push_back(position.x - 0.01);
			vertices.push_back(position.y);
			vertices.push_back(red.r);
			vertices.push_back(red.g);
			vertices.push_back(red.b);
			vertices.push_back(position.x + 0.01);
			vertices.push_back(position.y);
			vertices.push_back(red.r);
			vertices.push_back(red.g);
			vertices.push_back(red.b);
			vertices.push_back(position.x);
			vertices.push_back(position.y + 0.01);
			vertices.push_back(red.r);
			vertices.push_back(red.g);
			vertices.push_back(red.b);
			
			indices.push_back(next_index);
			indices.push_back(next_index + 1);
			indices.push_back(next_index + 2);
			next_index += 3;
		}
	}

	m_VA = new VertexArray();
	m_VB = new VertexBuffer(vertices, 4 * vertices.size());
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	m_VA->AddBuffer(*m_VB, layout);
	m_IB = new IndexBuffer(indices.data(), indices.size());
	m_IB->Bind();
	m_Shader = shader;

}

void TrafficLightRenderer::UpdateBuffer(const std::vector<StreetSegment>& segments)
{
	std::vector<float> vertices;
	for (size_t i = 0; i < segments.size(); i++)
	{
		StreetSegment segment = segments[i];
		auto lanes = segment.GetLanes();
		for (auto lane : lanes)
		{
			if (lane->GetConnectedLanes().size() < 1) continue;
			Vertex position;
			if (lane->GetStart().x > lane->GetEnd().x)
			{
				position = { lane->GetEnd().x + 0.02f, lane->GetEnd().y + 0.02f };
			}
			else if (lane->GetStart().x < lane->GetEnd().x)
			{
				position = { lane->GetEnd().x - 0.02f, lane->GetEnd().y - 0.02f };
			}
			else if (lane->GetStart().y > lane->GetEnd().y)
			{
				position = { lane->GetEnd().x - 0.02f, lane->GetEnd().y + 0.02f };
			}
			else
			{
				position = { lane->GetEnd().x + 0.02f, lane->GetEnd().y - 0.02f };
			}

			glm::vec3 color = lane->GetTrafficLightColor();
			vertices.push_back(position.x - 0.02);
			vertices.push_back(position.y);
			vertices.push_back(color.r);
			vertices.push_back(color.g);
			vertices.push_back(color.b);
			vertices.push_back(position.x + 0.02);
			vertices.push_back(position.y);
			vertices.push_back(color.r);
			vertices.push_back(color.g);
			vertices.push_back(color.b);
			vertices.push_back(position.x);
			vertices.push_back(position.y + 0.02);
			vertices.push_back(color.r);
			vertices.push_back(color.g);
			vertices.push_back(color.b);
		}
	}
	m_VB->Bind();
	m_VB->UpdateData(vertices, 4 * vertices.size());
}

TextureRenderer::TextureRenderer(Shader* shader)
{
	std::vector<float> vertices = {
		-1.0f, 1.0f, 0.0f, 0.0f, // x, y, tex_x, tex_y
		-0.1f, 1.0f, 1.0f, 0.0f,
		-0.1f, 0.6f, 1.0f, 1.0f,
		-1.0f, 0.6f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VA = new VertexArray();
	m_VB = new VertexBuffer(vertices, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VA->AddBuffer(*m_VB, layout);

	m_IB = new IndexBuffer(indices, 6);
	m_IB->Bind();
	m_Shader = shader;
}

void TextureRenderer::SetTextureCoordinates(float x, float y, float width, float height)
{
	m_Shader->Bind();
	m_Shader->SetUniform<glm::vec4>("u_TexCoordOffset", glm::vec4(x, y, width, height));
}
