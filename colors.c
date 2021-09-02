
//Function to change colour and underline text
void colour(){
    red();
    green();
    yellow();
    blue();
    magenta();
    cyan();
    ured();
    ugreen();
    uyellow();
    ublue();
    umagenta();
    ucyan();
    reset();
    system("cls");
}

void red(){ printf("\033[1;31m");}

void green(){ printf("\033[1;32m");}

void yellow(){ printf("\033[1;33m");}

void blue(){ printf("\033[1;34m");}

void magenta(){ printf("\033[1;35m");}

void cyan(){ printf("\033[1;36m");}

void ured(){ printf("\033[4;31m");}

void ugreen(){ printf("\033[4;32m");}

void uyellow(){ printf("\033[4;33m");}

void ublue(){ printf("\033[4;34m");}

void umagenta(){ printf("\033[4;35m");}

void ucyan(){ printf("\033[4;36m");}

void reset(){ printf("\033[0m");}
