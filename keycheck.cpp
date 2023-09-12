#include "ioset.cpp"
#include <shellapi.h>

class KeyCheck : public IOSet{
    private:
        std::vector<std::string> keyPressed, keyState, keyAns, keyFlag, newKey, keyScFileDataLine, scKey, scFunc;
        int flag;

    public:
        using IOSet::IOSet;
        std::vector<std::string> key(void){
            keyPressed.clear();
            if(GetKeyState(VK_LSHIFT) & 0x8000) keyPressed.push_back("LSHIFT");
            if(GetKeyState(VK_RSHIFT) & 0x8000) keyPressed.push_back("RSHIFT");
            if(GetKeyState(VK_LCONTROL) & 0x8000) keyPressed.push_back("LCTRL");
            if(GetKeyState(VK_RCONTROL) & 0x8000) keyPressed.push_back("RCTRL");
            if(GetKeyState(VK_LMENU) & 0x8000) keyPressed.push_back("LALT");
            if(GetKeyState(VK_RMENU) & 0x8000) keyPressed.push_back("RALT");
            if(GetKeyState(VK_SPACE) & 0x8000) keyPressed.push_back("SPACE");
            if(GetKeyState(VK_LWIN) & 0x8000) keyPressed.push_back("LWIN");
            if(GetKeyState(VK_RWIN) & 0x8000) keyPressed.push_back("RWIN");
            if(GetKeyState(VK_UP) & 0x8000) keyPressed.push_back("UP");
            if(GetKeyState(VK_DOWN) & 0x8000) keyPressed.push_back("DOWN");
            if(GetKeyState(VK_LEFT) & 0x8000) keyPressed.push_back("LEFT");
            if(GetKeyState(VK_RIGHT) & 0x8000) keyPressed.push_back("RIGHT");
            if(GetKeyState(VK_RETURN) & 0x8000) keyPressed.push_back("ENTER");
            if(GetKeyState(VK_ESCAPE) & 0x8000) keyPressed.push_back("ESC");
            if(GetKeyState(VK_LBUTTON) & 0x8000) keyPressed.push_back("LCLICK");
            if(GetKeyState(VK_RBUTTON) & 0x8000) keyPressed.push_back("RCLICK");
            if(GetKeyState('1') & 0x8000) keyPressed.push_back("1");
            if(GetKeyState('2') & 0x8000) keyPressed.push_back("2");
            if(GetKeyState('3') & 0x8000) keyPressed.push_back("3");
            if(GetKeyState('4') & 0x8000) keyPressed.push_back("4");
            if(GetKeyState('5') & 0x8000) keyPressed.push_back("5");
            if(GetKeyState('6') & 0x8000) keyPressed.push_back("6");
            if(GetKeyState('7') & 0x8000) keyPressed.push_back("7");
            if(GetKeyState('8') & 0x8000) keyPressed.push_back("8");
            if(GetKeyState('9') & 0x8000) keyPressed.push_back("9");
            if(GetKeyState('0') & 0x8000) keyPressed.push_back("0");
            if(GetKeyState('A') & 0x8000) keyPressed.push_back("a");
            if(GetKeyState('B') & 0x8000) keyPressed.push_back("b");
            if(GetKeyState('C') & 0x8000) keyPressed.push_back("c");
            if(GetKeyState('D') & 0x8000) keyPressed.push_back("d");
            if(GetKeyState('E') & 0x8000) keyPressed.push_back("e");
            if(GetKeyState('F') & 0x8000) keyPressed.push_back("f");
            if(GetKeyState('G') & 0x8000) keyPressed.push_back("g");
            if(GetKeyState('H') & 0x8000) keyPressed.push_back("h");
            if(GetKeyState('I') & 0x8000) keyPressed.push_back("i");
            if(GetKeyState('J') & 0x8000) keyPressed.push_back("j");
            if(GetKeyState('K') & 0x8000) keyPressed.push_back("k");
            if(GetKeyState('L') & 0x8000) keyPressed.push_back("l");
            if(GetKeyState('M') & 0x8000) keyPressed.push_back("m");
            if(GetKeyState('N') & 0x8000) keyPressed.push_back("n");
            if(GetKeyState('O') & 0x8000) keyPressed.push_back("o");
            if(GetKeyState('P') & 0x8000) keyPressed.push_back("p");
            if(GetKeyState('Q') & 0x8000) keyPressed.push_back("q");
            if(GetKeyState('R') & 0x8000) keyPressed.push_back("r");
            if(GetKeyState('S') & 0x8000) keyPressed.push_back("s");
            if(GetKeyState('T') & 0x8000) keyPressed.push_back("t");
            if(GetKeyState('U') & 0x8000) keyPressed.push_back("u");
            if(GetKeyState('V') & 0x8000) keyPressed.push_back("v");
            if(GetKeyState('W') & 0x8000) keyPressed.push_back("w");
            if(GetKeyState('X') & 0x8000) keyPressed.push_back("x");
            if(GetKeyState('Y') & 0x8000) keyPressed.push_back("y");
            if(GetKeyState('Z') & 0x8000) keyPressed.push_back("z");
            
            if(keyPressed.empty()){
                flag = 0;
                keyAns.clear();
                keyAns.push_back("RELEASE");
                keyState.clear();
                keyFlag.clear();
                return keyAns;
            }
            else{
                if(std::equal(keyPressed.begin(), keyPressed.end(), keyFlag.begin(), keyFlag.end())){
                    keyAns.clear();
                    keyAns.push_back("EQ");
                    return keyAns;
                }
                else{
                    newKey.clear();
                    std::set_difference(keyPressed.begin(), keyPressed.end(), keyFlag.begin(), keyFlag.end(), std::back_inserter(newKey));
                    keyFlag.clear();
                    std::copy(keyPressed.begin(), keyPressed.end(), std::back_inserter(keyFlag));
                    if(newKey.empty()){
                        keyAns.clear();
                        keyAns.push_back("RELEASE");
                        keyFlag.clear();
                        return keyAns;
                    }
                    else{
                        std::copy(newKey.begin(), newKey.end(), std::back_inserter(keyState));
                        return keyState;
                    }
                }
            }
        }

        int key_sc_data_read(std::string fileName){
            keyScFileDataLine.clear();
            if(read_file(fileName) == "FALSE"){
                return false;
            }
            else{
                str keyScFileData;
                keyScFileData = read_file(fileName);
                keyScFileDataLine = keyScFileData.split("\n");
                int scFileLineSize = keyScFileDataLine.size();
                scKey.clear();
                scFunc.clear();
                for (int i = 0; i < scFileLineSize; i++){
                    if (std::count(keyScFileDataLine[i].begin(), keyScFileDataLine[i].end(), '=') > 0){
                        str scData;
                        scData = keyScFileDataLine[i];
                        std::vector<std::string> scFileLine = scData.split("=");
                        scKey.push_back(scFileLine[0]);
                        scFunc.push_back(scFileLine[1]);
                    }
                    
                }
                return true;
            }
        }

        void key_func(std::vector<std::string> keyCombination){
            int registNum = scKey.size(), keyNum, registKeyNum;
            std::vector<std::string> registKeyCombination;
            for(int i = 0; i < registNum; i++){
                flag = 0;
                str scKeyData;
                scKeyData = scKey[i];
                registKeyCombination = scKeyData.split(",");
                keyNum = keyCombination.size(); //押されているキーの数
                registKeyNum = registKeyCombination.size();
                if (registKeyNum < keyNum){
                    for(int j = 0; j < keyNum; j++){
                        if(std::find(registKeyCombination.begin(), registKeyCombination.end(), keyCombination[j]) >= registKeyCombination.end()){
                            flag = 1;
                        }
                    }
                    if (flag == 0){
                        std::string command;
                        command = scFunc[i];
                        //std::async(std::launch::async, system, command.c_str());
                        create_process_cmd(command);
                        flag = 1;
                        Sleep(10);
                        break;
                    }
                }
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

//タスクトレイ設定
int process;
void finish(tray_menu *);
void key_sc_set(tray_menu *);
void help(tray_menu *);
tray tray_form ={               // タスクトレイの設定
    (char*)"icon.ico", // タスクトレイのアイコン画像。別途用意しておく。
    (tray_menu[]){
        {(char*)"Settings",0,0,key_sc_set},
        {(char*)"-"},                 // セパレータ
        {(char*)"Quit",0,0,finish},   //終了
        {(char*)"-"},
        {(char*)"Help",0,0,help},
        {nullptr}                     //最後の要素。必須。
    }
};

void finish(tray_menu *){
    process=false;
    tray_exit();  // タスクトレイから削除
}

void key_sc_set(tray_menu *){
    IOSet io;
    io.create_process_cmd("notepad " + io.dir() +"/keysc.ini");
}

void help(tray_menu *){
    IOSet io;
    io.create_process_cmd(io.dir()+"/help");
}


//キーの取得
void key_check(void){
    KeyCheck keycheck;
    keycheck.title("Keyboard Shortcut");
    while(process){
        keycheck.key_sc_data_read(keycheck.dir() + "/keysc.ini");
        keycheck.key_func(keycheck.key());
        Sleep(10);
    }
}

int main( void ) {
    process=true;
    std::thread keyboard(key_check);// 表示処理は別スレッド化
    tray_init(&tray_form); //タスクトレイに登録
    while(tray_loop(1) == 0){} //タスクトレイが表示されている間ループ
    keyboard.join();
    return 0;
}