#include "StdAfx.h"
#include "MapObjectSelectWindow.h"

MapObjectSelectWindow::MapObjectSelectWindow(std::string caption, MapObject** mapObjects, int mapObjectsCount) : Window(caption)
{
	int i, j;
	vector<std::string> tags;

	this->setFocusable(true);
	this->setVisible(false);
	
	okButton = new MenuButton("Test");
	this->add(okButton, 512, 320);

	//Tags collecting
	//TODO: All checked/unchecked
	//tags.push_back("All");
	for (i = 0; i < mapObjectsCount; i++)
	{
		for (j = 0; j < mapObjects[i]->tagsCount; j++)
		{
			if (std::find(tags.begin(), tags.end(), mapObjects[i]->tags[j]) == tags.end())
				tags.push_back(mapObjects[i]->tags[j]);
		}
	}
	tagsCount = tags.size();
	mapObjectsTags = new gcn::CheckBox*[tagsCount];
	for (i = 0; i < tagsCount; i++)
	{
		mapObjectsTags[i] = new gcn::CheckBox(tags[i]);
		mapObjectsTags[i]->setFocusable(false);
		this->add(mapObjectsTags[i], 8, 8 + 16 * i);
	}

	//NPC select ListBox
	listModel = new StringListModel();
	for (i = 0; i < mapObjectsCount; i++)
		listModel->add(mapObjects[i]->name);
	listBox = new gcn::ListBox(listModel);
	
	//TODO:
	//Auto resize npcSelectListBox. adjustSize doesn't work for width. Sadly...
	listBox->setSize(512, 0);
	listBox->adjustSize();
	
	listBoxScrollArea = new gcn::ScrollArea();
    listBoxScrollArea->setHorizontalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
    listBoxScrollArea->setVerticalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	listBoxScrollArea->setContent(listBox);
	listBoxScrollArea->setVisible(true);
	listBoxScrollArea->setSize(256, 320);
	
	this->add(listBoxScrollArea, 128, 8);

	//NPC preview image
	//gcn::Image* npcPreviewImage = gcn::Image::load("test_preview.bmp"); 
	npcPreviewIcon = new gcn::Icon(gcn::Image::load("test_preview.bmp"));// http://theinsaneatlantian.deviantart.com/art/RPG-Monster-2-252430339?q=boost%3Apopular%20rpg%20monster&qo=36
	this->add(npcPreviewIcon, 400, 8);

	this->resizeToContent();
	this->setPosition((Universe::instance->screenWidth - Universe::instance->toolbarWidth) / 2 - this->getWidth() / 2, Universe::instance->screenHeight / 2 - this->getHeight() / 2);
}


MapObjectSelectWindow::~MapObjectSelectWindow(void)
{
	delete[] mapObjectsTags;
	delete mapObjectsTags;
	delete listModel;
	delete listBox;
	delete listBoxScrollArea;
	delete npcPreviewIcon;
	delete okButton;
}