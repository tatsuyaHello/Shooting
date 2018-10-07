typedef volatile unsigned short hword;
#define VRAM 0x06000000
#define BGR(r, g, b) ((b << 10) + (g << 5) + r)


hword blue = BGR(0, 0, 0x1F);
hword red = BGR(0x1F, 0, 0);
hword black = BGR(0, 0, 0);
hword white = BGR(0x1F,0x1F,0x1F);
hword green = BGR(0,0x1F,0);
hword yellow = BGR(0x1F,0x1F,0);
hword x = 120;
hword y = 159;
hword yy = 2;
hword n = 0;
hword count = 0;	
int random[10];


void draw_point(int x,int y, hword color);
void draw_point2(int x,int y, hword color);
void draw_back(hword color);
void opening(void);
void cpu(void);
void play(void);
void draw_char(int moji[5][5], int x, int y, int d, int r);
void draw_circ(int x, int y, int r, hword color);
int judge(void);
int judge_start(void);
int mine(void);
void key(void);
void bullet(void);
void lose(void);
void win(void);

int main(void){
	n=0;
	*(hword*)0x04000000 = 0x0F03;

	draw_back(black);
	opening();
	play();
	

}

void opening(void){
	static int h[5][5]  ={{1,0,0,0,1},
			       {1,0,0,0,1},
	                            {1,1,1,1,1},
			       {1,0,0,0,1},
			       {1,0,0,0,1}};

	static int o[5][5]  ={{0,1,1,1,0},
			       {1,0,0,0,1},
	                            {1,0,0,0,1},
			       {1,0,0,0,1},
			       {0,1,1,1,0}};

	static int i[5][5]  ={{0,0,1,0,0},
			       {0,0,1,0,0},
	                            {0,0,1,0,0},
			       {0,0,1,0,0},
			       {0,0,1,0,0}};
	
	static int n[5][5]  ={{1,0,0,0,1},
			       {1,1,0,0,1},
	                            {1,0,1,0,1},
			       {1,0,0,1,1},
			       {1,0,0,0,1}};

	static int g[5][5]  ={{0,1,1,1,0},
			       {1,0,0,0,0},
	                            {1,0,0,1,1},
			       {1,0,0,0,1},
			       {0,1,1,1,0}};

	static int a[5][5]  ={{0,0,1,0,0},
			       {0,1,0,1,0},
	                            {1,0,0,0,1},
			       {1,1,1,1,1},
			       {1,0,0,0,1}};

	static int m[5][5]  ={{1,0,0,0,1},
			       {1,1,0,1,1},
			       {1,0,1,0,1},
			       {1,0,0,0,1},
                     	                  {1,0,0,0,1}};

	static int e[5][5]  ={{1,1,1,1,0},
			       {1,0,0,0,0},
		          	       {1,1,1,1,0},
			       {1,0,0,0,0},
			       {1,1,1,1,0}};

	static int s[5][5]  ={{0,1,1,1,1},
			       {1,0,0,0,0},
			       {0,1,1,1,0},
			       {0,0,0,0,1},
			       {1,1,1,1,0}};

	static int t[5][5]  ={{1,1,1,1,1},
			       {0,0,1,0,0},
			       {0,0,1,0,0},
			       {0,0,1,0,0},
                                       {0,0,1,0,0}};

	static int r[5][5]  ={{1,1,1,1,0},
			       {1,0,0,0,1},
			       {1,1,1,1,0},
		 	       {1,0,0,1,0},
                                       {1,0,0,0,1}};
	
		
	draw_char(s, 25, 30, 3, 3);
	draw_char(h, 50, 30, 3, 3);
	draw_char(o, 75, 30, 3, 3);
	draw_char(o, 100, 30, 3, 3);
	draw_char(t, 125, 30, 3, 3);
	draw_char(i, 150, 30, 3, 3);
	draw_char(n, 175, 30, 3, 3);
	draw_char(g, 200, 30, 3, 3);

	draw_char(g, 40, 70, 6, 5);
	draw_char(a, 85, 70, 6, 5);
	draw_char(m, 130, 70, 6, 5);
	draw_char(e, 175, 70, 6, 5);
	
	draw_char(s, 80, 120, 2, 2);
	draw_char(t, 95, 120, 2, 2);
	draw_char(a, 110, 120, 2, 2);
	draw_char(r, 125, 120, 2, 2);
	draw_char(t, 140, 120, 2, 2);

	
	int start;
	start = judge_start();
	if(start==1){
		return;
	}
}

void draw_char(int moji[5][5], int x, int y, int d, int r){
	int i;
	int j;

	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			if(moji[i][j]==1){
				draw_circ(x+j*d, y+i*d, r, white);
			}
		}
	}
}

void draw_circ(int x, int y, int r, hword color){
	int i;
	int j;

	for(i=x-r; i<x+r; i++){
		for(j=y-r; j<y+r; j++){
			if(((i-x)*(i-x) + (j-y)*(j-y)) < (r*r)){
				draw_point2(i, j, color);
			}
		}

	}
}

void draw_point(int x,int y, hword color){
	hword *ptr;
	ptr = (hword*)VRAM;
	ptr = ptr + x + y*240;
	*ptr = color;
	ptr += 2;
	*ptr = color;
	ptr += 2;
	*ptr = color;
	ptr += 2;
	*ptr = color;
}

void draw_point2(int x,int y, hword color){
	hword *ptr;
	ptr = (hword*)VRAM;
	ptr = ptr + x + y*240;
	*ptr = color;
}


void draw_back(hword color){
	int i ;

	for(i=0; i<38400; i++){
		draw_point(i, 0, color);
	}
}

int judge_start(void){
	hword *ptr;
	ptr = (hword*) 0x04000130;

	while(1){
		if(0x0008 != ((*ptr)&0x0008)){
			draw_back(black);
		return 1;
		}

	}
}


void play(void){
	cpu();
	mine();
}

int mine(void){
	draw_point(x, y, green);

	key();
}

void key(void){
	int j;
	int k;
	hword *ptr;
	ptr = (hword*) 0x04000130;

	while(1){
		int a = x;
		int b = y;
		if(judge()){
			draw_point(x, y, green);
			draw_point(a, b, black);
		}
		else if(0x0001!=((*ptr)&0x0001)){
			bullet();
			n++;
		}
		for(j=0;j<20000;j++){}
		if(n>15){
			lose();
			hword *ptr;
			ptr = (hword*) 0x04000130;
			if(0x0002!=((*ptr)&0x0002)){
				main();
			}
		}
		hword *ptr;
		ptr = (hword*)VRAM;
		for(k=0;k<=19199;k++){
			if(*ptr==yellow){
				count++;
			}
			ptr=ptr+1;
		}
		if(count==0){
			win();
			hword *ptr;
			ptr = (hword*) 0x04000130;
			if(0x0002!=((*ptr)&0x0002)){
				main();
			}
		}
		count = 0;
	}
}

int judge(void){
	hword *ptr;
	ptr = (hword*) 0x04000130;

	if(0x0010 != ((*ptr)&0x0010)){
		x = x + 1;
		if(x==239){
			x = x - 1;
			return 0;
		}
		
		return 1;	
	}else if(0x0020 != ((*ptr)&0x0020)){
		x = x -1;
		if(x==0){
			x = x + 1;
			return 0;
		}
		
		return 1;	
	}else{
		return 0;
	}
}

void bullet(void){
	int k;
	int c = x;
	int d = y;
	

	for(;d>=yy;d--){
		draw_point(c, d-1, white);
		for(k=0;k<3000;k++){}
		draw_point(c, d-1, black);
		for(k=0;k<3000;k++){}
		
	}
}

void cpu(void){
	int k;
	int i;
	int z;
	int j = 22;
	int h =11;
	
	for(i=0;i<3;i++){
		for(z=0;z<3;z++){
			random[i] = (j*j+50)%239+1;
			random[z] = (h*h+111)%80+1;
			draw_point(random[i], random[z], yellow);

			for(k=0;k<50000;k++){}
			j++;
			h++;
		}
	}
}

void lose(void){
	
	int k;
	
	static int l[5][5]  ={{1,0,0,0,0},
			       {1,0,0,0,0},
			       {1,0,0,0,0},
		 	       {1,0,0,0,0},
                                       {1,1,1,1,1}};

	static int o[5][5]  ={{0,1,1,1,0},
			       {1,0,0,0,1},
			       {1,0,0,0,1},
		 	       {1,0,0,0,1},
                                       {0,1,1,1,0}};

	static int s[5][5]  ={{0,1,1,1,1},
				  {1,0,0,0,0},
				  {0,1,1,1,0},
				  {0,0,0,0,1},
				  {1,1,1,1,0}};

	static int e[5][5]  ={{1,1,1,1,1},
			       {1,0,0,0,0},
	                            {1,1,1,1,1},
			       {1,0,0,0,0},
			       {1,1,1,1,1}};

	draw_back(blue);
	for(k=0;k<3000;k++){}
	draw_back(red);
	for(k=0;k<3000;k++){}
	draw_back(white);
	for(k=0;k<3000;k++){}
	draw_back(green);
	for(k=0;k<3000;k++){}
	draw_back(black);
	for(k=0;k<3000;k++){}	



	draw_char(l, 30, 50, 6, 6);
	draw_char(o, 80, 50, 6, 6);
	draw_char(s, 130, 50, 6, 6);
	draw_char(e, 180, 50, 6, 6);

	for(k=0;k<1000000;k++){}	

}

void win(void){
	
	static int w[5][5]  ={{1,0,0,0,1},
			       {1,0,1,0,1},
	                            {1,0,1,1,1},
			       {0,1,0,1,0},
			       {0,1,0,1,0}};

	static int i[5][5]  ={{0,1,1,1,0},
			       {0,0,1,0,0},
	                            {0,0,1,0,0},
			       {0,0,1,0,0},
			       {0,1,1,1,0}};

	
	static int n[5][5]  ={{1,0,0,0,1},
			       {1,1,0,0,1},
	                            {1,0,1,0,1},
			       {1,0,0,1,1},
			       {1,0,0,0,1}};





	draw_char(w, 50, 50, 6, 6);
	draw_char(i, 100, 50, 6, 6);
	draw_char(n, 150, 50, 6, 6);

}
