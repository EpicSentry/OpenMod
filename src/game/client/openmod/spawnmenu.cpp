//========= Copyright OpenMod, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "spawnmenu.h"
#include <vgui_controls/ListPanel.h>
#include <vgui_controls/Button.h>
#include <vgui_controls/ComboBox.h>
#include <vgui_controls/CheckButton.h>
#include <vgui_controls/PropertyPage.h>
#include <vgui_controls/PropertySheet.h>
#include <vgui_controls/PropertyDialog.h>
#include <vgui_controls/Controls.h>
#include <vgui_controls/MenuButton.h>
#include <vgui_controls/Menu.h>
#include <vgui_controls/MenuItem.h>
#include "filesystem.h"

using namespace vgui;

class CSMLButton : public MenuButton
{
	typedef MenuButton BaseClass;
public:
	CSMLButton(Panel* parent, const char* panelName, const char* text);

private:
	Menu* m_pMenu;
};

class CSMLCommandButton : public vgui::Button
{
	typedef vgui::Button BaseClass;

public:
	CSMLCommandButton(vgui::Panel* parent, const char* panelName, const char* labelText, const char* command)
		: BaseClass(parent, panelName, labelText)
	{
		AddActionSignalTarget(this);
		SetCommand(command);
	}

	virtual void OnCommand(const char* command)
	{
		engine->ClientCmd((char*)command);
	}

	virtual void OnTick(void)
	{
	}
};

class CSMLPage : public vgui::PropertyPage
{
	typedef vgui::PropertyPage BaseClass;
public:
	CSMLPage(vgui::Panel* parent, const char* panelName)
		: BaseClass(parent, panelName)
	{
		vgui::ivgui()->AddTickSignal(GetVPanel(), 250);
	}

	virtual void OnTick(void)
	{
		BaseClass::OnTick();

		if (!IsVisible())
			return;

		int c = m_LayoutItems.Count();
		for (int i = 0; i < c; i++)
		{
			vgui::Panel* p = m_LayoutItems[i];
			p->OnTick();
		}
	}

	virtual void PerformLayout()
	{
		BaseClass::PerformLayout();
		int x = 5;
		int y = 5;
		int w = 150;
		int h = 18;
		int gap = 2;

		int c = m_LayoutItems.Count();
		int tall = GetTall();

		for (int i = 0; i < c; i++)
		{
			vgui::Panel* p = m_LayoutItems[i];
			p->SetBounds(x, y, w, h);

			y += (h + gap);
			if (y >= tall - h)
			{
				x += (w + gap);
				y = 5;
			}
		}
	}

	void Init(KeyValues* kv)
	{
		for (KeyValues* control = kv->GetFirstSubKey(); control != NULL; control = control->GetNextKey())
		{
			int iType = control->GetInt("imagebutton", 0);

			if (iType == 1)
			{
				const char* a, * b, * c, * t;
				//command
				t = control->GetString("#", "");
				a = control->GetString("normal", "");
				b = control->GetString("overimage", "");
				c = control->GetString("mouseclick", "");

				if (t, a, b, c && t[0], a[0], b[0], c[0])
				{

				}
			}
			else
			{
				const char* m;

				//command
				m = control->GetString("#", "");
				if (m && m[0])
				{
					CSMLCommandButton* btn = new CSMLCommandButton(this, "CommandButton", control->GetName(), m);
					m_LayoutItems.AddToTail(btn);
					continue;
				}
			}
		}
	}
private:
	CUtlVector< vgui::Panel* >		m_LayoutItems;
};

ConVar spawn("cl_propmenu", "0", FCVAR_CLIENTDLL, "spawn menu");

class CSMLMenu : public vgui::PropertyDialog
{
	typedef vgui::PropertyDialog BaseClass;
public:

	CSMLMenu(vgui::VPANEL* parent, const char* panelName)
		: BaseClass(NULL, "SMLenu")
	{
		SetTitle("SPAWN MENU", true);
		SetPos(325, 100);

		KeyValues* kv = new KeyValues("SMLenu");
		if (kv)
		{
			if (kv->LoadFromFile(g_pFullFileSystem, "scripts/props.txt"))
			{
				for (KeyValues* dat = kv->GetFirstSubKey(); dat != NULL; dat = dat->GetNextKey())
				{
					if (!Q_strcasecmp(dat->GetName(), "width"))
					{
						SetWide(dat->GetInt());
						continue;
					}
					else if (!Q_strcasecmp(dat->GetName(), "height"))
					{
						SetTall(dat->GetInt());
						continue;
					}

					CSMLPage* page = new CSMLPage(this, dat->GetName());
					page->Init(dat);

					AddPage(page, dat->GetName());
				}
			}
			kv->deleteThis();
		}

		vgui::ivgui()->AddTickSignal(GetVPanel(), 100);
		//oh ok
		GetPropertySheet()->SetTabWidth(72);
		SetVisible(true);
		SetMouseInputEnabled(true);
		SetSizeable(true);
	}

	void Init(KeyValues* kv);

	void OnTick()
	{
		BaseClass::OnTick();
		SetVisible(spawn.GetBool());
	}

	void OnCommand(const char* command)
	{
		BaseClass::OnCommand(command);

		//if (!Q_stricmp(command, "Close"))
		//{
		//	spawn.SetValue(0);
		//}
	}

};

void CSMLMenu::Init(KeyValues* kv)
{
}

class CSMLPanelInterface : public SMLPanel
{
private:
	CSMLMenu* SMLPanel;
public:
	CSMLPanelInterface()
	{
		SMLPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		SMLPanel = new CSMLMenu(&parent, "SMenu");
	}
	void Destroy()
	{
		if (SMLPanel)
		{
			SMLPanel->SetParent((vgui::Panel*)NULL);
			delete SMLPanel;
		}
	}
	void Activate(void)
	{
		if (SMLPanel)
		{
			SMLPanel->Activate();
		}
	}
};
static CSMLPanelInterface g_SMLPanel;
SMLPanel* smlmenu = (SMLPanel*)&g_SMLPanel;
