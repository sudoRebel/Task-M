#pragma once

#include <sys/types.h> // pid_t

bool forceKillProcess(pid_t pid);

bool terminateProcess(pid_t pid);

bool suspendProcess(pid_t pid);

bool resumeProcess(pid_t pid);

bool isProcessRunning(pid_t pid);
