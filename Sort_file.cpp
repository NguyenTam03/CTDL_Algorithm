#include<iostream>
#include<fstream>
using namespace std;
struct info{
    string masv;
    int pos_MSSV;
};
void Sort(info A[], int q,int r){ 
    info temp;
        int i=q;
        int j=r;
        string x = A[(q+r) / 2].masv; //Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
    do
    {  // Phân đoạn dãy con a[q],..., a[r]
        while (A[i].masv < x)  i++; //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

        while (A[j].masv > x)  j--; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x

        if (i<=j){  // Doi cho A[i] voi A[j]
            temp = A[i];       A[i] =A[j];       A[j] = temp;
            i++ ;  j--;
        }
    } while (i<=j);
    if (q<j) 	// phần thứ nhất có từ 2 phần tử trở lên
        Sort(A,q,j);
    if (i<r)   	// phần thứ ba có từ 2 phần tử trở lên
        Sort (A,i,r);
}
void Quick_Sort(info A[], int n){ 
    Sort( A,0,n-1);	// Gọi hàm Sort với phần tử đầu có chỉ số 0 đến 	// phần tử cuối cùng có chỉ số n-1
}
int main(){
    int n=200;
    info a[n];
    ifstream ifs("dssv.bat",ios::in | ios::binary);
    string s;
    int i = 0;
    int temp =0;
    while(!ifs.eof()){
        getline(ifs,s);
        for(int j=0;j<s.length();j++){
            if(s[j]==',')   break;
            a[i].masv+=s[j];
        }
        a[i].pos_MSSV = temp;
        temp += s.length()+1; // +1 la ky tu \n or temp += sizeof(s[0]) * s.length() + 1;
        // nếu đúng theo đề là temp += 1024;
        i++;
    }
    ifs.close();
    Quick_Sort(a,n);
    ifstream ifs1("dssv.bat",ios::in | ios::binary);
    ofstream ofs("res.bat",ios::out | ios::binary);
    int b = 0, pos_MSSV = 0;
    for(int i=0;i<n;i++){
        ifs1.seekg(a[i].pos_MSSV,ios::beg);
        getline(ifs1,s);
        ofs << s << endl;
    }
    ifs1.close();
    ofs.close();
}
