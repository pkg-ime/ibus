
#ifndef __bus_marshal_MARSHAL_H__
#define __bus_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* BOOL:UINT,UINT,UINT (./marshalers.list:1) */
G_GNUC_INTERNAL void bus_marshal_BOOLEAN__UINT_UINT_UINT (GClosure     *closure,
                                                          GValue       *return_value,
                                                          guint         n_param_values,
                                                          const GValue *param_values,
                                                          gpointer      invocation_hint,
                                                          gpointer      marshal_data);
#define bus_marshal_BOOL__UINT_UINT_UINT	bus_marshal_BOOLEAN__UINT_UINT_UINT

/* OBJECT:STRING (./marshalers.list:2) */
G_GNUC_INTERNAL void bus_marshal_OBJECT__STRING (GClosure     *closure,
                                                 GValue       *return_value,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint,
                                                 gpointer      marshal_data);

/* VOID:INT,UINT (./marshalers.list:3) */
G_GNUC_INTERNAL void bus_marshal_VOID__INT_UINT (GClosure     *closure,
                                                 GValue       *return_value,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint,
                                                 gpointer      marshal_data);

/* VOID:INT,INT,INT,INT (./marshalers.list:4) */
G_GNUC_INTERNAL void bus_marshal_VOID__INT_INT_INT_INT (GClosure     *closure,
                                                        GValue       *return_value,
                                                        guint         n_param_values,
                                                        const GValue *param_values,
                                                        gpointer      invocation_hint,
                                                        gpointer      marshal_data);

/* VOID:OBJECT (./marshalers.list:5) */
#define bus_marshal_VOID__OBJECT	g_cclosure_marshal_VOID__OBJECT

/* VOID:OBJECT,BOOLEAN (./marshalers.list:6) */
G_GNUC_INTERNAL void bus_marshal_VOID__OBJECT_BOOLEAN (GClosure     *closure,
                                                       GValue       *return_value,
                                                       guint         n_param_values,
                                                       const GValue *param_values,
                                                       gpointer      invocation_hint,
                                                       gpointer      marshal_data);

/* VOID:OBJECT,STRING (./marshalers.list:7) */
G_GNUC_INTERNAL void bus_marshal_VOID__OBJECT_STRING (GClosure     *closure,
                                                      GValue       *return_value,
                                                      guint         n_param_values,
                                                      const GValue *param_values,
                                                      gpointer      invocation_hint,
                                                      gpointer      marshal_data);

/* VOID:OBJECT,UINT,BOOLEAN (./marshalers.list:8) */
G_GNUC_INTERNAL void bus_marshal_VOID__OBJECT_UINT_BOOLEAN (GClosure     *closure,
                                                            GValue       *return_value,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint,
                                                            gpointer      marshal_data);

/* VOID:OBJECT,UINT,BOOLEAN,UINT (./marshalers.list:9) */
G_GNUC_INTERNAL void bus_marshal_VOID__OBJECT_UINT_BOOLEAN_UINT (GClosure     *closure,
                                                                 GValue       *return_value,
                                                                 guint         n_param_values,
                                                                 const GValue *param_values,
                                                                 gpointer      invocation_hint,
                                                                 gpointer      marshal_data);

/* VOID:OBJECT,STRING,STRING,STRING (./marshalers.list:10) */
G_GNUC_INTERNAL void bus_marshal_VOID__OBJECT_STRING_STRING_STRING (GClosure     *closure,
                                                                    GValue       *return_value,
                                                                    guint         n_param_values,
                                                                    const GValue *param_values,
                                                                    gpointer      invocation_hint,
                                                                    gpointer      marshal_data);

/* VOID:STRING (./marshalers.list:11) */
#define bus_marshal_VOID__STRING	g_cclosure_marshal_VOID__STRING

/* VOID:STRING,INT (./marshalers.list:12) */
G_GNUC_INTERNAL void bus_marshal_VOID__STRING_INT (GClosure     *closure,
                                                   GValue       *return_value,
                                                   guint         n_param_values,
                                                   const GValue *param_values,
                                                   gpointer      invocation_hint,
                                                   gpointer      marshal_data);

/* VOID:UINT,UINT,UINT (./marshalers.list:13) */
G_GNUC_INTERNAL void bus_marshal_VOID__UINT_UINT_UINT (GClosure     *closure,
                                                       GValue       *return_value,
                                                       guint         n_param_values,
                                                       const GValue *param_values,
                                                       gpointer      invocation_hint,
                                                       gpointer      marshal_data);

/* VOID:VOID (./marshalers.list:14) */
#define bus_marshal_VOID__VOID	g_cclosure_marshal_VOID__VOID

G_END_DECLS

#endif /* __bus_marshal_MARSHAL_H__ */

