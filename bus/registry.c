/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil; -*- */
/* vim:set et sts=4: */
/* bus - The Input Bus
 * Copyright (C) 2008-2010 Peng Huang <shawn.p.huang@gmail.com>
 * Copyright (C) 2008-2010 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include "registry.h"
#include <glib/gstdio.h>
#include <gio/gio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "option.h"
#include "marshalers.h"
#include "dbusimpl.h"

enum {
    CHANGED,
    LAST_SIGNAL,
};

static guint             _signals[LAST_SIGNAL] = { 0 };

struct _BusRegistry {
    IBusObject parent;

    /* instance members */

    /* a list of IBusObservedPath objects. */
    GList *observed_paths;
    /* a list of BusComponent objects that are created from component XML files (or from the cache of them). */
    GList *components;
    /* a mapping from an engine name (e.g. 'pinyin') to the corresponding IBusEngineDesc object. */
    GHashTable *engine_table;

#ifdef G_THREADS_ENABLED
    GThread *thread;
    gboolean thread_running;
    GMutex  *mutex;
    GCond   *cond;
    gboolean changed;
#endif
};

struct _BusRegistryClass {
    IBusObjectClass parent;

    /* class members */
};

/* functions prototype */
static void              bus_registry_destroy           (BusRegistry        *registry);
static void              bus_registry_load              (BusRegistry        *registry);
static void              bus_registry_load_in_dir       (BusRegistry        *registry,
                                                         const gchar        *dirname);
static gboolean          bus_registry_save_cache        (BusRegistry        *registry);
static gboolean          bus_registry_load_cache        (BusRegistry        *registry);
static gboolean          bus_registry_check_modification(BusRegistry        *registry);
static void              bus_registry_remove_all        (BusRegistry        *registry);

G_DEFINE_TYPE (BusRegistry, bus_registry, IBUS_TYPE_OBJECT)

static void
bus_registry_class_init (BusRegistryClass *class)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (class);
    IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (class);

    _signals[CHANGED] =
        g_signal_new (I_("changed"),
            G_TYPE_FROM_CLASS (gobject_class),
            G_SIGNAL_RUN_LAST,
            0, /* does not associate a method in this class. the "changed" signal would be handled in other classes. */
            NULL, NULL,
            bus_marshal_VOID__VOID,
            G_TYPE_NONE,
            0);

    ibus_object_class->destroy = (IBusObjectDestroyFunc) bus_registry_destroy;
}

static void
bus_registry_init (BusRegistry *registry)
{
    GList *p;
    registry->observed_paths = NULL;
    registry->components = NULL;
    registry->engine_table = g_hash_table_new (g_str_hash, g_str_equal);

#ifdef G_THREADS_ENABLED
    /* If glib supports thread, we'll create a thread to monitor changes in IME
     * XML files and related files, so users can use newly installed IMEs
     * immediatlly.
     * Note that we don't use GFileMonitor for watching as we need to monitor
     * not only XML files but also other related files that can be scattered in
     * many places. Monitoring these files with GFileMonitor would be make it
     * complicated. hence we use a thread to poll the changes.
     */
    registry->thread = NULL;
    registry->thread_running = TRUE;
    registry->mutex = g_mutex_new ();
    registry->cond = g_cond_new ();
    registry->changed = FALSE;
#endif

    if (g_strcmp0 (g_cache, "none") == 0) {
        /* Only load registry, but not read and write cache. */
        bus_registry_load (registry);
    }
    else if (g_strcmp0 (g_cache, "refresh") == 0) {
        /* Load registry and overwrite the cache. */
        bus_registry_load (registry);
        bus_registry_save_cache (registry);
    }
    else {
        /* Load registry from cache. If the cache does not exist or
         * it is outdated, then generate it.
         */
        if (bus_registry_load_cache (registry) == FALSE ||
            bus_registry_check_modification (registry)) {
            bus_registry_remove_all (registry);
            bus_registry_load (registry);
            bus_registry_save_cache (registry);
        }
    }

    for (p = registry->components; p != NULL; p = p->next) {
        BusComponent *comp = (BusComponent *) p->data;
        GList *engines = bus_component_get_engines (comp);
        GList *p1;
        for (p1 = engines; p1 != NULL; p1 = p1->next) {
            IBusEngineDesc *desc = (IBusEngineDesc *) p1->data;
            g_hash_table_insert (registry->engine_table,
                                 (gpointer) ibus_engine_desc_get_name (desc),
                                 desc);
        }
        g_list_free (engines);
    }
}

static void
bus_registry_remove_all (BusRegistry *registry)
{
    g_list_foreach (registry->observed_paths, (GFunc) g_object_unref, NULL);
    g_list_free (registry->observed_paths);
    registry->observed_paths = NULL;

    g_list_foreach (registry->components, (GFunc) g_object_unref, NULL);
    g_list_free (registry->components);
    registry->components = NULL;

    g_hash_table_remove_all (registry->engine_table);
}

static void
bus_registry_destroy (BusRegistry *registry)
{
#ifdef G_THREADS_ENABLED
    if (registry->thread) {
        g_mutex_lock (registry->mutex);
        registry->thread_running = FALSE;
        g_mutex_unlock (registry->mutex);

        /* Raise a signal to cause the loop in _checks_changes() exits
         * immediately, and then wait until the thread finishes, and release all
         * resources of the thread.
         */
        g_cond_signal (registry->cond);
        g_thread_join (registry->thread);

        registry->thread = NULL;
    }
#endif

    bus_registry_remove_all (registry);

    g_hash_table_destroy (registry->engine_table);
    registry->engine_table = NULL;

#ifdef G_THREADS_ENABLED
    g_cond_free (registry->cond);
    registry->cond = NULL;

    g_mutex_free (registry->mutex);
    registry->mutex = NULL;
#endif

    IBUS_OBJECT_CLASS (bus_registry_parent_class)->destroy (IBUS_OBJECT (registry));
}

/**
 * bus_registry_load:
 *
 * Read all XML files in the PKGDATADIR (typically /usr/share/ibus/components/ *.xml) and update the registry object.
 */
static void
bus_registry_load (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    gchar *dirname;
    IBusObservedPath *path;

    dirname = g_build_filename (PKGDATADIR, "component", NULL);

    path = ibus_observed_path_new (dirname, TRUE);
    registry->observed_paths = g_list_append (registry->observed_paths, path);

    bus_registry_load_in_dir (registry, dirname);

    g_free (dirname);

#if 0
    /* FIXME Should we support install some IME in user dir? */
    dirname = g_build_filename (g_get_user_data_dir (), "ibus", "component", NULL);

    path = ibus_observed_path_new (dirname, TRUE);
    registry->observed_paths = g_list_append (registry->observed_paths, path);

    if (g_file_test (dirname, G_FILE_TEST_EXISTS)) {
        bus_registry_load_in_dir (registry, dirname);
    }

    g_free (dirname);
#endif
}

#define g_string_append_indent(string, indent)  \
    {                                           \
        gint i;                                 \
        for (i = 0; i < (indent); i++) {        \
            g_string_append (string, "    ");   \
        }                                       \
    }

static gboolean
bus_registry_load_cache (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    gchar *filename;
    XMLNode *node;
    GList *p;

    filename = g_build_filename (g_get_user_cache_dir (), "ibus", "bus", "registry.xml", NULL);
    node = ibus_xml_parse_file (filename);
    g_free (filename);

    if (node == NULL) {
        return FALSE;
    }

    if (g_strcmp0 (node->name, "ibus-registry") != 0) {
        ibus_xml_free (node);
        return FALSE;
    }

    for (p = node->sub_nodes; p != NULL; p = p->next) {
        XMLNode *sub_node = (XMLNode *) p->data;

        if (g_strcmp0 (sub_node->name, "observed-paths") == 0) {
            GList *pp;
            for (pp = sub_node->sub_nodes; pp != NULL; pp = pp->next) {
                IBusObservedPath *path;
                path = ibus_observed_path_new_from_xml_node (pp->data, FALSE);
                if (path) {
                    g_object_ref_sink (path);
                    registry->observed_paths = g_list_append (registry->observed_paths, path);
                }
            }
            continue;
        }
        if (g_strcmp0 (sub_node->name, "components") == 0) {
            GList *pp;
            for (pp = sub_node->sub_nodes; pp != NULL; pp = pp->next) {
                IBusComponent *component;
                component = ibus_component_new_from_xml_node (pp->data);
                if (component) {
                    BusComponent *buscomp = bus_component_new (component,
                                                               NULL /* factory */);
                    g_object_ref_sink (buscomp);
                    registry->components =
                        g_list_append (registry->components, buscomp);
                }
            }

            continue;
        }
        g_warning ("Unknown element <%s>", sub_node->name);
    }

    ibus_xml_free (node);
    return TRUE;
}

static gboolean
bus_registry_check_modification (BusRegistry *registry)
{
    GList *p;

    for (p = registry->observed_paths; p != NULL; p = p->next) {
        if (ibus_observed_path_check_modification ((IBusObservedPath *) p->data))
            return TRUE;
    }

    for (p = registry->components; p != NULL; p = p->next) {
        if (ibus_component_check_modification (bus_component_get_component ((BusComponent *) p->data)))
            return TRUE;
    }

    return FALSE;
}

static gboolean
bus_registry_save_cache (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    gchar *cachedir;
    gchar *filename;
    GString *output;
    GList *p;
    FILE *pf;
    size_t items = 0;

    cachedir = g_build_filename (g_get_user_cache_dir (), "ibus", "bus", NULL);
    filename = g_build_filename (cachedir, "registry.xml", NULL);
    g_mkdir_with_parents (cachedir, 0775);
    pf = g_fopen (filename, "w");
    g_free (filename);
    g_free (cachedir);

    if (pf == NULL) {
        g_warning ("create registry.xml failed");
        return FALSE;
    }

    output = g_string_new ("");
    g_string_append (output, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    g_string_append (output, "<!-- \n"
                             "    This file was generated by ibus-daemon. Please don't modify it.\n"
                             "    -->\n");
    g_string_append (output, "<ibus-registry>\n");

    if (registry->observed_paths) {
        g_string_append_indent (output, 1);
        g_string_append (output, "<observed-paths>\n");
        for (p = registry->observed_paths; p != NULL; p = p->next) {
            ibus_observed_path_output ((IBusObservedPath *) p->data,
                                      output, 2);
        }
        g_string_append_indent (output, 1);
        g_string_append (output, "</observed-paths>\n");
    }

    if (registry->components) {
        g_string_append_indent (output, 1);
        g_string_append (output, "<components>\n");
        for (p = registry->components; p != NULL; p = p->next) {
            ibus_component_output (bus_component_get_component ((BusComponent *) p->data),
                                   output, 2);
        }
        g_string_append_indent (output, 1);
        g_string_append (output, "</components>\n");
    }

    g_string_append (output, "</ibus-registry>\n");
    items = fwrite (output->str, output->len, 1, pf);
    g_string_free (output, TRUE);
    fclose (pf);
    return (items == 1 ? TRUE : FALSE);
}

/**
 * bus_registry_load_in_dir:
 *
 * Read all XML files in dirname, create a BusComponent object for each file, and add the component objects to the registry.
 */
static void
bus_registry_load_in_dir (BusRegistry *registry,
                          const gchar *dirname)
{
    g_assert (BUS_IS_REGISTRY (registry));
    g_assert (dirname);

    GError *error = NULL;
    GDir *dir;
    const gchar *filename;

    dir = g_dir_open (dirname, 0, &error);

    if (dir == NULL) {
        g_warning ("Unable open directory %s : %s", dirname, error->message);
        g_error_free (error);
        return;
    }

    while ((filename = g_dir_read_name (dir)) != NULL) {
        glong size;
        gchar *path;
        IBusComponent *component;

        size = g_utf8_strlen (filename, -1);
        if (g_strcmp0 (MAX (filename, filename + size - 4), ".xml") != 0)
            continue;

        path = g_build_filename (dirname, filename, NULL);
        component = ibus_component_new_from_file (path);
        if (component != NULL) {
            BusComponent *buscomp = bus_component_new (component,
                                                       NULL /* factory */);
            g_object_ref_sink (buscomp);
            registry->components =
                g_list_append (registry->components, buscomp);
        }

        g_free (path);
    }

    g_dir_close (dir);
}


BusRegistry *
bus_registry_new (void)
{
    BusRegistry *registry;
    registry = (BusRegistry *) g_object_new (BUS_TYPE_REGISTRY, NULL);
    return registry;
}

static gint
bus_register_component_is_name_cb (BusComponent *component,
                                   const gchar  *name)
{
    g_assert (BUS_IS_COMPONENT (component));
    g_assert (name);

    return g_strcmp0 (bus_component_get_name (component), name);
}

BusComponent *
bus_registry_lookup_component_by_name (BusRegistry *registry,
                                       const gchar *name)
{
    g_assert (BUS_IS_REGISTRY (registry));
    g_assert (name);

    GList *p;
    p = g_list_find_custom (registry->components,
                            name,
                            (GCompareFunc) bus_register_component_is_name_cb);
    if (p) {
        return (BusComponent *) p->data;
    }
    else {
        return NULL;
    }
}

GList *
bus_registry_get_components (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    return g_list_copy (registry->components);
}

GList *
bus_registry_get_engines (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    return g_hash_table_get_values (registry->engine_table);
}

GList *
bus_registry_get_engines_by_language (BusRegistry *registry,
                                      const gchar *language)
{
    g_assert (BUS_IS_REGISTRY (registry));
    g_assert (language);

    gint n;
    GList *p1, *p2, *engines;

    n = strlen (language);

    p1 = bus_registry_get_engines (registry);

    engines = NULL;

    for (p2 = p1; p2 != NULL; p2 = p2->next) {
        IBusEngineDesc *desc = (IBusEngineDesc *) p2->data;
        if (strncmp (ibus_engine_desc_get_language (desc), language, n) == 0) {
            engines = g_list_append (engines, desc);
        }
    }

    g_list_free (p1);
    return engines;
}

IBusEngineDesc *
bus_registry_find_engine_by_name (BusRegistry *registry,
                                  const gchar *name)
{
    g_assert (BUS_IS_REGISTRY (registry));
    g_assert (name);

    return (IBusEngineDesc *) g_hash_table_lookup (registry->engine_table, name);
}

void
bus_registry_stop_all_components (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    g_list_foreach (registry->components, (GFunc) bus_component_stop, NULL);

}

#ifdef G_THREADS_ENABLED
static gboolean
_emit_changed_signal_cb (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    g_signal_emit (registry, _signals[CHANGED], 0);
    return FALSE;
}

static gpointer
_check_changes (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    g_mutex_lock (registry->mutex);
    while (registry->thread_running == TRUE && registry->changed == FALSE) {
        extern gint g_monitor_timeout;
        GTimeVal tv;
        g_get_current_time (&tv);
        g_time_val_add (&tv, g_monitor_timeout * G_USEC_PER_SEC);
        /* Wait for the condition change or timeout. It will also unlock
         * the mutex, so that other thread could obay the lock and modify
         * the condition value.
         * Note that we use g_cond_timed_wait() here rather than sleep() so
         * that the loop can terminate immediately when the registry object
         * is destroyed. See also comments in bus_registry_destroy().
         */
        if (g_cond_timed_wait (registry->cond, registry->mutex, &tv) == FALSE) {
            /* Timeout happens. We check the modification of all IMEs' xml files
             * and related files specified in <observed-paths> in xml files.
             * If any file is changed, the changed signal will be emitted in
             * main thread. It is for finding install/uninstall/upgrade of IMEs.
             * On Linux desktop, ibus will popup UI to notificate users that
             * some IMEs are changed and ibus need a restart.
             */
            if (bus_registry_check_modification (registry)) {
                /* Emit the changed signal in main thread, and terminate
                 * this thread.
                 */
                registry->changed = TRUE;
                g_idle_add ((GSourceFunc) _emit_changed_signal_cb, registry);
                break;
            }
        }
        else
            g_warn_if_fail (registry->thread_running == FALSE);
    }
    g_mutex_unlock (registry->mutex);
    return NULL;
}

/**
 * bus_registry_start_monitor_changes:
 *
 * Start the monitor thread.
 */
void
bus_registry_start_monitor_changes (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));

    g_return_if_fail (registry->thread == NULL);
    g_return_if_fail (registry->changed == FALSE);

    registry->thread_running = TRUE;
    registry->thread = g_thread_create ((GThreadFunc) _check_changes,
                                        registry,
                                        TRUE,
                                        NULL);
}

gboolean
bus_registry_is_changed (BusRegistry *registry)
{
    g_assert (BUS_IS_REGISTRY (registry));
    return (registry->changed != 0);
}
#endif

void
bus_registry_name_owner_changed (BusRegistry *registry,
                                 const gchar *name,
                                 const gchar *old_name,
                                 const gchar *new_name)
{
    g_assert (BUS_IS_REGISTRY (registry));
    g_assert (name);
    g_assert (old_name);
    g_assert (new_name);

    BusComponent *component;
    BusFactoryProxy *factory;

    component = bus_registry_lookup_component_by_name (registry, name);

    if (component == NULL) {
        /* name is a unique name, or a well-known name we don't know. */
        return;
    }

    if (g_strcmp0 (old_name, "") != 0) {
        /* the component is stopped. */
        factory = bus_component_get_factory (component);

        if (factory != NULL) {
            ibus_proxy_destroy ((IBusProxy *) factory);
        }
    }

    if (g_strcmp0 (new_name, "") != 0) {
        /* the component is started. */
        BusConnection *connection =
                bus_dbus_impl_get_connection_by_name (BUS_DEFAULT_DBUS,
                                                      new_name);
        if (connection == NULL)
            return;

        factory = bus_factory_proxy_new (connection);
        if (factory == NULL)
            return;
        bus_component_set_factory (component, factory);
        g_object_unref (factory);
    }
}
