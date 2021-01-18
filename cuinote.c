/* TNC0299 : �t�@�C������ �ǂݍ��� �� */
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
	
	printf("TNC02999.c: �œ|nano\n");
	
	if(ar>=2){
		sprintf(filepath,"%s",b[1]);
		printf("%s���J���܂�\n",b[1]);
	}else{
		printf("�J���t�@�C�����w�肵�Ă��������B:");
		scanf("%s",filepath);
	}
	rfp=fopen(filepath,"r");
	if(rfp==NULL){
		printf("�t�@�C�����ǂݍ��߂Ȃ������݂��܂���B�����I�ɍ쐬���܂����H\n( y or n ):");
		if(yesorno()){
			printf("�v���O�������I�����܂�\n");
			fclose(rfp);
			return 1;
		}else{
			printf("�t�@�C�����쐬���܂�\n");
			fclose(rfp);
		}
	}
	rfp=fopen(filepath,"a+");
	if(rfp==NULL){
		perror("Error:");
		printf("������������I�����邨");
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
	
	printf("���݂̃t�@�C���̒��g���o�͂��܂�:\n\n");
	for(i=0;i<j;i++){
		printf("%3d:%s",i+1,dat[i]);
	}
	
	while(1){
		printf("\n\n�ǂ̂悤�ɕҏW���܂����H(h�Ńw���v���J���܂�)\n�����������͂����ꍇ�ɂ́AOS�̃V�X�e���ɃR�}���h�𑗂�܂��B:");
		fflush(stdin);
		gets(command);
		puts("");
		if(command[1]=='\0'){
			switch(command[0]){
				case '1':
					//�S���\��
					printf("���݂̃t�@�C���̒��g���o�͂��܂�:\n%s:\n\n",filepath);
					for(i=0;i<j;i++){
						printf("%3d:%s",i+1,dat[i]);
					}
					printf("\n\n���ݎ����͈ȉ��̒ʂ�ł�:");
					date("");
					break;
				case '2':
					//�w��s�̕ҏW
					printf("���s�ڂ�ҏW�������́H(0�ŃL�����Z��):");
					scanf("%d",&i);
					if(i==0){
						break;
					}else{
						strlen_save=strlen(dat[i-1]);
						dat[i-1][strlen_save-1]='\0';
						printf("%d�s�ڂ�ҏW���܂�\n���݂̕������\"%s\"�ł�\n�V����������:",i,dat[i-1]);
						scanf("%s",dat[i-1]);
						printf("�V�����������\"%s\"�ł�\n",dat[i-1]);
						strlen_save=strlen(dat[i-1]);
						dat[i-1][strlen_save]='\n';
					}
					
					break;
				case '3':
					//�w��s�̒ǉ��ƍ폜
					printf("�s��ǉ����܂����H�폜���܂����H\nA:add\nR:remove\nC:cancel\n\?:");
					yn=getch();
					if((yn=='a')||(yn=='A')){
						printf("���s�ڂɒǉ��������H:");
						while(1){
							scanf("%d",&i);
							if(i==0){
								printf("���̑���͖����ł�\n");
							}else{
								break;
							}
						}
						for(k=j;(k+2)>=i;k--){
							#if debug
							printf("%s��\n%s�ŏ㏑�����܂�\n",dat[k+1],dat[k]);
							printf("�S��%d�s����%d�s�ڂ̕ҏW\n",j,k);
							#endif
							strcpy(dat[k+1],dat[k]);
						}
						dat[i-1][0]='\n';
						dat[i-1][1]='\0';
						j++;
						if(i==1){
							printf("�擪�̍s��ǉ����܂���\n");
						}else if(i==j){
							printf("�Ō�̍s��ǉ����܂���\n");
						}else{
							printf("%s��\n%s�̊Ԃ̍s(%d�s��)��ǉ����܂���\n",dat[i-2],dat[i],i);
						}
						
					}else if((yn=='r')||(yn=='R')){
						printf("���s�ڂ����������H:");
						while(1){
							scanf("%d",&i);
							if(i==0){
								printf("���̑���͖����ł�\n");
							}else{
								break;
							}
						}
						for(i;i<j;i++){
							strcpy(dat[i-1],dat[i]);
						}
						j--;
						if(i==1){
							printf("�擪�̍s���폜���܂���\n");
						}else if(i==j){
							printf("�Ō�̍s���폜���܂���\n");
						}else{
							printf("%s��\n%s�̊Ԃ̍s(%d�s��)���폜���܂���\n",dat[i-1],dat[i],i);
						}
					}else{
						printf("�L�����Z�����܂���\n");
					}
					break;
				case '4':
					//�����񌟍�
					printf("����������������́i�啶���Ə���������ʂ��܂��j�H:");
					scanf("%s",search);
					printf("\"%s\"���������܂��c\n",search);
					sealen=strlen(search);
					searu=0;
					for(i=0;i<=j;i++){
						where=strstr(dat[i],search);
						#if debug
							printf("Serch now in line %4d, \"%s\" now.",i,dat[i]);
						#endif
						if(where==NULL){
							if((i==j)&&(searu==0)){
								printf("������\"%s\"�͌�����܂���ł����B\n",search);
							}
							continue;
						}else{
							sprintf(strv,"%s",where);
							leng_st=strlen(dat[i]);
							for(k=0;k<=leng_st;k++){
								if(strcmp(where,&dat[i][k])==0){
									printf("������\"%s\"��%d�s�ڂ�%d�����ڂɂ���܂��i�S�Ĕ��p�Ő������ꍇ�j�B\n",search,i+1,k+1);
									searu=1;
								}
							}
						}
					}
					//strcmp�Ń|�C���^�ƌ�����������r���A��v����ꏊ�Œl��ۑ�
					//dat[0]���珇�Ԃ�search�ϐ��̒��g���ƍ����Ă���
					//sealen���g���ăs�b�^���̕�����Ō�������
					break;
				case '5':
					//�㏑���ۑ�
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
					printf("�t�@�C����\"%s\"�ɕۑ����܂���\n",filepath);
					break;
				case '6':
					//���O��t���ĕۑ�
					printf("�p�X���݂ŕۑ����������O�������Ă�������:");
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
					printf("�t�@�C����\"%s\"�ɕۑ����܂���\n",filepath);
					break;
				case '7':
					//�S�폜
					printf("�x���I�t�@�C����S�폜���܂��I��낵���ł����H\nY:�t�@�C���̒��g���폜\nA:�t�@�C�����ƍ폜\nN:�L�����Z��\n\?:");
					yn=getch();
					if((yn=='y')||(yn=='Y')){
						fclose(rfp);
						rfp=fopen(filepath,"w");
						fclose(rfp);
						rfp=fopen(filepath,"a+");
						printf("�t�@�C��\"%s\"�̒��g���폜���܂���\n",filepath);
					}else if((yn=='a')||(yn=='A')){
						fclose(rfp);
						remove(filepath);
						printf("�t�@�C��\"%s\"���폜���܂���\n",filepath);
						programend=1;
					}else{
						printf("�L�����Z�����܂���");
					}
					break;
				case '8':
					//�����C���f���g
					
					printf(	"���̃v���O�����͊g���q��*.c�̃t�@�C���̃^�u�ʒu�𑵂���ׂ̂��̂ł��B\n"
							"���s�𒴂������͂̒�����ϐ��̐錾�̂݃C���f���g���Ȃ��΍�͎�������Ă���܂���B\n"
							"�܂��A�g���q��*.c�Œ��g��C����̃t�@�C���ł͂Ȃ��ꍇ�A�v��ʕ��̗͂���������N�����ꍇ������܂��B\n"
							"�S�p�����̃C���f���g�ɂ͑Ή����Ă��܂��B"
							"\n�ȏ�̂��Ƃ𗝉����A���̃v���O�����𗘗p���܂����H\n"
							"(y or n):");
					
					printf("\n");
					if(yesorno()){
						printf("����𒆒f���܂����B\n");
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
										printf("%d�s�ځA�C���f���g�폜:%d\n",i,indent[i+1]);
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
										printf("%d�s�ځA�C���f���g�ǉ�:%d\n",i,indent[i+1]);
									#endif
									break;
								case '}':
									indent[i]--;
									#if debug
										printf("%d�s�ځA�C���f���g�폜:%d\n",i,indent[i]);
									#endif
									break;
								default:
									break;
							}
							if(dat[i][strlen_save3-1]=='}'){
								indent[i]--;
									#if debug
										printf("%d�s�ځA�C���f���g�폜:%d\n",i,indent[i]);
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
						printf("�C���f���g���������܂����B\n");
					}else{
						printf(	"�t�@�C���̊g���q��\".c\"�łȂ����߁A�����C���f���g�͊J�n����܂���ł����B\n"
								"�������̃t�@�C����C����̃R�[�h�ł���ꍇ�́A���O��t���ĕۑ����g���q��.c�ɕύX���Ă��������B\n");
					}
					break;
				case '0':
					#if debug
						puts("Out of while and switch.");
					#endif
					//�I��
					programend=1;
					break;
				case 'g':
				case 'G':
					//RPG���Q�[��
					game_main();
					break;
				case 'i':
				case 'I':
					//����ҏ��
					printf("%s",PRESENTER);
					break;
				case 'c':
				case 'C':
					//��ʃN���A
					system("cls");
					break;
				case 'h':
				case 'H':
					//help
					printf("�w���v���o�͂��܂�\n");
					printf(	"\t1:���݂̃t�@�C���̒��g�ƌ��ݎ������o��\n"
							"\t2:�s�P�ʂł̃t�@�C���̕ҏW\n"
							"\t3:�s�̒ǉ��ƍ폜\n"
							"\t4:�����񌟍�\n"
							"\t5:�㏑���ۑ�\n"
							"\t6:���O��t���ĕۑ�\n"
							"\t7:�S�폜\n"
							"\t8:�����C���f���g�iC����̂݁j\n"
							"\t0:�I��\n"
							"\tg:RPG���̃Q�[�����J�n\n"
							"\th:�w���v���o��\n"
							"\tc:��ʂ��N���A����\n"
							"\ti:����ҏ��\n");
#if debug
					printf("\tp:debug mode:�t�@�C���̈Í����i���{���Ή��A�폜�ς݁j\n");
#endif
					break;
				default:
					printf("���̑���͎󂯕t���Ă���܂���B\n");
					break;
			}//switch�I��
			if(programend==1)break;
		}else{
			str_chk=strstr(command,"notepad");
			if(str_chk==NULL){
				system(command);
			}else{
				printf("notepad�̓��C�o���Ȃ̂ŊJ���܂���B\n");
			}
		}
	}
	
	printf("\n\nEnd of Program\n������������I�����邨\n");
	fclose(rfp);
	getch();
	
	return 0;
}

int yesorno(void){	//if(yesorno())��Y��False�AN��True
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
				printf("���̑���͎󂯕t���Ă���܂���B\n");
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
	
	printf("�e���L�[��2,4,6,8�ňړ��ł��܂�\nE����͂ŃQ�[�����I�����܂�\n");
	
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			switch(gmap[i][j]){
			case 0:
				printf("��");
				break;
			case 1:
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("�R");
				break;
			case 9:
				printf("�l");
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
				printf("��");
				break;
			case 1:
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("�R");
				break;
			case 9:
				printf("�l");
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
			printf("���̑���͂ł��܂���\n");
		}else{
			gmap[many][manx]=9;
			
			for(i=0;i<8;i++){
				for(j=0;j<8;j++){
					switch(gmap[i][j]){
					case 0:
						printf("��");
						break;
					case 1:
						printf("��");
						break;
					case 2:
						printf("��");
						break;
					case 3:
						printf("�R");
						break;
					case 9:
						printf("�l");
						break;
					}
				}
			printf("\n");
			}
		}
		movd=getch();
		printf("\n");
	}
	
	printf("�Q�[�����I�����܂�\n");
	
	return 0;
}