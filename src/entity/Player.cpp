#include "Player.h"

#include "../Application.h"

namespace Framework
{
	Player::Player()
	: Entity(100, 100)
	, m_textureAtlas()
	, m_currentFrame(new sf::Texture())
	{
		m_textureAtlas.loadFromFile("res/textures/player_modelDefault.png");

		constexpr static auto MAX_HEALTH = 800;

		addEffect(std::make_unique<HealthBoost>(DURATION_INFINITE, MAX_HEALTH, 0));
		m_health = MAX_HEALTH;

		addEffect(std::make_unique<Defense>(20 * 5, 20, 30));
	}

	Player::~Player()
	{
		delete m_currentFrame;
	}

	float g_movement_speed = 2;

	void Player::input(Application* app)
	{
		m_moveState = MoveState::Idle;

		if (app->inputPressed(MOVE_UP))
		{
			m_moveState = MoveState::Walk;
			velocity.y -= g_movement_speed;
		}
		if (app->inputPressed(MOVE_DOWN))
		{
			m_moveState = MoveState::Walk;
			velocity.y += g_movement_speed;
		}
		if (app->inputPressed(MOVE_LEFT))
		{
			m_faceDir = FaceDirection::Left;
			m_moveState = MoveState::Walk;
			velocity.x -= g_movement_speed;
		}
		if (app->inputPressed(MOVE_RIGHT))
		{
			m_faceDir = FaceDirection::Right;
			m_moveState = MoveState::Walk;
			velocity.x += g_movement_speed;
		}
	}

	void Player::update(float dt)
	{
		Entity::update();

		m_frameCounter++;
		if (m_frameCounter > 5)
		{
			m_frame++;
			m_frameCounter = 0;
		}
		if (m_frame > 7)
			m_frame = 0;

		sf::IntRect sprite_area(m_frame * 32, m_moveState == MoveState::Walk ? 33 : 0, 32, 32);
		m_currentFrame->loadFromImage(m_textureAtlas, sprite_area);
		getShape().setTexture(m_currentFrame);
		getShape().setTextureRect(m_faceDir == FaceDirection::Right ? sf::IntRect(0, 0, 32, 32) : sf::IntRect(32, 0, -32, 32));

		getShape().move(velocity);

		velocity *= 0.5f;
	}

	void Player::applyDamage(const Damage& dmg)
	{
		int32 real_dmg = dmg.amount;

		///@TODO Better algorithm to calculate defenses
		if (dmg.source == DamageSource::Physical)
			real_dmg = m_stats.armor / 100 * dmg.amount;

		if (dmg.source == DamageSource::Magic)
			real_dmg = m_stats.magic_resist / 100 * dmg.amount;

		m_health -= real_dmg;
	}
}
