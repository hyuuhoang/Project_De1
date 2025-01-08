#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"


// sinh vien
void getStudentByFile(int *numberStudent, struct Student *sv);
void saveStudent(struct Student *sv, int numberStudent);
void startTheProgram(int *choiceSystem);
void endTheProgram(int *flag);
void startMenu(int *choiceMenu);
void startStudentMenu(int *choiceStudentMenu);
char showAllStudent(int *numberStudent, struct Student *sv);
char addANewStudent(int *numberStudent, struct Student *sv, struct Student *sv1);
char editStudent(int *numberStudent, struct Student *sv);
char deleteStudent(int *numberStudent, struct Student *sv);
char searchStudentByName(int *numberStudent, struct Student *sv);
void sortStudentsByName(int *numberStudent, struct Student *sv, int order);
int compareStudentNameAscending(const void *a, const void *b);
int compareStudentNameDescending(const void *a, const void *b);
int isValidStudentId(char *studentId);
int isValidEmail(char *email);
int isValidPhoneNumber(char *phone);
int isPhoneNumberUnique(char *phone, struct Student *sv, int numberStudent);
   

void getTeacherByFile(int *numberTeacher, struct Teacher *gv);
void saveTeacher(struct Teacher *gv, int numberTeacher);
void startTeacherMenu(int *choiceTeacherMenu);
char addANewTeacher(int *numberTeacher, struct Teacher *gv, struct Teacher *gv1);
char showAllTeacher(int *numberTeacher, struct Teacher *gv);
char editTeacher(int *numberTeacher, struct Teacher *gv);
char deleteTeacher(int *numberTeacher, struct Teacher *gv);
char searchTeacherByName(int *numberTeacher, struct Teacher *gv);

#endif
