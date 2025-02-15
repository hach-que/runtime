#include <config.h>
#include <mono/utils/mono-compiler.h>
#include <mono/eglib/glib.h>

#if defined (HOST_WASM)

#include "mono/utils/mono-dl.h"
#include "mono/utils/mono-embed.h"
#include "mono/utils/mono-path.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <glib.h>

#ifndef HOST_WASI
#include <dlfcn.h>
#endif

const char *
mono_dl_get_so_prefix (void)
{
	return "";
}

const char **
mono_dl_get_so_suffixes (void)
{
	static const char *suffixes[] = {
		".wasm", //we only recognize .wasm files for DSOs.
		"",
	};
	return suffixes;
}

const char*
mono_dl_get_system_dir (void)
{
	return NULL;
}


void*
mono_dl_lookup_symbol (MonoDl *module, const char *name)
{
	return NULL;
}

char*
mono_dl_current_error_string (void)
{
	return g_strdup ("");
}

// Copied from mono-dl-posix.c
int
mono_dl_convert_flags (int mono_flags, int native_flags)
{
	int lflags = native_flags;

#ifndef HOST_WASI // On WASI, these flags are undefined and not required

	// Specifying both will default to LOCAL
	if (mono_flags & MONO_DL_GLOBAL && !(mono_flags & MONO_DL_LOCAL))
		lflags |= RTLD_GLOBAL;
	else
		lflags |= RTLD_LOCAL;

	if (mono_flags & MONO_DL_LAZY)
		lflags |= RTLD_LAZY;
	else
		lflags |= RTLD_NOW;

#endif

	return lflags;
}

void *
mono_dl_open_file (const char *file, int flags, MonoError *error)
{
	// Actual dlopen is done in driver.c:wasm_dl_load()
	return NULL;
}

void
mono_dl_close_handle (MonoDl *module, MonoError *error)
{
}

#else

MONO_EMPTY_SOURCE_FILE (mono_dl_wasm);

#endif
