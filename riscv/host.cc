#include "devices.h"
#include "processor.h"

host_t::host_t(std::vector<processor_t*>& procs)
  : procs(procs), signal_exits(procs.size(), false), exit_codes(procs.size(), 0)
{
}

#define HPRINT_BASE	0x0
#define CPRINT_BASE	0x1000
#define FINISH_BASE	0x2000
#define IO_SIZE 0x1000

bool host_t::load(reg_t addr, size_t len, uint8_t* bytes)
{
  return true;
}

bool host_t::store(reg_t addr, size_t len, const uint8_t* bytes)
{
  //printf("IN HOST STORE. Addr:%x\n", addr);
  int nprocs = procs.size();
  int hartid;
  
  if(addr >= HPRINT_BASE && addr < HPRINT_BASE+IO_SIZE) {

  }
  else if(addr >= CPRINT_BASE && addr < CPRINT_BASE+IO_SIZE) {
    for(int i=0; i<len; i++) {
      char c = bytes[i];
      printf("%c", c);
    }
  }
  else if(addr >= FINISH_BASE && addr < FINISH_BASE+IO_SIZE) {
    hartid = (addr - FINISH_BASE) >> 3;
    signal_exits[hartid] = true;
    exit_codes[hartid] = bytes[0];
    
    printf("[CORE%d FSH]: %x\n", hartid, bytes[0]);
    
    bool done = true;
    for(int i=0; i<nprocs; i++) {
      if(signal_exits[i] == false) {
        done = false;
        break;
      }
    }
    
    if(done) {
      exit(0);
    }
    
  }
  else {
    return false;
  }
  
//  if (addr >= MSIP_BASE && addr + len <= MSIP_BASE + procs.size()*sizeof(msip_t)) {
//    std::vector<msip_t> msip(procs.size());
//    std::vector<msip_t> mask(procs.size(), 0);
//    memcpy((uint8_t*)&msip[0] + addr - MSIP_BASE, bytes, len);
//    memset((uint8_t*)&mask[0] + addr - MSIP_BASE, 0xff, len);
//    for (size_t i = 0; i < procs.size(); ++i) {
//      if (!(mask[i] & 0xFF)) continue;
//      procs[i]->state.mip &= ~MIP_MSIP;
//      if (!!(msip[i] & 1))
//        procs[i]->state.mip |= MIP_MSIP;
//    }
//  } else if (addr >= MTIMECMP_BASE && addr + len <= MTIMECMP_BASE + procs.size()*sizeof(mtimecmp_t)) {
//    memcpy((uint8_t*)&mtimecmp[0] + addr - MTIMECMP_BASE, bytes, len);
//  } else if (addr >= MTIME_BASE && addr + len <= MTIME_BASE + sizeof(mtime_t)) {
//    memcpy((uint8_t*)&mtime + addr - MTIME_BASE, bytes, len);
//  } else {
//    return false;
//  }
//  increment(0);
  return true;
}
