#include <windows.h>
#include <tp_stub.h>
#include <ncbind.hpp>
#include <htmlhelp.h>
#include <string>


// ttstr��UTF8������֕ϊ�
std::string convertTtstrToUtf8String(ttstr &buf)
{
  int maxlen = buf.length() * 6 + 1;
  char *dat = new char[maxlen];
  int len = TVPWideCharToUtf8String(buf.c_str(), dat);
  std::string result(dat, len);
  delete[] dat;
  return result;
}


// �N�b�L�[
DWORD_PTR sCookie = 0;

// HTML�w���v��������
void RegisterFunc(void)
{
  HtmlHelp(NULL, NULL, HH_INITIALIZE, (DWORD_PTR)&sCookie);
}

NCB_PRE_REGIST_CALLBACK(RegisterFunc);

// HTML�w���v���I��
void UnregisterFunc(void)
{
  HtmlHelp(NULL, NULL, HH_UNINITIALIZE, (DWORD_PTR)sCookie);
}

NCB_POST_UNREGIST_CALLBACK(UnregisterFunc);

// �N���X�ɓo�^
class HtmlHelpClass
{
public:
  // �g�s�b�N��\������
  static void displayTopic(ttstr path) {
    HtmlHelp(NULL,
	     path.c_str(),
	     HH_DISPLAY_TOPIC,
	     0);
  }
};

NCB_REGISTER_CLASS_DIFFER(HtmlHelp, HtmlHelpClass)
{
  NCB_METHOD(displayTopic);
};
