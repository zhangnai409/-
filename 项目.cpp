#include "speechMagager.h"
#include "speaker.h"
#include <ctime>

int main() {
  // 随机数种子
  std::srand(time(0));
  // 创建管理类对象
  SpeechManager sm;
  int choice = 0; // 用户选项

//  for (std::map<int,Speaker>::iterator it = sm.speakers.begin();it != sm.speakers.end(); it++) {
//    std::cout << "选手编号：" << it->first<< " 姓名："<< it->second.name << " 分数：" << it->second.score[0] << std::endl;
//  }

  while (true) {
    sm.showMenu();

    std::cout << "请输入您的选择：" << std::endl;
    std::cin >> choice;

    switch (choice) {
      case 1: // 开始比赛
        sm.startSpeech();
        break;
      case 2: // 查看往届比赛记录
        sm.showRecord();
        break;
      case 3: // 清空比赛记录
        sm.clearRecord();
        break;
      case 0: // 退出系统
        sm.exitSystem();
        break;
      default:break;
    }
  }
  return 0;
}
