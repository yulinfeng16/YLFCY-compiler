#include <windows.h>
#include <commctrl.h>

#include "ylfcyedi.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT Message, WPARAM wParam,LPARAM lParam);

char g_szAppName[] = "MyMDIWindow";
char g_szChild[] = "MyMDIChild";
HINSTANCE g_hInst;
HWND g_hMDIClient, g_hStatusBar, g_hToolBar;
HWND g_hMainWindow;

BOOL LoadFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, NULL);
		if(dwFileSize != 0xFFFFFFFF) {
			LPSTR pszFileText;
			pszFileText = LPSTR(GlobalAlloc(GPTR, dwFileSize + 1));
			if(pszFileText != NULL) {
				DWORD dwRead;
				if(ReadFile(hFile, pszFileText, dwFileSize, &dwRead, NULL)) {
					pszFileText[dwFileSize] = 0; // Null terminator
					if(SetWindowText(hEdit, pszFileText))
						bSuccess = TRUE; // It worked!
				}
				GlobalFree(pszFileText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

BOOL SaveFile(HWND hEdit, LPSTR pszFileName) {
	HANDLE hFile;
	BOOL bSuccess = FALSE;

	hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile != INVALID_HANDLE_VALUE) {
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(hEdit);
		if(dwTextLength > 0) {// No need to bother if there's no text.
			LPSTR pszText;
			pszText = LPSTR(GlobalAlloc(GPTR, dwTextLength + 1));
			if(pszText != NULL) {
				if(GetWindowText(hEdit, pszText, dwTextLength + 1)) {
					DWORD dwWritten;
					if(WriteFile(hFile, pszText, dwTextLength, &dwWritten, NULL))
						bSuccess = TRUE;
				}
				GlobalFree(pszText);
			}
		}
		CloseHandle(hFile);
	}
	return bSuccess;
}

BOOL GetFileName(HWND hwnd, LPSTR pszFileName, BOOL bSave) {
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	pszFileName[0] = 0;

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "Text Files (*.cpi)\0*.cpi\0All Files (*.*)\0*.*\0\0";
	ofn.lpstrFile = pszFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrDefExt = "cpi";

	if(bSave) {
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;
		if(!GetSaveFileName(&ofn))
			return FALSE;
	} else {
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		if(!GetOpenFileName(&ofn))
			return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpszCmdParam, int nCmdShow) {
	MSG  Msg;
	WNDCLASSEX WndClassEx;

	g_hInst = hInstance;

	WndClassEx.cbSize          = sizeof(WNDCLASSEX);
	WndClassEx.style           = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc     = WndProc;
	WndClassEx.cbClsExtra      = 0;
	WndClassEx.cbWndExtra      = 0;
	WndClassEx.hInstance       = hInstance;
	WndClassEx.hIcon           = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor         = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hbrBackground   = (HBRUSH)(COLOR_3DSHADOW+1);
	WndClassEx.lpszMenuName    = "MAIN";
	WndClassEx.lpszClassName   = g_szAppName;
	WndClassEx.hIconSm         = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&WndClassEx)) {
		MessageBox(0, "Could Not Register Window", "Oops...",MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	WndClassEx.lpfnWndProc     = MDIChildWndProc;
	WndClassEx.lpszMenuName    = NULL;
	WndClassEx.lpszClassName   = g_szChild;
	WndClassEx.hbrBackground   = (HBRUSH)(COLOR_3DFACE+1);

	if(!RegisterClassEx(&WndClassEx)) {
		MessageBox(0, "Could Not Register Child Window", "Oops...",
		MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	g_hMainWindow = CreateWindowEx(WS_EX_APPWINDOW,g_szAppName,"MDI File Editor",WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0, 0, hInstance, NULL);

	if (g_hMainWindow == NULL){
		MessageBox(0, "No Window", "Oops...", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	ShowWindow(g_hMainWindow, nCmdShow);
	UpdateWindow(g_hMainWindow);

	while(GetMessage(&Msg, NULL, 0, 0)) {
		if (!TranslateMDISysAccel(g_hMDIClient, &Msg)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE: {
			CLIENTCREATESTRUCT ccs;
			int iStatusWidths[] = {200, 300, -1};
			TBADDBITMAP tbab;
			TBBUTTON tbb[9];

			// Find window menu where children will be listed
			ccs.hWindowMenu  = GetSubMenu(GetMenu(hwnd), 2);
			ccs.idFirstChild = ID_MDI_FIRSTCHILD;
			g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd, (HMENU)ID_MDI_CLIENT, g_hInst, (LPVOID)&ccs);
			ShowWindow(g_hMDIClient, SW_SHOW);

			g_hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
			hwnd, (HMENU)ID_STATUSBAR, g_hInst, NULL);
			SendMessage(g_hStatusBar, SB_SETPARTS, 3, (LPARAM)iStatusWidths);
			SendMessage(g_hStatusBar, SB_SETTEXT, 2, (LPARAM)"Toolbar & Statusbar Example");

			g_hToolBar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
			hwnd, (HMENU)ID_TOOLBAR, g_hInst, NULL);

			// Send the TB_BUTTONSTRUCTSIZE message, which is required for
			// backward compatibility.
			SendMessage(g_hToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage(g_hToolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);

			ZeroMemory(tbb, sizeof(tbb));

			tbb[0].iBitmap = STD_FILENEW;
			tbb[0].fsState = TBSTATE_ENABLED;
			tbb[0].fsStyle = TBSTYLE_BUTTON;
			tbb[0].idCommand = CM_FILE_NEW;

			tbb[1].iBitmap = STD_FILEOPEN;
			tbb[1].fsState = TBSTATE_ENABLED;
			tbb[1].fsStyle = TBSTYLE_BUTTON;
			tbb[1].idCommand = CM_FILE_OPEN;

			tbb[2].iBitmap = STD_FILESAVE;
			tbb[2].fsStyle = TBSTYLE_BUTTON;
			tbb[2].idCommand = CM_FILE_SAVE;

			tbb[3].fsStyle = TBSTYLE_SEP;

			tbb[4].iBitmap = STD_CUT;
			tbb[4].fsStyle = TBSTYLE_BUTTON;
			tbb[4].idCommand = CM_EDIT_CUT;

			tbb[5].iBitmap = STD_COPY;
			tbb[5].fsStyle = TBSTYLE_BUTTON;
			tbb[5].idCommand = CM_EDIT_COPY;

			tbb[6].iBitmap = STD_PASTE;
			tbb[6].fsStyle = TBSTYLE_BUTTON;
			tbb[6].idCommand = CM_EDIT_PASTE;

			tbb[7].fsStyle = TBSTYLE_SEP;

			tbb[8].iBitmap = STD_UNDO;
			tbb[8].fsStyle = TBSTYLE_BUTTON;
			tbb[8].idCommand = CM_EDIT_UNDO;

			SendMessage(g_hToolBar, TB_ADDBUTTONS, 9, (LPARAM)&tbb);
			return 0;
		}
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case CM_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				case CM_FILE_NEW: {
					MDICREATESTRUCT mcs;
					HWND hChild;

					mcs.szTitle = "[Untitled]";
					mcs.szClass = g_szChild;
					mcs.hOwner  = g_hInst;
					mcs.x = mcs.cx = CW_USEDEFAULT;
					mcs.y = mcs.cy = CW_USEDEFAULT;
					mcs.style = MDIS_ALLCHILDSTYLES;

					hChild = (HWND)SendMessage(g_hMDIClient, WM_MDICREATE,0, (LPARAM)&mcs);
					if(!hChild) {
						MessageBox(hwnd, "MDI Child creation failed.", "Oops...",MB_ICONEXCLAMATION | MB_OK);
					}
					break;
				}
				case CM_FILE_OPEN: {
					MDICREATESTRUCT mcs;
					HWND hChild;
					char szFileName[MAX_PATH];

					if(!GetFileName(hwnd, szFileName, FALSE))
						break;

					mcs.szTitle = szFileName;
					mcs.szClass = g_szChild;
					mcs.hOwner  = g_hInst;
					mcs.x = mcs.cx = CW_USEDEFAULT;
					mcs.y = mcs.cy = CW_USEDEFAULT;
					mcs.style = MDIS_ALLCHILDSTYLES;

					hChild = (HWND)SendMessage(g_hMDIClient, WM_MDICREATE, 0, (LPARAM)&mcs);

					if(!hChild) {
						MessageBox(hwnd, "MDI Child creation failed.", "Oops...",
						MB_ICONEXCLAMATION | MB_OK);
					}
					break;
				}
				case CM_WINDOW_TILEHORZ:
					PostMessage(g_hMDIClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);
					break;
				case CM_WINDOW_TILEVERT:
					PostMessage(g_hMDIClient, WM_MDITILE, MDITILE_VERTICAL, 0);
					break;
				case CM_WINDOW_CASCADE:
					PostMessage(g_hMDIClient, WM_MDICASCADE, 0, 0);
					break;
				case CM_WINDOW_ARRANGE:
					PostMessage(g_hMDIClient, WM_MDIICONARRANGE, 0, 0);
					break;
				default: {
					if(LOWORD(wParam) >= ID_MDI_FIRSTCHILD){
						DefFrameProc(hwnd, g_hMDIClient, Message, wParam, lParam);
					} else {
						HWND hChild;
						hChild = (HWND)SendMessage(g_hMDIClient, WM_MDIGETACTIVE,0,0);
						if(hChild){
							SendMessage(hChild, WM_COMMAND, wParam, lParam);
						}
					}
				}
			}
			break;
		}
		case WM_SIZE: {
			RECT rectClient, rectStatus, rectTool;
			UINT uToolHeight, uStatusHeight, uClientAlreaHeight;

			SendMessage(g_hToolBar, TB_AUTOSIZE, 0, 0);
			SendMessage(g_hStatusBar, WM_SIZE, 0, 0);

			GetClientRect(hwnd, &rectClient);
			GetWindowRect(g_hStatusBar, &rectStatus);
			GetWindowRect(g_hToolBar, &rectTool);

			uToolHeight = rectTool.bottom - rectTool.top;
			uStatusHeight = rectStatus.bottom - rectStatus.top;
			uClientAlreaHeight = rectClient.bottom;

			MoveWindow(g_hMDIClient, 0, uToolHeight, rectClient.right, uClientAlreaHeight - uStatusHeight - uToolHeight, TRUE);
			break;
		}
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefFrameProc(hwnd, g_hMDIClient, Message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT Message, WPARAM wParam,LPARAM lParam) {
	switch(Message) {
		case WM_CREATE: {
			char szFileName[MAX_PATH];
			HWND hEdit;

			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd, (HMENU)IDC_CHILD_EDIT, g_hInst, NULL);

			SendMessage(hEdit, WM_SETFONT,
			(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

			GetWindowText(hwnd, szFileName, MAX_PATH);
			if(*szFileName != '[') {
				if(!LoadFile(hEdit, szFileName)) {
					MessageBox(hwnd, "Couldn't Load File.", "Error.",MB_OK | MB_ICONEXCLAMATION);
					return -1; //cancel window creation
				}
			}
			break;
		}
		case WM_SIZE:
			if(wParam != SIZE_MINIMIZED)
				MoveWindow(GetDlgItem(hwnd, IDC_CHILD_EDIT), 0, 0, LOWORD(lParam),HIWORD(lParam), TRUE);
			break;
		case WM_MDIACTIVATE: {
			HMENU hMenu, hFileMenu;
			BOOL EnableFlag;
			char szFileName[MAX_PATH];

			hMenu = GetMenu(g_hMainWindow);
			if(hwnd == (HWND)lParam){      //being activated
				EnableFlag = TRUE;
			} else{
				EnableFlag = FALSE;    //being de-activated
			}
			EnableMenuItem(hMenu, 1, MF_BYPOSITION | (EnableFlag ? MF_ENABLED : MF_GRAYED));
			EnableMenuItem(hMenu, 2, MF_BYPOSITION | (EnableFlag ? MF_ENABLED : MF_GRAYED));

			hFileMenu = GetSubMenu(hMenu, 0);
			EnableMenuItem(hFileMenu, CM_FILE_SAVE, MF_BYCOMMAND | (EnableFlag ? MF_ENABLED : MF_GRAYED));
			EnableMenuItem(hFileMenu, CM_FILE_SAVEAS, MF_BYCOMMAND | (EnableFlag ? MF_ENABLED : MF_GRAYED));

			DrawMenuBar(g_hMainWindow);

			SendMessage(g_hToolBar, TB_ENABLEBUTTON, CM_FILE_SAVE, MAKELONG(EnableFlag, 0));
			SendMessage(g_hToolBar, TB_ENABLEBUTTON, CM_EDIT_UNDO, MAKELONG(EnableFlag, 0));
			SendMessage(g_hToolBar, TB_ENABLEBUTTON, CM_EDIT_CUT, MAKELONG(EnableFlag, 0));
			SendMessage(g_hToolBar, TB_ENABLEBUTTON, CM_EDIT_COPY, MAKELONG(EnableFlag, 0));
			SendMessage(g_hToolBar, TB_ENABLEBUTTON, CM_EDIT_PASTE, MAKELONG(EnableFlag, 0));

			GetWindowText(hwnd, szFileName, MAX_PATH);
			SendMessage(g_hStatusBar, SB_SETTEXT, 0, (LPARAM)(EnableFlag ? szFileName : ""));
			break;
		}
		case WM_SETFOCUS:
			SetFocus(GetDlgItem(hwnd, IDC_CHILD_EDIT));
			break;
		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case CM_FILE_SAVE: {
					char szFileName[MAX_PATH];

					GetWindowText(hwnd, szFileName, MAX_PATH);
					if(*szFileName != '[') {
						if(!SaveFile(GetDlgItem(hwnd, IDC_CHILD_EDIT), szFileName)) {
							MessageBox(hwnd, "Couldn't Save File.", "Error.",MB_OK | MB_ICONEXCLAMATION);
							return 0;
						}
					} else {
						PostMessage(hwnd, WM_COMMAND,MAKEWPARAM(CM_FILE_SAVEAS, 0), 0);
					}
					return 0;
				}
				case CM_FILE_SAVEAS: {
					char szFileName[MAX_PATH];

					if(GetFileName(hwnd, szFileName, TRUE)) {
						if(!SaveFile(GetDlgItem(hwnd, IDC_CHILD_EDIT), szFileName)) {
							MessageBox(hwnd, "Couldn't Save File.", "Error.",MB_OK | MB_ICONEXCLAMATION);
							return 0;
						} else {
							SetWindowText(hwnd, szFileName);
						}
					}
					return 0;
				}
				case CM_EDIT_UNDO:
					SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, EM_UNDO, 0, 0);
					break;
				case CM_EDIT_CUT:
					SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, WM_CUT, 0, 0);
					break;
				case CM_EDIT_COPY:
					SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, WM_COPY, 0, 0);
					break;
				case CM_EDIT_PASTE:
					SendDlgItemMessage(hwnd, IDC_CHILD_EDIT, WM_PASTE, 0, 0);
					break;
			}
			return 0;
		}
	}
	return DefMDIChildProc(hwnd, Message, wParam, lParam);
}

/*
====��־====
 ?   ?`M�g���]5�Rw[��i�oiR\���R:�r��?yW�z�����l��e��63��
\��2%��.LKU?	�z???>?*�`��?�V%�Q�q"I|>m��?���{6b��N9�t?k����7?��L�E�~��kb���^��s?��??�SF/?'?PXed?
�A��'<\`?��6ȁ���|#}*A%;#����??5??y=����}6�e{�h�R? �� P:!3�}3Q��??U��$pT¥C��J+e̖?_�U��Y�Q �Bˁ0??#z����_��?��A��?^?6�S`?8�h?��M��?�?t^,J�^??�f�c?�r}D��?F��l����
?�?�uO�z�Q�+S?�v���e��4ݰ����Ǽ��g�����{�k~? �q��? H?k��Y��AT�΃��.�Y<%N
�A��??&K���SL�ir��)P?S�C���?6�KQ�K�c��Hڡ�O��̓"����#��DipCT�#d�*?/��r/?>ެa0?q�
��0?�@pB�J@���@
V$��l�l
�lp��@m8�
P�?��?��
4�\!��Mc
_&�?�j���]l�N��ߪ��7�����\z����?Gc�ja�],[�~�Gg[?�fh?�O??�~ڜF�o?�m 0�Jʠp(��a?(�C��{ �� 2o??&��pC�X?�Ѐ?��?#?��3���? �x?A??.? 7?(���
xA�?$�c���~�T&���c���MR�[Xt�T̏��'�����L��?eW�M�]���Y��?��$2�@a?D��iRe@?�V��?a?'�e?g��?��ffKm<&�m2
A�F?2?�d��?��M���|��sA�ܲ�v�e����e��?�t??&b�xK,d??�b������?��BCl\/�?����ЗS~Vdr\?/H������3?8�{�wײ�~E?"?�?�|?6��@$�@4x?lB��?��,I��R�??�_�q��`��??D-T=��?�H?_�����????��!�rV??��y?(B?@L_?wU�P??j��:��;^ ??`Bh�<��5l?�E?��<^��?x��|!2�Z??)(���N��?vx/? `8?����$6$&�p>���pxI �h D�A���~J;��?�l�B��@
?m[*��v2
eT�v^�~<AFI,�E`t!?	6��L?X?�Jʢ�S�a?x|# `�p`�?�@??m �R?�`R?Ї�bPA��TJV;��??_@h???�J�otp?����P?~�x
A��dz;?2d?? j??�pf�I��>��?C�?4%V�g�~�|�{K???y??fa?�ׇ�´�����0"��$x!? ?.��K��^$?߶\%%`|$?�� ?_�����2Q?? ??�d�?���m]�UN!��@?��?���τ1ؔ?��X����<`#�b������*@@�PCP? ? ?? 8G�h�z���d�g��&��	;����Iӎ�?H;?!+N?�
�� y��B�d��? �f?.Jİ�G�?G? 3 �U�XdH�	#�LT����(5	_?�r����?�@(?7���e򎄀:#�B@?s��?ք1�A�j7?_���v?(��`? �A?4?de+@~�h��G�Ug�b@?�l�Qyr?.7�O�{�l}���c?�`R����F%����Tl @a ? ) �� � 9(@��0`!0X*???KS�k?��;?��`;��?�G��?(Ճ�H ���Tߕ*?�A�L��@�P:?b��Xƛ+ ?Є!Ŀ	 ?*Ĥ�Azp8�t��?=M?���0F����Lmd�JT����	l�x��7?�b02����
?D�a����(��??0?J?L#��`?g4
���C ���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�{?��?�k��ًKbPh�C�P�^: ���?ðj��<��N�`<?����?%??H!*oÅe?h��D���P�Si��쏋�3���J��aZ�򯍰�o���若?�PA�?V��B?�^?��9{C�՟�q��8[��fv̤B�xAH��0!��:��>l�? �SC�@db01x7��1`4?��x.��*��m`X�J?!����Z�FsßW���ɂ�pmV��??�@?đ�vB?S?Q,v�q�^��i�v�J�|���i�挒�0!2ʤ�?��Y0�Q��J��BI�e�uj�@? �Bd!?S[N ??g��D?ُ����[DB*�X.J�@����C����1c_?> ?��A܊?��|m�VG
??����?��$Z�h p�CM?V\??`�H???�Q_?���`��ߵ*o��5�`Ǿ6��?,N!�a???X~��?m�a�Cx��!	#�J? :��A-W?=U��;+�g�[d�� 2KkL?RQ!�j�caX��U8?%��׀mP?�Ö��@-l.��?�B0�R��??]?1��Ϛ8?]����KA�h{<��I�KR?�m�Ǔozج�n'V��?)��~qn����)A?}???�`6?  ��R@?S��?�� zؔ%?`�$��K0��????��'�0d��B`�vĀ>�m�� �rz^#+eR��M��~:����J����?+A����V?��3A(�� �u��C?�K ?��Hh
�ىAK?�ѱ��y��C����?��?}-?
?�� ??0C0WK?T$?F?t��?�J[?vD�r4�BJ����
6��?o��?n��?e3z?A�M?�mL=2�|?Un?r�R+?T�����F�f �uJ��?e?�?��vw��;7���؈p`Q|�h��z=��
E` 0?��*D?^�A�@???��?��|?%�kE�mx�X6��:oUg?IJ�t��R�I�-2???Y�cN�P��ix��*A�Si�����lP�� �Q??�@�@?  p"?T;�hҤ?)v?b��)6�`x�D���氽7�f`? :��d�px?C�@B �~%�B �A? Ċ҉bO? ��KL�I���̪�J[?�O�l^
�i����x:����c`p3��G�H"��I?,�C����9H��b�UU�A!?�����jq�aSIU/�Ҏ�?��|<k�V=J�|�s�l�f???.����???��?
�H?s0Am3J��A?m�a�j��?M�T,_؍��x-Da�zPA�H?Ċ���ښ����+?rHL�K? "��D?�Q�Vḅ�???	l�X%T�T�o������V��?�{��q�s�^�@$�Ye?����4i
??F?��x?A�?��<�x��A�c�� <7?�P����?
H<W�����[v�Z��j����W��???dS�ٓ�fN��?�p!?? H>w�x<?�q p?@9!��\_��h?���B|9j7��?��ߘS?i��3���|֫U��9��Sy���i������i����[V?U��!k,�?��������@�����@?܀?��??���`6q�܃P�t����U$kʘ-68�Q���a�vl�hZ??2h�FSX؂[ߖ
���t�`?J�˨�o�T�D�d�^���p?��
0	Px����?�y�R=�T{'?����I��X<����U????���t��F��?i�yW,Α^�n0�l�mƽ���M�n�E4p�V}�~�SL{���{7lp<?&
����_n_���gX�e?`x??+??ޛÀ5??`��~?<W��?7��<���!��????�x?��?3#��6?CN??Iρ�i��???�@�\�x^�r���[ZހQ|�d?��?n x??��?R??�Ŀ`A&e��BS_g��j�W��Q>]�a??Ih??i����?Z]+�QX��@f�Am�z��գmwx�x`�����Z
�s1&�� ?���?��� ��1��+N
�d@�zQ�P;1x�{<??Ki�l�x�h�v>L?��Ei?��Ո?j<?K��*Ǌ��}uD�X|???L
1&��0���pBV%c`tHX�X�G��?y��~>?���l?W�m�[8dH̓%��C%?Ֆ֙?�ՠd�q^)`~��7��I��A;0]��AZ?�\�v^
��A�fKҶ���b��k,�G?�T{-Q�ݨ�ZpaD1��?�n�r]^�� |��? �p&?��?A��!?°d��?l??嬠jro3n)--^)�s�a?? x%2��-no�A���W"œ����K�Ě�Hc��~	�Hx�u��+��Qux?�@�V?�\?�BP?���?�z!��R8	I��Y?,L��o?��Q�FK�g?�??����$2�K��U4
@
Ysi�w�h��?��e2F˙��y]J�~?ӥN_?+z��1N��E�����Q?�V??��?��?����6?��7�r���A& �G�^#	e���[_ 0(?�q�oՏ��D�`??1SK?��Lzj��/��àD�;T�r����pK�c`6?X2�Qcj��k?���rC�� y�ȴ`�P����6?��7�q�l}?�W�o?��~?�??��D �x��Ag6-U�`? a?���I �P��t�۪�B:V��?�h?l�|��D??H?$�mѴ��	�P��-?՜��BH<��?%`?��v����?JА��%�x?? q:v��հS&L��?���B�M�??��GgR߲ �A�D?I����`?�@߿g�ڬAkGʼ?c|??�Mܤ��x&?ɰ4����Dq
C����?;H!��?c?��Z��ׄ1��;�[}@��V��̹�z?��SfN/d^̋��?�d����?@x$A�����v����L>˿o��?j?j??iE_�U��Zl�K��s?�@?��=ĦĀ�Hh��腀!��??��@?��??�ҹ=?g�W����39����??(1p?Ĵ?БZ�� ?�����[I�`?A? ?\R?l!������hZ>6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6����??o?���b�o?����3?���x_G����?�̀�i88��ͣ�4? w,+cb?������� �Q$?JL?c?c?\%��0??����I��?g<��Tߚ-Tʨ�[>w?	`�H? e%��~hC ?|$$L�@Q?I?��+_??$|�L@0Jn}X)?D6?�xͶ�V��g�e?���{~�m���������wwm�o^�m�m��[e?���{~�m���m�{?����n��v��x<�����@?��0?�X0F ?K�� ��Q��TzJ��?�R?���hϳ}���-��?&?0<??��4��?���7���L$��
%���6?\���� �[C�@dB01p7��?�h6?��x.��*7�mdx�J?1��ɫz�Vw�G?�xzo��6��t??��
 07�d��?Ձ?G* H?P8���? p) �C??��AN?��pdj:w? ??�luU}��S�@??C)ς ?O�¿O?c��??.eRv�ق_6XT��Rx�a??H^$??؆�d�|�R��(?Մ/%ku��?�EeV?�L�m? ?0|��2Pp �8�PC?��`??JX8�ŀ?(���Fbd���S-3R%-��ƿ6�W??�cc�Z�e?��� `	 $*?U����f����+V��������e��������a_??�pK�� #0#?$? (�A)x!���\�T�t??XBL�CJ����6??�ʄ�BG?��̠2 ?AJ$?a
X~^�D[1�J?�����f?.*?�{ʒ*��cٙg�b x!B�N
?;�`�@;��u??8��03B�� ?Ǭ��?��?+?����Ơ�
/?fb��T?O�͉G��}��?���U�Q?f5��??��-@?D��4���E�x��?|�u�b�BH<H8$?V�J�zǛ �`?�AB>#?��Z??sna�⨐%��,x!�L�aؐ^�v>W�v?��7��oٰP��(7G���|���U?A�o����a�Oo��&aIc?s?�ӿi	@?��?	##?zϓ&��U����?��ݲJ�:,[L
��~!4Z�H0 ��?		Z�����X�e82��yGa? ?D?Q�@.lG3ǃ��?H%�IYG��9qzo�J?kT��M???+?3`???���B�S
��?�J@=^pzc�Y?$������>?�u?l ð?�ı��f?���tB.?p?��H�8I����~���c~!������?SVxa??��?<<�??�m?�l? ?��o������u\mޯ?��?Ã xC/V
�fA�?A�x?G@!6??H��&+?İi0z��??�~�IqP���x��??Px8@? �R?v�J@b��VPx���DV��J a(�Fh�p< ���Me��?UC? }=-N8@�� <|¶�Z��?��_RVn��?2Q?�\:B@�V��? 95.?�De.�[N?�[�{?�c���@������vLpx?�Đxx��?u��?p�Q?�A����t#��@2??C?ǀ? ?K?z#�H�GNY�ʹ�g��?�B
��!&d|??T��`C���p?�M7�p?�v!�yg��??	b(<?ּ^�r���Xf@?Ȉ?!��!�AI�p<;bRpU���|=+�R�D`?ȶ��¶���Z�_��r???(���x��E�Zf@�uJ��>e�Tw�G�����yE�h0���@u@?���G�q���@|?��ޛ��S_���ߍ���c/L@Ҡa?? x<`^�}�?B �x�A��%m?;~
�K�{1�c�a,!��B???�|��֧a�����hZ�A��<"X��@H Ɂ�?a+�?>
�b�lDp
��d?P(?%' ��/K?�S��
�Ɂ��h0?#�j
A��q)?hݦs��d�R�i?cV�X����v̗m���j?w�j)ۼ�m��Oq����R?7��b@�Gh�|;���C?�aP����a��?m.??��A?�V@�?�`?@ģ�R��? ??�z
 �C%L?��a$KJ
?Ji?��7Ǌ�PP���A�A�x3����??b��?p` e`?�n��aP�d���H$?�㵠e! IT^#G��E.lp�K8��A�`?!?J=��?���K@��	P�J?�Yn??�B.?$?A
8?l�]?:���s��0Ci�8������9��HҩYV;J_�懃��^ԩG??����?�N�|Jġ?@d��6[�h
P��}����?���t���R3�d|>gl[c?��?�@e�|I�q(|_���wʘ�Ҍ��I�L?D?�I��[l&��R*�pz��lܷ7,�ܼ�ؼ���y]�����sr����͋Ye^YV��?�`;N!?��K/��R�z6���xAd?6���U��YJ��t�m[����A??��?"�|���X�����s(2qI��P3?R?h��U�p����M??�U��?XQt\?G�Ҵ�q&?<k?���C�纎��X?��!??�<??`I�ʨ��\?4_|�\m�Q��G�k��?�J�ذ��N�k���L ?7?[?��_rp�p�u���T�kXg?����??? ?ڗ?�t|�����5�u���w��? �B?BSL$�hչE�wZ?'/?x??:���HW?$m?��?F���-�i?��W�T����
x????K?(?�azv�gZV�xAo�p�W����:? eQ?!P`��?D��x(Tn~( ��ٰ>,��Tq?��))?�Z�R4?����?X��R??TY6`0q��"�Q��q�� <��P6�ap?��$��?��D��S?l��C?��s??|p
CL?.???J�T.f?*`�����? !_b]R�Fm?L??���=��#��?:\��Z����?��
��3�s�����(;�Xi�e��TȐ\?VͺʼkX��[��m?��v��}C�����ͻߛ����Akx?�|�SR��/��k��}���M2�ȺA���etr? p@����N?Г?�W�`?T?2=?V�i2f��pdN��(��D�h? ??��?R���
Q&kG���t|���l!?y�y�O�qF��(�J?ih�Zr�J?����F���V��ڥ��NeG,����L?rel�����U4�i?����ܺ��Z�W-?��?G$R����(�Hr?}�j?K'��?��u�`�TYD�����d�t�c��{c�j°j�B(�J���~�����ok#�x���o�L�t?�����懀�Y0a,HC?z����?�@��@�?%��?�^�_%.NΥ/A?lv ؖ=d|<WU��?�U? b䠋U��Hm��v������u;-??���`=^c
��@��??X�LД???��sX]??T?h��hpZ?H����q<�o�a�M��w˯�k�b����p!��?KG
p��?~���sw���DI���{b0`QyP??&h|?K?Ā���?L?��?��W?�f�ϸ�? ?��?>`?���R#��?�����|?⦼�>5&5��f{$�O�Q$����?�N�x0Ai��X??����H&fK?k��?���Y��?T?���Ԡ��Q��F��"?�Iu
���b��F"s[m?i�t��^��i�շg��8T??X��=?J��?<����?��`����x���0Pa?L p7?�p!�xXS?J&?Ƙc��#gv?ӎӂ� 	)��K?�H%�B!��Ƽ\?$��J��?x?0F�|Hă��c)�Є�ZPR?t����P6?�u1pBL?h?it�B�i�����c?G��k
?B:�L�x���0Pa?L p7??0��J?��d?�H1`?|Y��l��sz@�Ts"�Tp�b?���j���?�Y8
η?_Kt=���T?KT^�dI(>0��?�CH�~?`����?��D?�V�A�s?>jg %�x���0Pa?L p7???0��J?��d?��? ��tBfs3
��6ɋ�	�PAR?ؽݥ�G��v,7୕�	 �p&?��?A��!?����?H#3�F�ɵX?b�V;H�F��?����r��_ٝQ�?��x�R\/U�W[˓�`XH2q�p�ZM.W�sٷ?Z��)&BCa# ���s�!�Lm����?@t@��?�?s.�p�v#]  1??���kI?��%?��?=/����� �A"?�ޅ�ñ?�xx?����)X)�@�h��
��}?G~?$? �_��|hz<�?T!5�����c?�_ p4k̤ǌ�h?q8�_���X�R8�E�ksY�<J��f��S��f[��?(?`����];c�xHA��??m�A?��<3�Y݆��?��$4İ:�C��Z%?I 1�� �\_`�aD���M?&J?��?�� ??a??˃b�_T9C��3���"
P2`
����(z:BBa(??6??�?�z>(?�@?2?(~=����?Y��?h|?pV`??Pa???�~����G�à@m�A������x>D?/??�C?
ݕ��f?}�c��?��?#=���WSa?uy??N`�l?P�XB?�Ii�H%?5S{��??��hyq  C�K4A�w��?Q�m������?A0"4???�^ �[
��o�K?��?,��O;ݲ����p(�� ǃ�� c��8~$�?J��#@???? ?��B^???б��p�IN��5??+)�B#�A��8�ap7���`v%�@wؔP?c???N?q ?�BX>��x�����lE��d?�A1 NxD��t?��??QF ?AD>H^?��X0@$g��N
z��K�?�h��tRc��A�L1A��۲s��\D�e����?F�r��m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m����o?���icu��s??��?����?tb��C??Y��#��C?����F/�V}���C?����F/�V}�����F/jt9ы?�iv��s??��?ϴ�mN?1{S�Ό_���K4��s??��?ϴ���s??��?ϴ��S�Ό^��s??>��S�Ό^��s??>�m���F/jt9ы?�i��C?����F/�V}��jt9ыڝtb?g�Cjt9ыڝtb?g�m?���N?1~��-?���N?1~��'�S�Ό^��s??>��S�Ό^��s??>�u?���N?1~��-?���N?1~��+��C?����F/�V}�v��s??��?ϴ? s5:���N?1x`X+���[jt9ыڝtb�E'?im���F/jt9ы?�X?9��C?����F/�R}cP`�
�Q3S�Ό_*��������??��y;V��z�^6��|߷?ܮ??,4.sp�d�qN��o��
��?~��?<
��U?? ��?�p?�aV��춯�O����{ɚ�oC�J��L`q潞ȶds��ގ}=����m#b�����?��L
?,??�VӃA??�X?NY��
?,??�V�fӃA??i��?���b@��RB���a?�n���P�ܛ�s��E�[?6??�	[~��5Q��d��	E���n�iR���r����8��T�[����0��Gͥ?��i?��6���v�f��۬1��������|S��???�Q��?#`������C��~��*A�g��i��J<�i??��+�_���UƧ;N2�Nc-???#�H?R�M? m[
��??��?E�i��?��𕁴��E�`G�J(?���k?c��?&�@���~???�B9l����trLEA�l��J|��?�^bs�dŻ�F?����	?�ffӃA??i��?���?@2{	?�ߓ�?��?�i�o3�m�e)͟�rǝYe���xy�����E�`G�J��p`"?#?ba p?`v>��?�}��? c ?�P�Ca]��fC���Q��_�X��J?{����ehQ1���tg R?i��?��𕁴��E�`G�Jc��c���[��A?�n??�VT�P p)A�`t�?��*��h#�B
��@?����:ǩ`"u??�XT>��[?V�#�R�v?he����ܬ⎢EQs?�6??�	XNY��|K�???D4�pKi?F/�����f�W��U`?�??��%�l~�cn�m8<`ɰ&�Uk
?�L9o?
Ec�ǴF/N��#:����W=��8n?%����6H8?��?�z2'h����R�g?l�D?i��?��𕁴��E�`G�K	�`f�>Z?}?�F��?���C��?�rj?l?~^ ?���^L��?�m?	 ��͂�z��?Q,��X?`} ��A?�<����?4z8;��@��`???-9h��?	V/T!R�]/J?`m80d????�	F�P7?	B? !'TΎ�F=/?޵k)<7?@?����,? =Z@=����tc??��4����d|?C?�z^<����܂H?��%?~
��risB[��B�J?
9�uP��m$\a�|��9|?#i��?��𕁴��E�`G�J9Ci��?���b�v?j�ߠ_DO]6*r�ނ��x?L�Gi��?��𕁴��E�`G�KH?���~c
d��)��{����?,?�Ӵ�?�y.�DZ��-@L��5��?�`m80d????�	Q?��`b???��`T1���?)}?�|�?l��Z
���`������E�`G�J��p`"?#?2;������?��v�YH�{�ۻ�;y��G��U2ʭ���V�V�n^w��,p��s49�F0�l
?,??�VӃA??{J�ھ}[�o7�TK?*8.??��94�X��?k~m�L���{j?Q��;)qU���έ�?Ͱ6??�	XNY���j�`?:#��x�v???S�Ɂ���hFi?8�GI?��A��d��?<҃B���T%%�V�C����B��S����S
�g�b����Z]?<?>�2ol�V�B3?o:�e��:E3i��?��𕁴��E�`G�J9���~^<n��?��?�L޵?��qe��Z?i��?��𕁴��E�`G�K??9ݳ"��gm�_�sކ��3"�c��0??A���x
V?�bH??�`��+�j��?z�/��́��"6?.5���e����^ā)X?�����v��羰~�b����E"?��gv�h`m80d????�	ChQ@?]��~
��R��?kRV�E��?=�^�O��n��h���v����Ґ��٪˷����"?�D?V����Vo�V��?wj�y��Z>fӃA??i��?���6�_n��nU���¯��
o�����v"FӃA??i��?��𕿶ӃA??i��?���,?$���ɣ�A??����BZd��^?��?�K=��?��s��֮???s??��-lđ^���[X???9-��,?NY��U��;V6??�i�Y�lo\?\&=�����E�`G�J��p`"?#?�J�9��po�|?�xj?
	E�]�]���v�����s�����\�t����??,??�VӃA???(??* �|��NA��??N��r������
C��Ja¶�qT�Z�h��NY��
?,??�V��3?�B)??�?:!?�? 8�O?��JU��~�y?��???�}�WTE��<��?[.�E5bN��?ӃA??i��?���??��J<V���̎�? �`�AG��ā%P.?c�U�p?GM4?G�~�K@`??	@����?�� ?'ď�R��Dv??��Ӷ }??���Vܞ����=�b_��;C?P�?5m����E�`G�J��p`"?#?
eC���T#4
v ��A������C��z?�x!%?��?ZGM��b����q%6	�j���� G���X?(|Ұ`?~В?	JK�l��`?����?'/? 9��	ljK�Z��T��2�c2.-�?+����j }?
Y
�G�`m80d????�	K??w?M?EC�lXX�~V;+ �گS������S�NГA@?�K ?Ĵ�X@?9�w?�D?�|A�F|��?��o|`�v;N$ x<�W˛��?@9G�}??�`p-͒)�c�?�@�p �P�� <T4�s��Ͱ6??�	XNY��? �d��?ֲ=Ɂ��a�@@PQ���Ѕ?@?�Āʂ>N�GM'�`6%��bZi(uxKL�pC �?�xA'd��?
��a�BV�I?tb|ԭ�碫��ݿ��?���??�Ή�?G<��,sш��L��p`"?#?`m80d??h0a??`|���x?��}Z�Q�A@j*��z�Ac�S3?���@�|�wK���o�j�\?+VW??w
��NY���f]A??�클��E�`G�J��p`"?#?(=N\:m��	��@2���l?�������CT?gy<�I9(?��j? ����fӃA??i��?���^
0f���蒐F/������-?i?|\?%O��mKQ??��?�?�ӃA??i��?���^
@?AN��`?��?C?A��T�Xq;?�DB?��>��KL����eqC��,��3u� �W��-�X!�][~ٚ���w��?S��?�c���v+??�r��M?EC�B6?NY��
?,??�S�x^9a����}?k�s?l����n�wrfE�8R^?�Je�BX��!jq����p(B??
?��0<��@0c���T#?�e	�y]����c?Ɩ6����.olS"���r�IssW?�{/g;3��O6��p`"?#?`m80d?�``OD4?#��Pi3�D�Yx��M%d�B�aА��G�\?.�H_�FE[Lؖ> ??!?X??L<T%�Q�Q?��S Š���oV?�����ٶy��n9�C%H??NY��
?,??�Q��NY��
?,??�V����??z�}}4د����E�`G�K-��+?��$�YP�|>,??@??AL���p�?
??B�J����LX��?��"?(r.y#��)�W��@u�ں�Xm???�	XNY����?�p!�`ŀ?� 1P"�?��?H�p�?c?B�J��z
H
P`?R�?��!?��x:ɀ�K��OӤT�5��y�h�z%$ڔ?H1j�{إTd��ۋeQ�X�X?�H?X?�P�`��ɼRW�z�P¹?ӃA??i��?���^ ��:������q�eTy�H0(A��H<����@��~ S��cM@o(��$�X������� 0 +?}!u?��?0/����S&�J��EY??���`B/}?%???H��oS<3��\�ܥV���Z0���??6��p`"?#?`m80d?? ?&R֓ p7���K/��A����{;4BG�H6?0P&a6�|
K?K��EC�`?ar t��?�|
(?m�D?��<1���B@pS��C??����xx$?k[L�?6�Qjt��~�]t�?,C?S�⼅7 ���`m80d????�	lHT:L:!.?��
?����?4?c?"p! o?3m��ap��HI�@�Sjն�f:��\%?�xt������ ?������u(��K0AQtA�f�A���|?N%??SJ?S?��R��?��Z�ъ�yX;(l~m��??~�}=tث����E�`G�J6hoA\?\&k�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V�FӃA??i��?��𕿑����E�`G�J��p`"?#?o�`m80d????�	[?NY��
?,??�V?i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����
?,??�VӃA??#i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����
?,??�VӃA??#i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����
?,??�VӃA??#i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����
?,??�VӃA??#i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����
?,??�VӃA??#i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����
?,??�VӃA??#i��?��𕁴��E�`G�J����p`"?#?`m80d?��06??�	XNY����???�	K����E�`G�J�om�r?N�J��[g��Y?��FN�;j;d'	 ?>�u;!?��?H?NP��ju���A#��Q-+E�浕l??ڋ3"��l�׊�(ǃ�G���`?��c#��?�a���Y?)���s??�|?Y�`?�|��?$(�ɚ��� {?$��jX�s��!?�{dql>��聿�?Z?��l�s�d�J��?�AV
��+��MZL��Ƌh??��
�[��i��?p��E-,??3��  �f�RZ#(�qb#��qv���vէs??q?��W3߀��5���ە]gqx�����MD$?��?a�C��~R�~?#[���}D�f����K*��&f4��??߂? ��zRxl?+`t������/eW.n&�? �S��j?���W??C]�����g��%?b02��?S&?���wq
�e?2ʏ+��ԥ�P?>?��h��2v���A��ĩ垪զ�5(��W?Hχ,|�I?-T Z
�<W?�ߺ�A��7�T��}RZ9S�b�o��?췠D��(?X3GC�N??N?p#�Sc�j?J�i08��B?�x��\???�?�@?����*P�b7&`?�t ??�v??�ia��?*��?B
?�??@xO�[@���W~�o�G�����p?��?��]�ܼ�?�A?v?0?!??"�[ X��n�v\����f�k�J��)5	�Q_?AH��c�PR�����{L��q���_ce���P?O=?��?򿂱%��?���mF��\#����+p��i��?\?���l<�I�UGB@d��a??�����s? }i����*�d`��0? �@#�I���{?? �\
��C?("?��
��
��??�ZБK�a?],��P���*��-�P?T�^򶜻YU��S?�yWk*2?(�n�����g�Hp�znd	 ?> ��6<�{��?�G/�A-��wá??��/? ?R��?%�ڢX�p<�c?@^l�T &��P)[Tʘ�fvR�j�q*�U??��.?,g�]�@�_����؃fJ��P?3?�p����iJ$uq["#�x�AD%Zu�o?? ��WAJ�`^$�d�[��?@yS#J��L;?�A??8??W?#O��&��@Q�M��Ga8d~h!???��GM����?��?|��?���D+Z??��?O"ױ8��R�Y�?ƪ�
?INBx	B0�I`��?*�@??Jg?(!Ff��?&��?��?J�j ?��:?G????��J>č?�XH>?dklw��?g���б��z��uO?rD��?��Kxa+u�m����?̃��e��?̃��g�܁�?<<?�h1���v??????lx
?��$Z��`,�@b����P������ڣw???��'����?ڴ|*m??c��Xa��[n�{;�d��;�H��?`8c��P??���K??/M�Bw��?�R�[Z?�^�Ř`T ͉ ?M��R�{12l?���©{?�̝�0<�Ae�M9?�[��2�Cn�d)ڳ�p?�� ��? ?<?<�msD`�^��B�x!��^��?��ֶY��GXd97�qІ??��){z9??v?g��Uu��lJ?T��UU��*��M،V܉@?�?�L���"�w��?1(�q??�����?".�� X�DP8M���?? x�??'m$�P��?��G�K��?�H�s[>!�͵�ꠅ�k@g?G����L�E	#?P??T��? ?���`<���?��J DN����?ƕ�}�n7��?/L=i��%.N�m'.cs|?*^?p��}5��??~��K��??����_/o7����0aK�U�mSi?�����y?����?.\��?>ݍd¸�T?e��?����x��@,?E�b��? b��đ��Kf{����K�Jγ�黻=7j������?��?�� ��g? ?Q��~? |?dr
&���a??��?��?����+l ��??���b 0?~��M.$
��p,+9z?�s��O����??7CѲ?��;�F��0p(��J�H8?ŀ?��?
��Rqntr��<??�Px�G8��e ??�U�s�ER?
?0<Dc�e ? <�?��?A?��e��%Px��@?Q��9�qn)?��?��àx�A�`=`<???�X@��〈�@8?,
px��? ?��x��???=09#`ˉ"B��J�N\���s��?Q�xXl?.�@|?b?h)??`? ��z?��?��?X)�T?�ť���?? j��20����1��lt�@0�^?:?3X\$ x?@b��f?���mC��������Hy!��?>?<, ?<O�`ð|���Fӂ?? AI��$D?�Ñ?}O����PD4��Mx?T��@<���0��6!��?<^?lPt�AX[|�@�D?4?��T��}B�U?
Aڦ���P?��`R}?>??P2͇�}X+?Һ��?+���
f@�;T$$�lG���wĽ�~.H�lǣ?4v����?ŏ?
?o?NX?)h0)��?b��U??WX?�?@���a$J���%*˄vZ����>hI�M4^\J�KD?J����{cY��Gt�����7��`. ??��`. ?�� 8~?��,Z�F��� �L. �h?t�i?>)?t??N��?�F���E9��?أ�ⵔy�ڦ��f�ˊ��gڻ8���F?��;A/��?fm`�v>J��/�'?��r]��Gw'Q�F��L�{qR��?�z�Lzy��[{��?��^����?��	BF+��?Ck�D?hq??@R�\��G>�Q�p�b`E �L���� h0??%�BUO������a~	!�Saz����B��_S????v�K�����Y�C
�{/�TA'��f��mY?k�?���[}�~(��Z�ʊ�T���艸�oA?&d�x<�tC����F?BH7��?L/l�焄�Ij@p�A,!??v��3=??��Dh?L`?��SX �_B�G`���Ȍ����@?��1,|�_?��@?ġ%SU?��? ϧ?����ֳoۨ6??�A?+?�}�p`??)?p??�L�J?�J??����>W����t�P?��L????��?�`?Ʀ/M?Ĉc?D�`��	 ʄ?PCe%h�؜v���_�U*�mRPB�҅��>��ܙ�Q��4`��4I?+n��?�D x�G?��?��4A0Q��??)G��@�}?�E`GJ>�?��{'�L:.T�p
?/N�a, ?d?�J%b9~??g��>?���`? ��?ot��?��O������0T�@=0]?�nq ��Lr?/���?!�IӪ�v�V?X���i����?��*O�dV?.H?ڟD�3��?�W�f]A??��? ��?����PA?��<<����?��A?	J?Uz���~�E�zw��{%ݲ8V>? ��?1ד??��4?=�D/?�j�ys|�Q��V�KvL?���,��!��`8<l$����??�PT��m	W��g�o���Ƈ�jx? �d��_j??{��?�oC?k@�O��?<�x8ᑡ����tx�t����*�� ���r�[8?j�UAZ�Z:9�?`{����#`C��? ؒ�GcE��x��A.�m?J?,m�����p?3j?M[A??�����?Zh@����7K1S��-CI��c~c��!�s!k73ź�K1l$?CH�LJ.R;��܉�Ĥ�b<���v
�?(?A�x
?ÐxX? ��P.
? XvH78|t%�Dd?��?,2¿\D9U��_��i����^nYk�x<��̓�? �m�`?9$�?��??
����?Fu?�p?p�I�h\!	>�e��d?�ǌ��f��Mn?yC6�p�4<?��E��dv]t
��,<�b_0����vJ��?��?X??��iq?��p?J?N?�Q\�lŽC�y?Y����HB�`̀`(? B?D Q{R�ƀ�Cf*�xBXX?]�F��V��?��R��0lv%�Dt헎�?,�ʿ�D9W��?�i����ZfI#�Q"X??�j�p�~��:�a�I�{??ᥑc��?7��+��f�N9����??�?�?�~??��(�z$��jՄ�B`<���C������dx>f1�VK��H��8#??P`?g?1V��?��0�]q?0V�K�@Ǝ��/??���*?Ty��9���{?P�f��Ɉ{^?��??�ޡ�H(��K@�@�z?2`d�����j��+�����i�a��#,�����_?H��?�Ô�?��?����:��?�춯��2a�i?�P�|Ң��%�a2FL��i���f9��m�m?��`. ?�ea��?�PD (?�L���p�?c��!R�s�?s �p??�����YʋZT��@��?�~>9b���C?µ�r���LZ��?��*�I/F�S6K��A��`Àx��?�ŀ?
�x8R) 1P0v9-?*W?�x?��^#��.ƀ?������Z?��Ⰰ
D?HP8��������ƥ"���z�M`|�����M�T\?�S�b?�B������?һ�T1��H?[���꺬������©�V0�d�j#? h�?�� �BEP8<)�e?zZ�I.? �?/�So?a�x��/&�� }L\���E.�f?
?!�AK�H]G��E�BKU%��[�L?�@?�u
��'ݡ����xI?h�`��I??���?��
		 ciڿ?k?bH��q?��oxB'BW�?X��м��a$|\ؖ?N?Ï�M2J? \???�~�� �P��@`� ?��և�km��?LA0?�`?��??�{M�m?Uі��1�Zu���~��<?�w? ꠀ!�X�x?�@ �m	c��,g��0CT�T���&M���{��?���?@?CJ!��^?��\U?`͈��#,�Z�`?�?8�p����L?6����?�f�S��)���e�q?5,�qB?+hoA\?\&\?��d. ?�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����%����՜)d�j��?V>L�W��U+��L2�~??|����˟����e��p?g.ˑВ=��c�u3m����1H��.̻-��?�?:��JB?��M?A$�H��:?F���I�BK lt?�PQ$y|������l��4? ����??�t��s�ՈI`��f�A,??��"??����+Kx~
 o��i��!6��c�C�a?�C�xʺ��#?!��b8??I���?4��? !�k춑G?���AUT	B[*?��7he;8?��I���̭b��X6����e?�rW!U8?v}_?v?e�O�r??-*�|�E~Q?�Q�^??��m�`+��	I?c��V?����}R��?q�2
F�hz$75�U?h�if?���f����X(? G �QU?	��"��?f&�n�T1��{�gdk��(= ?��Dpa?"Rb֘c�P2�C??��ZOx���y�����k��?l�ոo��$M����k?eA?���?<O��?��?S�WB*?�)>��A �PP�x�Y?XT;eC??n�z�{)��??ҦGI�[%͏qT��bD�l
��S�@hIjx���������K�CԢ@� ~>gU'aO�Xߖ?c~��߷a��J�c��L�k�DKʎ�UaJ�m���j�B?#?
?b2VVa0?Vݓ??��J??�lHƶ�[?��M�W���?r[ߖY�Ӑ�l���b����?�_4�U?��%��Ao[PZ?P��y:���e ��x_�X��G	?���eW�ƕ�F?����������eި?�E((?��n��?BM��?��k�����I��SF�e��os�O?@[?DB6?�b?4$?�q,F��?"�e*�`P?J?������?��??��["��	?\����Zf���w5Cmm��N[��,�[*��fIu��?ɓ?��$?VƗ?��L��l>?�d��X?/��"��ð9?
6
t??XF��ZR�f?pp��jT�l?Y_TN&?hN??��+�M�B9x��
�ix???�K�O^S��Q?>
A��=�r�hJJ�n?�MH��[��?��G16A��N�5Zh~FK?L?|r�vB8��& p�]�G��?nV����Bײ���Q��X��?8�ֵH�KS+H�s7;��v?D�j�~�e=�g8?�iY_��%D'l??��9s0Iǥ�Ve�pG.???|!ߖ4�B��ҭ?|��_Ij��Re����@L>w��˒}6�G��B?rq?*b?]?ⶇI5<��8�yE@�DtɚI�A�Ќ^��?����?5�`�?��?�NL�kU?Z@a�C2Z?�T
`U`���N${��?ؑ(��?��?��_ҧ�C�IӰ�[?�GAP?h;��M�{?��t�d$-???ࢢHA�`?H2?��̪R��!�����mD����("y2?�O? ��5�h>�`x0���������AW懑PoA��|�[k0{����P?�H	��|~�i�e �@��~%?6�v�媂2�����}�cQ]S���m���l?����?�b��S?}�eͤ��I�Z��`�[/��?u 1��W)��B	Q?�d�eK-T��3��
?��?f����. �b?��7��? 0���SQ �v�k>/�x?3?X(?
A�� 8��L&OZ��hAVӴ�@$	��1�ΏG? ���IS?��9ysc�@�?ĕP��~?r<��q?�T�u��?����W[.?��C���x"0;��`�R??T��as`?BI���S��k?_n��Ҿ?k)��D?d?;??aE?�?��?``<#?��0փ?'�[B01n&b��?%??j��� �y??a?�p0@?��s^I�x�A??D��U��*6?�n?������?CbRaH.�Za���#�~^?�Z���IN>h�[M7�\>M{�q��3-�U`?��?���p���?��? ?đ��R?�j?�S���T4�\9%\�Fq��QV YB�m? �Ce��??1?(��oʃƱ/?,Kg�� |�S7���c���W2 I??(����� s?S�^^�p�Z|-?��@h?��S�cn�m
??��$?�J3|p??q��Be?V ?�L?g�S�o�c�ѷ�D<�?0
/��?{����BFG��y�@U��g??�_lq4��?GmՄ R	`�t;?T�??? l��?Gm'�k��i��M_���ϲ�8?���K�Z�dި�Q~Yy��25o#~֪-Z?re?��ly$�Ū��Ƈ`��	??�?t %І?�� {?��%?�C�uRb?���s��??:ə��?W?p2vD�B ?����?��?�R�]w?�MS4����.l�8���h?���p|�G?`??0z?�Q,K?&���??c+ ? ??��A،:n5�+UK�k��eγ{��C~���vX��"P?7��%VҜ?��7*�iT��_4o?? �x��J�}G? z�m?????�X��o??���J?�z[*��?�R\6����?7?@?��r�E`t�G?c??��D�Dh
?ZZrYk�mSqCl?��G��6w-��U���a���U����X:U��u�{*�a"��k�?Z�d�ӧKZX?z�⛷��E�h*o��?˛�缝W��y��[yDh?G���_�_�??`<,b�l���:�x^??�zA$|��|�tñ?�W?�?��Sn����e����Lh0??`��pQ����Iď?��o???���a�ny�˙m8<$ zq�a��}KjA[?����?p�e�Oͻ��D��?�8�����u@��;̀T��~:�S-4_����?cIs��e���U���^���ŋ���=T��1v�D??v�Ri?*g��֚��?t ����ĭ7��P��? ?0?�Bl
���ʇ@ðaІ;�u#TF�`C/�q�y�z??~Hi�fA��~�[0?:��n�g?��Q�vw��?����͟n�~j<G�UʉgJa;Z�A�x��r���J/��/h@�K??�T?��M��?qr��?�}�d^)l?!����?eY��?��3sF;���r͊s?���~��~��͋l?��?G0?@�a#@֤?����=�V*U�@n��l�_����? 7��?@��??L
?&h~^? ?��]�T�[I<�fk
ƙ��~��Ti�����͹��?`?/B@???IՉ
?��?{]�Ej+;*����???E0?`�e#@�IZǿ?[�T?����~�u??O?j aE@?izd��? ����?��?C�S�k��/NϕV??}?oq�k��?^>?
*VڦZ`?�����Iq���_�c9�sZ��?��??c{��Ϩ��`*a,B?��IH�z�ߙ�?�f���XJ����*y�o?Twv�Q���*��{�k=?-?� ?Y�� y��e?"�� ����4�q#Պ�j����?"i̸�4mX��R`� ]T?K�',�\�`A/����ږ�l�Q���??�q$JN\?5�Z��?Ӫ4��?9qp<�c�G��?K�????G?&¸3@�|J	^???�j?m���O0�@�_��6�X?D���}<�l?�Ĺ�d?�BF��?ښ��x��US}��F����-T?��?"8?��"X?n0\\�w��:��y�d��e��1�e���n��C��`��K?05C�~5��,������f*��U���DC?��fst^��v?�W0 I���W0 I�kk?56*�B7?��?;{ ˽���p��KJ��JH�z?O��b��N�[u�T�km���ey1$`Ax%��?Q�m�����B ��M?W?�M34yG��	y����?3�������t9Z??�\�?�i'->K*�V��r��IV\�팾e�G��,l7��e����2Z�GC�� �ʤ�Z�QUC�%??é6ڸ��o��/���Q�� �����]p?��??Ľ��+W ? ?1����K
3?z��-M���k%Q[+J���n�G��ay{l?6O�S�eD��?x�iS
hjf�GȌ`�r�S;�@�A@��$~�b6'��
R��?��?��/K��??C?��g��?���_	i��L#!?}W��
��?%����g}�@���U�Lҵj�}4��?��oß_)��8F�|q��x�H?'��Ձ��?���|?�?�mj��!(7AMK�A#E����l�fEdF??��J
?6?Rp????
!	�jX��??��1TqWڕ? ��?B��,�|??b8)�=P?%L���H�x*?��?��m�� ��t����l�y�ny;����xYŧ��a3�~�����m?@?Q���~�~	x? �}(< ?�x
q?YT�l!?�ӱip??|x]G�C?�H`�B@?�`WO�C?*d~$%8��9x(B+e�h? ??��?Fhw?����?�Ġ|�`<??�bC` hC��A�!?Ԭ�lxЕ��*���ʹU4? 6�v?`��@b?m�S�?2��tXS�A?��7G�u8����Ô�����?�bV��"����P6��:�cMK
�|U�e��e���i�Yd?�O��U_i��B8�R�v�h?�BYp3`?#?�N�A$K?�j\>�bJD��#-?�O�R*?%��8? I1??<W��?Y1,��T��ð:(����?A?GT?��4x�I?:?lKb L0`
�}2��G��כj��? ? @�a��7�|Bh�ۉ��???[KT��?"8��?(ġ�V�@@>b?�[
?��@|B/N;
f?,`F..4:?h??ҭ�y?�?�FW���t,�z��?��j?��r�J$��?J??�KC�A{??v$���X2LC?��?6ď�J=��?S?�E?�]���pC��?��0A��F`?^Dp�?<�m7�"??n�@>�o?�ɆM�`?Ĝ?�`r%�x��RUU��;a?,��G�_*Q$+--*<��Q*v2?x�Gb?D?WD��ӈ�cv?�@��<9��Yzץ��ho��M(�`?l��_���EE?8/��?z~??@t ?A�?ɇ`??(
�p?��??V|!����ĥm*�I��H*��PAd1��9^��u??oF?��??��c��P�ڤ�
��
?U?`??���^h ��^2���g�s����??��`l6�� 0!�k̰��l�ϱ��h?��k�O������r���e����!��T�HbRq?'?�E��?W�4´?k�T?e?�s3�oٖ���IQi?H??z��B`|?��A�����n�@��V{��{?�O��?�L�M�JԈ
�y��Q��أ�U?QV{��F"�K7o��[wf?U�w��ݶ{����H.J�c�G�?`<m^�{?K�mQ̒/OH??<?<\����?��,L��QBHJGl?��V�X%\��!o��?J�F��p��ܟ����seQ�n"��"\>��n 8v^�����VUyH?���Uy=I�h)��)o��p?��4??$�B
����?�j?̎5�o�ݹ|?y?��o~����+??D?"b?�Ǖ���OY��F?�p8=ĵ�R�̰�ޣ��0'��T7?J/��$<���Q??��?o�a(?s#�Q*V�isl*ߴ�~��q?���rwKb��K���ƒ�? �P��?@J?U��?��A%��q�Z��,]O)[hx^ꠎ��P0h??}P!Fa*lU?�?~��-J?#Z7R??T?)�X���|<0�t��&f?�b??"۴��l?;�v`����g?eEI)?�?%�v?��\�Xb??_��m��s �p?#0�����b��p?B����J���X7X�g?
ʢ�F?�W0 I?��/2�l{?+WZ`x��l@???U?��e�$���k���`?e��\!{J��%Yxx?�s��?eQe#L ? !�?1(?��??Az?���?��|?ʔci?��:a?�Z�~a?�^d 'N��>$V����S8؀%?�g�Z��q��
��:l 	e�C?l?(s|Y????��@9]�"?��m
Tk?(Qh8��?=�@?9lB�?[
�d��pv?6	 0??(��d��(����z�Kw�|)@���h�F�� ?���`l?Pa??>�JQ?��aX0�H��? ��?H�Zf��IQ[���`YQ,!��?�`@�\:?��% ��-�L�����k[ݚ����r?�x�AB�U�|
?����?�X;?0|
j?�ǁB��
*x�C��7?���o T��hp ��?�t��O{m���l�Wr�m��?!FreP�� BCJ?��d�J? ?��>c�A�Q?6_/a0�H	c߰9�� ;D?����MD��z^����?RpR??�Z`��!??��C�AN��#*H!%?@k��%Z\+��?��&Mk�E��|K�}l�Q?Sh�Zh?�F���!4�e?�xy�UL݊��N
0��K@??��?08�d�ÀAg??��?V=iF|x�C�P6���EeX1��LD
?w[��N��|?q?m+#�U���k��D?��2�����}*?B��yp?h0?9?��_?��0?t�z�� |H2=D?��?�t#�p??��&l	"Wąq'�`!&?��� 2pa��*Q��ԩ��?��?0\�X?��d?�@?Q�� �C?@??��Z?7K?�����S����0,Tz#�`�K#�Dg���R1��(?��:�u��6�x �{T?��&�a��i����l[?_!7ͪH_-/Q�d��???yG???��$�m
??��$���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m����6���o�m�nRi��^?;p/ZC�@d?A?�İP?-��9�������?+L?
�d��?T�rA��?�y?����?, ?b:�샋Ĵ?��?jU{2j��?��?�S�n?��F����esE?\%?�i?��c|R��H��?? ��!��������x:Ǣ0A?��xU��4!&�?(7��؛??���G�P�G�f���f+����~���pJN;�Y���~۠��0~:�����I?r�i���a8?���r^a0e گ2
���B���6_��Iq���Y??����?~0\���P&? ��&?�z=�L;iO�J
A?�zҜ�e?�Yc�vM��[�|��GCz���wx3�Y?Խ?b?l��O{<?��Xa?0?6�p@d|
@?�p �bH!?�K?B��cĉ��?�pfĠB5l��B_��+��??����>���Y		R��C^�[H�~
!*L�sIw�d�q�ǭb_��-}xv����8 ��c�m�|t?hJq( ��7�����M����?�M��3O�H!�~???x$?&#?�!p7��j�Q??�׿�Zh>�x? uh�mYi?g?KviG?��??v�e�aN?�eH�j��>���`
(<��8��,!0�p@N>?�L
��a{�@ �]��??iZ?�dFĠa`~?��N�d���S����L2�`EL[���������n�f_?��C?��5�wxI�Tr ��	��	d?J�佨x��?l��=���!D?v?����$ ?����8?�F?�R}a��?��?�|AGp?T��?0@??��)rpn|}D���w?Đ��<��A>#��h?�ei��+m��?i��/
iJ
1��???��h)?A~�HJ9��`lx?��ϳ3㖵NfJ�w?�p!��C e��@?ix0���G Ń�S�d�h�Ii_O�����gX��?8Q"�w�i?�h��Ȑ�W����&˃A�L=`x[J��H?')��p4ؒ�D$����x�A�bC#�o<����G?	j��;�Z8��0(A??d��?_�t??�R���Gˇ�,?�T�}��<.V���
�ʘ܀g�ΟUZ�iYe*V[N?eZ?�Ye���m����m�m?m��m���?e����cD��E?q����?q�c��`1bY��?��
+ny2��?y�A?OK�Y�i��)�T�ϛ�ZZ����?ۛ�������ni��U��?��lZ�RvE??%L�C�V
?#?�p?�?�J!2_��Zƙ�����o��?m1s ?$M��i?"�H\h ?[��~?CN?����؝0�T~>s��?���}7�g��f��mV^����y��y���?�����jT?�}�u���ت��mIn��Z���-?8X��`m���F�����}�HH�kQ�k��t?`
lKV�JN%?Q�?/?c�K�HR=e?�dx%T��?X�|?{?9��?��?,k.ۍM����l�m��{m#w��[F��?�n����vF?;��?̃��e��?̃��g?�A?p0��9}?R)h�x:Ի��M&L\Ж?�J�_?��^:M��nkGB�����m(?bQza-"?
0?BN?�t��'k?	 �|w�ʁ��B���|=ւ 2q?�(t?�m�j���la?Zm��T����o��sr˖vx��- �t;b8�x#M?|^=J??��>L�z�I?Lc3��"z�pdH7R�rNvNt9��N]�ʁt�B��ޣX����?i�@�D�p0��?��Ɂ��?�X??�X馁�����?ք!��@T$h?���I0�C`m80"�hC? `
V�Be()�J�� ?'??��.?s? ���/;? [bC!��V��~%1~ %?9?O��T?�O�]�p>=.i,��i������H?q?	@?��?{A?�}?��D�GT��B?����?(��C??	I�GmG��y�Y���6[Ť�jx<?��&??�`�_iGom��L�m[�z�� x8 ����B ?0 bQ? ?��0?xb ?�`��b�`��H%��??w��V�؃A?d�z���o�g>??f��?������U�r�x>!�B[!J Ђ<iD6#����a-8��b��q;a���KG:W�y�ީ�S��M���h��\�R"?��??X#qr��?5?˼%�t:/?�?K�C��2T??
5B@?.aV?/�� ? ��fS{��???FA�U�e����??�R�b�f[??2?	^N
?K�Ή���P<"S yV�Z
?���M}?8??��K��Q�h��J?+B�z���������Է��V\+�Tx?���q߄1$??��愑�?J;�{����Y���S?�"��oC�}?r�Tk???�ŸiB?K9M�Q��f���|߁��J?v@�I??B?�?RZ��X��փ�c��PQ?U
�{|��Ðd?? ��)��|?��J.A
�x!?&�S�x��?�0
ղ�h!	/T�@c?	�`0)�`x����G~80)$��$�T���_����|???�V$?4�D���?���p=(D1??�|K? В=������j?�l�[Bv��g�g����		$m�F;fE��?hf??c?Q���^�p�����4��*3��?R?@TKĐ>^ؖ�c?vʁz%�d~^�g��S?��cY��;T{3"��??K`? 3C?[m���{?��?py?=��χۄÀ�P���`AhrҦ?��1O�gXO?����es��??��?&h?Z?-�Q��? 4?^�����qZ�u+jp��?���mX1��[i��UP�f|��Q�P??��}��
?T[+��??���愥c��eʒ%4��UC��c�Z����H?t���pEe�EN~?!��DQ@�r�^�O'��j���R�eB��
�g��?i?? eX��Z���P��P_�N�v<:?A"P@a?���d��?WT?����ʄ�x9���B�H38\�v]�Bhxʓ��A&??0%��J$��'��߶^�� �X(?6Ā
x�A��e@?!�K?�A??$�À?�r@oz?5��!*L4h��3M?KZ��Pf??z�ĞL$63?p?{�w�X/���}t��=dz?�T���[;[5�ckB�i&?�G��?7��/J??��!g�t	�P??K?lJ%.Ig���Lv��<i�x��?ye[`��j�c?����N��}�~��2
>?? ��?? ��$0�|?�E����?M�y$?%�J8JO5?��`(l.����  k�P߲? ?�x�G����2�N�`p?��aGj��T'L?y??���x�N?v����?���@6^��;P��v<��Id����?L=��??��?�@?0�d�~#?��'kXN?5��+c�G�e������[}�sb���e������68��r��K_Qb���O�r�u?p9��5E?�ND>��+�� �b�}����8?�x�\
Pn���t?`?? ?v?��?P??��3BP(?f`*ҏ??����Q-�AJ;H�vG?2f��D;N? 0?2T��@�����B[)U��̏�K�R?!
3L�|?bb�I�OGI��{Af�V�Qh|?,}Sb�ÕM��Qak�߷��\�}���m��s1_���f{c~������M?M����$������qB�m��;����$??�Sg�JE8om��+?��$�m��+?��$ǶLH4V??.4?��/��4]�Y����(?�P ��x?�W??g��/	??J��`? `�B?&��?F
��`
o�a?(D�i��tCM��??TK?`��e?��??�S��%��T߸=��V?α������si�`hC(A��G ?Kd{��?�G��Ĝ����?g��?{γ<ײo=;:�T�ܶe\�����O/�Q��
/7��.�Qj Kl?���??!	 ���?�j�`C?L???�x(?�@�CL��$"R��8��x<�ІҠc0�� �Yå@?K?����?�R?ʾ�����~?G�P?	n��?���an�fD��?0C`��T%?�Zh>lI-V?E�����l��5)g��TW?/`?V:A??G? �Q��?$�yV?ժe;-(c?���o/e=l*�hqw��ƭ?��ND}?[?�z@b_�?{���l^��&[V��썶�6���nq��?0
?��^ލ?u???�fXV?j��>��7��l���b��o??e$[`?�{�|r�~
L�W��ƿ�`'`
0?.��S�AZ��?�����`�V�̦�?/?	)B??ք0��-?b�� ?A�o5Dpd��..L?�R6��~��5@?|?c�����g���<fD��ZJ%+W??�H
 =X?�z%��?C��
����Ө�U�f2��1��84h�`>? �Y��??����Ch�RI?.����??|%���s`*��ʛ?�`��}?��f?��L(�Ka�ި�]����b�C^��*�H?�?e8�X!`�L$��@�I��?|B�x�|_YlI��?��������PX<j1<,��?��v>�Rv?A?f0?w�bpd`�V\
F?��A.m�g������:A??n��?�������ng?��My���r?���|!?ט��??�IvN_�Bۺ���M?��{&.���r�S��kc���l����ozyP`�Tmĩ4��mD^�ׯ��RfuFTz?��v?7��?./=w*�z�͈��Z?��M��
ǩ�X�ޭ`?���f$H�H���M?Sy�FD�T���f? �o��??Ψ??-��n�TV?)?[^e�`<;e�}���@? ���_�}�?ۖnn[,�q?Ƞ'(N?!
���lG?��R����[��x??�NNb�N:S?�A?�Gu�����l{�h?i(��K[ְ?a�����WcΈ`x �bpU x?���f2
ax�JN8�f6%�M�m�Q?^^S??f@ҵL�OuS-}�anM??=��Ŋ�e?F ��?a?Kd�a zb?@Ɂ�G���%?1�H?c���u2O?�S�����NC��a?z?8`P5d���G????����?5N���Z�����߹J��FH��??��`��d��??�Q���n*ġ��)V����1���z�s���T���sw�m��+?��$ª����x?l{dL�p���^��?�k��?<?�W0 I�JA��:??엏��@��?��S��
k��a����?�t}�y�W;j�U�ͥ}?u�M��4��}HU��s?��l??��6!��?���@\�^R:L%�cm��'�Y���C�we�PR�?A |= ��A���	�iR����ϳ��h��(j��?��C??4%?"v�{U���????��? ?!��?=?v��?��A?��(A��6?
Dl?Kąj��5?W?�^>lx??Xc>�l|
���a��_�uZ?
}��8���o?�W���ł��p}�T�A~kf{2��T�����UW<����8�t��?2
0��?�K��d�e��@L
5bBpe�������V�f?:?<��*�������V1?�k ?S��k;����̟n��_?�d�@p�}80�����恇��??�K+h?S�fD��B��?�z��/ج
?yR?��|=B���a?? ��a��Cl?�M���@N=? B ���{wS��%gx9-?/R"(,�Tt��?�PL��?1�HT��??D�����rv=?�����?lz??��R��2o��ꦺ�������V?��D��҃�@?c��0�X0?X:�_?*??*���W?M'��m�bn'Ut?./?8??�Ǌ�U����`���uW?�Ʉ�a��?Du &��*?JJ8Q����_Ǡ��uP�F�@ ɢ�|%?ZPj��?"BZ??A�J>N?��0@H���Q??V��?�s2����o)"�X?w끎έ�"��?��[��₝n(r~��{k�àAx9I?�����Z#��@�b�ǭ�ؔ?�c�P��M��}��ndN���h(�pR2��:?.��O�A  zfK��SF�Ge��??	l,_9a?KT��`Kk��CKS���d�|A�?B��x
P`Q��"�F�K�`>�KA)&? �??x��?)53bA{w���K���J�����S? 0A��(H?y?L\>L>k�R�1�I<?*?��K?qsT ��yh*џ?A���`+hoA\?\&XahoA\?\&_��m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m?"�?lF�`Ź����??F?Ѱ��??�ӛ�ĭa�S�K*b�e??A@?HՈ����A�v?���Z+�e5����[��7�]6?�u��??`�HH??�6?0^=�BYp<*��M �P??��l{+B2�x��@ hAִ@p|?-Z�U}P2@AI��`e�C�`?��K�ՉP?H=?�|
 d?V��( ?��@?e0��M'/duK��~��=��bX^*`�m�|$m�۠�9?��j;mc��6��?0;懪��J����V��0¨��+ԩ��5�hJL�Z?�BV&a�z*�U@?��?0��
�WR�q�G?P��?DR�Ajݎ�|8???����9b��`R�����v
?��|J
�j��M�U[?J��Zjk|�X�e@?2�@.H_?��Jˁ��a8�^^Do? qX0?[i�Zm:t��(U���]Pe!??G?kc�X��K0�F �@��??��p?	�Yz���b��?p�X??D����D����@?�V��?] ��{��?��?i/�F����jxc�Y?sZΆ�͘�b�\Cg?�ـ�򩨗G]{(u���?���ޜ/�s-M�mݽݶ�Q�W��]�̐Ԏ�T�齴b��6卶���Q%����-����S���XSQp�M�zy?`BT
 Q	B5AD�z\�tC �{~?/iX�J@�??$?2��e:����ۊ??'Od�]�T{'
��vb�uG!��?.?ܛ==[��,�nz?-�?��HX|І $�S b����8[IwGl��+?��8?t0`@���9��Ѐ#��?V�|;4<�`�VВ�P(�D?N׿?8"Za	����?��?ʓ@??��?z<�\ރJ?? x?m��3p�r8?��nI�pX42
@R̶%?@=1z��Lπ5����4��?!?'H?P?P�w��Ǔ?��^
>O�j�r ?>��o.w�qL�E��YOQ�F?-]gd浥���j�ʲ�.S����Fo?�T!��8�G?-?h��?��?	 �{��?L�a[BP��kc��sr?�C�`P��??Zj`(?��4??&��?T�z:T�~�V?q8ҵ*u��J#�`?@??|F#?�A��	^??0?��L?��U~?hB̵o��X??��6±�x3
c��4Y ??��?Ŀ��f??��T8��?��u,�~�|< Fa��|��mI.�Mrn'�B ??���¦�(�zJ���zSV�\?V$�m Є:�t|%	)K�T�??7s�aS_n"��S�C?;@??�F�}��?0?��b�4?l��E��͒��u<?��??��DQ���m����6���o�m��s �p�m��s �p����vF?m�f�vF?
?{a�\�㱳vF�}��n��o�m����??��a��??��c?`á86?�CL<�B��Q?��?4?2�^T�C����s����h��!����??M����q(?!�h7?BQv`3j��x!`)I{????���7�����r�}Rf��=N
/0Ȓ?L?�J<?C��?��BM��ú��?0����?�g??��Yy{J��v>lK��?�U�A?~!��?��[Z�Q
9zT�A����?a?oZܛ?M?���j?��
}??8��??�kb?0"?�h��;��P�p�u��<�5gGB@!1��z=dH�?�����^?Ra�d�l��a ��?`�kIB?<5:@B��=oA�?��}j?��J??��<du?��?��?ʙ��|?F��?l~��?yr��+L�e?����|����ٕ?`?"y*^*��??����hr�A(Ha �RT?Z^��X�~߱����bA�K!(0��F����qC? 1?47}
?��F�P?)Da���XBA�~�@b�P aR(Q?��`BA�j���>Ќε???�X�C?����IS?��7?%��]dCU&hv���NՏ���o��tЦ ?F?m�m�����+ѳ ��?����l??_�!{�Ɓ�?m�m ��j�N?}��e��Y�Ƈv?��KJ!�?u��|$x?����??�c�c��<�k�h�y?�f����U�ڵz<?�U��>??8@���@??���i�E����-Pd;�{)0�~G@߉??L�}�m1Oį���S��QuU��?��Zb<�E?���}?��??R��$��
�^�Q7��?յ~^�}��s�c��{e�L�Lʢ�Z����? d��\!irQ*�D?L P7?&�SR��/��UC����;X�Cv}O&?8\?�t?
���*a�̏?@e?�H#4^:Չ	S&�K?��������@?~g?A	�T>��9p)�ի�����V����"$j��aVg�]��Z?�a,m?+J^�vX
pDL#?<#?ؗ���??N#'?��D��͎?�}������?��?�ʈD��\��?WEO6�@$�� �P8!z?@�/hJ?	"H�!����GKA�g(@������i�u?)A?VȔ�X*Ǭ|!$�v?H�|V%D&?.�s!I?P����p2�K�@?L??0j�q�����?\K??4��Oz��??k٘ǀ18��8�c�x0A����?~??k%?�1?@?bQx(S{ݵV&Z���TYv��?��*C5�b��|��?�?$?8
?@?����j��f??? ��
%a�����A��?
��??���em)j��??B(bQ?C����b?�BaJJ�QAP@V`Q% �^��P	%����*���k$�K? ��`CNC���G��%4 �)h *e ����
�i��R�Z�e
&�oKT�� �fw��U�F?@�u?��v�� ��84#`N%$???:��~%�`n��?
?��?OoCz�[(�Ћ�P�F�K�q?333??����J��BJ
&?��?�xv< �`P	L�c�a�~f4%?wM�c??���?�G?p�\?L����a?R?��??����ġ#D�d@�lJ:)p2��=a#X??&�HT�����u
���g	y$�V��?���@
����?��`. ???_? l ��C��?.a��?I���i�Q%�C?͸��o?�W0 I���f��R�\��|���N�Nڮ?+G��E??�E��P6?����?Z�v�A��uP??���a?������
����Bn+B8?3?��D��q�q�cy��?����9��?܋O�FBə�L�a$?���wW�m�[H??��^��J"8�v?�q��v?z?�S?�oo�������}VҧW�mZ�Yo?cͶ?�0\ו$k7m��eM4¯B?��?#�� ?�̅�����?�R?��?�R��;N??lyq�U��6?I?[?ZQwO��x�A�G����%�l���̀m�ʵ�Q?�km��z1?"2/!KJ��v#�c���a?���ӥc?��4���~�@?f��<���w�?����wwv�wv�m��W�o��?>r!?isCz
�A��	2�?s �p?m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m��?�cfݑ����r��m?�f+@!�v�PCR�J����?�mSJ�i; Š??$
�f�Ӷ�JV�]Q�?/��;h��[�t{?oilV#???8 ͗?-�r��\??D?Rki������\�g��vˬk?T����?T��Q)H�C��4�U?��R+���t? ��P?����(0"�j�h�t?t??P{)B��U_? = ��Ki&���H?!��x�JJ
l
`�Qp2ubh����i8�<�L�̴?`�r ??���?��@���`7�x��?	?B <
�^
�㦇wZj��<��UP�vGI��?U�ƃ��e݀??8d??�m�����m�m���ނ��x?L��ނ��x?L�m�����m??0�vZT�_����^���of{!.�?��\�??��{��\dtX��@a�Q��J�K���Dm/ a�@N�x����/ԟHڿg��d�d��?y0�T#*???��J%?����ue?(:}[
��?dI��_���|?r>#@��sk��?t]�d}�ڃ�d��T?���� ��860=m��?<��(���h~?Qڼ��KWD��
�X;?��%�vKy�L0? ��??��m�m�����cx
?��	0�cx
?��	1�m?m�m��-�P��BH0?:\_�XU?2��?��?y�����H?��aRo%��8�{�?<1 )S c`?-6???��`CT?4?D&? a?�I��G�V����?AS~��>Y��t[�Ju~��첾�n���AХ%�pB�?��)?iv??�~�_*P?^?�ŊGՅM1��}�� h?�����ϱ�[k̴?��N�f0�e�e���J�7��??Z��P�_%BIt?���o�z6`?/���?0
?��^?���o�L@?�A1B�lɇ��ʾ�p�ݍ�i��0)�BM��f؛U����ӷ�a$��\�x�y�d?U?e�lBc��#U
���T�C(��??��8>?��7�%?��ѓK?:?��??
[(?��6$�����XC��@U'3��@\_�����`Q ��TҡD?)ed?4��@QA��T;��hu���J�~\ڱ萨{�R��? ��Q�z�S=V��?U*�����t?m?m����s �p�m��s �p�h�[rǫ,��Q����k-&�^?�WqR?Ygq��_���il*? ???m��? l���L��H
�ɢ@9���X ��??�~?2?�x/�|��y?U���8?�և�@��?0��x(�F!��,x]g�E�@2v=�u�D?𽽣�T?�tVa��eAƆG0p	؍?0?���R��pX)�ؓ�?����B��e-�qp1p��??b��;`A� ?��q�3?����?m����s �p�m��s �p?m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m�����m�m����?N {@����|S��??o?KlA��0??{G�E8<L??����?N {@����|S��??o?KlA��0??{G�E8<L??����?N {@����|S��??o?KlA��0??{G�E8<L??��o?P?YV?ӂ�JV?G??%+mU? ?�b��i`��Nf?��??|S��??o��Q|S��??o��,0�cP(l��?�G??`??ā�?G? ?[L�Hdt!{>?)�|?����0AL=m�������E ?���釉?����8=h?�>��c�`??T��[2?�h�� 	mh��Zq��!�L?i8>��A��0??{G�E8<L??�M��e7��
5�m�C!)?
E�AvNN�g�WA���J%x��>$�l0�#?)G��-j\ ?.�|%��?T�A��Ӯ­�P�� ?��"? ?C���Da
�BP��F�ˀ����#��H���??���T?*�N?KG�E8<L??��?N {@����y�T_+�FK?�i��?g��,'R?G�E8<L??��?N {@����-?|S��??o��A��0??��G�E8<L??��?N {@����-?|S��??o��A��0??��G�E8<L??��?N {@����-?|S��??o��A��0??��Cz
�A��	2??N {@���Ђ\m(<L??��m???& ��?�b??��=�|����؂>)��`h7�� ���px???��m???& ��?�b??��=�|����؂>)��`h7�� ���px???���k��)��[����$��?Y,G���Y?���px???��?N {@����r�U�Q??p?J:-��F?�|��"??.H���I�{����
B?f�d~��@�g*=0li��??Z?? ?��!���`a?`H�?6?�PB.K�z�p��K?M���T$�@oG�E8<L??��?N {@����p`�W��`0?5J=hz?GX?��i��?�ɠ��S4~�C�@? 52p:�Q+I��G??ҏq[ 
???& ��?�b??��=�|���RN:�E���a?��Vu-?|S��??o��A��0??��G�E8<L??��?N {@����-?|S��??o��A��0??��G�E8<L??��?N {@����m?��`. ?A��0??}%��҃���|����؂>)��`h7�� ���px???��m???& ��?�b??��=�|����؂>)��`h7�� ���px???��`�=p)?��l??*/
