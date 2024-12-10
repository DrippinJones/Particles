#include "Engine.h"
#include "Matrices.h"
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

using namespace std;
using namespace sf;



// The Engine constructor
Engine::Engine()
{
	VideoMode screen(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2, Style::Default);
	m_Window.create(screen, "nootice");
}

// Run will call all the private functions
void Engine::run()
{
	Clock clock;
	Time t1 = clock.getElapsedTime();

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("hawkTuah.wav"))
		return;

	
	sound.setBuffer(buffer);

	while (m_Window.isOpen())
	{
		t1 = clock.restart();

		input();
		update(t1.asSeconds());
		draw();

	}
}

// Private functions for internal use only
void Engine::input()
{
	Event event;
	srand(time(0));

	
	
	
	
	while (m_Window.pollEvent(event))
	{
		
		if (event.type == Event::Closed) // event might be a problem
		{
			m_Window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				sound.play();

				for (int i = 0; i < 5; i++)
				{
					int randNum = rand() % 26 + 25; // Random number [25, 50]
					m_particles.push_back(Particle(m_Window, randNum, Vector2i(event.mouseButton.x, event.mouseButton.y)));
				}

				//sound.stop();
			}

		}
	}
	
}

void Engine::update(float dtAsSeconds)
{
	
	for (auto it = m_particles.begin(); it != m_particles.end(); )
	{
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
			++it; 
		}
		else
		{
			it = m_particles.erase(it);
		}
	}

}

void Engine::draw()
{
	m_Window.clear();

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("brainrot.png"))
		return;

	Vector2f spriteSize(900.0f, 1200.0f);

	Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale(spriteSize.x / backgroundSprite.getLocalBounds().width, spriteSize.x / backgroundSprite.getLocalBounds().height);

	//m_Window.clear();
	//backgroundSprite.setScale(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	m_Window.draw(backgroundSprite);
	//m_Window.display();

	
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}

	m_Window.display();

}
