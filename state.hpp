#pragma once

# include "TinyASIO/TinyASIO.hpp"

// 状態遷移
enum class State
{
	SelectingDriver,
	SelectingChannel,
	ShowGuitarPlay
};

asio::Driver* driver;						// ドライバ自体はグローバルに宣言しておく
asio::InputBackController* controller;
size_t indexOfselectedInputChannel;

/**
* ドライバを選択させる
*/
State StateOfSelectingDriver(const Font& font, const asio::DriverList& lists)
{
	static size_t indexForDriver = 0;

	Array<String> options;

	for (size_t i = 0; i < lists.Count(); ++i)
	{
		auto driverName = Unicode::FromWString(lists.Items(i).driverName);
		options.push_back(driverName);
	}

	SimpleGUI::RadioButtons(indexForDriver, options, { 20, 20 });

	const int width = 100;
	const int space = 20;
	if (SimpleGUI::Button(U"Connect", { Window::ClientWidth() - width - space, space }, width))
	{
		driver = &asio::Driver::Init(lists.Items(indexForDriver));
		return State::SelectingChannel;
	}

	return State::SelectingDriver;
}

/**
* 入力1チャンネルに対して，出力多チャンネルに流す
*/
State StateOfSelectingChannel(const Font& font)
{
	const auto& channelManager = driver->ChannelManager();
	static size_t indexForInput = 0;

	Array<String> inputOptions;

	for (size_t i = 0; i < channelManager.NumberOfInputs(); ++i)
	{
		const auto& input = channelManager.Inputs(i);
		inputOptions.push_back(Unicode::Widen(input.name));
	}

	font(U"Select an input channel for output channels.").draw(Vec2{ 20, 20 }, Palette::Black);
	SimpleGUI::RadioButtons(indexForInput, inputOptions, { 20, 60 });

	const int width = 100;
	const int space = 20;
	if (SimpleGUI::Button(U"Connect", { Window::ClientWidth() - width - space, space }, width))
	{
		controller = new asio::InputBackController(driver, channelManager.Inputs(indexForInput));
		controller->Start();
		return State::ShowGuitarPlay;
	}

	return State::SelectingChannel;
}

State StateOfShowGuitarPlay(const Font& font)
{
	static std::vector<double> recordData;
	const auto fetched = controller->Fetch();
	

	const int height = 32;
	font(U"Sampling Rate: ", controller->SampleRate()).draw(0, height * 0);
	font(U"Buffered Size: ", fetched->size()).draw(0, height * 1);
	return State::ShowGuitarPlay;
}