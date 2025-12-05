#include <iostream>
#include <fstream>  // 必须包含：用于文件读取
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// === 标准 RC4 初始化 (KSA) ===
void rc4_init(vector<unsigned char>& s, const string& key) {
    int len = key.length();
    s.resize(256);
    for (int i = 0; i < 256; i++) s[i] = i;

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + (unsigned char)key[i % len]) % 256;
        swap(s[i], s[j]);
    }
}
// 注意：这里 data 传的是 vector<unsigned char>，不是 string
void rc4_crypt(vector<unsigned char>& s, vector<unsigned char>& data) {
    int i = 0, j = 0, t = 0;
    // 遍历 data 中的每一个字节
    for (size_t k = 0; k < data.size(); k++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        swap(s[i], s[j]);
        t = (s[i] + s[j]) % 256;

        // 异或运算：直接修改 data 原地解密
        data[k] ^= s[t];
    }
}
// === 打印 Hex 工具 ===
void print_hex(const vector<unsigned char>& data) {
    cout << hex << uppercase << setfill('0');
    for (unsigned char c : data) {
        cout << setw(2) << (int)c << " ";
    }
    cout << dec << endl; // 恢复正常输出
}
int main() {
    string key = "[Warnning]Access_Unauthorized";

    // 读取文件
    ifstream file("enflag.txt", ios::binary);
    if (!file) return 1;
    vector<unsigned char> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // 1. 打印文件里的原始内容 (密文)
    cout << "[*] 原始文件内容 (Hex View):" << endl;
    print_hex(data); // 这样看绝对安全，不会崩！

    // 2. 解密
    vector<unsigned char> s;
    rc4_init(s, key);
    rc4_crypt(s, data);

    // 3. 打印解密后的内容 (明文)
    cout << "\n[*] 解密后的内容 (Text View):" << endl;
    for (auto c : data) cout << c;
    cout << endl;
    // 4. 添加：打印解密后的内容 (明文) 的 Hex 视图
    cout << "\n[*] 解密后的内容 (Hex View):" << endl;
    print_hex(data);
    return 0;
}