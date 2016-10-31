//gcd實作
//輸入方法：輸入一行包含兩個整數（各4 x SIZE位數以下）的字串，兩個整數以空格隔開
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
using namespace std;

const int SIZE = 4;

class BigNumber{
private:
	int a[SIZE];
public:
	BigNumber(string str){
		assert(str.length() <= 9 * SIZE);
		for(int i = 0;i < SIZE;i++){
			a[i] = 0;
		}
		stringstream ss;
		int t = (str.length() - 1) / 9;
		for(int i = 0;i < t;i++){
			string sub = str.substr(str.length() - 9, 9);
			ss << sub;
			ss >> a[i];
			ss.clear();
			ss.str("");
			str = str.erase(str.length() - 9, 9);
		}
		ss << str;
		ss >> a[t];
	}
	BigNumber(const BigNumber& n){
		for(int i = 0;i < SIZE;i++){
			a[i] = n.a[i];
		}
	}
	size_t digit() const{
		stringstream ss;
		ss << (*this);
		string str = ss.str();
		return str.length();
	}
	bool operator == (int n) const{
		for(int i = 1;i < SIZE;i++){
			if(a[i]){
				return false;
			}
		}
		if(a[0] == n){
			return true;
		}
		return false;
	}
	bool operator != (int n) const{
		return !(*this == n);
	}
	bool operator == (const BigNumber& n) const{
		for(int i = 0;i < SIZE;i++){
			if(a[i] != n.a[i]){
				return false;
			}
		}
		return true;
	}
	bool operator != (const BigNumber& n) const{
		return !(*this == n);
	}
	bool operator < (const BigNumber& n) const{
		for(int i = SIZE - 1;i >= 0;i--){
			if(a[i] > n.a[i]){
				return false;
			}else if(a[i] < n.a[i]){
				return true;
			}
		}
		return false; //equal
	}
	bool operator <= (const BigNumber& n) const{
		return (*this) < n || (*this) == n;
	}
	bool operator > (int n) const{
		for(int i = SIZE - 1;i > 0;i--){
			if(a[i]){
				return true;
			}
		}
		if(a[0] > n){
			return true;
		}
		return false;
	}
	const BigNumber& operator = (const BigNumber& n){
		for(int i = 0;i < SIZE;i++){
			a[i] = n.a[i];
		}
		return (*this);
	}
	const BigNumber operator - (const BigNumber& n) const{
		BigNumber sol(*this);
		for(int i = 0;i < SIZE;i++){
			sol.a[i] -= n.a[i];
			if(sol.a[i] < 0 && i < SIZE - 1){
				sol.a[i + 1] --;
				sol.a[i] += 1000000000;
			}
		}
		return sol;
	}
	const BigNumber& operator -= (const BigNumber& n){
		(*this) = (*this) - n;
		return (*this);
	}
	const BigNumber& operator *= (int n){ //pseudomultiple
		stringstream ss;
		ss << (*this) << 0;
		string str = ss.str();
		BigNumber temp(str);
		(*this) = temp;
		return (*this);
	}
	const BigNumber operator * (int n) const{ //pseudomultiple
		BigNumber temp = (*this);
		temp *= 10;
		return temp;
	}
	const BigNumber& operator %= (const BigNumber& n){ //pseudomodule
		int t = digit() - n.digit();
		BigNumber temp = n;
		for(int i = 1;i < t;i++){
			temp *= 10;
		}
		if(t > 0 && temp * 10 <= (*this)){
			temp *= 10;
		}
		(*this) -= temp;
		return (*this);
	}
	const BigNumber operator % (const BigNumber& n) const{ //pseudomodule
		BigNumber temp = (*this);
		temp %= n;
		return temp;
	}
	friend ostream& operator << (ostream& os, const BigNumber& n);
};

ostream& operator << (ostream& os, const BigNumber& n){
	for(int i = SIZE - 1;i >= 0;i--){
		if(n.a[i] != 0){
			os << n.a[i];
			for(int j = i - 1;j >= 0;j--){
				os.width(9);
				os.fill('0');
				os << n.a[j];
			}
			break;
		}else if(i == 0){
			os << 0;
		}
	}
	return os;
}

int main(){
	string str;
	getline(cin, str);
	BigNumber n(str.substr(0, str.find(' ')));
	BigNumber p(str.substr(str.find(' ') + 1, str.length() - str.find(' ') - 1));
	while(n > 1 && p > 1 && n != p){
		if(n < p){
			p %= n;
		}else{
			n %= p;
		}
	}
	if(n == p){
		cout << n;
	}else if(n == 0){
		cout << p;
	}else if(p == 0){
		cout << n;
	}else{
		cout << 1;
	}
	return 0;
}
