#include "Renderer.h"
#include "GLError.h"

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

StreetRenderer::StreetRenderer(const std::vector<StreetSegment>& segments, Shader* shader)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int next_index = 0;
	for (size_t i = 0; i < segments.size(); i++)
	{
		StreetSegment segment = segments[i];
		std::vector<StreetSegmentLane> lanes = segment.GetLanes();

		for (const StreetSegmentLane& lane : lanes)
		{
			vertices.push_back(lane.GetStart().x);
			vertices.push_back(lane.GetStart().y);
			vertices.push_back(lane.GetColor().x);
			vertices.push_back(lane.GetColor().y);
			vertices.push_back(lane.GetColor().z);
			vertices.push_back(lane.GetEnd().x);
			vertices.push_back(lane.GetEnd().y);
			vertices.push_back(lane.GetColor().x);
			vertices.push_back(lane.GetColor().y);
			vertices.push_back(lane.GetColor().z);
			indices.push_back(next_index);
			indices.push_back(next_index + 1);
			next_index += 2;
		}
	}

	m_VA = new VertexArray();
	m_VB = new VertexBuffer(vertices.data(), 4 * vertices.size());
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	m_VA->AddBuffer(*m_VB, layout);
	m_IB = new IndexBuffer(indices.data(), indices.size());
	m_IB->Bind();
	m_Shader = shader;
}

StreetRenderer::~StreetRenderer()
{
	delete m_VA;
	delete m_VB;
	delete m_IB;
	delete m_Shader;
}

void StreetRenderer::Draw(int mode) const
{
	m_Shader->Bind();
	m_VA->Bind();
	GLCall(glDrawElements(mode, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void StreetRenderer::UpdateBuffer(const std::vector<StreetSegment>& segments)
{
	std::vector<float> vertices;
	for (size_t i = 0; i < segments.size(); i++)
	{
		StreetSegment segment = segments[i];
		std::vector<StreetSegmentLane> lanes = segment.GetLanes();

		for (const StreetSegmentLane& lane : lanes)
		{
			vertices.push_back(lane.GetStart().x);
			vertices.push_back(lane.GetStart().y);
			vertices.push_back(lane.GetColor().x);
			vertices.push_back(lane.GetColor().y);
			vertices.push_back(lane.GetColor().z);
			vertices.push_back(lane.GetEnd().x);
			vertices.push_back(lane.GetEnd().y);
			vertices.push_back(lane.GetColor().x);
			vertices.push_back(lane.GetColor().y);
			vertices.push_back(lane.GetColor().z);
		}
	}

	m_VB->Bind();
	m_VB->UpdateData(vertices.data(), 4 * vertices.size());
}
