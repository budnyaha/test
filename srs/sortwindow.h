#ifndef SRS_SORTWINDOW_H_
#define SRS_SORTWINDOW_H_

#include <gtkmm.h>
#include <vector>
#include "grup.h"

class SortWindow : public Gtk::Window
{
public:
	SortWindow();
  ~SortWindow() override;

protected:
  void fill_buffers();
  void on_dropdown_sort();
  void on_button_new();
  void on_button_sawe();
  void start_dialog();

  void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
      const Glib::RefPtr<Gtk::FileDialog>& dialog);

  const char* path;
  int selected = 0;
  std::string text_File;
  std::vector<object> file;

  Gtk::Box m_HBox_DropDown, m_HBox_New, m_HBox_Preview;
  Gtk::Box m_VBox_Top, m_VBox2;

  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1;
  Gtk::Entry m_Entry_Name, m_Entry_X, m_Entry_Y, m_Entry_Type;
  Gtk::DropDown m_DropDown_Sort;
  Gtk::Button m_Button_New, m_Button_Save;
  Gtk::TextView m_TextView_Preview;
  Gtk::ScrolledWindow m_ScrolledWindow;
};




#endif /* SRS_SORTWINDOW_H_ */
