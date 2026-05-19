#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

// Khởi tạo số lượng dsk, dsc và mtk tối đa cho phép
const int MAXDSK = 10;
const int MAXMTK = 10;
const int MAXDSC = MAXDSK * MAXDSK;

struct Node {
    int dinhke;
    int trongso = 0;
    Node* link;
};
typedef Node* Nodeptr;

struct DanhSachKe {
    int sodinh = 0;
    Nodeptr dsk[MAXDSK];
};

struct Canh {
    int dinhdau;
    int dinhcuoi;
    int trongso;
};

struct DanhSachCanh {
    int socanh = 0;
    Canh dsc[MAXDSC];
};

struct MaTranKe {
    int sodinh = 0;
    int mtk[MAXMTK][MAXMTK];
};

// đọc file 
void docfile_dsk(DanhSachKe& dsk, const char* duongdan, int cotrongso);
void docfile_mtk(MaTranKe& mtk, const char* duongdan);

// duyệt dsk và mtk và dsc
void duyet_dsk(DanhSachKe dsk);
void duyet_mtk(MaTranKe mtk);
void duyet_canh(Canh c);
void duyet_dsc(DanhSachCanh dsc);

// làm mới visited
void lammoivisited(bool visited[], int n);

// B. Chuyển đổi câu trúc 
// 1 Chuyển mtk sang dsk
DanhSachKe chuyen_mtk_sang_dsk(MaTranKe mtk);
// 2 Chuyển mtk sang dsc
DanhSachCanh chuyen_mtk_sang_dsc(MaTranKe mtk);
// 3 Chuyển dsk sang mtk
MaTranKe chuyen_dsk_sang_mtk(DanhSachKe dsk);
// 4 Chuyển dsk sang dsc
DanhSachCanh chuyen_dsk_sang_dsc(DanhSachKe dsk);
// 5 Chuyển dsc và 1 đỉnh sang mtk
MaTranKe chuyen_dsc_sang_mtk(DanhSachCanh dsc, int sodinh);
// 6 Chuyển dsc và 1 đỉnh sang dsk
DanhSachKe chuyen_dsc_sang_dsk(DanhSachCanh dsc, int sodinh);  

// C. Tính bậc
// 1 Viết hàm tính bậc vào của 1 đỉnh dsk
int bacvao_dsk(DanhSachKe dsk, int u);
// 2 Viết hàm tính bậc ra của 1 đỉnh dsk
int bacra_dsk(DanhSachKe dsk, int u);
// 3 Viết hàm tính bậc vào của 1 dỉnh mtk
int bacvao_mtk(MaTranKe mtk, int u);
// 4 Viết hàm tính bậc ra của 1 đỉnh mtk
int bacra_mtk(MaTranKe mtk, int u);
// 5 Viết hàm trả về đỉnh có bậc lớn nhất mtk
int baclonnhat_mtk(MaTranKe mtk);
// 6 Viết hàm trả về đỉnh có bậc nhỏ nhất mtk
int bacnhonhat_mtk(MaTranKe mtk);
// 7 Viết hàm trả về đỉnh có bậc lớn nhất dsk
int baclonnhat_dsk(DanhSachKe dsk);
// 8 Viết hàm trả về đỉnh có bậc nhỏ nhất dsk
int bacnhonhat_dsk(DanhSachKe dsk);
// 9 Viết hàm tìm đỉnh v kề u có bậc lớn nhất mtk
int dinh_v_baclonhat_mtk(MaTranKe mtk, int u, int &v);
// 10 Viết hàm tìm đỉnh v kề u có bậc nhỏ nhất mtk
int dinh_v_bacnhonhat_mtk(MaTranKe mtk, int u, int &v);
// 11 Viết hàm tìm đỉnh v kề u có bậc lớn nhất dsk
int dinh_v_baclonnhat_dsk(DanhSachKe dsk, int u, int &v);
// 12 Viết hàm tìm đỉnh v kề u có bậc nhỏ nhất dsk
int dinh_v_bacnhonhat_dsk(DanhSachKe dsk, int u, int &v);

// D. Tìm cạnh 
// 1 Viết hàm tìm cạnh lớn nhất mtk (là cạnh có trọng số lớn nhất)
int timcanhmax_mtk(MaTranKe mtk, Canh &canhmax);
// 2 Viết hàm tìm cạnh nhỏ nhất mtk
int timcanhmin_mtk(MaTranKe mtk, Canh &canhmin);
// 3 Viết hàm tìm cạnh lớn nhất dsk
int timcanhmax_dsk(DanhSachKe dsk, Canh &canhmax);
// 4 Viêt hàm tìm cạnh nhỏ nhất dsk
int timcanhmin_dsk(DanhSachKe dsk, Canh &canhmin);
// 5 Viết hàm trả về tổng trọng số các cạnh mtk
int tongtrongso_mtk(MaTranKe mtk);
// 6 Viết hàm trả về tổng trọng sô các cạnh dsk
int tongtrongso_dsk(DanhSachKe dsk);
// 7 Viết hàm trả về tổng trọng sô các cạnh từ đỉnh u mtk
int tongtrongsotuu_mtk(MaTranKe mtk, int u);
// 8 Viết hàm trả về tổng trọng số các cạnh vào đỉnh u mtk
int tongtrongsovaou_mtk(MaTranKe mtk, int u);
// 9 Viêt hàm trả về tỏng trọng số các cạnh từ đỉnh u dsk
int tongtrongsotuu_dsk(DanhSachKe dsk, int u);
// 10 Viết hàm trả về tổng trọng số các cạnh vào đỉnh u dsk
int tongtrongsovaou_dsk(DanhSachKe dsk, int u);

// duyệt dfs - bfs 
void duyet_dfs_dsk(DanhSachKe dsk, int u, bool visited[]);
void duyet_bfs_dsk(DanhSachKe dsk, int u, bool visited[]);
void duyet_dfs_mtk(MaTranKe mtk, int u, bool visited[]);
void duyet_bfs_mtk(MaTranKe mtk, int u, bool visited[]);