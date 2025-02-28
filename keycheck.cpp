#include "ioset.hpp"

class KeyCheck : public IOSet{
    protected:
        struct KeyConfig{
            int key;
            std::string value;
        };

        std::vector<KeyConfig> keyList{
            {VK_LSHIFT,     "LSHIFT"},
            {VK_RSHIFT,     "RSHIFT"},
            {VK_LCONTROL,   "LCTRL"},
            {VK_RCONTROL,   "RCTRL"},
            {VK_LMENU,      "LALT"},
            {VK_RMENU,      "RALT"},
            {VK_SPACE,      "SPACE"},
            {VK_LWIN,       "LWIN"},
            {VK_RWIN,       "RWIN"},
            {VK_UP,         "UP"},
            {VK_DOWN,       "DOWN"},
            {VK_LEFT,       "LEFT"},
            {VK_RIGHT,      "RIGHT"},
            {VK_RETURN,     "ENTER"},
            {VK_ESCAPE,     "ESC"},
            {VK_LBUTTON,    "LCLICK"},
            {VK_RBUTTON,    "RCLICK"},
            {VK_HOME,       "HOME"},
            {VK_END,        "END"},
            {VK_SPACE,      "SPACE"},
            {VK_F1,         "F1"},
            {VK_F2,         "F2"},
            {VK_F3,         "F3"},
            {VK_F4,         "F4"},
            {VK_F5,         "F5"},
            {VK_F6,         "F6"},
            {VK_F7,         "F7"},
            {VK_F8,         "F8"},
            {VK_F9,         "F9"},
            {VK_F10,         "F10"},
            {VK_F11,         "F11"},
            {VK_F12,         "F12"},
            {'1',   "1"},
            {'2',   "2"},
            {'3',   "3"},
            {'4',   "4"},
            {'5',   "5"},
            {'6',   "6"},
            {'7',   "7"},
            {'8',   "8"},
            {'9',   "9"},
            {'0',   "0"},
            {'A',   "a"},
            {'B',   "b"},
            {'C',   "c"},
            {'D',   "d"},
            {'E',   "e"},
            {'F',   "f"},
            {'G',   "g"},
            {'H',   "h"},
            {'I',   "i"},
            {'J',   "j"},
            {'K',   "k"},
            {'L',   "l"},
            {'M',   "m"},
            {'N',   "n"},
            {'O',   "o"},
            {'P',   "p"},
            {'Q',   "q"},
            {'R',   "r"},
            {'S',   "s"},
            {'T',   "t"},
            {'U',   "u"},
            {'V',   "v"},
            {'W',   "w"},
            {'X',   "x"},
            {'Y',   "y"},
            {'Z',   "z"}
        };

        struct ShortcutConfig{
            std::vector<std::string> key;
            std::string func;
        };

        std::vector<ShortcutConfig> shortcutList;

        std::vector<std::string> keyPressed, keyFlag, newKey;
        std::string keyState, shortcutFileName;

    public:
        KeyCheck(std::string title, std::string fileName) : IOSet(title){
            this->shortcutFileName = fileName;
            this->shortcut_data_read();
        };
        
        int key_state_check(void){
            this->keyPressed.clear();
            std::vector<std::string> ().swap(this->keyPressed);
            for(int i = 0; i < this->keyList.size(); i++){
                if (GetKeyState(this->keyList[i].key) & 0x8000) this->keyPressed.push_back(this->keyList[i].value);
            }
            return 0;
        }

        std::string get_key_event(void){
            this->key_state_check();
            
            if(this->keyPressed.empty()){ // キーが押されていない場合
                this->keyState = "RELEASE";
                this->keyFlag.clear();
                std::vector<std::string> ().swap(this->keyFlag);
                return this->keyState;
            }
            else{
                vec pressedKeys;
                pressedKeys = this->keyPressed;
                if(pressedKeys.vec_compare(this->keyFlag)){  //状態変化なし
                    this->keyState = "EQ";
                    //this->print(this->keyState);
                    return this->keyState;
                }
                else{
                    this->newKey.clear();
                    std::vector<std::string> ().swap(this->newKey);
                    std::set_difference( // 差集合
                        this->keyPressed.begin(), this->keyPressed.end(), 
                        this->keyFlag.begin(), this->keyFlag.end(), 
                        std::back_inserter(this->newKey)
                    );
                    
                    if(this->newKey.empty()){
                        this->keyState = "RELEASE";
                        this->keyFlag.clear();
                        std::vector<std::string> ().swap(this->keyFlag);
                        return this->keyState;
                    }
                    else{
                        this->keyFlag.clear();
                        std::vector<std::string> ().swap(this->keyFlag);
                        std::copy(this->keyPressed.begin(), this->keyPressed.end(), std::back_inserter(this->keyFlag));
                        this->keyState = "NEWKEY";
                        return this->keyState;
                    }
                }
            }
        }

        int shortcut_data_read(void){
            if(read_file(this->shortcutFileName) == "FALSE"){
                return false;
            }
            else{
                str shortcutFileData;
                std::vector<std::string> fileDataLine;
                ShortcutConfig shortcutConfig;
                shortcutFileData                = read_file(this->shortcutFileName);
                fileDataLine                    = shortcutFileData.split("\n");
                int fileLineNum                 = fileDataLine.size();
                this->shortcutList.clear();
                std::vector<ShortcutConfig> ().swap(this->shortcutList);
                
                for (int i = 0; i < fileLineNum; i++){
                    if (std::count(fileDataLine[i].begin(), fileDataLine[i].end(), '=') > 0){
                        std::vector<std::string> shortcutFileLine;
                        str shortcutData, shortcutKeyData;
                        shortcutData                = fileDataLine[i];
                        shortcutFileLine            = shortcutData.split("=");
                        shortcutKeyData             = shortcutFileLine[0];
                        shortcutConfig.key          = shortcutKeyData.split(",");
                        shortcutConfig.func         = shortcutFileLine[1];
                        this->shortcutList.push_back(shortcutConfig);
                    }
                    
                }
                return true;
            }
        }

        int key_func(void){
            int registNum = this->shortcutList.size(), keyNum, registKeyNum, flag;
            vec registKeyCombination;
            if (this->keyState != "NEWKEY"){
                return 2;
            }
            for(int i = 0; i < registNum; i++){
                registKeyCombination        = this->shortcutList[i].key;
                keyNum                      = this->keyPressed.size();              //押されているキーの数
                registKeyNum                = registKeyCombination.size();          //ショートカットのキーの数
                
                if (registKeyCombination.vec_compare(this->keyPressed)){
                    std::string command;
                    command = this->shortcutList[i].func;
                    //this->print(command);
                    //std::async(std::launch::async, system, command.c_str());
                    this->create_process_cmd(command);
                    Sleep(10);
                    return 1;
                }
            }
            return 0;
        }

        int main(void){
            this->get_key_event();
            this->key_func();
            return 0;
        }
};

IOSet io("");
KeyCheck keycheck("Keyboard Shortcut", io.pwd() + "\\keysc.ini");

TaskTray taskTray("KeyCheck");
int process = true;
void finish(tray_menu *){
    process=false;
    taskTray.tray_exit();  // タスクトレイから削除
}
void shortcut_setting(tray_menu *){
    io.create_process_cmd("notepad " + io.pwd() +"\\keysc.ini");
}

void shortcut_update(tray_menu *){
    keycheck.shortcut_data_read();
}

void help(tray_menu *){
    io.create_process_cmd("explorer " + io.pwd()+"\\README.md");
}

tray tray_form ={               // タスクトレイの設定
    (char*)"icon.ico", // タスクトレイのアイコン画像。別途用意しておく。
    (tray_menu[]){
        {(char*)"Settings",0,0,shortcut_setting},
        {(char*)"Update",0,0,shortcut_update},
        {(char*)"-"},                 // セパレータ
        {(char*)"Quit",0,0,finish},   //終了
        {(char*)"-"},
        {(char*)"Help",0,0,help},
        {nullptr}                     //最後の要素。必須。
    }
};

//キーの取得
void key_check(void){
    while(process){
        keycheck.main();
        Sleep(10);
    }
}

int main(int argc, char *argv[]) {
    std::thread keyboard(key_check);// 表示処理は別スレッド化
    taskTray.tray_update(&tray_form); //タスクトレイに登録
    while(taskTray.tray_loop(1) == 0){} //タスクトレイが表示されている間ループ
    keyboard.join();
    return 0;
}