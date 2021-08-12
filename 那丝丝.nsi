; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "YLFCYcompiler"
!define PRODUCT_VERSION "0.4.0pre1::fix==1"
!define PRODUCT_WEB_SITE "http://ylfcycompiler.mysxl.cn"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\ccc.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

SetCompressor /SOLID lzma
SetCompressorDictSize 32

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; 语言选择窗口常量设置
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 开始菜单设置页面
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "YLFCYcompiler"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!define MUI_FINISHPAGE_RUN "$INSTDIR\mingw-w64-install.exe"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "TradChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_LANGDLL
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

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
  File "升级…….html"
  File "帮助.txt"
  File "未命名1.cpp"
  File "未命名1.o"
  File "那丝丝.nsi"
  File "键盘监测.cpp"
  File "键盘监测.exe"
  File "项目1.dev"
  File "项目1.exe"
  File "项目1.exe.Manifest"
  File "项目1.ico"
  File "项目1.layout"
  File "项目1_private.h"
  File "项目1_private.rc"
  File "项目1_private.res"

; 创建开始菜单快捷方式
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\YLFCYcompiler.lnk" "$INSTDIR\项目1.exe"
  CreateShortCut "$DESKTOP\YLFCYcompiler.lnk" "$INSTDIR\项目1.exe"
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

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\项目1_private.res"
  Delete "$INSTDIR\项目1_private.rc"
  Delete "$INSTDIR\项目1_private.h"
  Delete "$INSTDIR\项目1.layout"
  Delete "$INSTDIR\项目1.ico"
  Delete "$INSTDIR\项目1.exe.Manifest"
  Delete "$INSTDIR\项目1.exe"
  Delete "$INSTDIR\项目1.dev"
  Delete "$INSTDIR\键盘监测.exe"
  Delete "$INSTDIR\键盘监测.cpp"
  Delete "$INSTDIR\那丝丝.nsi"
  Delete "$INSTDIR\未命名1.o"
  Delete "$INSTDIR\未命名1.cpp"
  Delete "$INSTDIR\帮助.txt"
  Delete "$INSTDIR\升级…….html"
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

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd
