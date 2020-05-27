
# include <Siv3D.hpp> // OpenSiv3D v0.4.2
# include "state.hpp"

void Main()
{
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	const Font font(24);

	const auto pathes = asio::Registry::GetAsioDriverPathes();

	State state = State::SelectingDriver;

	while (System::Update())
	{
		switch (state) {
		case State::SelectingDriver:
			state = StateOfSelectingDriver(font, pathes);
			break;

		case State::SelectingChannel:
			state = StateOfSelectingChannel(font);
			break;

		case State::ShowGuitarPlay:
			break;
		}
	}

	driver->Dispose();
}
