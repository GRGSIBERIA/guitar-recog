#pragma once

# include "TinyASIO/Driver.hpp"

// 状態遷移
enum class State
{
	SelectingDriver,
	SelectingChannel,
	ShowGuitarPlay
};

// ドライバ自体はグローバルに宣言しておく
asio::Driver* driver;

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

State StateOfSelectingChannel(const Font& font)
{
	const auto& channelManager = driver->ChannelManager();
	static size_t indexForInput = 0;
	static size_t indexForOutput = 0;

	Array<String> inputOptions;
	Array<String> outputOptions;

	for (size_t i = 0; i < channelManager.NumberOfInputs(); ++i)
	{
		const auto& input = channelManager.Inputs(i);
		inputOptions.push_back(Unicode::Widen(input.name));
	}

	for (size_t i = 0; i < channelManager.NumberOfOutputs(); ++i)
	{
		const auto& output = channelManager.Outputs(i);
		outputOptions.push_back(Unicode::Widen(output.name));
	}

	SimpleGUI::RadioButtons(indexForInput, inputOptions, { 20, 20 });
	SimpleGUI::RadioButtons(indexForOutput, outputOptions, { 300, 20 });

	const int width = 100;
	const int space = 20;
	if (SimpleGUI::Button(U"Connect", { Window::ClientWidth() - width - space, space }, width))
	{
		return State::SelectingChannel;
	}

	return State::SelectingChannel;
}