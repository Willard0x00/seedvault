#include "cpu_info.h"
#include <stdio.h>
#include <intrin.h>
#include <cstring>

void print_h(int n) {
    printf("%x %x %x %x\n", n & 0xff, n >> 8 & 0xff, n >> 16 & 0xff, n >> 24 & 0xff);
}

void print_b(int n) {
    for(int i = 0; i < sizeof(int) * 8; ++i) {
        (i % 8 == 0 && i != 0) ? printf(" ") : 0;
        ( n & 0x80000000 ) ? printf("1") : printf("0");
        n = n << 1;
    }
    printf("\n");
}

CPUInfo::CPUInfo() {
    int cpu[4];
    __cpuid(cpu, 0);

    _max_input = cpu[0];
    memcpy(&_vendorid[0], &cpu[1], 4);  
    memcpy(&_vendorid[4], &cpu[3], 4);
    memcpy(&_vendorid[8], &cpu[2], 4);
    _vendorid[12] = '\0';

    __cpuid(cpu, 1);
    // EAX
    _steppingid = cpu[0] & 0x0F;
    _model = cpu[0] >> 4 & 0x0F;
    _family = cpu[0] >> 8 & 0x0F;
    _processor_type = cpu[0] >> 12 & 0x0F;
    _ext_model = cpu[0] >> 16 & 0xFF;
    _ext_family = cpu[0] >> 20 & 0xFF;

    _family = _ext_family + _family;
    _model = _model + (_ext_model << 4);

    // EBX
    _local_apicid = cpu[1] & 0xFF;
    _logical_processors = cpu[1] >> 8 & 0xFF;
    _clflush = cpu[1] >> 16 & 0xFF;
    _brand_index = cpu[1] >> 24 & 0xFF;

    // Feature Information ECX
    _features._sse3 = cpu[2] & 0x01;
    _features._pclmulqdq = cpu[2] >> 1 & 0x01;
    _features._dtes64 = cpu[2] >> 2 & 0x01;
    _features._monitor = cpu[2] >> 3 & 0x01;
    _features._dscpl = cpu[2] >> 4 & 0x01;
    _features._vmx = cpu[2] >> 5 & 0x01;
    _features._smx = cpu[2] >> 6 & 0x01;
    _features._est = cpu[2] >> 7 & 0x01;
    _features._tm2 = cpu[2] >> 8 & 0x01;
    _features._ssse3 = cpu[2] >> 9 & 0x01;
    _features._cnxtid = cpu[2] >> 10 & 0x01;
    _features._sdbg = cpu[2] >> 11 & 0x01;
    _features._fma = cpu[2] >> 12 & 0x01;
    _features._cmpxchg16b == cpu[2] >> 13 & 0x01;
    _features._xtpr = cpu[2] >> 14 & 0x01;
    _features._pdcm = cpu[2] >> 15 & 0x01;
    _features._pcid = cpu[2] >> 17 & 0x01;
    _features._dca = cpu[2] >> 18 & 0x01;
    _features._sse4_1 = cpu[2] >> 19 & 0x01;
    _features._sse4_2 = cpu[2] >> 20 & 0x01;
    _features._x2apic = cpu[2] >> 21 & 0x01;
    _features._movebe = cpu[2] >> 22 & 0x01;
    _features._popcnt = cpu[2] >> 23 & 0x01;
    _features._tscdeadline = cpu[2] >> 24 & 0x01;
    _features._aes = cpu[2] >> 25 & 0x01;
    _features._xsave = cpu[2] >> 26 & 0x01;
    _features._osxsave = cpu[2] >> 27 & 0x01;
    _features._avx = cpu[2] >> 28 & 0x01;
    _features._f16c = cpu[2] >> 29 & 0x01;
    _features._rdrand = cpu[2] >> 30 & 0x01;

    // Feature Information EDX
    _features._fpu = cpu[3] & 0x01;
    _features._vme = cpu[3] >> 1 & 0x01;
    _features._de = cpu[3] >> 2 & 0x01;
    _features._pse = cpu[3] >> 3 & 0x01;
    _features._tsc = cpu[3] >> 4 & 0x01;
    _features._msr = cpu[3] >> 5 & 0x01;
    _features._pae = cpu[3] >> 6 & 0x01;
    _features._mce = cpu[3] >> 7 & 0x01;
    _features._cx8 = cpu[3] >> 8 & 0x01;
    _features._apic = cpu[3] >> 9 & 0x01;
    _features._sep = cpu[3] >> 11 & 0x01;
    _features._mtrr = cpu[3] >> 12 & 0x01;
    _features._pge = cpu[3] >> 13 & 0x01;
    _features._mca = cpu[3] >> 14 & 0x01;
    _features._cmov = cpu[3] >> 15 & 0x01;
    _features._pat = cpu[3] >> 16 & 0x01;
    _features._pse36 = cpu[3] >> 17 & 0x01;
    _features._psn = cpu[3] >> 18 & 0x01;
    _features._clfsh = cpu[3] >> 19 & 0x01;
    _features._ds = cpu[3] >> 21 & 0x01;
    _features._acpi = cpu[3] >> 22 & 0x01;
    _features._mmx = cpu[3] >> 23 & 0x01;
    _features._fxsr = cpu[3] >> 24 & 0x01;
    _features._sse = cpu[3] >> 25 & 0x01;
    _features._sse2 = cpu[3] >> 26 & 0x01;
    _features._ss = cpu[3] >> 27 & 0x01;
    _features._htt = cpu[3] >> 28 & 0x01;
    _features._tm = cpu[3] >> 29 & 0x01;
    _features._pbe = cpu[3] >> 31 & 0x01;

    __cpuid(cpu, 2);
    print_b(cpu[0]);
    print_h(cpu[0]);
    print_b(cpu[1]);
    print_h(cpu[1]);
    print_b(cpu[2]);
    print_h(cpu[2]);
    print_b(cpu[3]);
    print_h(cpu[3]);
}

const char* present(bool val) {
    return (val) ? "Present" : "Absent";
}

void CPUInfo::print() {
    printf("Maximum Input Value for Basic CPUID Information: %d\n", _max_input);
    printf("Vendor ID: %s\n", _vendorid);
    printf("Stepping ID: %d\n", _steppingid);
    printf("Model: %d\n", _model);
    printf("Family: %d\n", _family);
    printf("Processor Type: %d\n", _processor_type);
    printf("Extended Model: %d\n", _ext_model);
    printf("Extended Family: %d\n", _ext_family);
    printf("Brand Index: %d\n", _brand_index);
    printf("CLFlush: %d\n", _clflush);
    printf("Logical Processors: %d\n", _logical_processors);
    printf("Local APIC ID: %d\n", _local_apicid);

    printf("Features:");
    printf("\nSSE3 | Intel Streaming SIMD Extensions 3 : ");
    printf(present(_features._sse3));
    printf("\nPCLMULQDQ : ");
    printf(present(_features._pclmulqdq));
    printf("\nDTES64 | 64-bit DS Area : ");
    printf(present(_features._dtes64));
    printf("\nMONITOR | MONITOR/MWAIT : ");
    printf(present(_features._monitor));
    printf("\nDS-CPL | CPL Qualified Debug Store : ");
    printf(present(_features._dscpl));
    printf("\nVMX | Virutal Machine Extensions : ");
    printf(present(_features._vmx));
    printf("\nSMX | Safer Mode Extenstions : ");
    printf(present(_features._smx));
    printf("\nEST | Enhanced Intel SpeedStep Technology : ");
    printf(present(_features._est));
    printf("\nTM2 | Thermal Monitor 2 : ");
    printf(present(_features._tm2));
    printf("\nSSSE3 | Supplemental Streaming SIMD Extensions 3 : ");
    printf(present(_features._ssse3));
    printf("\nCNXT-ID | L1 Context ID : ");
    printf(present(_features._cnxtid));
    printf("\nSDBG | IA32_DEBUG_INTERFACE MSR : ");
    printf(present(_features._sdbg));
    printf("\nFMA | FMA Extenstions : ");
    printf(present(_features._fma));
    printf("\nCMPXCHG16B : ");
    printf(present(_features._cmpxchg16b));
    printf("\nxTPR Update Control | IA32_MISC_ENABLES : ");
    printf(present(_features._xtpr));
    printf("\nPDCM | Perfmon and Debug Capability : ");
    printf(present(_features._pdcm));
    printf("\nPCID | Process-context identifiers : ");
    printf(present(_features._pcid));
    printf("\nDCA | Direct Cache Access : ");
    printf(present(_features._dca));
    printf("\nSSE4.1 : ");
    printf(present(_features._sse4_1));
    printf("\nSSE4.2 : ");
    printf(present(_features._sse4_2));
    printf("\nx2APIC : ");
    printf(present(_features._x2apic));
    printf("\nMOVBE : ");
    printf(present(_features._movebe));
    printf("\nPOPCNT : ");
    printf(present(_features._popcnt));
    printf("\nTSC-Deadline : ");
    printf(present(_features._tscdeadline));
    printf("\nAES : ");
    printf(present(_features._aes));
    printf("\nXSAVE : ");
    printf(present(_features._xsave));
    printf("\nOSXSAve : ");
    printf(present(_features._osxsave));
    printf("\nAVX : ");
    printf(present(_features._avx));
    printf("\nF16C : ");
    printf(present(_features._f16c));
    printf("\nRDRAND : ");
    printf(present(_features._rdrand));
           
    printf("\nFPU | FPU on chip : ");
    printf(present(_features._fpu));
    printf("\nVME | Virtual-8086 Mode Enhancement : ");
    printf(present(_features._vme));
    printf("\nDE | Debugging Extensions : ");
    printf(present(_features._de));
    printf("\nPSE | Page Size Extensions : ");
    printf(present(_features._pse));
    printf("\nTSC | Time Stamp Counter : ");
    printf(present(_features._tsc));
    printf("\nMSR | RDMSR and WRMSR Support : ");
    printf(present(_features._msr));
    printf("\nPAE | Physical Address Extensions : ");
    printf(present(_features._pae));
    printf("\nMCE | Machine Check Exception : ");
    printf(present(_features._mce));
    printf("\nCX8 | CMPXCHG8B Inst. : ");
    printf(present(_features._cx8));
    printf("\nAPIC | APIC on Chip : ");
    printf(present(_features._apic));
    printf("\nSEP | SYSENTER and SYSEXIT : ");
    printf(present(_features._sep));
    printf("\nMTRR | Memory Type Range Registers : ");
    printf(present(_features._mtrr));
    printf("\nPGE | PTE Global Bit : ");
    printf(present(_features._pge));
    printf("\nMCA | Machine Check Architecture : ");
    printf(present(_features._mca));
    printf("\nCMOV | Conditional Move/Compare Instruction : ");
    printf(present(_features._cmov));
    printf("\nPAT | Page Attribute Table : ");
    printf(present(_features._pat));
    printf("\nPSE-36 | Page Size Extension : ");
    printf(present(_features._pse36));
    printf("\nPSN | Processor Serial Number : ");
    printf(present(_features._psn));
    printf("\nCLFSH | CLFLUSH Instruction : ");
    printf(present(_features._clfsh));
    printf("\nDS | Debug Store : ");
    printf(present(_features._ds));
    printf("\nACPI | Thermal Monitor and Clock Ctrl : ");
    printf(present(_features._acpi));
    printf("\nMMX | MMX Technology : ");
    printf(present(_features._mmx));
    printf("\nFXSR | FXSAVE/FXRSTOR : ");
    printf(present(_features._fxsr));
    printf("\nSSE | SSE Extenstions : ");
    printf(present(_features._sse));
    printf("\nSSE2 | SSE2 Extensions : ");
    printf(present(_features._sse2));
    printf("\nSS | Self Snoop : ");
    printf(present(_features._ss));
    printf("\nHTT | Multi-threading : ");
    printf(present(_features._htt));
    printf("\nTM | Thermal Monitor : ");
    printf(present(_features._tm));
    printf("\nPBE | Pend. Brk. EN. : ");
    printf(present(_features._pbe));
}
