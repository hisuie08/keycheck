#include "ioset.hpp"

class KeyCheck : public IOSet{
    private:
        std::vector<int> keyList{
            VK_LSHIFT,VK_RSHIFT,VK_LCONTROL,VK_RCONTROL,VK_LMENU,VK_RMENU,VK_SPACE,VK_LWIN,VK_RWIN,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_RETURN,VK_ESCAPE,VK_LBUTTON,VK_RBUTTON,
            '1','2','3','4','5','6','7','8','9','0','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
        };

        std::vector<std::string> keyVal{
            "LSHIFT","RSHIFT","LCTRL","RCTRL","LALT","RALT","SPACE","LWIN","RWIN","UP","DOWN","LEFT","RIGHT","ENTER","ESC","LCLICK","RCLICK",
            "1","2","3","4","5","6","7","8","9","0","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"
        };

        std::vector<std::string> keyPressed, keyFlag, newKey, keyScFileDataLine, scKey, scFunc;
        std::string keyState;

    public:
        KeyCheck(std::string title) : IOSet(title){};
        
        void key_state_check(void){
            this->keyPressed.clear();
            for(int i = 0; i < this->keyList.size(); i++){
                if (GetKeyState(this->keyList[i]) & 0x8000) this->keyPressed.push_back(this->keyVal[i]);
            }
        }

        std::string get_key_event(void){
            this->key_state_check();
            
            if(this->keyPressed.empty()){ // キーが押されていない場合
                this->keyState = "RELEASE";
                this->keyFlag.clear();
                return this->keyState;
            }
            else{
                if(std::equal(this->keyPressed.begin(), this->keyPressed.end(), this->keyFlag.begin(), this->keyFlag.end())){  //状態変化なし
                    this->keyState = "EQ";
                    return this->keyState;
                }
                else{
                    this->newKey.clear();
                    std::set_difference(
                        this->keyPressed.begin(), this->keyPressed.end(), 
                        this->keyFlag.begin(), this->keyFlag.end(), 
                        std::back_inserter(this->newKey)
                    );
                    
                    if(this->newKey.empty()){
                        this->keyState = "RELEASE";
                        this->keyFlag.clear();
                        return this->keyState;
                    }
                    else{
                        this->keyFlag.clear();
                        std::copy(this->keyPressed.begin(), this->keyPressed.end(), std::back_inserter(this->keyFlag));
                        this->keyState = "NEWKEY";
                        return this->keyState;
                    }
                }
            }
        }

        int key_sc_data_read(std::string fileName){
            this->keyScFileDataLine.clear();
            if(read_file(fileName) == "FALSE"){
                return false;
            }
            else{
                str keyScFileData;
                keyScFileData               = read_file(fileName);
                this->keyScFileDataLine     = keyScFileData.split("\n");
                int scFileLineSize          = this->keyScFileDataLine.size();
                this->scKey.clear();
                this->scFunc.clear();
                for (int i = 0; i < scFileLineSize; i++){
                    if (std::count(this->keyScFileDataLine[i].begin(), this->keyScFileDataLine[i].end(), '=') > 0){
                        str scData;
                        scData = this->keyScFileDataLine[i];
                        std::vector<std::string> scFileLine = scData.split("=");
                        this->scKey.push_back(scFileLine[0]);
                        this->scFunc.push_back(scFileLine[1]);
                    }
                    
                }
                return true;
            }
        }

        void key_func(void){
            int registNum = this->scKey.size(), keyNum, registKeyNum, flag;
            std::vector<std::string> registKeyCombination;
            if (this->keyState != "NEWKEY"){
                return;
            }
            for(int i = 0; i < registNum; i++){
                flag                = 0;
                str scKeyData;
                scKeyData               = this->scKey[i];
                registKeyCombination    = scKeyData.split(",");
                keyNum                  = this->keyPressed.size();              //押されているキーの数
                registKeyNum            = registKeyCombination.size();          //ショートカットのキーの数
                
                for(int j = 0; j < keyNum; j++){
                    if(std::find(registKeyCombination.begin(), registKeyCombination.end(), this->keyPressed[j]) >= registKeyCombination.end()){
                        flag = 1;
                        break;
                    }
                }

                for(int j = 0; j < registKeyNum; j++){
                    if(std::find(this->keyPressed.begin(), this->keyPressed.end(), registKeyCombination[j]) >= this->keyPressed.end()){
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0){
                    std::string command;
                    command = this->scFunc[i];
                    this->print(command);
                    //std::async(std::launch::async, system, command.c_str());
                    this->create_process_cmd(command);
                    Sleep(10);
                    break;
                }
                
            }
        }

        void main(void){
            this->get_key_event();
            this->key_func();
        }
};

TaskTray taskTray("KeyCheck");
int process = true;
void finish(tray_menu *){
    process=false;
    taskTray.tray_exit();  // タスクトレイから削除
}
void key_sc_set(tray_menu *){
    IOSet io("");
    io.create_process_cmd("notepad " + io.pwd() +"\\keysc.ini");
}

void help(tray_menu *){
    IOSet io("");
    io.create_process_cmd("explorer " + io.pwd()+"\\README.md");
}

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

//キーの取得
void key_check(void){
    KeyCheck keycheck("Keyboard Shortcut");
    while(process){
        keycheck.key_sc_data_read(keycheck.pwd() + "\\keysc.ini");
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