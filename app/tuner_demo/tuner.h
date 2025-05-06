#ifndef ___YWTUNER__H___
#define ___YWTUNER__H___

typedef enum res_tuner_diseqc_e
{
    TUNER_LNB_DISEQC_A = 0,
    TUNER_LNB_DISEQC_B,
    TUNER_LNB_DISEQC_C,
    TUNER_LNB_DISEQC_D,
    TUNER_LNB_DISEQC_OFF,
}res_tuner_diseqc_T;


int open_frontend(int adapter, int frontend);
BOOL start_frontend(int fd,
    char* lnb, /*UNIVERSAL, C-BAND*/
    fe_sec_tone_mode_t e22K,
    res_tuner_diseqc_T eDiseqc,
    int freq  /*MHZ*/,
    int sym,
    int pol_vert/*horizontal=0,vertical=1*/
    );
/**
    *return 1  lock
    *return 0  unlock
    */
int check_frontend (int fd);
void close_frontend(int fd);


#endif
