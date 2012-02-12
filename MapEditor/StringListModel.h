#pragma once

class StringListModel :
	public gcn::ListModel
{
public:
	int getNumberOfElements()
	{
		return mStrings.size();
	}

	std::string getElementAt(int i)
	{
		if (i >= mStrings.size()) //TODO: guichan bug?
			return "err";
		return mStrings.at(i);
	}

	void add(std::string str)
	{
		mStrings.push_back(str);
	}
	
	StringListModel(void);
	~StringListModel(void);

private:
	std::vector<std::string> mStrings;
};

