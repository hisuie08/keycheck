#include "ioset.cpp"

int main(void){
    IOSet io;
    io.title("ƒwƒ‹ƒv");
    io.print(io.read_file(io.dir()+"/text/readme"));
    io.cmd("pause>nul");
    return 0;
}