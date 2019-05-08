#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_OF_STUDENT 100

typedef struct data {
    char name[64];    /* 学生の氏名 */
    int score;        /* 学生の点数 */
} StudentData;

int             read_from_data(StudentData[]);
float           calculate_average(StudentData[], int);
StudentData     find_max_studentdata(StudentData[], int);
void            write_to_result(StudentData[], int, float, StudentData);

int main( void )
{
    StudentData students[MAX_OF_STUDENT];
    StudentData max_studentdata;
    float score_average;
    int num_students;

    num_students = read_from_data(students);

    score_average = calculate_average(students, num_students);
    max_studentdata = find_max_studentdata(students, num_students);

    write_to_result(students, num_students, score_average, max_studentdata);

    return 0;
}

int read_from_data( StudentData students[] )
{
    FILE *fp;
    int i = 0;

    /* data.txtの読み込み */
    if((fp = fopen("data.txt","r")) == NULL) {
        printf("file open error data.txt\n");
        exit(1);
    }

    /* data.txtより学生の名前と点数を取得する */
    while((fscanf(fp,"%s %d", students[i].name, &(students[i].score))) != EOF) {
        i++;
    }

    /* data.txtにデータが無い場合、異常終了とする */
    if(i==0) {
        printf("Student data not found in data.txt\n");
        exit(1);
    }

    fclose(fp);

    return i;
}

float calculate_average( StudentData students[], int num_students )
{
    int i;
    float average = 0;

    for(i=0; i<num_students; i++) {
        average += students[i].score;
    }
    average = average / num_students;

    return average;
}

StudentData find_max_studentdata( StudentData students[], int num_students )
{
    int i;
    StudentData max_student;

    max_student.score = 0;

    for(i=0; i<num_students; i++) {
        if(students[i].score > max_student.score) {
            max_student = students[i];
        }
    }

    return max_student;
}

void write_to_result( StudentData students[], int num_students, float score_average, StudentData max_studentdata )
{
    FILE *fp;
    int i;

    /* result.txtを開く(書込みモード) */
    if((fp = fopen("result.txt","w")) == NULL) {
        printf("file open error result.txt\n");
        exit(1);
    }

    /* result.txtに情報を書き込む */
    fprintf(fp,"平均点：%.2f 点\n", score_average);
    fprintf(fp,"最高点：%3d 点（%s）\n", max_studentdata.score, max_studentdata.name);

    fprintf(fp,"平均点以下の人：\n");
    for(i=0; i<num_students; i++) {
        if(students[i].score <= score_average) {
            fprintf(fp,"  %d 点 (%s)\n",students[i].score, students[i].name);
        }
    }

    fclose(fp);
}