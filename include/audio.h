#ifndef AUDIO_H
#define AUDIO_H

int init_audio(void);
void play_eat_sound(void);
void play_gameplay_music(void);
void pause_gameplay_music(void);
void resume_gameplay_music(void);
void stop_gameplay_music(void);
void cleanup_audio(void);

#endif