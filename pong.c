
#include "DEFINE.c"


#include "G_for_Pong/MapTitleScreen.c" 
#include "G_for_Pong/PaletteTitleScreen.c" 


const unsigned char DATE[]={
    "2017"};

const unsigned char NAME[]={
    "MAGNIN"};

const unsigned char SELECT1P[]={
    "1 Player"};

const unsigned char SELECT2P[]={
    "2 Player"};

const unsigned char SCOREP1[]={
    "Player 1 :"};

const unsigned char SCOREP2[]={
    "Player 2 :"};

const unsigned char SCORECMP[]={
    "Computer :"};

const unsigned char SCORESTRING[]={
    "SCORE"};

const unsigned char WINSP1[]={
    "Player 1 wins"};

const unsigned char WINSP2[]={
    "Player 2 wins"};

const unsigned char WINSCMP[]={
    "Computer wins"};


const unsigned char MetaSprite1_Y[] = {0, 8, 16};
const unsigned char MetaSprite1_X[] = {0, 0, 0};
const unsigned char MetaSprite1_Tile[] = {0x02, 0x02, 0x02};
const unsigned char MetaSprite1_Attrib[] = {2, 2, 2};


const unsigned char MetaSprite2_Y[] = {0, 8, 16};
const unsigned char MetaSprite2_X[] = {0, 0, 0};
const unsigned char MetaSprite2_Tile[] = {0x11, 0x11, 0x11};
const unsigned char MetaSprite2_Attrib[] = {2, 2, 2};


const unsigned char MetaSprite3_Y[] = {0};
const unsigned char MetaSprite3_X[] = {0};
const unsigned char MetaSprite3_Tile[] = {0x00};
const unsigned char MetaSprite3_Attrib[] = {0};





void main (void) {

    initGAME();
	Reset_Music();

    while (1){ 	// boucle
        while (NMI_flag == 0); // Attendre interuption NMI

        if(new_background == 0){

            Draw_Background(MapTitleScreen);
		Play_Fx(2);
            new_background = 1;
        }

        if(new_background == 1){
            TitleScreen();

            SelectMode();

            StartInit();
		
	    
        }

        if(new_background == 2){
		
		

            speedUpBall();

            movePaddle();

            collBKGandSCORE();
            if(new_background != 3){
                collSPRITES();

                XBall = XBall + speedBallX;
                YBall = YBall + speedBallY;

                update_PaddleSprites();
                update_BallSprites();
            }

        }

        if(new_background == 3){
            if(scoreP1 == 10){
                PPU_ADDRESS = 0x21;
                PPU_ADDRESS = 0xca;
                for(index = 0; index < sizeof(WINSP1) - 1; ++index){
                    PPU_DATA = WINSP1[index];
                }

                scoreP1 = 11;
            }
            else if(scoreP2CMP == 10 && textSwitch == 5){
                PPU_ADDRESS = 0x21;
                PPU_ADDRESS = 0xca;
                for(index = 0; index < sizeof(WINSCMP) - 1; ++index){
                    PPU_DATA = WINSCMP[index];
                }

                scoreP2CMP = 11;
            }
            else if(scoreP2CMP == 10 && textSwitch == 6){
                PPU_ADDRESS = 0x21;
                PPU_ADDRESS = 0xca;
                for(index = 0; index < sizeof(WINSP2) - 1; ++index){
                    PPU_DATA = WINSP2[index];
                }

                scoreP2CMP = 11;
            }

            Reset_Scroll();
            new_background = 4;
            Frame_Count = 0;


        }

        if(new_background == 4 && Frame_Count == 240){
            initGAME();
            Draw_Background(MapTitleScreen);
            TitleScreen();
            SelectMode();
            StartInit();
            new_background == 2;
            Frame_Count = 0;
        }


	Music_Update();
        NMI_flag = 0;

    }
}

// NMI_flag et Frame_Count s'incrémente à chaque VBLANK, instruction écrite en Assembleur


void All_Off (void) {
    PPU_CTRL = 0;
    PPU_MASK = 0; 
}

void TitleScreen (void) {
    if(Frame_Count == 10){
        if(textSwitch == 0 && textInc < sizeof(DATE) - 1){
            PPU_ADDRESS = 0x23;
            PPU_ADDRESS = 0x82 + textInc;
            PPU_DATA = DATE[textInc];
            ++textInc;
        }
        else if(textSwitch == 0 && textInc >= sizeof(DATE) - 1){
            textInc = 0;
            textSwitch = 1;

        }

        if(textSwitch == 1 && textInc < sizeof(NAME) - 1){
            PPU_ADDRESS = 0x23;
            PPU_ADDRESS = 0x98 + textInc;
            PPU_DATA = NAME[textInc];
            ++textInc;
        }
        else if(textSwitch == 1 && textInc >= sizeof(NAME) - 1){
            textInc = 0;
            textSwitch = 2;

        }

        if(textSwitch == 2 && textInc < sizeof(SELECT1P) - 1){
            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xad + textInc;
            PPU_DATA = SELECT1P[textInc];
            ++textInc;
        }
        else if(textSwitch == 2 && textInc >= sizeof(SELECT1P) - 1){
            textInc = 0;
            textSwitch = 3;

        }

        if(textSwitch == 3 && textInc < sizeof(SELECT2P) - 1){
            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xed + textInc;
            PPU_DATA = SELECT2P[textInc];
            ++textInc;
        }
        else if(textSwitch == 3 && textInc >= sizeof(SELECT2P) - 1){
            textInc = 0;
            textSwitch = 4;

        }

        if(textSwitch == 4){
            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xab;
            PPU_DATA = 0xFC; //le selecteur et a l'emplacement 0xFC dans le CHR
            textSwitch = 5;
        }
        Reset_Scroll();
        Frame_Count = 0;
    }

}

void SelectMode  (void){

    Get_Input();
    if(((joypad1 & SELECT) != 0) && ((joypad1old & SELECT) == 0)){

        if(textSwitch == 5){
            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xeb;
            PPU_DATA = 0xFC; 


            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xab;
            PPU_DATA = 0x00; 

        }
        else if(textSwitch == 6){
            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xab;
            PPU_DATA = 0xFC; 


            PPU_ADDRESS = 0x22;
            PPU_ADDRESS = 0xeb;
            PPU_DATA = 0x00; 


        }
        textSwitch++;
        if(textSwitch == 7){
            textSwitch = 5;
        }

        Reset_Scroll();

    }

}

void All_On (void) {
    PPU_CTRL = 0x90;
    PPU_MASK = 0x1e; 
}


void Reset_Scroll (void) {
    PPU_ADDRESS = 0;
    PPU_ADDRESS = 0;
    SCROLL = 0;
    SCROLL = 0;
}

void Draw_Background(const unsigned char Map[]) {
    All_Off();
    PPU_ADDRESS = 0x20;
    PPU_ADDRESS = 0x00;

    UnRLE(Map);	// on décompresse les données du BKG compréssé en RLE

    Wait_Vblank();		// on allume pas l'ecran avant le VBLANK
    All_On();
    Reset_Scroll();
}

void update_PaddleSprites (void) {
    index4 = 0;
    for (index = 0; index < 3; ++index ){
        //SPRITE 1 
        SPRITES[index4] = MetaSprite1_Y[index] + Y1;
        ++index4;
        SPRITES[index4] = MetaSprite1_Tile[index]; 
        ++index4;
        SPRITES[index4] = MetaSprite1_Attrib[index];
        ++index4;
        SPRITES[index4] = MetaSprite1_X[index] + X1;
        ++index4;
        //SPRITE 2
        SPRITES[index4] = MetaSprite2_Y[index] + Y2;
        ++index4;
        SPRITES[index4] = MetaSprite2_Tile[index]; 
        ++index4;
        SPRITES[index4] = MetaSprite2_Attrib[index];
        ++index4;
        SPRITES[index4] = MetaSprite2_X[index] + X2;
        ++index4;
    }
}

void update_BallSprites (void) {
    index4 = 24;
    index = 0;
    //SPRITE 3
    SPRITES[index4] = MetaSprite3_Y[index] + YBall;
    ++index4;
    SPRITES[index4] = MetaSprite3_Tile[index]; 
    ++index4;
    SPRITES[index4] = MetaSprite3_Attrib[index];
    ++index4;
    SPRITES[index4] = MetaSprite3_X[index] + XBall;
    ++index4;

}


void StartInit (void){

    if(((joypad1 & START) != 0) && ((joypad1old & START) == 0) && textSwitch >= 5 && new_background == 1){
        //Attr
	    
	Play_Fx(0);
        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xdb;
        PPU_DATA = 0x00;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xdc;
        PPU_DATA = 0x00;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xe3;
        PPU_DATA = 0x00;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xe4;
        PPU_DATA = 0x00;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xea;
        PPU_DATA = 0x00;
        //Fin Attr



        Draw_Background(TablePong);

        PPU_ADDRESS = 0x20;
        PPU_ADDRESS = 0x6d;
        for(index = 0; index < sizeof(SCORESTRING) - 1; ++index){
            PPU_DATA = SCORESTRING[index];
        }

        PPU_ADDRESS = 0x20;
        PPU_ADDRESS = 0xa2;
        for(index = 0; index < sizeof(SCOREP1) - 1; ++index){
            PPU_DATA = SCOREP1[index];
        }

        PPU_ADDRESS = 0x20;
        PPU_ADDRESS = 0xa2 + 0x0b;
        PPU_DATA = 0x30; //0 dans le CHR


        if(textSwitch == 6){

            PPU_ADDRESS = 0x20;
            PPU_ADDRESS = 0xb2;
            for(index = 0; index < sizeof(SCOREP2) - 1; ++index){
                PPU_DATA = SCOREP2[index];
            }

        }


        if(textSwitch == 5){

            PPU_ADDRESS = 0x20;
            PPU_ADDRESS = 0xb2;
            for(index = 0; index < sizeof(SCORECMP) - 1; ++index){
                PPU_DATA = SCORECMP[index];
            }

        }

        PPU_ADDRESS = 0x20;
        PPU_ADDRESS = 0xb2 + 0x0b;
        PPU_DATA = 0x30;





        //Attr

        for(index = 0xc8; index <= 0xcf; index++){
            PPU_ADDRESS = 0x23;
            PPU_ADDRESS = index;
            PPU_DATA = 0xf0;
        }		

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xd0;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xd8;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xe0;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xe8;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xd7;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xdf;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xe7;
        PPU_DATA = 0xff;

        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = 0xef;
        PPU_DATA = 0xff;

        for(index = 0xf0; index <= 0xf7; index++){
            PPU_ADDRESS = 0x23;
            PPU_ADDRESS = index;
            PPU_DATA = 0xff;
        }	

        //Attr


        update_PaddleSprites();
        update_BallSprites();
        Reset_Scroll();
	Play_Music(0);
        new_background = 2;

    }

}

int collisionCheck(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {

    if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {

        return 1;

    } else {

        return 0;

    }

}

void speedUpBall (void){
    
    if(speedBallY == 0){
	    
	    if(directionBallY == 0){
	    speedBallY = -1;
	    }
	    else if(directionBallY == 1){
		speedBallY = 3;    
	    }
    }
	
    if(speedUpCounter == 6){

        if(directionBallY == 0){
            ++speedBallY;
        }
        else{
            --speedBallY;
        }

        if(directionBallX == 0){
            ++speedBallX;
        }
        else{
            --speedBallX;
        }

        speedUpCounter = 0;
    }
}

void movePaddle (void){
    Get_Input();
    if(((joypad1 & UP) != 0) && (Y1 > 0x3e + 0x03)){
        Y1 = Y1 - 3;
    }
    else if(((joypad1 & DOWN) != 0) && (Y1 < 0xc6 - 0x11)){
        Y1 = Y1 + 3;
    }

    if(textSwitch == 6){
        Get_Input();
        if(((joypad2 & UP) != 0) && (Y2 > 0x3e + 0x03)){
            Y2 = Y2 - 3;
        }
        else if(((joypad2 & DOWN) != 0) && (Y2 < 0xc6 - 0x11)){
            Y2 = Y2 + 3;
        }
    }
    else if(textSwitch == 5){
        if ((YBall<Y2 + 12) && (Y2 > 0x3e + 0x03)){
		
		if(scoreP1 < 5){
            Y2 = Y2 - 2;
		}
		else{
			Y2 = Y2 - 3;
		}

        }
        if ((YBall>Y2 + 12) && (Y2 < 0xc6 - 0x11)){
            if(scoreP1 < 5){
            Y2 = Y2 + 2;
		}
		else{
			Y2 = Y2 + 3;
		}
        }
    }
}


void collBKGandSCORE(void){
    if(YBall < 0x3e){
	    YBall = 0x3e + 1; 
        speedBallY = speedBallY * -1;
        if(directionBallY == 1){
            directionBallY = 0;
        }
        else{
            ++directionBallY;
        }
    }

    if(YBall > 0xc6){
	YBall = 0xc6 - 1;
        speedBallY = speedBallY * -1;
        if(directionBallY == 1){
            directionBallY = 0;
        }
        else{
            ++directionBallY;
        }
    }

    if(XBall < 0x0e){
	Play_Fx(1);
        ++scoreP2CMP;
        XBall = 0x7c;
        YBall = 0x88;

        speedBallX = 1;
        speedBallY = 1;

        directionBallY = 0;
        directionBallX = 0;
        speedUpCounter = 0;

        switch(scoreP2CMP){

            case 1:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x31;
                Reset_Scroll();
                break;
            case 2:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x32;
                Reset_Scroll();
                break;
            case 3:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x33;
                Reset_Scroll();
                break;
            case 4:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x34;
                Reset_Scroll();
                break;
            case 5:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x35;
                Reset_Scroll();
                break;
            case 6:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x36;
                Reset_Scroll();
                break;
            case 7:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x37;
                Reset_Scroll();
                break;
            case 8:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x38;
                Reset_Scroll();
                break;
            case 9:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xbd;
                PPU_DATA = 0x39;
                Reset_Scroll();
                break;
            case 10:


                SPRITES[1] = 0xff;
                SPRITES[5] = 0xff;
                SPRITES[9] = 0xff;
                SPRITES[13] = 0xff;
                SPRITES[17] = 0xff;
                SPRITES[21] = 0xff;
                SPRITES[25] = 0xff;
		Reset_Music();
		Play_Fx(4);
                Draw_Background(BlackScreen);

                new_background = 3;


                break;

        }

    }

    if(XBall > 0xeb){
	Play_Fx(1);
        ++scoreP1;
        XBall = 0x7c;
        YBall = 0x88;

        speedBallX = 1;
        speedBallY = 1;

        directionBallY = 0;
        directionBallX = 0;
        speedUpCounter = 0;

        All_Off();
        switch(scoreP1){

            case 1:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x31;

                break;
            case 2:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x32;

                break;
            case 3:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x33;

                break;
            case 4:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x34;

                break;
            case 5:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x35;

                break;
            case 6:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x36;

                break;
            case 7:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x37;

                break;
            case 8:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x38;

                break;
            case 9:
                PPU_ADDRESS = 0x20;
                PPU_ADDRESS = 0xad;
                PPU_DATA = 0x39;

                break;
            case 10:

                SPRITES[1] = 0xff;
                SPRITES[5] = 0xff;
                SPRITES[9] = 0xff;
                SPRITES[13] = 0xff;
                SPRITES[17] = 0xff;
                SPRITES[21] = 0xff;
                SPRITES[25] = 0xff;
		Reset_Music();
		Play_Fx(4);
                Draw_Background(BlackScreen);

                new_background = 3;

                break;

        }
        Reset_Scroll();
        All_On();
    }

}


void collSPRITES(void){
    if(collisionCheck(XBall-2, YBall, 0x08, 0x08, X1, Y1, 0x08, 0x08)){
	Play_Fx(3);
        if(YBall <= Y1 - (8/2)){
            YBall = Y1 - 9;
            speedBallY = speedBallY * -1;
        }



        if(directionBallY == 0 ){
            speedBallX = speedBallX * -1;
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        else{
            speedBallY = speedBallY * -1;
            speedBallX = speedBallX * -1;
            if(directionBallY == 1){
                directionBallY = 0;
            }
            else{
                ++directionBallY;
            }
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }

        ++speedUpCounter;
    }
    else if(collisionCheck(XBall-2, YBall, 0x08, 0x08, X1, Y1+0x08, 0x08, 0x08)){
	    Play_Fx(3);
        speedBallX = speedBallX * -1;
        if(directionBallX == 1){
            directionBallX = 0;
        }
        else{
            ++directionBallX;
        }
        ++speedUpCounter;
    }
    else if(collisionCheck(XBall-2, YBall, 0x08, 0x08, X1, Y1+0x0f, 0x08, 0x08)){
	    Play_Fx(3);

        if(YBall >= Y1+ 0x0f + (8/2)){
            YBall = Y1 + 0x0f + 9;
            speedBallY = speedBallY * -1;
        }

        if(directionBallY == 1){
            speedBallX = speedBallX * -1;
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        else{
            speedBallY = speedBallY * -1;
            speedBallX = speedBallX * -1;
            if(directionBallY == 1){
                directionBallY = 0;
            }
            else{
                ++directionBallY;
            }
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        ++speedUpCounter;
    }

    else if(collisionCheck(XBall-2, YBall, 0x08, 0x08, X2, Y2, 0x08, 0x08)){
	    Play_Fx(3);
        if(YBall <= Y2 - (8/2)){
            YBall = Y2 - 9;
            speedBallY = speedBallY * -1;
        }

        if(directionBallY == 0){
            speedBallX = speedBallX * -1;
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        else{
            speedBallY = speedBallY * -1;
            speedBallX = speedBallX * -1;
            if(directionBallY == 1){
                directionBallY = 0;
            }
            else{
                ++directionBallY;
            }
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        ++speedUpCounter;
    }
    else if(collisionCheck(XBall-2, YBall, 0x08, 0x08, X2, Y2+0x08, 0x08, 0x08)){
	    Play_Fx(3);
        speedBallX = speedBallX * -1;
        if(directionBallX == 1){
            directionBallX = 0;
        }
        else{
            ++directionBallX;
        }
        ++speedUpCounter;
    }
    else if(collisionCheck(XBall-2, YBall, 0x08, 0x08, X2, Y2+0x0f, 0x08, 0x08)){
	    Play_Fx(3);
        if(YBall >= Y2+ 0x0f + (8/2)){
            YBall = Y2 + 0x0f + 9;
            speedBallY = speedBallY * -1;
        }

        if(directionBallY == 1){
            speedBallX = speedBallX * -1;
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        else{
            speedBallY = speedBallY * -1;
            speedBallX = speedBallX * -1;
            if(directionBallY == 1){
                directionBallY = 0;
            }
            else{
                ++directionBallY;
            }
            if(directionBallX == 1){
                directionBallX = 0;
            }
            else{
                ++directionBallX;
            }
        }
        ++speedUpCounter;
    }

}

void initGAME(void){
    All_Off();

    X1 = 0x18;
    Y1 = 0x80;

    X2 =  0xe2;
    Y2 = 0x80;

    XBall = 0x7c;
    YBall = 0x88;

    speedBallX = 1;
    speedBallY = 1;

    directionBallY = 0;
    directionBallX = 0;
    speedUpCounter = 0;

    textSwitch = 0;
    textInc = 0;

    scoreP1 = 0;
    scoreP2CMP = 0;
    
    song = 0;

    new_background = 0;
    PPU_ADDRESS = 0x3f;
    PPU_ADDRESS = 0x00;
    for( index = 0; index < sizeof(PaletteTitleScreen); ++index ){
        PPU_DATA = PaletteTitleScreen[index];
    }

    //Attr RESET
    for(index = 0xc0; index <= 0xfe; index++){
        PPU_ADDRESS = 0x23;
        PPU_ADDRESS = index;
        PPU_DATA = 0x00;
    }	

    //Attr RESET

    //Attr
    PPU_ADDRESS = 0x23;
    PPU_ADDRESS = 0xdb;
    PPU_DATA = 0xA0;

    PPU_ADDRESS = 0x23;
    PPU_ADDRESS = 0xdc;
    PPU_DATA = 0xA0;

    PPU_ADDRESS = 0x23;
    PPU_ADDRESS = 0xe3;
    PPU_DATA = 0x0A;

    PPU_ADDRESS = 0x23;
    PPU_ADDRESS = 0xe4;
    PPU_DATA = 0x0A;

    PPU_ADDRESS = 0x23;
    PPU_ADDRESS = 0xea;
    PPU_DATA = 0xAA;
    //Fin Attr
	
     
    Reset_Scroll();
    All_On();
}
