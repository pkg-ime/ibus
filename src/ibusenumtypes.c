
/* Generated data (by glib-mkenums) */

#include "ibus.h"

/* enumerations from "ibusobject.h" */
GType
ibus_object_flags_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { IBUS_IN_DESTRUCTION, "IBUS_IN_DESTRUCTION", "in-destruction" },
            { IBUS_DESTROYED, "IBUS_DESTROYED", "destroyed" },
            { IBUS_RESERVED_1, "IBUS_RESERVED_1", "reserved-1" },
            { IBUS_RESERVED_2, "IBUS_RESERVED_2", "reserved-2" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("IBusObjectFlags"), values);
    }
    return etype;
}

/* enumerations from "ibusattribute.h" */
GType
ibus_attr_type_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_ATTR_TYPE_UNDERLINE, "IBUS_ATTR_TYPE_UNDERLINE", "underline" },
            { IBUS_ATTR_TYPE_FOREGROUND, "IBUS_ATTR_TYPE_FOREGROUND", "foreground" },
            { IBUS_ATTR_TYPE_BACKGROUND, "IBUS_ATTR_TYPE_BACKGROUND", "background" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusAttrType"), values);
    }
    return etype;
}

GType
ibus_attr_underline_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_ATTR_UNDERLINE_NONE, "IBUS_ATTR_UNDERLINE_NONE", "none" },
            { IBUS_ATTR_UNDERLINE_SINGLE, "IBUS_ATTR_UNDERLINE_SINGLE", "single" },
            { IBUS_ATTR_UNDERLINE_DOUBLE, "IBUS_ATTR_UNDERLINE_DOUBLE", "double" },
            { IBUS_ATTR_UNDERLINE_LOW, "IBUS_ATTR_UNDERLINE_LOW", "low" },
            { IBUS_ATTR_UNDERLINE_ERROR, "IBUS_ATTR_UNDERLINE_ERROR", "error" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusAttrUnderline"), values);
    }
    return etype;
}

/* enumerations from "ibusproperty.h" */
GType
ibus_prop_type_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { PROP_TYPE_NORMAL, "PROP_TYPE_NORMAL", "normal" },
            { PROP_TYPE_TOGGLE, "PROP_TYPE_TOGGLE", "toggle" },
            { PROP_TYPE_RADIO, "PROP_TYPE_RADIO", "radio" },
            { PROP_TYPE_MENU, "PROP_TYPE_MENU", "menu" },
            { PROP_TYPE_SEPARATOR, "PROP_TYPE_SEPARATOR", "separator" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusPropType"), values);
    }
    return etype;
}

GType
ibus_prop_state_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { PROP_STATE_UNCHECKED, "PROP_STATE_UNCHECKED", "unchecked" },
            { PROP_STATE_CHECKED, "PROP_STATE_CHECKED", "checked" },
            { PROP_STATE_INCONSISTENT, "PROP_STATE_INCONSISTENT", "inconsistent" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusPropState"), values);
    }
    return etype;
}

/* enumerations from "ibustypes.h" */
GType
ibus_modifier_type_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { IBUS_SHIFT_MASK, "IBUS_SHIFT_MASK", "shift-mask" },
            { IBUS_LOCK_MASK, "IBUS_LOCK_MASK", "lock-mask" },
            { IBUS_CONTROL_MASK, "IBUS_CONTROL_MASK", "control-mask" },
            { IBUS_MOD1_MASK, "IBUS_MOD1_MASK", "mod1-mask" },
            { IBUS_MOD2_MASK, "IBUS_MOD2_MASK", "mod2-mask" },
            { IBUS_MOD3_MASK, "IBUS_MOD3_MASK", "mod3-mask" },
            { IBUS_MOD4_MASK, "IBUS_MOD4_MASK", "mod4-mask" },
            { IBUS_MOD5_MASK, "IBUS_MOD5_MASK", "mod5-mask" },
            { IBUS_BUTTON1_MASK, "IBUS_BUTTON1_MASK", "button1-mask" },
            { IBUS_BUTTON2_MASK, "IBUS_BUTTON2_MASK", "button2-mask" },
            { IBUS_BUTTON3_MASK, "IBUS_BUTTON3_MASK", "button3-mask" },
            { IBUS_BUTTON4_MASK, "IBUS_BUTTON4_MASK", "button4-mask" },
            { IBUS_BUTTON5_MASK, "IBUS_BUTTON5_MASK", "button5-mask" },
            { IBUS_HANDLED_MASK, "IBUS_HANDLED_MASK", "handled-mask" },
            { IBUS_FORWARD_MASK, "IBUS_FORWARD_MASK", "forward-mask" },
            { IBUS_IGNORED_MASK, "IBUS_IGNORED_MASK", "ignored-mask" },
            { IBUS_SUPER_MASK, "IBUS_SUPER_MASK", "super-mask" },
            { IBUS_HYPER_MASK, "IBUS_HYPER_MASK", "hyper-mask" },
            { IBUS_META_MASK, "IBUS_META_MASK", "meta-mask" },
            { IBUS_RELEASE_MASK, "IBUS_RELEASE_MASK", "release-mask" },
            { IBUS_MODIFIER_MASK, "IBUS_MODIFIER_MASK", "modifier-mask" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("IBusModifierType"), values);
    }
    return etype;
}

GType
ibus_capabilite_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { IBUS_CAP_PREEDIT_TEXT, "IBUS_CAP_PREEDIT_TEXT", "preedit-text" },
            { IBUS_CAP_AUXILIARY_TEXT, "IBUS_CAP_AUXILIARY_TEXT", "auxiliary-text" },
            { IBUS_CAP_LOOKUP_TABLE, "IBUS_CAP_LOOKUP_TABLE", "lookup-table" },
            { IBUS_CAP_FOCUS, "IBUS_CAP_FOCUS", "focus" },
            { IBUS_CAP_PROPERTY, "IBUS_CAP_PROPERTY", "property" },
            { IBUS_CAP_SURROUNDING_TEXT, "IBUS_CAP_SURROUNDING_TEXT", "surrounding-text" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("IBusCapabilite"), values);
    }
    return etype;
}

GType
ibus_preedit_focus_mode_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_ENGINE_PREEDIT_CLEAR, "IBUS_ENGINE_PREEDIT_CLEAR", "clear" },
            { IBUS_ENGINE_PREEDIT_COMMIT, "IBUS_ENGINE_PREEDIT_COMMIT", "commit" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusPreeditFocusMode"), values);
    }
    return etype;
}

GType
ibus_orientation_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_ORIENTATION_HORIZONTAL, "IBUS_ORIENTATION_HORIZONTAL", "horizontal" },
            { IBUS_ORIENTATION_VERTICAL, "IBUS_ORIENTATION_VERTICAL", "vertical" },
            { IBUS_ORIENTATION_SYSTEM, "IBUS_ORIENTATION_SYSTEM", "system" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusOrientation"), values);
    }
    return etype;
}

GType
ibus_bus_name_flag_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { IBUS_BUS_NAME_FLAG_ALLOW_REPLACEMENT, "IBUS_BUS_NAME_FLAG_ALLOW_REPLACEMENT", "allow-replacement" },
            { IBUS_BUS_NAME_FLAG_REPLACE_EXISTING, "IBUS_BUS_NAME_FLAG_REPLACE_EXISTING", "replace-existing" },
            { IBUS_BUS_NAME_FLAG_DO_NOT_QUEUE, "IBUS_BUS_NAME_FLAG_DO_NOT_QUEUE", "do-not-queue" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("IBusBusNameFlag"), values);
    }
    return etype;
}

GType
ibus_bus_request_name_reply_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_BUS_REQUEST_NAME_REPLY_PRIMARY_OWNER, "IBUS_BUS_REQUEST_NAME_REPLY_PRIMARY_OWNER", "primary-owner" },
            { IBUS_BUS_REQUEST_NAME_REPLY_IN_QUEUE, "IBUS_BUS_REQUEST_NAME_REPLY_IN_QUEUE", "in-queue" },
            { IBUS_BUS_REQUEST_NAME_REPLY_EXISTS, "IBUS_BUS_REQUEST_NAME_REPLY_EXISTS", "exists" },
            { IBUS_BUS_REQUEST_NAME_REPLY_ALREADY_OWNER, "IBUS_BUS_REQUEST_NAME_REPLY_ALREADY_OWNER", "already-owner" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusBusRequestNameReply"), values);
    }
    return etype;
}

GType
ibus_bus_start_service_by_name_reply_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_BUS_START_REPLY_SUCCESS, "IBUS_BUS_START_REPLY_SUCCESS", "success" },
            { IBUS_BUS_START_REPLY_ALREADY_RUNNING, "IBUS_BUS_START_REPLY_ALREADY_RUNNING", "already-running" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusBusStartServiceByNameReply"), values);
    }
    return etype;
}

GType
ibus_error_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { IBUS_ERROR_NO_ENGINE, "IBUS_ERROR_NO_ENGINE", "engine" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("IBusError"), values);
    }
    return etype;
}


/* Generated data ends here */

