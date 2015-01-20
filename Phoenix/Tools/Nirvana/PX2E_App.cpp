/*
*
* �ļ�����	��	PX2E_App.cpp
*
*/

#include "PX2E_App.hpp"
#include "PX2E_MainFrame.hpp"
#include "PX2E_RenderView.hpp"
#include "PX2E_ResTree.hpp"
#include "PX2EngineLoop.hpp"
#include "PX2Edit.hpp"
using namespace PX2Editor;
using namespace PX2;

//-----------------------------------------------------------------------------
IMPLEMENT_APP(PX2Editor::E_App)
//-----------------------------------------------------------------------------
E_App::E_App()
{
}
//-----------------------------------------------------------------------------
E_App::~E_App()
{
}
//-----------------------------------------------------------------------------
bool E_App::OnInit()
{
	Edit::SetEditForm(wxID_HIGHEST);

	wxLog::SetLogLevel(0);

	wxImage::AddHandler(new wxBMPHandler());
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxGIFHandler());

	int displayWidth, displayHeight;
	wxDisplaySize(&displayWidth, &displayHeight);

#if defined _DEBUG
#if defined(_WIN64) || defined(WIN64)
	mMainFrame = new E_MainFrame("NirvanaDx964D", 0, 0, wxMin(1024,
		displayWidth), wxMin(768, displayHeight));
#else
	mMainFrame = new E_MainFrame("NirvanaDx9D", 0, 0, wxMin(1024,
		displayWidth), wxMin(768, displayHeight));
#endif
#else
#if defined(_WIN64) || defined(WIN64)
	mMainFrame = new E_MainFrame("NirvanaDx964", 0, 0, wxMin(1024,
		displayWidth), wxMin(768, displayHeight));
#else
	mMainFrame = new E_MainFrame("NirvanaDx9", 0, 0, wxMin(1024,
		displayWidth), wxMin(768, displayHeight));
#endif
#endif

	mMainFrame->Initlize();

	mMainFrame->Show(true);
	SetTopWindow(mMainFrame);
	mMainFrame->Center();
	mMainFrame->Maximize();

	PX2_ENGINELOOP.SetPt_Data(mMainFrame->GetRenderView()->GetHandle());
	PX2_ENGINELOOP.SetPt_Size(Sizef(1024.0f, 768.0f));
	PX2_ENGINELOOP.Initlize();

	Edit *edit = new0 Edit();
	edit->Initlize();

	ResTree::GetSingleton().UpdateOnPath("Data/");

	return true;
}
//-----------------------------------------------------------------------------
int E_App::OnExit()
{
	Edit *edit = Edit::GetSingletonPtr();
	if (edit)
	{
		edit->Ternamate();
		delete0(edit);
		Edit::Set(0);
	}

	PX2_ENGINELOOP.Ternamate();

	return 0;
}
//-----------------------------------------------------------------------------