#ifndef SPLASH_H
#define SPLASH_H

typedef enum SplashChoice {
    SPLASH_CHOICE_NEW_GAME,
    SPLASH_CHOICE_CONTINUE
} SplashChoice;

SplashChoice splash_show(void);

#endif
