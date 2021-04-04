#ifndef INTERFACE_H
#define INTERFACE_H

//Note:
//  mk_arch_:               cpu/board specific functions


// Should prepare periodic system timer + interrupts   
void mk_arch_prepare_scheduler();

// Called periodically
//  used for task switching
void mk_tick_callback();


#endif // INTERFACE_H