/* -*- mode: C; c-basic-offset: 4; indent-tabs-mode: nil; -*- */
/* vim:set et sts=4: */
/* bus - The Input Bus
 * Copyright (C) 2008-2011 Peng Huang <shawn.p.huang@gmail.com>
 * Copyright (C) 2010-2011 Takao Fujiwara <takao.fujiwara1@gmail.com>
 * Copyright (C) 2008-2011 Red Hat, Inc.
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

#if !defined (__IBUS_H_INSIDE__) && !defined (IBUS_COMPILATION)
#error "Only <ibus.h> can be included directly"
#endif

/**
 * SECTION: ibusutil
 * @short_description: Utilities with C-Language.
 * @stability: Unstable
 *
 * Utilized functions are available for miscellaneous purposes.
 */

#ifndef __IBUS_UTIL_H_
#define __IBUS_UTIL_H_

/**
 * ibus_get_language_name:
 * @_locale: A const locale name.
 * @returns: language name
 */
const gchar *    ibus_get_language_name         (const gchar    *_locale);

#endif
