#include <iostream>
#include<string>
#include <cstdlib>
#define MAX 1000
using namespace std;
struct person {
    string name;
    int sex;//1男2女
    int age;
    string phone;
    string addr;
};
struct addressbooks {
    struct person personarray[MAX];
    int site;
};
void addperson(addressbooks* ppp) {
    //判断是否可以增加
    if (ppp->site == MAX) {
        cout << "已满" << endl;
        return;
    }
    else {
        string name;
        cout << "请输入姓名" << endl;
        cin >> name;
        ppp->personarray[ppp->site].name = name;
        cout << "请输入性别" << endl;
        cout << "1---男" << endl;
        cout << "2---女" << endl;
        int sex = 0;
        while (true) {
            cin >> sex;
            if (sex == 1 || sex == 2) {
                ppp->personarray[ppp->site].sex = sex;
                break;
            }
            cout << "输入有误，请重新输入" << endl;
        }
        cout << "请输入年龄" << endl;
        int age = 0;
        cin >> age;
        ppp->personarray[ppp->site].age = age;
        string tele ;
        cout << "请输入电话" << endl;
        cin >> tele;
        ppp->personarray[ppp->site].phone = tele;
        cout << "请输入住址" << endl;
        string address;
        cin >> address;
        ppp->personarray[ppp->site].addr = address;
        ppp->site++;
        cout << "添加成功" << endl;
        std::system("pause");
        std::system("cls");//清屏
    }
}
// 菜单界面函数
void showperson(addressbooks* ppp) {
    if (ppp->site == 0) {
        cout << "目前没有加入联系人" << endl;
    }
    else {
        for (int i = 0;i < ppp->site;i++) {
            cout << "姓名" << ppp->personarray[i].name << "\t";
            cout << "性别" << (ppp->personarray[i].sex==1?"男":"女" )<< "\t";
            cout << "年龄" << ppp->personarray[i].age << "\t";
            cout << "电话" << ppp->personarray[i].phone << "\t";
            cout << "地址" << ppp->personarray[i].addr << "\t";
        }
    }
    std::system("pause");
    std::system("cls");
}
int  findperson(addressbooks*ppp,string name) {
    for (int i = 0;i < ppp->site;i++)
    {
        if (ppp->personarray[i].name==name) {
            return i;

        }
    }
    return -1;
}
void checkperson(addressbooks &ppp) {
    cout << "请输入你要查找的联系人" << endl;
    string name;

    cin >> name;
    int ret = findperson(&ppp, name);
    if (ret != -1) {
        cout << "找到此人" << endl;
        cout << "姓名：" << ppp.personarray[ret].name << "\t";
        cout << "性别：" << (ppp.personarray[ret].sex == 1 ? "男" : "女") << "\t";
        cout << "年龄：" << ppp.personarray[ret].age <<"\t";
        cout << "电话：" << ppp.personarray[ret].phone << "\t";
        cout << "住址：" << ppp.personarray[ret].addr << "\t";
    }
    else {
        cout << "查无此人" << endl;
    }
    std::system("pause");
    std::system("cls");
    return;
}
void deleteperson(addressbooks *ppp) {
    cout << "请输入要删除的联系人" << endl;
    string name;
    cin >> name;
    int ret=findperson(ppp,name);
    if (ret != -1) {
        for (int i = ret;i < ppp->site;i++) {
            ppp->personarray[i] = ppp->personarray[i + 1];
        }
        ppp->site--;
    }
    else {
        cout << "查无此人" << endl;
    }
    std::system("pause");
    std::system("cls");
}
void changeperson(addressbooks*ppp) {
    cout << "请输入要更改的联系人的名称" << endl;
    string name;
    cin >> name;
    int ret = findperson(ppp, name);
    if (ret != -1) {
        cout << "请输入修改的对象" << endl;
        cout << "1,姓名 2.性别 3.年龄 4.电话 5.住址" << endl;
        int choose = 0;
        cin >> choose;
        switch (choose) {
            
        case 1: {
            string newname;
            cout << "请输入新名字" << endl;
            cin >> newname;
            ppp->personarray[ret].name = newname;
            cout<<"修改成功"<<endl;
        }
        case 2: {
            int newsex = 0;
            cout << "请输入新性别1，男生 2，女生" << endl;
            cin >> newsex;
            ppp->personarray[ret].sex = newsex;
            cout << "修改成功" << endl;
            break;
        }
        case 3: {
            int newage;
            cout << "请输入新年龄" << endl;
            cin >> newage;
            ppp->personarray[ret].age = newage;
            cout << "修改成功" << endl;
            break;
        }
        case 4: {
            string newphone;
            cout << "请输入新电话" << endl;
            cin >> newphone;
            ppp->personarray[ret].phone = newphone;
            cout << "修改成功" << endl;
            break;
        }
        case 5: {
            string newaddr;
            cout << "请输入新地址" << endl;
            cin >> newaddr;
            ppp->personarray[ret].addr = newaddr;
            cout << "修改成功" << endl;
            break;
        }
        case 0:
            break;
        }
    }
    else {
        cout << "查无此人" << endl;
        
    }
    std::system("pause");
    std::system("cls");
}
void showMenu() {
    cout << "*****************************" << endl;
    cout << "***** 1、添加联系人 *****" << endl;
    cout << "***** 2、显示联系人 *****" << endl;
    cout << "***** 3、删除联系人 *****" << endl;
    cout << "***** 4、查找联系人 *****" << endl;
    cout << "***** 5、修改联系人 *****" << endl;
    cout << "***** 6、清空联系人 *****" << endl;
    cout << "***** 0、退出通讯录 *****" << endl;
    cout << "*****************************" << endl;
}
void cleanperson(addressbooks *ppp ) {
    ppp->site = 0;
    cout << "通讯录已清空" << endl;
    std::system("pause");
    std::system("cls");
}
int main() {
    int select = 0; // 用于存储用户输入的选择
    addressbooks ppp;
    ppp.site = 0;
    while (true) {
        // 1. 调用菜单界面 
        showMenu();

        // 2. 接收用户输入
        cout << "请输入您的选择: ";
        cin >> select;

        // 3. 根据用户输入进行分支判断
        switch (select) {
        case 1: // 1、添加联系人
            addperson(&ppp);// 后续在这里补全添加联系人的逻辑
            break;
        case 2: // 2、显示联系人
            showperson(&ppp);
            break;
        case 3: // 3、删除联系人
            deleteperson(&ppp);
            break;
        case 4: // 4、查找联系人
            checkperson(ppp);
            break;
        case 5: // 5、修改联系人
            changeperson(&ppp);
            break;
        case 6: // 6、清空联系人
            
            break;
        case 0: // 0、退出通讯录
            cout << "welcome use again" << endl;
            system("pause"); // 截图中出现“请按任意键继续...”就是这句代码的作用
            return 0;        // 结束主函数，退出程序
        default:
            cout << "输入有误，请重新输入" << endl;
            std::system("pause");
            std::system("cls"); // 清屏，重新显示菜单
            break;
        }
    }
    return 0;
} 