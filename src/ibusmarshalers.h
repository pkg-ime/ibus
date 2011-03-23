
#ifndef __ibus_marshal_MARSHAL_H__
#define __ibus_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:NONE (./ibusmarshalers.list:1) */
#define ibus_marshal_VOID__VOID	g_cclosure_marshal_VOID__VOID
#define ibus_marshal_VOID__NONE	ibus_marshal_VOID__VOID

/* VOID:OBJECT (./ibusmarshalers.list:2) */
#define ibus_marshal_VOID__OBJECT	g_cclosure_marshal_VOID__OBJECT

/* VOID:POINTER (./ibusmarshalers.list:3) */
#define ibus_marshal_VOID__POINTER	g_cclosure_marshal_VOID__POINTER

/* VOID:STRING (./ibusmarshalers.list:4) */
#define ibus_marshal_VOID__STRING	g_cclosure_marshal_VOID__STRING

/* VOID:STRING,INT (./ibusmarshalers.list:5) */
extern void ibus_marshal_VOID__STRING_INT (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);

/* VOID:STRING,UINT (./ibusmarshalers.list:6) */
extern void ibus_marshal_VOID__STRING_UINT (GClosure     *closure,
                                            GValue       *return_value,
                                            guint         n_param_values,
                                            const GValue *param_values,
                                            gpointer      invocation_hint,
                                            gpointer      marshal_data);

/* BOOL:POINTER (./ibusmarshalers.list:7) */
extern void ibus_marshal_BOOLEAN__POINTER (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);
#define ibus_marshal_BOOL__POINTER	ibus_marshal_BOOLEAN__POINTER

/* BOOL:POINTER,POINTER (./ibusmarshalers.list:8) */
extern void ibus_marshal_BOOLEAN__POINTER_POINTER (GClosure     *closure,
                                                   GValue       *return_value,
                                                   guint         n_param_values,
                                                   const GValue *param_values,
                                                   gpointer      invocation_hint,
                                                   gpointer      marshal_data);
#define ibus_marshal_BOOL__POINTER_POINTER	ibus_marshal_BOOLEAN__POINTER_POINTER

/* BOOL:UINT,UINT (./ibusmarshalers.list:9) */
extern void ibus_marshal_BOOLEAN__UINT_UINT (GClosure     *closure,
                                             GValue       *return_value,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint,
                                             gpointer      marshal_data);
#define ibus_marshal_BOOL__UINT_UINT	ibus_marshal_BOOLEAN__UINT_UINT

/* BOOL:UINT,UINT,UINT (./ibusmarshalers.list:10) */
extern void ibus_marshal_BOOLEAN__UINT_UINT_UINT (GClosure     *closure,
                                                  GValue       *return_value,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint,
                                                  gpointer      marshal_data);
#define ibus_marshal_BOOL__UINT_UINT_UINT	ibus_marshal_BOOLEAN__UINT_UINT_UINT

/* BOOL:ULONG (./ibusmarshalers.list:11) */
extern void ibus_marshal_BOOLEAN__ULONG (GClosure     *closure,
                                         GValue       *return_value,
                                         guint         n_param_values,
                                         const GValue *param_values,
                                         gpointer      invocation_hint,
                                         gpointer      marshal_data);
#define ibus_marshal_BOOL__ULONG	ibus_marshal_BOOLEAN__ULONG

/* VOID:INT,INT,INT,INT (./ibusmarshalers.list:12) */
extern void ibus_marshal_VOID__INT_INT_INT_INT (GClosure     *closure,
                                                GValue       *return_value,
                                                guint         n_param_values,
                                                const GValue *param_values,
                                                gpointer      invocation_hint,
                                                gpointer      marshal_data);

/* VOID:UINT,UINT (./ibusmarshalers.list:13) */
extern void ibus_marshal_VOID__UINT_UINT (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

/* VOID:INT,UINT (./ibusmarshalers.list:14) */
extern void ibus_marshal_VOID__INT_UINT (GClosure     *closure,
                                         GValue       *return_value,
                                         guint         n_param_values,
                                         const GValue *param_values,
                                         gpointer      invocation_hint,
                                         gpointer      marshal_data);

/* VOID:UINT,UINT,UINT (./ibusmarshalers.list:15) */
extern void ibus_marshal_VOID__UINT_UINT_UINT (GClosure     *closure,
                                               GValue       *return_value,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint,
                                               gpointer      marshal_data);

/* VOID:OBJECT,UINT,BOOL (./ibusmarshalers.list:16) */
extern void ibus_marshal_VOID__OBJECT_UINT_BOOLEAN (GClosure     *closure,
                                                    GValue       *return_value,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint,
                                                    gpointer      marshal_data);
#define ibus_marshal_VOID__OBJECT_UINT_BOOL	ibus_marshal_VOID__OBJECT_UINT_BOOLEAN

/* VOID:OBJECT,UINT,BOOL,UINT (./ibusmarshalers.list:17) */
extern void ibus_marshal_VOID__OBJECT_UINT_BOOLEAN_UINT (GClosure     *closure,
                                                         GValue       *return_value,
                                                         guint         n_param_values,
                                                         const GValue *param_values,
                                                         gpointer      invocation_hint,
                                                         gpointer      marshal_data);
#define ibus_marshal_VOID__OBJECT_UINT_BOOL_UINT	ibus_marshal_VOID__OBJECT_UINT_BOOLEAN_UINT

/* VOID:OBJECT,BOOL (./ibusmarshalers.list:18) */
extern void ibus_marshal_VOID__OBJECT_BOOLEAN (GClosure     *closure,
                                               GValue       *return_value,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint,
                                               gpointer      marshal_data);
#define ibus_marshal_VOID__OBJECT_BOOL	ibus_marshal_VOID__OBJECT_BOOLEAN

/* VOID:BOXED,BOOL (./ibusmarshalers.list:19) */
extern void ibus_marshal_VOID__BOXED_BOOLEAN (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);
#define ibus_marshal_VOID__BOXED_BOOL	ibus_marshal_VOID__BOXED_BOOLEAN

/* VOID:BOXED (./ibusmarshalers.list:20) */
#define ibus_marshal_VOID__BOXED	g_cclosure_marshal_VOID__BOXED

/* VOID:STRING,STRING,BOXED (./ibusmarshalers.list:21) */
extern void ibus_marshal_VOID__STRING_STRING_BOXED (GClosure     *closure,
                                                    GValue       *return_value,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint,
                                                    gpointer      marshal_data);

/* VOID:STRING,STRING,STRING (./ibusmarshalers.list:22) */
extern void ibus_marshal_VOID__STRING_STRING_STRING (GClosure     *closure,
                                                     GValue       *return_value,
                                                     guint         n_param_values,
                                                     const GValue *param_values,
                                                     gpointer      invocation_hint,
                                                     gpointer      marshal_data);

/* VOID:UINT (./ibusmarshalers.list:23) */
#define ibus_marshal_VOID__UINT	g_cclosure_marshal_VOID__UINT

/* VOID:UINT,POINTER (./ibusmarshalers.list:24) */
#define ibus_marshal_VOID__UINT_POINTER	g_cclosure_marshal_VOID__UINT_POINTER

G_END_DECLS

#endif /* __ibus_marshal_MARSHAL_H__ */

