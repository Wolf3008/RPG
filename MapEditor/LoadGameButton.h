#pragma once

class LoadGameButton :
	public gcn::Button
{
public:
	char* continueFlag;

	void mouseClicked(gcn::MouseEvent& mouseEvent);
	
	LoadGameButton(std::string label);
	~LoadGameButton(void);
};
