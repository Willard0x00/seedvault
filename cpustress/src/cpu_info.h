#ifndef CPU_INFO_H
#define CPU_INFO_H

#include <cstdint>

struct Features {
    bool _sse3;
    bool _pclmulqdq;
    bool _dtes64;
    bool _monitor;
    bool _dscpl;
    bool _vmx;
    bool _smx;
    bool _est;
    bool _tm2;
    bool _ssse3;
    bool _cnxtid;
    bool _sdbg;
    bool _fma;
    bool _cmpxchg16b;
    bool _xtpr;
    bool _pdcm;
    bool _pcid;
    bool _dca;
    bool _sse4_1;
    bool _sse4_2;
    bool _x2apic;
    bool _movebe;
    bool _popcnt;
    bool _tscdeadline;
    bool _aes;
    bool _xsave;
    bool _osxsave;
    bool _avx;
    bool _f16c;
    bool _rdrand;

    bool _fpu;
    bool _vme;
    bool _de;
    bool _pse;
    bool _tsc;
    bool _msr;
    bool _pae;
    bool _mce;
    bool _cx8;
    bool _apic;
    bool _sep;
    bool _mtrr;
    bool _pge;
    bool _mca;
    bool _cmov;
    bool _pat;
    bool _pse36;
    bool _psn;
    bool _clfsh;
    bool _ds;
    bool _acpi;
    bool _mmx;
    bool _fxsr;
    bool _sse;
    bool _sse2;
    bool _ss;
    bool _htt;
    bool _tm;
    bool _pbe;
};

class CPUInfo {
public:
    CPUInfo();
    
    void print();

    int _max_input;
    char _vendorid[13];
    
    uint8_t  _model;
    uint8_t  _family;
    uint8_t  _steppingid;

    uint8_t  _ext_model;
    uint8_t  _ext_family;
    
    uint8_t _processor_type;

    uint8_t _brand_index;
    uint8_t _clflush;
    uint8_t _logical_processors;
    uint8_t _local_apicid; 

    Features _features;
};

#endif
