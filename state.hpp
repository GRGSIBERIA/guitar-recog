#pragma once

# include "TinyASIO/Driver.hpp"

// 状態遷移
enum class State
{
	SelectingDriver,
	SelectingChannel,
	ShowGuitarPlay
};

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

	SimpleGUI::RadioButtons(indexForDriver, options, { 0, 0 });

	const int width = 100;
	const int space = 20;
	if (SimpleGUI::Button(U"Connect", { Window::ClientWidth() - width - space, space }, width))
	{
		driver = &asio::Driver::Init(lists.Items(indexForDriver));
	}

	return State::SelectingDriver;
}

State StateOfSelectingChannel(const Font& font)
{
	auto channelManager = driver->ChannelManager();
	
}