#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // 用于 swap

using namespace std;

// 初始化 RC4 (KSA: Key Scheduling Algorithm)
// S 盒应该使用 vector<unsigned char> 以确保处理 0-255 的数值
void rc4_init(vector<unsigned char>& s, const string& key)
{
	int len = key.length();
	s.resize(256); // 确保 S 盒大小为 256

	// 1. 标准初始化：S[i] = i
	for (int i = 0; i < 256; i++) {
		s[i] = i;
	}

	// 2. 打乱 S 盒
	int j = 0;
	for (int i = 0; i < 256; i++) {
		// 核心公式：j = (j + S[i] + key[i % key_len]) % 256
		j = (j + s[i] + (unsigned char)key[i % len]) % 256;

		// 交换 S[i] 和 S[j]
		swap(s[i], s[j]);
	}
}

// 加密/解密过程 (PRGA: Pseudo-Random Generation Algorithm)
void rc4_crypt(vector<unsigned char>& s, string& data)
{
	int i = 0, j = 0, t = 0;
	unsigned long len = data.length();

	// 这里的 S 盒必须是副本或者重新初始化过的，
	// 因为 RC4 是流密码，S 盒的状态会随着加密过程改变。
	// 如果要解密，需要用原始密钥重新生成初始 S 盒。

	for (unsigned long k = 0; k < len; k++) {
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;

		swap(s[i], s[j]);

		t = (s[i] + s[j]) % 256;

		// 异或运算进行加密/解密
		data[k] ^= s[t];
	}
}

int main() {
	string key = " ";
	string text = " ";

	cout << "原始数据: " << text << endl;

	// 1. 初始化 S 盒
	vector<unsigned char> s;
	rc4_init(s, key);

	// 2. 加密
	// 注意：为了演示，这里创建 S 盒的副本用于加密，保留原 S 盒状态可能用于重置
	// 但在标准流程中，通常每次操作都重新 init
	vector<unsigned char> s_encrypt = s;
	rc4_crypt(s_encrypt, text);
	cout << "加密后 (乱码): " << text << endl;

	// 3. 解密 (RC4 是对称加密，再次异或即可还原，但必须重置 S 盒)
	// 重新初始化 S 盒以获得初始状态
	vector<unsigned char> s_decrypt;
	rc4_init(s_decrypt, key);

	rc4_crypt(s_decrypt, text);
	cout << "解密后: " << text << endl;

	return 0;
}