#include <SFML/Graphics.hpp>
#include "player.h"
#include "error.h"



Player::Player(sf::RenderWindow* pWindow, const char* txtPath, sf::Vector2f pos)
	: playerSprite()
{
	mPWindow = pWindow;
	mPos = pos;
	if (!mTexture.loadFromFile(txtPath))
	{
		ConsoleError::throwError("Player texture loading failed!");
	}
	playerSprite.setTexture(mTexture);
	playerSprite.setPosition(mPos);
	playerSprite.setOrigin(mTexture.getSize().x, mTexture.getSize().y);

	// Setting movement directions booleans
	mIsMovingUp = false;
	mIsMovingDown = false;
	mIsMovingRight = false;
	mIsMovingLeft = false;

	// Setting mouse input booleans to default (false)
	mIsLMBPressed = false;
	mIsRMBPressed = false;

	// Player speed
	playerSpeed = 500.0f;
}

void Player::inputHandleKeyboard(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Player::inputHandleMouse(sf::Mouse::Button button, bool isPressed)
{
	if (button == sf::Mouse::Left)
	{
		mIsLMBPressed = isPressed;
	}
	if (button == sf::Mouse::Right)
	{
		mIsRMBPressed = isPressed;
	}
}

void Player::inputManager()
{
	if (mIsLMBPressed)
	{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*mPWindow);
		playerSprite.setPosition((float)mousePos.x, (float)mousePos.y);
	}
}

void Player::move(const sf::Time* deltaTime)
{
	// Player movement
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= playerSpeed;
	if (mIsMovingDown)
		movement.y += playerSpeed;
	if (mIsMovingLeft)
		movement.x -= playerSpeed;
	if (mIsMovingRight)
		movement.x += playerSpeed;
	playerSprite.move(movement * (*deltaTime).asSeconds());
}



void Player::update(const sf::Time* deltaTime)
{
	move(deltaTime);
	inputManager();
	mPWindow->draw(playerSprite);
}