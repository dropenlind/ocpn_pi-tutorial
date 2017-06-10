#ifndef _DEMOWINDOW_H_
#define _DEMOWINDOW_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

class demoWindow : public wxWindow
{
public:
      demoWindow(wxWindow *pparent, wxWindowID id);
      ~demoWindow();

      void OnPaint(wxPaintEvent& event);
      // void SetSentence(wxString &sentence);
      void OnSize(wxSizeEvent& event);

      wxString          m_NMEASentence;
      double            mLat, mLon, mSog, mCog, mVar;


DECLARE_EVENT_TABLE()
};

#endif
