/* document_view.c generated by valac 0.12.1, the Vala compiler
 * generated from document_view.vala, do not modify */

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
#include <gtksourceview/gtksourceview.h>
#include <gio/gio.h>
#include <pango/pango.h>
#include <float.h>
#include <math.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gdk/gdk.h>


#define TYPE_DOCUMENT_VIEW (document_view_get_type ())
#define DOCUMENT_VIEW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DOCUMENT_VIEW, DocumentView))
#define DOCUMENT_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DOCUMENT_VIEW, DocumentViewClass))
#define IS_DOCUMENT_VIEW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DOCUMENT_VIEW))
#define IS_DOCUMENT_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DOCUMENT_VIEW))
#define DOCUMENT_VIEW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DOCUMENT_VIEW, DocumentViewClass))

typedef struct _DocumentView DocumentView;
typedef struct _DocumentViewClass DocumentViewClass;
typedef struct _DocumentViewPrivate DocumentViewPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _pango_font_description_free0(var) ((var == NULL) ? NULL : (var = (pango_font_description_free (var), NULL)))

#define TYPE_DOCUMENT (document_get_type ())
#define DOCUMENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_DOCUMENT, Document))
#define DOCUMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_DOCUMENT, DocumentClass))
#define IS_DOCUMENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_DOCUMENT))
#define IS_DOCUMENT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_DOCUMENT))
#define DOCUMENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_DOCUMENT, DocumentClass))

typedef struct _Document Document;
typedef struct _DocumentClass DocumentClass;
#define _g_free0(var) (var = (g_free (var), NULL))

#define TYPE_COMPLETION_PROVIDER (completion_provider_get_type ())
#define COMPLETION_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_COMPLETION_PROVIDER, CompletionProvider))
#define COMPLETION_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_COMPLETION_PROVIDER, CompletionProviderClass))
#define IS_COMPLETION_PROVIDER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_COMPLETION_PROVIDER))
#define IS_COMPLETION_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_COMPLETION_PROVIDER))
#define COMPLETION_PROVIDER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_COMPLETION_PROVIDER, CompletionProviderClass))

typedef struct _CompletionProvider CompletionProvider;
typedef struct _CompletionProviderClass CompletionProviderClass;
typedef struct _Block16Data Block16Data;
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

#define TYPE_APP_SETTINGS (app_settings_get_type ())
#define APP_SETTINGS(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_APP_SETTINGS, AppSettings))
#define APP_SETTINGS_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_APP_SETTINGS, AppSettingsClass))
#define IS_APP_SETTINGS(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_APP_SETTINGS))
#define IS_APP_SETTINGS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_APP_SETTINGS))
#define APP_SETTINGS_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_APP_SETTINGS, AppSettingsClass))

typedef struct _AppSettings AppSettings;
typedef struct _AppSettingsClass AppSettingsClass;

struct _DocumentView {
	GtkSourceView parent_instance;
	DocumentViewPrivate * priv;
};

struct _DocumentViewClass {
	GtkSourceViewClass parent_class;
};

struct _DocumentViewPrivate {
	GSettings* editor_settings;
	PangoFontDescription* font_desc;
};

struct _Block16Data {
	int _ref_count_;
	DocumentView * self;
	CompletionProvider* provider;
};


static gpointer document_view_parent_class = NULL;

GType document_view_get_type (void) G_GNUC_CONST;
#define DOCUMENT_VIEW_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_DOCUMENT_VIEW, DocumentViewPrivate))
enum  {
	DOCUMENT_VIEW_DUMMY_PROPERTY
};
#define DOCUMENT_VIEW_SCROLL_MARGIN 0.02
GType document_get_type (void) G_GNUC_CONST;
DocumentView* document_view_new (Document* doc);
DocumentView* document_view_construct (GType object_type, Document* doc);
static void _lambda14_ (GObject* d, GParamSpec* p, DocumentView* self);
gboolean document_get_readonly (Document* self);
static void __lambda14__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
void document_view_set_font_from_settings (DocumentView* self);
void document_set_style_scheme_from_string (Document* self, const gchar* scheme_id);
GType completion_provider_get_type (void) G_GNUC_CONST;
static Block16Data* block16_data_ref (Block16Data* _data16_);
static void block16_data_unref (Block16Data* _data16_);
CompletionProvider* completion_provider_get_default (void);
static void _lambda15_ (Block16Data* _data16_);
void completion_provider_hide_calltip_window (CompletionProvider* self);
static void __lambda15__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static gboolean document_view_on_backspace (DocumentView* self, GdkEventKey* event);
static gboolean _document_view_on_backspace_gtk_widget_key_press_event (GtkWidget* _sender, GdkEventKey* event, gpointer self);
void document_view_scroll_to_cursor (DocumentView* self, gdouble margin);
void document_view_cut_selection (DocumentView* self);
void document_view_copy_selection (DocumentView* self);
void document_view_my_paste_clipboard (DocumentView* self);
void document_view_delete_selection (DocumentView* self);
void document_view_my_select_all (DocumentView* self);
guint document_view_my_get_visual_column (DocumentView* self, GtkTextIter* iter);
GType app_settings_get_type (void) G_GNUC_CONST;
AppSettings* app_settings_get_default (void);
const gchar* app_settings_get_system_font (AppSettings* self);
void document_view_set_font_from_string (DocumentView* self, const gchar* font);
void document_view_enlarge_font (DocumentView* self);
void document_view_shrink_font (DocumentView* self);
gchar* document_view_get_indentation_style (DocumentView* self);
static void document_view_finalize (GObject* obj);


static void _lambda14_ (GObject* d, GParamSpec* p, DocumentView* self) {
	gboolean _tmp0_;
	g_return_if_fail (d != NULL);
	g_return_if_fail (p != NULL);
	_tmp0_ = document_get_readonly (DOCUMENT (d));
	gtk_text_view_set_editable ((GtkTextView*) self, !_tmp0_);
}


static void __lambda14__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	_lambda14_ (_sender, pspec, self);
}


static Block16Data* block16_data_ref (Block16Data* _data16_) {
	g_atomic_int_inc (&_data16_->_ref_count_);
	return _data16_;
}


static void block16_data_unref (Block16Data* _data16_) {
	if (g_atomic_int_dec_and_test (&_data16_->_ref_count_)) {
		_g_object_unref0 (_data16_->self);
		_g_object_unref0 (_data16_->provider);
		g_slice_free (Block16Data, _data16_);
	}
}


static void _lambda15_ (Block16Data* _data16_) {
	DocumentView * self;
	self = _data16_->self;
	completion_provider_hide_calltip_window (_data16_->provider);
}


static void __lambda15__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	_lambda15_ (self);
}


static gboolean _document_view_on_backspace_gtk_widget_key_press_event (GtkWidget* _sender, GdkEventKey* event, gpointer self) {
	gboolean result;
	result = document_view_on_backspace (self, event);
	return result;
}


DocumentView* document_view_construct (GType object_type, Document* doc) {
	DocumentView * self = NULL;
	GSettings* _tmp0_ = NULL;
	guint tmp = 0U;
	gboolean _tmp1_;
	gboolean _tmp2_;
	gboolean _tmp3_;
	gboolean _tmp4_;
	gchar* _tmp5_ = NULL;
	gchar* _tmp6_;
	Block16Data* _data16_;
	CompletionProvider* _tmp7_ = NULL;
	GtkSourceCompletion* _tmp8_ = NULL;
	GtkSourceCompletion* _tmp9_ = NULL;
	GtkTextBuffer* _tmp10_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (doc != NULL, NULL);
	self = (DocumentView*) g_object_new (object_type, NULL);
	gtk_text_view_set_buffer ((GtkTextView*) self, (GtkTextBuffer*) doc);
	g_signal_connect_object ((GObject*) doc, "notify::readonly", (GCallback) __lambda14__g_object_notify, self, 0);
	gtk_text_view_set_wrap_mode ((GtkTextView*) self, GTK_WRAP_WORD);
	gtk_source_view_set_auto_indent ((GtkSourceView*) self, TRUE);
	gtk_source_view_set_indent_width ((GtkSourceView*) self, -1);
	_tmp0_ = g_settings_new ("org.gnome.latexila.preferences.editor");
	_g_object_unref0 (self->priv->editor_settings);
	self->priv->editor_settings = _tmp0_;
	document_view_set_font_from_settings (self);
	g_settings_get (self->priv->editor_settings, "tabs-size", "u", &tmp);
	gtk_source_view_set_tab_width ((GtkSourceView*) self, tmp);
	_tmp1_ = g_settings_get_boolean (self->priv->editor_settings, "insert-spaces");
	gtk_source_view_set_insert_spaces_instead_of_tabs ((GtkSourceView*) self, _tmp1_);
	_tmp2_ = g_settings_get_boolean (self->priv->editor_settings, "display-line-numbers");
	gtk_source_view_set_show_line_numbers ((GtkSourceView*) self, _tmp2_);
	_tmp3_ = g_settings_get_boolean (self->priv->editor_settings, "highlight-current-line");
	gtk_source_view_set_highlight_current_line ((GtkSourceView*) self, _tmp3_);
	_tmp4_ = g_settings_get_boolean (self->priv->editor_settings, "bracket-matching");
	gtk_source_buffer_set_highlight_matching_brackets ((GtkSourceBuffer*) doc, _tmp4_);
	_tmp5_ = g_settings_get_string (self->priv->editor_settings, "scheme");
	_tmp6_ = _tmp5_;
	document_set_style_scheme_from_string (doc, _tmp6_);
	_g_free0 (_tmp6_);
	gtk_source_view_set_smart_home_end ((GtkSourceView*) self, GTK_SOURCE_SMART_HOME_END_AFTER);
	_data16_ = g_slice_new0 (Block16Data);
	_data16_->_ref_count_ = 1;
	_data16_->self = g_object_ref (self);
	_tmp7_ = completion_provider_get_default ();
	_data16_->provider = _tmp7_;
	_tmp8_ = gtk_source_view_get_completion ((GtkSourceView*) self);
	gtk_source_completion_add_provider (_tmp8_, (GtkSourceCompletionProvider*) _data16_->provider, &_inner_error_);
	if (_inner_error_ != NULL) {
		block16_data_unref (_data16_);
		_data16_ = NULL;
		goto __catch39_g_error;
	}
	_tmp9_ = gtk_source_view_get_completion ((GtkSourceView*) self);
	g_object_set (_tmp9_, "remember-info-visibility", TRUE, NULL);
	_tmp10_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_signal_connect_data ((GObject*) _tmp10_, "notify::cursor-position", (GCallback) __lambda15__g_object_notify, block16_data_ref (_data16_), (GClosureNotify) block16_data_unref, 0);
	block16_data_unref (_data16_);
	_data16_ = NULL;
	goto __finally39;
	__catch39_g_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		fprintf (stderr, "Error completion: %s\n", e->message);
		_g_error_free0 (e);
	}
	__finally39:
	if (_inner_error_ != NULL) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	g_signal_connect_object ((GtkWidget*) self, "key-press-event", (GCallback) _document_view_on_backspace_gtk_widget_key_press_event, self, 0);
	return self;
}


DocumentView* document_view_new (Document* doc) {
	return document_view_construct (TYPE_DOCUMENT_VIEW, doc);
}


void document_view_scroll_to_cursor (DocumentView* self, gdouble margin) {
	GtkTextBuffer* _tmp0_ = NULL;
	GtkTextMark* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp1_ = gtk_text_buffer_get_insert (_tmp0_);
	gtk_text_view_scroll_to_mark ((GtkTextView*) self, _tmp1_, margin, FALSE, (gdouble) 0, (gdouble) 0);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


void document_view_cut_selection (DocumentView* self) {
	GtkTextBuffer* _tmp0_ = NULL;
	GtkClipboard* _tmp1_ = NULL;
	GtkClipboard* _tmp2_;
	GtkClipboard* clipboard;
	GtkTextBuffer* _tmp3_ = NULL;
	GtkTextBuffer* _tmp4_ = NULL;
	gboolean _tmp5_;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_return_if_fail (_tmp0_ != NULL);
	_tmp1_ = gtk_widget_get_clipboard ((GtkWidget*) self, GDK_SELECTION_CLIPBOARD);
	_tmp2_ = _g_object_ref0 (_tmp1_);
	clipboard = _tmp2_;
	_tmp3_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp4_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp5_ = document_get_readonly (DOCUMENT (_tmp4_));
	gtk_text_buffer_cut_clipboard (_tmp3_, clipboard, !_tmp5_);
	document_view_scroll_to_cursor (self, DOCUMENT_VIEW_SCROLL_MARGIN);
	gtk_widget_grab_focus ((GtkWidget*) self);
	_g_object_unref0 (clipboard);
}


void document_view_copy_selection (DocumentView* self) {
	GtkTextBuffer* _tmp0_ = NULL;
	GtkClipboard* _tmp1_ = NULL;
	GtkClipboard* _tmp2_;
	GtkClipboard* clipboard;
	GtkTextBuffer* _tmp3_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_return_if_fail (_tmp0_ != NULL);
	_tmp1_ = gtk_widget_get_clipboard ((GtkWidget*) self, GDK_SELECTION_CLIPBOARD);
	_tmp2_ = _g_object_ref0 (_tmp1_);
	clipboard = _tmp2_;
	_tmp3_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	gtk_text_buffer_copy_clipboard (_tmp3_, clipboard);
	gtk_widget_grab_focus ((GtkWidget*) self);
	_g_object_unref0 (clipboard);
}


void document_view_my_paste_clipboard (DocumentView* self) {
	GtkTextBuffer* _tmp0_ = NULL;
	GtkClipboard* _tmp1_ = NULL;
	GtkClipboard* _tmp2_;
	GtkClipboard* clipboard;
	GtkTextBuffer* _tmp3_ = NULL;
	GtkTextBuffer* _tmp4_ = NULL;
	gboolean _tmp5_;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_return_if_fail (_tmp0_ != NULL);
	_tmp1_ = gtk_widget_get_clipboard ((GtkWidget*) self, GDK_SELECTION_CLIPBOARD);
	_tmp2_ = _g_object_ref0 (_tmp1_);
	clipboard = _tmp2_;
	_tmp3_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp4_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp5_ = document_get_readonly (DOCUMENT (_tmp4_));
	gtk_text_buffer_paste_clipboard (_tmp3_, clipboard, NULL, !_tmp5_);
	document_view_scroll_to_cursor (self, DOCUMENT_VIEW_SCROLL_MARGIN);
	gtk_widget_grab_focus ((GtkWidget*) self);
	_g_object_unref0 (clipboard);
}


void document_view_delete_selection (DocumentView* self) {
	GtkTextBuffer* _tmp0_ = NULL;
	GtkTextBuffer* _tmp1_ = NULL;
	GtkTextBuffer* _tmp2_ = NULL;
	gboolean _tmp3_;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_return_if_fail (_tmp0_ != NULL);
	_tmp1_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp2_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp3_ = document_get_readonly (DOCUMENT (_tmp2_));
	gtk_text_buffer_delete_selection (_tmp1_, TRUE, !_tmp3_);
	document_view_scroll_to_cursor (self, DOCUMENT_VIEW_SCROLL_MARGIN);
}


void document_view_my_select_all (DocumentView* self) {
	GtkTextBuffer* _tmp0_ = NULL;
	GtkTextIter start = {0};
	GtkTextIter end = {0};
	GtkTextBuffer* _tmp1_ = NULL;
	GtkTextIter _tmp2_ = {0};
	GtkTextIter _tmp3_ = {0};
	GtkTextBuffer* _tmp4_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_return_if_fail (_tmp0_ != NULL);
	_tmp1_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	gtk_text_buffer_get_bounds (_tmp1_, &_tmp2_, &_tmp3_);
	start = _tmp2_;
	end = _tmp3_;
	_tmp4_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	gtk_text_buffer_select_range (_tmp4_, &start, &end);
}


guint document_view_my_get_visual_column (DocumentView* self, GtkTextIter* iter) {
	guint result = 0U;
	guint column;
	guint _tmp0_;
	guint tab_width;
	GtkTextIter position;
	g_return_val_if_fail (self != NULL, 0U);
	column = (guint) 0;
	_tmp0_ = gtk_source_view_get_tab_width ((GtkSourceView*) self);
	tab_width = _tmp0_;
	position = *iter;
	gtk_text_iter_set_visible_line_offset (&position, 0);
	while (TRUE) {
		gboolean _tmp1_;
		gunichar _tmp2_;
		gboolean _tmp3_;
		_tmp1_ = gtk_text_iter_equal (iter, &position);
		if (!(!_tmp1_)) {
			break;
		}
		_tmp2_ = gtk_text_iter_get_char (&position);
		if (_tmp2_ == '\t') {
			column = column + (tab_width - (column % tab_width));
		} else {
			column++;
		}
		_tmp3_ = gtk_text_iter_forward_char (&position);
		if (!_tmp3_) {
			break;
		}
	}
	result = column;
	return result;
}


void document_view_set_font_from_settings (DocumentView* self) {
	gchar* font = NULL;
	gboolean _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = g_settings_get_boolean (self->priv->editor_settings, "use-default-font");
	if (_tmp0_) {
		AppSettings* _tmp1_ = NULL;
		AppSettings* _tmp2_;
		const gchar* _tmp3_ = NULL;
		gchar* _tmp4_;
		_tmp1_ = app_settings_get_default ();
		_tmp2_ = _tmp1_;
		_tmp3_ = app_settings_get_system_font (_tmp2_);
		_tmp4_ = g_strdup (_tmp3_);
		_g_free0 (font);
		font = _tmp4_;
		_g_object_unref0 (_tmp2_);
	} else {
		gchar* _tmp5_ = NULL;
		_tmp5_ = g_settings_get_string (self->priv->editor_settings, "editor-font");
		_g_free0 (font);
		font = _tmp5_;
	}
	document_view_set_font_from_string (self, font);
	_g_free0 (font);
}


void document_view_set_font_from_string (DocumentView* self, const gchar* font) {
	PangoFontDescription* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (font != NULL);
	_tmp0_ = pango_font_description_from_string (font);
	_pango_font_description_free0 (self->priv->font_desc);
	self->priv->font_desc = _tmp0_;
	gtk_widget_modify_font ((GtkWidget*) self, self->priv->font_desc);
}


void document_view_enlarge_font (DocumentView* self) {
	gint _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = pango_font_description_get_size (self->priv->font_desc);
	pango_font_description_set_size (self->priv->font_desc, _tmp0_ + PANGO_SCALE);
	gtk_widget_modify_font ((GtkWidget*) self, self->priv->font_desc);
}


void document_view_shrink_font (DocumentView* self) {
	gint _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = pango_font_description_get_size (self->priv->font_desc);
	pango_font_description_set_size (self->priv->font_desc, _tmp0_ - PANGO_SCALE);
	gtk_widget_modify_font ((GtkWidget*) self, self->priv->font_desc);
}


gchar* document_view_get_indentation_style (DocumentView* self) {
	gchar* result = NULL;
	gboolean _tmp0_;
	gchar* _tmp3_;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = gtk_source_view_get_insert_spaces_instead_of_tabs ((GtkSourceView*) self);
	if (_tmp0_) {
		guint _tmp1_;
		gchar* _tmp2_ = NULL;
		_tmp1_ = gtk_source_view_get_tab_width ((GtkSourceView*) self);
		_tmp2_ = g_strnfill ((gsize) _tmp1_, ' ');
		result = _tmp2_;
		return result;
	}
	_tmp3_ = g_strdup ("\t");
	result = _tmp3_;
	return result;
}


static gchar string_get (const gchar* self, glong index) {
	gchar result = '\0';
	g_return_val_if_fail (self != NULL, '\0');
	result = ((gchar*) self)[index];
	return result;
}


static gboolean document_view_on_backspace (DocumentView* self, GdkEventKey* event) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_;
	GtkTextIter iter_start = {0};
	GtkTextIter iter_insert = {0};
	GtkTextBuffer* _tmp9_ = NULL;
	GtkTextBuffer* _tmp10_ = NULL;
	GtkTextMark* _tmp11_ = NULL;
	GtkTextIter _tmp12_ = {0};
	GtkTextBuffer* _tmp13_ = NULL;
	gint _tmp14_;
	GtkTextIter _tmp15_ = {0};
	GtkTextBuffer* _tmp16_ = NULL;
	gchar* _tmp17_ = NULL;
	gchar* text;
	gint nb_chars_to_delete;
	gboolean between;
	gboolean _tmp23_;
	GtkTextBuffer* _tmp24_ = NULL;
	GtkTextBuffer* _tmp25_ = NULL;
	GtkTextBuffer* _tmp26_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp4_ = g_settings_get_boolean (self->priv->editor_settings, "insert-spaces");
	if (!_tmp4_) {
		_tmp3_ = TRUE;
	} else {
		gboolean _tmp5_;
		_tmp5_ = g_settings_get_boolean (self->priv->editor_settings, "forget-no-tabs");
		_tmp3_ = !_tmp5_;
	}
	if (_tmp3_) {
		_tmp2_ = TRUE;
	} else {
		_tmp2_ = (*event).keyval != 0xff08;
	}
	if (_tmp2_) {
		_tmp1_ = TRUE;
	} else {
		GtkTextBuffer* _tmp6_ = NULL;
		gboolean _tmp7_;
		_tmp6_ = gtk_text_view_get_buffer ((GtkTextView*) self);
		_tmp7_ = gtk_text_buffer_get_has_selection (_tmp6_);
		_tmp1_ = _tmp7_;
	}
	if (_tmp1_) {
		_tmp0_ = TRUE;
	} else {
		guint _tmp8_;
		_tmp8_ = gtk_source_view_get_tab_width ((GtkSourceView*) self);
		_tmp0_ = _tmp8_ == 1;
	}
	if (_tmp0_) {
		result = FALSE;
		return result;
	}
	_tmp9_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp10_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp11_ = gtk_text_buffer_get_insert (_tmp10_);
	gtk_text_buffer_get_iter_at_mark (_tmp9_, &_tmp12_, _tmp11_);
	iter_insert = _tmp12_;
	_tmp13_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp14_ = gtk_text_iter_get_line (&iter_insert);
	gtk_text_buffer_get_iter_at_line (_tmp13_, &_tmp15_, _tmp14_);
	iter_start = _tmp15_;
	_tmp16_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	_tmp17_ = gtk_text_buffer_get_text (_tmp16_, &iter_start, &iter_insert, FALSE);
	text = _tmp17_;
	if (g_strcmp0 (text, "") == 0) {
		result = FALSE;
		_g_free0 (text);
		return result;
	}
	nb_chars_to_delete = 0;
	between = TRUE;
	{
		glong i;
		i = (glong) 0;
		{
			gboolean _tmp18_;
			_tmp18_ = TRUE;
			while (TRUE) {
				gint _tmp19_;
				gchar _tmp20_;
				gchar _tmp21_;
				guint _tmp22_;
				if (!_tmp18_) {
					i++;
				}
				_tmp18_ = FALSE;
				_tmp19_ = strlen (text);
				if (!(i < _tmp19_)) {
					break;
				}
				_tmp20_ = string_get (text, i);
				if (_tmp20_ == '\t') {
					nb_chars_to_delete = 1;
					between = TRUE;
					continue;
				}
				_tmp21_ = string_get (text, i);
				if (_tmp21_ != ' ') {
					result = FALSE;
					_g_free0 (text);
					return result;
				}
				if (between) {
					nb_chars_to_delete = 1;
					between = FALSE;
					continue;
				}
				nb_chars_to_delete++;
				_tmp22_ = gtk_source_view_get_tab_width ((GtkSourceView*) self);
				if (nb_chars_to_delete == _tmp22_) {
					between = TRUE;
				}
			}
		}
	}
	iter_start = iter_insert;
	_tmp23_ = gtk_text_iter_backward_chars (&iter_start, nb_chars_to_delete);
	if (!_tmp23_) {
		result = FALSE;
		_g_free0 (text);
		return result;
	}
	_tmp24_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	gtk_text_buffer_begin_user_action (_tmp24_);
	_tmp25_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	g_signal_emit_by_name (_tmp25_, "delete-range", &iter_start, &iter_insert);
	_tmp26_ = gtk_text_view_get_buffer ((GtkTextView*) self);
	gtk_text_buffer_end_user_action (_tmp26_);
	result = TRUE;
	_g_free0 (text);
	return result;
}


static void document_view_class_init (DocumentViewClass * klass) {
	document_view_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (DocumentViewPrivate));
	G_OBJECT_CLASS (klass)->finalize = document_view_finalize;
}


static void document_view_instance_init (DocumentView * self) {
	self->priv = DOCUMENT_VIEW_GET_PRIVATE (self);
}


static void document_view_finalize (GObject* obj) {
	DocumentView * self;
	self = DOCUMENT_VIEW (obj);
	_g_object_unref0 (self->priv->editor_settings);
	_pango_font_description_free0 (self->priv->font_desc);
	G_OBJECT_CLASS (document_view_parent_class)->finalize (obj);
}


GType document_view_get_type (void) {
	static volatile gsize document_view_type_id__volatile = 0;
	if (g_once_init_enter (&document_view_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (DocumentViewClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) document_view_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (DocumentView), 0, (GInstanceInitFunc) document_view_instance_init, NULL };
		GType document_view_type_id;
		document_view_type_id = g_type_register_static (GTK_TYPE_SOURCE_VIEW, "DocumentView", &g_define_type_info, 0);
		g_once_init_leave (&document_view_type_id__volatile, document_view_type_id);
	}
	return document_view_type_id__volatile;
}


