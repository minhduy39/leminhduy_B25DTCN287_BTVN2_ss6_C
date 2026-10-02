#include <stdio.h>
#include <string.h>

#define MAX 100
#define PHI_PHAT_NGAY 5000
#define HAN_MUON 14

int main(void) {
    char maPhieu[MAX][15];
    char tenSach[MAX][50];
    int soNgayMuon[MAX];
    int tienPhat[MAX];
    
    int soLuong = 0;
    int luaChon;

    do {
        printf("\n================ HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ================\n");
        printf("1. Them luot muon sach moi\n");
        printf("2. Hien thi danh sach muon sach\n");
        printf("3. Cap nhat so ngay muon theo Ma phieu\n");
        printf("4. Xoa luot muon sach theo Ma phieu\n");
        printf("5. Thong ke danh sach phieu muon bi phat (Qua han > 14 ngay)\n");
        printf("6. Thoat chuong trinh\n");
        printf("==============================================================================\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long thu lai!\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (luaChon) {
            case 1: {
                printf("\n=== THEM LUOT MUON SACH MOI ===\n");
                if (soLuong >= MAX) {
                    printf("He thong day, khong the them phieu muon moi!\n");
                    break;
                }

                char maMoi[15];
                int maTrungLap;

                do {
                    maTrungLap = 0;
                    printf("Nhap ma phieu muon (khong chua khoang trang): ");
                    scanf("%14s", maMoi);
                    while (getchar() != '\n');

                    for (int i = 0; i < soLuong; i++) {
                        if (strcmp(maPhieu[i], maMoi) == 0) {
                            printf("Loi: Ma phieu '%s' da ton tai trong he thong! Vui long nhap ma khac.\n", maMoi);
                            maTrungLap = 1;
                            break;
                        }
                    }
                } while (maTrungLap == 1);

                strcpy(maPhieu[soLuong], maMoi);

                printf("Nhap ten sach: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                
                size_t len = strlen(tenSach[soLuong]);
                if (len > 0 && tenSach[soLuong][len - 1] == '\n') {
                    tenSach[soLuong][len - 1] = '\0';
                }

                int ngay;
                do {
                    printf("Nhap so ngay muon thuc te (> 0): ");
                    if (scanf("%d", &ngay) != 1 || ngay <= 0) {
                        printf("Loi: So ngay muon phai la so nguyen duong!\n");
                        while (getchar() != '\n');
                        ngay = -1;
                    } else {
                        while (getchar() != '\n');
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;

                if (ngay > HAN_MUON) {
                    tienPhat[soLuong] = (ngay - HAN_MUON) * PHI_PHAT_NGAY;
                } else {
                    tienPhat[soLuong] = 0;
                }

                printf("\n--> Tien phat tu dong tinh: %d VND\n", tienPhat[soLuong]);
                soLuong++;
                printf("--> Them luot muon sach thanh cong!\n");
                break;
            }

            case 2: {
                printf("\n================================ DANH SACH MUON SACH ================================\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                printf("%-5s | %-12s | %-35s | %-10s | %-15s\n", "STT", "Ma Phieu", "Ten Sach", "So Ngay", "Tien Phat (VND)");
                printf("-------------------------------------------------------------------------------------\n");

                long long tongTienPhat = 0;
                for (int i = 0; i < soLuong; i++) {
                    printf("%-5d | %-12s | %-35s | %-10d | %-15d\n", 
                           i + 1, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    tongTienPhat += tienPhat[i];
                }

                printf("-------------------------------------------------------------------------------------\n");
                printf("Tong tien phat toan he thong: %lld VND\n", tongTienPhat);
                break;
            }

            case 3: {
                printf("\n=== CAP NHAT SO NGAY MUON ===\n");
                if (soLuong == 0) {
                    printf("Danh sach hien dang rong, khong the cap nhat!\n");
                    break;
                }

                char maTim[15];
                printf("Nhap ma phieu muon can cap nhat: ");
                scanf("%14s", maTim);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maTim) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", maTim);
                } else {
                    printf("Tim thay phieu muon cua sach: %s (So ngay hien tai: %d)\n", tenSach[index], soNgayMuon[index]);

                    int ngayMoi;
                    do {
                        printf("Nhap so ngay muon thuc te moi (> 0): ");
                        if (scanf("%d", &ngayMoi) != 1 || ngayMoi <= 0) {
                            printf("Loi: So ngay muon phai la so nguyen duong!\n");
                            while (getchar() != '\n');
                            ngayMoi = -1;
                        } else {
                            while (getchar() != '\n');
                        }
                    } while (ngayMoi <= 0);

                    soNgayMuon[index] = ngayMoi;
                    if (ngayMoi > HAN_MUON) {
                        tienPhat[index] = (ngayMoi - HAN_MUON) * PHI_PHAT_NGAY;
                    } else {
                        tienPhat[index] = 0;
                    }

                    printf("\n--> Tien phat moi: %d VND\n", tienPhat[index]);
                    printf("--> Cap nhat so ngay muon thanh cong!\n");
                }
                break;
            }

            case 4: {
                printf("\n=== XOA LUOT MUON SACH ===\n");
                if (soLuong == 0) {
                    printf("Danh sach hien dang rong, khong the xoa!\n");
                    break;
                }

                char maXoa[15];
                printf("Nhap ma phieu muon can xoa: ");
                scanf("%14s", maXoa);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], maXoa) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", maXoa);
                } else {
                    for (int i = index; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                        tienPhat[i] = tienPhat[i + 1];
                    }

                    soLuong--;
                    printf("Xoa phieu muon '%s' thanh cong!\n", maXoa);
                }
                break;
            }

            case 5: {
                printf("\n================ DANH SACH PHIEU MUON QUA HAN (> 14 NGAY) ================\n");
                int demQuaHan = 0;

                for (int i = 0; i < soLuong; i++) {
                    if (soNgayMuon[i] > HAN_MUON) {
                        if (demQuaHan == 0) {
                            printf("%-5s | %-12s | %-35s | %-10s | %-15s\n", "STT", "Ma Phieu", "Ten Sach", "So Ngay", "Tien Phat (VND)");
                            printf("-------------------------------------------------------------------------------------\n");
                        }
                        demQuaHan++;
                        printf("%-5d | %-12s | %-35s | %-10d | %-15d\n", 
                               demQuaHan, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    }
                }

                if (demQuaHan == 0) {
                    printf("Khong co luot muon nao bi qua han phat!\n");
                } else {
                    printf("-------------------------------------------------------------------------------------\n");
                    printf("Tong so luot muon bi qua han: %d phieu\n", demQuaHan);
                }
                break;
            }

            case 6:
                printf("\nCam on ban da su dung HE THONG QUAN LY MUON TRA SACH (LIBRARY_WMS)!\n");
                printf("Tam biet va hen gap lai.\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                break;
        }

    } while (luaChon != 6);

    return 0;
}
