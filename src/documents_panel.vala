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

public class DocumentsPanel : Notebook
{
    public DocumentsPanel ()
    {
        this.set_scrollable (true);
    }

    public void add_tab (DocumentTab tab, int position, bool jump_to)
    {
        int i = this.insert_page (tab, tab.label, position);
        this.set_tab_reorderable (tab, true);
        if (jump_to)
            this.set_current_page (i);
    }

    public void remove_tab (DocumentTab tab)
    {
        int pos = page_num (tab);
        remove_page (pos);
    }
}
