/******************************************************************************
 *
 * Project:  Minimal OpenCPN plugin
 * Author:   Mohamed Saad Ibn Seddik
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mohamed Saad Ibn Seddik   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <wx/aui/aui.h>

#include "minimal_pi.h"


// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
  return new minimal_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
  delete p;
}





//---------------------------------------------------------------------------------------------------------
//
//    demo PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------
minimal_pi::minimal_pi(void *ppimgr):opencpn_plugin_114(ppimgr)
{
  initialize_images();
}


minimal_pi::~minimal_pi()
{
  delete _img_logo_pi;
  delete _img_logo;
  delete m_pdemo_window;
}

int minimal_pi::Init(void)
{
  m_pdemo_window = NULL;

  // Get a pointer to the opencpn display canvas, to use as a parent for windows created
  m_parent_window = GetOCPNCanvasWindow();

  // Create the Context Menu Items

  //    In order to avoid an ASSERT on msw debug builds,
  //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
  //    The Items will be re-parented when added to the real context meenu
  wxMenu dummy_menu;

  wxMenuItem *pmi = new wxMenuItem(&dummy_menu, -1, _("Show PlugIn DemoWindow"));
  m_show_id = AddCanvasContextMenuItem(pmi, this );
  SetCanvasContextMenuItemViz(m_show_id, true);

  wxMenuItem *pmih = new wxMenuItem(&dummy_menu, -1, _("Hide PlugIn DemoWindow"));
  m_hide_id = AddCanvasContextMenuItem(pmih, this );
  SetCanvasContextMenuItemViz(m_hide_id, false);

  m_pdemo_window = new demoWindow(m_parent_window, wxID_ANY);

  m_AUImgr = GetFrameAuiManager();
  m_AUImgr->AddPane(m_pdemo_window);
  m_AUImgr->GetPane(m_pdemo_window).Name(_T("Demo Window Name"));

  m_AUImgr->GetPane(m_pdemo_window).Float();
  m_AUImgr->GetPane(m_pdemo_window).FloatingPosition(300,30);

  m_AUImgr->GetPane(m_pdemo_window).Caption(_T("AUI Managed Demo Window"));
  m_AUImgr->GetPane(m_pdemo_window).CaptionVisible(true);
  m_AUImgr->GetPane(m_pdemo_window).GripperTop(true);
  m_AUImgr->GetPane(m_pdemo_window).CloseButton(true);
  m_AUImgr->GetPane(m_pdemo_window).Show(false);
  m_AUImgr->Update();

  return (
           INSTALLS_CONTEXTMENU_ITEMS     |
           USES_AUI_MANAGER
        );
}

bool minimal_pi::DeInit(void)
{
  m_AUImgr->DetachPane(m_pdemo_window);
  if(m_pdemo_window)
  {
    m_pdemo_window->Close();
  }
  return true;
}

int minimal_pi::GetAPIVersionMajor()
{
  return MY_API_VERSION_MAJOR;
}

int minimal_pi::GetAPIVersionMinor()
{
  return MY_API_VERSION_MINOR;
}

int minimal_pi::GetPlugInVersionMajor()
{
  return PLUGIN_VERSION_MAJOR;
}

int minimal_pi::GetPlugInVersionMinor()
{
  return PLUGIN_VERSION_MINOR;
}

wxBitmap *minimal_pi::GetPlugInBitmap()
{
      return _img_logo_pi;
}

wxString minimal_pi::GetCommonName()
{
  return _("Minimal");
}

wxString minimal_pi::GetShortDescription()
{
  return _("Minimal PlugIn for OpenCPN");
}

wxString minimal_pi::GetLongDescription()
{
  return _("Minimal PlugIn for OpenCPN\n\
to show how to write an easy plugin.");

}


void minimal_pi::OnContextMenuItemCallback(int id)
{
  wxLogMessage(_T("minimal_pi OnContextMenuCallBack()"));
 ::wxBell();

  //  Note carefully that this is a "reference to a wxAuiPaneInfo classs instance"
  //  Copy constructor (i.e. wxAuiPaneInfo pane = m_AUImgr->GetPane(m_pdemo_window);) will not work

  wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_pdemo_window);
  if(!pane.IsOk())
    return;

  if(!pane.IsShown())
  {
//            printf("show\n");
    SetCanvasContextMenuItemViz(m_hide_id, true);
    SetCanvasContextMenuItemViz(m_show_id, false);

    pane.Show(true);
    m_AUImgr->Update();

  }
  else
  {
//            printf("hide\n");
  SetCanvasContextMenuItemViz(m_hide_id, false);
  SetCanvasContextMenuItemViz(m_show_id, true);

  pane.Show(false);
  m_AUImgr->Update();
  }

/*
  if(NULL == m_pdemo_window)
  {
    m_pdemo_window = new demoWindow(m_parent_window, wxID_ANY);

    SetCanvasContextMenuItemViz(m_hide_id, true);
    SetCanvasContextMenuItemViz(m_show_id, false);
  }
  else
  {
    m_pdemo_window->Close();
    m_pdemo_window->Destroy();
    m_pdemo_window = NULL;

    SetCanvasContextMenuItemViz(m_hide_id, false);
    SetCanvasContextMenuItemViz(m_show_id, true);
  }
*/
}

void minimal_pi::UpdateAuiStatus(void)
{
  //    This method is called after the PlugIn is initialized
  //    and the frame has done its initial layout, possibly from a saved wxAuiManager "Perspective"
  //    It is a chance for the PlugIn to syncronize itself internally with the state of any Panes that
  //    were added to the frame in the PlugIn ctor.

  //    We use this callback here to keep the context menu selection in sync with the window state


  wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_pdemo_window);
  if(!pane.IsOk())
    return;

  printf("update %d\n",pane.IsShown());

  SetCanvasContextMenuItemViz(m_hide_id, pane.IsShown());
  SetCanvasContextMenuItemViz(m_show_id, !pane.IsShown());

}

bool minimal_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
  return false;
}

void minimal_pi::SetCursorLatLon(double lat, double lon)
{

}

bool minimal_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
  /*   if(m_pGribDialog && m_pGRIBOverlayFactory)
  {
    if(m_pGRIBOverlayFactory->IsReadyToRender())
    {
      m_pGRIBOverlayFactory->RenderGLGribOverlay ( pcontext, vp );
      return true;
    }
    else
      return false;
  }
  else*/
    return false;
}

int minimal_pi::GetToolbarToolCount(void)
{
  return 1;
}

void minimal_pi::ShowPreferencesDialog( wxWindow* parent )
{

}

void minimal_pi::OnToolbarToolCallback(int id)
{

}

void minimal_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{

}

void minimal_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{

}

//----------------------------------------------------------------
//
//    demo Window Implementation
//
//----------------------------------------------------------------

BEGIN_EVENT_TABLE(demoWindow, wxWindow)
EVT_PAINT ( demoWindow::OnPaint )
EVT_SIZE(demoWindow::OnSize)


END_EVENT_TABLE()

demoWindow::demoWindow(wxWindow *pparent, wxWindowID id)
      :wxWindow(pparent, id, wxPoint(10,10), wxSize(200,200),
             wxSIMPLE_BORDER, _T("OpenCPN PlugIn"))
{
  mLat = 0.0;
  mLon = 1.0;
  mSog = 2.0;
  mCog = 3.0;
  mVar = 4.0;
}

demoWindow::~demoWindow()
{
}

void demoWindow::OnSize(wxSizeEvent& event)
{
  printf("demoWindow OnSize()\n");
}

void demoWindow::OnPaint(wxPaintEvent& event)
{
  wxLogMessage(_T("minimal_pi onpaint"));

  wxPaintDC dc ( this );

  {
    dc.Clear();

    wxString data;
    data.Printf(_T("Lat: %g "), mLat);
    dc.DrawText(data, 10, 10);

    data.Printf(_T("Lon: %g"), mLon);
    dc.DrawText(data, 10, 40);

    data.Printf(_T("Sog: %g"), mSog);
    dc.DrawText(data, 10, 70);

    data.Printf(_T("Cog: %g"), mCog);
    dc.DrawText(data, 10, 100);
  }
}
