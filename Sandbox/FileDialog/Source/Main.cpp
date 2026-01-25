
#if 0
#include <Windows.h>
#include <commdlg.h>
#include <iostream>

std::wstring OpenFileDialog()
{
	wchar_t filename[MAX_PATH] = { 0 };

	OPENFILENAMEW ofn = { 0 };
	ofn.lStructSize   = sizeof(ofn);
	ofn.lpstrFilter   = L"All Files\0*.*\0Text Files\0*.txt\0";
	ofn.lpstrFile     = filename;
	ofn.nMaxFile      = MAX_PATH;
	ofn.Flags         = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrTitle    = L"ファイルを選択";

	if (GetOpenFileName(&ofn))
	{
		return filename;
	}
	else
	{
		return L""; // ユーザーがキャンセルしたか、エラー
	}
}

int main()
{
	std::wstring filePath = OpenFileDialog();
	if (!filePath.empty())
	{
		std::wcout << L"選択されたファイル: " << filePath << std::endl;
	}
	else
	{
		std::wcout << L"ファイルは選択されませんでした。" << std::endl;
	}
	return 0;
}
#elif 0
#include <iostream>
#include <shlobj.h>
#include <windows.h>

std::wstring SelectFolderDialog()
{
	BROWSEINFOW bi                    = { 0 };
	wchar_t     displayName[MAX_PATH] = { 0 };

	bi.lpszTitle      = L"フォルダを選択してください";
	bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.pszDisplayName = displayName;

	PIDLIST_ABSOLUTE pidl = SHBrowseForFolderW(&bi);
	if (pidl)
	{
		wchar_t path[MAX_PATH];
		if (SHGetPathFromIDListW(pidl, path))
		{
			CoTaskMemFree(pidl);
			return path;
		}
		CoTaskMemFree(pidl);
	}

	return L"";
}

int main()
{
	std::wstring folderPath = SelectFolderDialog();
	if (!folderPath.empty())
	{
		std::wcout << L"選択されたフォルダ: " << folderPath << std::endl;
	}
	else
	{
		std::wcout << L"フォルダは選択されませんでした。" << std::endl;
	}
	return 0;
}
#else
// https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ifiledialog

#include <iostream>
#include <shobjidl.h> // IFileDialog
#include <string>
#include <windows.h>

std::wstring OpenFileDialogModern()
{
	std::wstring result;

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileDialog* pFileDialog = nullptr;

		// Create the FileOpenDialog object
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));

		if (SUCCEEDED(hr))
		{
			// Set file type filters (optional)
			COMDLG_FILTERSPEC filterSpec[] = {
				{ L"Text Documents (*.txt)", L"*.txt" },
				{ L"All Files (*.*)", L"*.*" },
			};
			pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);

			// Show the Open dialog
			hr = pFileDialog->Show(NULL);
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileDialog->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath = nullptr;
					hr                = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
					if (SUCCEEDED(hr))
					{
						result = pszFilePath;
						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileDialog->Release();
		}
		CoUninitialize();
	}

	return result;
}

std::wstring OpenFolderDialogModern()
{
	std::wstring result;
	HRESULT      hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileDialog* pFileDialog = nullptr;
		hr                       = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
		if (SUCCEEDED(hr))
		{
			// Set folder picker mode
			DWORD options;
			pFileDialog->GetOptions(&options);
			pFileDialog->SetOptions(options | FOS_PICKFOLDERS);

			hr = pFileDialog->Show(NULL);
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileDialog->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFolderPath = nullptr;
					hr                  = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);
					if (SUCCEEDED(hr))
					{
						result = pszFolderPath;
						CoTaskMemFree(pszFolderPath);
					}
					pItem->Release();
				}
			}
			pFileDialog->Release();
		}
		CoUninitialize();
	}

	return result;
}

int main()
{
	std::wstring path = OpenFileDialogModern();
	if (!path.empty())
	{
		std::wcout << L"選択されたファイル: " << path << std::endl;
	}
	else
	{
		std::wcout << L"ファイルは選択されませんでした。" << std::endl;
	}

    std::wstring folder = OpenFolderDialogModern();
	if (!folder.empty())
	{
		std::wcout << L"選択されたフォルダ: " << folder << std::endl;
	}
	else
	{
		std::wcout << L"フォルダは選択されませんでした。" << std::endl;
	}

	return 0;
}
#endif
