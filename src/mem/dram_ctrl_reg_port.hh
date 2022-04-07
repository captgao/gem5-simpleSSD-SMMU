#include "mem/qport.hh"
#include "mem/tport.hh"
#include "mem/dram_ctrl.hh"

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
