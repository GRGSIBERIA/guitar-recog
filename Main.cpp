
# include <Siv3D.hpp> // OpenSiv3D v0.4.2
# include "state.hpp"

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	// 大きさ 60 のフォントを用意
	const Font font(60);

	// 猫のテクスチャを用意
	const Texture cat(Emoji(U"🐈"));

	// 猫の座標
	Vec2 catPos(640, 450);

	// ドライバーのパスを描画
	const auto pathes = asio::Registry::GetAsioDriverPathes();

	State state = State::SelectingDriver;

	while (System::Update())
	{
		switch (state) {
		case State::SelectingDriver:
			state = StateOfSelectingDriver(font, pathes);
			break;

		case State::SelectingChannel:
			break;

		case State::ShowGuitarPlay:
			break;
		}
	}
}
