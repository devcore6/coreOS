# coreOS
## What even is this?
Honestly, don't know. It is a fun project tho. I'll see how far I take stuff with this.

## To do list (in order of when I'm probably going to make stuff, give or take):
- VGA driver (currently under development)
- Serial driver
- `<stdio.h>` input functions (mostly done, still needing scanf however)
- PS2 mouse driver
- Preemptive scheduler
- Terminal system (already begun, mostly only needs to be adapted to run as a process rather than as part of the kernel)
- First sorta proper GUI
- SATA driver
- Filesystem
- `<string>`, `<iostream>`, and all other IO headers
- Support for multiple cores
- USB drivers
- Remaining C standard library
- Remaining C++ standard library (this will take forever)
- x86_64 long mode (ugh)

## That's a lot of to dos, what's already done?
- It boots
- Paging, heap allocation
- Interrupt service routines
- PS2 keyboard driver
- VGA text mode
- Basic kernel error reporting (mostly only for page faults currently)
- PIT which will probably only be used for the scheduler
- Kernel wait functions which put the CPU in a lower power state (C1)
- 12 TTYs

## Credits where credits are due
- [Meaty Skeleton](https://gitlab.com/sortie/meaty-skeleton) - I used this as a base structure while getting started
- [osdev.org](https://wiki.osdev.org/) - Got a lot of useful information while making this from there
