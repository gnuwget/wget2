/*
 * Copyright(c) 2012 Tim Ruehsen
 * Copyright(c) 2015-2019 Free Software Foundation, Inc.
 *
 * This file is part of libwget.
 *
 * Libwget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libwget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libwget.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * Memory allocation routines
 *
 * Changelog
 * 25.06.2012  Tim Ruehsen  created
 *
 */

#include <config.h>

#include <string.h>

#include <wget.h>
#include "private.h"

/**
 * \file
 * \brief Memory functions
 * \defgroup libwget-mem Memory functions
 * @{
 *
 * This is a collections of short memory function not available in standard libraries.
 */

/**
 * \param[in] m Memory to clone
 * \param[in] n Length of memory
 * \return Cloned memory
 *
 * Clone's the memory region \p m with length \p n.
 * Returns NULL if \p m is NULL.
 *
 * You should free() the returned pointer when not needed any more.
 */
void *wget_memdup(const void *m, size_t n)
{
	return m ? memcpy(xmalloc(n), m, n) : NULL;
}

/**
 * \param[in] s String to clone
 * \return Cloned string
 *
 * Clone's the string \p s like strdup() does.
 * Returns NULL if \p s is NULL.
 *
 * You should free() the returned string when not needed any more.
 */
char *wget_strdup(const char *s)
{
	return s ? wget_memdup(s, strlen(s) + 1) : NULL;
}

/**
 * \param[in] m Memory to convert into string
 * \param[in] n Length of memory
 * \return Created string
 *
 * Convert the given memory region \p m with length \p n into a C string.
 * Returns NULL if \p m is NULL.
 *
 * You should free() the returned string when not needed any more.
 */
char *wget_strmemdup(const void *m, size_t n)
{
	if (!m)
		return NULL;

	char *ret = memcpy(xmalloc(n + 1), m, n);
	ret[n] = 0;

	return ret;
}

/**
 * \param[out] s Buffer to hold the C string output
 * \param[in] ssize Size of the output buffer
 * \param[in] m Memory to read from
 * \param[in] n Length of memory
 *
 * Convert the given memory region \p m with length \p n into a C string at \p s.
 * A max. of \p ssize - 1  is copied into \p s.
 */
void wget_strmemcpy(char *s, size_t ssize, const void *m, size_t n)
{
	if (!s || !ssize)
		return;

	if (likely(n > 0)) {
		if (n >= ssize)
			n = ssize - 1; // truncate

		if (m)
			memmove(s, m, n);
		else
			n = 0;
	}
	s[n] = 0;
}

/**@}*/
