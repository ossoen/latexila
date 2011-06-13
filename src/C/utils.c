/* utils.c generated by valac 0.12.1, the Vala compiler
 * generated from utils.vala, do not modify */

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

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xregion.h>
#include <stdio.h>
#include <gdk-pixbuf/gdk-pixdata.h>

#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

#define TYPE_BUILD_TOOL (build_tool_get_type ())

#define TYPE_BUILD_JOB (build_job_get_type ())
typedef struct _BuildJob BuildJob;
typedef struct _BuildTool BuildTool;
#define _gtk_tree_path_free0(var) ((var == NULL) ? NULL : (var = (gtk_tree_path_free (var), NULL)))

struct _BuildJob {
	gboolean must_succeed;
	gchar* post_processor;
	gchar* command;
	gchar** command_args;
	gint command_args_length1;
};

struct _BuildTool {
	gchar* description;
	gchar* extensions;
	gchar* label;
	gchar* icon;
	gboolean compilation;
	GList* jobs;
};



void utils_flush_queue (void);
gchar* utils_str_middle_truncate (const gchar* str, guint max_length);
gchar* utils_replace_home_dir_with_tilde (const gchar* uri);
gchar* utils_uri_get_dirname (const gchar* uri);
gchar* utils_get_dirname_for_display (GFile* location);
gchar* utils_get_shortname (const gchar* path);
glong utils_get_extension_pos (const gchar* path);
gchar* utils_get_extension (const gchar* path);
#define UTILS_ALL_WORKSPACES ((guint) 0xffffff)
guint utils_get_window_workspace (GtkWindow* gtkwindow);
GtkWidget* utils_add_scrollbar (GtkWidget* child);
GType build_tool_get_type (void) G_GNUC_CONST;
GType build_job_get_type (void) G_GNUC_CONST;
BuildJob* build_job_dup (const BuildJob* self);
void build_job_free (BuildJob* self);
void build_job_copy (const BuildJob* self, BuildJob* dest);
void build_job_destroy (BuildJob* self);
BuildTool* build_tool_dup (const BuildTool* self);
void build_tool_free (BuildTool* self);
void build_tool_copy (const BuildTool* self, BuildTool* dest);
void build_tool_destroy (BuildTool* self);
void utils_print_build_tool (BuildTool* build_tool);
void utils_delete_file (GFile* file);
gboolean utils_tree_model_iter_prev (GtkTreeModel* model, GtkTreeIter* iter);
void utils_set_entry_error (GtkWidget* entry, gboolean _error_);
gint utils_get_selected_row (GtkTreeView* view, GtkTreeIter* iter_to_set);
GdkPixbuf* utils_get_pixbuf_from_stock (const gchar* stock_id, GtkIconSize size);


void utils_flush_queue (void) {
	while (TRUE) {
		gboolean _tmp0_;
		_tmp0_ = gtk_events_pending ();
		if (!_tmp0_) {
			break;
		}
		gtk_main_iteration ();
	}
}


static gchar* string_slice (const gchar* self, glong start, glong end) {
	gchar* result = NULL;
	gint _tmp0_;
	glong string_length;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	gchar* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = strlen (self);
	string_length = (glong) _tmp0_;
	if (start < 0) {
		start = string_length + start;
	}
	if (end < 0) {
		end = string_length + end;
	}
	if (start >= 0) {
		_tmp1_ = start <= string_length;
	} else {
		_tmp1_ = FALSE;
	}
	g_return_val_if_fail (_tmp1_, NULL);
	if (end >= 0) {
		_tmp2_ = end <= string_length;
	} else {
		_tmp2_ = FALSE;
	}
	g_return_val_if_fail (_tmp2_, NULL);
	g_return_val_if_fail (start <= end, NULL);
	_tmp3_ = g_strndup (((gchar*) self) + start, (gsize) (end - start));
	result = _tmp3_;
	return result;
}


gchar* utils_str_middle_truncate (const gchar* str, guint max_length) {
	gchar* result = NULL;
	gint _tmp0_;
	guint half_length;
	gint _tmp2_;
	gint l;
	gchar* _tmp3_ = NULL;
	gchar* _tmp4_;
	gchar* _tmp5_;
	gchar* _tmp6_;
	gchar* _tmp7_ = NULL;
	gchar* _tmp8_;
	gchar* _tmp9_;
	gchar* _tmp10_;
	g_return_val_if_fail (str != NULL, NULL);
	_tmp0_ = strlen (str);
	if (_tmp0_ <= max_length) {
		gchar* _tmp1_;
		_tmp1_ = g_strdup (str);
		result = _tmp1_;
		return result;
	}
	half_length = (max_length - 4) / 2;
	_tmp2_ = strlen (str);
	l = _tmp2_;
	_tmp3_ = string_slice (str, (glong) 0, (glong) half_length);
	_tmp4_ = _tmp3_;
	_tmp5_ = g_strconcat (_tmp4_, "...", NULL);
	_tmp6_ = _tmp5_;
	_tmp7_ = string_slice (str, (glong) (l - half_length), (glong) l);
	_tmp8_ = _tmp7_;
	_tmp9_ = g_strconcat (_tmp6_, _tmp8_, NULL);
	_tmp10_ = _tmp9_;
	_g_free0 (_tmp8_);
	_g_free0 (_tmp6_);
	_g_free0 (_tmp4_);
	result = _tmp10_;
	return result;
}


gchar* utils_replace_home_dir_with_tilde (const gchar* uri) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_;
	gchar* home;
	gboolean _tmp3_;
	gchar* _tmp10_;
	g_return_val_if_fail (uri != NULL, NULL);
	g_return_val_if_fail (uri != NULL, NULL);
	_tmp0_ = g_get_home_dir ();
	_tmp1_ = g_strdup (_tmp0_);
	home = _tmp1_;
	if (g_strcmp0 (uri, home) == 0) {
		gchar* _tmp2_;
		_tmp2_ = g_strdup ("~");
		result = _tmp2_;
		_g_free0 (home);
		return result;
	}
	_tmp3_ = g_str_has_prefix (uri, home);
	if (_tmp3_) {
		gint _tmp4_;
		gint _tmp5_;
		gchar* _tmp6_ = NULL;
		gchar* _tmp7_;
		gchar* _tmp8_;
		gchar* _tmp9_;
		_tmp4_ = strlen (home);
		_tmp5_ = strlen (uri);
		_tmp6_ = string_slice (uri, (glong) _tmp4_, (glong) _tmp5_);
		_tmp7_ = _tmp6_;
		_tmp8_ = g_strconcat ("~", _tmp7_, NULL);
		_tmp9_ = _tmp8_;
		_g_free0 (_tmp7_);
		result = _tmp9_;
		_g_free0 (home);
		return result;
	}
	_tmp10_ = g_strdup (uri);
	result = _tmp10_;
	_g_free0 (home);
	return result;
}


gchar* utils_uri_get_dirname (const gchar* uri) {
	gchar* result = NULL;
	gchar* _tmp0_ = NULL;
	gchar* dir;
	gchar* _tmp1_ = NULL;
	g_return_val_if_fail (uri != NULL, NULL);
	g_return_val_if_fail (uri != NULL, NULL);
	_tmp0_ = g_path_get_dirname (uri);
	dir = _tmp0_;
	if (g_strcmp0 (dir, ".") == 0) {
		result = NULL;
		_g_free0 (dir);
		return result;
	}
	_tmp1_ = utils_replace_home_dir_with_tilde (dir);
	result = _tmp1_;
	_g_free0 (dir);
	return result;
}


gchar* utils_get_dirname_for_display (GFile* location) {
	gchar* result = NULL;
	GMount* _tmp0_ = NULL;
	GMount* mount;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_;
	gchar* mount_name;
	gchar* _tmp3_ = NULL;
	gchar* _tmp4_;
	gchar* _tmp6_ = NULL;
	gchar* dirname;
	gboolean _tmp7_ = FALSE;
	gchar* _tmp8_;
	gchar* _tmp9_;
	gchar* _tmp10_;
	gchar* _tmp11_;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (location != NULL, NULL);
	_tmp0_ = g_file_find_enclosing_mount (location, NULL, &_inner_error_);
	mount = _tmp0_;
	if (_inner_error_ != NULL) {
		goto __catch40_g_error;
	}
	_tmp1_ = g_mount_get_name (mount);
	_tmp2_ = g_strdup (_tmp1_);
	mount_name = _tmp2_;
	_tmp3_ = g_file_get_path (location);
	_tmp4_ = _tmp3_;
	if (_tmp4_ == NULL) {
		gchar* _tmp5_ = NULL;
		_tmp5_ = g_file_get_uri (location);
		_g_free0 (_tmp4_);
		_tmp4_ = _tmp5_;
	}
	_tmp6_ = utils_uri_get_dirname (_tmp4_);
	dirname = _tmp6_;
	if (dirname == NULL) {
		_tmp7_ = TRUE;
	} else {
		_tmp7_ = g_strcmp0 (dirname, ".") == 0;
	}
	if (_tmp7_) {
		result = mount_name;
		_g_free0 (dirname);
		_g_free0 (_tmp4_);
		_g_object_unref0 (mount);
		return result;
	}
	_tmp8_ = g_strconcat (mount_name, " ", NULL);
	_tmp9_ = _tmp8_;
	_tmp10_ = g_strconcat (_tmp9_, dirname, NULL);
	_tmp11_ = _tmp10_;
	_g_free0 (_tmp9_);
	result = _tmp11_;
	_g_free0 (dirname);
	_g_free0 (_tmp4_);
	_g_free0 (mount_name);
	_g_object_unref0 (mount);
	return result;
	_g_free0 (dirname);
	_g_free0 (_tmp4_);
	_g_free0 (mount_name);
	_g_object_unref0 (mount);
	goto __finally40;
	__catch40_g_error:
	{
		GError * e;
		gchar* _tmp12_ = NULL;
		gchar* _tmp13_;
		gchar* _tmp15_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp12_ = g_file_get_path (location);
		_tmp13_ = _tmp12_;
		if (_tmp13_ == NULL) {
			gchar* _tmp14_ = NULL;
			_tmp14_ = g_file_get_uri (location);
			_g_free0 (_tmp13_);
			_tmp13_ = _tmp14_;
		}
		_tmp15_ = utils_uri_get_dirname (_tmp13_);
		result = _tmp15_;
		_g_free0 (_tmp13_);
		_g_error_free0 (e);
		return result;
	}
	__finally40:
	g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
	g_clear_error (&_inner_error_);
	return NULL;
}


gchar* utils_get_shortname (const gchar* path) {
	gchar* result = NULL;
	glong _tmp0_;
	gchar* _tmp1_ = NULL;
	g_return_val_if_fail (path != NULL, NULL);
	_tmp0_ = utils_get_extension_pos (path);
	_tmp1_ = string_slice (path, (glong) 0, _tmp0_);
	result = _tmp1_;
	return result;
}


gchar* utils_get_extension (const gchar* path) {
	gchar* result = NULL;
	glong _tmp0_;
	gint _tmp1_;
	gchar* _tmp2_ = NULL;
	g_return_val_if_fail (path != NULL, NULL);
	_tmp0_ = utils_get_extension_pos (path);
	_tmp1_ = strlen (path);
	_tmp2_ = string_slice (path, _tmp0_, (glong) _tmp1_);
	result = _tmp2_;
	return result;
}


static gchar string_get (const gchar* self, glong index) {
	gchar result = '\0';
	g_return_val_if_fail (self != NULL, '\0');
	result = ((gchar*) self)[index];
	return result;
}


glong utils_get_extension_pos (const gchar* path) {
	glong result = 0L;
	gint _tmp0_;
	glong l;
	g_return_val_if_fail (path != NULL, 0L);
	_tmp0_ = strlen (path);
	l = (glong) _tmp0_;
	{
		glong i;
		i = l - 1;
		{
			gboolean _tmp1_;
			_tmp1_ = TRUE;
			while (TRUE) {
				gchar _tmp2_;
				if (!_tmp1_) {
					i--;
				}
				_tmp1_ = FALSE;
				if (!(i >= 0)) {
					break;
				}
				_tmp2_ = string_get (path, i);
				if (_tmp2_ == '/') {
					result = l;
					return result;
				} else {
					gchar _tmp3_;
					_tmp3_ = string_get (path, i);
					if (_tmp3_ == '.') {
						result = i;
						return result;
					}
				}
			}
		}
	}
	result = l;
	return result;
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


guint utils_get_window_workspace (GtkWindow* gtkwindow) {
	guint result = 0U;
	gboolean _tmp0_;
	guint ret;
	GdkWindow* _tmp1_ = NULL;
	GdkWindow* _tmp2_;
	GdkWindow* window;
	GdkDisplay* _tmp3_ = NULL;
	GdkDisplay* _tmp4_;
	GdkDisplay* display;
	Display* _tmp5_ = NULL;
	Display* x_display;
	Atom type;
	gint format = 0;
	gulong nitems = 0UL;
	gulong bytes_after = 0UL;
	guint* workspace = NULL;
	XID _tmp6_;
	Atom _tmp7_;
	Atom _tmp8_;
	gint _tmp9_;
	gulong _tmp10_;
	gulong _tmp11_;
	void* _tmp12_ = NULL;
	gint _tmp13_;
	gint _result_;
	gint _tmp14_;
	gint err;
	gboolean _tmp15_ = FALSE;
	gboolean _tmp16_ = FALSE;
	gboolean _tmp17_ = FALSE;
	g_return_val_if_fail (gtkwindow != NULL, 0U);
	_tmp0_ = gtk_widget_get_realized ((GtkWidget*) gtkwindow);
	g_return_val_if_fail (_tmp0_, 0);
	ret = UTILS_ALL_WORKSPACES;
	_tmp1_ = gtk_widget_get_window ((GtkWidget*) gtkwindow);
	_tmp2_ = _g_object_ref0 (_tmp1_);
	window = _tmp2_;
	_tmp3_ = gdk_drawable_get_display ((GdkDrawable*) window);
	_tmp4_ = _g_object_ref0 (_tmp3_);
	display = _tmp4_;
	_tmp5_ = gdk_x11_display_get_xdisplay (display);
	x_display = _tmp5_;
	gdk_error_trap_push ();
	_tmp6_ = gdk_x11_drawable_get_xid ((GdkDrawable*) window);
	_tmp7_ = gdk_x11_get_xatom_by_name_for_display (display, "_NET_WM_DESKTOP");
	_tmp13_ = XGetWindowProperty (x_display, (Window) _tmp6_, _tmp7_, (glong) 0, G_MAXLONG, FALSE, XA_CARDINAL, &_tmp8_, &_tmp9_, &_tmp10_, &_tmp11_, (unsigned char **) (&_tmp12_));
	type = _tmp8_;
	format = _tmp9_;
	nitems = _tmp10_;
	bytes_after = _tmp11_;
	workspace = _tmp12_;
	_result_ = _tmp13_;
	_tmp14_ = gdk_error_trap_pop ();
	err = _tmp14_;
	if (err != Success) {
		_tmp15_ = TRUE;
	} else {
		_tmp15_ = _result_ != Success;
	}
	if (_tmp15_) {
		result = ret;
		_g_object_unref0 (display);
		_g_object_unref0 (window);
		return result;
	}
	if (type == XA_CARDINAL) {
		_tmp17_ = format == 32;
	} else {
		_tmp17_ = FALSE;
	}
	if (_tmp17_) {
		_tmp16_ = nitems > 0;
	} else {
		_tmp16_ = FALSE;
	}
	if (_tmp16_) {
		ret = workspace[0];
	}
	XFree (workspace);
	result = ret;
	_g_object_unref0 (display);
	_g_object_unref0 (window);
	return result;
}


GtkWidget* utils_add_scrollbar (GtkWidget* child) {
	GtkWidget* result = NULL;
	GtkScrolledWindow* _tmp0_ = NULL;
	GtkScrolledWindow* scrollbar;
	g_return_val_if_fail (child != NULL, NULL);
	_tmp0_ = (GtkScrolledWindow*) gtk_scrolled_window_new (NULL, NULL);
	scrollbar = g_object_ref_sink (_tmp0_);
	gtk_scrolled_window_set_policy (scrollbar, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add ((GtkContainer*) scrollbar, child);
	result = (GtkWidget*) scrollbar;
	return result;
}


static gchar* bool_to_string (gboolean self) {
	gchar* result = NULL;
	if (self) {
		gchar* _tmp0_;
		_tmp0_ = g_strdup ("true");
		result = _tmp0_;
		return result;
	} else {
		gchar* _tmp1_;
		_tmp1_ = g_strdup ("false");
		result = _tmp1_;
		return result;
	}
}


void utils_print_build_tool (BuildTool* build_tool) {
	fprintf (stdout, "\n=== Build Tool ===\n");
	fprintf (stdout, "desc: %s\n", (*build_tool).description);
	fprintf (stdout, "ext: %s\n", (*build_tool).extensions);
	fprintf (stdout, "label: %s\n", (*build_tool).label);
	fprintf (stdout, "icon: %s\n\n", (*build_tool).icon);
	{
		GList* build_job_collection;
		GList* build_job_it;
		build_job_collection = (*build_tool).jobs;
		for (build_job_it = build_job_collection; build_job_it != NULL; build_job_it = build_job_it->next) {
			BuildJob _tmp0_;
			BuildJob _tmp1_ = {0};
			BuildJob build_job;
			build_job_copy ((BuildJob*) build_job_it->data, &_tmp1_);
			_tmp0_ = _tmp1_;
			build_job = _tmp0_;
			{
				gchar* _tmp2_ = NULL;
				gchar* _tmp3_;
				fprintf (stdout, "== Build Job ==\n");
				_tmp2_ = bool_to_string (build_job.must_succeed);
				_tmp3_ = _tmp2_;
				fprintf (stdout, "must succeed: %s\n", _tmp3_);
				_g_free0 (_tmp3_);
				fprintf (stdout, "post processor: %s\n", build_job.post_processor);
				fprintf (stdout, "command: %s\n\n", build_job.command);
				build_job_destroy (&build_job);
			}
		}
	}
}


void utils_delete_file (GFile* file) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (file != NULL);
	g_file_delete (file, NULL, &_inner_error_);
	if (_inner_error_ != NULL) {
		goto __catch41_g_error;
	}
	goto __finally41;
	__catch41_g_error:
	{
		GError * e;
		gchar* _tmp0_ = NULL;
		gchar* _tmp1_;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp0_ = g_file_get_parse_name (file);
		_tmp1_ = _tmp0_;
		fprintf (stderr, "Warning: delete file \"%s\" failed: %s\n", _tmp1_, e->message);
		_g_free0 (_tmp1_);
		_g_error_free0 (e);
	}
	__finally41:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


gboolean utils_tree_model_iter_prev (GtkTreeModel* model, GtkTreeIter* iter) {
	gboolean result = FALSE;
	GtkTreePath* _tmp0_ = NULL;
	GtkTreePath* path;
	gboolean _tmp1_;
	g_return_val_if_fail (model != NULL, FALSE);
	_tmp0_ = gtk_tree_model_get_path (model, iter);
	path = _tmp0_;
	_tmp1_ = gtk_tree_path_prev (path);
	if (_tmp1_) {
		GtkTreeIter _tmp2_ = {0};
		gboolean _tmp3_;
		gboolean ret;
		_tmp3_ = gtk_tree_model_get_iter (model, &_tmp2_, path);
		*iter = _tmp2_;
		ret = _tmp3_;
		result = ret;
		_gtk_tree_path_free0 (path);
		return result;
	}
	result = FALSE;
	_gtk_tree_path_free0 (path);
	return result;
}


void utils_set_entry_error (GtkWidget* entry, gboolean _error_) {
	g_return_if_fail (entry != NULL);
	if (_error_) {
		GdkColor red = {0};
		GdkColor white = {0};
		GdkColor _tmp0_ = {0};
		GdkColor _tmp1_ = {0};
		gdk_color_parse ("#FF6666", &_tmp0_);
		red = _tmp0_;
		gdk_color_parse ("white", &_tmp1_);
		white = _tmp1_;
		gtk_widget_modify_base (entry, GTK_STATE_NORMAL, &red);
		gtk_widget_modify_text (entry, GTK_STATE_NORMAL, &white);
	} else {
		gtk_widget_modify_base (entry, GTK_STATE_NORMAL, NULL);
		gtk_widget_modify_text (entry, GTK_STATE_NORMAL, NULL);
	}
}


gint utils_get_selected_row (GtkTreeView* view, GtkTreeIter* iter_to_set) {
	GtkTreeIter _iter_to_set = {0};
	gint result = 0;
	GtkTreeSelection* _tmp0_ = NULL;
	GtkTreeSelection* _tmp1_;
	GtkTreeSelection* select;
	GtkTreeIter iter = {0};
	GtkTreeIter _tmp2_ = {0};
	gboolean _tmp3_;
	g_return_val_if_fail (view != NULL, 0);
	_tmp0_ = gtk_tree_view_get_selection (view);
	_tmp1_ = _g_object_ref0 (_tmp0_);
	select = _tmp1_;
	_tmp3_ = gtk_tree_selection_get_selected (select, NULL, &_tmp2_);
	iter = _tmp2_;
	if (_tmp3_) {
		GtkTreeModel* _tmp4_ = NULL;
		GtkTreeModel* _tmp5_;
		GtkTreeModel* model;
		GtkTreePath* _tmp6_ = NULL;
		GtkTreePath* path;
		gint* _tmp7_ = NULL;
		if ((&_iter_to_set) != NULL) {
			_iter_to_set = iter;
		}
		_tmp4_ = gtk_tree_view_get_model (view);
		_tmp5_ = _g_object_ref0 (_tmp4_);
		model = _tmp5_;
		_tmp6_ = gtk_tree_model_get_path (model, &iter);
		path = _tmp6_;
		_tmp7_ = gtk_tree_path_get_indices (path);
		result = _tmp7_[0];
		_gtk_tree_path_free0 (path);
		_g_object_unref0 (model);
		_g_object_unref0 (select);
		if (iter_to_set) {
			*iter_to_set = _iter_to_set;
		}
		return result;
	}
	result = -1;
	_g_object_unref0 (select);
	if (iter_to_set) {
		*iter_to_set = _iter_to_set;
	}
	return result;
}


GdkPixbuf* utils_get_pixbuf_from_stock (const gchar* stock_id, GtkIconSize size) {
	GdkPixbuf* result = NULL;
	GtkInvisible* _tmp0_ = NULL;
	GtkInvisible* w;
	GdkPixbuf* _tmp1_ = NULL;
	GdkPixbuf* pixbuf;
	g_return_val_if_fail (stock_id != NULL, NULL);
	_tmp0_ = (GtkInvisible*) gtk_invisible_new ();
	w = g_object_ref_sink (_tmp0_);
	_tmp1_ = gtk_widget_render_icon ((GtkWidget*) w, stock_id, size, "vala");
	pixbuf = _tmp1_;
	result = pixbuf;
	_g_object_unref0 (w);
	return result;
}


