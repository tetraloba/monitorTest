#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#define SIZEX 800
#define SIZEY 800
using namespace std;
typedef unsigned int uint;
struct Pos{
    double x;
    double y;
};
struct RGB{
    uint r;
    uint g;
    uint b;
};
int pow(int a, int b){
    int ans = 1;
    for (int i = 0; i < b; i++) {
        ans *= a;
    }
    return ans;
}
/* SVGのヘッダを出力 指定座標でキャンバスサイズとビューポイント */
void start(Pos, Pos, string, ofstream&);
/* SVGタグを閉じる */
void finish(ofstream&);
/* 直線を出力 */
void line(Pos, Pos, RGB, ofstream&);
/* 矩形(長方形)を出力 */
void rect(Pos, Pos, RGB, ofstream&);
/* 円を出力 */
void circle(Pos, Pos, RGB, ofstream&);
/* 文字を出力 */
void text(Pos, string, RGB, uint, ofstream&);

int main(){
    // string fName = "colorChart_red.svg"; // RED
    string fName = "colorChart_green.svg"; // GREEN
    // string fName = "colorChart_blue.svg"; // BLUE

    ofstream fout(fName);
    if (!fout) {
        cout << "ファイル(" << fName << ")が開けません" << endl;
        return 1;
    }
    fout.fill('0');
    Pos pos1{0.0, 0.0};
    Pos pos2{SIZEX, SIZEY};
    string unit = "px";
    start(pos1, pos2, unit, fout);
    RGB rgb{0, 0, 0};
    rect(pos1, pos2, rgb, fout);
    const int r = 50;
    for (uint y = 0; y < 16; y++) {
        for (uint x = 0; x < 16; x++) {
            pos1.x = x * r;
            pos1.y = y * r;
            // rect(pos1, Pos{pos1.x + r, pos1.y + r}, RGB{y * 16 + x, 0, 0}, fout); // RED
            rect(pos1, Pos{pos1.x + r, pos1.y + r}, RGB{0, y * 16 + x, 0}, fout); // GREEN
            // rect(pos1, Pos{pos1.x + r, pos1.y + r}, RGB{0, 0, y * 16 + x}, fout); // BLUE
        }
    }
    finish(fout);
    fout.close();
    return 0;
}

/* SVG出力用関数 */
void start(Pos pos1, Pos pos2, string unit, ofstream& fout){
    fout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg version=\"1.1\" width=\"" << pos2.x << unit << "\" height=\"" << pos2.y << unit << "\"\n  viewBox=\"" << pos1.x << ' ' << pos1.y << ' ' << 800 << ' ' << 800 << "\"\n  preserveAspectRatio=\"xMidYMid\"\n  fill-rule=\"evenodd\"\n  xmlns=\"http://www.w3.org/2000/svg\"\n  xmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;
    return;
}
void finish(ofstream& fout){
    fout << "</svg>" << endl;
    return;
}
void text(Pos pos, string str, RGB rgb, uint size, ofstream& fout){
    fout << "<text x=\"" << pos.x << "\" y=\"" << pos.y << "\" font-family=\"Verdana\" font-size=\"" << size << "\" stroke=\"none\" fill=\"#" << hex << setw(2) << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\">\n  " << str << "\n</text>" << endl;
    return;
}
void circle(Pos pos1, Pos pos2, RGB rgb, ofstream& fout){
    const double strokeWidth = 8.0;
    fout << "<circle cx=\"" << pos1.x << "\" cy=\"" << pos1.y << "\" r=\"" << pos2.x - pos1.x << "\" fill=\"none\" stroke=\"#" << hex << setw(2) << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" stroke-width=\"" << strokeWidth << "\" />" << endl;
    return;
}
void rect(Pos pos1, Pos pos2, RGB rgb, ofstream& fout){
    fout << "<rect x=\"" << pos1.x << "\" y=\"" << pos1.y << "\" width=\"" << pos2.x - pos1.x << "\" height=\"" << pos2.y - pos1.y << "\" style=\" fill:#" << setw(2) << hex << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" />" << endl;
    return;
}
void line(Pos pos1, Pos pos2, RGB rgb, ofstream& fout){
    fout << "<line x1=\"" << fixed << pos1.x << "\" y1=\"" << pos1.y << "\" x2=\"" << pos2.x << "\" y2=\"" << pos2.y << "\" stroke=\"#" << hex << setw(2) << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" stroke-width=\"" << 1 << "\" stroke-opacity=\"" << 1 << "\" stroke-linecap=\"round\" />" << endl;
    return;
}