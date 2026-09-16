#pragma once
#include "djui.h"

extern bool gDjuiPanelJoinMessageVisible;
extern float gDownloadProgress;
extern float gDownloadProgressInf;
#define DOWNLOAD_ESTIMATE_LENGTH 64
extern char gDownloadEstimate[];

void djui_panel_join_message_error(char* message);
void djui_panel_join_message_create(struct DjuiBase* caller);
