#include "speechMagager.h"
#include "speaker.h"
#include <ctime>

int main() {
  // ���������
  std::srand(time(0));
  // �������������
  SpeechManager sm;
  int choice = 0; // �û�ѡ��

//  for (std::map<int,Speaker>::iterator it = sm.speakers.begin();it != sm.speakers.end(); it++) {
//    std::cout << "ѡ�ֱ�ţ�" << it->first<< " ������"<< it->second.name << " ������" << it->second.score[0] << std::endl;
//  }

  while (true) {
    sm.showMenu();

    std::cout << "����������ѡ��" << std::endl;
    std::cin >> choice;

    switch (choice) {
      case 1: // ��ʼ����
        sm.startSpeech();
        break;
      case 2: // �鿴���������¼
        sm.showRecord();
        break;
      case 3: // ��ձ�����¼
        sm.clearRecord();
        break;
      case 0: // �˳�ϵͳ
        sm.exitSystem();
        break;
      default:break;
    }
  }
  return 0;
}
