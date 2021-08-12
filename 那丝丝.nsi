; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

; ��װ�����ʼ���峣��
!define PRODUCT_NAME "YLFCYcompiler"
!define PRODUCT_VERSION "0.4.0pre1::fix==1"
!define PRODUCT_WEB_SITE "http://ylfcycompiler.mysxl.cn"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\ccc.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

SetCompressor /SOLID lzma
SetCompressorDictSize 32

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ����ѡ�񴰿ڳ�������
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��ʼ�˵�����ҳ��
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "YLFCYcompiler"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!define MUI_FINISHPAGE_RUN "$INSTDIR\mingw-w64-install.exe"
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_LANGDLL
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\YLFCYcompiler"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BGGradient 0000FF 00FF00

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "111.ico"
  File "1111.cpp"
  File "1111.h"
  File "bu001_sys_0.2.15.yld.log.yre"
  File "bu002_sys_0.3.0.yld.log.yre"
  File "bu003_sys_0.3.3.yld.log.yre"
  File "ccc.exe"
  File "colorset.cpp"
  File "colorset.h"
  File "colorset.o"
  File "dll.dev"
  File "dll.dll"
  File "dll.h"
  File "DLL.layout"
  File "dllmain.cpp"
  File "dllmain.o"
  File "gmon.out"
  File "IDE.cpp"
  File "IDE.o"
  File "IDE_private.h"
  File "IDE_private.h.gch"
  File "IDE_private.o"
  File "IDE_private.rc"
  File "keydownprint.cpp"
  File "keydownprint.h"
  File "keydownprint.o"
  File "libdll.a"
  File "libDLL.def"
  File "Makefile.win"
  File "max(3).cpp"
  File "max(3).h"
  File "max(3).o"
  File "mingw-w64-install.exe"
  File "��������.html"
  File "����.txt"
  File "δ����1.cpp"
  File "δ����1.o"
  File "��˿˿.nsi"
  File "���̼��.cpp"
  File "���̼��.exe"
  File "��Ŀ1.dev"
  File "��Ŀ1.exe"
  File "��Ŀ1.exe.Manifest"
  File "��Ŀ1.ico"
  File "��Ŀ1.layout"
  File "��Ŀ1_private.h"
  File "��Ŀ1_private.rc"
  File "��Ŀ1_private.res"

; ������ʼ�˵���ݷ�ʽ
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\YLFCYcompiler.lnk" "$INSTDIR\��Ŀ1.exe"
  CreateShortCut "$DESKTOP\YLFCYcompiler.lnk" "$INSTDIR\��Ŀ1.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\ccc.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\ccc.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
 ******************************/

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\��Ŀ1_private.res"
  Delete "$INSTDIR\��Ŀ1_private.rc"
  Delete "$INSTDIR\��Ŀ1_private.h"
  Delete "$INSTDIR\��Ŀ1.layout"
  Delete "$INSTDIR\��Ŀ1.ico"
  Delete "$INSTDIR\��Ŀ1.exe.Manifest"
  Delete "$INSTDIR\��Ŀ1.exe"
  Delete "$INSTDIR\��Ŀ1.dev"
  Delete "$INSTDIR\���̼��.exe"
  Delete "$INSTDIR\���̼��.cpp"
  Delete "$INSTDIR\��˿˿.nsi"
  Delete "$INSTDIR\δ����1.o"
  Delete "$INSTDIR\δ����1.cpp"
  Delete "$INSTDIR\����.txt"
  Delete "$INSTDIR\��������.html"
  Delete "$INSTDIR\mingw-w64-install.exe"
  Delete "$INSTDIR\max(3).o"
  Delete "$INSTDIR\max(3).h"
  Delete "$INSTDIR\max(3).cpp"
  Delete "$INSTDIR\Makefile.win"
  Delete "$INSTDIR\libDLL.def"
  Delete "$INSTDIR\libdll.a"
  Delete "$INSTDIR\keydownprint.o"
  Delete "$INSTDIR\keydownprint.h"
  Delete "$INSTDIR\keydownprint.cpp"
  Delete "$INSTDIR\IDE_private.rc"
  Delete "$INSTDIR\IDE_private.o"
  Delete "$INSTDIR\IDE_private.h.gch"
  Delete "$INSTDIR\IDE_private.h"
  Delete "$INSTDIR\IDE.o"
  Delete "$INSTDIR\IDE.cpp"
  Delete "$INSTDIR\gmon.out"
  Delete "$INSTDIR\dllmain.o"
  Delete "$INSTDIR\dllmain.cpp"
  Delete "$INSTDIR\DLL.layout"
  Delete "$INSTDIR\dll.h"
  Delete "$INSTDIR\dll.dll"
  Delete "$INSTDIR\dll.dev"
  Delete "$INSTDIR\colorset.o"
  Delete "$INSTDIR\colorset.h"
  Delete "$INSTDIR\colorset.cpp"
  Delete "$INSTDIR\ccc.exe"
  Delete "$INSTDIR\bu003_sys_0.3.3.yld.log.yre"
  Delete "$INSTDIR\bu002_sys_0.3.0.yld.log.yre"
  Delete "$INSTDIR\bu001_sys_0.2.15.yld.log.yre"
  Delete "$INSTDIR\1111.h"
  Delete "$INSTDIR\1111.cpp"
  Delete "$INSTDIR\111.ico"

  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Website.lnk"
  Delete "$DESKTOP\YLFCYcompiler.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\YLFCYcompiler.lnk"

  RMDir "$SMPROGRAMS\$ICONS_GROUP"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd
