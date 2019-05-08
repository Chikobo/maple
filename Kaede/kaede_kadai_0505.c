#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Num_of_student 6

typedef struct data{
	char name[64];
	int score;
}Data;

int main(){
	FILE *fp;
	Data student[Num_of_student];
	int max = 0,i;
	char max_name[64];
	float average = 0;

	if((fp = fopen("data.txt","r")) == NULL){
		printf("file open error\n");
		exit(1);
	};//data.txtを読み込みモードで開くよ 失敗したら終わりにするよ

	for(i=0;i<Num_of_student;i++){
		fscanf(fp,"%s %d",student[i].name,&(student[i].score));
	}//名前と点数を格納するよ

	for(i=0;i<Num_of_student;i++){
		average += student[i].score;
	}
	average = average/Num_of_student;//平均点を出すよ

	for(i=0;i<Num_of_student;i++){
		if(student[i].score>max){
			max = student[i].score;
			strcpy(max_name, student[i].name);
		}
	}//最高点を出すよ 誰の点数かも記録するよ
	printf("%s\n",max_name);

	fclose(fp);//data.txtを閉じるよ

	if((fp = fopen("result.txt","w")) == NULL){
		printf("file open error\n");
		exit(1);
	}//result.txtを書き込みモードで開くよ 失敗したら終わりにするよ

	fprintf(fp,"平均点：%.2f 点\n",average);//平均点を出力するよ
	fprintf(fp,"最高点：%3d 点（%s）\n",max,max_name);//最高点と名前を出力するよ

	fprintf(fp,"平均点以下の人：\n");
	for(i=0;i<Num_of_student;i++){
		if(student[i].score <= average){
			fprintf(fp,"  %d 点 (%s)\n",student[i].score,student[i].name);
		}
	}

	fclose(fp);//result.txtを閉じるよ

	return 0;
}