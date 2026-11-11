// Copyright (c) 2025.
// IWIN-FINS Lab, Shanghai Jiao Tong University, Shanghai, China.
// All rights reserved.

#include "Task.h"

#include "MultiMedia/BeepMusic.h"

void TaskBeepMusic() {
    BeepMusic::MusicChannels[0].BeepService();
}
TASK_EXPORT(TaskBeepMusic);
