#include "thuvien.h"

// viết hàm đọc file cho dsk và mtk
void docfile_dsk(DanhSachKe& dsk, const char* duongdan, int cotrongso){
    ifstream file(duongdan);
    if(!file.is_open()){
        cout << "Khong mo duoc file: " << duongdan << endl;
        return;
    }
    // Lấy số đầu tiên trong file làm số đỉnh 
    file >> dsk.sodinh;
    for(int i = 0; i < dsk.sodinh; i++){
        dsk.dsk[i] = NULL;
    }
    for(int i = 0; i < dsk.sodinh; i++){
        // Lấy số đỉnh kề của từng đỉnh 
        int m; file >> m;
        // duyệt qua từng đỉnh kề 
        for(int j = 0; j < m; j++){
            // tạo 1 node nối vào dslk (làm đỉnh kề của đỉnh i)
            Nodeptr p = new Node;
            p->link = NULL;
            if(cotrongso) file >> p->dinhke >> p->trongso;
            else file >> p->dinhke;
            // Nối đỉnh kề vào dslk của đỉnh i
            if(dsk.dsk[i] == NULL) 
                dsk.dsk[i] = p;
            else {
                Nodeptr q = dsk.dsk[i];
                while(q->link != NULL){
                    q = q->link;
                }
                q->link = p;
            }
        }
    }
    file.close();
    cout << "Doc file: " << duongdan << " thanh cong !" << endl;
}

void docfile_mtk(MaTranKe& mtk, const char* duongdan){
    ifstream file(duongdan);
    if(!file.is_open()){
        cout << "Khong mo duoc file: " << duongdan << endl;
        return;
    }
    file >> mtk.sodinh;
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            file >> mtk.mtk[i][j];
        }
    }
    file.close();
    cout << "Da doc file: " << duongdan << " thanh cong !" << endl;
}

// duyệt dsk và mtk
void duyet_dsk(DanhSachKe dsk){
    for(int i = 0; i < dsk.sodinh; i++){
        cout << i << ": ";
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            cout << p->dinhke << " ";
            p = p->link;
        }
        cout << endl;
    }
}

void duyet_mtk(MaTranKe mtk){
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            cout << mtk.mtk[i][j] << " ";
        }
        cout << endl;
    }
}

void duyet_canh(Canh c){
    cout << "Canh: (" 
             << c.dinhdau << ", " 
             << c.dinhcuoi << ", " 
             << c.trongso << ")"
             << endl;
}

void duyet_dsc(DanhSachCanh dsc){
    for(int i = 0; i < dsc.socanh; i++){
        Canh c = dsc.dsc[i];
        duyet_canh(c);
    }
}

void lammoivisited(bool visited[], int n){
    fill(visited, visited+n, false);
}

// B. Chuyển đổi câu trúc 
// 1 Chuyển mtk sang dsk
DanhSachKe chuyen_mtk_sang_dsk(MaTranKe mtk){
    DanhSachKe dsk;
    dsk.sodinh = mtk.sodinh;
    for(int i = 0; i < dsk.sodinh; i++){
        dsk.dsk[i] = NULL;
    }
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            if(mtk.mtk[i][j] != 0){
                Nodeptr nodemoi = new Node;
                nodemoi->dinhke = j;
                nodemoi->trongso = mtk.mtk[i][j];
                nodemoi->link = NULL;
                if(dsk.dsk[i] == NULL){
                    dsk.dsk[i] = nodemoi;
                } else {
                    Nodeptr q = dsk.dsk[i];
                    while(q->link != NULL){
                        q=q->link;
                    }
                    q->link = nodemoi;
                }
            }
        }
    }
    return dsk;
}

// 2 Chuyển mtk sang dsc
DanhSachCanh chuyen_mtk_sang_dsc(MaTranKe mtk){
    DanhSachCanh dsc;
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            if(mtk.mtk[i][j] != 0){
                Canh c = {i, j, mtk.mtk[i][j]};
                dsc.dsc[dsc.socanh++] = c;
            }
        }
    }
    return dsc;
}

// 3 Chuyển dsk sang mtk
MaTranKe chuyen_dsk_sang_mtk(DanhSachKe dsk){
    MaTranKe mtk;
    mtk.sodinh = dsk.sodinh;
    for(int i = 0; i < dsk.sodinh; i++){
        for(int j = 0; j < dsk.sodinh; j++){
            mtk.mtk[i][j] = 0;
        }
    }
    for(int i = 0; i < mtk.sodinh; i++){
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            mtk.mtk[i][p->dinhke] = p->trongso;
            p = p->link;
        }
    }
    return mtk;
}

// 4 Chuyển dsk sang dsc
DanhSachCanh chuyen_dsk_sang_dsc(DanhSachKe dsk){
    DanhSachCanh dsc;
    for(int i = 0; i < dsk.sodinh; i++){
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            Canh c = {i, p->dinhke, p->trongso};
            dsc.dsc[dsc.socanh++] = c;
            p = p->link;
        }
    }
    return dsc;
}

// 5 Chuyển dsc và 1 đỉnh sang mtk
MaTranKe chuyen_dsc_sang_mtk(DanhSachCanh dsc, int sodinh){
    MaTranKe mtk;
    mtk.sodinh = sodinh;
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            mtk.mtk[i][j] = 0;
        }
    }
    for(int i = 0; i < dsc.socanh; i++){
        Canh c = dsc.dsc[i];
        mtk.mtk[c.dinhdau][c.dinhcuoi] = c.trongso;
    }
    return mtk;
}

// 6 Chuyển dsc và 1 đỉnh sang dsk
DanhSachKe chuyen_dsc_sang_dsk(DanhSachCanh dsc, int sodinh){
    DanhSachKe dsk;
    dsk.sodinh = sodinh;
    for(int i = 0; i < dsk.sodinh; i++){
        dsk.dsk[i] = NULL;
    }
    for(int i = 0; i < dsc.socanh; i++){
        Canh c = dsc.dsc[i];
        Nodeptr nodemoi = new Node;
        nodemoi->dinhke = c.dinhcuoi;
        nodemoi->trongso = c.trongso;
        nodemoi->link = NULL;
        int dinhdau = c.dinhdau;
        if(dsk.dsk[dinhdau] == NULL){
            dsk.dsk[dinhdau] = nodemoi;
        } else {
            Nodeptr q = dsk.dsk[dinhdau];
            while(q->link != NULL){
                q = q->link;
            }
            q->link = nodemoi;
        }
    }
    return dsk;
}

// C. Tính bậc
// 1 Viết hàm tính bậc vào của 1 đỉnh dsk
int bacvao_dsk(DanhSachKe dsk, int u){
    int bacvao = 0;
    for(int i = 0; i < dsk.sodinh; i++){
        if(i == u) continue;
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            if(p->dinhke == u){
                bacvao++;
            }
            p = p->link;
        }
    }
    return bacvao;
}

// 2 Viết hàm tính bậc ra của 1 đỉnh dsk
int bacra_dsk(DanhSachKe dsk, int u){
    int bacra = 0;
    Nodeptr p = dsk.dsk[u];
    while(p != NULL){
        bacra++;
        p = p->link;
    }
    return bacra;
}

// 3 Viết hàm tính bậc vào của 1 dỉnh mtk
int bacvao_mtk(MaTranKe mtk, int u){
    int bacvao = 0;
    for(int i = 0; i < mtk.sodinh; i++){
        if(u == i) continue;
        if(mtk.mtk[i][u] != 0) {
            bacvao++;
        }
    }
    return bacvao;
}

// 4 Viết hàm tính bậc ra của 1 đỉnh mtk
int bacra_mtk(MaTranKe mtk, int u){
    int bacra = 0;
    for(int i = 0; i < mtk.sodinh; i++){
        if(mtk.mtk[u][i] != 0){
            bacra++;
        }
    }
    return bacra;
}

// 5 Viết hàm trả về đỉnh có bậc lớn nhất mtk
int baclonnhat_mtk(MaTranKe mtk){
    int bacmax = -1, dinh = -1;
    for(int i = 0; i < mtk.sodinh; i++){
        int bacvao = bacvao_mtk(mtk, i);
        int bacra = bacra_mtk(mtk, i);
        if(bacvao+bacra > bacmax){
            bacmax = bacvao + bacra;
            dinh = i;
        }
    }
    return dinh;
}

// 6 Viết hàm trả về đỉnh có bậc nhỏ nhất mtk
int bacnhonhat_mtk(MaTranKe mtk){
    int bacmin = 100, dinh = -1;
    for(int i = 0; i < mtk.sodinh; i++){
        int bacvao = bacvao_mtk(mtk, i);
        int bacra = bacra_mtk(mtk, i);
        if(bacvao + bacra < bacmin){
            bacmin = bacvao + bacra;
            dinh = i;
        }
    }
    return dinh;
}

// 7 Viết hàm trả về đỉnh có bậc lớn nhất dsk
int baclonnhat_dsk(DanhSachKe dsk){
    int bacmax = -1, dinh = -1;
    for(int i = 0; i < dsk.sodinh; i++){
        int bacvao = bacvao_dsk(dsk, i);
        int bacra = bacra_dsk(dsk, i);
        if(bacvao + bacra > bacmax){
            bacmax = bacvao + bacra;
            dinh = i;
        }
    }
    return dinh;
}

// 8 Viết hàm trả về đỉnh có bậc nhỏ nhất dsk
int bacnhonhat_dsk(DanhSachKe dsk){
    int bacmin = 100, dinh = -1;
    for(int i = 0; i < dsk.sodinh; i++){
        int bacvao = bacvao_dsk(dsk, i);
        int bacra = bacra_dsk(dsk, i);
        if(bacvao + bacra < bacmin){
            bacmin = bacvao + bacra;
            dinh = i;
        }
    }
    return dinh;
}

// 9 Viết hàm tìm đỉnh v kề u có bậc lớn nhất mtk
int dinh_v_baclonhat_mtk(MaTranKe mtk, int u, int &v){
    int bacmax = -1, dinh = -1;
    for(int i = 0; i < mtk.sodinh; i++){
        if(mtk.mtk[u][i] != 0){
            int bacvao = bacvao_mtk(mtk, i);
            int bacra = bacra_mtk(mtk, i);
            if(bacvao + bacra > bacmax){
                bacmax = bacvao+bacra;
                dinh = i;
            }
        }
    }
    if(dinh != -1){
        v = dinh;
        return 1;
    }
    return 0;
}

// 10 Viết hàm tìm đỉnh v kề u có bậc nhỏ nhất mtk
int dinh_v_bacnhonhat_mtk(MaTranKe mtk, int u, int &v){
    int bacmin = 100, dinh = -1;
    for(int i = 0; i < mtk.sodinh; i++){
        if(mtk.mtk[u][i] != 0){
            int bacvao = bacvao_mtk(mtk, i);
            int bacra = bacra_mtk(mtk, i);
            if(bacvao + bacra < bacmin){
                bacmin = bacvao+bacra;
                dinh = i;
            }
        }
    }
    if(dinh != -1){
        v = dinh;
        return 1;
    }
    return 0;
}

// 11 Viết hàm tìm đỉnh v kề u có bậc lớn nhất dsk
int dinh_v_baclonnhat_dsk(DanhSachKe dsk, int u, int &v){
    Nodeptr p = dsk.dsk[u];
    int bacmax = -1, dinh = -1;
    while(p != NULL){
        int bacvao = bacvao_dsk(dsk, p->dinhke);
        int bacra = bacra_dsk(dsk, p->dinhke);
        if(bacvao+bacra > bacmax){
            bacmax = bacvao + bacra;
            dinh = p->dinhke;
        }
        p = p->link;
    }
    return dinh;
}

// 12 Viết hàm tìm đỉnh v kề u có bậc nhỏ nhất dsk
int dinh_v_bacnhonhat_dsk(DanhSachKe dsk, int u, int &v){
    Nodeptr p = dsk.dsk[u];
    int bacmin = 100, dinh = -1;
    while(p != NULL){
        int bacvao = bacvao_dsk(dsk, p->dinhke);
        int bacra = bacra_dsk(dsk, p->dinhke);
        if(bacvao+bacra < bacmin){
            bacmin = bacvao + bacra;
            dinh = p->dinhke;
        }
        p = p->link;
    }
    return dinh;
}

// D. Tìm cạnh 
// 1 Viết hàm tìm cạnh lớn nhất mtk (là cạnh có trọng số lớn nhất)
int timcanhmax_mtk(MaTranKe mtk, Canh &canhmax){
    int trongsomax = -1;
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            if(mtk.mtk[i][j] != 0 && mtk.mtk[i][j] > trongsomax){
                trongsomax = mtk.mtk[i][j];
                canhmax = {i, j, mtk.mtk[i][j]};
            }
        }
    }
    if(trongsomax != -1)
        return 1;
    return 0;
}

// 2 Viết hàm tìm cạnh nhỏ nhất mtk
int timcanhmin_mtk(MaTranKe mtk, Canh &canhmin){
    int trongsomin = 100;
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            if(mtk.mtk[i][j] != 0 && mtk.mtk[i][j] < trongsomin){
                trongsomin = mtk.mtk[i][j];
                canhmin = {i, j, mtk.mtk[i][j]};
            }
        }
    }
    if(trongsomin != 100)
        return 1;
    return 0;
}

// 3 Viết hàm tìm cạnh lớn nhất dsk
int timcanhmax_dsk(DanhSachKe dsk, Canh &canhmax){
    int trongsomax = -1;
    for(int i = 0; i < dsk.sodinh; i++){
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            if(p->trongso > trongsomax){
                trongsomax = p->trongso;
                canhmax = {i, p->dinhke, p->trongso};
            }
            p = p->link;
        }
    }
    if(trongsomax != -1)
        return 1;
    return 0;
}

// 4 Viêt hàm tìm cạnh nhỏ nhất dsk
int timcanhmin_dsk(DanhSachKe dsk, Canh &canhmin){
    int trongsomin = 100;
    for(int i = 0; i < dsk.sodinh; i++){
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            if(p->trongso < trongsomin){
                trongsomin = p->trongso;
                canhmin = {i, p->dinhke, p->trongso};
            }
            p = p->link;
        }
    }
    if(trongsomin != -1)
        return 1;
    return 0;
}

// 5 Viết hàm trả về tổng trọng số các cạnh mtk
int tongtrongso_mtk(MaTranKe mtk){
    int tongtrongso = 0;
    for(int i = 0; i < mtk.sodinh; i++){
        for(int j = 0; j < mtk.sodinh; j++){
            tongtrongso += mtk.mtk[i][j];
        }
    }
    return tongtrongso;
}

// 6 Viết hàm trả về tổng trọng sô các cạnh dsk
int tongtrongso_dsk(DanhSachKe dsk){
    int tongtrongso = 0;
    for(int i = 0; i < dsk.sodinh; i++){
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            tongtrongso += p->trongso;
            p = p->link;
        }
    }
    return tongtrongso;
}

// 7 Viết hàm trả về tổng trọng sô các cạnh từ đỉnh u mtk
int tongtrongsotuu_mtk(MaTranKe mtk, int u){
    int tongtrongso = 0;
    for(int i = 0; i < mtk.sodinh; i++){
        tongtrongso += mtk.mtk[u][i];
    }
    return tongtrongso;
}

// 8 Viết hàm trả về tổng trọng số các cạnh vào đỉnh u mtk
int tongtrongsovaou_mtk(MaTranKe mtk, int u){
    int tongtrongso = 0;
    for(int i = 0; i < mtk.sodinh; i++){
        tongtrongso += mtk.mtk[i][u];
    }
    return tongtrongso;
}

// 9 Viêt hàm trả về tỏng trọng số các cạnh từ đỉnh u dsk
int tongtrongsotuu_dsk(DanhSachKe dsk, int u){
    int tongtrongso = 0;
    Nodeptr p = dsk.dsk[u];
    while(p != NULL){
        tongtrongso += p->trongso;
        p = p->link;
    }    
    return tongtrongso;
}
// 10 Viết hàm trả về tổng trọng số các cạnh vào đỉnh u dsk
int tongtrongsovaou_dsk(DanhSachKe dsk, int u){
    int tongtrongso = 0;
    for(int i = 0; i < dsk.sodinh; i++){
        if(i == u) continue;
        Nodeptr p = dsk.dsk[i];
        while(p != NULL){
            if(p->dinhke == u){
                tongtrongso += p->trongso;
            }
            p = p->link;
        }
    }
    return tongtrongso;
}

void duyet_dfs_dsk(DanhSachKe dsk, int u, bool visited[]){
    visited[u] = true;
    cout << u << " ";
    Nodeptr p = dsk.dsk[u];
    while(p != NULL){
        int v = p->dinhke;
        if(!visited[v]){
            duyet_dfs_dsk(dsk, v, visited);
        }
        p = p->link;
    }
}

void duyet_bfs_dsk(DanhSachKe dsk, int u, bool visited[]){
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while(!q.empty()){
        int v = q.front();
        cout << v << " ";
        q.pop();
        Nodeptr p = dsk.dsk[v];
        while(p != NULL){
            int w = p->dinhke;
            if(!visited[w]){
                visited[w] = true;
                q.push(w);
            }
            p = p->link;
        }
    }
}

void duyet_dfs_mtk(MaTranKe mtk, int u, bool visited[]){
    visited[u] = true;
    cout << u << " ";
    for(int i = 0; i < mtk.sodinh; i++){
        if(mtk.mtk[u][i] != 0 && !visited[i]){
            duyet_dfs_mtk(mtk, i, visited);
        }
    }
}

void duyet_bfs_mtk(MaTranKe mtk, int u, bool visited[]){
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        cout << v << " ";
        for(int i = 0; i < mtk.sodinh; i++){
            if(mtk.mtk[v][i] != 0 && !visited[i]){
                q.push(i);
                visited[i] = true;
            }
        }
    }
}
