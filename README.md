# keycheck
入力されたキーを取得するだけのプログラムです。  
オプション機能として、ショートカットキーを登録してコマンドを実行することが出来ます。
### 注意
動作確認環境 : **Windows11**
## 起動方法
### コンパイル
<<<<<<< HEAD
MinGW : `g++ -g keycheck.cpp -pthread -mwindows -o keycheck.exe`  
GNUMake：`make`
=======
- Install : `GCC`
```bash
$ build.bat
```
>>>>>>> b05b0ab20481e35d804db7c14d752a0ec5f8c713

## 特殊キーについて
|       特殊キー      |        キー名       |
| -----------------  | ------------------- |
|     左Shift        |       `LSHIFT`        |
|     右Shift        |       `RSHIFT`        |
|     左CTRL         |       `LCTRL`         |
|     右CTRL         |       `RCTRL`         |
|     左Alt          |        `LALT`         |
|     右Alt          |        `RALT`         |
|     Space          |        `SPACE`        |
|     左Win          |        `LWIN`         |
|     右Win          |        `RWIN`         |
|     上             |        `UP`           |
|     下             |        `DOWN`         |
|     左             |        `LEFT`         |
|     右             |        `RIGHT`        |
|     Enter          |        `ENTER`        |
|     Esc            |        `ESC`          |
|     左クリック      |        `LCLICK`       |
|     右クリック      |        `RCLICK`       |
|     F1 ～ F12      |        `F1`～`F12`     |
|     ,              |        `COMMA`       |
|     /              |        `/`           |
|     \              |        `\`           |
|    [               |        `[`           |
|     ]              |        `]`           |
|     @              |        `@`           |
|     -              |        `-`           |
|     ;              |        `;`           |
