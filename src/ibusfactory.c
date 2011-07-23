/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil; -*- */
/* vim:set et sts=4: */
/* ibus - The Input Bus
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
#include "ibusfactory.h"
#include "ibusengine.h"
#include "ibusshare.h"
#include "ibusinternal.h"

#define IBUS_FACTORY_GET_PRIVATE(o)  \
   (G_TYPE_INSTANCE_GET_PRIVATE ((o), IBUS_TYPE_FACTORY, IBusFactoryPrivate))

enum {
    LAST_SIGNAL,
};

enum {
    PROP_0,
};

/* IBusFactoryPriv */
struct _IBusFactoryPrivate {
    guint id;
    GList          *engine_list;
    GHashTable     *engine_table;
};

/* functions prototype */
static void      ibus_factory_destroy        (IBusFactory        *factory);
static void      ibus_factory_set_property   (IBusFactory        *engine,
                                              guint               prop_id,
                                              const GValue       *value,
                                              GParamSpec         *pspec);
static void      ibus_factory_get_property   (IBusFactory        *factory,
                                              guint               prop_id,
                                              GValue             *value,
                                              GParamSpec         *pspec);
static void      ibus_factory_service_method_call
                                              (IBusService        *service,
                                               GDBusConnection    *connection,
                                               const gchar        *sender,
                                               const gchar        *object_path,
                                               const gchar        *interface_name,
                                               const gchar        *method_name,
                                               GVariant           *parameters,
                                               GDBusMethodInvocation
                                                                  *invocation);
static GVariant *ibus_factory_service_get_property
                                             (IBusService        *service,
                                              GDBusConnection    *connection,
                                              const gchar        *sender,
                                              const gchar        *object_path,
                                              const gchar        *interface_name,
                                              const gchar        *property_name,
                                              GError            **error);
static gboolean  ibus_factory_service_set_property
                                             (IBusService        *service,
                                              GDBusConnection    *connection,
                                              const gchar        *sender,
                                              const gchar        *object_path,
                                              const gchar        *interface_name,
                                              const gchar        *property_name,
                                              GVariant           *value,
                                              GError            **error);
static void      ibus_factory_engine_destroy_cb
                                             (IBusEngine         *engine,
                                              IBusFactory        *factory);

G_DEFINE_TYPE (IBusFactory, ibus_factory, IBUS_TYPE_SERVICE)

static const gchar introspection_xml[] =
    "<node>"
    "  <interface name='org.freedesktop.IBus.Factory'>"
    "    <method name='CreateEngine'>"
    "      <arg direction='in'  type='s' name='name' />"
    "      <arg direction='out' type='o' />"
    "    </method>"
    "  </interface>"
    "</node>";

static void
ibus_factory_class_init (IBusFactoryClass *class)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (class);
    IBusObjectClass *ibus_object_class = IBUS_OBJECT_CLASS (class);

    gobject_class->set_property = (GObjectSetPropertyFunc) ibus_factory_set_property;
    gobject_class->get_property = (GObjectGetPropertyFunc) ibus_factory_get_property;

    ibus_object_class->destroy = (IBusObjectDestroyFunc) ibus_factory_destroy;

    IBUS_SERVICE_CLASS (class)->service_method_call  = ibus_factory_service_method_call;
    IBUS_SERVICE_CLASS (class)->service_get_property = ibus_factory_service_get_property;
    IBUS_SERVICE_CLASS (class)->service_set_property = ibus_factory_service_set_property;

    ibus_service_class_add_interfaces (IBUS_SERVICE_CLASS (class), introspection_xml);

    g_type_class_add_private (class, sizeof (IBusFactoryPrivate));
}

static void
ibus_factory_init (IBusFactory *factory)
{
    factory->priv = IBUS_FACTORY_GET_PRIVATE (factory);
    factory->priv->engine_table =
        g_hash_table_new_full (g_str_hash,
                               g_str_equal,
                               g_free,
                               NULL);
}

static void
ibus_factory_destroy (IBusFactory *factory)
{
    GList *list;

    list = g_list_copy (factory->priv->engine_list);
    g_list_foreach (list, (GFunc) ibus_object_destroy, NULL);
    g_list_free (factory->priv->engine_list);
    g_list_free (list);
    factory->priv->engine_list = NULL;

    if (factory->priv->engine_table) {
        g_hash_table_destroy (factory->priv->engine_table);
    }

    IBUS_OBJECT_CLASS(ibus_factory_parent_class)->destroy (IBUS_OBJECT (factory));
}

static void
ibus_factory_set_property (IBusFactory  *factory,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
    switch (prop_id) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (factory, prop_id, pspec);
    }
}

static void
ibus_factory_get_property (IBusFactory *factory,
                           guint        prop_id,
                           GValue      *value,
                           GParamSpec  *pspec)
{
    switch (prop_id) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (factory, prop_id, pspec);
    }
}

static void
ibus_factory_engine_destroy_cb (IBusEngine  *engine,
                                IBusFactory *factory)
{
    factory->priv->engine_list = g_list_remove (factory->priv->engine_list, engine);
    g_object_unref (engine);
}

static void
ibus_factory_service_method_call (IBusService           *service,
                                  GDBusConnection       *connection,
                                  const gchar           *sender,
                                  const gchar           *object_path,
                                  const gchar           *interface_name,
                                  const gchar           *method_name,
                                  GVariant              *parameters,
                                  GDBusMethodInvocation *invocation)
{
    IBusFactory *factory = IBUS_FACTORY (service);

    if (g_strcmp0 (method_name, "CreateEngine") == 0) {
        gchar *engine_name = NULL;
        g_variant_get (parameters, "(&s)", &engine_name);
        GType engine_type = (GType )g_hash_table_lookup (factory->priv->engine_table, engine_name);

        if (engine_type == G_TYPE_INVALID) {
            gchar *error_message = g_strdup_printf ("Can not fond engine %s", engine_name);
            g_dbus_method_invocation_return_error (invocation,
                                                   G_DBUS_ERROR,
                                                   G_DBUS_ERROR_FAILED,
                                                   error_message);
            g_free (error_message);
        }
        else {
            gchar *object_path = g_strdup_printf ("/org/freedesktop/IBus/Engine/%d",
                                            ++factory->priv->id);
            IBusEngine *engine = ibus_engine_new_type (engine_type,
                                                       engine_name,
                                                       object_path,
                                                       ibus_service_get_connection ((IBusService *)factory));
            g_assert (engine != NULL);
            g_object_ref_sink (engine);
            factory->priv->engine_list = g_list_append (factory->priv->engine_list, engine);
            g_signal_connect (engine,
                              "destroy",
                              G_CALLBACK (ibus_factory_engine_destroy_cb),
                              factory);
            g_dbus_method_invocation_return_value (invocation,
                                                   g_variant_new ("(o)", object_path));
            g_free (object_path);
        }
        return;
    }

    IBUS_SERVICE_CLASS (ibus_factory_parent_class)->
            service_method_call (service,
                                 connection,
                                 sender,
                                 object_path,
                                 interface_name,
                                 method_name,
                                 parameters,
                                 invocation);
}

static GVariant *
ibus_factory_service_get_property (IBusService        *service,
                                   GDBusConnection    *connection,
                                   const gchar        *sender,
                                   const gchar        *object_path,
                                   const gchar        *interface_name,
                                   const gchar        *property_name,
                                   GError            **error)
{
    return IBUS_SERVICE_CLASS (ibus_factory_parent_class)->
                service_get_property (service,
                                      connection,
                                      sender,
                                      object_path,
                                      interface_name,
                                      property_name,
                                      error);
}

static gboolean
ibus_factory_service_set_property (IBusService        *service,
                                   GDBusConnection    *connection,
                                   const gchar        *sender,
                                   const gchar        *object_path,
                                   const gchar        *interface_name,
                                   const gchar        *property_name,
                                   GVariant           *value,
                                   GError            **error)
{
    return IBUS_SERVICE_CLASS (ibus_factory_parent_class)->
                service_set_property (service,
                                      connection,
                                      sender,
                                      object_path,
                                      interface_name,
                                      property_name,
                                      value,
                                      error);
}

IBusFactory *
ibus_factory_new (GDBusConnection *connection)
{
    g_return_val_if_fail (G_IS_DBUS_CONNECTION (connection), NULL);

    IBusEngine *object = g_object_new (IBUS_TYPE_FACTORY,
                                       "object-path", IBUS_PATH_FACTORY,
                                       "connection", connection,
                                       NULL);

    return IBUS_FACTORY (object);
}

void
ibus_factory_add_engine (IBusFactory *factory,
                         const gchar *engine_name,
                         GType        engine_type)
{
    g_return_if_fail (IBUS_IS_FACTORY (factory));
    g_return_if_fail (engine_name != NULL);
    g_return_if_fail (g_type_is_a (engine_type, IBUS_TYPE_ENGINE));

    g_hash_table_insert (factory->priv->engine_table, g_strdup (engine_name), (gpointer) engine_type);
}
