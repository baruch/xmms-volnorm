/*
 * This header file is a place holder for the XMMS functions used in the 
 * plugin, so as to allow to easily test the plugin without loading XMMS.
 */

#include <xmms/xmmsctrl.h>
#include <xmms/configfile.h>
#include <stdio.h>

gint xmms_remote_get_playlist_pos(gint session)
{
	return session;
}

void xmms_cfg_free(ConfigFile * cfg)
{
	cfg = NULL;
}

ConfigFile *xmms_cfg_open_default_file(void)
{
	return NULL;
}

gboolean xmms_cfg_write_default_file(ConfigFile * cfg)
{
	cfg = NULL;
	return FALSE;
}

gboolean xmms_cfg_read_double(ConfigFile * cfg, gchar * section, gchar * key, gdouble * value)
{
	cfg = NULL; section = NULL; key = NULL; value = NULL;
	return FALSE;
}

void xmms_cfg_write_double(ConfigFile * cfg, gchar * section, gchar * key, gdouble value)
{
	cfg = NULL; section = NULL; key = NULL; value = 0.0;
}

gboolean xmms_cfg_read_boolean(ConfigFile * cfg, gchar * section, gchar * key, gboolean * value)
{
	cfg = NULL; section = NULL; key = NULL; value = NULL;
	return FALSE;
}

void xmms_cfg_write_boolean(ConfigFile * cfg, gchar * section, gchar * key, gboolean value)
{
	cfg = NULL; section = NULL; key = NULL; value = 0;
}

gchar *xmms_remote_get_playlist_file(gint session, gint pos)
{
	session = pos = 0;
	return NULL;
}

gchar *xmms_remote_get_playlist_title(gint session, gint pos)
{
	session = pos = 0;
	return NULL;
}

gint xmms_remote_get_playlist_time(gint session, gint pos)
{
	session = pos = 0;
	return 0;
}
