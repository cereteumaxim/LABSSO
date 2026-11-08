// What the sysinfo system call fills in for the caller.
struct sysinfo {
  uint64 freemem; // free physical memory, in bytes
  uint64 nproc;   // processes whose state is not UNUSED
};
