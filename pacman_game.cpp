//Code :   !!!!!
#include<graphics.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

void initialise(void);
char endscreen(void);
void startscreen(void);
void music(int);
void vline(unsigned char ,int,int,int,int);
void hline(unsigned char,int,int,int,int);
void drawbox (int,int,int,int,char);
void gamescreen(void);
void getname(void);
void size (int,int);
void writechar(char,int,int,int);
void monitor(void);
void getkeyhit(void);
int testkeys(void);
void readchar(int,int,unsigned char*);
void bug(int *,int *,int *,unsigned char *);
void movebugright(int *,int *,unsigned char *);
void movebugleft(int *,int *,unsigned char *);
void movebugup(int *,int *,unsigned char *);
void movebugdown(int *,int *,unsigned char *);
void killeater(void);

int maze[25][80],score,row,col,ascii,scan,liveslost,delayfactor;
int gd=DETECT,gm,midx,midy,maxx,maxy;
int bugnumber , r[5],c[5],dir[5];
char name[10];
unsigned  char charbelow[5];
char far *vid_mem= (char far *) 0xB8000000L ;

void main(void)
{

   char ans ;
 clrscr();
/* intialize randonm number generator wih a random value */

randomize ();
startscreen();

while (1)
{

   /* Initialize variables at thee4 start of each game*/
	    /*create opening screen*/
initialise();
getname();
/* Draw ther screen for the game*/
gamescreen();
/* Get the name from the user*/

/* monitor the movement of the bugs and the eater*/


monitor();
/*create ending screen*/
ans=endscreen();

/*check  whether the user wishes to continue playing*/
if(ans== 'N')
 break;
}
}

void getname(void)
{
	clrscr();
	printf("Enter Your Name: ");
	scanf("%s",&name);
}

void startscreen(void)
{
char ch;
int i;

/* Intialize the graphices system*/
initgraph (&gd,&gm,"c:\\turboc3\\bgi");

/* get maximum x and y screen coordinates*/

maxx = getmaxx();
maxy= getmaxy();

/* calculate the center of the screen*/

midx= maxx/2;
midy=maxy/2;

/* draw a double-lined box*/
setcolor(GREEN);
rectangle (0,0,maxx,midy);
setcolor(BLUE);
rectangle (2,2,maxx-2,maxy-2);
setcolor(YELLOW);
/* Draw two vertical lines*/
line (55,1,55,maxy-2);
line (maxx-55,1,maxx-55,maxy-2);


/*display the string  "EATER" ,horizontally */
setcolor(6);
settextjustify (CENTER_TEXT,CENTER_TEXT);
settextstyle (4,HORIZ_DIR,8);
outtextxy (midx,midy,"The PacMan");


/* Place the eater character at random on the start screen*/
int loop;

randomize();
for(loop=0; loop<40;loop++)
{
gotoxy(rand() % 80,rand()%25);
music(1);
printf("%c",2);
delay(100);
}
nosound();

/*play the starting music*/


/* Clear the area enclosed by the double-lined boundry */

setviewport (0,0,maxx,maxy,1);

clearviewport();

/* Draw the screen for display instructions*/
setcolor(BLUE);
rectangle(30,0,maxx-33,maxy);

setcolor(YELLOW);
for (i=15;i<=maxy-15;i+=15)

{
ellipse(15,i,0,360,6,3);
ellipse(maxx-15,i,0,360,6,3);
}
setcolor(5);
settextjustify (CENTER_TEXT,TOP_TEXT);

settextstyle(4,HORIZ_DIR,5);
outtextxy (midx,60,"INSTRUCTION");

/*display instruction*/

settextstyle(2,HORIZ_DIR,5);
outtextxy(midx,110,"You goal:- To eatup all the CRUNCHY MUNCHY      ");
outtextxy(midx,130,"           UNDAY scattered throughtout the BHOOL BHULLYIAN   ");
outtextxy(midx,170,"Your task is not a HALWA! There are 5 Rascals chasing you     ");
outtextxy(midx,210,"The Eater.You have to watch out for the bugs ");
outtextxy(midx,250,"To help you ,we have bestowed the PacMan with 3 Janums");
outtextxy(midx,290,"You can move around the BHOOL BHULLYIAN  using arrow keys       ");
outtextxy(midx,330,"If you are ready to start, press any  key");
setcolor(GREEN);
settextstyle (DEFAULT_FONT,HORIZ_DIR,3);
outtextxy(midx,400,"We wish you Best of luck");


/*Wait for key press*/

while(!kbhit());
/*Flush the keyboard buffer*/

if (getch()==0)
    getch();

/*Draaw the screen for asking user level*/

setviewport (0,0,maxx,maxy,1);
clearviewport();
rectangle(midx-200,midy-60,midx+200,midy+60);

settextstyle (DEFAULT_FONT,HORIZ_DIR,2);
outtextxy(midx,60,"Select Speed");

settextstyle (DEFAULT_FONT,HORIZ_DIR,1);
outtextxy(midx,90,"Slow(S)");
outtextxy(midx,105,"Medium(M)");
outtextxy(midx,120,"Fast(F)");

/*Get user level*/

/*flush the keyboard buffer*/

if ((ch=getch())==0)
getch();

/*Set the value of variable delayfactor according to level selected*/

switch(toupper(ch))
{
case'S':
delayfactor=100;
break;
case'M':
delayfactor=50;
break;
case'F':
delayfactor=20;
break;
default:
delayfactor=100;
}
if(delayfactor==100)
outtextxy(midx,midy,"Slow(S)");
if(delayfactor==50)
outtextxy(midx,midy,"Medium(M)");
if(delayfactor==20)
outtextxy(midx,midy,"Fast(F)");
/*Change over to text mode*/
while(!kbhit());



closegraph();
restorecrtmode();

}

void music(int type)
{
float octave[7]={130.81,146.83,164.81,174.61,196,220,246.94};
int n,i;
switch(type)
{
case 1:
n=random(6);
sound(octave[n]*4);
delay(50);
break;
case 2:
for(i=6;i>=0;i--){
sound(octave[i]);
delay(54);}
nosound();
break;
case 3:
sound(octave[6]*2);
delay(50);
nosound();
}}



char endscreen()
{
char ans;
initgraph(&gd,&gm,"C:\\turboc3\\bgi");
rectangle(0,0,maxx,maxy);
rectangle(2,2,maxx-2,maxy-2);
settextjustify(CENTER_TEXT,CENTER_TEXT);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
if(liveslost==3)
{

outtextxy(midx,midy-30,"Bad Luck!!");
outtextxy(midx,midy, name);
outtextxy(midx,midy+30,"Try Again");
outtextxy(midx,midy+60,"your score : ");
char sc[10];
itoa(score,sc,10);
outtextxy(midx+90,midy+60,sc);
}
else
{
	outtextxy(midx,midy/2-30,name);
	outtextxy(midx,midy/2,"you really are a");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
	outtextxy(midx,midy,"GENIUS!!");
}

settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
outtextxy(midx,midy+midy/2,"Another game(Y?N)...");
while(!(ans=='Y'||ans=='N'))
   {
   fflush(stdin);
   ans=getch();
   ans=toupper(ans);
      }
closegraph();
restorecrtmode();
return(ans);
}

void initialise(void)
{
int j;
/*initialise row and column of EATere*/
row=12;
col=40;

r[0]=3;c[0]=76;
r[1]=3;c[1]=12;
r[2]=12;c[2]=4;
r[3]=14;c[3]=62;
score=0;
liveslost=0;
bugnumber=0;
for(j=0;j<4;j++)
{
dir[j]=0;
charbelow[j]=250;
}
}

void gamescreen(void)
{
int i ;
size(32,0); /*hide cursor*/

/*Fill the screen with the specified color*/

drawbox (0,0,16,79,12);

//draw the horizontal lines of the maze

/*Draw the titbits*/
hline(205,1,0,0,79);
hline(205,1,2,2,20);
hline(205,1,2,22,38);
hline(205,1,2,42,61);
hline(205,1,2,63,77);
hline(205,1,4,2,20);
hline(205,1,4,22,61);
hline(205,1,4,63,77);
hline(205,1,17,0,79);
hline(205,1,15,2,38);
hline(205,1,15,42,77);
hline(205,1,13,0,12);
hline(205,1,13,65,78);
hline(205,1,13,16,61);
hline(205,1,11,2,14);
hline(205,1,11,62,77);
hline(205,1,8,16,61);
hline(205,1,6,2,38);
hline(205,1,6,42,77);
hline(205,1,7,63,77);
hline(205,1,9,63,78);
hline(205,1,7,2,14);
hline(205,1,9,1,14);

/*Draw the columns of the titbits */

vline(186,1,0,0,16);
vline(186,1,79,0,16);
vline(186,1,40,0,2);
vline(186,1,40,4,6);
vline(186,1,14,12,14);
vline(186,1,40,13,15);
vline(186,1,63,12,14);
vline(186,1,40,9,11);
vline(202,1,14,15,15);
vline(202,1,63,15,15);
vline(203,1,40,0,0);
vline(203,1,40,4,4);
vline(203,1,40,8,8);
vline(203,1,40,13,13);
vline(187,1,79,0,0);
vline(201,1,0,0,0);
vline(188,1,79,17,17);
vline(200,1,0,17,17);
vline(204,1,0,9,9);
vline(204,1,0,13,13);
vline(185,1,79,9,9);
vline(185,1,79,13,13);

for(int vlin=16;vlin<=60;vlin+=2)
vline(186,1,vlin,10,11);

gotoxy(51,24);

printf("Press Esc to stop the game");
gotoxy(2,24);
printf("Point: %3d",score);

/*Place the five bugs at strategic Positions*/

writechar(2,3,76,15);
writechar(2,3,12,15);
writechar(2,12,4,15);
writechar(2,14,62,15);

/*Play Music*/

music(2);
}

/*Draw a box filling the required area*/

void drawbox (int sr,int sc,int er,int ec,char attr)
{
int r,c;
char far *v;
for(r=sr;r<=er;r++)
{for(c=sc;c<=ec;c++){
v=vid_mem+(r*160)+(c*2);
*v=250 ;
v++;
*v=attr;}}}


/* Write character and its attributes into memeory */
void writechar(char ch,int r,int c,int attr)
{
char far *v ;
/*calculate address*/

v=vid_mem+(r*160)+c*2;
*v=ch;/*store ascii code*/
v++;
*v=attr;/*store attribute */
}
/*draws horizantal line*/
void hline(unsigned char ch,int attr,int r,int c1,int c2)
{
int c;
for(c=c1;c<=c2;c++)
{
 writechar (ch,r,c,attr);
/*if tibit placed at row r and column c, set corresponding element of
array maez[][]to 1*/
maze[r][c]=1;
}
}
/*draws vertical line */
void vline(unsigned char ch,int attr,int c,int r1,int r2)
{
int r;
for(r=r1;r<=r2;r++)
{
writechar(ch,r,c,attr);
/*if tibit placed at row r and column c, set corresponding element of
array maez[][]to 1*/
maze[r][c]=1;
}
}


void size(int ssl,int esl)
{
union REGS i,o;
i.h.ah=1;
i.h.ch=ssl;
i.h.cl=esl;
i.h.bh=0;
int86(16,&i,&o);
}

void monitor(void)
{
int key ;
unsigned char ch;
while(1)
{
/*place eater at specified row and column */
writechar(1,row,col,14);
/*move bugs around until a key is hit */
getkeyhit();
/*if all 3 lives of the eater are lost */
if(liveslost==3 )
break;
/*place a space in the position currently occuped by the eater*/
writechar(' ',row,col,1);
/*update the position of the eater*/
key =testkeys();


/*if invalid key pressed*/
if(key==0)
{
/*write backeater in its orignal position */
writechar(1,row,col,14);
}
else
{
/*read character at the position whixh the eater is to occupy */
readchar(row,col,&ch);
/*if character read is tibit ,increment score and sound music*/
if(ch==250)
{
score++;
music(3);
}
if(ch==2)
killeater();
/*if character read is bug , kill the eater */
if(liveslost==3)
break;
/*print the latest score*/
gotoxy(2,24);
printf("points : %3d",score);
/*if all the tibits are eaten up*/
if(score>=692)
{
/*erase the last tibit*/
writechar(' ',row,col,1);
break;
}
}
}
}
/*moves the bugs aroubnd until a key is hit */
void getkeyhit()
{
union REGS i,o;
int count;
/*unti a player hits a key, move each bug in turn*/
while(!kbhit())
{
/*introduce delay*/

	       delay(delayfactor);

bug(&r[bugnumber],&c[bugnumber],&dir[bugnumber],&charbelow[bugnumber]);
	/*if all 3 lives of the eater  are lost*/
	if (liveslost==3)
	   return;
	   /*goto next bug*/
	   bugnumber++;
/*start with the first bug if allfive bugs have been moved*/
if(bugnumber==4)
bugnumber=0;
}
/*issue interrupt to read the ascii code and scan code od the kay
pressed*/
i.h.ah=0;/*store service no*/
int86(22,&i,&o);/*issue interrupt*/
ascii=o.h.al;
scan=o.h.ah;
}
/*reports which key has ben hit*/
int testkeys(void)
{
 switch(scan)
 {
 case 72:/*up arrow*/

 /*if path is not present in the specified direction */
if(maze[row-1][col]==1)
return(0);
/*update row of eater*/
row--;
break;

case 80:/*down arrow*/

if(maze[row+1][col]==1)
return(0);
row++;
break;

case 77:/*right arrow*/

if(maze[row][col+1]==1)
return(0);
col++;
break;

case 75:/*left arrow*/

if(maze[row][col-1]==1)
return(0);
col--;
break;

case 1:/*esc key*/
 exit(0);/*terminate the programm*/
default:
return(0);
}
}
/*reads the character presennt at the row r and volumn c into ch*/
void readchar(int r,int c,unsigned char *ch)
{
char far *v;
/*calculate addresss*/
v=vid_mem+(r*160) +c*2;
*ch=*v;
}
/*moves the specefy bug in the appropriate direction*/
void bug(int *r,int *c,int* dir,unsigned char *ch)
{

int trials=1,flag=0;
char temp;
/*select a valid direction which takes the bug closer to eater
in  each if statement the 1st condition checks whether the movement in
 that directionwould move the bug closer to the eater , whereas the 2nd
 condition checks if the maze permits a movement in that direction*/
if(abs(*r-1-row)<abs(*r-row)&&maze[*r-1][*c]!=1)
*dir=UP;
else
if(abs(*r+1-row)<abs(*r-row)&&maze[*r+1][*c]!=1)
*dir=DOWN;
else
if(abs(*c+1-col)<abs(*c-col)&&maze[*r][*c+1]!=1)
*dir=RIGHT;
else
if(abs(*c-1-col)<abs(*c-col)&&maze[*r][*c-1]!=1)
*dir=LEFT;

/*check whether the direction chosen contains another bug , if so find 
an
alternate direction*/
while(1)
{
switch(*dir)
   {
   case RIGHT:
   /*if there is a path to right of bug*/
   if(maze[*r][*c+1]!=1)
      {
       /* read the character to the right of the bug*/
      readchar(*r,*c+1,&temp);
      if(temp==2)
      {
      /*if the character is again a bug find alternate direction*/
       if(maze[*r][*c-1]!=1)
       *dir=LEFT;

       else
       {
       /*if patch exists to the top of the bug*/
	 if (maze[*r-1][*c]!=1)
	 *dir=UP;

	 else
	 {
	 /*if path exist below the bug*/
	 if(maze[*r+1][*c]!=1)
	 *dir=DOWN;
	 }
      }
}

   else

   {
     /*if there is no bug to the right of the bug being
     considered , move the bug right*/
     movebugright(r,c,ch);
     flag=1;
     }
}

	else
  {
   /*since there is no pat in the RIGHT directio ,
   try another path*/

    *dir=random(4);
    }

   break;
   case LEFT:

   /*if there is a path to the LEFT of the bug*/
   if(maze[*r][*c-1]!=1)

   {
   /*read the character to the ;eft of the bug*/
readchar(*r,*c-1,&temp);
if(temp==2)
{
	if(maze[*r][*c+1]!=1)
		*dir=RIGHT;
	else
	{
	if(maze[*r-1][*c]!=1)
	*dir=UP;
	else
	{
	if(maze[*r+1][*c]!=1)
		*dir=DOWN;
	}
    }
}
else
   {
movebugleft(r,c,ch);
flag=1;
}
}
else
{
*dir=random(4);
}
break;
case UP:
if(maze[*r-1][*c]!=1)
{
readchar(*r-1,*c,&temp);
if(temp==2)
{
if(maze[*r][*c+1]!=1)
*dir=RIGHT;
else
{
if(maze[*r][*c-1]!=1)
*dir=LEFT;
else
{
if(maze[*r+1][*c]!=1)
*dir=DOWN;
}
}
}
else
{
movebugup(r,c,ch);
flag=1;
}
}
else
*dir=random(4);
break;
case DOWN:
if(maze[*r+1][*c]!=1)
{
readchar(*r+1,*c,&temp);
if (temp==2)
{
if(maze[*r][*c+1]!=1)
*dir=RIGHT;
else
{
if(maze[*r][*c-1]!=1)
*dir=LEFT;
else
{
if(maze[*r-1][*c]!=1)
*dir=UP;
}
}
}
else
{
movebugdown(r,c,ch);
flag=1;
}
}
else
*dir=random(4);
break;
}
if(flag==1)
break;
trials++;
if(trials>15)
break;
}
if(*r==row&&*c==col)
killeater();
}

void movebugleft( int *row,int * colm,unsigned char  *ch)

{
if( *ch==0)
*ch=0;
writechar(*ch,*row,*colm,12);

*colm=*colm-1;
readchar(*row,*colm,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*colm,15);
}

void movebugright(int *row,int *colm,unsigned  char *ch)
{
if( *ch==0)
*ch=0;
writechar(*ch,*row,*colm,12);
*colm=*colm+1;
readchar(*row,*colm,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*colm,15);
}
void movebugup(int *row,int *col,unsigned char *ch)
{
if( *ch==0)
*ch=0;

writechar(*ch,*row,*col,12);
*row=*row-1;
readchar(*row,*col,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*col,15);
}
void movebugdown(int *row,int *col,unsigned char *ch)
{
if( *ch==0)
*ch=0;

writechar(*ch,*row,*col,12);
*row=*row+1;
readchar(*row,*col,ch);
if(*ch==1)
*ch=' ';
writechar(2,*row,*col,15);
}
void killeater(void){
int r,c;
r=row;
c=col;
writechar(1,row,col,112);
writechar(1,23,15+liveslost*3,14);
music(2);
liveslost++;
if(liveslost==3)
return;
row=12;
col=40;
writechar(1,row,col,14);

}
