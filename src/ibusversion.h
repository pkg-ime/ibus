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
/**
 * SECTION: ibusversion
 * @short_description: Current version of IBus.
 * @stability: Stable
 *
 * IBusVersion shows the current IBus version.
 */

#ifndef __IBUS_VERSION_H_
#define __IBUS_VERSION_H_
/* compile time version
 */
/**
 * IBUS_MAJOR_VERSION:
 *
 * IBus major version.
 */
#define IBUS_MAJOR_VERSION				(1)

/**
 * IBUS_MINOR_VERSION:
 *
 * IBus minor version.
 */
#define IBUS_MINOR_VERSION				(3)

/**
 * IBUS_MICRO_VERSION:
 *
 * IBus micro version.
 */
#define IBUS_MICRO_VERSION				(99)

/**
 * IBUS_CHECK_VERSION:
 * @major: Major version of ibus.
 * @minor: Minor version of ibus.
 * @micro: Micro version of ibus.
 *
 * Check whether the current IBus version is equal to or greater than
 * given major.minor.micro.
 */
#define	IBUS_CHECK_VERSION(major,minor,micro)	\
    (IBUS_MAJOR_VERSION > (major) || \
     (IBUS_MAJOR_VERSION == (major) && IBUS_MINOR_VERSION > (minor)) || \
     (IBUS_MAJOR_VERSION == (major) && IBUS_MINOR_VERSION == (minor) && \
      IBUS_MICRO_VERSION >= (micro)))

#endif

