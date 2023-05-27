#include<iostream>
#include<fstream>
using namespace std;
void Sort(int A[], int q,int r){ 
    int temp;
        int i=q;
        int j=r;
        int x = A[(q+r) / 2]; //Lấy phần tử giữa của dãy cần sắp thứ tự làm chốt
    do
    {  // Phân đoạn dãy con a[q],..., a[r]
        while (A[i] < x)  i++; //Tìm phần tử đầu tiên có trị lớn hơn hay bằng x

        while (A[j] > x)  j--; //Tìm phần tử đầu tiên có trị nhỏ hơn hay bằng x

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

void Quick_Sort(int A[], int n){ 
    Sort( A,0,n-1);	// Gọi hàm Sort với phần tử đầu có chỉ số 0 đến 	// phần tử cuối cùng có chỉ số n-1
}
void Chia_file(ifstream &ifs, ofstream &f_Tb1, ofstream &f_Tb2, int n){
    int a[n]; // temp
    bool check = false;
    if(!ifs){
        cout << "Khong mo duoc";
        return;
    }
    while(!ifs.eof()){
        for(int i = 0; i < n; i++){ // push vao mang
            ifs >> a[i];
            if(ifs.eof()){ // nếu là vị trí cuối của file thì break;
                check = true;
                n = i+1; // đếm số lượng phần tử cuối cùng // số lượng của runs cuối cùng 
                break;
            } 
        }
        Quick_Sort(a, n); // sap xep

        for(int i = 0; i < n; i++){ // Push Tb1
            f_Tb1 << a[i] << " ";
        }

        if(check){ // thoát 
            return;
        } 
        for(int i = 0; i < n; i++){ // push vao mang
            ifs >> a[i];
            if(ifs.eof()){ // nếu là vị trí cuối của file thì break;
                n=i+1; // đếm số lượng phần tử cuối cùng
                break;
            } 
        }
        Quick_Sort(a, n); // sắp xếp
        for(int i = 0; i < n; i++){ // Push Tb2
            f_Tb2 << a[i] << " ";
        }
    }
}
void merge_sort(ifstream &f_Tb1,ifstream &f_Tb2,ofstream &f_Ta1,ofstream &f_Ta2, int n){
    int a,b,i(1),j(1);

    while(!f_Tb1.eof() && !f_Tb2.eof()){ // cả 2 file đều ở cuối thì mới dừng
        f_Tb1 >> a; // đọc 1 phần tử ở file Tba1
        f_Tb2 >> b;// đọc 1 phần tử ở file Tb2
        i=j=1; // biến đếm số lượng của mỗi lần duyệt, i là số lượng bên Tb1, j là Tb2
        // Ghi vào file Ta1
        while(i <= n && j <= n){ // n là số lượng cần duyệt của mỗi dòng 
            if(f_Tb2.eof()){ //  nếu ở cuối file Tb2 thì bưng hết số lượng phần từ Ta1 vào Tb1
                while(!f_Tb1.eof()){
                    f_Ta1 << a << " ";
                    f_Tb1 >> a;
                }
                return;
            }
            
            if(a > b){ // phần từ ở f_Tb1 > phần từ ở f_Tb2 
                f_Ta1 << b << " "; // Push vào file Tb1
                if(j < n){ // nếu j nó nhỏ hơn nút cuối cùng của số lượng cần duyệt            
                    f_Tb2 >> b; // cập nhật lại b  
                } 
                // nếu nó bằng thì không duyệt bời vì nó sẽ duyệt sang phần tử bên cạnh.
                j++; 
                // nếu không thực hiện điều kiện if ở trên j = n+1;        
                if(f_Tb2.eof()){ 
                    while(!f_Tb1.eof()){ // nếu ở cuối file Ta2 thì bưng hết số lượng phần từ Ta1 vào Tb1
                        f_Ta1 << a << " ";
                        f_Tb1 >> a;
                    }
                    return;
                }
            }
            else{
                f_Ta1 << a << " "; 
                if(i < n){
                    f_Tb1 >> a;
                }
                i++;

                if(f_Tb1.eof()){
                    while(!f_Tb2.eof()){
                        f_Ta1 << b << " ";
                        f_Tb2 >> b;
                    }
                    return;
                }

            }
            // không để i == n vì để so sánh xem nút cuối cùng có lơn hơn phần tử kia hay không, nếu nó vẫn nhỏ hơn thì lại tăng lên 1
            while(i==n+1 && j<=n){  // nếu nó i bằng số lượng cần duyệt + 1
                if(f_Tb2.eof()) return;
                f_Ta1 << b << " ";
                if(j<n) f_Tb2 >> b;
                j++;
            }
            while(j==n+1 && i<=n){
                if(f_Tb1.eof()) return;
                f_Ta1 << a << " ";
                if(i<n) f_Tb1 >> a;
                i++;
            }
        }
        // Ghi vào file Tb2
        f_Tb1 >> a;
        f_Tb2 >> b;
        i=j=1;
        while(i <= n && j<=n){
            if(f_Tb2.eof()){
                while(!f_Tb1.eof()){
                    f_Ta2 << a << " ";
                    f_Tb1 >> a;
                }
                return;
            }
            
            if(a > b){
                f_Ta2 << b << " ";     
                if(j < n){             
                    f_Tb2 >> b;   
                } 
                j++;         
                if(f_Tb2.eof()){
                    while(!f_Tb1.eof()){
                        f_Ta2 << a << " ";
                        f_Tb1 >> a;
                    }
                    return;
                }
                //
            }
            else{
                f_Ta2 << a << " "; 
                if(i<n){
                    f_Tb1 >> a; 
                }
                i++;
                 // 
                if(f_Tb1.eof()){
                    while(!f_Tb2.eof()){
                        f_Ta2 << b << " ";
                        f_Tb2 >> b;
                    }
                    return;
                }
                //
            }
            if(f_Tb1.eof() && f_Tb2.eof())  break;
            while(i==n+1 && j<=n){
                if(f_Tb2.eof()) return;
                f_Ta2 << b << " ";
                if(j<n) f_Tb2 >> b;
                j++;
            }
            while(j==n+1 && i<=n){
                if(f_Tb1.eof()) return;
                f_Ta2 << a << " ";
                if(i<n) f_Tb1 >> a;
                i++;
            }
        }          
    }
}
int main(){
    int n = 3;
    ifstream ifs("Ta.txt",ios::in);
    ofstream of_Tb1("Tb1.txt",ios::out ); 
    ofstream of_Tb2("Tb2.txt",ios::out );   
    Chia_file( ifs , of_Tb1, of_Tb2,n);
    ifs.close();
    of_Tb1.close();
    of_Tb2.close();
    while(1){
        ifstream f_Tb1("Tb1.txt",ios::in);
        ifstream f_Tb2("Tb2.txt",ios::in);
        ofstream f_Ta1("Ta1.txt",ios::out);
        ofstream f_Ta2("Ta2.txt",ios::out);
        merge_sort(f_Tb1,f_Tb2,f_Ta1,f_Ta2,n);
        f_Tb1.close();
        f_Tb2.close();
        f_Ta1.close();
        f_Ta2.close();
        ifstream ifs_Ta2("Ta2.txt"); // Nếu file Ta2 rỗng thì dừng
        ifs_Ta2.seekg(0, ios::end); // di chuyen con tro file den cuoi file
        int isEmpty = ifs_Ta2.tellg(); // lay vi tri hien tai cua con tro file
        if(isEmpty == 0){
            break;
        } 
        ifs_Ta2.close();
        n=n*2;  
        ofstream f1_Tb1("Tb1.txt",ios::out );
        ofstream f1_Tb2("Tb2.txt",ios::out );
        ifstream f1_Ta1("Ta1.txt", ios::in);
        ifstream f1_Ta2("Ta2.txt", ios::in);
        merge_sort(f1_Ta1, f1_Ta2, f1_Tb1, f1_Tb2,n); 
        f1_Tb1.close();
        f1_Tb2.close();
        f1_Ta1.close();
        f1_Ta2.close();  
        n=n*2;
    }
}