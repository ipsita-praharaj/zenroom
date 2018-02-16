/*  Zenroom (DECODE project)
 *
 *  (c) Copyright 2017-2018 Dyne.org foundation
 *  designed, written and maintained by Denis Roio <jaromil@dyne.org>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Public License as published
 * by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// open/close
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// read
#include <unistd.h>

#include <errno.h>

#include <jutils.h>

#include <luasandbox.h>
#include <luasandbox/util/util.h>
#include <luasandbox/lauxlib.h>

#include <luazen.h>

#define CONF "zenroom.conf"

#define MAX_SCRIPT 102400 // process max 100Kb scripts
#define MAX_CONF 1024 // load max 1Kb confs

// prototypes from lua_functions
void lsb_setglobal_string(lsb_lua_sandbox *lsb, char *key, char *val);
void lsb_openlibs(lsb_lua_sandbox *lsb);
// from timing.c
// extern int set_hook(lua_State *L);

// void log_debug(lua_State *l, lua_Debug *d) {
// 	error("%s\n%s\n%s",d->name, d->namewhat, d->short_src);
// }

void logger(void *context, const char *component,
                   int level, const char *fmt, ...) {
	// suppress warnings about these unused paraments
	(void)context;
	(void)level;

	va_list args;
	fprintf(stderr,"%s: ", component ? component : "unknown");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fwrite("\n", 1, 1, stderr);
	fflush(stderr);
}

int main(int argc, char **argv) {
	lsb_lua_sandbox *lsb = NULL;
	static char conffile[512] = "zenroom.conf";
	static char scriptfile[512] = "zenroom.lua";
	static char conf[MAX_CONF];
	static char script[MAX_SCRIPT];
	int fdconf, fdscript;
	size_t readin;

	char *p;
	int opt, index;
	int return_code = 1; // return error by default

	const char *short_options = "hdc:";
    const char *help =
		"Usage: zenroom [-c config] script.lua\n";
    scriptfile[0] = '\0';

	notice( "LUA Restricted execution environment %s",VERSION);
	act("Copyright (C) 2017-2018 Dyne.org foundation");
	while((opt = getopt(argc, argv, short_options)) != -1) {
		switch(opt) {
		case 'd':
			set_debug(3);
			break;
		case 'h':
			fprintf(stdout,"%s",help);
			exit(0);
			break;
		case 'c':
			snprintf(conffile,511,"%s",optarg);
			break;
		case '?': error(help); exit(1);
		default:  error(help); exit(1);
		}
	}
	for (index = optind; index < argc; index++) {
		snprintf(scriptfile,511,"%s",argv[index]);
		act("script: %s", scriptfile);
	}
	if(scriptfile[0] == '\0') {
		error("No script specified.");
		error(help);
		exit(1);
	}

	fdscript = open(scriptfile, O_RDONLY);
	if(fdscript<0) {
		error("Error opening %s: %s", scriptfile, strerror(errno));
		close(fdscript);
		exit(1); }
	readin = read(fdscript, script, MAX_SCRIPT);
	if(readin<0) {
		error("Error reading %s: %s", scriptfile, strerror(errno));
		close(fdscript);
		exit(1); }
	act("script size: %u", readin);
	func("script contents:\n%s\n", script);
	close(fdscript);


	fdconf = open(conffile, O_RDONLY);
	if(fdconf<0) {
		error("Error opening %s: %s", conffile, strerror(errno));
		close(fdconf);
		exit(1); }
	readin = read(fdconf, conf, MAX_CONF);
	if(readin<0) {
		error("Error reading %s: %s", conffile, strerror(errno));
		close(fdconf);
		exit(1); }
	act("conf size: %u", readin);
	act("configuration: $s", conffile);
	func("conf contents:\n%s\n", conf);
	close(fdscript);


	// TODO: how to pass config file and script to javascript?

	lsb_logger lsb_vm_logger = { .context = scriptfile, .cb = logger };

	lsb = lsb_create(NULL, scriptfile, conf, &lsb_vm_logger);
	if(!lsb) {
		error("Error creating sandbox: %s", lsb_get_error(lsb));
	} else {
		const luaL_Reg *lib;
		const char *r;
		// load our own extensions
		lib = (luaL_Reg*) &luazen;
		func("loading crypto extensions");
		for (; lib->func; lib++) {
			func("%s",lib->name);
			lsb_add_function(lsb, lib->func, lib->name);
		}

		// initialise global variables
		lsb_setglobal_string(lsb, "VERSION", VERSION);
		lsb_openlibs(lsb);

		r = lsb_init(lsb, NULL);
		if(r) {
			error(r);
			error(lsb_get_error(lsb));
			error("Error detected. Execution aborted.");
		}
		return_code = 0; // return success
		// debugging stats here
		// while(lsb_get_state(lsb) == LSB_RUNNING)
		// 	act("running...");
		int u;
		u = lsb_usage(lsb, LSB_UT_MEMORY, LSB_US_CURRENT);
		act("used memory: %u bytes", u);
		u = lsb_usage(lsb, LSB_UT_INSTRUCTION, LSB_US_CURRENT);
		act("executed operations: %u", u);
	}

	act("DECODE exec terminating.");
	if(lsb) {
		lsb_pcall_teardown(lsb);
		lsb_stop_sandbox_clean(lsb);
		p = lsb_destroy(lsb);
		if(p) free(p);
	}
	exit(return_code);
}
