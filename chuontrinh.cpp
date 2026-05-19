#include "thuvien.h"

int main(){
    // Khởi tạo dsk và mtk
    DanhSachKe dsk;
    MaTranKe mtk;
    // Khởi tạo mảng visited dùng cho duyệt dfs và bfs
    int nvs = 100;
    bool visited[nvs];

    docfile_dsk(dsk, "dsk.txt", 1);
    docfile_mtk(mtk, "mtk.txt");
    // Đọc dữ liệu từ file xong in dsk và mtk ra 
    cout << "Danh sach ke doc tu file" << endl;
    duyet_dsk(dsk);
    cout << "Ma tran ke doc tu file" << endl;
    duyet_mtk(mtk);

    // B. Chuyển đổi cấu trúc
    cout << "\nB. CHUYEN DOI CAU TRUC\n";
    cout << "Chuyen mtk sang dsk" << endl;
    DanhSachKe dsk1 = chuyen_mtk_sang_dsk(mtk);
    duyet_dsk(dsk1);

    cout << "Chuyen mtk sang dsc" << endl;
    DanhSachCanh dsc1 = chuyen_mtk_sang_dsc(mtk);
    duyet_dsc(dsc1);
    
    cout << "Chuyen dsk sang mtk" << endl;
    MaTranKe mtk1 = chuyen_dsk_sang_mtk(dsk);
    duyet_mtk(mtk1);
    
    cout << "Chuyen dsk sang dsc" << endl;
    DanhSachCanh dsc2 = chuyen_dsk_sang_dsc(dsk);
    duyet_dsc(dsc2);
    
    cout << "Chuyen dsc sang mtk" << endl;
    MaTranKe mtk2 = chuyen_dsc_sang_mtk(dsc1, 5);
    duyet_mtk(mtk2);
    
    cout << "Chuyen dsc sang dsk" << endl;
    DanhSachKe dsk2 = chuyen_dsc_sang_dsk(dsc1, 5);
    duyet_dsk(dsk2);

    // C. Tính bậc
    cout << "\nTÍNH BẬC\n";
    cout << "Nhap dinh: ";
    int u; cin >> u;
    cout << "Bac vao dsk: " << bacvao_dsk(dsk, u) << endl;
    cout << "Bac ra dsk: " << bacra_dsk(dsk, u) << endl;
    cout << "Bac vao mtk: " << bacvao_mtk(mtk, u) << endl;
    cout << "Bac ra mtk: " << bacra_mtk(mtk, u) << endl;
    cout << "Dinh co bac lon nhat mtk: " << baclonnhat_mtk(mtk) << endl;
    cout << "Dinh co bac nho nhat mtk: " << bacnhonhat_mtk(mtk) << endl;
    cout << "Dinh co bac lon nhat dsk: " << baclonnhat_dsk(dsk) << endl;
    cout << "Dinh co bac nho nhat dsk: " << bacnhonhat_dsk(dsk) << endl;
    int v;
    if(dinh_v_baclonhat_mtk(mtk, u, v)) 
        cout << "Dinh v co bac lon nhat mtk: " << v << endl;
    if(dinh_v_bacnhonhat_mtk(mtk, u, v))
        cout << "Dinh v co bac nho nhat mtk: " << v << endl;
    if(dinh_v_baclonnhat_dsk(dsk, u, v))
        cout << "Dinh v co bac lon nhat dsk: " << v << endl;
    if(dinh_v_bacnhonhat_dsk(dsk, u, v))
        cout << "Dinh v co bac nho nhat dsk: " << v << endl;

    // D. Tìm cạnh 
    cout << "\nTÌM CẠNH\n";
    Canh canhmax, canhmin;
    if(timcanhmax_mtk(mtk, canhmax)){
        cout << "Canh co trong so lon nhat mtk: ";
        duyet_canh(canhmax);
    }
    if(timcanhmin_mtk(mtk, canhmin)){
        cout << "Canh co trong so nho nhat mtk: ";
        duyet_canh(canhmin);
    }
    if(timcanhmax_dsk(dsk, canhmax)){
        cout << "Canh co trong so lon nhat dsk: ";
        duyet_canh(canhmax);
    }
    if(timcanhmin_dsk(dsk, canhmin)){
        cout << "Canh co trong so nho nhat dsk: ";
        duyet_canh(canhmin);
    }
    cout << "Tong trong so cac canh mtk: " << tongtrongso_mtk(mtk) << endl;
    cout << "Tong trong so cac canh dsk: " << tongtrongso_dsk(dsk) << endl;
    cout << "Tong trong so xuat phat tu dinh " << u << ": " << tongtrongsotuu_mtk(mtk, u) << endl;
    cout << "Tong trong so di vao dinh " << u << ": " << tongtrongsovaou_mtk(mtk, u) << endl;
    cout << "Tong trong so xuat phat tu dinh " << u << ": " << tongtrongsotuu_dsk(dsk, u) << endl;
    cout << "Tong trong so xuat phat tu dinh " << u << ": " << tongtrongsovaou_dsk(dsk, u) << endl;
    
    cout << "Duyet dfs dsk: ";
    lammoivisited(visited, nvs);
    duyet_dfs_dsk(dsk, u, visited);
    cout << endl;

    cout << "Duyet bfs dsk: ";
    lammoivisited(visited, nvs);
    duyet_bfs_dsk(dsk, u, visited);
    cout << endl;

    cout << "Duyet dfs mtk: ";
    lammoivisited(visited, nvs);
    duyet_dfs_mtk(mtk, u, visited);
    cout << endl;

    cout << "Duyet bfs mtk: ";
    lammoivisited(visited, nvs);
    duyet_bfs_mtk(mtk, u, visited);
    cout << endl;
    return 0;
}