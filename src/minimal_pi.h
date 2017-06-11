/*****************************************************************************
 *
 * Project:  Minimal OpenCPN Plugin
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

#ifndef _MINIMALPI_H_
#define _MINIMALPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/fileconf.h"

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    1

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    14

#include "ocpn_plugin.h"

#include "minimalwindow.h"
//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class minimal_pi : public opencpn_plugin_114
{
public:
      minimal_pi(void *ppimgr);
      ~minimal_pi();

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();

      wxBitmap* GetPlugInBitmap();

      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The optional method overrides

      // void SetNMEASentence(wxString &sentence);
      void OnContextMenuItemCallback(int id);
      void UpdateAuiStatus(void);

//    The override PlugIn Methods
      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      void SetCursorLatLon(double lat, double lon);
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      int GetToolbarToolCount(void);
      void ShowPreferencesDialog( wxWindow* parent );
      void OnToolbarToolCallback(int id);
      void SetPluginMessage(wxString &message_id, wxString &message_body);
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);


private:
      wxWindow         *m_parent_window;

      bool              LoadConfig(void);
      bool              SaveConfig(void);
      wxFileConfig     *m_pconfig;
      bool              m_bShowToolbarIcon;
      int               m_iToolbarIconID;
      bool              m_bShowPluginPanel;

      minimalWindow    *m_pdemo_window;
      wxAuiManager     *m_AUImgr;
      int               m_iButton1ContextActiveID;
      int               m_iButton1ContextDeactiveID;

};

#endif
