#include <bits/stdc++.h> //<cstdio> <cstdlib> <iostream> <cstring> <algorithm> <iterator>  <fstream> <istream> <sstream> <vector> <tuple> <iomanip> <thread> <future>
#include <Windows.h>
#include <shellapi.h>

class str : public std::string{
    public:
        using std::string::string;
        std::string replace_all(std::string target, std::string replacement){
            std::string::size_type pos = 0;
            std::string stringText = *this;
            while ((pos = stringText.find(target, pos)) != std::string::npos) {
                stringText.replace(pos, target.length(), replacement);
                pos += replacement.length();
            }
            return stringText;
        }

        std::vector<std::string> split(std::string del) {
            int first = 0;
            int i = 0;
            std::string stringText = *this;
            std::vector<std::string> result;
            std::vector<int> subStrNum = find_all(del);
            while (first < stringText.size()) {
                std::string subStr(stringText, first, subStrNum[i] - first);
                result.push_back(subStr); //配列の末尾に要素を追加する
                first = subStrNum[i] + 1;
                i++;
            }
            return result;
        }

        std::vector<int> find_all(std::string subStr) {
            std::vector<int> result;
            std::string stringText = *this;
            int subStrSize = subStr.size();
            int pos = stringText.find(subStr);
            while (pos != std::string::npos) {
                result.push_back(pos);
                pos = stringText.find(subStr, pos + subStrSize);
            }
            return result;
        }
        std::string to_string(){
            return (std::string)*this;
        }

        str& operator+(const str &targetText) {
            str strText = targetText;
            for(int i = 0; i < strText.size(); i++){
                this -> push_back(strText[i]);
            }
            return *this;
        }

        str& operator= (std::string target){
            std::string targetString = target;
            this -> clear();
            for(int i = 0; i < targetString.size(); i++){
                this -> push_back(targetString[i]);
            }
            return *this;
        }

        str& operator= (auto targetString){
            this -> clear();
            for(int i = 0; i < targetString.size(); i++){
                this -> push_back(std::to_string(targetString[i]));
            }
            return *this;
        }
        
};

class vec : public std::vector<std::string>{
    public:
        using std::vector<std::string>::vector;
        std::string to_str (){
            std::string ans = "";
            std::vector<std::string> sourceVec = *this;
            for(int i = 0; i < sourceVec.size(); i++){
                ans = ans + sourceVec[i];
            }
            return ans;
        }
        std::vector<std::string> to_vec (){
            return (std::vector<std::string>)*this;
        }
        vec& operator= (std::vector<std::string> target){
            std::vector<std::string> targetVec = target;
            this -> clear();
            for(int i = 0; i < targetVec.size(); i++){
                this -> push_back(targetVec[i]);
            }
            return *this;
        }

        vec& operator= (std::vector<auto> targetVec){
            this -> clear();
            for(int i = 0; i < targetVec.size(); i++){
                this -> push_back(std::to_string(targetVec[i]));
            }
            return *this;
        }
};

class IOSet {
    public:
        std::string cwdPath; //カレントディレクトリ
        std::string sourcePath; //ファイルパス
        std::string sourcePathNoEX; //ファイルパス(拡張子無し)
        
        IOSet() {
            char path[256];
            GetCurrentDirectory(sizeof(path),path);
            cwdPath = path;
            GetModuleFileName(NULL, path, sizeof(path));
            sourcePath = path;
            str pathData(sourcePath.c_str());
            sourcePathNoEX = pathData.replace_all(".exe", "");
        }

        void title(std::string stringText){
            std::string changeTitleCmd = "title " + stringText;
            cmd(changeTitleCmd);
        }
        
        std::string print(std::string stringText, std::string stringEnd) {
            std::cout << stringText << stringEnd;
            return stringText;
        }

        std::string print(std::string stringText) {
            std::cout << stringText << std::endl; // 「std::endl」 \n とバッファをフラッシュ
            return stringText;
        }
        std::string input(std::string stringPrompt) {
            if (stringPrompt != ""){
                std::cout << stringPrompt << std::endl; // 「std::endl」 \n とバッファをフラッシュ
            }
            std::string inputText;
            std::getline(std::cin, inputText);
            return inputText;
        }
        std::string cmd(std::string stringCmd) {
            system(stringCmd.c_str());
            return stringCmd;
        }
        int create_process_cmd(std::string stringCmd){
            std::string cmdLog = "";
            cmdLog = stringCmd;
            STARTUPINFO si;
            PROCESS_INFORMATION pi;
            ZeroMemory( &si, sizeof(si) );
            si.cb = sizeof(si);
            ZeroMemory( &pi, sizeof(pi) );
            // Start the child process. 
            CreateProcess( NULL,   // No module name (use command line)
                TEXT((char*)cmdLog.c_str()),        // Command line
                NULL,           // Process handle not inheritable
                NULL,           // Thread handle not inheritable
                FALSE,          // Set handle inheritance to FALSE
                0,              // No creation flags
                NULL,           // Use parent's environment block
                NULL,           // Use parent's starting directory 
                &si,            // Pointer to STARTUPINFO structure
                &pi );           // Pointer to PROCESS_INFORMATION structure

            Sleep(100); //起動出来るまで待つ
        
            // Close process and thread handles. 
            CloseHandle( pi.hProcess );
            CloseHandle( pi.hThread );

            return 0;
        }
        std::string path(int mode) {
            switch(mode){
                case 1:
                    return sourcePathNoEX;
                default:
                    return sourcePath;
            }
            
        }
        std::string dir() {
            return cwdPath;
        }
        int MsgBox(std::string msgBoxTitle,std::string msgBoxText,int button ,int icon,int help){
            int ans;
            int val1 = 0, val2 =  0, val3 = 0, forms = 0;
            switch(button){
                case 1:
                    val1 = MB_OKCANCEL;
                    break;
                case 2:
                    val1 = MB_ABORTRETRYIGNORE;
                    break;
                case 3:
                    val1 = MB_YESNOCANCEL;
                    break;
                case 4:
                    val1 = MB_YESNO;        
                    break;
                case 5:
                    val1 = MB_RETRYCANCEL;
                    break;
                default:
                    val1 = MB_OK;
                    break;
            }
            switch(icon){
                case 1:
                case MB_ICONWARNING:
                    val2 = MB_ICONWARNING;
                    break;
                case 2:
                case MB_ICONINFORMATION:
                    val2 = MB_ICONINFORMATION;
                    break;
                case 3:
                case MB_ICONQUESTION:
                    val2 = MB_ICONQUESTION;
                    break;
                case 4:
                case MB_ICONERROR:
                    val2 = MB_ICONERROR;
                    break;
                default:
                    break;
            }
            switch(help){
                case 1:
                case MB_HELP:
                    val3 = MB_HELP;
                    break;
                default:
                    break;
            }
            forms = val1 | val2 | val3;
            ans = MessageBox(NULL , msgBoxText.c_str(), msgBoxTitle.c_str(), forms );
            return ans;
        }
        std::string read_file(std::string path){
            std::ifstream ifs(path);
            std::string fileData = "";
            std::string str;
            if (ifs.fail()) {
                return "FALSE";
            }
            else{
                while (getline(ifs, str)) {
                    fileData = fileData + str + "\n";
                }
                return fileData;
            }
        }
        int write_file(std::string path, std::string data, std::string mode){
            if (mode == "a"){
                if (path == sourcePathNoEX + ".cpp" || path == sourcePath){
                    int ans;
                    ans = MsgBox("警告", "このプログラムの重要ファイルです。\n書き換えますか？", 4, 1, 0);
                    if (ans == IDNO){
                        print("アクセス拒否されました。");
                        return 2;
                    }
                }
                std::string sdata = read_file(path); //データ読み込み
                std::ofstream ofs(path); //空ファイルにする
                if (ofs.fail()){
                    print("FALSE");
                    return -1;
                }
                ofs << sdata << data << std::endl;
                print(path + "に追加書き込み完了しました。");
                return 0;
            }
            else if (mode == "w"){
                if (path == sourcePathNoEX + ".cpp" || path == sourcePath){
                    int ans;
                    ans = MsgBox("警告", "このプログラムの重要ファイルです。\nエディタで書き換えてください！！", 0, 4, 0);
                    print("アクセス拒否されました。");
                    return -1;
                }
                std::ofstream ofs(path); //空ファイルにする
                if (ofs.fail()){
                    print("FALSE");
                    print("書き込み失敗");
                    return -1;
                }
                ofs << data << std::endl;
                print(path + "に書き込み完了しました。");
                return 0;
            }
            else{
                print("モードが違います。");
                return -1;
            }
        }
};


//タスクトレイ
#define TRAY_H
#define WM_TRAY_CALLBACK_MESSAGE (WM_USER + 1)
#define WC_TRAY_CLASS_NAME "TRAY"
#define ID_TRAY_FIRST 1000

WNDCLASSEX wc;
NOTIFYICONDATA nid;
HWND hwnd;
HMENU hmenu = NULL;

struct tray_menu;

struct tray {
    char *icon;
    struct tray_menu *menu;
};

struct tray_menu {
    char *text;
    int disabled;
    int checked;

    void (*cb)(struct tray_menu *);
    void *context;

    struct tray_menu *submenu;
};

void tray_update(struct tray *tray);

LRESULT CALLBACK _tray_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_TRAY_CALLBACK_MESSAGE:
            switch (lparam){
                case WM_LBUTTONUP:
                case WM_RBUTTONUP:
                    POINT p;
                    GetCursorPos(&p);
                    SetForegroundWindow(hwnd);
                    WORD cmd = TrackPopupMenu(hmenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY,
                                                p.x, p.y, 0, hwnd, NULL);

                    SendMessage(hwnd, WM_COMMAND, cmd, 0);
                    return 0;
            }
            break;
        case WM_COMMAND:
            if (wparam >= ID_TRAY_FIRST) {
                MENUITEMINFO item = {
                    .cbSize = sizeof(MENUITEMINFO), .fMask = MIIM_ID | MIIM_DATA,
                };
                if (GetMenuItemInfo(hmenu, wparam, FALSE, &item)) {
                    struct tray_menu *menu = (struct tray_menu *)item.dwItemData;
                    if (menu != NULL && menu->cb != NULL) {
                        menu->cb(menu);
                    }
                }
                return 0;
            }
            break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

HMENU _tray_menu(struct tray_menu *m, UINT *id) {
    HMENU hmenu = CreatePopupMenu();
    for (; m != NULL && m->text != NULL; m++, (*id)++) {
        if (strcmp(m->text, "-") == 0) {
            InsertMenu(hmenu, *id, MF_SEPARATOR, TRUE, "");
        } 
        else {
            MENUITEMINFO item;
            memset(&item, 0, sizeof(item));
            item.cbSize = sizeof(MENUITEMINFO);
            item.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_DATA;
            item.fType = 0;
            item.fState = 0;
            if (m->submenu != NULL) {
                item.fMask = item.fMask | MIIM_SUBMENU;
                item.hSubMenu = _tray_menu(m->submenu, id);
            }
            if (m->disabled) {
                item.fState |= MFS_DISABLED;
            }
            if (m->checked) {
                item.fState |= MFS_CHECKED;
            }
            item.wID = *id;
            item.dwTypeData = m->text;
            item.dwItemData = (ULONG_PTR)m;

            InsertMenuItem(hmenu, *id, TRUE, &item);
        }
    }
    return hmenu;
}


int tray_init(struct tray *tray) {
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = _tray_wnd_proc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = WC_TRAY_CLASS_NAME;
    wc.lpszMenuName = "MYMENU";
    if (!RegisterClassEx(&wc)) {
        return -1;
    }

    hwnd = CreateWindowEx(0, WC_TRAY_CLASS_NAME, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (hwnd == NULL) {
        return -1;
    }
    UpdateWindow(hwnd);

    memset(&nid, 0, sizeof(nid));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 0;
    nid.uFlags = NIF_ICON | NIF_MESSAGE;
    nid.uCallbackMessage = WM_TRAY_CALLBACK_MESSAGE;
    lstrcpy( nid.szTip, TEXT("MYMENU")); 
    Shell_NotifyIcon(NIM_ADD, &nid);

    tray_update(tray);
    return 0;
}

int tray_loop(int blocking) {
    MSG msg;
    if (blocking) {
        GetMessage(&msg, NULL, 0, 0);
    } 
    else {
        PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
    }
    if (msg.message == WM_QUIT) {
        return -1;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    return 0;
}

void tray_update(struct tray *tray) {
    HMENU prevmenu = hmenu;
    UINT id = ID_TRAY_FIRST;
    hmenu = _tray_menu(tray->menu, &id);
    SendMessage(hwnd, WM_INITMENUPOPUP, (WPARAM)hmenu, 0);
    HICON icon;
    ExtractIconEx(tray->icon, 0, NULL, &icon, 1);
    if (nid.hIcon) {
        DestroyIcon(nid.hIcon);
    }
    nid.hIcon = icon;
    Shell_NotifyIcon(NIM_MODIFY, &nid);

    if (prevmenu != NULL) {
        DestroyMenu(prevmenu);
    }
}

void tray_exit() {
    Shell_NotifyIcon(NIM_DELETE, &nid);
    if (nid.hIcon != 0) {
        DestroyIcon(nid.hIcon);
    }
    if (hmenu != 0) {
        DestroyMenu(hmenu);
    }
    PostQuitMessage(0);
    UnregisterClass(WC_TRAY_CLASS_NAME, GetModuleHandle(NULL));
}

