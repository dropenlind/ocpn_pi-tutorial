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
#include "minimalwindow.h"


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

  // recover configuration object to load and save configuration.
  m_pconfig = GetOCPNConfigObject();


  LoadConfig();

  // Add plugin icon to toolbar
  if (m_bShowToolbarIcon) {
    m_iToolbarIconID = InsertPlugInTool(_T(""), _img_logo, _img_logo,
                              wxITEM_CHECK, _("Minimal plugin"),_T(""),
                              NULL, -1, 0, this);
  }

  // Create the Context Menu Items

  //    In order to avoid an ASSERT on msw debug builds,
  //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
  //    The Items will be re-parented when added to the real context meenu
  wxMenu dummy_menu;

  wxMenuItem *pmi = new wxMenuItem(&dummy_menu, -1, _("Activate Button1"));
  m_iButton1ContextActiveID = AddCanvasContextMenuItem(pmi, this );
  SetCanvasContextMenuItemViz(m_iButton1ContextActiveID, true);

  wxMenuItem *pmih = new wxMenuItem(&dummy_menu, -1, _("Deactivate Button"));
  m_iButton1ContextDeactiveID = AddCanvasContextMenuItem(pmih, this );
  SetCanvasContextMenuItemViz(m_iButton1ContextDeactiveID, false);

  m_pdemo_window = new minimalWindow(m_parent_window);

  m_AUImgr = GetFrameAuiManager();
  m_AUImgr->AddPane(m_pdemo_window);

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
           WANTS_TOOLBAR_CALLBACK         |
           INSTALLS_TOOLBAR_TOOL          |
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

  m_bShowPluginPanel = false;

  SaveConfig();

  RequestRefresh(m_parent_window);

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

}

void minimal_pi::UpdateAuiStatus(void)
{
  return;
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
  wxLogMessage(_T("minimal_pi OnToolbarToolCallback()"));
  ::wxBell();

  //  Note carefully that this is a "reference to a wxAuiPaneInfo classs instance"
  //  Copy constructor (i.e. wxAuiPaneInfo pane = m_AUImgr->GetPane(m_pdemo_window);) will not work

  wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_pdemo_window);
  if(!pane.IsOk())
    return;

  // toggle show panel
  m_bShowPluginPanel = !m_bShowPluginPanel;

  pane.Show(m_bShowPluginPanel);
  m_AUImgr->Update();
}

void minimal_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{

}

void minimal_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{

}

bool minimal_pi::LoadConfig(void)
{
  wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

  if (pConf) {
    pConf->SetPath(_T("/Settings/minimal_pi"));

    pConf->Read(_T("ShowToolBarIcon"), &m_bShowToolbarIcon, 1);
    pConf->Read(_T("ShowPluginPanel"), &m_bShowPluginPanel, 0);

    return true;
  }
  return false;
}

bool minimal_pi::SaveConfig(void)
{
  wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

  if (pConf) {
    pConf->SetPath(_T("/Settings/minimal_pi"));

    pConf->Write(_T("ShowToolBarIcon"), m_bShowToolbarIcon);
    pConf->Read(_T("ShowPluginPanel"), m_bShowPluginPanel);

    return true;
  }
  return false;
}
