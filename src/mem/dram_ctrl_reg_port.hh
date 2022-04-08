#ifndef __MEM_DRAM_CTRL_REG_PORT_HH__
#define __MEM_DRAM_CTRL_REG_PORT_HH__

#include "mem/qport.hh"
#include "mem/tport.hh"

class DRAMCtrl;

class DRAMControlPort : public SimpleTimingPort
{
  protected:
    AddrRange addrRange;
    DRAMCtrl &dramCtrl;

    virtual Tick recvAtomic(PacketPtr pkt);
    virtual AddrRangeList getAddrRanges() const;

  public:
    DRAMControlPort(const std::string &_name, DRAMCtrl &_dramCtrl, AddrRange _addrRange);
    virtual ~DRAMControlPort() {}
};

#endif