/* main.cpp
 *
 * Copyright (C) 2017 Rémi Cohen-Scali
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <libglademm.h>

Gtk::Application *pApp = 0;
Gtk::ApplicationWindow *pMainWindow = 0;

void on_toolButtonQuitter_clicked(void *uData)
{
  Gtk::ApplicationWindow *mainWindow = (Gtk::ApplicationWindow*)uData;
  if(mainWindow)
    mainWindow->hide(); //hide() will cause main::run() to end.
}


int main(int   argc,
         char *argv[])
{
  Gtk::Application(argc, argv, "AstExplorer");

  //Load the Glade file and instiate its widgets:
  Glib::RefPtr<Gnome::Glade::Xml> refXml;

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    refXml = Gnome::Glade::Xml::create("AstExplorer.glade");
  }
  catch(const Gnome::Glade::XmlError& ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
#else
  std::auto_ptr<Gnome::Glade::XmlError> error;
  refXml = Gnome::Glade::Xml::create("AstExplorer.glade", "", "", error);
  if(error.get())
  {
    std::cerr << error->what() << std::endl;
    return 1;
  }
#endif

  //Get the Glade-instantiated Dialog:

  refXml->get_widget("applicationWindow", pMainWindow);
  if(pMainWindow)
  {
    pApp.add_window(pMainWindow);

    //Get the Glade-instantiated Button, and connect a signal handler:
    Gtk::Button* pButton = 0;
    refXml->get_widget("toolButtonQuitter", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_toolButtonQuitter_clicked) );
    }

    pApp.run(*pMainWindow);
  }

  return 0;

}
