
#define PPU_CTRL		*((unsigned char*)0x2000)
#define PPU_MASK		*((unsigned char*)0x2001)
#define PPU_STATUS		*((unsigned char*)0x2002)
#define OAM_ADDRESS		*((unsigned char*)0x2003)
#define SCROLL			*((unsigned char*)0x2005)
#define PPU_ADDRESS		*((unsigned char*)0x2006)
#define PPU_DATA		*((unsigned char*)0x2007)
#define OAM_DMA			*((unsigned char*)0x4014)


#define RIGHT		0x01
#define LEFT		0x02
#define DOWN		0x04
#define UP			0x08
#define START		0x10
#define SELECT		0x20
#define B_BUTTON	0x40
#define A_BUTTON	0x80


#pragma bssseg(push, "ZEROPAGE")
unsigned char NMI_flag;
unsigned char Frame_Count;

unsigned char index;
unsigned char index4;

unsigned char X1;
unsigned char Y1;

unsigned char X2;
unsigned char Y2;

unsigned char XBall;
unsigned char YBall;

unsigned char speedBallX;
unsigned char speedBallY;

unsigned char directionBallY;
unsigned char directionBallX;

unsigned char scoreP1;
unsigned char scoreP2CMP;

unsigned char speedUpCounter;

unsigned char song;
//joypad
unsigned char joypad1;
unsigned char joypad1old;
unsigned char joypad1test; 
unsigned char joypad2; 
unsigned char joypad2old;
unsigned char joypad2test;
//joypad


unsigned char new_background;	
unsigned char textInc;
unsigned char textSwitch;


#pragma bssseg(push, "OAM")
unsigned char SPRITES[256];
// OAM equals ram addresses 200-2ff


// Prototypes
void All_Off (void);
void All_On (void);
void Reset_Scroll (void);
void Draw_Background (const unsigned char []);
void TitleScreen (void);
void SelectMode (void);
void update_PaddleSprites(void);
void update_BallSprites(void);
void StartInit(void);
int collisionCheck(int, int, int, int, int, int, int, int);
void speedUpBall (void);
void movePaddle (void);
void collBKGandSCORE(void);
void collSPRITES(void);
void initGAME(void);

void __fastcall__ Play_Fx(unsigned char effect);
void Reset_Music(void);
void __fastcall__ Play_Music(unsigned char song);
void Music_Update(void);
void Wait_Vblank(void);
void __fastcall__ UnRLE(const unsigned char *data);
void Get_Input(void); //fonction programmé en ASM, pour éviter les Glitch
