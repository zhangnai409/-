#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include "speaker.h"

// 演讲比赛管理类
class SpeechManager {
 public:
  // 保存第一轮比赛选手编号容器
  std::vector<int> v1;
  // 第一轮晋级选手编号容器
  std::vector<int> v2;
  // 胜出前三名选手容器
  std::vector<int> victory;
  // 存放编号以及对应选手容器
  std::map<int, Speaker> speakers;
  // 存放比赛轮数
  int index;
  // 判断文件是否为空
  bool fileIsEmpty;
  // 存放往届记录的容器
  std::map<int, std::vector<std::string>> record;

  SpeechManager();
  // 初始化
  void initSpeech();
  // 创建选手
  void createSpeaker();
  // 开始比赛
  void startSpeech();
  // 抽签
  void speechDraw();
  // 比赛
  void speechContest();
  // 显示得分
  void showScore();
  // 保存记录
  void saveRecord();
  // 读取记录分数
  void loadRecord();
  // 显示往届记录
  void showRecord();
  // 清空记录
  void clearRecord();
  // 展示菜单
  void showMenu();
  // 退出系统
  void exitSystem();
  ~SpeechManager();
};

SpeechManager::SpeechManager() {
  // 初始化容器和属性
  this->initSpeech();

  // 创建12名选手
  this->createSpeaker();

  // 获取往届记录
  this->loadRecord();
}

SpeechManager::~SpeechManager() {}

// 展示菜单
void SpeechManager::showMenu() {
  std::cout << "************************************" << std::endl;
  std::cout << "************ 欢迎参加演讲比赛 *********" << std::endl;
  std::cout << "************ 1.开始演讲比赛  *********" << std::endl;
  std::cout << "************ 2.查看往届记录  *********" << std::endl;
  std::cout << "************ 3.清空比赛记录  *********" << std::endl;
  std::cout << "************ 0.退出比赛程序  *********" << std::endl;
  std::cout << "************************************" << std::endl;
  std::cout << std::endl;
}

// 退出系统
void SpeechManager::exitSystem() {
  std::cout << "欢迎下次使用" << std::endl;
  std::system("pause");
  std::exit(0);
}

// 初始化
void SpeechManager::initSpeech() {
  // 容器置空
  this->v1.clear();
  this->v2.clear();
  this->victory.clear();
  this->speakers.clear();
  this->record.clear();

  // 初始化比赛轮数
  this->index = 1;
}

// 创建选手
void SpeechManager::createSpeaker() {
  std::string nameeed = "ABCDEFGHIJKL";
  for (int i = 0; i < nameeed.size(); ++i) {
    std::string name = "选手";
    name += nameeed[i];

    // 创建具体选手
    Speaker sp;
    sp.name = name;
    for (int j = 0; j < 2; ++j) {
      sp.score[j] = 0;
    }

    // 创建选手编号，并放到v1容器中
    this->v1.push_back(i + 10001);

    // 选手编号以及对应选手放入到map容器中
    this->speakers.insert(std::make_pair(i + 10001, sp));
  }
}

// 开始比赛
void SpeechManager::startSpeech() {
  // 第一轮

  // 1. 抽签
  this->speechDraw();
  // 2. 比赛
  this->speechContest();
  // 3. 显示晋级结果
  this->showScore();

  // 第二轮
  this->index++;
  // 1. 抽签
  this->speechDraw();
  // 2. 比赛
  this->speechContest();
  // 3. 显示最终结果
  this->showScore();
  // 4. 保存分数到文件中
  this->saveRecord();

  // 重置比赛,获取记录
  // 初始化容器和属性
  this->initSpeech();

  // 创建12名选手
  this->createSpeaker();

  // 获取往届记录
  this->loadRecord();

  std::cout << "本届比赛结束" << std::endl;
  std::system("pause");
}

// 抽签
void SpeechManager::speechDraw() {
  std::cout << "第 << " << this->index << " >> 轮比赛选手正在抽签" << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << "抽签后演讲顺序如下： " << std::endl;

  if (this->index == 1) {
    // 第一轮
    std::random_shuffle(v1.begin(), v1.end());
    for (auto it : v1) {
      std::cout << it << " ";
    }
  } else {
    // 第二轮
    std::random_shuffle(v2.begin(), v2.end());
    for (auto it : v2) {
      std::cout << it << " ";
    }
  }
  std::cout << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::system("pause");
  std::cout << std::endl;
}

// 比赛
void SpeechManager::speechContest() {
  std::cout << "-----------第" << this->index << "轮比赛正式开始---------------\n" << std::endl;

  // 准备临时容器，存放小组成绩
  std::multimap<double, int, std::greater<double>> groupScore;
  // 统计人员数目 6人一组
  int num = 0;
  // 比赛选手容器
  std::vector<int> sp;

  if (this->index == 1) {
    sp = v1;
  } else {
    sp = v2;
  }

  // 遍历所有选手进行比赛
  for (auto i : sp) {
    num++;

    // 评委打分
    std::deque<double> d;
    for (int j = 0; j < 10; ++j) {
      double score = (rand() % 401 + 600) / 10.f; // 600 ~ 1000
//      std::cout << score << " ";
      d.push_back(score);
    }

    std::sort(d.begin(), d.end(), std::greater<double>()); // 排序
    d.pop_front(); // 去除最高分
    d.pop_back(); // 去除最低分

    double sum = std::accumulate(d.begin(), d.end(), 0.0f); // 总分
    double avg = sum / (double) d.size(); // 平均分

    // 打印平均分
//    std::cout << "编号：" << i << " 姓名：" << this->speakers[i].name << " 获得平均分：" << avg << std::endl;

    // 将平均分放入map容器中
    this->speakers[i].score[this->index - 1] = avg;

    // 将打分数据存入临时小组容器
    // key 是得分 value是具体选手编号
    groupScore.insert(std::make_pair(avg, i));

    // 每 6 人去出前三名
    if (num % 6 == 0) {
      std::cout << "第" << num / 6 << "小组比赛名次" << std::endl;
      for (auto it : groupScore) {
        std::cout << "编号：" << it.second << " 姓名：" << this->speakers[it.second].name
                  << " 分数：" << this->speakers[it.second].score[this->index - 1] << std::endl;
      }
      std::cout << std::endl;

      // 取走前三名
      int count = 0;
      for (auto it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
        if (this->index == 1) {
          v2.push_back((*it).second);
        } else {
          this->victory.push_back((*it).second);
        }
      }
      // 小组容器清空
      groupScore.clear();
    }
  }
  std::cout << "-----------第" << this->index << "轮比赛结束---------------\n" << std::endl;
  std::system("pause");

}

// 显示得分
void SpeechManager::showScore() {
  std::cout << "-----------第" << this->index << "轮晋级选手信息如下：---------------\n" << std::endl;

  std::vector<int> v;
  if (this->index == 1) {
    v = v2;
  } else {
    v = victory;
  }

  for (auto it : v) {
    std::cout << "选手编号：" << it << " 姓名：" << this->speakers[it].name
              << " 得分：" << this->speakers[it].score[this->index - 1] << std::endl;
  }
  std::cout << std::endl;
  std::system("pause");
}

// 保存记录
void SpeechManager::saveRecord() {
  std::ofstream ofs;
  // 追加方式写文件
  ofs.open("speech.csv", std::ios::out | std::ios::app);
  // 将每个选手数据，写入文件
  for (auto it : victory) {
    ofs << it << "," << this->speakers[it].score[1] << ",";
  }
  ofs << std::endl;

  // 关闭
  ofs.close();
  std::cout << "记录已保存" << std::endl;
  // 文件不为空
  this->fileIsEmpty = false;
}

// 读取记录分数
void SpeechManager::loadRecord() {
  // 读文件
  std::ifstream ifs("speech.csv", std::ios::in);

  if (!ifs.is_open()) {
    this->fileIsEmpty = true;
    std::cout << "该文件不存在" << std::endl;
    ifs.close();
    return;
  }

  // 文件清空情况
  char ch;
  ifs >> ch;
  if (ifs.eof()) {
    std::cout << "文件为空" << std::endl;
    this->fileIsEmpty = true;
    ifs.close();
    return;
  }

  // 文件不为空
  this->fileIsEmpty = false;

  ifs.putback(ch); // 将上面读取的单个字符放回来
  std::string data;
  int index = 0; // 第几届

  while (ifs >> data) {
//    std::cout << data << std::endl;
    // 10002,86.675,10009,81.3,10007,78.55,

    // 存放记录数据
    std::vector<std::string> v;

    int pos = -1; // 查到 “,” 位置的变量
    int start = 0;

    while (true) {
      pos = data.find(",", start);
      if (pos == -1) {
        // 没有找到
        break;
      }
      std::string temp = data.substr(start, pos - start);
//      std::cout << temp << std::endl;
      v.push_back(temp);
      start = pos + 1;
    }

    this->record.insert(std::make_pair(index, v));
    index++;
  }

  ifs.close();
//  for (auto i : record) {
//    std::cout << i.first << " 冠军编号：" << i.second[0] << " 分数：" << i.second[1] << std::endl;
//  }
}

// 显示往届记录
void SpeechManager::showRecord() {
  if (this->fileIsEmpty) {
    std::cout << "文件为空或者文件不存在" << std::endl;
  } else {
    for (int i = 0; i < this->record.size(); ++i) {
      std::cout << "第" << i + 1 << "届" << std::endl;
      std::cout << "冠军编号：" << this->record[i][0] << " 得分：" << this->record[i][1] << std::endl;
      std::cout << "亚军编号：" << this->record[i][2] << " 得分：" << this->record[i][3] << std::endl;
      std::cout << "季军编号：" << this->record[i][4] << " 得分：" << this->record[i][5] << std::endl;
      std::cout << std::endl;
    }
  }
  std::system("pause");
}

// 清空记录
void SpeechManager::clearRecord() {
  std::cout << "是否确认清空文件？" << std::endl;
  std::cout << "1. 是" << std::endl;
  std::cout << "2. 否" << std::endl;

  int select;
  std::cin >> select;

  if (select == 1) {
    std::ofstream ofs("speech.csv", std::ios::trunc);
    ofs.close();

    // 初始化容器和属性
    this->initSpeech();

    // 创建12名选手
    this->createSpeaker();

    // 获取往届记录
    this->loadRecord();
    std::cout << "清空成功" << std::endl;
  }

  std::system("pause");
}