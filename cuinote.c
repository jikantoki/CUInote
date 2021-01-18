/* TNC0299 : ファイル処理 読み込み 編 */
/* Programed by SATOU Reo */
/* 2020/09/23 */
#define debug 0


#include	<stdio.h>
#include	<stdlib.h>
#include	<conio.h>
#include	<string.h>
#include	<time.h>
#define		STRL 512
#define		HEI 768
#define		PASSNUM 4245000
#define		PASS_ENT 613
#define		A_STR 4243852
#define		PRESENTER "Info\nCUINote 1.0 Presented by\n\tSato\n\tYoshida\n\tMiyakuni\n\tYamada\n\n"
#define		DEBUGMES "This is debug mode.\nIf you want to upload this program for public, change value variable \"debug\" 0.\n"

int date();
int yesorno();
int game_main();

int	main(int ar,char **b)
{
FILE *rfp,*passfp;
char filepath[128],savepath[128];
char dat[HEI][STRL];
int int_dat[HEI][STRL];
int height[HEI];
int strret;
char command[256];
char yn;
int int_yn;
char search[160];
unsigned int i,j,k,m,r;
unsigned int sealen;
int strlen_save;
int strlen_save2;
int strlen_save3;
int strlen_save4;
int ret;
char *where,*strstart;
unsigned int strp;
int searu,leng_st;
int programend=0;
char strv[STRL];
unsigned int indent[STRL];
char *str_chk;

#if debug
	puts(DEBUGMES);
#endif
#if debug==0
	printf("Start of Program\n");
#endif
	
	printf("TNC02999.c: 打倒nano\n");
	
	if(ar>=2){
		sprintf(filepath,"%s",b[1]);
		printf("%sを開きます\n",b[1]);
	}else{
		printf("開くファイルを指定してください。:");
		scanf("%s",filepath);
	}
	rfp=fopen(filepath,"r");
	if(rfp==NULL){
		printf("ファイルが読み込めないか存在しません。強制的に作成しますか？\n( y or n ):");
		if(yesorno()){
			printf("プログラムを終了します\n");
			fclose(rfp);
			return 1;
		}else{
			printf("ファイルを作成します\n");
			fclose(rfp);
		}
	}
	rfp=fopen(filepath,"a+");
	if(rfp==NULL){
		perror("Error:");
		printf("何か押したら終了するお");
		getch();
		exit(-1);
	}
	
	for(i=0;1;i++){
		fgets(dat[i],STRL,rfp);
		strret=strlen(dat[i]);
		#if debug
			puts(dat[i]);
		#endif
		if(dat[i][0]=='\0'){
			j=i;
			break;
		}
	}
	
	printf("現在のファイルの中身を出力します:\n\n");
	for(i=0;i<j;i++){
		printf("%3d:%s",i+1,dat[i]);
	}
	
	while(1){
		printf("\n\nどのように編集しますか？(hでヘルプを開きます)\n複数文字入力した場合には、OSのシステムにコマンドを送ります。:");
		fflush(stdin);
		gets(command);
		puts("");
		if(command[1]=='\0'){
			switch(command[0]){
				case '1':
					//全文表示
					printf("現在のファイルの中身を出力します:\n%s:\n\n",filepath);
					for(i=0;i<j;i++){
						printf("%3d:%s",i+1,dat[i]);
					}
					printf("\n\n現在時刻は以下の通りです:");
					date("");
					break;
				case '2':
					//指定行の編集
					printf("何行目を編集したいの？(0でキャンセル):");
					scanf("%d",&i);
					if(i==0){
						break;
					}else{
						strlen_save=strlen(dat[i-1]);
						dat[i-1][strlen_save-1]='\0';
						printf("%d行目を編集します\n現在の文字列は\"%s\"です\n新しい文字列:",i,dat[i-1]);
						scanf("%s",dat[i-1]);
						printf("新しい文字列は\"%s\"です\n",dat[i-1]);
						strlen_save=strlen(dat[i-1]);
						dat[i-1][strlen_save]='\n';
					}
					
					break;
				case '3':
					//指定行の追加と削除
					printf("行を追加しますか？削除しますか？\nA:add\nR:remove\nC:cancel\n\?:");
					yn=getch();
					if((yn=='a')||(yn=='A')){
						printf("何行目に追加したい？:");
						while(1){
							scanf("%d",&i);
							if(i==0){
								printf("その操作は無効です\n");
							}else{
								break;
							}
						}
						for(k=j;(k+2)>=i;k--){
							#if debug
							printf("%sを\n%sで上書きします\n",dat[k+1],dat[k]);
							printf("全体%d行中の%d行目の編集\n",j,k);
							#endif
							strcpy(dat[k+1],dat[k]);
						}
						dat[i-1][0]='\n';
						dat[i-1][1]='\0';
						j++;
						if(i==1){
							printf("先頭の行を追加しました\n");
						}else if(i==j){
							printf("最後の行を追加しました\n");
						}else{
							printf("%sと\n%sの間の行(%d行目)を追加しました\n",dat[i-2],dat[i],i);
						}
						
					}else if((yn=='r')||(yn=='R')){
						printf("何行目を消したい？:");
						while(1){
							scanf("%d",&i);
							if(i==0){
								printf("その操作は無効です\n");
							}else{
								break;
							}
						}
						for(i;i<j;i++){
							strcpy(dat[i-1],dat[i]);
						}
						j--;
						if(i==1){
							printf("先頭の行を削除しました\n");
						}else if(i==j){
							printf("最後の行を削除しました\n");
						}else{
							printf("%sと\n%sの間の行(%d行目)を削除しました\n",dat[i-1],dat[i],i);
						}
					}else{
						printf("キャンセルしました\n");
					}
					break;
				case '4':
					//文字列検索
					printf("検索したい文字列は（大文字と小文字を区別します）？:");
					scanf("%s",search);
					printf("\"%s\"を検索します…\n",search);
					sealen=strlen(search);
					searu=0;
					for(i=0;i<=j;i++){
						where=strstr(dat[i],search);
						#if debug
							printf("Serch now in line %4d, \"%s\" now.",i,dat[i]);
						#endif
						if(where==NULL){
							if((i==j)&&(searu==0)){
								printf("文字列\"%s\"は見つかりませんでした。\n",search);
							}
							continue;
						}else{
							sprintf(strv,"%s",where);
							leng_st=strlen(dat[i]);
							for(k=0;k<=leng_st;k++){
								if(strcmp(where,&dat[i][k])==0){
									printf("文字列\"%s\"は%d行目の%d文字目にあります（全て半角で数えた場合）。\n",search,i+1,k+1);
									searu=1;
								}
							}
						}
					}
					//strcmpでポインタと検索文字列を比較し、一致する場所で値を保存
					//dat[0]から順番にsearch変数の中身を照合していく
					//sealenを使ってピッタリの文字列で検索する
					break;
				case '5':
					//上書き保存
					fclose(rfp);
					rfp=fopen(filepath,"w");
					for(i=0;1;i++){
						fprintf(rfp,"%s",dat[i]);
						#if debug
							printf("Added:%s",dat[i]);
						#endif
						if(i==j)break;
					}
					fclose(rfp);
					rfp=fopen(filepath,"a+");
					printf("ファイルを\"%s\"に保存しました\n",filepath);
					break;
				case '6':
					//名前を付けて保存
					printf("パス込みで保存したい名前を教えてください:");
					scanf("%s",savepath);
					fclose(rfp);
					rfp=fopen(savepath,"w");
					for(i=0;1;i++){
						fprintf(rfp,"%s",dat[i]);
						#if debug
							printf("Added:%s",dat[i]);
						#endif
						if(i==j)break;
					}
					fclose(rfp);
					strcpy(filepath,savepath);
					rfp=fopen(filepath,"a+");
					printf("ファイルを\"%s\"に保存しました\n",filepath);
					break;
				case '7':
					//全削除
					printf("警告！ファイルを全削除します！よろしいですか？\nY:ファイルの中身を削除\nA:ファイルごと削除\nN:キャンセル\n\?:");
					yn=getch();
					if((yn=='y')||(yn=='Y')){
						fclose(rfp);
						rfp=fopen(filepath,"w");
						fclose(rfp);
						rfp=fopen(filepath,"a+");
						printf("ファイル\"%s\"の中身を削除しました\n",filepath);
					}else if((yn=='a')||(yn=='A')){
						fclose(rfp);
						remove(filepath);
						printf("ファイル\"%s\"を削除しました\n",filepath);
						programend=1;
					}else{
						printf("キャンセルしました");
					}
					break;
				case '8':
					//自動インデント
					
					printf(	"このプログラムは拡張子が*.cのファイルのタブ位置を揃える為のものです。\n"
							"改行を超えた文章の調整や変数の宣言のみインデントしない対策は実装されておりません。\n"
							"また、拡張子が*.cで中身がC言語のファイルではない場合、思わぬ文章の乱れを引き起こす場合があります。\n"
							"全角文字のインデントには対応しています。"
							"\n以上のことを理解し、このプログラムを利用しますか？\n"
							"(y or n):");
					
					printf("\n");
					if(yesorno()){
						printf("操作を中断しました。\n");
						break;
					}
					
					indent[0]=0;
					
					strlen_save=strlen(filepath);
					if(!strcmp(&filepath[strlen_save-2],".c")){
						for(i=0;i<j;i++){
							strlen_save2=strlen(dat[i]);
							for(k=0;k<strlen_save2;k++){
								if((dat[i][0]==' ')||(dat[i][0]=='\t')){
									sprintf(dat[i],"%s",&dat[i][1]);
								}
							}
							if(i!=0){
								indent[i+1]=indent[i];
							}
							switch(dat[i][0]){
								case '}':
									indent[i+1]--;
									#if debug
										printf("%d行目、インデント削除:%d\n",i,indent[i+1]);
									#endif
									break;
								default:
									break;
							}
							strlen_save3=strlen(dat[i]);
							switch(dat[i][strlen_save3-2]){
								case '{':
									indent[i+1]++;
									#if debug
										printf("%d行目、インデント追加:%d\n",i,indent[i+1]);
									#endif
									break;
								case '}':
									indent[i]--;
									#if debug
										printf("%d行目、インデント削除:%d\n",i,indent[i]);
									#endif
									break;
								default:
									break;
							}
							if(dat[i][strlen_save3-1]=='}'){
								indent[i]--;
									#if debug
										printf("%d行目、インデント削除:%d\n",i,indent[i]);
									#endif
							}
							if(indent[i]<0)indent[i]=0;
							for(m=0;m<indent[i];m++){
								strlen_save4=strlen(dat[i]);
								if(strlen_save4==1){
									dat[i][1]=dat[i][0];
								}else if(strlen_save4!=0){
									for(r=strlen_save4+1;r>0;r--){
										dat[i][r]=dat[i][r-1];
									}
								}
								dat[i][0]='\t';
							}
						}
						printf("インデントが完了しました。\n");
					}else{
						printf(	"ファイルの拡張子が\".c\"でないため、自動インデントは開始されませんでした。\n"
								"もしこのファイルがC言語のコードである場合は、名前を付けて保存より拡張子を.cに変更してください。\n");
					}
					break;
				case '0':
					#if debug
						puts("Out of while and switch.");
					#endif
					//終了
					programend=1;
					break;
				case 'g':
				case 'G':
					//RPG風ゲーム
					game_main();
					break;
				case 'i':
				case 'I':
					//製作者情報
					printf("%s",PRESENTER);
					break;
				case 'c':
				case 'C':
					//画面クリア
					system("cls");
					break;
				case 'h':
				case 'H':
					//help
					printf("ヘルプを出力します\n");
					printf(	"\t1:現在のファイルの中身と現在時刻を出力\n"
							"\t2:行単位でのファイルの編集\n"
							"\t3:行の追加と削除\n"
							"\t4:文字列検索\n"
							"\t5:上書き保存\n"
							"\t6:名前を付けて保存\n"
							"\t7:全削除\n"
							"\t8:自動インデント（C言語のみ）\n"
							"\t0:終了\n"
							"\tg:RPG風のゲームを開始\n"
							"\th:ヘルプを出力\n"
							"\tc:画面をクリアする\n"
							"\ti:製作者情報\n");
#if debug
					printf("\tp:debug mode:ファイルの暗号化（日本語非対応、削除済み）\n");
#endif
					break;
				default:
					printf("その操作は受け付けておりません。\n");
					break;
			}//switch終了
			if(programend==1)break;
		}else{
			str_chk=strstr(command,"notepad");
			if(str_chk==NULL){
				system(command);
			}else{
				printf("notepadはライバルなので開けません。\n");
			}
		}
	}
	
	printf("\n\nEnd of Program\n何か押したら終了するお\n");
	fclose(rfp);
	getch();
	
	return 0;
}

int yesorno(void){	//if(yesorno())でYがFalse、NがTrue
	char sub_yn;
	while(1){
		sub_yn=getch();
		switch(sub_yn){
			case 'Y':
			case 'y':
				return 0;
				break;
			case 'N':
			case 'n':
				return 1;
				break;
			default:
				printf("その操作は受け付けておりません。\n");
				break;
		}
	}
}

int date(char type[64]){
time_t a_now=time(NULL);
struct tm *a_date;
int a_ret;
a_date=localtime(&a_now);
	
	printf("%s",asctime(a_date));
	return a_ret;
}

int game_main(void)
{
int gmap[8][8] ={	{ 1,1,1,1,1,1,1,1 },	//0
					{ 1,0,0,0,0,0,0,1 },	//1
					{ 1,2,2,2,2,2,2,1 },	//2
					{ 1,3,3,3,3,3,3,1 },	//3
					{ 1,0,1,1,1,1,0,1 },	//4
					{ 1,0,0,0,0,0,0,1 },	//5
					{ 1,2,2,2,2,2,2,1 },	//6
					{ 1,1,1,1,1,1,1,1 } };	//7
int manx,many;
int savo;
char movd;
int i,j;
int err=0;
	
	printf("テンキーの2,4,6,8で移動できます\nEを入力でゲームを終了します\n");
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			switch(gmap[i][j]){
			case 0:
				printf("□");
				break;
			case 1:
				printf("壁");
				break;
			case 2:
				printf("沼");
				break;
			case 3:
				printf("山");
				break;
			case 9:
				printf("人");
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
	
	manx=3;
	many=5;
	savo=gmap[many][manx];
	gmap[many][manx]=9;
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			switch(gmap[i][j]){
			case 0:
				printf("□");
				break;
			case 1:
				printf("壁");
				break;
			case 2:
				printf("沼");
				break;
			case 3:
				printf("山");
				break;
			case 9:
				printf("人");
				break;
			}
		}
		printf("\n");
	}
	
	movd=getch();
	
	while(1){
		if((movd=='e')||(movd=='E'))break;
		switch(movd){
			case '2':
				if(many<7){
					gmap[many][manx]=savo;
					many+=1;
					savo=gmap[many][manx];
					err=0;
				}else{
					err=1;
				}
				break;
			case '4':
				if(manx>0){
					gmap[many][manx]=savo;
					manx-=1;
					savo=gmap[many][manx];
					err=0;
				}else{
					err=1;
				}
				break;
			case '6':
				if(manx<7){
					gmap[many][manx]=savo;
					manx+=1;
					savo=gmap[many][manx];
					err=0;
				}else{
					err=1;
				}
				break;
			case '8':
				if(many>0){
					gmap[many][manx]=savo;
					many-=1;
					savo=gmap[many][manx];
					err=0;
				}else{
					err=1;
				}
				break;
			default:
				err=1;
				break;
		}
		if(err==1){
			printf("その操作はできません\n");
		}else{
			gmap[many][manx]=9;
			
			for(i=0;i<8;i++){
				for(j=0;j<8;j++){
					switch(gmap[i][j]){
					case 0:
						printf("□");
						break;
					case 1:
						printf("壁");
						break;
					case 2:
						printf("沼");
						break;
					case 3:
						printf("山");
						break;
					case 9:
						printf("人");
						break;
					}
				}
			printf("\n");
			}
		}
		movd=getch();
		printf("\n");
	}
	
	printf("ゲームを終了します\n");
	
	return 0;
}