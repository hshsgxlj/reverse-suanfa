#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    // 1. 题目中硬编码的目标字符串
    // 注意：C++中字符串可以直接定义，不需要像C那样担心长度
    string target = "DH~mqqvqxB^||zll@Jq~jkwpmvez{";

    // 2. 存储解密结果的字符串
    string flag = "";

    // 3. 密钥 (0x1F)
    char key = 0x1F;
    cout << "[*] 目标字符串: " << target << endl;

    // 4. 遍历字符串进行逆向异或操作
    for (int i = 0; i < target.length(); i++) {
        // 核心逆向逻辑：Input = Target ^ Key
        // 原理：(Input ^ Key) ^ Key = Input
        char decrypted_char = target[i] ^ key;
        flag += decrypted_char;
    }

    // 5. 输出结果
    cout << "------------------------------------------------" << endl;
    cout << "[*] 解密结果: " << flag << endl;
    cout << "------------------------------------------------" << endl;


    return 0;
}