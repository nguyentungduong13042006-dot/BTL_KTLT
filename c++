#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

// --- 1. LOP GOI CUOC (Use Case 1: CRUD Gói Cu?c) ---
class GoiCuoc {
private:
    string maGoi;
    string tenGoi;
    double giaCuoc;
    int dungLuongData;

public:
    GoiCuoc() : maGoi(""), tenGoi(""), giaCuoc(0), dungLuongData(0) {}
    GoiCuoc(string ma, string ten, double gia, int data) 
        : maGoi(ma), tenGoi(ten), giaCuoc(gia), dungLuongData(data) {}

    string getMaGoi() const { return maGoi; }

    void nhap() {
        cout << "Nhap ma goi cuoc: "; cin >> maGoi;
        cout << "Nhap ten goi cuoc: "; cin.ignore(); getline(cin, tenGoi);
        cout << "Nhap gia cuoc (VND): "; cin >> giaCuoc;
        cout << "Nhap dung luong Data (GB): "; cin >> dungLuongData;
    }

    void xuat() const {
        cout << left << setw(10) << maGoi 
             << setw(20) << tenGoi 
             << setw(15) << fixed << setprecision(0) << giaCuoc 
             << setw(10) << dungLuongData << "GB\n";
    }

    void ghiFile(ofstream &fout) const {
        fout << maGoi << "\n" << tenGoi << "\n" << giaCuoc << "\n" << dungLuongData << "\n";
    }

    void docFile(ifstream &fin) {
        fin >> maGoi;
        fin.ignore();
        getline(fin, tenGoi);
        fin >> giaCuoc >> dungLuongData;
    }
};

// --- 2. LOP THUE BAO (Use Case 2: CRUD Thuê Bao) ---
class ThueBao {
private:
    string soDienThoai;
    string tenChuSoHuu;
    string maGoiDangKy;
    string loaiHinh; // "TraTruoc" ho?c "TraSau"

public:
    ThueBao() : soDienThoai(""), tenChuSoHuu(""), maGoiDangKy(""), loaiHinh("") {}
    ThueBao(string sdt, string ten, string maGoi, string loai)
        : soDienThoai(sdt), tenChuSoHuu(ten), maGoiDangKy(maGoi), loaiHinh(loai) {}

    string getSoDienThoai() const { return soDienThoai; }

    void nhap() {
        cout << "Nhap so dien thoai: "; cin >> soDienThoai;
        cout << "Nhap ten chu thue bao: "; cin.ignore(); getline(cin, tenChuSoHuu);
        cout << "Nhap ma goi cuoc dang ky: "; cin >> maGoiDangKy;
        cout << "Nhap loai hinh (1. Tra truoc / 2. Tra sau): ";
        int chon; cin >> chon;
        loaiHinh = (chon == 1) ? "TraTruoc" : "TraSau";
    }

    void xuat() const {
        cout << left << setw(15) << soDienThoai 
             << setw(20) << tenChuSoHuu 
             << setw(15) << maGoiDangKy 
             << setw(15) << loaiHinh << "\n";
    }

    void ghiFile(ofstream &fout) const {
        fout << soDienThoai << "\n" << tenChuSoHuu << "\n" << maGoiDangKy << "\n" << loaiHinh << "\n";
    }

    void docFile(ifstream &fin) {
        fin >> soDienThoai;
        fin.ignore();
        getline(fin, tenChuSoHuu);
        fin >> maGoiDangKy >> loaiHinh;
    }
};

// --- QU?N LƯ DANH SÁCH & FILE ---
vector<GoiCuoc> danhSachGoiCuoc;
vector<ThueBao> danhSachThueBao;

void docDuLieuFile() {
    ifstream fGoi("goicuoc.txt");
    if (fGoi.is_open()) {
        int n;
        if (fGoi >> n) {
            danhSachGoiCuoc.resize(n);
            for (int i = 0; i < n; ++i) danhSachGoiCuoc[i].docFile(fGoi);
        }
        fGoi.close();
    }

    ifstream fTB("thuebao.txt");
    if (fTB.is_open()) {
        int n;
        if (fTB >> n) {
            danhSachThueBao.resize(n);
            for (int i = 0; i < n; ++i) danhSachThueBao[i].docFile(fTB);
        }
        fTB.close();
    }
}

void ghiDuLieuFile() {
    ofstream fGoi("goicuoc.txt");
    if (fGoi.is_open()) {
        fGoi << danhSachGoiCuoc.size() << "\n";
        for (size_t i = 0; i < danhSachGoiCuoc.size(); ++i) {
            danhSachGoiCuoc[i].ghiFile(fGoi);
        }
        fGoi.close();
    }

    ofstream fTB("thuebao.txt");
    if (fTB.is_open()) {
        fTB << danhSachThueBao.size() << "\n";
        for (size_t i = 0; i < danhSachThueBao.size(); ++i) {
            danhSachThueBao[i].ghiFile(fTB);
        }
        fTB.close();
    }
}

// --- CÁC HÀM CRUD GÓI CU?C ---
void menuGoiCuoc() {
    int chon;
    do {
        cout << "\n--- QUAN LY GOI CUOC (CRUD) ---\n";
        cout << "1. Them goi cuoc\n2. Xem danh sach goi cuoc\n3. Tim kiem goi cuoc\n4. Xoa goi cuoc\n0. Quay lai\n";
        cout << "Lua chon cua ban: "; cin >> chon;
        if (chon == 1) {
            GoiCuoc g; g.nhap();
            danhSachGoiCuoc.push_back(g);
            ghiDuLieuFile();
            cout << "Them thanh cong!\n";
        } else if (chon == 2) {
            cout << left << setw(10) << "Ma Goi" << setw(20) << "Ten Goi" << setw(15) << "Gia (VND)" << setw(10) << "Data\n";
            for (size_t i = 0; i < danhSachGoiCuoc.size(); ++i) danhSachGoiCuoc[i].xuat();
        } else if (chon == 3) {
            string ma; cout << "Nhap ma goi can tim: "; cin >> ma;
            bool found = false;
            for (size_t i = 0; i < danhSachGoiCuoc.size(); ++i) {
                if (danhSachGoiCuoc[i].getMaGoi() == ma) {
                    danhSachGoiCuoc[i].xuat(); found = true; break;
                }
            }
            if (!found) cout << "Khong tim thay!\n";
        } else if (chon == 4) {
            string ma; cout << "Nhap ma goi can xoa: "; cin >> ma;
            bool found = false;
            for (vector<GoiCuoc>::iterator it = danhSachGoiCuoc.begin(); it != danhSachGoiCuoc.end(); ++it) {
                if (it->getMaGoi() == ma) {
                    danhSachGoiCuoc.erase(it);
                    ghiDuLieuFile();
                    cout << "Da xoa thanh cong!\n"; found = true; break;
                }
            }
            if (!found) cout << "Khong tim thay ma goi nay!\n";
        }
    } while (chon != 0);
}


void menuThueBao() {
    int chon;
    do {
        cout << "\n--- QUAN LY THUE BAO (CRUD) ---\n";
        cout << "1. Them thue bao\n2. Xem danh sach thue bao\n3. Tim kiem thue bao\n4. Xoa thue bao\n0. Quay lai\n";
        cout << "Lua chon cua ban: "; cin >> chon;
        if (chon == 1) {
            ThueBao tb; tb.nhap();
            danhSachThueBao.push_back(tb);
            ghiDuLieuFile();
            cout << "Them thanh cong!\n";
        } else if (chon == 2) {
            cout << left << setw(15) << "SDT" << setw(20) << "Chu Thue Bao" << setw(15) << "Ma Goi" << setw(15) << "Loai Hinh\n";
            for (size_t i = 0; i < danhSachThueBao.size(); ++i) danhSachThueBao[i].xuat();
        } else if (chon == 3) {
            string sdt; cout << "Nhap so dien thoai can tim: "; cin >> sdt;
            bool found = false;
            for (size_t i = 0; i < danhSachThueBao.size(); ++i) {
                if (danhSachThueBao[i].getSoDienThoai() == sdt) {
                    danhSachThueBao[i].xuat(); found = true; break;
                }
            }
            if (!found) cout << "Khong tim thay thue bao!\n";
        } else if (chon == 4) {
            string sdt; cout << "Nhap so dien thoai can xoa: "; cin >> sdt;
            bool found = false;
            for (vector<ThueBao>::iterator it = danhSachThueBao.begin(); it != danhSachThueBao.end(); ++it) {
                if (it->getSoDienThoai() == sdt) {
                    danhSachThueBao.erase(it);
                    ghiDuLieuFile();
                    cout << "Da xoa thanh cong!\n"; found = true; break;
                }
            }
            if (!found) cout << "Khong tim thay so dien thoai nay!\n";
        }
    } while (chon != 0);
}


int main() {
    docDuLieuFile();
    int choice;
    do {
        cout << "\n============================================\n";
        cout << "   HE THONG QUAN LY GOI CUOC & THUE BAO     \n";
        cout << "============================================\n";
        cout << "1. Quan ly Goi Cuoc \n";
        cout << "2. Quan ly Thue Bao \n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Nhap lua chon cua ban: "; cin >> choice;

        if (choice == 1) {
            menuGoiCuoc();
        } else if (choice == 2) {
            menuThueBao();
        }
    } while (choice != 0);

    return 0;
}
