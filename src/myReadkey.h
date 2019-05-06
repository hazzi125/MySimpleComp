#ifndef MY_READKEY
#define MY_READKEY

int curs;

enum keys {
    LOAD,
    SAVE,
    RUN,
    STEP,
    RESET,
    F5,
    F6,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    NONE
};

int rk_readkey(enum keys *);
int rk_mytermsave();
int rk_mytermrestore();
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif
