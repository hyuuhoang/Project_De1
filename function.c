#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "function.h"


// mo danh sach sinh vien tu file 
void getStudentByFile(int *numberStudent, struct Student *sv) {
    FILE *file = fopen("student.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file. Khoi tao danh sach rong.\n");
        *numberStudent = 0;
        return;
    }
    *numberStudent = fread(sv, sizeof(struct Student), 100, file);
    fclose(file);
}

// ham ghi danh sach sinh vien vao file
void saveStudent(struct Student *sv, int numberStudent) {
    FILE *file = fopen("student.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(sv, sizeof(struct Student), numberStudent, file);
    fclose(file);
}

void startTheProgram(int *choiceSystem) {
    printf("*** SU DUNG HE THONG QUAN LY SINH VIEN C***\n\n");
    printf("\t\tCHON VAI TRO CUA BAN\n");
    printf("\t========================\n");
    printf("\t[1] Quan tri vien.\n");
    printf("\t[0] Thoat khoi truong trinh.\n");
    printf("\t========================\n");
    printf("\tNhap lua chon cua ban: ");
    scanf("%d", choiceSystem);
}

// ket thuc chuong trinh
void endTheProgram(int *flag) {
    printf("\t========= Thank You =========\n");
    printf("\t========= See You Soon ======\n\n");
    *flag = 0;
}

// ham menu chinh
void startMenu(int *choiceMenu) {
    printf("*** SU DUNG HE THONG QUAN LY SINH VIEN TRONG C***\n\n");
    printf("\t\tMENU\n");
    printf("\t===========================\n");
    printf("\t[1] Quan ly sinh vien.\n");
    printf("\t[2] Quan ly lop hoc (Dang phat trien).\n");
    printf("\t[3] Quan ly giao vien.\n");
    printf("\t[4] Huong dan su dung.\n");
    printf("\t[5] Ve chung toi.\n");
    printf("\t[0] Thoat khoi chuong trinh.\n");
    printf("\t===========================\n");
    printf("\tNhap lua chon cua ban: ");
    scanf("%d", choiceMenu);
}

void startStudentMenu(int *choiceStudentMenu) {
    printf("*** SU DUNG HE THONG QUAN LY SINH VIEN C***\n\n");
    printf("\t\tSTUDENT MENU\n");
    printf("\t=======================\n");
    printf("\t[1] Them mot sinh vien moi.\n");
    printf("\t[2] Hien thi danh sach sinh vien.\n");
    printf("\t[3] Sua sinh vien.\n");
    printf("\t[4] Xoa sinh vien.\n");
    printf("\t[5] Tim kiem sinh vien theo ten.\n");
    printf("\t[6] Sap xep danh sach sinh vien theo ten.\n");
    printf("\t[0] Thoat khoi truong trinh.\n");
    printf("\t========================\n");
    printf("\tNhap lua chon cua ban: ");
    scanf("%d", choiceStudentMenu);
}

// hien thi danh sach sinh vien
char showAllStudent(int *numberStudent, struct Student *sv) {
    if (*numberStudent == 0) {
        printf("\t\t**** Danh Sach Sinh Vien Trong **** \n\n");
        return 1;
    }

    printf("\t\t\t**** All Student **** \n\n");
    printf("|==========|====================|=========================|===============|===========|\n");
    printf("|    ID    |        Name        |          Email          |     Phone     | NO.Course |\n");
    printf("|==========|====================|=========================|===============|===========|\n");

    for (int i = 0; i < *numberStudent; i++) {
        printf("| %-8s | %-18s | %-23s | %-15s | %-9d |\n", 
                sv[i].studentId, 
                sv[i].studentName, 
                sv[i].email, 
                sv[i].phone, 
                sv[i].courseCount);
        printf("|----------|--------------------|-------------------------|---------------|-----------|\n");
    }

    return 0;
}

// them sinh vien moi
char addANewStudent(int *numberStudent, struct Student *sv, struct Student *sv1) {
    printf("Nhap thong tin sinh vien moi:\n");

    do {
        printf("Ma sinh vien: ");
        scanf("%s", sv1->studentId);
    } while (!isValidStudentId(sv1->studentId));

    while (getchar() != '\n');

    printf("Ten sinh vien: ");
    fgets(sv1->studentName, sizeof(sv1->studentName), stdin);
    strtok(sv1->studentName, "\n");

    printf("Ma lop: ");
    fgets(sv1->classroomId, sizeof(sv1->classroomId), stdin);
    strtok(sv1->classroomId, "\n");

    printf("Ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &sv1->dateOfBirth.day, &sv1->dateOfBirth.month, &sv1->dateOfBirth.year);
    while (getchar() != '\n');

    printf("Gioi tinh (1: Nam, 0: Nu): ");
    scanf("%d", &sv1->gender);
    while (getchar() != '\n');

    do {
        printf("Email: ");
        fgets(sv1->email, sizeof(sv1->email), stdin);
        strtok(sv1->email, "\n");
    } while (!isValidEmail(sv1->email));

    do {
        printf("Sdt: ");
        fgets(sv1->phone, sizeof(sv1->phone), stdin);
        strtok(sv1->phone, "\n");
    } while (!isValidPhoneNumber(sv1->phone) || !isPhoneNumberUnique(sv1->phone, sv, *numberStudent));

    printf("So khoa hoc: ");
    scanf("%d", &sv1->courseCount);

    sv[*numberStudent] = *sv1;
    (*numberStudent)++;

    saveStudent(sv, *numberStudent);

    return 0;
}

// kiem tra xem ma sinh vien co hop le hay khong
int isValidStudentId(char *studentId) {
    if (strlen(studentId) < 5) {
        printf("Ma sinh vien phai co do dai toi thieu 5 ky tu.\n");
        return 0;
    }
    return 1;
}

// kiem tra xem email co hop le hay khong
int isValidEmail(char *email) {
    if (strstr(email, "@gmail") == NULL || strstr(email, ".com") == NULL) {
        printf("Email phai ket thuc bang @gmail.com.\n");
        return 0;
    }
    return 1;
}

// kiem tra xem sdt co hop le hay khong
int isValidPhoneNumber(char *phone) {
    if (phone[0] != '0') {
        printf("So dien thoai phai bat dau bang so 0.\n");
        return 0;
    }
    if (strlen(phone) < 10 || strlen(phone) > 11) {
        printf("So dien thoai phai co do dai tu 10 den 11 ky tu.\n");
        return 0;
    }
    return 1;
}

// kiem tra sdt co phai la so duy nhat hay khong
int isPhoneNumberUnique(char *phone, struct Student *sv, int numberStudent) {
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].phone, phone) == 0) {
            printf("So dien thoai nay da ton tai trong danh sach.\n");
            return 0;
        }
    }
    return 1;
}

char editStudent(int *numberStudent, struct Student *sv) {
    char studentId[20];
    printf("Nhap ma sinh vien can sua: ");
    scanf("%s", studentId);
    getchar();

    for (int i = 0; i < *numberStudent; i++) {
        if (strcmp(sv[i].studentId, studentId) == 0) {
            printf("Sua thong tin sinh vien %s:\n", sv[i].studentName);

            printf("Nhap ten moi: ");
            fgets(sv[i].studentName, sizeof(sv[i].studentName), stdin);
            strtok(sv[i].studentName, "\n");

            printf("Nhap ma lop moi: ");
            scanf("%s", sv[i].classroomId);
            getchar();

            printf("Nhap ngay sinh moi (dd mm yyyy): ");
            scanf("%d %d %d", &sv[i].dateOfBirth.day, &sv[i].dateOfBirth.month, &sv[i].dateOfBirth.year);
            getchar();

            printf("Nhap gioi tinh moi (1: Nam, 0: Nu): ");
            scanf("%d", &sv[i].gender);
            getchar();

            printf("Nhap email moi: ");
            fgets(sv[i].email, sizeof(sv[i].email), stdin);
            strtok(sv[i].email, "\n");

            printf("Nhap sdt moi: ");
            fgets(sv[i].phone, sizeof(sv[i].phone), stdin);
            strtok(sv[i].phone, "\n");

            saveStudent(sv, *numberStudent);

            printf("Sua thong tin sinh vien thanh cong.\n");
            return 0;
        }
    }

    printf("Sinh vien khong ton tai.\n");
    return 1;
}

// ham xoa sinh vien  
char deleteStudent(int *numberStudent, struct Student *sv) {
    char studentId[20];
    printf("Nhap ma sinh vien can xoa: ");
    scanf("%s", studentId);

    for (int i = 0; i < *numberStudent; i++) {
        if (strcmp(sv[i].studentId, studentId) == 0) { // so sanh 2 chuoi 
            // yeu cau xac nhan tu nguoi dung
            char confirm[3];
            printf("Ban co chac chan muon xoa sinh vien %s (Co/Khong)? ", sv[i].studentName);
            scanf("%s", confirm); // doc cau tra loi "Co" hoac "Khong"

            // Kiem tra nguoi dung co tra loi co "Co"
            if (strcmp(confirm, "Co") == 0 || strcmp(confirm, "co") == 0) {
                // xoa sinh vien
                for (int j = i; j < *numberStudent - 1; j++) {
                    sv[j] = sv[j + 1]; // di chuyen sinh vien phia sau len
                }
                (*numberStudent)--; // giam so luong sinh vien
                saveStudent(sv, *numberStudent); // luu lai danh sach sinh vien
                printf("Sinh vien da duoc xoa.\n");
                return 0;
            } else {
                printf("Xoa sinh vien bi huy.\n");
                return 1;
            }
        }
    }

    printf("Sinh vien khong ton tai.\n");
    return 1;
}

// tim kiem sinh vien theo ten  
char searchStudentByName(int *numberStudent, struct Student *sv) {
    char name[50];
    printf("Nhap ten sinh vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");

    printf("|==========|====================|=========================|===============|===========|\n");
    printf("|    ID    |        Name        |          Email          |     Phone     | NO.Course |\n");
    printf("|==========|====================|=========================|===============|===========|\n");

    for (int i = 0; i < *numberStudent; i++) {
        if (strstr(sv[i].studentName, name) != NULL) {
            printf("| %-8s | %-18s | %-23s | %-15s | %-9d |\n", 
                    sv[i].studentId, 
                    sv[i].studentName, 
                    sv[i].email, 
                    sv[i].phone, 
                    sv[i].courseCount);
            printf("|----------|--------------------|-------------------------|---------------|-----------|\n");
        }
    }

    return 0;
}

// ham so sanh ten sinh vien A-Z
int compareStudentNameAscending(const void *a, const void *b) {
    return strcmp(((struct Student *)a)->studentName, ((struct Student *)b)->studentName);
}

// ham so sanh ten sinh vien Z-A  
int compareStudentNameDescending(const void *a, const void *b) {
    return strcmp(((struct Student *)b)->studentName, ((struct Student *)a)->studentName);
}

void sortStudentsByName(int *numberStudent, struct Student *sv, int order) {
    if (order == 1) { // A-Z
        qsort(sv, *numberStudent, sizeof(struct Student), compareStudentNameAscending);
    } else if (order == 2) {  // Z-A
        qsort(sv, *numberStudent, sizeof(struct Student), compareStudentNameDescending);
    }
}






void getTeacherByFile(int *numberTeacher, struct Teacher *gv) {
    FILE *file = fopen("teacher.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file. Khoi tao danh sach rong.\n");
        *numberTeacher = 0;
        return;
    }
    *numberTeacher = fread(gv, sizeof(struct Teacher), 100, file);
    fclose(file);
}

void saveTeacher(struct Teacher *gv, int numberTeacher) {
    FILE *file = fopen("teacher.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(gv, sizeof(struct Teacher), numberTeacher, file);
    fclose(file);
}

void startTeacherMenu(int *choiceTeacherMenu) {
    printf("*** SU DUNG HE THONG QUAN LY GIAO VIEN ***\n\n");
    printf("\t\tTEACHER MENU\n");
    printf("\t=======================\n");
    printf("\t[1] Them mot giao vien moi.\n");
    printf("\t[2] Hien thi danh sach giao vien.\n");
    printf("\t[3] Sua giao vien.\n");
    printf("\t[4] Xoa giao vien.\n");
    printf("\t[5] Tim kiem giao vien theo ten.\n");
    printf("\t[0] Thoat khoi truong trinh.\n");
    printf("\t========================\n");
    printf("\tNhap lua chon cua ban: ");
    scanf("%d", choiceTeacherMenu);
}

char addANewTeacher(int *numberTeacher, struct Teacher *gv, struct Teacher *gv1) {
    printf("Nhap thong tin giao vien moi:\n");
    
    printf("Ma giao vien: ");
    scanf("%s", gv1->teacherId);
    while (getchar() != '\n');

    printf("Ten giao vien: ");
    fgets(gv1->teacherName, sizeof(gv1->teacherName), stdin);
    strtok(gv1->teacherName, "\n");

    printf("Bo mon: ");
    fgets(gv1->subject, sizeof(gv1->subject), stdin);
    strtok(gv1->subject, "\n");

    printf("Email: ");
    fgets(gv1->email, sizeof(gv1->email), stdin);
    strtok(gv1->email, "\n");

    printf("Sdt: ");
    fgets(gv1->phone, sizeof(gv1->phone), stdin);
    strtok(gv1->phone, "\n");

    gv[*numberTeacher] = *gv1;
    (*numberTeacher)++;

    saveTeacher(gv, *numberTeacher);

    return 0;
}

char showAllTeacher(int *numberTeacher, struct Teacher *gv) {
    if (*numberTeacher == 0) {
        printf("\t\t**** Danh Sach Giao Vien Trong **** \n\n");
        return 1;
    }

    printf("\t\t\t**** All Teachers **** \n\n");
    printf("|==========|====================|====================|=========================|===============|\n");
    printf("|    ID    |        Name        |      Subject       |          Email          |     Phone     |\n");
    printf("|==========|====================|====================|=========================|===============|\n");

    for (int i = 0; i < *numberTeacher; i++) {
        printf("| %-8s | %-18s | %-18s | %-23s | %-15s |\n", 
                gv[i].teacherId, 
                gv[i].teacherName, 
                gv[i].subject, 
                gv[i].email, 
                gv[i].phone);
        printf("|----------|--------------------|--------------------|-------------------------|---------------|\n");
    }

    return 0;
}

char editTeacher(int *numberTeacher, struct Teacher *gv) {
    char teacherId[20];
    printf("Nhap ma giao vien can sua: ");
    scanf("%s", teacherId);
    getchar();

    for (int i = 0; i < *numberTeacher; i++) {
        if (strcmp(gv[i].teacherId, teacherId) == 0) {
            printf("Sua thong tin giao vien %s:\n", gv[i].teacherName);

            printf("Nhap ten moi: ");
            fgets(gv[i].teacherName, sizeof(gv[i].teacherName), stdin);
            strtok(gv[i].teacherName, "\n");

            printf("Nhap bo mon moi: ");
            fgets(gv[i].subject, sizeof(gv[i].subject), stdin);
            strtok(gv[i].subject, "\n");

            printf("Nhap email moi: ");
            fgets(gv[i].email, sizeof(gv[i].email), stdin);
            strtok(gv[i].email, "\n");

            printf("Nhap sdt moi: ");
            fgets(gv[i].phone, sizeof(gv[i].phone), stdin);
            strtok(gv[i].phone, "\n");

            saveTeacher(gv, *numberTeacher);

            printf("Sua thong tin giao vien thanh cong.\n");
            return 0;
        }
    }

    printf("Giao vien khong ton tai.\n");
    return 1;
}

char deleteTeacher(int *numberTeacher, struct Teacher *gv) {
    char teacherId[20];
    printf("Nhap ma giao vien can xoa: ");
    scanf("%s", teacherId);

    for (int i = 0; i < *numberTeacher; i++) {
        if (strcmp(gv[i].teacherId, teacherId) == 0) {
            char confirm[3];
            printf("Ban co chac chan muon xoa giao vien %s (Co/Khong)? ", gv[i].teacherName);
            scanf("%s", confirm);

            if (strcmp(confirm, "Co") == 0 || strcmp(confirm, "co") == 0) {
                for (int j = i; j < *numberTeacher - 1; j++) {
                    gv[j] = gv[j + 1];
                }
                (*numberTeacher)--;
                saveTeacher(gv, *numberTeacher);
                printf("Giao vien da duoc xoa.\n");
                return 0;
            } else {
                printf("Xoa giao vien bi huy.\n");
                return 1;
            }
        }
    }

    printf("Giao vien khong ton tai.\n");
    return 1;
}

char searchTeacherByName(int *numberTeacher, struct Teacher *gv) {
    char name[50];
    printf("Nhap ten giao vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    strtok(name, "\n");

    printf("|==========|====================|====================|=========================|===============|\n");
    printf("|    ID    |        Name        |      Subject       |          Email          |     Phone     |\n");
    printf("|==========|====================|====================|=========================|===============|\n");

    for (int i = 0; i < *numberTeacher; i++) {
        if (strstr(gv[i].teacherName, name) != NULL) {
            printf("| %-8s | %-18s | %-18s | %-23s | %-15s |\n", 
                    gv[i].teacherId, 
                    gv[i].teacherName, 
                    gv[i].subject, 
                    gv[i].email, 
                    gv[i].phone);
            printf("|----------|--------------------|-------------------------|---------------|-----------|\n");
        }
    }

    return 0;
}

