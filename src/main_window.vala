/*
 * This file is part of LaTeXila.
 *
 * Copyright © 2010 Sébastien Wilmet
 *
 * LaTeXila is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LaTeXila is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LaTeXila.  If not, see <http://www.gnu.org/licenses/>.
 */

using Gtk;

public class MainWindow : Window
{
    // for the menu and the toolbar
    // name, stock_id, label, accelerator, tooltip, callback
    private const ActionEntry[] action_entries =
    {
        // File
        { "File", null, N_("_File") },
        { "FileNew", STOCK_NEW, null, null,
            N_("New file"), on_file_new },
        { "FileNewWindow", null, N_("New _Window"), null,
            N_("Create a new window"), on_new_window },
        { "FileOpen", STOCK_OPEN, null, null,
            N_("Open a file"), on_file_open },
        { "FileSave", STOCK_SAVE, null, null,
            N_("Save the current file"), on_file_save },
        { "FileSaveAs", STOCK_SAVE_AS, null, null,
            N_("Save the current file with a different name"), on_file_save_as },
        { "FileClose", STOCK_CLOSE, null, null,
            N_("Close the current file"), on_file_close },
        { "FileQuit", STOCK_QUIT, null, null,
            N_("Quit the program"), on_quit },

        // Edit
        { "Edit", null, N_("_Edit") },
        { "EditUndo", STOCK_UNDO, null, "<Control>Z",
            N_("Undo the last action"), on_edit_undo },
        { "EditRedo", STOCK_REDO, null, "<Shift><Control>Z",
            N_("Redo the last undone action"), on_edit_redo },
        { "EditCut", STOCK_CUT, null, null,
            N_("Cut the selection"), on_edit_cut },
        { "EditCopy", STOCK_COPY, null, null,
            N_("Copy the selection"), on_edit_copy },
        { "EditPaste", STOCK_PASTE, null, null,
            N_("Paste the clipboard"), on_edit_paste },
        { "EditDelete", STOCK_DELETE, null, null,
            N_("Delete the selected text"), on_edit_delete },
        { "EditSelectAll", STOCK_SELECT_ALL, null, "<Control>A",
            N_("Select the entire document"), on_edit_select_all },
        { "EditComment", null, N_("_Comment"), "<Control>D",
            N_("Comment the selected lines (add the character \"%\")"),
            on_edit_comment },
        { "EditUncomment", null, N_("_Uncomment"), "<Shift><Control>D",
            N_("Uncomment the selected lines (remove the character \"%\")"),
            on_edit_uncomment },
        { "EditPreferences", STOCK_PREFERENCES, null, null,
            N_("Configure the application"), on_open_preferences },

        // View
        { "View", null, N_("_View") },
        { "ViewZoomIn", STOCK_ZOOM_IN, N_("Zoom _In"), "<Control>plus",
            N_("Enlarge the font"), on_view_zoom_in },
        { "ViewZoomOut", STOCK_ZOOM_OUT, N_("Zoom _Out"), "<Control>minus",
            N_("Shrink the font"), on_view_zoom_out },
        { "ViewZoomReset", STOCK_ZOOM_100, N_("_Reset Zoom"), "<Control>0",
            N_("Reset the size of the font"), on_view_zoom_reset },

        // Documents
        { "Documents", null, N_("_Documents") },
        { "DocumentsCloseAll", STOCK_CLOSE, N_("_Close All"), "<Shift><Control>W",
            N_("Close all open files"), on_documents_close_all },

        // Help
        { "Help", null, N_("_Help") },
        { "HelpAbout", STOCK_ABOUT, null, null,
            N_("About LaTeXila"), on_about_dialog }
    };

    private string file_chooser_current_folder = Environment.get_home_dir ();
    private DocumentsPanel documents_panel;
    private ActionGroup action_group;
    private CustomStatusbar statusbar;

    public DocumentTab? active_tab
    {
        get
        {
            if (documents_panel.get_n_pages () == 0)
                return null;
            return documents_panel.active_tab;
        }

        set
        {
            int n = documents_panel.page_num (value);
            if (n != -1)
                documents_panel.set_current_page (n);
        }
    }

    public DocumentView? active_view
    {
        get
        {
            if (active_tab == null)
                return null;
            return active_tab.view;
        }
    }

    public Document? active_document
    {
        get
        {
            if (active_tab == null)
                return null;
            return active_tab.document;
        }
    }

    public MainWindow ()
    {
        this.title = "LaTeXila";

        /* restore window state */
        GLib.Settings settings = new GLib.Settings ("org.gnome.latexila.state.window");

        int w, h;
        // FIXME use directly settings.get() when the vapi file is fixed upstream
        Variant variant = settings.get_value ("size");
        variant.get ("(ii)", out w, out h);
        set_default_size (w, h);

        Gdk.WindowState state = (Gdk.WindowState) settings.get_int ("state");
        if ((state & Gdk.WindowState.MAXIMIZED) != 0)
            maximize ();
        else
            unmaximize ();

        if ((state & Gdk.WindowState.STICKY) != 0)
            stick ();
        else
            unstick ();

        /* menu and toolbar */

        // recent documents
        Action recent_action = new RecentAction ("FileOpenRecent", _("Open _Recent"),
            _("Open recently used files"), "");
        configure_recent_chooser ((RecentChooser) recent_action);

        action_group = new ActionGroup ("ActionGroup");
        action_group.set_translation_domain (Config.GETTEXT_PACKAGE);
        action_group.add_actions (action_entries, this);
        action_group.add_action (recent_action);

        var ui_manager = new UIManager ();
        ui_manager.insert_action_group (action_group, 0);
        try
        {
            var path = Path.build_filename (Config.DATA_DIR, "ui", "ui.xml");
            ui_manager.add_ui_from_file (path);
        }
        catch (GLib.Error err)
        {
            error ("%s", err.message);
        }

        add_accel_group (ui_manager.get_accel_group ());

        /* components */
        documents_panel = new DocumentsPanel ();
        var menu = ui_manager.get_widget ("/MainMenu");
        Toolbar toolbar = (Toolbar) ui_manager.get_widget ("/MainToolbar");
        toolbar.set_style (ToolbarStyle.ICONS);
        setup_toolbar_open_button (toolbar);

        statusbar = new CustomStatusbar ();

        /* signal handlers */

        delete_event.connect (() =>
        {
            on_quit ();

            // the destroy signal is not emitted
            return true;
        });

        documents_panel.page_added.connect (() =>
        {
            if (documents_panel.get_n_pages () == 1)
                set_file_actions_sensitivity (true);
        });

        documents_panel.page_removed.connect (() =>
        {
            if (documents_panel.get_n_pages () == 0)
            {
                statusbar.set_cursor_position (-1, -1);
                set_file_actions_sensitivity (false);
            }
            my_set_title ();
        });

        documents_panel.switch_page.connect (() =>
        {
            set_undo_sensitivity ();
            set_redo_sensitivity ();
            my_set_title ();
            update_cursor_position_statusbar ();
        });

        set_file_actions_sensitivity (false);

        /* packing widgets */
        var main_vbox = new VBox (false, 0);
        main_vbox.pack_start (menu, false, false, 0);
        main_vbox.pack_start (toolbar, false, false, 0);
        main_vbox.pack_start (documents_panel, true, true, 0);
        main_vbox.pack_end (statusbar, false, false, 0);

        add (main_vbox);
    }

    public List<Document> get_documents ()
    {
        List<Document> res = null;
        int nb = documents_panel.get_n_pages ();
        for (int i = 0 ; i < nb ; i++)
        {
            DocumentTab tab = (DocumentTab) documents_panel.get_nth_page (i);
            res.append (tab.document);
        }
        return res;
    }

    public List<DocumentView> get_views ()
    {
        List<DocumentView> res = null;
        int nb = documents_panel.get_n_pages ();
        for (int i = 0 ; i < nb ; i++)
        {
            DocumentTab tab = (DocumentTab) documents_panel.get_nth_page (i);
            res.append (tab.view);
        }
        return res;
    }

    public void open_document (File location)
    {
        /* check if the document is already opened */
        foreach (MainWindow w in Application.get_default ().windows)
        {
            foreach (Document doc in w.get_documents ())
            {
                if (doc.location != null && location.equal (doc.location))
                {
                    /* the document is already opened in this window */
                    if (this == w)
                    {
                        active_tab = doc.tab;
                        return;
                    }

                    /* the document is already opened in another window */
                    DocumentTab tab = create_tab_from_location (location, true);
                    tab.view.readonly = true;
                    string primary_msg = _("This file (%s) is already opened in another LaTeXila window.")
                        .printf (location.get_parse_name ());
                    string secondary_msg = _("LaTeXila opened this instance of the file in a non-editable way. Do you want to edit it anyway?");
                    InfoBar infobar = tab.add_message (primary_msg, secondary_msg,
                        MessageType.WARNING);
                    infobar.add_button (_("Edit Anyway"), ResponseType.YES);
                    infobar.add_button (_("Don't Edit"), ResponseType.NO);
                    infobar.response.connect ((response_id) =>
                    {
                        if (response_id == ResponseType.YES)
                            tab.view.readonly = false;
                        infobar.destroy ();
                        tab.view.grab_focus ();
                    });
                    return;
                }
            }
        }

        create_tab_from_location (location, true);
    }

    public DocumentTab? create_tab (bool jump_to)
    {
        var tab = new DocumentTab ();

        /* get unsaved document number */
        uint[] all_nums = {};
        foreach (Document doc in Application.get_default ().get_documents ())
        {
            if (doc.location == null)
                all_nums += doc.unsaved_document_n;
        }

        uint num;
        for (num = 1 ; num in all_nums ; num++);
        tab.document.unsaved_document_n = num;

        return process_create_tab (tab, jump_to);
    }

    public DocumentTab? create_tab_from_location (File location, bool jump_to)
    {
        var tab = new DocumentTab.from_location (location);
        return process_create_tab (tab, jump_to);
    }

    private DocumentTab? process_create_tab (DocumentTab? tab, bool jump_to)
    {
        if (tab == null)
            return null;

        tab.close_document.connect (() => { close_tab (tab); });

        /* sensitivity of undo and redo */
        tab.document.notify["can-undo"].connect (() =>
        {

            if (tab != active_tab)
                return;
            set_undo_sensitivity ();
        });

        tab.document.notify["can-redo"].connect (() =>
        {
            if (tab != active_tab)
                return;
            set_redo_sensitivity ();
        });

        /* sensitivity of cut/copy/delete */
        tab.document.notify["has-selection"].connect (() =>
        {
            if (tab != active_tab)
                return;
            selection_changed ();
        });

        /* set window title */
        tab.document.notify["location"].connect (() =>
        {
            if (tab != active_tab)
                return;
            my_set_title ();
        });

        tab.document.modified_changed.connect (() =>
        {
            if (tab != active_tab)
                return;
            my_set_title ();
        });

        tab.document.cursor_moved.connect (update_cursor_position_statusbar);

        tab.show ();

        // add the tab at the end of the notebook
        documents_panel.add_tab (tab, -1, jump_to);

        set_undo_sensitivity ();
        set_redo_sensitivity ();
        selection_changed ();

        if (! this.get_visible ())
            this.present ();

        return tab;
    }

    // return true if the tab was closed
    public bool close_tab (DocumentTab tab, bool force_close = false)
    {
        /* If document not saved
         * Ask the user if he wants to save the file, or close without saving, or cancel
         */
        if (! force_close && tab.document.get_modified ())
        {
            var dialog = new MessageDialog (this,
                DialogFlags.DESTROY_WITH_PARENT,
                MessageType.QUESTION,
                ButtonsType.NONE,
                _("Save changes to document \"%s\" before closing?"),
                tab.label_text);

            dialog.add_buttons (_("Close without Saving"), ResponseType.CLOSE,
                STOCK_CANCEL, ResponseType.CANCEL);

            if (tab.document.location == null)
                dialog.add_button (STOCK_SAVE_AS, ResponseType.ACCEPT);
            else
                dialog.add_button (STOCK_SAVE, ResponseType.ACCEPT);

            while (true)
            {
                int res = dialog.run ();
                // Close without Saving
                if (res == ResponseType.CLOSE)
                    break;

                // Save or Save As
                else if (res == ResponseType.ACCEPT)
                {
                    if (save_document (tab.document, false))
                        break;
                    continue;
                }

                // Cancel
                else
                {
                    dialog.destroy ();
                    return false;
                }
            }

            dialog.destroy ();
        }

        documents_panel.remove_tab (tab);
        return true;
    }

    public DocumentTab? get_tab_from_location (File location)
    {
        foreach (Document doc in get_documents ())
        {
            if (location.equal (doc.location))
                return doc.tab;
        }

        // not found
        return null;
    }

    public bool is_on_workspace_screen (Gdk.Screen? screen, uint workspace)
    {
        if (screen != null)
        {
            var cur_name = screen.get_display ().get_name ();
            var cur_n = screen.get_number ();
            Gdk.Screen s = this.get_screen ();
            var name = s.get_display ().get_name ();
            var n = s.get_number ();

            if (cur_name != name || cur_n != n)
                return false;
        }

        if (! this.get_realized ())
            this.realize ();

        uint ws = Gedit.Utils.get_window_workspace (this);
        return ws == workspace || ws == Gedit.Utils.Workspace.ALL_WORKSPACES;
    }

    private void set_file_actions_sensitivity (bool sensitive)
    {
        // actions that must be insensitive if the notebook is empty
        string[] file_actions =
        {
            "FileSave", "FileSaveAs", "FileClose", "EditUndo", "EditRedo", "EditCut",
            "EditCopy", "EditPaste", "EditDelete", "EditSelectAll", "EditComment",
            "EditUncomment", "ViewZoomIn", "ViewZoomOut", "ViewZoomReset"
        };

        foreach (string file_action in file_actions)
        {
            Action action = action_group.get_action (file_action);
            action.set_sensitive (sensitive);
        }
    }

    private void set_undo_sensitivity ()
    {
        if (active_tab != null)
        {
            Action action = action_group.get_action ("EditUndo");
            action.set_sensitive (active_document.can_undo);
        }
    }

    private void set_redo_sensitivity ()
    {
        if (active_tab != null)
        {
            Action action = action_group.get_action ("EditRedo");
            action.set_sensitive (active_document.can_redo);
        }
    }

    private void selection_changed ()
    {
        if (active_tab != null)
        {
            bool has_selection = active_document.has_selection;

            // actions that must be insensitive if there is no selection
            string[] selection_actions = { "EditCut", "EditCopy", "EditDelete" };

            foreach (string selection_action in selection_actions)
            {
                Action action = action_group.get_action (selection_action);
                action.set_sensitive (has_selection);
            }
        }
    }

    private void my_set_title ()
    {
        if (active_tab == null)
        {
            set_title ("LaTeXila");
            return;
        }

        uint max_title_length = 100;
        string title = null;
        string dirname = null;

        File loc = active_document.location;
        if (loc == null)
            title = active_document.get_unsaved_document_name ();
        else
        {
            string basename = loc.get_basename ();
            if (basename.length > max_title_length)
                title = Utils.str_middle_truncate (basename, max_title_length);
            else
            {
                title = basename;
                dirname = Utils.str_middle_truncate (
                    Utils.get_dirname_for_display (loc),
                    (uint) long.max (20, max_title_length - basename.length));
            }
        }

        if (active_document.get_modified ())
            title = "*" + title;

        if (active_view.readonly)
        {
            if (dirname != null)
                set_title (title + " [" + _("Read-Only") + "] (" + dirname
                    + ") - LaTeXila");
            else
                set_title (title + " [" + _("Read-Only") + "] - LaTeXila");
        }
        else
        {
            if (dirname != null)
                set_title (title + " (" + dirname + ") - LaTeXila");
            else
                set_title (title + " - LaTeXila");
        }
    }

    // return true if the document has been saved
    public bool save_document (Document doc, bool force_save_as)
    {
        if (! force_save_as && doc.location != null)
        {
            doc.save ();
            return true;
        }

        var file_chooser = new FileChooserDialog (_("Save File"), this,
            FileChooserAction.SAVE,
            STOCK_CANCEL, ResponseType.CANCEL,
            STOCK_SAVE, ResponseType.ACCEPT,
            null);

        file_chooser.set_current_name (doc.tab.label_text);
        if (this.file_chooser_current_folder != null)
            file_chooser.set_current_folder (this.file_chooser_current_folder);

        if (doc.location != null)
        {
            try
            {
                // override the current name and current folder
                file_chooser.set_file (doc.location);
            }
            catch (Error e) {}
        }

        while (file_chooser.run () == ResponseType.ACCEPT)
        {
            File file = file_chooser.get_file ();

            /* if the file exists, ask the user if the file can be replaced */
            if (file.query_exists (null))
            {
                var confirmation = new MessageDialog (this,
                    DialogFlags.DESTROY_WITH_PARENT,
                    MessageType.QUESTION,
                    ButtonsType.NONE,
                    _("A file named \"%s\" already exists. Do you want to replace it?"),
                    file.get_basename ());

                confirmation.add_button (STOCK_CANCEL, ResponseType.CANCEL);

                var button_replace = new Button.with_label (_("Replace"));
                var icon = new Image.from_stock (STOCK_SAVE_AS, IconSize.BUTTON);
                button_replace.set_image (icon);
                confirmation.add_action_widget (button_replace, ResponseType.YES);
                button_replace.show ();

                var response = confirmation.run ();
                confirmation.destroy ();

                if (response != ResponseType.YES)
                    continue;
            }

            doc.location = file;
            break;
        }

        this.file_chooser_current_folder = file_chooser.get_current_folder ();
        file_chooser.destroy ();

        if (doc.location != null)
        {
            doc.save (false);
            return true;
        }
        return false;
    }

    // return true if all the documents are closed
    private bool close_all_documents ()
    {
        /* get unsaved documents */
        List<Document> unsaved_documents = null;

        foreach (Document doc in get_documents ())
        {
            if (doc.get_modified ())
                unsaved_documents.append (doc);
        }

        /* no unsaved document */
        if (unsaved_documents == null)
        {
            documents_panel.remove_all_tabs ();
            return true;
        }

        /* only one unsaved document */
        else if (unsaved_documents.next == null)
        {
            Document doc = unsaved_documents.data;
            active_tab = doc.tab;
            if (close_tab (doc.tab))
            {
                documents_panel.remove_all_tabs ();
                return true;
            }
        }

        /* more than one unsaved document */
        else
        {
            Dialogs.close_several_unsaved_documents (this, unsaved_documents);
            if (documents_panel.get_n_pages () == 0)
                return true;
        }

        return false;
    }

    public void remove_all_tabs ()
    {
        documents_panel.remove_all_tabs ();
    }

    private void update_cursor_position_statusbar ()
    {
        TextIter iter;
        active_document.get_iter_at_mark (out iter, active_document.get_insert ());
        int row = (int) iter.get_line ();
        int col = (int) active_view.my_get_visual_column (iter);
        statusbar.set_cursor_position (row + 1, col + 1);
    }

    private void setup_toolbar_open_button (Toolbar toolbar)
    {
        RecentManager recent_manager = RecentManager.get_default ();
        Widget toolbar_recent_menu = new RecentChooserMenu.for_manager (recent_manager);
        configure_recent_chooser ((RecentChooser) toolbar_recent_menu);

        MenuToolButton open_button = new MenuToolButton.from_stock (STOCK_OPEN);
        open_button.set_menu (toolbar_recent_menu);
        open_button.set_tooltip_text (_("Open a file"));
        open_button.set_arrow_tooltip_text (_("Open a recently used file"));

        Action action = action_group.get_action ("FileOpen");
        open_button.set_related_action (action);

        toolbar.insert (open_button, 1);
    }

    private void configure_recent_chooser (RecentChooser recent_chooser)
    {
        recent_chooser.set_local_only (false);
        recent_chooser.set_sort_type (RecentSortType.MRU);

        RecentFilter filter = new RecentFilter ();
        filter.add_application ("latexila");
        recent_chooser.set_filter (filter);

        recent_chooser.item_activated.connect ((chooser) =>
        {
            string uri = chooser.get_current_uri ();
            open_document (File.new_for_uri (uri));
        });
    }

    public void save_state (bool sync = false)
    {
        GLib.Settings settings = new GLib.Settings ("org.gnome.latexila.state.window");

        // state of the window
        Gdk.WindowState state = get_window ().get_state ();
        settings.set_int ("state", state);

        // get width and height of the window
        int w, h;
        get_size (out w, out h);

        // If window is maximized, store sizes that are a bit smaller than full screen,
        // else making window non-maximized the next time will have no effect.
        if ((state & Gdk.WindowState.MAXIMIZED) != 0)
        {
            w -= 100;
            h -= 100;
        }

        // FIXME use directly settings.set() when the vapi file is fixed upstream
        Variant size = new Variant ("(ii)", w, h);
        settings.set_value ("size", size);

        if (sync)
            settings.sync ();
    }


    /*******************
     *    CALLBACKS
     ******************/

    /* File menu */

    public void on_file_new ()
    {
        create_tab (true);
    }

    public void on_new_window ()
    {
        Application.get_default ().create_window ();
    }

    public void on_file_open ()
    {
        FileChooserDialog file_chooser = new FileChooserDialog (_("Open Files"), this,
            FileChooserAction.OPEN,
            STOCK_CANCEL, ResponseType.CANCEL,
            STOCK_OPEN, ResponseType.ACCEPT,
            null);

        if (this.file_chooser_current_folder != null)
            file_chooser.set_current_folder (this.file_chooser_current_folder);

        file_chooser.select_multiple = true;

        SList<File> files_to_open = null;
        if (file_chooser.run () == ResponseType.ACCEPT)
            files_to_open = file_chooser.get_files ();

        this.file_chooser_current_folder = file_chooser.get_current_folder ();
        file_chooser.destroy ();

        // We open the files after closing the dialog, because open a lot of documents can
        // take some time (this is not async).
        foreach (File file in files_to_open)
            open_document (file);
    }

    public void on_file_save ()
    {
        return_if_fail (active_tab != null);
        save_document (active_document, false);
    }

    public void on_file_save_as ()
    {
        return_if_fail (active_tab != null);
        save_document (active_document, true);
    }

    public void on_file_close ()
    {
        return_if_fail (active_tab != null);
        close_tab (active_tab);
    }

    public void on_quit ()
    {
        if (close_all_documents ())
        {
            save_state ();
            destroy ();
        }
    }

    /* Edit menu */

    public void on_edit_undo ()
    {
        return_if_fail (active_tab != null);
        if (active_document.can_undo)
        {
            active_document.undo ();
            active_view.scroll_to_cursor ();
            active_view.grab_focus ();
        }
    }

    public void on_edit_redo ()
    {
        return_if_fail (active_tab != null);
        if (active_document.can_redo)
        {
            active_document.redo ();
            active_view.scroll_to_cursor ();
            active_view.grab_focus ();
        }
    }

    public void on_edit_cut ()
    {
        return_if_fail (active_tab != null);
        active_view.cut_selection ();
    }

    public void on_edit_copy ()
    {
        return_if_fail (active_tab != null);
        active_view.copy_selection ();
    }

    public void on_edit_paste ()
    {
        return_if_fail (active_tab != null);
        active_view.my_paste_clipboard ();
    }

    public void on_edit_delete ()
    {
        return_if_fail (active_tab != null);
        active_view.delete_selection ();
    }

    public void on_edit_select_all ()
    {
        return_if_fail (active_tab != null);
        active_view.my_select_all ();
    }

    public void on_edit_comment ()
    {
        return_if_fail (active_tab != null);
        active_document.comment_selected_lines ();
    }

    public void on_edit_uncomment ()
    {
        return_if_fail (active_tab != null);
        active_document.uncomment_selected_lines ();
    }

    public void on_open_preferences ()
    {
        PreferencesDialog.show_me (this);
    }

    /* View */

    public void on_view_zoom_in ()
    {
        return_if_fail (active_tab != null);
        active_view.enlarge_font ();
    }

    public void on_view_zoom_out ()
    {
        return_if_fail (active_tab != null);
        active_view.shrink_font ();
    }

    public void on_view_zoom_reset ()
    {
        return_if_fail (active_tab != null);
        active_view.set_font_from_settings ();
    }

    /* Documents */

    public void on_documents_close_all ()
    {
        close_all_documents ();
    }

    /* Help */

    public void on_about_dialog ()
    {
        string comments =
            _("LaTeXila is an Integrated LaTeX Environment for the GNOME desktop");
        string copyright = "Copyright (C) 2009, 2010 Sébastien Wilmet";
        string licence =
"""LaTeXila is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

LaTeXila is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LaTeXila.  If not, see <http://www.gnu.org/licenses/>.""";

		string website = "http://latexila.sourceforge.net/";

		string[] authors =
		{
		    "Sébastien Wilmet <sebastien.wilmet@gmail.com>",
		    null
		};

		string[] artists =
		{
		    "Eric Forgeot <e.forgeot@laposte.net>",
		    "Sébastien Wilmet <sebastien.wilmet@gmail.com>",
		    "The Kile Team: http://kile.sourceforge.net/",
		    "Gedit LaTeX Plugin: http://www.michaels-website.de/gedit-latex-plugin/",
		    null
		};

        Gdk.Pixbuf logo = null;
        try
        {
		    logo = new Gdk.Pixbuf.from_file (Config.DATA_DIR + "/images/app/logo.png");
		}
		catch (Error e)
		{
		    stderr.printf ("Error with the logo: %s\n", e.message);
		}

		show_about_dialog (this,
		    "program-name", "LaTeXila",
		    "version", Config.APP_VERSION,
		    "authors", authors,
		    "artists", artists,
		    "comments", comments,
		    "copyright", copyright,
		    "license", licence,
		    "title", _("About LaTeXila"),
		    "translator-credits", _("translator-credits"),
		    "website", website,
		    "logo", logo,
		    null);
    }
}
