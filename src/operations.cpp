#include <csignal>
#include <sys/types.h>

bool forceKillProcess(pid_t pid) { return kill(pid, SIGKILL) == 0; }

bool terminateProcess(pid_t pid) { return kill(pid, SIGTERM) == 0; }

bool suspendProcess(pid_t pid) { return kill(pid, SIGSTOP) == 0; }

bool resumeProcess(pid_t pid) { return kill(pid, SIGCONT) == 0; }

bool isProcessRunning(pid_t pid) { return kill(pid, 0) == 0; }
