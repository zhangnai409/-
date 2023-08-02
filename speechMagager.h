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

// �ݽ�����������
class SpeechManager {
 public:
  // �����һ�ֱ���ѡ�ֱ������
  std::vector<int> v1;
  // ��һ�ֽ���ѡ�ֱ������
  std::vector<int> v2;
  // ʤ��ǰ����ѡ������
  std::vector<int> victory;
  // ��ű���Լ���Ӧѡ������
  std::map<int, Speaker> speakers;
  // ��ű�������
  int index;
  // �ж��ļ��Ƿ�Ϊ��
  bool fileIsEmpty;
  // ��������¼������
  std::map<int, std::vector<std::string>> record;

  SpeechManager();
  // ��ʼ��
  void initSpeech();
  // ����ѡ��
  void createSpeaker();
  // ��ʼ����
  void startSpeech();
  // ��ǩ
  void speechDraw();
  // ����
  void speechContest();
  // ��ʾ�÷�
  void showScore();
  // �����¼
  void saveRecord();
  // ��ȡ��¼����
  void loadRecord();
  // ��ʾ�����¼
  void showRecord();
  // ��ռ�¼
  void clearRecord();
  // չʾ�˵�
  void showMenu();
  // �˳�ϵͳ
  void exitSystem();
  ~SpeechManager();
};

SpeechManager::SpeechManager() {
  // ��ʼ������������
  this->initSpeech();

  // ����12��ѡ��
  this->createSpeaker();

  // ��ȡ�����¼
  this->loadRecord();
}

SpeechManager::~SpeechManager() {}

// չʾ�˵�
void SpeechManager::showMenu() {
  std::cout << "************************************" << std::endl;
  std::cout << "************ ��ӭ�μ��ݽ����� *********" << std::endl;
  std::cout << "************ 1.��ʼ�ݽ�����  *********" << std::endl;
  std::cout << "************ 2.�鿴�����¼  *********" << std::endl;
  std::cout << "************ 3.��ձ�����¼  *********" << std::endl;
  std::cout << "************ 0.�˳���������  *********" << std::endl;
  std::cout << "************************************" << std::endl;
  std::cout << std::endl;
}

// �˳�ϵͳ
void SpeechManager::exitSystem() {
  std::cout << "��ӭ�´�ʹ��" << std::endl;
  std::system("pause");
  std::exit(0);
}

// ��ʼ��
void SpeechManager::initSpeech() {
  // �����ÿ�
  this->v1.clear();
  this->v2.clear();
  this->victory.clear();
  this->speakers.clear();
  this->record.clear();

  // ��ʼ����������
  this->index = 1;
}

// ����ѡ��
void SpeechManager::createSpeaker() {
  std::string nameeed = "ABCDEFGHIJKL";
  for (int i = 0; i < nameeed.size(); ++i) {
    std::string name = "ѡ��";
    name += nameeed[i];

    // ��������ѡ��
    Speaker sp;
    sp.name = name;
    for (int j = 0; j < 2; ++j) {
      sp.score[j] = 0;
    }

    // ����ѡ�ֱ�ţ����ŵ�v1������
    this->v1.push_back(i + 10001);

    // ѡ�ֱ���Լ���Ӧѡ�ַ��뵽map������
    this->speakers.insert(std::make_pair(i + 10001, sp));
  }
}

// ��ʼ����
void SpeechManager::startSpeech() {
  // ��һ��

  // 1. ��ǩ
  this->speechDraw();
  // 2. ����
  this->speechContest();
  // 3. ��ʾ�������
  this->showScore();

  // �ڶ���
  this->index++;
  // 1. ��ǩ
  this->speechDraw();
  // 2. ����
  this->speechContest();
  // 3. ��ʾ���ս��
  this->showScore();
  // 4. ����������ļ���
  this->saveRecord();

  // ���ñ���,��ȡ��¼
  // ��ʼ������������
  this->initSpeech();

  // ����12��ѡ��
  this->createSpeaker();

  // ��ȡ�����¼
  this->loadRecord();

  std::cout << "�����������" << std::endl;
  std::system("pause");
}

// ��ǩ
void SpeechManager::speechDraw() {
  std::cout << "�� << " << this->index << " >> �ֱ���ѡ�����ڳ�ǩ" << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << "��ǩ���ݽ�˳�����£� " << std::endl;

  if (this->index == 1) {
    // ��һ��
    std::random_shuffle(v1.begin(), v1.end());
    for (auto it : v1) {
      std::cout << it << " ";
    }
  } else {
    // �ڶ���
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

// ����
void SpeechManager::speechContest() {
  std::cout << "-----------��" << this->index << "�ֱ�����ʽ��ʼ---------------\n" << std::endl;

  // ׼����ʱ���������С��ɼ�
  std::multimap<double, int, std::greater<double>> groupScore;
  // ͳ����Ա��Ŀ 6��һ��
  int num = 0;
  // ����ѡ������
  std::vector<int> sp;

  if (this->index == 1) {
    sp = v1;
  } else {
    sp = v2;
  }

  // ��������ѡ�ֽ��б���
  for (auto i : sp) {
    num++;

    // ��ί���
    std::deque<double> d;
    for (int j = 0; j < 10; ++j) {
      double score = (rand() % 401 + 600) / 10.f; // 600 ~ 1000
//      std::cout << score << " ";
      d.push_back(score);
    }

    std::sort(d.begin(), d.end(), std::greater<double>()); // ����
    d.pop_front(); // ȥ����߷�
    d.pop_back(); // ȥ����ͷ�

    double sum = std::accumulate(d.begin(), d.end(), 0.0f); // �ܷ�
    double avg = sum / (double) d.size(); // ƽ����

    // ��ӡƽ����
//    std::cout << "��ţ�" << i << " ������" << this->speakers[i].name << " ���ƽ���֣�" << avg << std::endl;

    // ��ƽ���ַ���map������
    this->speakers[i].score[this->index - 1] = avg;

    // ��������ݴ�����ʱС������
    // key �ǵ÷� value�Ǿ���ѡ�ֱ��
    groupScore.insert(std::make_pair(avg, i));

    // ÿ 6 ��ȥ��ǰ����
    if (num % 6 == 0) {
      std::cout << "��" << num / 6 << "С���������" << std::endl;
      for (auto it : groupScore) {
        std::cout << "��ţ�" << it.second << " ������" << this->speakers[it.second].name
                  << " ������" << this->speakers[it.second].score[this->index - 1] << std::endl;
      }
      std::cout << std::endl;

      // ȡ��ǰ����
      int count = 0;
      for (auto it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
        if (this->index == 1) {
          v2.push_back((*it).second);
        } else {
          this->victory.push_back((*it).second);
        }
      }
      // С���������
      groupScore.clear();
    }
  }
  std::cout << "-----------��" << this->index << "�ֱ�������---------------\n" << std::endl;
  std::system("pause");

}

// ��ʾ�÷�
void SpeechManager::showScore() {
  std::cout << "-----------��" << this->index << "�ֽ���ѡ����Ϣ���£�---------------\n" << std::endl;

  std::vector<int> v;
  if (this->index == 1) {
    v = v2;
  } else {
    v = victory;
  }

  for (auto it : v) {
    std::cout << "ѡ�ֱ�ţ�" << it << " ������" << this->speakers[it].name
              << " �÷֣�" << this->speakers[it].score[this->index - 1] << std::endl;
  }
  std::cout << std::endl;
  std::system("pause");
}

// �����¼
void SpeechManager::saveRecord() {
  std::ofstream ofs;
  // ׷�ӷ�ʽд�ļ�
  ofs.open("speech.csv", std::ios::out | std::ios::app);
  // ��ÿ��ѡ�����ݣ�д���ļ�
  for (auto it : victory) {
    ofs << it << "," << this->speakers[it].score[1] << ",";
  }
  ofs << std::endl;

  // �ر�
  ofs.close();
  std::cout << "��¼�ѱ���" << std::endl;
  // �ļ���Ϊ��
  this->fileIsEmpty = false;
}

// ��ȡ��¼����
void SpeechManager::loadRecord() {
  // ���ļ�
  std::ifstream ifs("speech.csv", std::ios::in);

  if (!ifs.is_open()) {
    this->fileIsEmpty = true;
    std::cout << "���ļ�������" << std::endl;
    ifs.close();
    return;
  }

  // �ļ�������
  char ch;
  ifs >> ch;
  if (ifs.eof()) {
    std::cout << "�ļ�Ϊ��" << std::endl;
    this->fileIsEmpty = true;
    ifs.close();
    return;
  }

  // �ļ���Ϊ��
  this->fileIsEmpty = false;

  ifs.putback(ch); // �������ȡ�ĵ����ַ��Ż���
  std::string data;
  int index = 0; // �ڼ���

  while (ifs >> data) {
//    std::cout << data << std::endl;
    // 10002,86.675,10009,81.3,10007,78.55,

    // ��ż�¼����
    std::vector<std::string> v;

    int pos = -1; // �鵽 ��,�� λ�õı���
    int start = 0;

    while (true) {
      pos = data.find(",", start);
      if (pos == -1) {
        // û���ҵ�
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
//    std::cout << i.first << " �ھ���ţ�" << i.second[0] << " ������" << i.second[1] << std::endl;
//  }
}

// ��ʾ�����¼
void SpeechManager::showRecord() {
  if (this->fileIsEmpty) {
    std::cout << "�ļ�Ϊ�ջ����ļ�������" << std::endl;
  } else {
    for (int i = 0; i < this->record.size(); ++i) {
      std::cout << "��" << i + 1 << "��" << std::endl;
      std::cout << "�ھ���ţ�" << this->record[i][0] << " �÷֣�" << this->record[i][1] << std::endl;
      std::cout << "�Ǿ���ţ�" << this->record[i][2] << " �÷֣�" << this->record[i][3] << std::endl;
      std::cout << "������ţ�" << this->record[i][4] << " �÷֣�" << this->record[i][5] << std::endl;
      std::cout << std::endl;
    }
  }
  std::system("pause");
}

// ��ռ�¼
void SpeechManager::clearRecord() {
  std::cout << "�Ƿ�ȷ������ļ���" << std::endl;
  std::cout << "1. ��" << std::endl;
  std::cout << "2. ��" << std::endl;

  int select;
  std::cin >> select;

  if (select == 1) {
    std::ofstream ofs("speech.csv", std::ios::trunc);
    ofs.close();

    // ��ʼ������������
    this->initSpeech();

    // ����12��ѡ��
    this->createSpeaker();

    // ��ȡ�����¼
    this->loadRecord();
    std::cout << "��ճɹ�" << std::endl;
  }

  std::system("pause");
}