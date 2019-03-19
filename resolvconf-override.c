/* -*- Mode: C; indent-tabs-mode: t -*- */

/*
 * Copyright 2013, 2017 Bastien Nocera
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the Gnome Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301  USA.
 *
 * Authors: Bastien Nocera <hadess@hadess.net>
 *
 */

#include <resolv.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <assert.h>

#define __USE_GNU
#include <dlfcn.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* For debugging */
#if 0
static void
print_ns (void)
{
	int i;
	for(i=0;i<_res.nscount;i++) {
		char buf[INET_ADDRSTRLEN];

		inet_ntop(AF_INET, &_res.nsaddr_list[i].sin_addr, buf, sizeof(buf));
		fprintf(stderr, "dnssrvr: %s\n", buf);
	}
}
#endif

static void
override_ns (void)
{
	int i;
	int valid_ns = 0;

	for (i = 0; i < MAXNS; i++) {
		char envvar[] = "NAMESERVERx";
		const char *ns;

		/* Rename to NAMESERVERx where x is the name server number,
		 * and the first one is NAMESERVER1 */
		envvar[10] = '1' + i;

		ns = getenv (envvar);
		if (ns == NULL)
			break;
		if (inet_pton (AF_INET, ns, &_res.nsaddr_list[i].sin_addr) < 1) {
			fprintf (stderr, "Ignoring invalid nameserver '%s'\n", ns);
			continue;
		}

		valid_ns++;
	}

	/* Set the number of valid nameservers */
	if (valid_ns > 0)
		_res.nscount = valid_ns;
}

static void
override_options (void)
{
	if (getenv ("FORCE_DNS_OVER_TCP") != NULL)
		_res.options |= RES_USEVC;
}

struct hostent *gethostbyname(const char *name)
{
	if (res_init () < 0)
		return NULL;
	struct hostent * (*f)() = dlsym (RTLD_NEXT, "gethostbyname");
	struct hostent *ret =  f(name);

	return ret;
}

int getaddrinfo(const char *node, const char *service,
		const struct addrinfo *hints,
		struct addrinfo **res)
{
	if (res_init () < 0)
		return EAI_SYSTEM;
	int (*f)() = dlsym (RTLD_NEXT, "getaddrinfo");
	return f(node, service, hints, res);
}

int __res_init(void)
{
	int (*f)() = dlsym (RTLD_NEXT, "__res_init");
	assert (f);
	int ret = f();

	override_ns ();
	override_options ();

	return ret;
}
