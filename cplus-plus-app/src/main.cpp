#include <iostream>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
		void *handle;
		void (*func_print_name)();

		handle = dlopen("./../rust-library/target/debug/librustlib.dylib", RTLD_LAZY);

		if (!handle) {
				/* fail to load the library */
				fprintf(stderr, "Error: %s\n", dlerror());
				return EXIT_FAILURE;
		}

		*(void**)(&func_print_name) = dlsym(handle, "hello");
		if (!func_print_name) {
				/* no such symbol */
				fprintf(stderr, "Error: %s\n", dlerror());
				dlclose(handle);
				return EXIT_FAILURE;
		}

		func_print_name();
		dlclose(handle);

		return EXIT_SUCCESS;
}