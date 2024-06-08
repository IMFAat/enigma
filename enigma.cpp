#include <iostream>
#include <string>
#include <cmath>
#include<vector>
#include<algorithm>
using namespace std;
int i=0,j=0,h=0,g=0;
class rotor_twsix{
    public:
        void start_rand(){
            srand(114514);
            for(h=0;h<rp;h++){
                for(i=0;i<26;i++){
                    if(i==0){
                        r_begin.push_back(rand()%26);
                    }
                    else{
                        r_begin.push_back(rand()%26);
                        for(j=0;j<i;j++){
                            if(r_begin.at(j)==r_begin.at(i)){
                                i--;
                                r_begin.pop_back();
                                break;
                            }
                        }
                    }     
                }
                r_b.push_back(r_begin);
                r_begin.clear();
            }
            srand(228922);
            for(h=0;h<rp;h++){
                for(i=0;i<26;i++){
                    if(i==0){
                        r_begin.push_back(rand()%26);
                    }
                    else{
                        r_begin.push_back(rand()%26);
                        for(j=0;j<i;j++){
                            if(r_begin.at(j)==r_begin.at(i)){
                                i--;
                                r_begin.pop_back();
                                break;
                            }
                        }
                    }     
                }
                r_c.push_back(r_begin);
                r_begin.clear();
                con.push_back(0);
            }
        }
        void get_pswd(int a){
            pswd.push_back(a);
        }
        void get_rp(int a){
            rp=a;
        }
        void swith(char c_1,char c_2){
            int index_1,index_2;
            for(i=0;i<sizeof(r_a);i++){
                if(r_a[i]==c_1)
                    index_1=i;
                if(r_a[i]==c_2)
                    index_2=i;
            }
            r_a[index_1]=c_2;
            r_a[index_2]=c_1;
        }
        void rotate(){
            int cop_b[sizeof(r_a)]={},cop_c[sizeof(r_a)]={};
            for(i=0;i<rp;i++){
                for(j=0;j<sizeof(r_a);j++){
                    cop_b[j]=r_b[i][j];
                    cop_c[j]=r_c[i][j];
                }
                for(j=0;j<sizeof(r_a);j++){
                    if(j+pswd[i]+con[i]>25){
                        r_b[i][j]=cop_b[j+pswd[i]+con[i]-26];
                        r_c[i][j]=cop_c[j+pswd[i]+con[i]-26];
                    }
                    else{
                        r_b[i][j]=cop_b[j+pswd[i]+con[i]];
                        r_c[i][j]=cop_c[j+pswd[i]+con[i]];
                    }
                }
            }
        }
        void encode(string str_1){
            for(i=0;i<str_1.length();i++){
                int index=0,judge=0;
                for(j=0;j<26;j++){
                    if(str_1[i]==r_a[j])
                        judge=1;
                }
                if(judge==0){
                    cout<<str_1[i];
                    continue;
                }
                for(j=0;j<rp;j++){
                    if(j==0){
                        for(h=0;h<26;h++){
                            if(str_1[i]==r_a[h]){
                                index=h;
                                break;
                            }
                        }
                    }
                    for(h=0;h<26;h++){
                        if(r_b[j][index]==r_c[j][h]){
                            index=h;
                            break;
                        }
                    }
                }
                for(j=0;j<26;j++){
                    if(reflect[index]==reflect[j]&&j!=index){
                        index=j;
                        break;
                    }
                }
                for(j=rp-1;j>=0;j--){
                    for(h=0;h<26;h++){
                        if(r_c[j][index]==r_b[j][h]){
                            index=h;
                            break;
                        }
                    }
                    if(j==0){
                        cout<<r_a[index];
                    }
                }
            }
            cout<<endl;
        }
        void counter(){
            con[0]++;
            for(j=0;j<rp;j++){
                if(con[j]>25){
                    con[j+1]++;
                    con[j]=0;
                }
            }
        }
        void test(){
            for(i=0;i<r_c.size();i++){
                for(j=0;j<26;j++){
                    cout<<r_b[i][j]<<" ";
                }
                cout<<endl;
                for(j=0;j<26;j++){
                    cout<<r_c[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<"rp:"<<rp<<endl;
            cout<<"r_a:";
            for(i=0;i<sizeof(r_a);i++)
                cout<<r_a[i];
            cout<<endl;
            cout<<"pswd:";
            for(i=0;i<pswd.size();i++)
                cout<<pswd[i];
            cout<<endl;
            cout<<"con:";
            for(i=0;i<con.size();i++){
                cout<<con[i]<<" ";
            }
            cout<<endl;
        }
        void clear(){
            char r_a[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
            r_b.clear();
            r_c.clear();
            pswd.clear();
            con.clear();
            rp=0;
        }
    private:
        int reflect[26]={11,3,9,11,8,12,1,7,2,7,10,13,6,6,12,13,8,5,3,10,5,4,9,1,4,2};
        char r_a[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        vector<vector<int>> r_b,r_c;
        vector<int> pswd,con,r_begin;
        int rp=0;
};
int main(){ 
    while(true){
        rotor_twsix a;
        int rp,sw_line,sp;
        char c_1,c_2;
        string str_1;
        cout<<"請輸入轉子數:";
        cin>>rp;
        a.get_rp(rp);
        cout<<endl<<"請輸入密鑰(0~25):";
        for(i=0;i<rp;i++){
            cin>>sp;
            a.get_pswd(sp);
        }
        cout<<endl<<"請輸入交換線數:";
        cin>>sw_line;
        cout<<endl;
        if(sw_line!=0){
            cout<<"請輸入要交換的字母:";
            for(i=0;i<sw_line;i++){
                cin>>c_1>>c_2;
                a.swith(c_1,c_2);
            }
            cout<<endl;
        }
        a.start_rand();
        a.rotate();
        cin.ignore(114514,'\n');//endl
        while(true){
            cout<<"請輸入密碼或明文(輸入test查看當前的密碼表、輸入agepep重製機器”):";
            getline(cin,str_1);
            if(str_1=="agepep"){
                a.clear();
                break;
            }
            else if(str_1=="test"){
                str_1="a b c d e f g h i j k l m n o p q r s t u v w x y z";
                cout<<"明文:"<<str_1<<endl<<"密碼:";
                a.encode(str_1);
            }
            else{
                a.encode(str_1);
                a.counter();
                a.rotate();
            }
            
        }
    }    
}
