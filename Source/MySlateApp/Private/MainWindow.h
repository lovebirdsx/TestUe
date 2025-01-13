#pragma once

class SWindow;

class IMainWindow
{
public:
	static TSharedPtr<IMainWindow> Create();

	virtual ~IMainWindow() = default;	
	virtual TSharedRef<SWindow> CreateMainWindow() = 0;
};
