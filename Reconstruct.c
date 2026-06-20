#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define length sizeof(struct student)

struct menu {
    char serial[5];
    char choice[30];
}menu[11]={
    {"1","录入学生成绩"},
    {"2","删除学生成绩"},
    {"3","查看学生成绩"},
    {"4","以学号查找学生成绩"},
    {"5","修改学生成绩"},
    {"6","以姓名查找学生成绩"},
    {"7","保存学生成绩"},
    {"8","学生成绩报告"},
    {"9","单科成绩排名"},
    {"A/a","退出"},
    {"0","刷新菜单"}
};

struct student {
    int id;
    char name[10];
    int age;
    float c_score;
    float english_score;
    float mathanaly_score;
    float total_score;
    struct student *next;
}*p1,*p2,*p3,*head,*q1_f,*q1_b,*q3_f,*q3_b,*q_temp,*q1,*q2,*q3,*hat;

char file_name[50];
char judge;
char try_get[5];
char name_temp[10];
int id_temp;
int count = 0;
FILE *f;

void menu_present() {
    printf("\n\n\n\n     ");
    printf("****************----------------学生成绩管理系统---------------***********");
    printf("\n\n\n\n");
    for (int i=0 ; i<=10 ; i++) {
        if (i%2 == 0) {
            printf("                     ");
            printf("-[%s] %s",(menu[i]).serial,(menu[i]).choice);
        }
        else {
            printf("                ");
            printf("-[%s] %s\n\n",(menu[i]).serial,(menu[i]).choice);
        }
    }
    printf("\n\n     ");
    printf("****************-----------------欢迎使用学生成绩管理系统---------------***********\n\n");
    printf("请输入您想做的事件编号0—A:   ");
}

int y_judge(char a) {
    switch (a) {
        case 'Y':
        case 'y': return 1;
        default : return 0;
    }
}

int end_judge() {
    fread(try_get,1,1,f);
    if (feof(f)) {
        clearerr(f);
        return 1;
    }
    else {
        fseek(f,-1,SEEK_CUR);
        return 0;
    }
}

int content_judge() {
    if (f == NULL) {
        printf("文件打开失败\n");
        return 0;
    }
    else if (end_judge()) {
        printf("无学生信息\n");
        return 0;
    }
    else {
        return 1;
    }
}

void f_backup() {
    p1 = (struct student *)malloc(length);
    head = p1;
    p2 = p1;
    if (content_judge()) {
        while (!end_judge()) {
            fscanf(f,"%d %s %d %f %f %f",&p1->id,p1->name,&p1->age,&p1->c_score,&p1->english_score,&p1->mathanaly_score);
            p1->total_score = p1->c_score + p1->english_score + p1->mathanaly_score;
            if (!end_judge()) {
                fread(try_get,1,1,f);
            }
            p2 = (struct student *)malloc(length);
            p1->next = p2;
            p1 = p2;
        }
        fseek(f,0,SEEK_SET);
    }
    
}

void sub_f1() {
    printf("是否新增学生信息？(y/n): ");
    scanf("%c",&judge);
    getchar();
    if (y_judge(judge)) {
        do {
            printf("请输入学号: ");
            scanf("%d",&p1->id);
            getchar();
            printf("请输入姓名、年龄、C语言成绩、英语成绩、数分成绩（空格分隔）: ");
            scanf("%s %d %f %f %f",p1->name,&p1->age,&p1->c_score,&p1->english_score,&p1->mathanaly_score);
            p1->total_score = p1->c_score + p1->english_score + p1->mathanaly_score;
            getchar();
            printf("是否继续新增？(y/n): ");
            scanf("%c",&judge);
            getchar();
            p2 = (struct student *)malloc(length);
            p1->next = p2;
            p1 = p2;
            count++;
        }while(y_judge(judge));
        printf("已成功添加 %d 名学生信息。\n",count);
        count = 0;
    }
    else {
        printf("未添加任何学生。\n");
    }
}

int sub_f4_f5_f6(int a) {
    switch (a) {
        case 4: 
        case 5: strcpy(name_temp,"NULL"); break;
        case 6: id_temp = -1; break;
    }
    p1 = head;
    while (p1 != p2) {
        if (p1->id == id_temp || !strcmp(p1->name,name_temp)) {
            count = -1;
            break;
        }
        p1 = p1->next;
    }
    if (count == 0) {
        switch (a) {
            case 4:
            case 5: printf("未找到学号为 %d 的学生。\n",id_temp); break;
            case 6: printf("未找到姓名为 %s 的学生。\n",name_temp); break;
        }
        return 0;
    }
    else {
        return 1;
    }
}

int sub_f4_f6(int a) {
    getchar();
    if (content_judge()) {
        if (sub_f4_f5_f6(a)) {
            printf("学号: %d, 姓名: %s, 年龄: %d, C语言: %.1f, 英语: %.1f, 数分: %.1f, 总分: %.1f\n",
            p1->id,p1->name,p1->age,p1->c_score,p1->english_score,p1->mathanaly_score,p1->total_score);
            p1 = p2;
        }
        count = 0;
    }
}

void sub_f9(int a) {
    count = 0;
    int count_extra = 0;
    float *arr[10];
    p1 = head;
    q1 = (struct student *)malloc(length);
    hat = q1;
    while (p1 != p2) {
        *q1 = *p1;
        q2 = (struct student *)malloc(length);
        q1->next = q2;
        q1 = q2;
        p1 = p1->next;
    }
    q1 = hat; q1_f = q1; q1_b = q1->next;
    while (q1->next != q2) {
        q3 = q1->next; 
        q3_b = q3->next;
        q3_f = q3; 
        while (q3 != q2) {
            arr[0] = (float *)&q1->id; arr[1] = (float *)&q3->id;
            arr[2] = &q3->c_score; arr[3] = &q1->c_score;
            arr[4] = &q3->english_score; arr[5] = &q1->english_score; 
            arr[6] = &q3->mathanaly_score; arr[7] = &q1->mathanaly_score; 
            arr[8] = &q3->total_score; arr[9] = &q1->total_score;
            if (*arr[a*2-2] > *arr[a*2-1]) {
                if (q1_b == q3) { 
                    q_temp = (struct student *)malloc(length);
                    q1->next = q_temp;
                    q_temp->next = q3;
                    q1_b = q_temp;
                    q3_f = q_temp;
                }
                q1_f->next = q3;
                q3->next = q1_b;
                q3_f->next = q1;
                q1->next = q3_b;
                if (q1_b == q_temp) {
                    q_temp->next = NULL;
                    q3->next = q1;
                    q1_b = q1;
                    q3_f = q1;
                    free(q_temp); 
                }
                if (q1 == hat) {
                    hat = q3;
                    q1_f = q3;
                }
                q_temp = q3;
                q3 = q1;
                q1 = q_temp;
                q_temp = NULL;
            }
            count++;
            if (count >= 1) {
                q3_f = q3;
            }
            q3 = q3_b;
            if (q3_b != q2) {
                q3_b = q3_b->next;
            }
        }
        count_extra++;
        if (count_extra >= 1) {
            q1_f = q1;
        }
        q1 = q1_b;
        q1_b = q1_b->next;
    }
    q1 = q2;
    count = 0;
}

void f1() {
    if (f == NULL || end_judge()) {
        printf("文件为空或不存在，将新建学生信息。\n");
        sub_f1();
    }
    else {
        printf("已有学生信息如下：\n");
        printf("学号     姓名       年龄   C语言   英语    数分\n");
        p1 = head;
        do {
            printf("%-9d%-10s%7d%7.1f%7.1f%7.1f\n",p1->id,p1->name,p1->age,p1->c_score,p1->english_score,p1->mathanaly_score);
            p1 = p1->next;
        }while(p1 != p2);
        sub_f1();
    }
}

void f2() {
    printf("请输入要删除的学生学号: ");
    scanf("%d",&id_temp);
    getchar();
    if (content_judge()) {
        p1 = head;
        while(p1 != p2) {
            if (p1->id == id_temp) {
                if (p1 == head) {
                    p1 = p1->next;
                    head = p1;
                }
                else if (count == 1) {
                    head->next = p1->next;
                }
                else {
                    p3->next = p1->next;
                }
                count = -1;
                break;
            }
            if (count >= 1) {
                p3 = p1;
            }            
            count++;
            p1 = p1->next;
        }
        p1 = p2;
        p3 = NULL;
        if (count != -1) {
            printf("未找到学号为 %d 的学生。\n",id_temp);
        }
        else {
            printf("删除成功。\n");
        }
        count = 0;
    }
    id_temp = -1;
}

void f3() {
    if (end_judge()) {
        printf("无学生信息。\n");
    }
    else if (f == NULL) {
        printf("打开文件失败，可能尚无数据。\n");
    }
    else {
        printf("学号     姓名       年龄   C语言   英语    数分    总分\n");
        p1 = head;
        do {
            printf("%-9d%-10s%7d%7.1f%7.1f%7.1f%7.1f\n",
                p1->id,p1->name,p1->age,p1->c_score,p1->english_score,p1->mathanaly_score,p1->total_score);
                p1 = p1->next;
        }while(p1 != p2);
    }
}

void f4() {
    printf("请输入要查找的学号: ");
    scanf("%d",&id_temp);
    sub_f4_f6(4);
}

void f5() {
    printf("请输入要修改的学生学号: ");
    scanf("%d",&id_temp);
    getchar();
    if (content_judge()) {
        if (sub_f4_f5_f6(5)) {
            printf("请选择要修改的科目: c(C语言), e(英语), m(数分): ");
            char subject_temp;
            scanf("%c",&subject_temp);
            switch (subject_temp) {
                case 'c': printf("请输入新的C语言成绩: "); scanf("%f",&p1->c_score); break;
                case 'e': printf("请输入新的英语成绩: "); scanf("%f",&p1->english_score); break;
                case 'm': printf("请输入新的数分成绩："); scanf("%f",&p1->mathanaly_score); break;
            }
            getchar();
            printf("成绩修改成功。\n");
            p1 = p2;
            count = 0;
        }
    }
}


void f6() {
    printf("请输入要查找的姓名: ");
    scanf("%s",name_temp);
    sub_f4_f6(6);
}

void f7() {
    printf("所有修改均已自动保存到文件 %s",file_name);
    f = fopen(file_name,"w+");
    p1 = head;
    while(p1 != p2) {
        fprintf(f,"%d %s %d %.1f %.1f %.1f\n",p1->id,p1->name,p1->age,p1->c_score,p1->english_score,p1->mathanaly_score);
        p1 = p1->next;
    }
    fclose(f);
    f = fopen(file_name,"r+");
}

void f8() {
    if (f == NULL) {
        printf("文件打开失败\n");
    }
    else if (end_judge()) {
        printf("无学生信息，无法生成报告。\n");
    }
    else {
        float c=0, e=0, m=0, c6=0, e6=0, m6=0, c9=0, e9=0, m9=0;
        p1 = head;
        while (p1 != p2) {
            c += (p1->c_score);
            e += (p1->english_score);
            m += (p1->mathanaly_score);
            count++;
            c6 += (p1->c_score>60 ? 1:0);
            e6 += (p1->english_score>60 ? 1:0);
            m6 += (p1->mathanaly_score>60 ? 1:0);
            c9 += (p1->c_score>90 ? 1:0);
            e9 += (p1->english_score>90 ? 1:0);
            m9 += (p1->mathanaly_score>90 ? 1:0);
            p1 = p1->next;
        }
        printf("====== 成绩统计报告 ======\n");
        printf("C语言平均成绩: %.1f, 60分以上占比: %.1f%%, 90分以上占比: %.1f%%\n",c/count,c6/count*100,c9/count*100);
        printf("英语平均成绩: %.1f, 60分以上占比: %.1f%%, 90分以上占比: %.1f%%\n",e/count,e6/count*100,e9/count*100);
        printf("数分平均成绩: %.1f, 60分以上占比: %.1f%%, 90分以上占比: %.1f%%\n",m/count,m6/count*100,m9/count*100);
        printf("==========================\n");
        count = 0;
    }
    
}

void f9() {
    printf("请选择排序方式: 1-按学号(升序) 2-按C语言成绩(降序) 3-按英语成绩(降序) 4-按数分成绩(降序) 5-按总成绩(降序): ");
    scanf("%d",&count);
    getchar();
    if (content_judge()) {
        sub_f9(count);
        printf("学号     姓名       年龄   C语言   英语    数分    总分\n");
        q1 = hat;
        do {
            printf("%-9d%-10s%7d%7.1f%7.1f%7.1f%7.1f\n",
                q1->id,q1->name,q1->age,q1->c_score,q1->english_score,q1->mathanaly_score,q1->total_score);
                q1 = q1->next;
        }while(q1 != q2);
    }
}

void fa() {
    printf("退出系统。");
    exit(0);
}

void f0() {
    printf("\n");
}

int main() {
    printf("\n请输入学生信息文件名: ");
    scanf("%s",file_name);
    getchar();
    f = fopen(file_name,"r+");
    f_backup();
    char choice;
    while (1) {
        menu_present();
        scanf("%c",&choice);
        getchar();
        switch (choice) {
            case '1': f1(); break;
            case '2': f2(); break;
            case '3': f3(); break;
            case '4': f4(); break;
            case '5': f5(); break;
            case '6': f6(); break;
            case '7': f7(); break;
            case '8': f8(); break;
            case '9': f9(); break;
            case 'a': fa(); break;
            case 'A': fa(); break;
            case '0': f0(); break;
            default : printf("\n无效选项，请重新输入。\n");
        }
    }
}