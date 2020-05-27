#pragma once

# include "TinyASIO/TinyASIO.hpp"

// 状態遷移
enum class State
{
	SelectingDriver,
	SelectingChannel,
	ShowGuitarPlay
};

asio::Driver* driver;		// ドライバ自体はグローバルに宣言しておく

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
	//static size_t indexForOutput = 0;

	Array<String> inputOptions;
	//Array<String> outputOptions;

	for (size_t i = 0; i < channelManager.NumberOfInputs(); ++i)
	{
		const auto& input = channelManager.Inputs(i);
		inputOptions.push_back(Unicode::Widen(input.name));
	}

	//for (size_t i = 0; i < channelManager.NumberOfOutputs(); ++i)
	//{
	//	const auto& output = channelManager.Outputs(i);
	//	outputOptions.push_back(Unicode::Widen(output.name));
	//}

	font(U"Select an input channel for output channels.").draw(Vec2{ 20, 20 }, Palette::Black);
	SimpleGUI::RadioButtons(indexForInput, inputOptions, { 20, 60 });
	//SimpleGUI::RadioButtons(indexForOutput, outputOptions, { 300, 60 });

	const int width = 100;
	const int space = 20;
	if (SimpleGUI::Button(U"Connect", { Window::ClientWidth() - width - space, space }, width))
	{
		
		return State::SelectingChannel;
	}

	return State::SelectingChannel;
}