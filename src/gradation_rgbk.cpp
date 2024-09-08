#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#define SIZEX 1920
#define SIZEY 1080
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
/* SVGのヘッダを出力 指定座標でキャンバスサイズとビューポイント */
void start(Pos, Pos, string, ofstream&);
/* SVGタグを閉じる */
void finish(ofstream&);
/* 矩形(長方形)を出力 */
void rect(Pos, Pos, RGB, ofstream&);

int main(){
    // string fName = "gradation_red.svg";
    // string fName = "gradation_green.svg";
    string fName = "gradation_rgbk.svg";

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
    const uint r = 7;
    const uint offset = 64;
    pos1.y = 0;
    rect(pos1, Pos{pos1.x + offset, pos1.y + 1080}, RGB{255, 255, 255}, fout);
    for (uint x = 0; x < 256; x++) {
        pos1.x = offset + x * r;
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{x, 0, 0}, fout);
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{0, x, 0}, fout);
        rect(pos1, Pos{pos1.x + r, pos1.y + 270}, RGB{x, 0, 0}, fout);
    }
    pos1 = {0.0, 270.0};
    for (uint x = 0; x < 256; x++) {
        pos1.x = offset + x * r;
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{x, 0, 0}, fout);
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{0, x, 0}, fout);
        rect(pos1, Pos{pos1.x + r, pos1.y + 270}, RGB{0, x, 0}, fout);
    }
    pos1 = {0.0, 540.0};
    for (uint x = 0; x < 256; x++) {
        pos1.x = offset + x * r;
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{x, 0, 0}, fout);
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{0, x, 0}, fout);
        rect(pos1, Pos{pos1.x + r, pos1.y + 270}, RGB{0, 0, x}, fout);
    }
    pos1 = {0.0, 810.0};
    for (uint x = 0; x < 256; x++) {
        pos1.x = offset + x * r;
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{x, 0, 0}, fout);
        // rect(pos1, Pos{pos1.x + r, pos1.y + 1080}, RGB{0, x, 0}, fout);
        rect(pos1, Pos{pos1.x + r, pos1.y + 270}, RGB{x, x, x}, fout);
    }
    // pos1.x = offset + 256 * r;
    pos1.y = 0;
    rect(pos1, Pos{pos1.x + offset, pos1.y + 1080}, RGB{0, 0, 0}, fout);
    finish(fout);
    fout.close();
    return 0;
}

/* SVG出力用関数 */
void start(Pos pos1, Pos pos2, string unit, ofstream& fout){
    fout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n  \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg version=\"1.1\" width=\"" << pos2.x << unit << "\" height=\"" << pos2.y << unit << "\"\n  viewBox=\"" << pos1.x << ' ' << pos1.y << ' ' << 1920 << ' ' << 1080 << "\"\n  preserveAspectRatio=\"xMidYMid\"\n  fill-rule=\"evenodd\"\n  xmlns=\"http://www.w3.org/2000/svg\"\n  xmlns:xlink=\"http://www.w3.org/1999/xlink\">" << endl;
    return;
}
void finish(ofstream& fout){
    fout << "</svg>" << endl;
    return;
}
void rect(Pos pos1, Pos pos2, RGB rgb, ofstream& fout){
    fout << "<rect x=\"" << pos1.x << "\" y=\"" << pos1.y << "\" width=\"" << pos2.x - pos1.x << "\" height=\"" << pos2.y - pos1.y << "\" style=\" fill:#" << setw(2) << hex << rgb.r << setw(2) << rgb.g << setw(2) << rgb.b << dec << "\" />" << endl;
    return;
}