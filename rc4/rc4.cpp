#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
//初始化S盒，用密钥轮转生成T，S和T加密
using namespace std;
void rc4_init(vector<unsigned char>& s, const string& key)
{
	int len = key.length();
	s.resize(256); 
	for (int i = 0; i < 256; i++) {
		s[i] = i;
	}
	int j = 0;
	for (int i = 0; i < 256; i++) {
		j = (j + s[i] + (unsigned char)key[i % len]) % 256;//T盒轮转+加密
		swap(s[i], s[j]);
	}
}
void rc4_crypt(vector<unsigned char>& s, string& data)
{
	int i = 0, j = 0, t = 0;
	unsigned long len = data.length();
	for (unsigned long k = 0; k < len; k++) {
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;

		swap(s[i], s[j]);

		t = (s[i] + s[j]) % 256;
		data[k] ^= s[t];
	}
}

int main() {
	string key = "[Warnning]Access_Unauthorized";
	string text = "脗?鯨6;Y棠轳?睎5";

	cout << "原始数据: " << text << endl;
	cout << "key: " << key << endl;
	vector<unsigned char> s;
	rc4_init(s, key);
	vector<unsigned char> s_encrypt = s;
	rc4_crypt(s_encrypt, text);
	cout << "加密后 (乱码): " << text << endl;
	vector<unsigned char> s_decrypt;
	rc4_init(s_decrypt, key);
	rc4_crypt(s_decrypt, text);
	cout << "解密后: " << text << endl;
	return 0;
}