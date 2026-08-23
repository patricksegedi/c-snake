#include "audio.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <stdio.h>

static MIX_Mixer *mixer = NULL;
static MIX_Audio *eat_sound = NULL;
static MIX_Audio *gameplay_background_music = NULL;
static MIX_Track *gameplay_music_track = NULL;

int init_audio(void)
{
    if (!MIX_Init()) {
        printf("MIX_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    mixer = MIX_CreateMixerDevice(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        NULL
    );

    if (mixer == NULL) {
        printf("MIX_CreateMixerDevice failed: %s\n", SDL_GetError());
        MIX_Quit();
        return 0;
    }

    eat_sound = MIX_LoadAudio(
        mixer,
        "../assets/audio/yoshi-eat.mp3",
        true
    );

    if (eat_sound == NULL) {
        printf("Failed to load eat sound: %s\n", SDL_GetError());
        MIX_DestroyMixer(mixer);
        mixer = NULL;
        MIX_Quit();
        return 0;
    }

    gameplay_background_music = MIX_LoadAudio(
        mixer,
        "../assets/audio/gameplay_background_music.mp3",
        true
    );

    if (gameplay_background_music == NULL) {
        printf("Failed to load gameplay background music: %s\n", SDL_GetError());
        MIX_DestroyAudio(eat_sound);
        eat_sound = NULL;
        MIX_DestroyMixer(mixer);
        mixer = NULL;
        MIX_Quit();
        return 0;
    }

    gameplay_music_track = MIX_CreateTrack(mixer);

    if (gameplay_music_track == NULL) {
        printf("Failed to create gameplay music track: %s\n", SDL_GetError());
        MIX_DestroyAudio(gameplay_background_music);
        gameplay_background_music = NULL;
        MIX_DestroyAudio(eat_sound);
        eat_sound = NULL;
        MIX_DestroyMixer(mixer);
        mixer = NULL;
        MIX_Quit();
        return 0;
    }

    if (!MIX_SetTrackAudio(gameplay_music_track, gameplay_background_music)) {
        printf("Failed to set gameplay music track audio: %s\n", SDL_GetError());
        MIX_DestroyTrack(gameplay_music_track);
        gameplay_music_track = NULL;
        MIX_DestroyAudio(gameplay_background_music);
        gameplay_background_music = NULL;
        MIX_DestroyAudio(eat_sound);
        eat_sound = NULL;
        MIX_DestroyMixer(mixer);
        mixer = NULL;
        MIX_Quit();
        return 0;
    }

    return 1;
}

void play_eat_sound(void)
{
    MIX_PlayAudio(mixer, eat_sound);
}

void play_gameplay_music(void)
{
    SDL_PropertiesID options = SDL_CreateProperties();

    SDL_SetNumberProperty(
        options,
        MIX_PROP_PLAY_LOOPS_NUMBER,
        -1
    );

    MIX_PlayTrack(gameplay_music_track, options);

    SDL_DestroyProperties(options);
}

void pause_gameplay_music(void)
{
    MIX_PauseTrack(gameplay_music_track);
}

void resume_gameplay_music(void)
{
    MIX_ResumeTrack(gameplay_music_track);
}

void stop_gameplay_music(void)
{
    MIX_StopTrack(gameplay_music_track, 0);
}

void cleanup_audio(void)
{
    if (gameplay_music_track != NULL)
        MIX_DestroyTrack(gameplay_music_track);

    if (gameplay_background_music != NULL)
        MIX_DestroyAudio(gameplay_background_music);

    if (eat_sound != NULL)
        MIX_DestroyAudio(eat_sound);

    if (mixer != NULL)
        MIX_DestroyMixer(mixer);

    MIX_Quit();
}