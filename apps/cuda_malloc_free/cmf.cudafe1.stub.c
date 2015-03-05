#define __NV_CUBIN_HANDLE_STORAGE__ static
#include "crt/host_runtime.h"
#include "cmf.fatbin.c"
extern void __device_stub__Z8mykernelPf(float *);
extern void __device_stub__Z9mykernel2Pf(float *);
static void __nv_cudaEntityRegisterCallback(void **);
static void __sti____cudaRegisterAll_11_cmf_cpp1_ii_7aca50b9(void) __attribute__((__constructor__));
void __device_stub__Z8mykernelPf(float *__par0){__cudaSetupArgSimple(__par0, 0UL);__cudaLaunch(((char *)((void ( *)(float *))mykernel)));}
# 10 "cmf.cu"
void mykernel( float *__cuda_0)
# 10 "cmf.cu"
{__device_stub__Z8mykernelPf( __cuda_0);
# 16 "cmf.cu"
}
# 1 "cmf.cudafe1.stub.c"
void __device_stub__Z9mykernel2Pf( float *__par0) {  __cudaSetupArgSimple(__par0, 0UL); __cudaLaunch(((char *)((void ( *)(float *))mykernel2))); }
# 18 "cmf.cu"
void mykernel2( float *__cuda_0)
# 18 "cmf.cu"
{__device_stub__Z9mykernel2Pf( __cuda_0);
# 24 "cmf.cu"
}
# 1 "cmf.cudafe1.stub.c"
static void __nv_cudaEntityRegisterCallback( void **__T21) {  __nv_dummy_param_ref(__T21); __cudaRegisterEntry(__T21, ((void ( *)(float *))mykernel2), _Z9mykernel2Pf, (-1)); __cudaRegisterEntry(__T21, ((void ( *)(float *))mykernel), _Z8mykernelPf, (-1)); }
static void __sti____cudaRegisterAll_11_cmf_cpp1_ii_7aca50b9(void) {  __cudaRegisterBinary(__nv_cudaEntityRegisterCallback);  }
