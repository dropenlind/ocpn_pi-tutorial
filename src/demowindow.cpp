#include "demowindow.h"

BEGIN_EVENT_TABLE(demoWindow, wxWindow)
EVT_PAINT ( demoWindow::OnPaint )
EVT_SIZE(demoWindow::OnSize)


END_EVENT_TABLE()

demoWindow::demoWindow(wxWindow *pparent, wxWindowID id)
      :wxWindow(pparent, id, wxPoint(10,10), wxSize(200,200),
             wxSIMPLE_BORDER, _T("OpenCPN PlugIn"))
{
  mLat = 0.0;
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
  }

  {
    // note that _img_logo has been globally initialized by the plugin
    dc.DrawBitmap(*_img_logo, 84, 0);
  }
}
