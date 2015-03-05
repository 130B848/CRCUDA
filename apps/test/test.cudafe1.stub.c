#define __NV_CUBIN_HANDLE_STORAGE__ static
#include "crt/host_runtime.h"
#include "test.fatbin.c"
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll_12_test_cpp1_ii_main(void) __attribute__((__constructor__));
static void __nv_cudaEntityRegisterCallback(void **__T20){__nv_dummy_param_ref(__T20);}
static void __sti____cudaRegisterAll_12_test_cpp1_ii_main(void){__cudaRegisterBinary(__nv_cudaEntityRegisterCallback);}
