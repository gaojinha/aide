#ifndef VOICE_H
#define VOICE_H

int voice_init(void);
int voice_stt_whisper(const char *file, char *text);
int voice_tts_edge(const char *text, const char *output);

#endif
