#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_OF_STUDENT 6

typedef struct data{
	char name[64];	/* 学生の氏名 */
	int score;		/* 学生の点数 */
} StudentData;

void 		read_from_data(StudentData[]);
float		calculate_average(StudentData[]);
StudentData	find_max_studentdata(StudentData[]);
void		write_to_result(StudentData[], float, StudentData);

int main( void )
{
	StudentData students[NUM_OF_STUDENT];
	StudentData max_studentdata;
	float score_average;

	read_from_data(students);

	score_average = calculate_average(students);
	max_studentdata = find_max_studentdata(students);

	write_to_result(students, score_average, max_studentdata);

	return 0;
}

void read_from_data( StudentData students[] )
{
	FILE *fp;
	int i;

	/* data.txtの読み込み */
	if((fp = fopen("data.txt","r")) == NULL){
		printf("file open error data.txt\n");
		exit(1);
	}

    /* data.txtより学生の名前と点数を取得する */
	for(i=0; i<NUM_OF_STUDENT; i++){
		fscanf(fp,"%s %d", students[i].name, &(students[i].score));
        // printf("%s: \t%d\n", students[i].name, students[i].score);
	}

	fclose(fp);
}

float calculate_average( StudentData students[] )
{
	int i;
	float average = 0;

	for(i=0; i<NUM_OF_STUDENT; i++){
		average += students[i].score;
	}
	average = average / NUM_OF_STUDENT;

	return average;
}

StudentData find_max_studentdata( StudentData students[] )
{
	int i;
	StudentData max_student;

	max_student.score = 0;

	for(i=0; i<NUM_OF_STUDENT; i++){
		if(students[i].score > max_student.score){
			max_student = students[i];
		}
	}

	return max_student;
	// printf("%s\n", max_student.name);
	// printf("%d\n", max_student.score);
}

void write_to_result( StudentData students[], float score_average, StudentData max_studentdata )
{
	FILE *fp;
	int i;

	if((fp = fopen("result.txt","w")) == NULL){
		printf("file open error result.txt\n");
		exit(1);
	}

	fprintf(fp,"平均点：%.2f 点\n", score_average);
	fprintf(fp,"最高点：%3d 点（%s）\n", max_studentdata.score, max_studentdata.name);

	fprintf(fp,"平均点以下の人：\n");
	for(i=0;i<NUM_OF_STUDENT;i++){
		if(students[i].score <= score_average){
			fprintf(fp,"  %d 点 (%s)\n",students[i].score, students[i].name);
		}
	}

	fclose(fp);
}