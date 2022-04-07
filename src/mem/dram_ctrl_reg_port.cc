#include "mem/dram_ctrl_reg_port.hh"

DRAMControlPort::DRAMControlPort(const std::string &_name, DRAMCtrl &_dramCtrl, AddrRange _addrRange)
:
    SimpleTimingPort(_name, &_dramCtrl),
    dramCtrl(_dramCtrl),
    addrRange(_addrRange)
{}

Tick
DRAMControlPort::recvAtomic(PacketPtr pkt)
{
    Addr addr = pkt->getAddr();
    unsigned size = pkt->getSize();

    if (!addrRange.contains(addr) || !addrRange.contains(addr+size))
        panic("DRAM: invalid address on control port %x, packet size %d",
                addr, size);

    // @todo: We need to pay for this and not just zero it out
    pkt->headerDelay = pkt->payloadDelay = 0;

    return pkt->isRead() ? dramCtrl.readControl(pkt) : dramCtrl.writeControl(pkt);
}

AddrRangeList
DRAMControlPort::getAddrRanges() const
{
    AddrRangeList list;
    list.push_back(addrRange);
    return list;
}