#include "myReadkey.h"

int rk_readkey(enum keys *key) {
    struct termios def_opt;
    char buff[16];

    if(tcgetattr(0, &def_opt) == -1)
        return -1;

    if(rk_mytermregime(0, 1, 1, 0, 0) == -1)
        return -1;

    read(0, buff, 15);
    
    if(buff[0] == 'q')
        *key = QUIT;

    else if(buff[0] == 'l')
        *key = LOAD;

    else if(buff[0] == 's')
        *key = SAVE;

    else if(buff[0] == 'r')
        *key = RUN;

    else if(buff[0] == 'i')
        *key = RESET;

    else if(buff[0] == 't')
        *key = STEP;

    else if(buff[0] == 'e')
        *key = ENTER;

    else if(buff[0] == 'g')
        *key = TRANS;

    else if((buff[0] == '\033') && (buff[1] == '[') && (buff[2] == '1') && (buff[3] == '5'))
        *key = F5;

    else if((buff[0] == '\033') && (buff[1] == '[') && (buff[2] == '1') && (buff[3] == '7'))
        *key = F6;  

    else if((buff[0] == '\033') && (buff[1] == '[') && (buff[2] == 'A'))
        *key = UP;

    else if((buff[0] == '\033') && (buff[1] == '[') && (buff[2] == 'B'))
        *key = DOWN;

    else if((buff[0] == '\033') && (buff[1] == '[') && (buff[2] == 'D'))
        *key = LEFT;

    else if((buff[0] == '\033') && (buff[1] == '[') && (buff[2] == 'C'))
        *key = RIGHT;

    //else
        //*key = NONE;

    if(tcsetattr(0, TCSANOW, &def_opt) != 0)
        return -1;

    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {
    struct termios opt;
    if(tcgetattr(0, &opt) == -1)
        return -1;

    if(regime == 1)
        opt.c_lflag |= ICANON;
    
    else {
        opt.c_lflag &= ~ICANON;
        opt.c_cc[VTIME] = vtime;
        opt.c_cc[VMIN] = vmin;
        
        if(echo)
            opt.c_lflag |= ECHO;

        else
            opt.c_lflag &= ~ECHO;

        if(sigint)
            opt.c_lflag |= ISIG;

        else
            opt.c_lflag &= ~ISIG;
    }

    if(tcsetattr(0, TCSANOW, &opt) == -1)
        return -1;

    return 0; 
}

int rk_mytermsave() {
    struct termios term;
    FILE *t;
    if(tcgetattr(0, &term) == -1)
        return -1;

    if((t = fopen("term", "wb")) == NULL)
        return -1;

    fwrite(&term, sizeof(term), 1, t);
    fclose(t);
    return 0;
}

int rk_mytermrestore() {
    struct termios term;
    FILE *t;
    if(tcgetattr(0, &term) == -1)
        return -1;

    if((t = fopen("term", "wb")) == NULL)
        return -1;

    if(fread(&term, sizeof(term), 1, t) > 0) {
        if(tcsetattr(0, TCSAFLUSH, &term) == -1)
            return -1;

        else
            fclose(t);
    }
    return 0;
}
