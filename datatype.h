#ifndef DATATYPE_H
#define DATATYPE_H

struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char studentId[20];
    char studentName[50];
    char classroomId[20];
    struct Date dateOfBirth;
    int gender;
    char email[50];
    char phone[15];
    int courseCount;
};
struct Teacher {
    char teacherId[20];
    char teacherName[50];
    char subject[30];
    char email[50];
    char phone[15];
};
#endif
