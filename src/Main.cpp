#include"oxuCore/game.hpp"

int main()
{

	/*sf::TcpListener listener;

	if(listener.listen(666) != sf::Socket::Done)
	{
		std::cout<<"err\n";
	}

	sf::TcpSocket client;
	listener.setBlocking(false);
	if (listener.accept(client) != sf::Socket::Done)
	{
		std::cout<<"no luck\n";
	}*/

	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	oxu::Game game;
	game.run();

	return 0;
}