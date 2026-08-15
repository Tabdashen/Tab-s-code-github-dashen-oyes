// 游戏名：《战神》或者《战神1》 右边的名字叫的多，因为以后还要更新战神2。
// 战神1
// 作者原创
// 作者：岚光、米饭蒸螃蟹，谢XX，Tab666，超级小蟹
// 禁止抄袭（特例奖光，许XX，Space999，借鉴了我（他的话，我已许可，不算抄袭），他做的目前叫《战神剧情版1》）
// 由于我还算个蒟蒻，所以不喜勿喷
// 向着神犇前进
// 作为一个GESP3级几乎满分通过的OIer，我感到我做的是多么不可思议，只能说:
// 666
// 共计800余行代码
// 我选择紧凑的写法，我的内容也多！
// 可以让玩家体验得更好
// 是我这个游戏作者的职责！！！
// 希望大家喜欢我的游戏！！！！！！！！！！

/*
更新日志：
2025/11/8：游戏诞生日！！！并且做了大多数游戏内容、框架，如个人数据，商店、部分打怪和打药
2025/11/9：做了打怪部分、怪兽结构体，增加商品"不死图腾"。我还重构了代码，把玩家数据做成结构体，把大多数功能封装成函数。
           完善了战斗系统，平衡了怪物数值，完成了完整游戏流程！
2025/11/10：添加了存档功能，现在可以保存和加载游戏进度了！
2026/01/10：完善了法术值
2026/03/03：官方发现有部分玩家恶意通过bug（其实也不算bug）刷金币，于是官方将通关难度大增。具体游玩见晓。但是超级勇士也变强了。
战神之剑、战神盔甲、
战神法杖以及战神医疗包也被加强。
游戏更加丰富啦！！！
（恶龙是不是有点太强了？）
2026/03/26：题外话：今天打字比赛打完了，是一等奖！
回到正题，今天加了一个开始游戏的特效，和那些大型游戏一样的制作方logo展示！游戏变得更加正式，更加完整！（完全是人工手绘。（本来想用AI，但是AI太傻了，根本不会画！）
2026/03/27：优化了开始游戏的特效
2026/03/28：为了防止某些玩家利用某种bug(bushi
，来重复某个/某些按键，以将角色的数值提高，实现以秒为单位的速通，所以，今天，我要干一件，逆天的事情。
我将把各种说话的地方加上Sleep等待函数，以防止刷数值！
并且使用豆包重新渲染了码风
2026/04/07：重大更新！！！我把开始特效优化了。而且，我几乎使每一个输出都变成了逐帧输出，类似于某些角色扮演游戏中NPC
说话的那种字一个一个显示。
而且把我之前那个占了100行的AI总结给去掉了，代码变得紧凑了！
考虑到战神系列装备太强，于是，我加高了它们的价格！
但是也加强了亿点这些装备！！！玩家要感谢我！！！
2026/04/08：重大更新，我把每一次的界面都要进行清屏，就像那些大型游戏一样。
并且增加了例如“正在前往商店”的提示
并且修复了某些Bug
2026/04/21：维护代码，修复了一些关于输出的bug
2026/05/04：维护代码，修复了一些关于输出的bug
2026/06/26：维护代码，修复了一些关于输出的bug
2026/06/27：维护代码
2026/07/21：修改代码风格
*/
/*
公告：
2025/11/10 游戏完整做完！ （不含后期优化与更新）
*/

// 正式代码

#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
bool gameover = 0;

// 玩家数据结构体
struct Playr {
    string name;     // 名字
    int xuel;        // 血量
    int zhandou;     // 战斗力
    int fangyv;      // 防御力
    int fashu;       // 法术值
    int manei;       // 马内数（钱数）
    int puyi = 0;    // 普通医疗包数量
    int gaoyi = 0;   // 高级医疗包数量
    int zhanyi = 0;  // 战神医疗包数量
    int busis = 0;   // 不死图腾数量
};

// 怪物结构体
struct Monster {
    string name;      // 怪物名字
    int xuel;         // 怪物血量
    int zhandou;      // 怪物攻击力
    int fangyv;       // 怪物防御力
    int jibai_manei;  // 击败后获得的钱
    int minLevel;     // 击败最小等级，用地区编号
    string miaoshu;   // 怪物描述
};

// 怪物数据 部分是某seek想的
Monster smallGhost = {
    "小幽灵", 40, 5, 2, 50, 1, "飘忽不定的幽灵，攻击力不强但很烦人"};
Monster kuileiMonster = {
    "傀儡怪", 50, 15, 15, 80, 1, "被魔法控制的傀儡，防御力不错"};
Monster firejingling = {"火焰精灵", 180, 50, 5, 120, 2, "魔法湖中的火元素生物"};
Monster wateryuansu = {
    "水元素", 230, 30, 100, 150, 2, "湖水的化身，防御力很强"};
Monster yanjv = {
    "熔岩巨人", 450, 200, 150, 250, 3, "火山中的岩石怪物，攻击力惊人"};
Monster firelong = {"小火龙", 500, 180, 200, 350, 3, "拥有龙族血统的强大生物"};
Monster huanyzs = {
    "幻影战士", 1300, 300, 50, 1000, 4, "幻神宫的守护者，实力非凡"};
Monster sshou = {
    "神兽", 1500, 400, 75, 1500, 4, "传说中的神兽，击败它将获得丰厚奖励"};

// 用于逐帧输出（慢）
void print(string a) {
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i];
        Sleep(40);
    }
}

void print2(string a) {
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i];
        Sleep(10);
    }
}

// 开始的logo函数
void start_print() {
    cout << "  ********       *********\n";
    Sleep(150);
    cout << " *        *              *\n";
    Sleep(150);
    cout << "*                        *\n";
    Sleep(150);
    cout << "*                        *\n";
    Sleep(150);
    cout << "*                        *\n";
    Sleep(150);
    cout << "*                        *\n";
    Sleep(150);
    cout << " *        *    *         *\n";
    Sleep(150);
    cout << "  ********      ********* \n";

    Sleep(2000);

    system("cls");

    print("CJ集团出品CJ集团出品CJ集团出品");
    Sleep(1000);

    system("cls");
    print("欢迎进入战神1！！！");
    Sleep(1000);
    system("cls");
    Sleep(250);
}

// 存档功能函数
void saveGame(Playr& w) {
    ofstream saveFile("zhanshen_save.txt");

    if (saveFile.is_open()) {
        saveFile << w.name << endl;
        saveFile << w.xuel << endl;
        saveFile << w.zhandou << endl;
        saveFile << w.fangyv << endl;
        saveFile << w.fashu << endl;
        saveFile << w.manei << endl;
        saveFile << w.puyi << endl;
        saveFile << w.gaoyi << endl;
        saveFile << w.zhanyi << endl;
        saveFile << w.busis << endl;
        saveFile.close();

        cout << "游戏已保存！下次可以继续冒险了！" << endl;
    }
    else {
        cout << "保存失败！无法创建存档文件。" << endl;
    }
    Sleep(1000);
    system("cls");
}

// 读档功能函数
bool loadGame(Playr& w) {
    ifstream saveFile("zhanshen_save.txt");
    if (saveFile.is_open()) {
        getline(saveFile, w.name);
        saveFile >> w.xuel;
        saveFile >> w.zhandou;
        saveFile >> w.fangyv;
        saveFile >> w.fashu;
        saveFile >> w.manei;
        saveFile >> w.puyi;
        saveFile >> w.gaoyi;
        saveFile >> w.zhanyi;
        saveFile >> w.busis;
        saveFile.close();
        cout << "游戏加载成功！欢迎回来，" << w.name << "！" << endl;
        Sleep(1000);
        system("cls");
        return true;
    }
    else {
        Sleep(1000);
        system("cls");
        cout << "没有找到存档文件，开始新游戏。" << endl;
        return false;
    }
}

// 商店函数
void shopMenu(Playr& w) {
    while (1) {
        cout << endl;
        print("良心商人：“您好亲。您要来点儿什么？”");
        cout << "1、铁剑 100元" << endl;
        cout << "2、金剑 150元" << endl;
        cout << "3、神木剑 300元" << endl;
        cout << "4、战神之剑 2000元" << endl;
        cout << "5、铁头盔 100元" << endl;
        cout << "6、铁盔甲 150元" << endl;
        cout << "7、钛合金头盔 300元" << endl;
        cout << "8、钛合金盔甲 350元" << endl;
        cout << "9、战神头盔 2250元" << endl;
        cout << "10、战神盔甲 2500元" << endl;
        cout << "11、超级法杖 500元" << endl;
        cout << "12、战神法杖 1700元" << endl;
        cout << "13、普通医疗包 100元" << endl;
        cout << "14、高级医疗包 400元" << endl;
        cout << "15、战神医疗包 1050元" << endl;
        cout << "16、不死图腾 500元" << endl;
        cout << "0、离开商店" << endl;

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {  // 铁剑
                if (w.manei - 100 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 100;
                    w.zhandou += 50;
                    cout << "购买成功！";
                }
                break;
            }
            case 2: {  // 金剑
                if (w.manei - 150 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 150;
                    w.zhandou += 75;
                    cout << "购买成功！";
                }
                break;
            }
            case 3: {  // 神木剑
                if (w.manei - 300 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 300;
                    w.zhandou += 150;
                    cout << "购买成功！";
                }
                break;
            }
            case 4: {  // 战神之剑
                if (w.manei - 2000 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 2000;
                    w.zhandou += 66666;
                    cout << "购买成功！";
                }
                break;
            }
            case 5: {  // 铁头盔
                if (w.manei - 100 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 100;
                    w.fangyv += 70;
                    cout << "购买成功！";
                }
                break;
            }
            case 6: {  // 铁盔甲
                if (w.manei - 150 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 150;
                    w.fangyv += 120;
                    cout << "购买成功！";
                }
                break;
            }
            case 7: {  // 钛合金头盔
                if (w.manei - 300 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 300;
                    w.fangyv += 275;
                    cout << "购买成功！";
                }
                break;
            }
            case 8: {  // 钛合金盔甲
                if (w.manei - 350 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 350;
                    w.fangyv += 310;
                    cout << "购买成功！";
                }
                break;
            }
            case 9: {  // 战神头盔
                if (w.manei - 2250 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 2250;
                    w.fangyv += 32200;
                    cout << "购买成功！";
                }
                break;
            }
            case 10: {  // 战神盔甲
                if (w.manei - 2500 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 2500;
                    w.fangyv += 55000;
                    cout << "购买成功！";
                }
                break;
            }
            case 11: {  // 超级法杖
                if (w.manei - 500 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 500;
                    w.fashu += 500;
                    cout << "购买成功！";
                }
                break;
            }
            case 12: {  // 战神法杖
                if (w.manei - 1700 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 1700;
                    w.fashu += 15000;
                    cout << "购买成功！";
                }
                break;
            }
            case 13: {  // 普通医疗包
                if (w.manei - 100 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 100;
                    w.puyi++;
                    cout << "购买成功！";
                }
                break;
            }
            case 14: {  // 高级医疗包
                if (w.manei - 400 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 400;
                    w.gaoyi++;
                    cout << "购买成功！";
                }
                break;
            }
            case 15: {  // 战神医疗包
                if (w.manei - 1050 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 1050;
                    w.zhanyi++;
                    cout << "购买成功！";
                }
                break;
            }
            case 16: {  // 不死图腾
                if (w.manei - 500 < 0) {
                    cout << "您的钱不够了";
                }
                else {
                    w.manei -= 500;
                    w.busis++;
                    cout << "购买成功";
                }
                break;
            }
            default:
                cout << "请选择有效情况！";
                continue;
        }
        Sleep(1000);
        system("cls");
    }
    Sleep(1000);
    system("cls");
}

// 回血函数
void healPlayer(Playr& w) {
    cout << endl << "您有" << w.puyi << "个普通医疗包" << endl;
    cout << w.gaoyi << "个高级医疗包" << endl;
    cout << w.zhanyi << "个战神医疗包" << endl;
    cout
        << "您要使用哪一个医疗包回血？普通医疗包：1 高级医疗包：2 战神医疗包：3"
        << endl;

    int choice;
    cin >> choice;

    if (choice == 1 && w.puyi > 0) {
        w.puyi--;
        w.xuel += 100;
        cout << "使用了普通医疗包，恢复100点血量！" << endl;
    }
    else if (choice == 2 && w.gaoyi > 0) {
        w.gaoyi--;
        w.xuel += 400;
        cout << "使用了高级医疗包，恢复400点血量！" << endl;
    }
    else if (choice == 3 && w.zhanyi > 0) {
        w.zhanyi--;
        w.xuel += 100000;
        cout << "使用了战神医疗包，恢复100000点血量！" << endl;
    }
    else {
        cout << "您选择错误或者您没有任何医疗包！请重新选择！" << endl;
        cout << "你重新按步骤进入回血界面" << endl << endl;
    }
    Sleep(1000);
    system("cls");
}

// 查看状态函数
void showStatus(Playr& w) {
    cout << endl;
    print("========== 个人状态 ==========");
    cout << endl;
    cout << "您的姓名：" << w.name << endl;
    cout << "您目前的血量：" << w.xuel << endl;
    cout << "您的战斗力：" << w.zhandou << endl;
    cout << "您的防御力：" << w.fangyv << endl;
    cout << "您的法术值：" << w.fashu << endl;
    cout << "您的马内数：" << w.manei << endl;
    cout << "医疗包数量：" << w.puyi << "普/" << w.gaoyi << "高/" << w.zhanyi
         << "战" << endl;
    cout << "不死图腾：" << w.busis << "个" << endl;
    cout << "==============================" << endl << endl;
    Sleep(5000);
    system("cls");
}

// 战斗函数
void battleMonster(Playr& w, Monster& m) {
    cout << "你遇到了" << m.name << endl;
    cout << m.miaoshu << endl;
    int mxuel = m.xuel;
    int zhan = w.zhandou;
    int fang = w.fangyv;
    int gailv = rand() % 4;  // 25%概率触发法术加成
    if (gailv == 1 && w.fashu != 0) {
        zhan += w.fashu * 5;
        cout << "通过法杖使攻击力增加" << w.fashu * 5 << endl;
    }
    while (mxuel > 0 && w.xuel > 0) {
        cout << endl << m.name << " 血量: " << mxuel << endl;
        cout << "你的血量: " << w.xuel << endl;
        cout << "你要干什么？" << endl;
        cout << "1、攻击" << endl;
        cout << "2、逃跑" << endl;
        cout << "请选择: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // 玩家攻击怪物
            int gong = zhan - fang;
            if (gong < 1) {
                gong = 1;
            }
            mxuel -= gong;
            cout << "你对" << m.name << "造成了" << gong << "点伤害！" << endl;

            if (mxuel <= 0) {
                cout << "你击败了" << m.name << "！" << endl;
                w.manei += m.jibai_manei;
                cout << "获得了" << m.jibai_manei << "金币！" << endl;
                break;
            }

            // 怪物攻击玩家
            int mgong = m.zhandou - fang;
            if (mgong < 1) {
                mgong = 1;
            }
            w.xuel -= mgong;
            cout << m.name << "对你造成了" << mgong << "点伤害！" << endl;

            // 战斗过程中检查玩家是否死亡
            if (w.xuel <= 0) {
                if (w.busis > 0) {
                    cout << "不死图腾生效！你复活了！" << endl;
                    w.xuel = 100;
                    w.busis--;
                    cout << "你现在的血量: " << w.xuel << endl;
                }
                else {
                    cout << "你被" << m.name
                         << "击败了！这时你退出探险世界就会死掉！" << endl;
                    break;
                }
            }
        }
        else if (choice == 2) {
            // 逃跑逻辑
            if (rand() % 2 == 0) {
                cout << "逃跑成功！" << endl;
                break;
            }
            else {
                cout << "逃跑失败！" << endl;
                // 怪物攻击玩家
                int mgong = m.zhandou - fang;
                if (mgong < 1) {
                    mgong = 1;
                }
                w.xuel -= mgong;
                cout << m.name << "对你造成了" << mgong << "点伤害！" << endl;

                // 逃跑失败后检查玩家是否死亡
                if (w.xuel <= 0) {
                    if (w.busis > 0) {
                        cout << "不死图腾生效！你复活了！" << endl;
                        w.xuel = 100;
                        w.busis--;
                        cout << "你现在的血量: " << w.xuel << endl;
                    }
                    else {
                        cout << "你被" << m.name << "击败了！" << endl;
                        break;
                    }
                }
            }
        }
        else {
            cout << "选择错误！" << endl;
        }
    }

    // 战斗结束后再次检查玩家是否死亡
    if (w.xuel <= 0 && w.busis == 0) {
        gameover = true;
    }
    Sleep(1000);
    system("cls");
}

// 探险世界函数
void adventureWorld(Playr& w) {
    while (1) {
        cout << endl;

        cout << endl;

        print2("欢迎您前来探险！！！\n\n");

        cout << "1、奇异森林" << endl;
        cout << "2、魔法湖" << endl;
        cout << "3、威特火山" << endl;
        cout << "4、幻神宫" << endl;
        cout << "0、退出" << endl;
        cout << "请注意，数字越大的地方越危险，当然收益越大" << endl;
        cout << "请选择（1、2、3、4、0）" << endl;

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                cout << "你进入了奇异森林..." << endl;
                int sui = rand() % 2;
                if (sui == 0) {
                    battleMonster(w, smallGhost);
                }
                else {
                    battleMonster(w, kuileiMonster);
                }
                // 战斗后可能有额外奖励
                if (rand() % 3 == 0 && w.xuel > 0) {
                    cout << "你在森林中发现了一个宝箱！" << endl;
                    w.manei += 50;
                    cout << "获得了50金币！" << endl;
                    Sleep(2000);
                    system("cls");
                }
                break;
            }
            case 2: {
                cout << "你来到了魔法湖..." << endl;
                int sui = rand() % 2;
                if (sui == 0) {
                    battleMonster(w, firejingling);
                }
                else {
                    battleMonster(w, wateryuansu);
                }
                // 战斗后可能有额外奖励
                if (rand() % 3 == 0 && w.xuel > 0) {
                    cout << "你在湖底发现了一个发光的宝箱！" << endl;
                    w.manei += 50;
                    cout << "获得了50金币！" << endl;
                    Sleep(2000);
                    system("cls");
                }
                break;
            }
            case 3: {
                cout << "你登上了威特火山..." << endl;
                int sui = rand() % 2;
                if (sui == 0) {
                    battleMonster(w, yanjv);
                }
                else {
                    battleMonster(w, firelong);
                }
                // 战斗后可能有额外奖励
                if (rand() % 3 == 0 && w.xuel > 0) {
                    cout << "你在火山岩洞中发现了一个宝箱！" << endl;
                    w.manei += 50;
                    cout << "获得了50金币！" << endl;
                    Sleep(2000);
                    system("cls");
                }
                break;
            }
            case 4: {
                cout << "你进入了幻神宫..." << endl;
                int sui = rand() % 2;
                if (sui == 0) {
                    battleMonster(w, huanyzs);
                }
                else {
                    battleMonster(w, sshou);
                }
                // 战斗后可能有额外奖励
                if (rand() % 3 == 0 && w.xuel > 0) {
                    cout << "你在宫殿的密室中发现了一个宝箱！" << endl;
                    w.manei += 50;
                    cout << "获得了50金币！" << endl;
                    Sleep(2000);
                    system("cls");
                }
                break;
            }
            default:
                cout << "选择错误！请重新选择！" << endl << endl;
                break;
        }
    }
    Sleep(1000);
    system("cls");
}

// 决斗地域函数
void battleArena(Playr& w) {
    cout << "你来到了决斗地域，准备挑战恶龙！" << endl;
    cout << "恶龙：\"渺小的人类，竟敢挑战我！公主是我的！\"" << endl;
    cout << "你：\"放开公主，让我来打败你！\"" << endl;

    // 创建恶龙BOSS
    Monster evilDragon = {
        "恶龙",
        1170000,
        25000,
        20000,
        10000,
        55,
        "抓走公主的邪恶巨龙，实力极其非常究极无敌强大，血量高达117w。"};

    battleMonster(w, evilDragon);

    if (w.xuel > 0) {
        cout << endl << "恭喜你！你打败了恶龙，拯救了公主！" << endl;
        cout << "王国为你举行了盛大的庆祝仪式！" << endl;
        cout << "游戏胜利！" << endl;
        gameover = 1;
    }
}

// 删除存档功能函数
void deleteSaveFile() {
    if (remove("zhanshen_save.txt") == 0) {
        cout << "存档已成功删除！" << endl;
    }
    else {
        cout << "没有找到存档文件，或删除失败。" << endl;
    }
    Sleep(1000);
    system("cls");
}

int main() {
    system("title 战神1");

    srand(time(0));
    Playr w;

    // 调用展示logo函数
    start_print();

    print(
        "恶龙抓走了王国的公主，你作为国王手下的英雄，你要去打败恶龙，拯救公主！"
        "！！");
    cout << endl;
    Sleep(500);

    print("是否加载存档？(1=是, 0=否，开始新游戏): ");
    // 游戏开始时询问是否加载存档

    int loadChoice;
    cin >> loadChoice;

    if (loadChoice == 1) {
        system("cls");
        if (!loadGame(w)) {
            // 如果加载失败，开始新游戏
            cout << "请输入您的姓名：" << endl;
            cin >> w.name;
            cout << endl;

            if (w.name == "超级勇士") {
                // 超级勇士Buff
                w.xuel = 2500;
                w.zhandou = 1500;
                w.fangyv = 500;
                w.fashu = 300;
                w.manei = 3000;
            }
            else {
                w.xuel = 300;
                w.zhandou = 75;
                w.fangyv = 30;
                w.fashu = 0;
                w.manei = 300;
            }
        }
    }
    else {
        system("cls");

        // 开始新游戏

        print("请输入您的姓名：");
        cin >> w.name;
        cout << endl;

        if (w.name == "超级勇士") {
            // 超级勇士Buff
            w.xuel = 2500;
            w.zhandou = 1500;
            w.fangyv = 500;
            w.fashu = 300;
            w.manei = 3000;
        }

        else {
            w.xuel = 300;
            w.zhandou = 75;
            w.fangyv = 30;
            w.fashu = 0;
            w.manei = 300;
        }
    }

    while (!gameover) {
        print2("请输入你要去干什么？");
        cout << endl;

        int choice;
        cout << "1、交易市场" << endl;
        cout << "2、探险世界" << endl;
        cout << "3、决斗地狱" << endl;
        cout << "4、查看个人数据" << endl;
        cout << "5、回血" << endl;
        cout << "6、保存游戏" << endl;
        cout << "7、删除存档" << endl;
        cout << "8、退出游戏" << endl;
        cout << "请选择（1、2、3、4、5、6、7、8）" << endl;

        cin >> choice;
        system("cls");

        if (choice == 1) {
            cout << "正在前往交易市场…\n";
            Sleep(1000);
            shopMenu(w);
        }

        else if (choice == 2) {
            cout << "正在前往探险世界…\n";
            Sleep(1000);
            adventureWorld(w);
        }

        else if (choice == 3) {
            cout << "正在前往决斗地狱…\n";
            Sleep(1000);
            battleArena(w);
        }

        else if (choice == 4) {
            system("cls");
            showStatus(w);
        }

        else if (choice == 5) {
            system("cls");
            healPlayer(w);
        }

        else if (choice == 6) {
            system("cls");
            saveGame(w);
        }

        else if (choice == 7) {
            system("cls");
            print(
                "确定要删除存档并退出吗？这将永久删除您的游戏进度！(1=确定, "
                "0=取消):");
            int deleteChoice;
            cin >> deleteChoice;
            if (deleteChoice == 1) {
                deleteSaveFile();
                return 0;
            }
            else {
                cout << "取消删除存档。" << endl;
            }
        }

        else if (choice == 8) {
            system("cls");
            // 退出前询问是否保存
            cout << "退出前是否保存游戏？(1=是, 0=否): ";
            int saveChoice;
            cin >> saveChoice;
            if (saveChoice == 1) {
                saveGame(w);
            }
            break;
        }
        else {
            system("cls");
            cout << "选择错误！请重新选择！";
            continue;
        }

        // 主循环死亡检查
        if (w.xuel <= 0) {
            if (w.busis > 0) {
                print("不死图腾生效！你复活了！");
                w.xuel = 100;
                w.busis--;
            }
            else {
                cout << "你死了！游戏结束！" << endl;
                gameover = true;
            }
        }
    }
    print("感谢游玩！");
    // 完美结束！！！
    return 0;
}  // 最后一个大括号
