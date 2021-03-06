#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "MenuEventReceiver.h"
#include "EditorEventReceiver.h"
#include "Universe.h"
#include "Render.h"

Render::Render(int screenWidth, int screenHeight)
{
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(screenWidth, screenHeight), 16, false, false, false, NULL); //(IEventReceiver*)editorEventReceiver
	device->setResizable(true);
	if (!device)
		return;
	device->setWindowCaption(L"RPGator");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	
	
}

Render::~Render(void)
{
}

void Render::drawScene()
{

}

void Render::createMenu()
{

}

void Render::drawKub(f32 xPos,f32 yPos,f32 zPos)
{
	ISceneNode* n = smgr->addCubeSceneNode(); // ������� �� ����� ���
        if (n)
        {
				n->setPosition(core::vector3df(xPos,yPos,zPos)); // ������������ �����
                n->setMaterialTexture(0, driver->getTexture("grass.bmp")); // ������������ ���
                n->setMaterialFlag(video::EMF_LIGHTING, false); // ��������� ��������� ���������
				//n->scal
        }
}