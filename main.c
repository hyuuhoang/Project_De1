#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
    int choiceSystem = -1;
    int choiceMenu = -1;
    int choiceStudentMenu = -1;
    int numberStudent = 0;
    struct Student sv[100], sv1;
    
    int choiceTeacherMenu = -1;
    int numberTeacher = 0;
    struct Teacher gv[100], gv1;
    

    
    // lay thong tin tu file
    getStudentByFile(&numberStudent, sv);
    getTeacherByFile(&numberTeacher, gv);

    startTheProgram(&choiceSystem);

    while (1) { 
        if (choiceSystem < 0 || choiceSystem > 3) {
            printf("Lua chon khong hop le. Vui long nhap lai.\n");
            startTheProgram(&choiceSystem);
        }

        if (choiceSystem == 0) { 
            endTheProgram(&choiceSystem);
            break;
        } else if (choiceSystem == 1) { // Quan tri vien
            while (choiceMenu != 0) {
                startMenu(&choiceMenu);

                if (choiceMenu == 1) { // Quan ly sinh vien
                    while (choiceStudentMenu != 0) {
                        startStudentMenu(&choiceStudentMenu);

                        if (choiceStudentMenu == 1) { // Them sinh vien moi
                            addANewStudent(&numberStudent, sv, &sv1);
                        } else if (choiceStudentMenu == 2) { // hien thi danh sach sinh vien
                            showAllStudent(&numberStudent, sv);
                        } else if (choiceStudentMenu == 3) { // sua thong tin sinh vien
                            editStudent(&numberStudent, sv);
                        } else if (choiceStudentMenu == 4) { // Xoa sinh vien
                            deleteStudent(&numberStudent, sv);
                        } else if (choiceStudentMenu == 5) { // tim kiem sinh vien theo ten
                            searchStudentByName(&numberStudent, sv);
                        } else if (choiceStudentMenu == 6) { // sap xep sinh vien theo ten 
                            int order;
                            printf("Chon thu tu sap xep:\n");
                            printf("[1] A-Z\n");
                            printf("[2] Z-A\n");
                            printf("Nhap lua chon: ");
                            scanf("%d", &order);
                            sortStudentsByName(&numberStudent, sv, order);
                            showAllStudent(&numberStudent, sv);
                        }
                    }
                } else if (choiceMenu == 2) { // Quan ly lop hoc
                    printf("Chuc nang Quan ly lop hoc dang phat trien.\n");
                } else if (choiceMenu == 3) { // quan ly giao vien
                    while (choiceTeacherMenu != 0) {
                        startTeacherMenu(&choiceTeacherMenu);

                        if (choiceTeacherMenu == 1) { // Them giao vien moi
                            addANewTeacher(&numberTeacher, gv, &gv1);
                        } else if (choiceTeacherMenu == 2) { // Hien thi danh sach giao vien
                            showAllTeacher(&numberTeacher, gv);
                        } else if (choiceTeacherMenu == 3) { // Sua thong tin giao vien
                            editTeacher(&numberTeacher, gv);
                        } else if (choiceTeacherMenu == 4) { // Xoa giao vien
                            deleteTeacher(&numberTeacher, gv);
                        } else if (choiceTeacherMenu == 5) { // Tim kiem giao vien theo ten
                            searchTeacherByName(&numberTeacher, gv);
                        }
                    }
                } else if (choiceMenu == 4) { // huong dan su dung
                    printf("Chuc nang Huong dan su dung dang phat trien.\n");
                } else if (choiceMenu == 5) { // Gioi thieu ve chung toi
                    printf("Chuc nang 'Ve chung toi' dang phat trien.\n");
                } else if (choiceMenu == 0) { // Thoat
                    endTheProgram(&choiceSystem);
                }
            }
        } else if (choiceSystem == 2) { 
            printf("Lua chon khong hop le. Vui long nhap lai.\n");
            startTheProgram(&choiceSystem); 
        } else if (choiceSystem == 3) {
            printf("Lua chon khong hop le. Vui long nhap lai.\n");
            startTheProgram(&choiceSystem); 
        }
    }

    return 0;
}

