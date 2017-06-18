#include "InputScheme.h"

#include "../../util/Log.h"

namespace Input
{
	InputScheme::InputScheme(std::string fileName)
	{
		initMap();
		using json = nlohmann::json;
		auto source = getFileContents("res/settings/" + fileName);

		json json_ = json::parse(source.c_str());

		for (json::iterator it = json_.begin(); it != json_.end(); ++it)
		{
			m_actionMap[it.key()] = m_nameMap[it.value()];
			LOG_INFO("Mapping ", it.key().c_str(), " to ", m_nameMap[it.value()]);
		}
	}

	sf::Keyboard::Key InputScheme::getKeyForAction(std::string actionName)
	{
		return m_actionMap[actionName];
	}

	void InputScheme::initMap()
	{
		m_nameMap["A"] = sf::Keyboard::A;
		m_nameMap["B"] = sf::Keyboard::B;
		m_nameMap["C"] = sf::Keyboard::C;
		m_nameMap["D"] = sf::Keyboard::D;
		m_nameMap["E"] = sf::Keyboard::E;
		m_nameMap["F"] = sf::Keyboard::F;
		m_nameMap["G"] = sf::Keyboard::G;
		m_nameMap["H"] = sf::Keyboard::H;
		m_nameMap["I"] = sf::Keyboard::I;
		m_nameMap["J"] = sf::Keyboard::J;
		m_nameMap["K"] = sf::Keyboard::K;
		m_nameMap["L"] = sf::Keyboard::L;
		m_nameMap["M"] = sf::Keyboard::M;
		m_nameMap["N"] = sf::Keyboard::N;
		m_nameMap["O"] = sf::Keyboard::O;
		m_nameMap["P"] = sf::Keyboard::P;
		m_nameMap["Q"] = sf::Keyboard::Q;
		m_nameMap["R"] = sf::Keyboard::R;
		m_nameMap["S"] = sf::Keyboard::S;
		m_nameMap["T"] = sf::Keyboard::T;
		m_nameMap["U"] = sf::Keyboard::U;
		m_nameMap["V"] = sf::Keyboard::V;
		m_nameMap["W"] = sf::Keyboard::W;
		m_nameMap["X"] = sf::Keyboard::X;
		m_nameMap["Y"] = sf::Keyboard::Y;
		m_nameMap["Z"] = sf::Keyboard::Z;
		m_nameMap["Num0"] = sf::Keyboard::Num0;
		m_nameMap["Num1"] = sf::Keyboard::Num1;
		m_nameMap["Num2"] = sf::Keyboard::Num2;
		m_nameMap["Num3"] = sf::Keyboard::Num3;
		m_nameMap["Num4"] = sf::Keyboard::Num4;
		m_nameMap["Num5"] = sf::Keyboard::Num5;
		m_nameMap["Num6"] = sf::Keyboard::Num6;
		m_nameMap["Num7"] = sf::Keyboard::Num7;
		m_nameMap["Num8"] = sf::Keyboard::Num8;
		m_nameMap["Num9"] = sf::Keyboard::Num9;
		m_nameMap["Escape"] = sf::Keyboard::Escape;
		m_nameMap["LControl"] = sf::Keyboard::LControl;
		m_nameMap["LShift"] = sf::Keyboard::LShift;
		m_nameMap["LAlt"] = sf::Keyboard::LAlt;
		m_nameMap["LSystem"] = sf::Keyboard::LSystem;
		m_nameMap["RControl"] = sf::Keyboard::RControl;
		m_nameMap["RShift"] = sf::Keyboard::RShift;
		m_nameMap["RAlt"] = sf::Keyboard::RAlt;
		m_nameMap["RSystem"] = sf::Keyboard::RSystem;
		m_nameMap["Menu"] = sf::Keyboard::Menu;
		m_nameMap["LBracket"] = sf::Keyboard::LBracket;
		m_nameMap["RBracket"] = sf::Keyboard::RBracket;
		m_nameMap["SemiColon"] = sf::Keyboard::SemiColon;
		m_nameMap["Comma"] = sf::Keyboard::Comma;
		m_nameMap["Period"] = sf::Keyboard::Period;
		m_nameMap["Quote"] = sf::Keyboard::Quote;
		m_nameMap["Slash"] = sf::Keyboard::Slash;
		m_nameMap["BackSlash"] = sf::Keyboard::BackSlash;
		m_nameMap["Tilde"] = sf::Keyboard::Tilde;
		m_nameMap["Equal"] = sf::Keyboard::Equal;
		m_nameMap["Dash"] = sf::Keyboard::Dash;
		m_nameMap["Space"] = sf::Keyboard::Space;
		m_nameMap["Return"] = sf::Keyboard::Return;
		m_nameMap["BackSpace"] = sf::Keyboard::BackSpace;
		m_nameMap["Tab"] = sf::Keyboard::Tab;
		m_nameMap["PageUp"] = sf::Keyboard::PageUp;
		m_nameMap["PageDown"] = sf::Keyboard::PageDown;
		m_nameMap["End"] = sf::Keyboard::End;
		m_nameMap["Home"] = sf::Keyboard::Home;
		m_nameMap["Insert"] = sf::Keyboard::Insert;
		m_nameMap["Delete"] = sf::Keyboard::Delete;
		m_nameMap["Add"] = sf::Keyboard::Add;
		m_nameMap["Subtract"] = sf::Keyboard::Subtract;
		m_nameMap["Multiply"] = sf::Keyboard::Multiply;
		m_nameMap["Divide"] = sf::Keyboard::Divide;
		m_nameMap["Left"] = sf::Keyboard::Left;
		m_nameMap["Right"] = sf::Keyboard::Right;
		m_nameMap["Up"] = sf::Keyboard::Up;
		m_nameMap["Down"] = sf::Keyboard::Down;
		m_nameMap["Numpad0"] = sf::Keyboard::Numpad0;
		m_nameMap["Numpad1"] = sf::Keyboard::Numpad1;
		m_nameMap["Numpad2"] = sf::Keyboard::Numpad2;
		m_nameMap["Numpad3"] = sf::Keyboard::Numpad3;
		m_nameMap["Numpad4"] = sf::Keyboard::Numpad4;
		m_nameMap["Numpad5"] = sf::Keyboard::Numpad5;
		m_nameMap["Numpad6"] = sf::Keyboard::Numpad6;
		m_nameMap["Numpad7"] = sf::Keyboard::Numpad7;
		m_nameMap["Numpad8"] = sf::Keyboard::Numpad8;
		m_nameMap["Numpad9"] = sf::Keyboard::Numpad9;
		m_nameMap["F1"] = sf::Keyboard::F1;
		m_nameMap["F2"] = sf::Keyboard::F2;
		m_nameMap["F3"] = sf::Keyboard::F3;
		m_nameMap["F4"] = sf::Keyboard::F4;
		m_nameMap["F5"] = sf::Keyboard::F5;
		m_nameMap["F6"] = sf::Keyboard::F6;
		m_nameMap["F7"] = sf::Keyboard::F7;
		m_nameMap["F8"] = sf::Keyboard::F8;
		m_nameMap["F9"] = sf::Keyboard::F9;
		m_nameMap["F10"] = sf::Keyboard::F10;
		m_nameMap["F11"] = sf::Keyboard::F11;
		m_nameMap["F12"] = sf::Keyboard::F12;
		m_nameMap["F13"] = sf::Keyboard::F13;
		m_nameMap["F14"] = sf::Keyboard::F14;
		m_nameMap["F15"] = sf::Keyboard::F15;
		m_nameMap["Pause"] = sf::Keyboard::Pause;
	}
}