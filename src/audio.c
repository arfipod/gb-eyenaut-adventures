#include <gb/gb.h>
#include "audio.h"

void audio_init(void)
{
    NR52_REG = AUDENA_ON;
    NR50_REG = AUDVOL_VOL_LEFT(7u) | AUDVOL_VOL_RIGHT(7u);
    NR51_REG = AUDTERM_1_LEFT | AUDTERM_1_RIGHT |
               AUDTERM_2_LEFT | AUDTERM_2_RIGHT |
               AUDTERM_4_LEFT | AUDTERM_4_RIGHT;
}

static void play_square_ch1(uint8_t sweep, uint8_t length, uint8_t envelope,
                            uint8_t freq_lo, uint8_t freq_hi)
{
    NR10_REG = sweep;
    NR11_REG = length;
    NR12_REG = envelope;
    NR13_REG = freq_lo;
    NR14_REG = (uint8_t)(0x80u | freq_hi);
}

static void play_square_ch2(uint8_t length, uint8_t envelope,
                            uint8_t freq_lo, uint8_t freq_hi)
{
    NR21_REG = length;
    NR22_REG = envelope;
    NR23_REG = freq_lo;
    NR24_REG = (uint8_t)(0x80u | freq_hi);
}

static void play_noise(uint8_t length, uint8_t envelope, uint8_t poly)
{
    NR41_REG = length;
    NR42_REG = envelope;
    NR43_REG = poly;
    NR44_REG = 0x80u;
}

void audio_play_jump(void)
{
    play_square_ch1(0x16u, 0x80u, 0xF2u, 0xC0u, 0x06u);
}

void audio_play_mine(void)
{
    play_noise(0x18u, 0xF2u, 0x43u);
}

void audio_play_place(void)
{
    play_noise(0x08u, 0xB1u, 0x22u);
}

void audio_play_craft(void)
{
    play_square_ch2(0x40u, 0xD2u, 0x80u, 0x07u);
}

void audio_play_error(void)
{
    play_square_ch1(0x00u, 0x80u, 0xA2u, 0x80u, 0x04u);
}
