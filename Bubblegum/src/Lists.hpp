#pragma once
#include "UI/GUI.hpp"

namespace Big::Lists
{
	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient"
	};

	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::Gradient
	};

	inline std::size_t HeaderTypesPosition = 1;

	inline const char* DemoList[10]
	{
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten"
	};
	inline std::size_t DemoListPos = 0;

	//Level Menu
	inline const char* SelectCharacterLEVEL[3]{
		"Character 1",
		"Character 2",
		"Both"
	};
	inline std::size_t  SelectCharacterPosLEVEL = 0;
	
	inline const char* SelectedCharacterSetSTAT[2]{
		"Character 1",
		"Character 2"
	};
	inline std::size_t  SelectedCharacterPosSetSTAT = 0;

	//Vehicle Lists
	inline const char* SelectedVehicleSuper[4]{
		"adder",
		"bullet",
		"c",
		"d",
	};
	inline std::size_t  SelectedVehicleSuperPos = 0;
}


