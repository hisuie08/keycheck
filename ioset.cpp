#include <bits/stdc++.h> //<cstdio> <cstdlib> <iostream> <cstring> <algorithm> <iterator>  <fstream> <istream> <sstream> <vector> <tuple> <iomanip> <thread> <future>
#include <Windows.h>

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
