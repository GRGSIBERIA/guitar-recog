
# include <Siv3D.hpp> // OpenSiv3D v0.4.2
# include "TinyASIO/Driver.hpp"

// 状態遷移
enum class State { SelectingDriver, ShowGuitarPlay };

State StateOfSelectingDriver(const Font& font, const asio::DriverList& lists)
{
	static size_t indexForDriver = 0;

	Array<String> options;

	for (size_t i = 0; i < lists.Count(); ++i)
	{
		auto driverName = Unicode::FromWString(lists.Items(i).driverName);
		options.push_back(driverName);
	}

	SimpleGUI::RadioButtons(indexForDriver, options, { 0, 0 });

	return State::SelectingDriver;
}

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
			
			// ボタンが押されたら
			if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
			{
				// 猫の座標を画面内のランダムな位置に移動する
				catPos = RandomVec2(Scene::Rect());
			}
			break;

		case State::ShowGuitarPlay:
			break;
		}
	}
}
