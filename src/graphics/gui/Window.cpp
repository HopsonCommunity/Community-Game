#include "Window.h"

#include "../../app/Application.h"
#include "../../app/Cursor.h"

#include "../../util/FileUtil.h"

namespace GUI
{
	Window::Window(const std::string& title, const FloatRectangle& bounds, const Vec2& minSize)
		: Widget(bounds)
		, m_title(Graphics::Label(title, Application::get().getFont("/Inconsolata-Bold"), 12))
		, m_minSize(minSize)
	{
		m_title.setPosition({ 6, 3 });
		
		validateSize();
		updateButtons();

		// Setup shader and texture
		sf::Shader* const transparency = new sf::Shader();
		transparency->loadFromMemory(getFileContents("res/shaders/transparency.frag"), sf::Shader::Fragment);
		transparency->setUniform("u_Opacity", .9f);
		transparency->setUniform("u_Texture", sf::Shader::CurrentTexture);

		m_states.blendMode = sf::BlendAlpha;
		m_states.shader = transparency;
		m_states.texture = &Application::get().getTexture("/gui/dev/window");

		rebuildVertexArray();
	}
	
	bool Window::mousePressed(Events::MousePressedEvent& e)
	{
		const Vec2 mouse = Application::get().uiMousePos();

		if (close_button.contains(mouse))
		{
			setActive(false);
			StandardCursor Cursor(StandardCursor::NORMAL);
			Cursor.set(Application::get().getWindow().getSystemHandle());
		}
		if (resize_button.contains(mouse))
		{
			m_resizing.active = true;
			m_resizing.offset = mouse - resize_button.position + Vec2(9, 9);
		}
		if (move_section.contains(mouse))
		{
			m_moving.active = true;
			m_moving.offset = mouse - m_bounds.position;
		}

		return true;
	}

	bool Window::mouseReleased(Events::MouseReleasedEvent& e)
	{
		m_resizing.active = false;
		m_moving.active = false;

		return true;
	}

	bool Window::mouseMoved(Events::MouseMovedEvent& e)
	{
		const Vec2 mouse = Application::get().uiMousePos();

		if (m_resizing.active)
		{
			m_bounds.size = mouse - m_bounds.position + m_resizing.offset;

			validateSize();
			updateButtons();
			
			rebuildVertexArray();
		}

		if (m_moving.active)
		{
			m_bounds.position = mouse - m_moving.offset;
			
			validatePosition();
			updateButtons();
		}

		if (close_button.contains(mouse))
		{
			//StandardCursor Cursor(StandardCursor::HAND);
			//Cursor.set(Application::get().getWindow().getSystemHandle());
		}
		else if (resize_button.contains(mouse))
		{
			//StandardCursor Cursor(StandardCursor::SIZENWSE);
			//Cursor.set(Application::get().getWindow().getSystemHandle());
		}
		else
		{
			//StandardCursor Cursor(StandardCursor::NORMAL);
			//Cursor.set(Application::get().getWindow().getSystemHandle());
		}

		return false;
	}

	void Window::update()
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_resizing.active = false;
			m_moving.active = false;
		}
	}

	void Window::render(sf::RenderWindow& window)
	{
		m_states.transform = sf::Transform().translate(m_bounds.position);
		window.draw(m_vao.data(), m_vao.size(), sf::Quads, m_states);
		m_title.render(window, m_states);
	}

	void Window::rebuildVertexArray()
	{
		m_vao.clear();

		const float width = m_bounds.width;
		const float height = m_bounds.height;

		///@TODO: Get rid of these hardcoded values
		// Top left corner
		m_vao.push_back({ { 0, 0 },{ 0, 0 } });
		m_vao.push_back({ { 32, 0 },{ 32, 0 } });
		m_vao.push_back({ { 32, 32 },{ 32, 32 } });
		m_vao.push_back({ { 0, 32 },{ 0, 32 } });

		// Top edge
		m_vao.push_back({ { 32, 0 },{ 32, 0 } });
		m_vao.push_back({ { width - 32, 0 },{ 64, 0 } });
		m_vao.push_back({ { width - 32, 32 },{ 64, 32 } });
		m_vao.push_back({ { 32, 32 },{ 32, 32 } });

		// Top right corner
		m_vao.push_back({ { width - 32, 0 },{ 64, 0 } });
		m_vao.push_back({ { width, 0 },{ 96, 0 } });
		m_vao.push_back({ { width, 32 },{ 96, 32 } });
		m_vao.push_back({ { width - 32, 32 },{ 64, 32 } });

		// Right edge
		m_vao.push_back({ { width - 32, 32 },{ 64, 32 } });
		m_vao.push_back({ { width, 32 },{ 96, 32 } });
		m_vao.push_back({ { width, height - 32 },{ 96, 64 } });
		m_vao.push_back({ { width - 32, height - 32 },{ 64, 64 } });

		// Bottom right corner
		m_vao.push_back({ { width - 32, height - 32 },{ 64, 64 } });
		m_vao.push_back({ { width, height - 32 },{ 96, 64 } });
		m_vao.push_back({ { width, height },{ 96, 96 } });
		m_vao.push_back({ { width - 32, height },{ 64, 96 } });

		// Bottom edge
		m_vao.push_back({ { 32, height - 32 },{ 32, 64 } });
		m_vao.push_back({ { width - 32, height - 32 },{ 64, 64 } });
		m_vao.push_back({ { width - 32, height },{ 64, 96 } });
		m_vao.push_back({ { 32, height },{ 32, 96 } });

		// Bottom left corner
		m_vao.push_back({ { 0, height - 32 },{ 0, 64 } });
		m_vao.push_back({ { 32, height - 32 },{ 32, 64 } });
		m_vao.push_back({ { 32, height },{ 32, 96 } });
		m_vao.push_back({ { 0, height },{ 0, 96 } });

		// Left edge
		m_vao.push_back({ { 0, 32 },{ 0, 32 } });
		m_vao.push_back({ { 32, 32 },{ 32, 32 } });
		m_vao.push_back({ { 32, height - 32 },{ 32, 64 } });
		m_vao.push_back({ { 0, height - 32 },{ 0, 64 } });

		// Center
		m_vao.push_back({ { 32, 32 },{ 32, 32 } });
		m_vao.push_back({ { width - 32, 32 },{ 64, 32 } });
		m_vao.push_back({ { width - 32, height - 32 },{ 64, 64 } });
		m_vao.push_back({ { 32, height - 32 },{ 32, 64 } });
	}

	void Window::validateSize()
	{
		if (m_bounds.getMinimumBound().x < 0)
			m_bounds.width = m_bounds.x;
		if (m_bounds.getMaximumBound().x > Application::get().screenWidth())
			m_bounds.width = Application::get().screenWidth() - m_bounds.position.x;

		if (m_bounds.getMinimumBound().y < 0)
			m_bounds.height = m_bounds.y;
		if (m_bounds.getMaximumBound().y > Application::get().screenHeight())
			m_bounds.height = Application::get().screenHeight() - m_bounds.position.y;

		if (m_bounds.width < m_minSize.x)
			m_bounds.width = m_minSize.x;
		if (m_bounds.height < m_minSize.y)
			m_bounds.height = m_minSize.y;
	}

	void Window::validatePosition()
	{
		if (m_bounds.x < 0)
			m_bounds.x = 0;
		if (m_bounds.getMaximumBound().x > Application::get().screenWidth())
			m_bounds.x = Application::get().screenWidth() - m_bounds.width;

		if (m_bounds.y < 0)
			m_bounds.y = 0;
		if (m_bounds.getMaximumBound().y > Application::get().screenHeight())
			m_bounds.y = Application::get().screenHeight() - m_bounds.height;
	}

	void Window::updateButtons()
	{
		close_button = { m_bounds.x + m_bounds.width - 18, m_bounds.y + 9, 9, 9 };
		resize_button = { m_bounds.x + m_bounds.width - 18, m_bounds.y + m_bounds.height - 18, 11, 11 };
		move_section = { m_bounds.x, m_bounds.y, m_bounds.width, 16 };
	}
}
